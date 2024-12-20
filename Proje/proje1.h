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
    Calisan **birimCalisanlar;
    int calisanSayisi; // Birimdeki çalışan sayısını tutar.
} Birim;

// Fonksiyon Bildirimleri
Birim *birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan **birimCalisanlar, int calisanSayisi);
Calisan *calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
Calisan **calisanDiziOlustur(Calisan *calisan, Calisan ***calisanlar, int *calisanSayisi);
Birim **birimDiziOlustur(Birim *birim, Birim ***birimDizi, int *birimSayisi);
void calisanYazdir(Calisan *c);
void birimYazdir(Birim *birim);
void birimDiziYazdir(Birim *birim, Birim **birimDizi, int *birimSayisi);
float birimCalisanMaasOrtalamaHesapla(Birim *b);
void birimCalisanOrtalamaUstuMaas(Birim *b);
void enYuksekMaas(Birim *b);
void maasGuncelle(float yeniMaas, Calisan **calisanlar, int calisanSayisi);
void birimDosyaYazdir(Birim *birimDizi, int birimSayisi);
void calisanDosyaYazdir(Calisan *calisanDizi, int calisanSayisi);
void birimDosyaOku(Birim **birimDizi, int *birimSayisi, char *dosyaAdi);
void calisanDosyaOku(Calisan **calisanDizi, int *calisanSayisi, char *dosyaAdi);

#endif // PROJE1_H
