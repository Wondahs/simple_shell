Simple Shell

This is a project for Alx Software Engineering School that simulates a shell as a program that interprets basic commands entered in the terminal by users

User Guide

The simple shell is build with functions that implement structures, system call and functions of libraries like <sys/types.h> <sys/stat.h> that together read commands, which shows the content in a directory and it files etc.

Installation Guide

Download the project in this address: https://github.com/Wondahs/simple_shell

Compilation

You should compiled this way::

gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

Examples

execute in this form ./shell

Use commands like ls -l for list directories for example:

**WELCOME TO SIMPLE SHELL**

	Wonders & Isek7
$ ls

README.md check_hash.c customUtils3.c cl_exec_exit.c looper_read_file.c customUtils.c eprintf_functions.c changelog customUtils2.c customUtils4.c cd.c setenv_unset_free.c e_printf.c eprintf.h printenv.c printf_functions.c printf.c printf.h shell.c variable_expansion.c special_cases.c

Commands     Options

ls	     -l, -a, -t

cd	     -, ~, ..

pwd	     Display present working directory

Authors

Wonders Victor <wondersprince1@gmail.com>

Ben Gabriel Isek <bengabrielisek@gmail.com>
