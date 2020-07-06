import os
import sys
import unittest
from subprocess import Popen, PIPE


class Shelltests(unittest.TestCase):

    def setUp(self):
        self.their_shell = '/bin/bash'
        self.our_shell = f'{os.path.abspath(os.getcwd())}/21sh'

    def tearDown(self):
        pass

    def exec_shell(self, command, real=False):
        """
        :param command: list of command like ["/bin/ls", "-l"]
        """
        cmd_list = ["/bin/echo"] + command
        p_command = Popen(cmd_list, stdout=PIPE)
        if real is True:
            shell = Popen([self.their_shell], stdin=p_command.stdout, stdout=PIPE, stderr=PIPE)
        else:
            shell = Popen([self.our_shell], stdin=p_command.stdout, stdout=PIPE, stderr=PIPE)
        p_command.stdout.close()
        p_command.wait()
        stdout, stderr = shell.communicate()
        shell.wait()
        return stdout, stderr

    def compare_shells(self, command):
        our_out, our_err = self.exec_shell(command)
        their_out, their_err = self.exec_shell(command, real=True)
        our_err = our_err.replace(b"21sh: ", b"")
        their_err = their_err.replace(b"/bin/bash: line 1: ", b"")
        self.assertEqual(our_out, their_out)
        self.assertEqual(our_err, their_err)

    # def test_00(self):
    #     command = ["/bin/ls", "-t"]
    #     self.compare_shells(command)

    def test_01_basic(self):
        command = ["/bin/pwd"]
        self.compare_shells(command)

    def test_02_echo(self):
        command = ["   ", "/bin/echo", "  testing....  "]
        self.compare_shells(command)

    def test_03_fake_binary(self):
        command = ["fake_file_name", "-o", "/"]
        self.compare_shells(command)

    def test_04_empty_multi(self):
        command = ["  ", ""]
        self.compare_shells(command)

    def test_05_empty1(self):
        command = [""]
        self.compare_shells(command)

    def test_06_empty2(self):
        command = ["      "]
        self.compare_shells(command)

    # def test_07(self):
    #     command = ["echo", "$?", "$?", "\t$?  "]
    #     self.compare_shells(command)

    def test_08_exit(self):
        command = ["exit", "1"]
        self.compare_shells(command)

    def test_09_cd_not_exist(self):
        command = ["cd", "/doesnotexist"]
        self.compare_shells(command)

    # def test_10(self):
    #     command = ["mkdir", "test", ";", "cd", "test", ";", "ls", "-a", ";", "ls", "|", "cat", "|", "wc", "-c", ">", "fifi", ";", "cat", "fifi"]
    #     our_out, our_err = self.exec_shell(command)
        # self.exec_shell(["rm", "-rf", "test"])
        # their_out, their_err = self.exec_shell(command, real=True)
        # self.exec_shell(["rm", "-rf", "test"], real=True)

    # def test_11_cd_and_pwd(self):
    #     command = ["cd", "../", ";", "cd", ";", "/bin/pwd"]
    #     self.compare_shells(command)

    def test_12_not_dir(self):
        command = ["cd", "/bin/pwd"]
        self.compare_shells(command)


if __name__ == '__main__':
    unittest.main()