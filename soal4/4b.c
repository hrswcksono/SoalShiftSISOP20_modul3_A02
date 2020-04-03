#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int a=0;

void *fac(void *arg){
    int b=0;
    while(a){
        b+=a;
        a--;
    }
    printf("%d ",b);
}


int main(){

    int matC[4][5];
    int r = 4;
    int c = 5;
    int idx = 0;
    int *mat;

    key_t key = 1234;
    int shmid = shmget(key, sizeof(int)*r*c, IPC_CREAT | 0666);
    mat = (int *)shmat(shmid, NULL, 0);

    for (int i = 0; i < r; i++){
       for (int j = 0; j < c; j++){
             matC[i][j] =  mat[(i*6) + j];
       }
    }    

    printf("\nPerkalian matriks\n");

    for (int i = 0; i < r; i++){
       for (int j = 0; j < c; j++){
             printf("%d ",matC[i][j]);
       } 
       printf("\n");
    }

    pthread_t threads[21];

    printf("\nFaktorial jumlah\n");

    for (int i = 0; i < r; i++){
       for (int j = 0; j < c; j++){
            a=matC[i][j];
            int* p;
            pthread_create(&threads[idx], NULL, fac, (void*)(p));
            pthread_join(threads[idx], NULL);
            idx++;
       }
       printf("\n");
    }

    shmdt(mat);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0; 
}
