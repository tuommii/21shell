### Buglist

Some found bugs:
- [ ] write newline after CTRL+D
- [ ] `cd -` causes EOF error
- [x] fake binary name does not write to STDERR
- [ ] command = ["echo", "$?", "$?", "\t$?  "]
- [ ] /bin/echo "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi" | ./21sh -- seg fault
- [ ] cd causes segfault when piped to shell