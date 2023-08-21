#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rowsA = 2;
    int colsA = 3;
    int rowsB = 3;
    int colsB = 2;

    std::vector< std::vector<int> > A = {{1, 2, 3}, {4, 5, 6}};
    std::vector< std::vector<int> > B = {{7, 8}, {9, 10}, {11, 12}};
    std::vector< std::vector<int> > C(rowsA, std::vector<int>(colsB));

    int num_processes = rowsA;

    int pipes[num_processes][2];
    for (int i = 0; i < num_processes; ++i) {
        if (pipe(pipes[i]) == -1) {
            std::cerr << "Error creating pipe\n";
            return -1;
        }
    }

    // создание дочерних процессов
    for (int i = 0; i < num_processes; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            std::cerr << "Error creating child process\n";
            return -1;
        } else if (pid == 0) {
            for (int j = 0; j < colsB; ++j) {
                C[i][j] = 0;
                for (int k = 0; k < colsA; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }

            write(pipes[i][1], C[i].data(), colsB * sizeof(int));
            close(pipes[i][1]);

            exit(0);
        }
    }

    // родительский процесс
    for (int i = 0; i < num_processes; ++i) {
        close(pipes[i][1]);

        read(pipes[i][0], C[i].data(), colsB * sizeof(int));
        close(pipes[i][0]);

        wait(nullptr); // Ожидание завершения дочернего процесса
    }

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            std::cout << C[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}