#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char input[100];
	char input_c[100];

	char* tempStr[20] = {NULL};
	char* arg[20] = {NULL};
	int i;
	int j;
	int res;
	pid_t pid;
	
	while(1)
	{
		for(int c = 0; c < 20; c++)
		{
			tempStr[c] = '\0';
			arg[c] = '\0';
		}
		i = 0;
		printf("$ ");
//		atexit(myExit);
		fgets(input, sizeof(input), stdin);
		input[strlen(input)-1] = '\0';
		strcpy(input_c, input);
		if(strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0)
			exit(0);
		char *ptr = strtok(input, " ");
		while(ptr != NULL)
		{
			tempStr[i] = ptr;
			i++;
			ptr = strtok(NULL, " ");
		}
		for (j = 0; j < i; j++)
		{
			arg[j] = tempStr[j];
		}
		char* file = tempStr[0];
//		printf("%s\n", file);
//		printf("%s\n", arg[0]);

		if(strcmp(arg[0], "chdir") == 0 || strcmp(arg[0], "cd") == 0)
		{
			char path[200];
			int ch = chdir(arg[1]);	// chdir의 경우 다음 명령어는 위치
			getcwd(path, 200);
			if(ch == 0)
				printf("%s\n", path);
			else
				printf("\'%s\' to \'%s\' is failed.\n", arg[0], arg[1]);
			continue;
		}

		if((pid = fork()) < 0)
		{
			printf("fail to fork\n");
			exit(1);
		}
		else if(pid == 0)
		{
			execvp(file, arg);
			printf("\'%s\' is failed\n", input_c);
			exit(1);
		}
		if((pid = waitpid(pid, &res, 0)) < 0)
		{
			printf("waitpid error\n");
		}
		else
			printf("(%d)\n", pid);
	}
	return 0;
}
