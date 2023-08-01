#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void allocate_args(int size, char **args);
void set_args(int size, char **argv, char **args);
void free_args(char **args);


int main(int argc, char *argv[])
{
	int pid, status, all;
	char *commit_m, commit[275] = "git commit -m '", *push = "git push";
	char **args = NULL, *commited, *added = "git add .";

	read(STDIN_FILENO, commit_m, 256);
	if (argc < 2)
		all = 1;
	else
	{
		allocate_args(argc, args);
		set_args(argc, argv, args);
	}
	pid = fork();
	if (pid == 0)
	{
		if (all)
			system(added);
		else
			execve("/usr/bin/git", args, NULL);
		commited = strcat(commit, commit_m);
		commited = strcat(commit, "'");
		system(commited);
		system(push);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");
	free_args(args);
	return (0);
}

void allocate_args(int size, char **args)
{
	args = malloc((size + 1)* sizeof(char *));
	if (!args)
		perror("malloc");
}
void set_args(int size, char **argv, char **args)
{
	int i = 0;
	for (; i < size; i++)
		args[i] = strdup(argv[i]);
	args[i] = NULL;
}
void free_args(char **args)
{
	int i = 0;
	if (args)
	{
		while(args[i])
			free(args[i++]);
		free(args[i]);
		free(args);
	}
}
