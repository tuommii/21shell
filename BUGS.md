### Buglist

Some found bugs:
- [ ] If input contains only existing directory name, no command not found error is printed
and that also leaks memory
- [ ] write newline after CTRL+D
- [ ] `cd -` causes EOF error and goes to wrong dir sometime. Also prints
extra '/'
- [x] fake binary name does not write to STDERR
- [ ] command = ["echo", "$?", "$?", "\t$?  "]
- [ ] /bin/echo "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi" | ./21sh -- seg fault
- [ ] cd causes segfault when piped to shell
- [ ] a lot of small leaks here and there
