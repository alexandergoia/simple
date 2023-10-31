#include <unistd.h>
#include <cstdio>
#include <vector>

using namespace std;

int multifork(int n, vector<pid_t> *processes)
{
    int pid = getpid();
    int i;
    int forkpid;

    for(i = 0; i < n; i++)
    {
        if(getpid() == pid)
        {
            forkpid = fork();
            if(forkpid == 0) return 0;
            else
            {
                processes->push_back(forkpid);
            }
        }
    }

    return 0;
}

int main()
{
    vector<pid_t> procs;
    multifork(3, &procs);
    printf("hello world\n");
}

