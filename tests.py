#!/usr/bin/python3

'''
IN PROGRESS
	need to fix redirect issues to get this working

Commands:
	killall -9 21sh
'''

import os
import subprocess
from pathlib import Path

TIMEOUT = 2
cwd = Path().absolute()
our_shell = '%s/21sh' % cwd
their_shell = "/bin/bash"

command = ["/bin/ls", "-l"]
cmd_list = ["/bin/echo"] + command

# ./21sh < /bin/echo | /bin/ls -l ; exit

p_cmd = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
p_sh = subprocess.Popen([our_shell], stdin=p_cmd.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
p_cmd.stdout.close()
stdout, stderr = p_sh.communicate(timeout=TIMEOUT)
print(stdout.decode(), stderr.decode())
# p_sh.terminate()


# proc.communicate()
	# print(outs, errs)
# os.spawnl(os.P_DETACH, subprocess.Popen([shell_path]))

# with subprocess.Popen(["ifconfig"], stdout=PIPE) as proc:
#     log.write(proc.stdout.read())

# try:
#     outs, errs = proc.communicate(input="ls", timeout=15)
# except TimeoutExpired:
#     proc.kill()
#     outs, errs = proc.communicate()