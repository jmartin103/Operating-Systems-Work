#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/* Calculate the Collatz conjecture pattern */
int collatz(int num) {
	printf("%d, ", num);
	if (num == 1) {
	}
	else if (num % 2 == 0)
		collatz(num / 2);
	else
		collatz(3 * num + 1);
	return num;
}
int main(int argc, char *argv[])
{
	pid_t pid, pid1;
	int n;
	if (argc == 1) {
		fprintf(stderr,"Usage: ./a.out <starting value>\n");
		return 1;
	}
	n = atoi(argv[1]);

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) {
		pid1 = getpid();
		printf("child: pid = %d\n", pid);
		printf("child: pid1 = %d\n", pid1);
	}
	else {
		pid1 = getpid();
		printf("parent: pid = %d\n", pid);
		printf("parent: pid1 = %d\n", pid1);
		wait(NULL);
	}
	collatz(n);
	printf("\n");
	return 0;
}