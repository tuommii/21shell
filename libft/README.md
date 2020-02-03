# Description
Library for functions used in Hive projects

## Lightweight ptf
- printf & dprintf
- no float support

## Regex quick reference
- c    matches any literal character c
- .    matches any single character
- ^    matches the beginning of the input string
- $    matches the end of the input string
- *    matches zero or more occurrences of the previous character

## Quick testing
```sh
make fclean && make && make test
make fclean && make clean_test
```