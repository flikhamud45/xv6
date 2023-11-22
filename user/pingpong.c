#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pipe1_fds[2];
    int pipe2_fds[2];
    pipe(pipe1_fds);
    pipe(pipe2_fds);
    int pid = fork();
    if (pid == 0) {
	// child
	char buff[2];
	read(pipe1_fds[0], buff, 1);
	//char s[100];
	//itoa(getpid(), s, 10);
	//strcat(s, ": received ping\n");
        //write(1, s, strlen(s));
	printf("%d: received ping\n", getpid());
        write(pipe2_fds[1], buff, 1);
    }
    else {
	// parent
	write(pipe1_fds[1], "a", 1);
	char buff[2];
	read(pipe2_fds[0], buff, 1);
	//char s[100];
	//itoa(getpid(), s, 10);
        //strcat(s, ": received pong\n");
	//write(1, s, strlen(s));
	printf("%d: received pong\n", getpid());
	
	
    }
    close(pipe1_fds[0]);
    close(pipe1_fds[1]);
    close(pipe2_fds[0]);
    close(pipe2_fds[1]);
    exit(0);
}
