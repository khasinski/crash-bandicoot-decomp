# crash-bandicoot-decomp - Crash Bandicoot (PS1, USA SCUS-94900) matching decompilation.

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:

VERSION    ?= USA
BASENAME   := main
TARGET_SHA := b2af088a162e046ad07f532d46b655cfcc42a05c

ROOT       := $(abspath .)
PY         ?= $(if $(wildcard $(ROOT)/.venv/bin/python),$(ROOT)/.venv/bin/python,python3)
SPLAT_CFG  := configs/$(VERSION)/$(BASENAME).yaml

BUILD      := build/$(VERSION)
ASM_DIR    := asm/$(VERSION)/$(BASENAME)
LD_SCRIPT  := linkers/$(VERSION)/$(BASENAME).ld
TARGET_BIN := assets/$(VERSION)/$(BASENAME).exe
ELF        := $(BUILD)/$(BASENAME).elf
OUT_BIN    := $(BUILD)/$(BASENAME).exe

# GNU binutils: prefer mipsel-none-elf-, fall back to Homebrew's mipsel-linux-gnu-.
CROSS      ?= $(if $(shell command -v mipsel-none-elf-as),mipsel-none-elf-,mipsel-linux-gnu-)
export CROSS
AS         := $(CROSS)as
LD         := $(CROSS)ld
NM         := $(CROSS)nm
OBJCOPY    := $(CROSS)objcopy
OBJDUMP    := $(CROSS)objdump
CC_WRAPPER := tools/scripts/cc.sh
TOOLCHAIN  := tools/toolchain

# The retail file stops at the 0x800 boundary after .sdata; .sbss/.bss are
# not stored. objcopy reproduces the zero padding PsyQ's EXE conversion wrote
# (--pad-to takes a load address, which here is the file offset of 0x80056800).
PAD_TO     := 0x47000

# Compile exactly the units the splat config names, so a TU switches from asm
# to C by changing its subsegment type to `c`.
C_SRCS   := $(shell awk -F, '/, c,/{gsub(/^[[:space:]]+|[[:space:]\]]+$$/, "", $$3); print "src/$(BASENAME)/" $$3 ".c"}' $(SPLAT_CFG) 2>/dev/null)
ASM_SRCS := $(shell find $(ASM_DIR) -name '*.s' -not -path '*/nonmatchings/*' -not -path '*/matchings/*' 2>/dev/null)

ASM_OBJS := $(ASM_SRCS:%.s=$(BUILD)/%.s.o)
C_OBJS   := $(C_SRCS:%=$(BUILD)/%.o)
OBJS     := $(ASM_OBJS) $(C_OBJS)

-include $(C_OBJS:.o=.o.d) $(OBJS:%=%.asm.d)

UNDEFINED_SYMS   := linkers/$(VERSION)/undefined_syms_auto.$(BASENAME).txt
UNDEFINED_FUNCS  := linkers/$(VERSION)/undefined_funcs_auto.$(BASENAME).txt
UNDEFINED_MANUAL := configs/$(VERSION)/undefined_syms_manual.txt
ADDR_ALIASES     := $(BUILD)/undefined_addr_aliases.$(BASENAME).txt

.PHONY: all setup toolchain stage split build check diff objdiff-config report m2c permute probe test test-source verify clean distclean help

all: build check

setup:
	python3.12 -m venv .venv || python3 -m venv .venv
	.venv/bin/pip install -r requirements.txt

toolchain:
	tools/toolchain/setup.sh

stage:
	$(PY) tools/scripts/stage_disc.py

split:
	rm -rf $(ASM_DIR) $(LD_SCRIPT) $(UNDEFINED_SYMS) $(UNDEFINED_FUNCS) $(BUILD)
	$(PY) -m splat split $(SPLAT_CFG)

$(BUILD)/asm/%.s.o: asm/%.s
	@mkdir -p $(dir $@)
	$(AS) -EL -G0 -march=r3000 -mtune=r3000 -no-pad-sections -Iinclude -I$(ASM_DIR) --MD $@.asm.d -o $@ $<

$(BUILD)/src/%.c.o: src/%.c $(CC_WRAPPER) Makefile
	@mkdir -p $(dir $@)
	$(CC_WRAPPER) $< $@

