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
