pipex is a C program that mimics the behavior of a shell command pipeline, simulating the redirection of input and output between two commands using pipes. The program reads from an input file, executes two specified commands with their arguments, and writes the result to an output file. It is designed to replicate the functionality of a typical shell pipeline like:

bash
Copy
Edit
< file1 cmd1 | cmd2 > file2
This project demonstrates handling pipes, forking processes, redirecting file descriptors, and using execve to run shell commands. It requires careful error handling and resource management to ensure correct behavior and avoid memory leaks.
