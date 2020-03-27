# 21sh

Sh

## Debug
```sh
valgrind ./21sh --leak-check=full --track-origins=yes
```

## To-do

### Parsing
- [ ] Single quotes parsing
- [ ] IO numbers (2&1> null etc stuff)
- [ ] Handle signals for execve (etc. cat + CTRL+C exits only cat)

### History (for 42sh at least)
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
- [ ] **Paste** text to shell from outside


test cmd
```sh
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
```

## Keyboard shorcuts
| KEY | ACTION |
|---------|---------|
| CTRL + LEFT | Moves cursor one word left |
| CTRL + RIGHT | Moves cursor one word right |
| CTRL + UP | Moves cursor one row up |
| CTRL + DOWN | Moves cursor one row down |
| HOME | Moves cursor to beginning of input |
| END | Moves cursor to end of input |
| DELETE | Delete char at cursor |
| CTRL + D | Delete char at cursor, exit if no input |
| CTRL + X | Cut. First press is start index and second is end index |
| CTRL + K | Copy. First press is start index and second is end index |
| CTRL + P | Paste |

### Refrences
- [control operators](https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators)
- [BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)

<div align='center'>
    <sub>Created by <a href='https://github.com/rouhija'>Sami Rouhe (srouhe) <a href='https://github.com/tuommii'>Miikka Tuominen (mtuomine)</a></sub>
</div>
<div align='center'>
    <sub>From <a href='https://www.hive.fi/en/'>Hive Helsinki</a></sub>
</div>
