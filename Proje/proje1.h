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
void calisanYazdir(const Calisan *c);
void birimYazdir(const Birim *birim);
void birimDiziYazdir(Birim *birim, Birim **birimDizi, int *birimSayisi);
float birimCalisanMaasOrtalamaHesapla(const Birim *b);
void birimCalisanOrtalamaUstuMaas(const Birim *b);
void enYuksekMaas(const Birim *b);
void maasGuncelle(float yeniMaas, Calisan **calisanlar, int calisanSayisi);
void DosyaOku(const char *calisanlarDosyaAdi, const char *birimlerDosyaAdi, Calisan ***calisanlar, Birim ***birimler, int *calisanSayisi, int *birimSayisi);
void DosyaYazdir(const char *calisanlarDosyaAdi, const char *birimlerDosyaAdi, Calisan **calisanlar, Birim **birimler, int calisanSayisi, int birimSayisi);
#endif // PROJE1_H
