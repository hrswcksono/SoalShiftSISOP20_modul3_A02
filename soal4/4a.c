#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>


int matA[4][2] = {{1, 2},
                {3, 4},
                {5, 6},
                {7, 8} };

int matB[2][5] = {{1, 2, 3, 4,  5},
                {6, 7, 8, 9, 10} };

int matC[10][10];
int d = 0;

void *multiplicant(void *arg){
int a = d++;
    for (int i = a ; i < (a + 1) ; i=i+5)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 2; k++)
                matC[i][j] += matA[i][k] * matB[k][j];
}

int main(){
    
    int r = 4;
    int c = 5;
    int *mat;

    key_t key = 1234;
    int shmid = shmget(key, sizeof(int)*r*c, IPC_CREAT | 0666);
    mat = (int *)shmat(shmid, NULL, 0);

    pthread_t threads[9];



    for (int i = 0; i < 4; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multiplicant, (void*)(p));
        pthread_join(threads[i], NULL);
    }

    printf("Matriks Pertama\n");
    for (int i = 0; i < 4; i++){   
       for (int j = 0; j < 2; j++){
            printf("%d ",matA[i][j]);
       }
       printf("\n");
    }

    printf("\nMatriks Kedua\n");
    for (int i = 0; i < 2; i++){   
       for (int j = 0; j < 5; j++){
            printf("%d ", matB[i][j]);
       }
       printf("\n");
    }

    for (int i = 0; i < r; i++){
       for (int j = 0; j < c; j++){
            mat[(i*6) + j] = matC[i][j];
       }
    }    

    printf("\nPerkalian matriks\n");

    for (int i = 0; i < r; i++){
       for (int j = 0; j < c; j++){
             printf("%d ",mat[(i*6) + j]);
       } 
       printf("\n");
    } 

    sleep(10);

    shmdt(mat);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0; 
}
