import unittest
import subprocess
from tests.utils.setup import TestBuilder, TestBuilderAlt

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

    @unittest.skip("Deprecated test")
    def test_command(self):
        # The command under test
        command = [f"./{self.test_name}", "echo", "-n", "test", "test2", "test3", "-n"]
        result = subprocess.run(command, capture_output=True).stdout

        # The bash equivalent
        bash_emulated_command = ["echo", "-n", "test", "test2", "test3", "-n"]

        expected_result = subprocess.run(
            bash_emulated_command, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)

    @unittest.skip("Deprecated test")
    def test_command2(self):
        # The command under test
        command = [f"./{self.test_name}", "echo", "test", "test2", "test3", "-n"]
        result = subprocess.run(command, capture_output=True).stdout

        # The bash equivalent
        bash_emulated_command = ["echo", "test", "test2", "test3", "-n"]

        expected_result = subprocess.run(
            bash_emulated_command, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)

    @unittest.skip("Deprecated test")
    def test_command3(self):
        # The command under test
        command = [f"./{self.test_name}"]
        result = subprocess.run(command, capture_output=True).stdout

        # The bash equivalent
        bash_emulated_command = ["echo"]

        expected_result = subprocess.run(
            bash_emulated_command, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)

if __name__ == "__main__":
    unittest.main()
