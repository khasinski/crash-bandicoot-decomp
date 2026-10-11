# Recovered structures and matching workflow

The shared headers describe observed layouts on the PS1 32-bit ABI. Padding
marks unknown bytes. A partial view's `sizeof` is not the size of the complete
original object unless an allocation or copy establishes it.

| Header | Evidence and useful offsets |
|---|---|
| `gool.h` | Runtime object: entry `0x28`, flags `0xCC`/`0x120`, stack/PC/frame `0xDC`/`0xE0`/`0xE4`, value `0x138`; frame restore and release routines |
| `gool.h` | Separate defaults block (`0x30` bytes) and collision/message actor view: bounds `0x08`, resource `0x20`, position `0x80`, radius `0xB0` |
| `engine_state.h` | Lifecycle prefix; separate mode-25 allocation ending at `0x35D8`; event request's two pointers and event word |
| `resource.h` | Resource entries, handles, `0x2C` slots, eight-byte hash buckets, pool counter at `0x68C`, zone references at `0x23C` |
| `gpu.h`, `render.h` | `0x5C` drawing snapshot; buffer display `0x04`, drawing `0x18`, cursors `0x74`/`0x78`, ordering table `0x88` |

Do not merge views just because old local typedefs were called `Object` or
`Entry`. The message resource's entry type lives at `+4`, whereas a
`ResourceEntry` kind lives at `+8`. Hash buckets contain a tagged integer word
and an ID; they are not twenty-byte resource entries. The `D_800580A4` alias
starts four bytes into a slot but retains the `0x2C` array stride. Its signed
state view remains separate from the full slot's unsigned field.

The runtime object includes the `+4`, `+0x68` and `+0x6C` link fields from
the traversal view: both traversal cleanup and object release pass their
object to `func_8001CDD0`, supporting that shared prefix. `Node` remains a
small traversal view; callback signatures are not changed to assume that every
context argument is an object pointer.

The declarations are included in `m2c_context.h`, so first-pass decompilation
can use known prototypes and layouts. Public prototypes cover the confirmed
resource lookup/release, GPU drawing, traversal, and typed GOOL operations.
Ambiguous callback ABIs and formats retain local declarations pending evidence.

The engine-state storage owner suppresses the header's forward declarations
of its own globals. With GCC 2.6.3, introducing those declarations ahead of the
retail-ordered definitions changes tentative storage order and linked `gp`
offsets. Consumers and m2c still receive the shared declarations.

`tests/layout_assertions.c` checks sizes and offsets using stock GCC 2.6.3,
including pointer fields. Run `make test` after changing shared declarations.
Host-compiler layout checks would incorrectly use 64-bit pointers on macOS.

`func_80031D50` is the first new match using these shared layouts. The native
function uses `EngineMode25State.word359C`, scans texture slot states 8..14
with the recovered `0x2C` stride, and selects a resource item through the first
item's word at `+0x204`. The separate `ResourceItemListView` describes that
item-pointer array at `+0x10`; it must not be mistaken for a page header.
An indexed loop over `ResourceSlotStateView` matches all 89 native instructions
under the unit's stock GCC 2.6.3 profile. The initial manual cursor loop had the
same instruction count but Levenshtein distance four from initialization order.
The linked executable also passes the retail checksum.

A direct field expression can change register allocation or alias analysis.
For the resource flag routines, the matching byte-pointer access is retained,
with `CRASH_OFFSETOF(GoolResourceState, flags2DC)` deriving its offset from the
shared structure instead of a duplicated constant. Do not add packing,
`volatile`, or dummy fields merely to influence compilation.

## Trying stock profiles

```sh
.venv/bin/python tools/scripts/probe_profiles.py scratch/candidate.c
.venv/bin/python tools/scripts/probe_profiles.py scratch/candidate.c \
    --profile engine --profile engine-gp --function func_80012345
```

Profiles are in `configs/compiler_profiles.json`. The tool regenerates the
retail reference once, compiles each selected profile without changing source
or production objects, and ranks the sum of instruction Levenshtein distances.
Compilation failures and missing references cannot receive a score or match.
Exit status is zero only if at least one valid profile has distance zero for
all selected functions. This does not replace the linked executable checksum.

`source` uses the file's current settings. Other profiles select known compiler,
CPU, maspsx and GNU small-data settings; source optimization comments remain
active unless the profile explicitly supplies `CRASH_CC1_FLAGS`. Ambient
experimental overrides are cleared. The matrix is a starting set, not a claim
that these are every compiler setting used by the game.

When a profile matches, record its stock settings in the production source
comments, run the normal probe, then `make build check`. The wrapper also
accepts `CRASH_GNU_AS_G` for experiments; promote that setting through the
existing `GNU_AS_G` source comment. Relocation masks cover actual relocation
fields, including PC-relative branch targets, while ordinary branch offsets
and instruction opcodes remain part of the Levenshtein comparison.
