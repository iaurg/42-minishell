#!/usr/bin/env python
import subprocess
import glob
import sys

# Compiles builtins tests for you
# Usage: ./test_raw.py <command name>

TEST_NAME = sys.argv[1]

builtins = glob.glob("./libs/builtins/*.c")
libft = glob.glob("./libs/libft/*.c")

command = [
    "gcc",
    "-Wall",
    "-Wextra",
    "-o",
    TEST_NAME,
    f"./tests/test_{TEST_NAME}_alt.c",
    *builtins,
    *libft,
]
subprocess.call(command)
