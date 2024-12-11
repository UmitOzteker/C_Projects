#ifndef PROJE1_H
#define PROJE1_H

/**
* @file main.c
* @description Programınızın açıklaması ne yaptığına dair.
* @assignment 1
* @date 11.12.2024  
* @author Ümit Özteker | umit.ozteker@stu.fsm.edu.tr
*/

typedef struct
{
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct
{
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan birimCalisanlar;
} Birim;


Birim birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan *birimCalisanlar, int calisanSayisi);
Calisan calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
void diziyeEkle(Calisan *calisanDizi, int *calisanSayisi, Birim *birimDizi, int *birimSayisi);
void calisanYazdir(Calisan c);
void birimYazdir(Birim b);
void birimDiziYazdir(Birim *birimDizi, int birimSayisi);
float birimCalisanMaasOrtalamaHesapla(Birim b);
void birimCalisanOrtalamaUstuMaas(Birim b);
void enYuksekMaas(Birim b);
void yeniMaas(Calisan *calisanDizi, int calisanSayisi, float yeniMaasDegeri);
void dosyaYazdir(Birim *birimDizi, int birimSayisi, char *dosyaAdi);
void dosyaOku(Birim **birimDizi, int *birimSayisi, char *dosyaAdi);


#endif
