## To-do

- man pages: /usr/share/man
- autocompletion over current directory
- add trailing slash '/' if file is dir
- print all suggestions / tab changes suggestion
- recursive git branch checking or git command, seperate from print_prompt() - its called in redraw()

- echo==14735== Warning: noted but unhandled ioctl 0x5412 with no size/direction hints. README_MISSING_SYSCALL_OR_IOCTL
- tokenize -> init_lexer LEAKS! If no inpu, just ENTER
- CTRL+Y is reserved on OS X
- echo "text" | pbcopy

### Needs more testing
- [ ] Memory leaks (leaks in lexer - exec & parser not really)

### History (for 42sh at least)
- [ ]           Trailing pipe and open quotes -> update history!
- [ ]			Save history to file
- [ ] `CTRL+R`	Incremental search from history
- [ ] `fc`		Opens latest command in editor and runs that after closed
- [ ] `!!`		print last command
- [ ] `!ls`		execute last command where ls is found
- [ ] `!1`		nth command without params, not in bash?
- [ ] `!-3`		nth command with params

### Misc
- [ ] Output **colors** e.g for ls
- [ ] Dynamic prompt (at least showing current folder)
- [x] **Paste** text to shell from outside (in 42sh **popen** is allowed)
- [ ] Readline should keep the newline in?
- [x] CTRL + L to clear the screen would be nice -> Miikka
- [ ] Prompt to display cwd
- [x] Expand $ ~ in parser
- [x] Resizing the window makes prompt disappear
- [x] MIIKKA check these -> `echo "pwd" | ./21sh`



Works now
```sh
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
```

### Refrences
- [Control operators](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)
- [BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
- [Unittests](https://github.com/JulienBalestra/21sh/blob/e1703310e11bf2774fb781c9b21937a69bb9e4ec/tests/test_minishell.py)
