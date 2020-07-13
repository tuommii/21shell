import os
import shutil
import pathlib
import unittest
from subprocess import call, Popen, PIPE
from utils import QueueProcess, valgrind_wrapper


class Shelltests(unittest.TestCase):

    def setUp(self):
        self.their_shell = '/bin/bash'
        self.root = pathlib.Path(__file__).parent.absolute().parent
        self.our_shell = f'{self.root}/21sh'
        self.tail = True if "TRUE" in "%s" % os.getenv("VG_TAIL") else False
        self.valgrind = True if shutil.which('valgrind') is not None else False

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
        if self.valgrind:
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
        command = ["   \t   "]
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
        self.assertEqual(our_out, their_out)
        self.assertEqual(our_err, their_err)

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

    def test_19_syntax(self):
        command = ["echo", "moro", "|", "cat", ";", "|"]
        expected = b"21sh: syntax error near unexpected token `|'\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_20_misc(self):
        command = ["libft"]
        expected = b"21sh: libft: command not found\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_21_cd(self):
        command = ["cd", "..", ";", "cd", "--", ";", "cd", "-", ";", "cd"]
        self.valgrind_leaks(command)

    def test_22_cd(self):
        command = ["cd", "~/..////", ";", "pwd ;"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_23_chain(self):
        command = ["echo", "\"'moro'\"", "|", "cat", ";", "echo"]
        self.compare_shells(command)
        self.valgrind_leaks(command)

    def test_24_permission(self):
        command = ["./libft"]
        expected = b"21sh: is a directory: ./libft\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_25_permission(self):
        command = ["./Makefile"]
        expected = b"21sh: permission denied: ./Makefile\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_26_permission(self):
        command = ["cd", ";", "./Makefile"]
        expected = b"21sh: ./Makefile: No such file or directory\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, b'')
        self.assertEqual(err, expected)
        self.valgrind_leaks(command)

    def test_26_misc(self):
        command = ["echo", "stuff to a file", ">", ".test", ";", "cat", ".test", "|", "grep", "file"]
        expected = b"stuff to a file\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, expected)
        self.assertEqual(err, b'')
        self.valgrind_leaks(command)

        command = ["echo", "second line", ">>", ".test", ";", "cat", "<", ".test"]
        expected = b"stuff to a file\nsecond line\n"
        out, err = self.exec_shell(command)
        self.assertEqual(out, expected)
        self.assertEqual(err, b'')
        self.exec_shell(["rm", "-rf", ".test"])


if __name__ == '__main__':
    unittest.main()