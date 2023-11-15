# ALX Simple Shell

A simple Unix shell implementation for the ALX Software Engineering program.

## Introduction

ALX Simple Shell is a basic Unix shell created as part of the ALX Software Engineering curriculum. The project aims to implement a simple command-line interface with fundamental shell functionalities.

## Features

- **Command Execution:** Execute basic shell commands.
- **Built-in Commands:** Support for a few built-in commands.
- **Simple Prompt:** Display a simple command prompt.

## Contributing

Contributions are welcome! If you'd like to contribute to the project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/new-feature`.
3. Make your changes and commit them: `git commit -m 'Add new feature'`.
4. Push to the branch: `git push origin feature/new-feature`.
5. Submit a pull request.

## My Files
1. my_atoic.c
2. builtins.c
3. more_builtins.c
4. environs.c
5. errors.c
6. handle_errors.c
6. exits.c
7. _getenvv.c
8. _getinfo.c
9. _getline.c
10. _history.c
11. lists.c
12. more_lists.c
13. main.c
14. memory.c
15. parser.c
16. reallocate.c
17. main_shell.c
18. handle_strings.c
19. more_errors.c
20. string1.c
21. tokens.c
22. variables.c
23. shell.h


## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Running Valgrind to check for memory leaks

valgrind --leak-check=full ./hsh

##Output

==434== Memcheck, a memory error detector
==434== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==434== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==434== Command: ./hsh
==434==

##Coclusion

No memory leaks
