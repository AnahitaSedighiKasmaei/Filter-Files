# Filter-Files

A C program, called it findExt, to find all files in a directory hierarchy, whose extensions
are in the extension list provided as arguments to the program. Your program should print the
whole pathnames of the found files.
Synopsis: findExt <extension-list> [-t target-directory]
When target-directory is missing, the working directory (./) will be the target directory
Some sample runs:
$ findExt txt pdf
That is, find all files whose extensions are either txt or pdf in the directory hierarchy ./
$ findExt jpg -t $HOME //target directory is home directory
That is, find all files whose extensions is jpg in the directory hierarchy $HOME
Requirement:
- You must use the system call nftw() that allows you to walk across a file tree. This system call
will do all the recursive walk and each time it visits a file or a directory, it will call your own
function (a function that you pass as a parameter). Read the manual of nftw() before starting
your assignment.
