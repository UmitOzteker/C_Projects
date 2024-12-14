#ifndef PROJE1_H
#define PROJE1_H

/**
 * @file proje1.h
 * @description Çalışan ve birim yönetimi için tanımlamalar ve fonksiyonlar.
 * @assignment 1
 * @date 11.12.2024
 * @author Ümit
 */

// Veri Yapıları
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
    Calisan *birimCalisanlar;
    int calisanSayisi; // Birimdeki çalışan sayısını tutar.
} Birim;

// Fonksiyon Bildirimleri
Birim *birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan *birimCalisanlar, int calisanSayisi);
Calisan *calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
Calisan *calisanDiziOlustur(Calisan *calisanDizi, int *calisanSayisi, Calisan yeniCalisan);
void birimDiziOlustur(Calisan *calisanDizi, int *calisanSayisi, Calisan yeniCalisan);
void calisanYazdir(Calisan *c);
void birimYazdir(Birim *b);
void birimDiziYazdir(Birim *birimDizi, int birimSayisi);
float birimCalisanMaasOrtalamaHesapla(Birim b);
void birimCalisanOrtalamaUstuMaas(Birim b);
void enYuksekMaas(Birim b);
void yeniMaas(Calisan *calisanDizi, int calisanSayisi, float yeniMaasDegeri);
void birimDosyaYazdir(Birim *birimDizi, int birimSayisi);
void calisanDosyaYazdir(Calisan *calisanDizi, int calisanSayisi);
void birimDosyaOku(Birim **birimDizi, int *birimSayisi, char *dosyaAdi);
void calisanDosyaOku(Calisan **calisanDizi, int *calisanSayisi, char *dosyaAdi);

#endif // PROJE1_H
