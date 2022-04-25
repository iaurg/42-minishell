import unittest
import subprocess
import glob

TEST_NAME = "echo"

builtins = glob.glob("./libs/builtins/*.c")
libft = glob.glob("./libs/libft/*.c")

command = [
    "gcc",
    "-Wall",
    "-Wextra",
    "-o",
    TEST_NAME,
    f"./tests/test_{TEST_NAME}.c",
    *builtins,
    *libft,
]
subprocess.call(command)
