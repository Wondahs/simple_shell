Simple Shell

This is a project for Alx Software Engineering School that simulates a shell as a program that interprets basic commands entered in the terminal by users

User Guide
The simple shell is build with functions that implement structures, system call and functions of libraries like <sys/types.h> <sys/stat.h> that together read commands, which shows the content in a directory and it files etc.

Installation Guide
Download the project in this address: https://github.com/Wondahs/simple_shell

Compilation

You should compiled this way:

gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

Examples

execute in this form ./shell

Use commands like ls -l for list directories for example:

**WELCOME TO SIMPLE SHELL**

	Wonders & Isek7
$ ls

README.md check_hash.c customUtils3.c customUtils5.c customUtils7.c customUtils.c eprintf_functions.c changelog customUtils2.c customUtils4.c customUtils6.c customUtils8.c e_printf.c eprintf.h printenv.c printf_functions.c printf.c printf.h shell.c special_cases.c

Commands	Options

ls	-l, -a, -t

cd	-, ~, ..

pwd	Display directory actuall

Authors

Wonders Victor <wondersprince1@gmail.com>

Ben Gabriel Isek <bengabrielisek@gmail.com>
