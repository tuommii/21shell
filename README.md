# 21sh

Sh

## Debug
```sh
valgrind ./21sh --leak-check=full --track-origins=yes
```

## To-do

### Parsing
- [x] Remove quotes after parser
- [x] Single quotes parsing
- [x] IO numbers (2&1> null etc stuff)
- [ ] Heredoc proper implementation (<<) PIPE IT
- [x] Handle signals for execve (etc. cat + CTRL+C exits only cat)
- [x] Trailing pipe (prompt for input)

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
- [x] cmd + trailing semicolon bugs out (quick fix in place)

### Needs more testing
- [ ] Double check syntax error check in parser
- [ ] Builtin commands
- [ ] Memory leaks
- [ ] Long chained commands with lots of pipes


test cmd
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
- [control operators](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)
- [BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)

<div align='center'>
    <sub>Created by <a href='https://github.com/rouhija'>Sami Rouhe (srouhe) <a href='https://github.com/tuommii'>Miikka Tuominen (mtuomine)</a></sub>
</div>
<div align='center'>
    <sub>From <a href='https://www.hive.fi/en/'>Hive Helsinki</a></sub>
</div>
