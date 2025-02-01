<div align = center>

# :shell: Minishell | 42 SP

![Norminette](https://github.com/RogerioLS/Minishell-42sp/actions/workflows/norminette.yml/badge.svg)
![Build](https://github.com/RogerioLS/Minishell-42sp/actions/workflows/build.yml/badge.svg)
![Static Badge](https://custom-icon-badges.demolab.com/badge/MINISHELL-42-blue?logo=repo)
![42 São Paulo](https://custom-icon-badges.demolab.com/badge/42-SP-1E2952)
![License](https://custom-icon-badges.demolab.com/github/license/RogerioLS/Minishell-42sp?logo=law&color=dark-green)
![Code size in bytes](https://custom-icon-badges.demolab.com/github/languages/code-size/RogerioLS/Minishell-42sp?logo=file-code&color=dark-green)
![Top language](https://custom-icon-badges.demolab.com/github/languages/top/RogerioLS/Minishell-42sp?color=dark-green)
![Last commit](https://custom-icon-badges.demolab.com/github/last-commit/RogerioLS/Minishell-42sp?logo=history&color=dark-green)
![Repo size](https://custom-icon-badges.demolab.com/github/repo-size/RogerioLS/Minishell-42sp?logo=database)
![Languages](https://custom-icon-badges.demolab.com/github/languages/count/RogerioLS/Minishell-42sp?logo=command-palette&color=red)
![GitHub repo file count (file type)](https://custom-icon-badges.demolab.com/github/directory-file-count/RogerioLS/Minishell-42sp%2Fsources?logo=file&label=files%20sources&color=8602b1)
![Discord](https://custom-icon-badges.demolab.com/discord/1114673462859006044?&logo=comments&label=testemunhas%20de%20vim&color=ffbe3a)
![](https://img.shields.io/github/forks/RogerioLS/Minishell-42sp)

</div>

---

In this project, students are tasked with building a program that executes in a loop*, prompting the user for a command (or sequence of commands**), interpreting the inserted input and then executing the command, finally returning the prompt back to the user, until it is terminated by the user.

This minishell is able to run any commands that can be found in the `$PATH` variable or otherwise in a specified path; redirect input and outputs with redirection operators, as well as some built-in functionalities, and also supports the wildcard character `*`.

> *Commonly referred to as REPL - Read, Evaluate and Print Loop. Learn more about the REPL studying [this diagram](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J).
> ![image](https://user-images.githubusercontent.com/49699403/212203315-c6d419cd-427c-43da-8a15-3c4c5731360c.png)

> **Also know as `pipelines`, that is, a sequence of terminal commands separated by the pipe character `|`.

---

### Supported Features

Minishell is a miniature shell program based on Bash. Minishell supports:
* Prompt display
* Command history (up and down arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Local executables (`./minishell`)
* Builtin commands :
  * `echo` (and option `-n`)
  * `cd` (with only a relative or absolute path)
  * `pwd` (no options)
  * `export` (no options)
  * `unset` (no options)
  * `env` (no options or arguments)
  * `exit` (with exit number but no other options) 
* Pipes `|` which redirect output from one command to input for the next
* Redirections:
  * `>` redirects output
  * `>>` redirects output in append mode
  * `<` redirects input
  * `<< DELIMITER` displays a new prompt, reads user input until reaching `DELIMITER`, redirects user input to command input (does not update history)
* Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
  * `$?` expands to the exit status of the most recently executed foreground pipeline.
* User keyboard signals:
  * `ctrl-c` displays a new prompt line.
  * `ctrl-d` exits minishell
  * `ctrl-\` does nothing

However, Minishell does not support `\`, `;`, `&&`, `||`, or wildcards.

---

### Useful Resources for the Minishell Project

:us: Articles in English about the concepts tackled in this project: 

* [Creating and Killing Child Processes in C](https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/)
* [Pipe: an Inter-Process Communication Method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)
* [Sending and Intercepting a Signal in C](https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/)
* [Handling a File by its Descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
* [Errno and Error Management in C](https://www.codequoi.com/en/errno-and-error-management-in-c/)

:fr: Articles en français sur les concepts abordés dans ce projet :

* [Créer et tuer des processus fils en C](https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/)
* [Pipe : une méthode de communication inter-processus](https://www.codequoi.com/pipe-une-methode-de-communication-inter-processus/)
* [Envoyer et intercepter un signal en C](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)
* [Manipuler un fichier à l’aide de son descripteur en C](https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/)
* [Errno et la gestion d’erreur en C](https://www.codequoi.com/errno-et-la-gestion-derreur-en-c/)

Other useful links:

* [Bash reference manual](https://www.gnu.org/software/bash/manual/bash.html)
* Introduction to Systems Programming: a Hands-on Approach, [Chapter 5. Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [Stephen Brennan's Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* The Open Group Base Specifications, [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [A Guide to Unix Shell Quoting](https://rg1-teaching.mpi-inf.mpg.de/unixffb-ss98/quoting-guide.html)
* [Austin Tripp's Quick Tutorial on Bash Quotes](https://www.austintripp.ca/blog/2019/07/18/bash-quotes)


## Download and use this project

``` shell
$> git clone https://github.com/RogerioLS/Minishell-42sp
$> cd Minishell-42sp
$> make
$> ./minishell
```

If you want to exit the minishell, simply type in the command `exit` or press `ctrl+D`. There ya go!

---

> [!NOTE]  
> Because of 42 School norm requirements:
> * Each function can't have more than 25 lines of code.
> * All variables are declared and aligned at the top of each function.
> * Project should be created just with allowed functions otherwise it's cheating.