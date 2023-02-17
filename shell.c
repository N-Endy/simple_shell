#include "shell.h"

int main(void)
{
	char buffer[BUFFER_SIZE];
	int status;

	while (1)
	{
		printf("$ ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
			break;

		/* Remove the newline character from the end of the input*/
		buffer[strcspn(buffer, "\n")] = 0;

		/* Fork a child process to execute the command */
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			execlp(buffer, buffer, (char *)NULL);
			perror("execlp");
			exit(EXIT_FAILURE);
		} else
			/* Wait for the child process to complete */
			waitpid(pid, &status, 0);
	}

	return (EXIT_SUCCESS);
}
