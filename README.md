## Soal3
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
● Semisal program dijalankan:
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/kategori%20f.png)

● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang user inginkan seperti contoh di atas.
● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual, melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi, maka dia akan disimpan dalam folder “Unknown”.
● Program kategori ini juga menerima perintah (*) seperti di bawah;
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/kategori%20star.png)
● Artinya mengkategori seluruh file yang ada di working directory ketika menjalankan program C tersebut.
● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/kategory%20d.png)

● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/ directory ).
● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau menggunakan (*) terdapat folder yang berisi file, maka file dalam folder tersebut tidak dihiraukan, cukup file pada 1 level saja.
● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang juga menggunakan fork-exec dan system.
● Silahkan download soal3.zip sebagai percobaan. Namun silahkan dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin
belum ada di soal3.zip.

>Source code file: [Soal3](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/soal3.c)

```javascript
char *getExt (char fspec[]) {
    char *e = strrchr (fspec, '.');
    if (e == NULL)
        e = ""; // fast method, could also use &(fspec[strlen(fspec)]).
    return e;
}
```

fungsi getExt digunakan untuk mendapatkan string setelah "." terakhir, misalnya : .jpg, .png, .JPG, .PNG.

```javascript
char *getDir (char fspec[]) {
    char *e = strrchr (fspec, '/');
    if (e == NULL)
        e = ""; // fast method, could also use &(fspec[strlen(fspec)]).
    return e;
}
```

fungsi getDir digunakan untuk mendapatkan string setelah "/" terakhir, misalnya : /jpg, /png, /JPG, /PNG.

```javascript
void lower_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}
```

fungsi lower string untuk merubah huruf kapital jadi huruf kecil.
## -f
```javascript
    if(strcmp(argv[1],"-f")==0){
        for (int i = 2; i < argc; i++) {
           strcpy(in,argv[i]);
           int* p;
           pthread_create(&threads[i-1], NULL, categoryf, (void*)(p));
           pthread_join(threads[i-1], NULL);
           printf("%s\n",input(in));
        }
    }
```
mencopykan setiap pathfile argv[] yang diinputkan ke variable global.
membuat thread sesuai banyaknya path file yang diinpukan.
```javascript
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
```
mendapatkan ekstensi dari nama file tersebut untuk membuat nama folder "strtok(getExt((in)),".")"
jika tidak ada exstensinya akan membuat folder "Unknown"
mendapatkan nama file dengan "strtok(getDir(in),"/")"
kemudian gabungkan nama file dengan nama folder masing-masing
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3f%20null.png)
sebelum program dijalankan
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3f%20input.png)
input pada program
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3f%20hasil.png)

## *
```javascript
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
```
membuka direktori "." atau tempat file tersebut di jalankan, dan menghitung banyaknya file bukan folder di direktori sekarang,
dan membuat thread sebanyak file yang ada

```javascript
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
```
thread : membuka direktori file dan memindahkan kedalam folder sesuai exstensinya, dan jika tidak punya extensi maka akan dipindahkan ke folder "Unknown".
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3%20star%20null.png)
sebelum program dijalankan
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3%20star%20input.png)
input pada program
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3%20star%20hasil.png)

## -d

```javascript
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
```
membuka direktori sesuai path direktori yang di inputkan, kemudian menghitung file bukan folder yang ada di dalamnya.
kemudian jumlah file tersebut digunakan untuk membuat banyaknya thread.

```javascript
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
```
Thread : membuka direktori sesuai inputan, mendapatkan ekstensi file tersebut untuk membuat folder pada direktori program dijalankan.
Untuk memindahkan file tersebut harus menggabungkan path direktori dan nama file yang ada "path_direktori/nama_file", 
kemudian selanjutnya gabungkan nama ekstensinya dengan nama file di direktori yang di buka terseut misal : "jpg/qwerty.jpg", png/qwerty.PNG.
kemudian hasil gabungan tersebut digunakan untuk memindahkan file.
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3%20d%20null.png)
sebelum program dijalankan
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3%20d%20input.png)
input pada program
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal3/3%20d%20hasil.png)

## Soal4
Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda. 

Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian.

- Batu mulia pertama. Emerald. Batu mulia yang berwarna hijau mengkilat. Pada
batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan
matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.


```
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
```

![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal4/4a.png)

- Batu kedua adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya
adalah:

1. Buatlah program C kedua dengan nama "4b.c". Program ini akan
mengambil variabel hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(Catatan!: gunakan shared memory)
2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan
format seperti matriks.

Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...],

maka:

1 2 6 24
120 720 ... ...
...

(Catatan! : Harus menggunakan Thread dalam penghitungan
faktorial)


```
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
```

![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal4/4b.png)

- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan
teka-teki berikut!

1. Buatlah program C ketiga dengan nama "4c.c". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.
(Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin
besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah
batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.

```
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(){
    int fd[2];
    pid_t cpid;

    pipe(fd);

    cpid = fork();
    if (cpid == 0){
        dup2(fd[1],STDOUT_FILENO);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
    }

    else {
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"wc", "-l", NULL};
        execv("/bin/wc", argv);
    }
}
```
![screenshot_bang](https://github.com/hrswcksono/SoalShiftSISOP20_modul3_A02/blob/master/soal4/4c.png)

Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak
pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada
Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta
karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut.
Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut
melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece
does exist".

