# Holberton-super_simple_shell

This repository contains a simple shell project completed as part of the Holberton School low-level programming curriculum.  
The goal of this project is to build a basic UNIX command-line interpreter in C, handling user input, executing commands, and managing environment variables.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Compilation](#compilation)
- [Usage](#usage)
- [Files](#files)
- [Requirements](#requirements)
- [Author](#author)

## Description

**Holberton-super_simple_shell** is a minimalist shell that replicates some basic functionalities of standard UNIX shells.  
It demonstrates process creation, command parsing, environment variable management, and basic error handling.

## Features

- Display a prompt and wait for user input
- Parse and execute commands found in the PATH
- Handle built-in commands like `env`
- Manage environment variables (`getenv`, `setenv`, `unsetenv`)
- Handle errors gracefully
- Support for simple memory management

## Compilation

All C files are compiled on Ubuntu 20.04 LTS with:
```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o super_simple_shell
```

## Usage

To start the shell, run:
```bash
./super_simple_shell
```
You can then type commands as you would in a standard shell.  
To exit, use `Ctrl+D` or the `exit` command (if implemented).

## Files

- `main.c` - Entry point of the shell
- `getline.c` - Handles user input
- `environnement/` - Functions for environment variable management
- `arguments/` - Argument parsing utilities
- `README.md` - This file

## Requirements

- All code is written in C and tested on Ubuntu 20.04 LTS.
- Code follows Holberton School guidelines and Betty style.
- No global variables unless specified.
- Maximum of 5 functions per file (unless specified).
- Only allowed standard library functions per project instructions.

## Author

# Lucas - Holberton School Student