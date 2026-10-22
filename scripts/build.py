"""Build 32-bit SA-MP plugins with the mise-pinned Zig toolchain."""
import argparse
import os
import sys
from pathlib import Path
import subprocess
import tempfile
import zipfile

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "build"


def run(*args, **kwargs):
    subprocess.run(args, cwd=ROOT, check=True, **kwargs)


def test():
    executable = OUT / "directory-test"
    if os.name == "nt":
        executable = executable.with_suffix(".exe")
    # Apple SDK headers require the system compiler for host-only tests.
    compiler = ["clang++"] if sys.platform == "darwin" else ["zig", "c++"]
    run(*compiler, "-std=c++11", "tests/directory_test.cpp", "-o", str(executable))
    with tempfile.TemporaryDirectory() as temporary:
        fixture = Path(temporary)
        for name in ["zebra.txt", "alpha.txt", "Beta.txt", ".hidden"]:
            (fixture / name).touch()
        (fixture / "folder").mkdir()
        (fixture / "empty").mkdir()
        run(str(executable), str(fixture))


def build(platform):
    windows = platform == "Windows"
    binary = OUT / ("FileManager.dll" if windows else "filemanager.so")
    flags = (["FileManager/filemanager.def"] if windows else
             ["-DLINUX", "-fPIC", "-fvisibility=hidden"])
    run("zig", "c++", "-target", "x86-windows-gnu" if windows else "x86-linux-gnu.2.17",
        "-std=c++11", "-DHAVE_STDINT_H", f'-DFILEMANAGER_VERSION="{args.version}"',
        "-I.", "-O2", "-shared",
        "FileManager/filemanager.cpp", "SDK/amxplugin.cpp", *flags,
        "-o", str(binary))
    with zipfile.ZipFile(OUT / f"FileManager_{args.version}_{platform}.zip", "w",
                         zipfile.ZIP_DEFLATED) as archive:
        for path in [binary, ROOT / "filemanager.inc", ROOT / "README.md",
                     ROOT / "LICENSE", ROOT / "sample.pwn"]:
            archive.write(path, path.name)


parser = argparse.ArgumentParser()
parser.add_argument("--platform", choices=["Linux", "Windows", "all"], default="all")
parser.add_argument("--version", default="dev")
parser.add_argument("--test", action="store_true")
args = parser.parse_args()
OUT.mkdir(exist_ok=True)
if args.test:
    test()
else:
    for platform in (["Linux", "Windows"] if args.platform == "all" else [args.platform]):
        build(platform)
