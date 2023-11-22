#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void run(int read_left_pipe) { 
	int p;
	int i = read(read_left_pipe, &p, sizeof(p));
	if (i == 0) 
		printf(":(");
	printf("prime %d\n", p);
	int n = 0;
	if (p < 31) {
		int pipe_fd[2];
		pipe(pipe_fd);
		int pid = fork();
		if(pid == 0) {
			close(pipe_fd[1]);
			run(pipe_fd[0]);
			close(read_left_pipe);
			return;
		}
		close(pipe_fd[0]);
		while( n < 31) {
			read(read_left_pipe, &n, sizeof(n));
			if (n % p != 0)
				write(pipe_fd[1],  &n, sizeof(n));
		}
		close(pipe_fd[1]);
		wait(0);
	}
	close(read_left_pipe);
}

int main(int argc, char *argv[])
{
    int pipe_fds[2];
    pipe(pipe_fds);
    int pid = fork();
    if (pid == 0) {
	close(pipe_fds[1]);
	run(pipe_fds[0]);
    }
    else {
	// parent
	close(pipe_fds[0]);
	for(int i = 2; i < 35; i++) {
		write(pipe_fds[1], &i, sizeof(i));
	}
	close(pipe_fds[1]);
	wait(0);
    };
    exit(0);
}
