def apply(config, args):
    import shutil
    cross = "mipsel-none-elf-" if shutil.which("mipsel-none-elf-objdump") else "mipsel-linux-gnu-"
    config["arch"] = "mipsel"
    config["baseimg"] = "assets/USA/main.exe"
    config["myimg"] = "build/USA/main.exe"
    config["mapfile"] = "build/USA/main.map"
    config["source_directories"] = ["src", "include"]
    config["objdump_executable"] = cross + "objdump"
    config["map_format"] = "gnu"
    config["build_command"] = ["make", "-j", "build"]
