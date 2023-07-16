//
// Created by masad on 7/16/2023.
//
// test cases are provided in "./soal case TK3 - 04 gaji karyawan testing inputs.txt"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>


#define GAJI_POKOK_D1 2500000
#define GAJI_POKOK_D2 2000000
#define GAJI_POKOK_D3 1500000

#define TARIF_LEMBUR_PER_JAM 20000


typedef enum Kategori_e {D1=1, D2, D3, KATEGORI_COUNT} Kategori;

typedef struct Pegawai_s {
  char nip[30];
  char nama[64];
  char alamat[256];
  char no_hp[40];
  Kategori kategori;
} Pegawai;

typedef struct DataLemburan_s {
  char nip[30];
  int jmlJamLembur;
} DataLemburan;


void printPilihanKategori();
int pilihKategoriPegawai(int pilihan);
Pegawai * inputPegawai(int howMany);

DataLemburan * inputLemburanPegawai(int howMany);

// Searching for the match index
int findIndexOfDataLemburanByNIP(DataLemburan **ptrDataLemburan, int length, char *nip);

int getGajiPokok(Kategori kategori);

int main(){
  int n;
  printf("Berapa jumlah pegawai?");
  scanf("%d", &n);
  fflush(stdin);
  
  Pegawai * himpunanPegawai = inputPegawai(n);
  
  printf("\n\n========== Input Lemburan Pegawai ==========\n");
  DataLemburan * dataLemburan = inputLemburanPegawai(n);
  
  
  printf("\n\n========== Daftar Total Gaji Pegawai ==========\n");
  for (int i = 0; i < n; i++) {
    printf("\n=== Detail Gaji Pegawai #%d ===\n\n", i+1);
    printf("%20s: %s\n", "NIP" ,himpunanPegawai[i].nip);
    printf("%20s: %s\n", "Nama" ,himpunanPegawai[i].nama);
    printf("%20s: %s\n", "Alamat", himpunanPegawai[i].alamat);
    printf("%20s: %s\n", "Nomor HP", himpunanPegawai[i].no_hp);
    
    int gajiPokok = getGajiPokok(himpunanPegawai[i].kategori);
    
    printf("%20s: %d\n", "Gaji Pokok", gajiPokok);
    
    // Cari index yang pas untuk mendapatkan data lemburan yang match/sesuai dengan NIP
    int indexMatch = findIndexOfDataLemburanByNIP(&dataLemburan, n, himpunanPegawai[i].nip);
    
    // Persyaratan lembur ialah jam kerja > 8 jam.
    // Namun pada program diminta untuk menerima input berupa jml jam lembur
    // Oleh karena itu tidak perlu lagi mengecheck apakah lembur atau tidak.
    // Karena jika tidak lembur seharusnya jml jam lembur = 0. Sehingga bila jam lembur > 0 sudah dianggap lembur.
    // Tidak perlu lagi check apakah jam kerja > 8.
    int jmlJamLembur = indexMatch < 0 ? 0 : dataLemburan[indexMatch].jmlJamLembur;
    
    printf("%20s: %d\n", "Jumlah jam lembur", jmlJamLembur);
    
    float upahLembur = indexMatch < 0 ? 0 : (float ) (jmlJamLembur * TARIF_LEMBUR_PER_JAM);
    
    printf("%20s: %.2f\n", "Upah lembur", upahLembur);
    
    float totalGaji = (float ) gajiPokok + upahLembur;
    printf("%2s-----------------------------------\n", "");
    printf("%20s= Pokok + Lembur\n", "Total gaji ");
    printf("%20s= %d + %.2f\n", "", gajiPokok, upahLembur);
    printf("%20s= %.2f\n\n", "", totalGaji);
    
  }
  
  printf("\n\nKetikkan apapun untuk keluar...");
  getch();
  
  return 0;
}


void printPilihanKategori(){
  
  Kategori k;
  
  for (k = D1; k < KATEGORI_COUNT; k++) {
    switch (k) {
      case D1:
        printf("(%d) = \"%s\"", k, "Diploma 1");
        break;
      case D2:
        printf("(%d) = \"%s\"", k, "Diploma 2");
        break;
      case D3:
        printf("(%d) = \"%s\"", k, "Diploma 3");
        break;
      default:
        break;
    }
    
    if(k < 3) printf(" | ");
    
  }
  
  printf("\n");
  
}

int pilihKategoriPegawai(int pilihan){
  switch (pilihan) {
    case 1:
      return D1;
    case 2:
      return D2;
    case 3:
      return D3;
    default:
      return D1;
  }
}

Pegawai * inputPegawai(int howMany){
  
  Pegawai *listPegawai = malloc(sizeof(Pegawai) * howMany);
  
  char buffer[100];
  
  for (int i = 0; i < howMany; i++) {
    
    printf("\n\nInput data karyawan #%d\n", i+1);
    
    printf("Masukkan Nomor Induk Pegawai: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %30[^\n]", listPegawai[i].nip);
    
    printf("Masukkan nama: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %64[^\n]", listPegawai[i].nama);
    
    printf("Masukkan alamat: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %256[^\n]", listPegawai[i].alamat);
    
    printf("Masukkan nomor HP: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %40[^\n]", listPegawai[i].no_hp);
    
    
    int chosenCategory;
    
    printf("\n");
    printPilihanKategori();
    printf("Pilih kategori pegawai: ");
    scanf("%d", &chosenCategory);
    fflush(stdin);
    
    listPegawai[i].kategori = pilihKategoriPegawai(chosenCategory);
    
  }
  
  return listPegawai;
  
}

DataLemburan * inputLemburanPegawai(int howMany){
  
  DataLemburan * dataLemburan = malloc(sizeof (DataLemburan) * howMany);
  
  char buffer[100];
  
  for (int i = 0; i < howMany; i++) {
    printf("\nInput data karyawan #%d\n", i+1);
    
    printf("Masukkan Nomor Induk Pegawai: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, " %30[^\n]", dataLemburan[i].nip);
    
    printf("Berpa jam lembur kerja? ");
    scanf("%d", &dataLemburan[i].jmlJamLembur);
    fflush(stdin);
    
  }
  
  return dataLemburan;
}

// Searching for the match index
int findIndexOfDataLemburanByNIP(DataLemburan **ptrDataLemburan, int length, char *nip){
  
  for (int i = 0; i < length; i++) {
    int isMatch = strcmp((*ptrDataLemburan)[i].nip, nip);
    
    if(isMatch == 0) return i;
  }
  
  return -1;
  
}

int getGajiPokok(Kategori kategori){
  switch (kategori) {
    case D1:
      return GAJI_POKOK_D1;
    case D2:
      return GAJI_POKOK_D2;
    case D3:
      return GAJI_POKOK_D3;
    default:
      return 0;
  }
}