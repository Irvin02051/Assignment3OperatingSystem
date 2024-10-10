#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

const int SIZE = 20;

int main() {
    int arr[SIZE];
    srand(static_cast<unsigned>(time(0)));

    // Fill the array with random numbers
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 51; // Random numbers between 0 and 99
    }

    // Print the array
    std::cout << "Array: ";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        std::cerr << "Fork Unsuccessful!" << std::endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        int minChild = arr[SIZE / 2];
        for (int i = SIZE / 2 + 1; i < SIZE; ++i) {
            if (arr[i] < minChild) {
                minChild = arr[i];
            }
        }

        std::cout << "Child Process ID: " << getpid() << " - Minimum found in the second half: " << minChild << std::endl;
        exit(minChild);
    } else {
        // Parent process
        int minParent = arr[0];
        for (int i = 1; i < SIZE / 2; ++i) {
            if (arr[i] < minParent) {
                minParent = arr[i];
            }
        }

        // Wait for child process to finish and get its minimum
        int minChild;
        waitpid(pid, &minChild, 0);
        minChild = WEXITSTATUS(minChild);

        std::cout << "Parent Process ID: " << getpid() << " - Minimum found in the first half: " << minParent << std::endl;
        std::cout << "Minimum number of the array : " << std::min(minParent, minChild) << std::endl;
    }

    return 0;
}
