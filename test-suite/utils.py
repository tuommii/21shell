import os
from subprocess import Popen, PIPE
from multiprocessing import Process


def get_leaks(results):
    lst = results.split('\n')
    for i, line in enumerate(lst):
        if 'LEAK SUMMARY' in line:
            return lst[i + 1]

def valgrind_wrapper(program, command):
    valgrind = ["valgrind", "--leak-check=full"]
    cmd_list = ["/bin/echo"] + command
    p_command = Popen(cmd_list, stdout=PIPE)
    p_shell = Popen(valgrind + [program], stdin=p_command.stdout, stdout=PIPE, stderr=PIPE)
    p_command.stdout.close()
    p_command.wait()
    _, err = p_shell.communicate()
    p_shell.wait()
    results = err.decode()
    if 'All heap blocks were freed -- no leaks are possible' not in results and 'definitely lost: 0 bytes in 0 blocks' not in results:
        print(f'LEAKS SUMMARY FOR COMMAND {command}:\n{results}\n')


class QueueProcess:

    def __init__(self, function, tail, *args):
        self.p = []
        self.args = args
        self.function = function
        self.tail = tail
        self.process = Process(target=self.function, args=self.args)

    def start(self):
        self.process.start()
        if self.tail is True:
            self.process.join()
            if self.process.exitcode != 0:
                raise AssertionError
        self.p.append(self)
