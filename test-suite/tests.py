import os
import shutil
import unittest
from subprocess import call, Popen, PIPE
from utils import QueueProcess, valgrind_wrapper


class Shelltests(unittest.TestCase):

    def setUp(self):
        self.their_shell = '/bin/bash'
        self.our_shell = f'{os.path.abspath(os.getcwd())}/21sh'
        self.tail = True if "TRUE" in "%s" % os.getenv("VG_TAIL") else False
        valgrind_binary = shutil.which('valgrind')
        if valgrind_binary is not None:
            self.valgrind = True
        else:
            self.valgrind = False
            print('Valgrind not available')

    def tearDown(self):
        pass

    def exec_shell(self, command, real=False):
        """
        :param command: list of command like ["/bin/ls", "-l"]
        """
        cmd_list = ["/bin/echo"] + command
        p_command = Popen(cmd_list, stdout=PIPE)
        if real is True:
            p_shell = Popen([self.their_shell], stdin=p_command.stdout, stdout=PIPE, stderr=PIPE)
        else:
            p_shell = Popen([self.our_shell], stdin=p_command.stdout, stdout=PIPE, stderr=PIPE)
        p_command.stdout.close()
        p_command.wait()
        stdout, stderr = p_shell.communicate()
        p_shell.wait()
        return stdout, stderr

    def compare_shells(self, command):
        our_out, our_err = self.exec_shell(command)
        their_out, their_err = self.exec_shell(command, real=True)
        our_err = our_err.replace(b"21sh: ", b"")
        their_err = their_err.replace(b"/bin/bash: line 1: ", b"")
        self.assertEqual(our_out, their_out)
        self.assertEqual(our_err, their_err)

    def valgrind_leaks(self, command):
        if self.valgrind is True:
            leaks = QueueProcess(valgrind_wrapper, self.tail, self.our_shell, command)
            leaks.start()

    def test_00_syntax(self):
        command = [";"]
        expected = b"21sh: syntax error near unexpected token `;'\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_01_basic(self):
        command = ["/bin/pwd"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_02_echo(self):
        command = ["   ", "/bin/echo", "  testing....  "]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_03_fake_binary(self):
        command = ["fake_file_name", "-o", "/"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_04_empty_multi(self):
        command = ["  ", ""]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_05_empty1(self):
        command = [""]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_06_empty2(self):
        command = ["      "]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_07_last_exec(self):
        command = ["echo", "$?", "$?", "\t$?  "]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_08_exit(self):
        command = ["exit", "1"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_09_cd_not_exist(self):
        command = ["cd", "/doesnotexist"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_10_chained(self):
        command = ["mkdir", "test", ";", "cd", "test", ";", "ls", "-a", ";", "ls", "|", "cat", "|", "wc", "-c", ">", "fifi", ";", "cat", "fifi"]
        our_out, our_err = self.exec_shell(command)
        self.exec_shell(["rm", "-rf", "test"])
        their_out, their_err = self.exec_shell(command, real=True)
        self.exec_shell(["rm", "-rf", "test"], real=True)

    def test_11_cd_and_pwd(self):
        command = ["cd", "../", ";", "cd", ";", "/bin/pwd"]
        self.compare_shells(command)

    def test_12_not_dir(self):
        command = ["cd", "/bin/pwd"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_13_redir(self):
        command = ["echo", "firstline", ">", "test-suite/resources/testfile", ";", "cat", "test-suite/resources/testfile", "|", "cat"]
        expected = b'firstline\n'
        out, err = self.exec_shell(command)
        self.assertEqual(out, expected)
        self.assertEqual(err, b'')
        self.valgrind_leaks(command)

    def test_14_no_permission(self):
        command = ["./test-suite/resources/testbin"]
        expected = b'21sh: permission denied: ./test-suite/resources/testbin\n'
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_15_pipes(self):
        command = ["cat", "<", "test-suite/resources/testfile2", "|", "wc", "-c"]
        expected = b'40\n'
        out, err = self.exec_shell(command)
        self.assertEqual(out, expected)
        self.assertEqual(err, b'')
        self.valgrind_leaks(command)

    def test_16_redir(self):
        command = ["cat", "doesnotexist", "2>&1"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_17_redir(self):
        command = ["cat", "doesnotexist", ">", "/dev/null"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_18_redir(self):
        command = ["echo", "An error occurred, bye!", ">&2"]
        self.compare_shells(command)
        self.valgrind_leaks(command)


if __name__ == '__main__':
    unittest.main()