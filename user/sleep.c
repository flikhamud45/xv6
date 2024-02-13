#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc != 2) 
	    write(1, "Invalid number of arguments", strlen("Invalid number of arguments"));
    else {
    	int n = atoi(argv[1]);
    	if (n==0) {
    	    write(1, "Invalid argumnet", strlen("Invalid argument"));
    	    exit(0);
    	    return 0;
    	}
    	sleep(n*10);
    	write(1, "sleeped for ", strlen("sleeped for ")); 
    }
    exit(0);
}
