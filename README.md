## Minishell

The objective of this project is for you to create a simple shell. Yes, your
little bash or zsh. You will learn a lot about processes and file descriptors.

Made with PDF version 6

> Think about architecture and how to implement it.

## Material

[notion wwwwelton](https://www.notion.so/Minishell-94b7e6ad303d4b19b1dfe7d4bbacc9aa)

[Notion Notes](https://www.notion.so/Minishell-e856e9af377f44b588e5fe120d4b6e2a)

[Minishell materials](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c)

[Making Linux Shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)

[Building a shell in 10 min](https://www.youtube.com/watch?v=k6TTj4C0LF0)

[Write a Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/)

[Harm Smiths](https://harm-smits.github.io/42docs/projects/minishell)

[Minishell Ex](https://github.com/parismart/minishell)

[Bash reference](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)

[Creating a Lexer & Parse](https://www.youtube.com/watch?v=70NVv0nVLlE&ab_channel=LambdaShow)

[Parse lecture](https://www.youtube.com/watch?v=4m7ubrdbWQU&ab_channel=DmitrySoshnikov)

[Nice Resources](https://github.com/Hamzaelkhatri/minishell)

## How shell interpret a input

1. shell has analyzed input in the following way:

2. The shell reads its input from a file, from a string or from the user's terminal.

3. Input is broken up into words and operators, obeying the quoting rules, see Chapter 3. These tokens are separated by metacharacters. Alias expansion is performed.

4. The shell parses (analyzes and substitutes) the tokens into simple and compound commands.

5. Bash performs various shell expansions, breaking the expanded tokens into lists of filenames and commands and arguments.

6. Redirection is performed if necessary, redirection operators and their operands are removed from the argument list.

7. Commands are executed.

8. Optionally the shell waits for the command to complete and collects its exit status.

## Resume of allowed functions

[readline](https://man7.org/linux/man-pages/man3/readline.3.html): readline from terminal and return it

[rl_clear_history](https://tiswww.case.edu/php/chet/readline/readline.html#IDX357): Clear the history list by deleting all of the entries.

[rl_on_new_line](https://tiswww.case.edu/php/chet/readline/readline.html#IDX363): Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

[rl_replace_line](https://tiswww.case.edu/php/chet/readline/readline.html#IDX338): Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

[rl_redisplay](https://tiswww.case.edu/php/chet/readline/readline.html#IDX304): Change what's displayed on the screen to reflect the current contents of rl_line_buffer.

[add_history](https://man7.org/linux/man-pages/man3/history.3.html): Place string at the end of the history list. The associated data field (if any) is set to NULL.

[access](https://man7.org/linux/man-pages/man2/access.2.html): checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.

[open](https://man7.org/linux/man-pages/man2/open.2.html): system call opens the file specified by pathname. If the specified file does not exist, it may optionally (if O_CREAT
is specified in flags) be created by open(). The return value of open() is a file descriptor, a small, nonnegative integer that is an index to an entry in the process's table of open file descriptors.

[read](https://man7.org/linux/man-pages/man2/read.2.html): attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

[close](https://man7.org/linux/man-pages/man2/close.2.html): closes a file descriptor, so that it no longer refers to any file and may be reused.

[fork](https://man7.org/linux/man-pages/man2/fork.2.html): creates a new process by duplicating the calling process. The new process is referred to as the child process. The calling process is referred to as the parent process.

[wait](https://man7.org/linux/man-pages/man2/wait.2.html): wait for process to change state. system call suspends execution of the calling thread until one of its children terminates.

[waitpid](https://man7.org/linux/man-pages/man2/wait.2.html): system call suspends execution of the calling thread until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument

[wait3, wait4](https://man7.org/linux/man-pages/man2/wait3.2.html): These functions are nonstandard; in new programs, the use of waitpid or waitid is preferable. The wait3() and wait4() system calls are similar to waitpid, but additionally return resource usage information about the child in the structure pointed to by rusage.

[signal](https://man7.org/linux/man-pages/man7/signal.7.html): Avoid its use: use sigaction

[sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html): examine and change a signal action. sigaction() system call is used to change the action taken by a process on receipt of a specific signal.

[kill](https://man7.org/linux/man-pages/man2/kill.2.html): send signal to a process. system call can be used to send any signal to any process group or process.

[exit](https://man7.org/linux/man-pages/man3/exit.3.html): this function causes normal process termination and the least significant byte of status (i.e., status & 0xFF) is returned to the parent

[getcwd](https://man7.org/linux/man-pages/man3/getcwd.3.html): These functions return a null-terminated string containing an absolute pathname that is the current working directory of the calling process. The pathname is returned as the function result and via the argument buf, if present.

[chdir](https://man7.org/linux/man-pages/man2/chdir.2.html): changes the current working directory of the calling process to the directory specified in path

[stat](https://man7.org/linux/man-pages/man1/stat.1.html): display file or file system status, retrieve information about the file pointed to by pathname;

[lstat](https://man7.org/linux/man-pages/man2/lstat.2.html): is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that the link refers to.

[fstat](https://man7.org/linux/man-pages/man2/lstat.2.html): is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.

[unlink](https://man7.org/linux/man-pages/man2/unlink.2.html): deletes a name from the filesystem. If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.

[execve](https://man7.org/linux/man-pages/man2/execve.2.html): executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

[dup](https://man7.org/linux/man-pages/man2/dup.2.html): duplicate a file descriptor, The dup() system call allocates a new file descriptor that refers to the same open file description as the descriptor oldfd.

[dup2](https://man7.org/linux/man-pages/man2/dup.2.html): The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd param. In other words, the file descriptor newfd is adjusted so that it now refers to the same open file description as oldfd.

[pipe](https://man7.org/linux/man-pages/man2/pipe.2.html): creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.

[opendir](https://man7.org/linux/man-pages/man3/opendir.3.html): open a directory, function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.

[readdir](https://man7.org/linux/man-pages/man3/readdir.3.html): function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.

[closedir](https://man7.org/linux/man-pages/man3/closedir.3.html): close a directory, function closes the directory stream associated with dirp.

[strerror](https://man7.org/linux/man-pages/man3/strerror.3.html): function returns a pointer to a string that describes the error code passed in the argument errnum, possibly using the LC_MESSAGES part of the current locale to select the appropriate language.

[perror](https://man7.org/linux/man-pages/man3/perror.3.html): function produces a message on standard error describing the last error encountered during a call to a system or library function.

[isatty](https://man7.org/linux/man-pages/man3/isatty.3.html): function tests whether fd is an open file descriptor referring to a terminal

[ttyname](https://man7.org/linux/man-pages/man3/ttyname.3.html): returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error (for example, if fd is not connected to a terminal).

[ttyslot](https://man7.org/linux/man-pages/man3/ttyslot.3.html): returns the index of the current user's entry in some file.

[ioctl](https://man7.org/linux/man-pages/man2/ioctl.2.html): system call manipulates the underlying device parameters of special files

[getenv](https://man7.org/linux/man-pages/man3/getenv.3.html): function searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string

[tcsetattr](https://man7.org/linux/man-pages/man3/tcsetattr.3p.html): function shall set the parameters associated with the terminal referred to by the open file descriptor fildes (an open file descriptor associated with a terminal) from the termios structure referenced by termios_p.

[tcgetattr](https://man7.org/linux/man-pages/man3/tcgetattr.3p.html): function shall get the parameters associated with the terminal referred to by fildes and store them in the termios structure referenced by termios_p.

[tgetflag, tgetent, tgetnum, tgetstr, tgoto](https://linux.die.net/man/3/tgetflag): These routines are included as a conversion aid for programs that use the termcap library. Their parameters are the same and the routines are emulated using the terminfo database. Thus, they can only be used to query the capabilities of entries for which a terminfo entry has been compiled.
