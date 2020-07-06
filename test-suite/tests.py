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
        print(our_out.decode())
        print(their_out.decode())
        # self.assertEqual(our_out.decode(), their_out.decode())

    def test_00(self):
        command = ["/bin/ls"]
        self.compare_shells(command)

    def test_01(self):
        command = ["   ", "/bin/echo", "  toto  "]
        self.compare_shells(command)

    def test_02(self):
        command = ["a_very_large_fake_binary_name", "-o", "/"]
        self.compare_shells(command)


if __name__ == '__main__':
    unittest.main()