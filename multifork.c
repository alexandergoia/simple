#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void multifork(int no_proc, vector<pid_t> *list, void (*f)());
void hello();

void hello()
{
	printf("hello, world!\n");
}

void multifork(int no_proc, vector<pid_t> *list, void (*f)())
{
	int i;
	pid_t ppid = getppid();
	pid_t pid;
	for(i = 0; i < no_proc && (ppid == getppid()); i++) {
		pid = fork();
		if(pid > 0) 
			list->push_back(pid);
		else if (pid == 0)
			f();
 	}	
}

int main(int argc, char *argv[])
{
	vector<pid_t> pid_list;
	multifork(atoi(argv[1]), & pid_list, hello);
	return(0);
}
		