# splat's undefined_*_auto files are linker *assignments*, which would pin a
# symbol's address even after a C object defines it. Only the addresses that
# are still unresolved after looking at the objects are linked.
$(ADDR_ALIASES): tools/scripts/gen_undefined_addr_aliases.py $(OBJS) $(UNDEFINED_MANUAL) $(UNDEFINED_SYMS) $(UNDEFINED_FUNCS) configs/$(VERSION)/sym.$(BASENAME).txt
	$(PY) tools/scripts/gen_undefined_addr_aliases.py --nm $(NM) --output $@ \
	      --source $(UNDEFINED_SYMS) --source $(UNDEFINED_FUNCS) \
	      --source configs/$(VERSION)/sym.$(BASENAME).txt \
	      --manual $(UNDEFINED_MANUAL) $(OBJS)

$(ELF): Makefile $(OBJS) $(LD_SCRIPT) $(UNDEFINED_MANUAL) $(ADDR_ALIASES)
	$(LD) -EL -T $(LD_SCRIPT) -T $(UNDEFINED_MANUAL) -T $(ADDR_ALIASES) \
	      -Map $(BUILD)/$(BASENAME).map --no-check-sections -o $@

$(OUT_BIN): $(ELF) Makefile
	$(OBJCOPY) -O binary --gap-fill 0 --pad-to $(PAD_TO) $< $@

build: $(OUT_BIN)

check: $(OUT_BIN)
	@echo "$(TARGET_SHA)  $(OUT_BIN)" | shasum -c -

# make diff FUNC=GOOL_InterpretObject   (asm-differ against the retail EXE)
diff:
	@test -n "$(FUNC)" || { echo "usage: make diff FUNC=<symbol>"; exit 2; }
	$(PY) $(TOOLCHAIN)/asm-differ/diff.py -mwo --overlap $(FUNC)

clean:
	rm -rf $(BUILD)

distclean: clean
	rm -rf asm/$(VERSION) $(LD_SCRIPT) $(UNDEFINED_SYMS) $(UNDEFINED_FUNCS)

help:
	@echo "Targets:"
	@echo "  setup            Create .venv and install Python tooling"
	@echo "  toolchain        Fetch/build gcc-2.5.7/2.6.3/2.7.2/2.8.1-psx, maspsx, objdiff, asm-differ, permuter"
	@echo "  stage            Extract SCUS_949.00 from disc/USA into assets/USA/main.exe"
	@echo "  split            Run splat on the retail executable"
	@echo "  build            Assemble, compile and link build/USA/main.exe"
	@echo "  check            Verify the rebuilt EXE's SHA-1 against retail"
	@echo "  probe FILE=path.c  Compare functions against freshly split retail assembly"
	@echo "  test             Run tooling regression tests (requires setup/toolchain/split)"
	@echo "  diff FUNC=name   asm-differ one function against retail"
	@echo "  objdiff-config   Build retail target objects (expected/) and objdiff.json"
	@echo "  report           objdiff progress report -> build/USA/report.json"
	@echo "  m2c FUNC=name    m2c decompilation of a not-yet-decompiled function"
	@echo "  permute FUNC=name  Set up a decomp-permuter scratch dir in nonmatchings/"

# objdiff: target objects re-split from retail into expected/, plus objdiff.json.
objdiff-config:
	$(PY) tools/scripts/gen_objdiff.py --version $(VERSION)

report: check objdiff-config
	$(TOOLCHAIN)/bin/objdiff-cli report generate -p . -o $(BUILD)/report.json
	$(PY) tools/scripts/progress.py $(BUILD)/report.json

m2c:
	@test -n "$(FUNC)" || { echo "usage: make m2c FUNC=<symbol>"; exit 2; }
	@tools/scripts/m2c.sh $(FUNC)

# Creates nonmatchings/<FUNC>/ with base.c, target.o and compile.sh, then:
#   tools/toolchain/decomp-permuter/permuter.py nonmatchings/<FUNC> -j8
permute:
	@test -n "$(FUNC)" || { echo "usage: make permute FUNC=<symbol>"; exit 2; }
	$(PY) $(TOOLCHAIN)/decomp-permuter/import.py \
	      $$(grep -rl "$(FUNC)" src --include='*.c' | head -1) \
	      $$(find $(ASM_DIR)/nonmatchings -name '$(FUNC).s' | head -1)

probe:
	@test -n "$(FILE)" || { echo "usage: make probe FILE=src/main/<unit>.c"; exit 2; }
	$(PY) tools/scripts/probe_match.py $(FILE) --version $(VERSION) -v

test:
	$(PY) -m unittest discover -s tests -v

# Retail-free checks suitable for a public checkout and CI.
test-source:
	$(PY) -m unittest discover -s tests -p test_instruction_distance.py -v
	$(PY) -m unittest discover -s tests -p test_tooling.py -k test_shell_syntax -v

verify: build check test
