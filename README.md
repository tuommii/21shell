
<h1 align="center">
	(WIP) Shell
	<br><br>
</h1>

<p align="center">
	<img width=320 src="shell.gif">
</p>

### Challenge
Stability. TODO

#### Restrictions
- Max **25 lines** per function
- Max **5 functions** per **.c file**
- Comments are only allowed outside of functions
- All defines, and typedef must be done in header files

#### Functions allowed
```
- malloc, free
- access
- open, close, read, write
- opendir, readdir, closedir
- getcwd, chdir
- stat, lstat, fstat
- fork, execve
- wait, waitpid, wait3, wait4
- signal, kill
- exit
- pipe
- dup, dup2
- isatty, ttyname, ttyslot
- ioctl
- getenv
- tcsetattr, tcgetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs
```

### Features

#### Context-Aware Autocompleter (WIP)
Cursor can be anywhere and it recognizes:
- Built-ins
- Executables
- Envinronment variables
- Paths
- Flags (?)

#### Other
- Multiline support
- History
- Copy/Paste text between different windows (xclip on Linux)

### Try It
Compile and run with:
```bash
make
./21sh
```

### Unittests
```sh
python3 test-suite/tests.py
```

### Keyboard shorcuts
| KEY | ACTION |
|---------|---------|
| <kbd>CTRL + LEFT</kbd> | Moves cursor one word **left** |
| <kbd>CTRL + RIGHT</kbd> | Moves cursor one word **right** |
| <kbd>CTRL + UP</kbd> | Moves cursor one row **up** |
| <kbd>CTRL + DOWN</kbd> | Moves cursor one row **down** |
| <kbd>HOME</kbd> | Moves cursor to **beginning** of input |
| <kbd>END</kbd> | Moves cursor to **end** of input |
| <kbd>DELETE</kbd> | Delete char at cursor position |
| <kbd>CTRL + L</kbd> | Clear screen |
| <kbd>CTRL + U</kbd> | Clear input |
| <kbd>CTRL + D</kbd> | Delete char at cursor, exit if no input |
| <kbd>CTRL + W</kbd> | **Cut** from start to cursor
| <kbd>CTRL + E</kbd> | **Cut** from cursor to end
| <kbd>CTRL + A</kbd> | **Yank**, internal paste
| <kbd>CTRL + K</kbd> | (WIP) **Copy**. Copy current input to clipboard |
| <kbd>CTRL + P</kbd> | External **Paste** |
| <kbd>LEFT</kbd> | Moves cursor left |
| <kbd>RIGHT</kbd> | Moves cursor right |
| <kbd>UP</kbd> | Get next command from history |
| <kbd>DOWN</kbd> | Go back one command |
| <kbd>BACKSPACE</kbd> | Delete on char left of cursor and move cursor left |
| <kbd>ESC</kbd> | Quit |

<div align='center'>
    <sub>Created by <a href='https://github.com/rouhija'>Sami Rouhe (srouhe)</a> and <a href='https://github.com/tuommii'>Miikka Tuominen (mtuomine)</a></sub>
</div>
<div align='center'>
    <sub>From <a href='https://www.hive.fi/en/'>Hive Helsinki</a></sub>
</div>
