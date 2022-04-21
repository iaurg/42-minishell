import unittest
import subprocess
from glob import glob


class TestBuilder(unittest.TestCase):
    test_name = None

    @classmethod
    def setUpClass(cls):
        builtins_files = glob("./libs/builtins/*.c")
        libft_files = glob("./libs/libft/*.c")
        command = [
            "gcc",
            "-Wall",
            "-Wextra",
            "-o",
            cls.test_name,
            f"./tests/test_{cls.test_name}.c",
            *builtins_files,
            *libft_files,
        ]
        subprocess.call(command)

    @classmethod
    def tearDownClass(cls):
        command = ["rm", cls.test_name]
        subprocess.call(command)


class TestEnv(TestBuilder):
    test_name = "env"

    def test_command(self):
        # The command under test
        command = [f"./{self.test_name}"]
        result = subprocess.run(command, capture_output=True).stdout

        # The bash equivalent
        bash_emulated_command = ["env"]
        expected_result = subprocess.run(
            bash_emulated_command, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)


class TestEcho(TestBuilder):
    test_name = "echo"

    def test_command(self):
        # The command under test
        command = [f"./{self.test_name}", "-n", "test", "test2", "test3", "-n"]
        result = subprocess.run(command, capture_output=True).stdout

        # The bash equivalent
        bash_emulated_command = ["echo", "-n", "test", "test2", "test3", "-n"]

        expected_result = subprocess.run(
            bash_emulated_command, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)


if __name__ == "__main__":
    unittest.main()
