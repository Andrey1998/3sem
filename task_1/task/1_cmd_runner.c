/*
  Write a program which allow you to: 
- run another programs via command line.
- get exit codes of terminated programs

## TIPS:
1. Use "2_fork_wait_exit.c" and "4_exec_dir.c" from examples. Combine them.
2. Parse input string according to the type of exec* (see "man exec").
   a) if execvp is used, string splitting into "path" and "args" is all you need.
3. Collect exit codes via waitpid/WEXITSTATUS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>

int main()
{
	char** arg = (char**)malloc(100*sizeof(char*));
	for (int i = 0; i < 100; i++)
	{
		arg[i] = (char*)malloc(100*sizeof(char));
	}
	char c = 'y';
	int j = 0;
	char h;
	int i = 0;
	int status;
	int n;
	while (c =='y')
	{
	c = 0;
        const pid_t pid = fork();
        if (pid == -1) {
                printf("fork() error\n");
                return -1;
        }
        if (pid != 0) {
                waitpid(pid, &status, 0);
                printf("Ret code: %d\n", WEXITSTATUS(status));
		printf("Once more?");
		scanf("%c", &c);
        } else {
		i = 0;
		printf("args:");
		scanf("%d ",&n);
		j = 0;
		for (i = 0; i < n; i++)
		{
			/*
			scanf("%c", &h);
			arg[i][j] = h;
			while (h != '\n')
			{
				j++;
				scanf("%c", &h);
				arg[i][j] = h;
			}
			arg[i]= arg[i] + '\0';
			for (int k = 0; k <= j+1; k++)
				printf ("%c", arg[i][k]);
			printf("%s", arg[i]);
			j = 0;*/
			scanf("%s", arg[i]);
		}
		arg[n] = NULL;
		printf("%s", arg[1]);
		/*
		arg[0] = "1.out" + '\0';
		printf("%s", arg[0]);
		arg[1] = NULL;
		*/
		execve(arg[0], arg, NULL);
        }
	}
        return 0;
}
