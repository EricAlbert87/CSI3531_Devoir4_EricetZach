#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    // Récupération de l'ID de la mémoire partagée
    int shmid = shmget(1234, 0, 0666);
    if (shmid < 0) {
        perror("Erreur shmget");
        return 1;
    }

    // Attachement à la mémoire
    long *shm = (long *)shmat(shmid, NULL, 0);
    if (shm == (long *)-1) {
        perror("Erreur shmat");
        return 1;
    }

    // Lecture de n (nombre de termes)
    int n = shm[0];
    printf("Consommateur : lecture de %d nombres de Catalan.\n", n);

    // Affichage des nombres
    for (int i = 1; i <= n; i++) {
        printf("C%d = %ld\n", i, shm[i]);
    }

    // Détachement
    shmdt(shm);
    return 0;
}
