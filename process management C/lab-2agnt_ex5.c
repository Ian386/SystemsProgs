//NAME: IAN NDOLO MWAU
//REG NO: SCT211-0034/2022

/* Write program to illustrate the usage of execlp(), execle(), execv(), execvp(), execve() system calls, ensure that in your program, there are enough comments explaining each of the working */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
// The exec family of functions replaces the current running process with a new process. It can be used to run a C program by using another C program.

// The exec family includes several variations, which all load and run a new program, but they differ in how arguments and environment variables are passed to the new program.
{
    // execlp() system call

    // The execlp() system call executes a program specified by a filename, using the system's PATH to find the executable.
    // The execlp() system call takes the file name to be executed and a list of arguments as arguments.
    // The last argument must be NULL.
    // If the file is found, it is executed.
    // If the file is not found, the execlp() system call returns -1.

    // execlp() system call example
    printf("Running execlp to execute 'ls' command:\n");
    // The execlp() system call replaces the current process with the "ls -l" command.

    if (fork() == 0)
    {
        //child process

        // ------------SYNTAX----------------
        // execlp(program_name, arg0, arg1, ..., NULL);
        execlp("ls", "ls", "-l", NULL);
        // If execlp() is successful, the following code will not be executed.
        printf("execlp() failed\n");
        exit(EXIT_FAILURE);
    }
    // The parent process waits for the child process to finish executing.
    wait(NULL);




    // execle() system call
    // The execle() system call is similar to the execlp() system call, but it allows you to specify the environment variables for the new process.
    // The execle() system call takes the file name to be executed, a list of arguments, and the environment variables as arguments.
    // The last argument must be NULL.


    // execle() system call example
    // This will execute the `env` command and print custom environment variables.
    printf("\nRunning execle to print custom environment variables:\n");
    if (fork() == 0)
    {
        // In the child process
        // The execle() system call replaces the current process with the "env" command and custom environment variables.
        char *env[] = {"MYVAR=HelloWorld", NULL};
        // execle(path, arg0, ..., NULL, envp)
        execle("/usr/bin/env", "env", NULL, env);
        // If execle() is successful, the following code will not be executed.
        perror("execle failed");
        exit(EXIT_FAILURE);
    }
    wait(NULL);




    // execv() system call
    // The execv() system call is similar to the execlp() system call, but it takes an array of arguments instead of a list of arguments.
    // The execv() system call takes the file name to be executed and an array of arguments as arguments.
    // The last element of the array must be NULL.
    // If the file is found, it is executed.
    // If the file is not found, the execv() system call returns -1.



    // execv() system call example
    printf("\nRunning execv to execute 'ls' command:\n");
    // This will execute the `ls` command with arguments passed as an array.

    if (fork() == 0)
    {
        // In the child process
        char *args[] = {"ls", "-a", NULL}; // Argument array (argv)
        execv("/bin/ls", args);            // execv(path, argv)
        perror("execv failed");
        exit(EXIT_FAILURE);
    }
    wait(NULL);



    // execvp() system call
    // The execvp() system call is similar to the execv() system call, but it searches for the file in the directories listed in the PATH environment variable.
    // The execvp() system call takes the file name to be executed and an array of arguments as arguments.
    // The last element of the array must be NULL.
    // If the file is found, it is executed.
    // If the file is not found, the execvp() system call returns -1.



    // execvp() system call example
    printf("\nRunning execvp to execute 'ls' command:\n");
    // This will execute the `ls` command using the system's PATH.

    if (fork() == 0)
    {
        // In the child process
        char *args[] = {"ls", "-R", NULL}; // Argument array (argv)
        execvp("ls", args);                // execvp(file, argv)
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    // execve() system call
    // The execve() system call is similar to the execv() system call, but it allows you to specify the environment variables for the new process.
    // It takes an array of arguments and environment variables but doesn't use PATH to find the program, so it requires a full path.
    // The execve() system call takes the file name to be executed, an array of arguments, and the environment variables as arguments.
    // The last element of the array must be NULL.
    // If the file is found, it is executed.



    // execve() system call example
    printf("\nRunning execve to print custom environment variables:\n");
    // This will execute the `env` command with custom environment variables passed as an array.

    if (fork() == 0)
    {
        // In the child process
        char *args[] = {"env", NULL};                                           // Argument array (argv)
        char *env[] = {"USER=student", "PATH=/usr/bin", "MYENV=TestEnv", NULL}; // Environment array (envp)
        execve("/usr/bin/env", args, env);                                      // execve(path, argv, envp)
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    
    };


    
// ---------------NOTES----------------
//No wait() Used: The parent process doesn't call wait() for the child processes to finish, meaning the child processes run independently. Since exec() replaces the child process image, it won't return control back to the child once the new program starts.
//Custom Environments: execle() and execve() allow passing custom environment variables.
//PATH Lookup: execlp() and execvp() search for the program in the system's PATH, while execle(), execv(), and execve() require the full path to the executable.