# 21sh

Sh

## Debug

Flags `--lexer` and `--ast` give you information about tokens and AST

```sh
valgrind ./21sh --leak-check=full --track-origins=yes
```

## To-do

### Bugs

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
- [ ] CTRL + L to clear the screen would be nice -> Miikka
- [ ] Prompt to display cwd
- [x] Expand $ ~ in parser
- [ ] Resizing the window makes prompt disappear
- [ ] MIIKKA check these -> `valgrind ./21sh < /bin/echo | /bin/ls -l` -- `echo "pwd" | ./21sh`

### Needs more testing
- [ ] Double check syntax error check in parser
- [ ] Builtin commands
- [ ] Memory leaks
- [ ] Redirection section in execution


Works now
```sh
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
```

## Keyboard shorcuts
| KEY | ACTION |
|---------|---------|
| <kbd>CTRL + LEFT</kbd> | Moves cursor one word **left** |
| <kbd>CTRL + RIGHT</kbd> | Moves cursor one word **right** |
| <kbd>CTRL + UP</kbd> | Moves cursor one row **up** |
| <kbd>CTRL + DOWN</kbd> | Moves cursor one row **down** |
| <kbd>HOME</kbd> | Moves cursor to **beginning** of input |
| <kbd>END</kbd> | Moves cursor to **end** of input |
| <kbd>DELETE</kbd> | Delete char at cursor position |
| <kbd>CTRL + D</kbd> | Delete char at cursor, exit if no input |
| <kbd>CTRL + X</kbd> | **Cut**. First press is start index and second is end index |
| <kbd>CTRL + K</kbd> | **Copy**. First press is start index and second is end index |
| <kbd>CTRL + P</kbd> | **Paste** |
| <kbd>LEFT</kbd> | Moves cursor left |
| <kbd>RIGHT</kbd> | Moves cursor right |
| <kbd>UP</kbd> | Get next command from history |
| <kbd>DOWN</kbd> | Go back one command |
| <kbd>BACKSPACE</kbd> | Delete on char left of cursor and move cursor left |
| <kbd>ESC</kbd> | Quit |

### Refrences
- [Control operators](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)
- [BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
- [Unittests](https://github.com/JulienBalestra/21sh/blob/e1703310e11bf2774fb781c9b21937a69bb9e4ec/tests/test_minishell.py)

<div align='center'>
    <sub>Created by <a href='https://github.com/rouhija'>Sami Rouhe (srouhe) <a href='https://github.com/tuommii'>Miikka Tuominen (mtuomine)</a></sub>
</div>
<div align='center'>
    <sub>From <a href='https://www.hive.fi/en/'>Hive Helsinki</a></sub>
</div>
