#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Fonction pour calculer le n-ième nombre de Catalan
long catalan(int n) {
    long res = 1;
    for (int i = 0; i < n; ++i) {
        res = res * (2 * (2 * i + 1)) / (i + 2);
    }
    return res;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nombre>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // Nombre de termes à générer
    if (n <= 0) {
        fprintf(stderr, "Le nombre doit être > 0.\n");
        return 1;
    }

    // Création de la mémoire partagée
    int shmid = shmget(1234, sizeof(long) * (n + 1), IPC_CREAT | 0666);
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

    shm[0] = n;  // Stocke la valeur de n dans la première case

    // Calcul et stockage des nombres de Catalan
    for (int i = 1; i <= n; i++) {
        shm[i] = catalan(i);
    }

    printf("Producteur : %d nombres de Catalan générés dans la mémoire partagée.\n", n);

    // Détachement
    shmdt(shm);
    return 0;
}
