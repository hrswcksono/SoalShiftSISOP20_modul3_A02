#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
//#include <dir.h>

char *getExt (char fspec[]) {
    char *e = strrchr (fspec, '.');
    if (e == NULL)
        e = ""; // fast method, could also use &(fspec[strlen(fspec)]).
    return e;
}

char *getDir (char fspec[]) {
    char *e = strrchr (fspec, '/');
    if (e == NULL)
        e = ""; // fast method, could also use &(fspec[strlen(fspec)]).
    return e;
}

char *input(char *inp){
    return inp;
}

void lower_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

struct stat st = {0};

char in[100];

void* categoryf(void *arg){
    char nf[100];
    char na[100];
    strcpy(na,strtok(getExt((in)),"."));
    lower_string(na);
    memset(nf, '\0', sizeof(nf));
    if(strlen(getExt(in)) != 0){
     if (stat(na, &st) == -1)
     {
        mkdir(na,0777);
     }
     sprintf(nf,"%s/%s",  na, strtok(getDir(in),"/") );
     rename(in, nf);
     //printf("%s %s   %s\n",strtok(getExt(in),"."), nf,in );
     //memset(in, '\0', sizeof(in));
     }
     else{
     if (stat("Unknown)", &st) == -1)
     {    
        mkdir("Unknown",0777);
     }
     sprintf(nf,"Unknown/%s",strtok(getDir(in),"/"));
     rename(in, nf);
     }
}

void* categorystar(void *arg){
    char nama[100];
    struct dirent *de;
    DIR *dr = opendir(".");
    while ((de = readdir(dr)) != NULL){ 
       if (de->d_type == DT_REG)
       {    
         if(strlen(getExt(de->d_name)) != 0){
              char na[100];
              strcpy(na,strtok(getExt((de->d_name)),"."));
              lower_string(na);
              if (stat(na, &st) == -1)
              {
                 mkdir(na,0777);
              }
              sprintf(nama,"%s/%s",na,de->d_name);
              //sprintf(buffer,"%s/%s",input(in),de->d_name);
              //printf("%s\n",de->d_name);
              //printf("%s\n",buffer);
              rename(de->d_name , nama);
           
        }
       else{
         if (stat("Unknown)", &st) == -1)
         {    
             mkdir("Unknown",0777);
         }
         sprintf(nama,"Unknown/%s",de->d_name);
         rename(de->d_name, nama);
       }}
    }
    closedir(dr);
}

void* categoryd(void *arg){
    char asal[100];
    char nama[100];
    struct dirent *de;
    DIR *dr = opendir(in);
    while ((de = readdir(dr)) != NULL){ 
       if (de->d_type == DT_REG)
       {    
         if(strlen(getExt(de->d_name)) != 0){
              char na[100];
              strcpy(na,strtok(getExt((de->d_name)),"."));
              lower_string(na);
              if (stat(na, &st) == -1)
              {
                 mkdir(na,0777);
              }
              sprintf(nama,"%s/%s",na,de->d_name);
              sprintf(asal,"%s/%s",in,de->d_name);
              //printf("%s\n",de->d_name);
              //printf("%s\n",buffer);
              rename(asal , nama);
           
        }
       else{
         if (stat("Unknown)", &st) == -1)
         {    
             mkdir("Unknown",0777);
         }
         sprintf(asal,"%s%s",in,de->d_name);
         sprintf(nama,"Unknown/%s",de->d_name);
         rename(asal, nama);
       }}
    }
    closedir(dr);
}



int main(int argc, char *argv[]){
    pthread_t threads[20];
    int a=0;
    if(strcmp(argv[1],"-f")==0){
        for (int i = 2; i < argc; i++) {
           strcpy(in,argv[i]);
           int* p;
           pthread_create(&threads[i-1], NULL, categoryf, (void*)(p));
           pthread_join(threads[i-1], NULL);
           printf("%s\n",input(in));
        }
    }
    else if(strcmp(argv[1],"*") == 0){
        struct dirent *de;
        DIR *dr = opendir(".");
        while ((de = readdir(dr)) != NULL){ 
        if (de->d_type == DT_REG)
        {
          a++;
        }
        }
        printf("%d\n",a);
        closedir(dr);
        for(int b=0;b<a;b++){
           int* p;
           pthread_create(&threads[b], NULL, categorystar, (void*)(p));
           pthread_join(threads[b], NULL);
        }
    }
    else if(strcmp(argv[1],"-d") == 0){
        struct dirent *de;
        DIR *dr = opendir(argv[2]);
        while ((de = readdir(dr)) != NULL){ 
        if (de->d_type == DT_REG)
        {
          a++;
        }
        }
        printf("%d\n",a);
        closedir(dr);
        strcpy(in,argv[2]);
        for(int b=0;b<a;b++){
           int* p;
           pthread_create(&threads[b], NULL, categoryd, (void*)(p));
           pthread_join(threads[b], NULL);
        }

    }
}
