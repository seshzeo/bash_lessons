#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    if (fork() > 0) {
        pid_t parent = getppid();
        cout << "Hello, i`m parent! My pid is "<< parent << endl;
        sleep(60);
    } else {
        exit(0);
        cout << "Exit from child process...\n";
    }
    return 0;
}
