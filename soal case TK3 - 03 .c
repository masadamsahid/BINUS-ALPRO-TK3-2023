//
// Created by masad on 7/13/2023.
//
// test cases are provided in "./soal case TK3 - 03 - barang buku testing inputs.txt"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
  char nama[64];
  char deskripsi[1024];
} Kategori;

typedef struct {
  char nama[64];
  char deskripsi[1024];
} Penerbit;

typedef struct {
  char id_buku[40];
  char judul_buku[64];
  int jumlah_buku;
  char pengarang_buku[32];
  char no_ISBN[20];
  Kategori kategori_buku;
  Penerbit penerbit;
} Barang;

Kategori categories[] = {
  {"Fiksi", "Deskripsi buku fiksi."},
  { "Kuliner", "Deskripsi buku kuliner." },
  { "Biologi", "Deskripsi buku biologi." },
  { "Filsafat", "Deskripsi buku filsafat." },
  { "Komputer", "Deskripsi buku komputer." },
  { "Managemen", "Deskripsi buku manajemen." },
};

Penerbit publishers[] = {
  {"Erlangga", "Deskripsi Penerbit Erlangga"},
  {"Tiga Sekawan", "Deskripsi Penerbit Tiga Sekawan"},
  {"Gramedia", "Deskripsi Penerbit Gramedia"},
  {"Tiga Dunia", "Deskripsi Penerbit Tiga Dunia"}
};

typedef union Generic_u {
  Kategori kategori;
  Penerbit penerbit;
} Generic;

char* getIDUsingCurrentDateTime() ;
char* generateRandomNumberString(int length);
void printPilihan(void *pArrOfStruct, int length);
void printPilihanKategori();
void printPilihanPenerbit();

Kategori pilihKategori(int n){
  return categories[n-1];
};

Penerbit pilihPenerbit(int n){
  return publishers[n-1];
}

int main(){
  
  int n = 5;
  Barang barang[n];
  
  printf("Mohon masukkan 5 buku beserta detailnya!\n");
  
  char buffer[100];
  
  for (int i = 0; i < n; i++) {
    printf("\nInput barang #%d\n", i+1);
    
    strcpy(barang[i].id_buku, getIDUsingCurrentDateTime());
    
    printf("Masukkan judul buku: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %20[^\n]", barang[i].judul_buku);
    
    printf("Masukkan jumlah :");
    scanf("%d", &barang[i].jumlah_buku);
    fflush(stdin);
    
    printf("Masukkan pengarang: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %20[^\n]", barang[i].pengarang_buku);
    
    printf("Masukkan ISBN: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %20[^\n]", barang[i].no_ISBN);
    
    
    int chosenCategory;
    
    printf("\n");
    printPilihanKategori();
    printf("Pilih Kategori: ");
    scanf("%d", &chosenCategory);
    barang[i].kategori_buku = pilihKategori(chosenCategory);
    fflush(stdin);
    
    
    int chosenPublisher;
    
    printf("\n");
    printPilihanPenerbit();
    printf("Pilih Penerbit:");
    scanf("%d", &chosenPublisher);
    barang[i].penerbit = pilihPenerbit(chosenPublisher);
    fflush(stdin);
    
  }
  
  
  printf("\n\n============================= DAFTAR BARANG =============================\n");
  
  for (int i = 0; i < n; ++i) {
    printf("\nDetail Barang #%d\n", i+1);
    
    printf("%-10s: %s\n", "Judul Buku", barang[i].judul_buku);
    printf("%-10s: %s\n", "ID", barang[i].id_buku);
    printf("%-10s: %d\n", "Jumlah", barang[i].jumlah_buku);
    printf("%-10s: %s\n", "Pengarang", barang[i].pengarang_buku);
    printf("%-10s: %s\n", "ISBN", barang[i].no_ISBN);
    printf("%-10s: %s\n", "Kategori", barang[i].kategori_buku.nama);
    printf("%-10s: %s\n", "Penerbit", barang[i].penerbit.nama);
    
  }
  
  printf("\n\nKetikkan apapun untuk keluar...");
  getch();
  
  return 0;
}

void printPilihan(void *pArrOfStruct, int length){
  
  Generic *ptr = (Generic *) pArrOfStruct;
  
  
  for (int i = 0; i < length; i++) {
    
    char *choice;
    
    if(strlen(ptr->penerbit.nama) == 0 || ptr->penerbit.nama[0] == '\n'){
      choice = ptr[i].penerbit.nama;
    } else {
      choice = ptr[i].kategori.nama;
    }
    
    printf("(%d) = \"%s\"", i+1, choice);
    
    if(i != length-1) printf(" | ");
  }
  
}

void printPilihanKategori(){
  int lengthOfCategories = sizeof(categories)/ sizeof(categories[0]);
  
  printPilihan(categories, lengthOfCategories);
  
  printf("\n");
}

void printPilihanPenerbit(){
  int lengthOfPublishers = sizeof(publishers)/ sizeof(publishers[0]);
  
  printPilihan(publishers, lengthOfPublishers);
  
  printf("\n");
}

char* getIDUsingCurrentDateTime() {
  time_t currentTime;
  struct tm* timeInfo;
  char* dateTimeString = (char*)malloc(sizeof(char) * 100);
  
  currentTime = time(NULL);
  
  timeInfo = localtime(&currentTime);
  
  strftime(dateTimeString, 100, "B-%y%m%d%H%M%S", timeInfo);
  
  strcat(dateTimeString, generateRandomNumberString(2));
  
  return dateTimeString;
}

char* generateRandomNumberString(int length) {
  char* str = (char*)malloc((length + 1) * sizeof(char));
  int i;
  
  for (i = 0; i < length; i++) {
    int randomNum = rand() % 10;
    str[i] = randomNum + '0';
  }
  
  str[length] = '\0';
  return str;
}