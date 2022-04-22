from glob import glob
import subprocess
import unittest

class TestBuilder(unittest.TestCase):
    """
    The standard builtins setup class for tests

    To create tests use the `tests/` directory and name your test the same as the builtin tested. e.g.:
        `test/test_echo.c` will test the builtin `echo.c`
        also name your test_name parameter with the same test name as the builtin. e.g.:
        `test_name = "echo"`
    """
    test_name = None

    builtins_files = glob("./libs/builtins/*.c")
    libft_files = glob("./libs/libft/*.c")

    @classmethod
    def setUpClass(cls):
        cls.build_test_definition(cls.test_name)
        subprocess.call(cls.command)

    @classmethod
    def build_test_definition(cls, test_name):
        cls.command = [
            "gcc",
            "-Wall",
            "-Wextra",
            "-o",
            cls.test_name,
            f"./tests/test_{test_name}.c",
            *cls.builtins_files,
            *cls.libft_files,
        ]

    @classmethod
    def tearDownClass(cls):
        command = ["rm", cls.test_name]
        subprocess.call(command)


class TestBuilderAlt(TestBuilder):
    """The same setup as TestBuilder, but includes the test `_alt` posfix"""
    @classmethod
    def setUpClass(cls):
        cls.build_test_definition(cls.test_name + "_alt")
        subprocess.call(cls.command)
