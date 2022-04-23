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


@unittest.skip("Not implemented yet")
class TestEcho(TestBuilder):
    test_name = "echo"

    def test_command(self):
        # The command under test
        command = [f"./{self.test_name}", "Hello World"]
        result = subprocess.run(command, capture_output=True).stdout

        # The bash equivalent
        bash_emulated_command = ["echo", "Hello World"]
        expected_result = subprocess.run(
            bash_emulated_command, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)


class TestExport(TestBuilder):
    test_name = "export"

    def test_command_successful(self):
        command = [f"./{self.test_name}", "FOO=bar"]
        result = subprocess.run(command, capture_output=True).stdout

        bash_emulated_command = "export FOO=bar; echo $FOO"
        expected_result = subprocess.run(
            bash_emulated_command, shell=True, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)

class TestExportAlt(TestBuilderAlt):
    test_name = "export"
    def test_command_successful(self):
        # This setup will capture argv[1] as argv[0]
        command = [f"./{self.test_name}", "FOO=bar"]
        result = subprocess.run(command, capture_output=True).stdout

        bash_emulated_command = "FOO=bar; echo $FOO"
        expected_result = subprocess.run(
            bash_emulated_command, shell=True, capture_output=True
        ).stdout

        self.assertEqual(result, expected_result)


if __name__ == "__main__":
    unittest.main()
