#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid_padre = fork();

    if (pid_padre < 0) {
        perror("fork");
        exit(1);
    }

    if (pid_padre == 0) {
        // Processo Padre (figlio del nonno)
        pid_t pid_nipote = fork();

        if (pid_nipote < 0) {
            perror("fork");
            exit(1);
        }

        if (pid_nipote == 0) {
            // Processo Nipote
            printf("Nipote (PID %d): termino.\n", getpid());
            exit(0);
        }

        wait(NULL);
        printf("Padre (PID %d): il nipote ha terminato, chiudo.\n", getpid());
        exit(0);
    }

    wait(NULL);
    printf("Nonno (PID %d): il padre ha terminato, chiudo.\n", getpid());
    return 0;
}