#include <iostream>
#include <string>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    pid_t pid;
    char cmd;
    char *arg_psa[] = {"ps", "-a", nullptr};
    char *arg_psx[] = {"ps", "-x", nullptr};
    while (true)
    {
        cout << "-------------------------" << endl;
        cout << "enter a : ps -a" << endl;
        cout << "enter x : ps -x" << endl;
        cout << "enter q : quit" << endl;
        cout << "-------------------------" << endl;
        cout << "please enter :";
        cmd = getchar();
        getchar();

        if ((pid = fork()) < 0)
        {
            perror("fork error");
            return -1;
        }
        if (pid == 0)
        {
            switch (cmd)
            {
            case 'a':
                execve("/bin/ps", arg_psa, NULL);
                break;
            case 'x':
                execve("/bin/ps", arg_psx, NULL);
                break;
            case 'q':
                break;

            default:
                cout << "wrong cmd" << endl;
            }
            exit(0);
        }
        else
        {
            if (cmd == 'q')
            {
                break;
            }
        }
    }
    while (waitpid(-1, nullptr, WNOHANG) > 0)
    {
        ;
    }
    return 0;
}
