#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file main.c
 * @description Programınızın açıklaması ne yaptığına dair.
 * @assignment 1
 * @date 11.12.2024
 * @author Ümit Özteker | umit.ozteker@stu.fsm.edu.tr
 */

Calisan *calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili)
{
    Calisan *newCalisan = malloc(sizeof(Calisan));
    if (newCalisan == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        return NULL; // Hata durumunda NULL döndür
    }
    newCalisan->calisanAdi = calisanAdi;
    newCalisan->calisanSoyadi = calisanSoyadi;
    newCalisan->birimKodu = birimKodu;
    newCalisan->maas = maas;
    newCalisan->girisYili = girisYili;
    return newCalisan;
}

Calisan *calisanDiziOlustur(Calisan *calisanDizi, int *calisanSayisi, Calisan *yeniCalisan) {
    (*calisanSayisi)++;
    Calisan *yeniCalisanDizi = realloc(calisanDizi, sizeof(Calisan) * (*calisanSayisi));

    if (yeniCalisanDizi == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        (*calisanSayisi)--;
        return calisanDizi;
    }

    yeniCalisanDizi[*calisanSayisi - 1] = *yeniCalisan; // Pointer'ın gösterdiği değeri kopyala
    return yeniCalisanDizi;
}

Birim *birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan *birimCalisanlar, int calisanSayisi)
{
    Birim *newBirim = malloc(sizeof(Birim));
    if (newBirim == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        return NULL; // Hata durumunda NULL döndür
    }
    newBirim->birimAdi = birimAdi;
    newBirim->birimKodu = birimKodu;
    newBirim->birimCalisanlar = malloc(sizeof(Calisan) * calisanSayisi);
    if (newBirim->birimCalisanlar == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        free(newBirim); // Önceki tahsisi serbest bırak
        return NULL;    // Hata durumunda NULL döndür
    }
    for (int i = 0; i < calisanSayisi; i++)
    {
        newBirim->birimCalisanlar[i] = birimCalisanlar[i];
    }

    newBirim->calisanSayisi = calisanSayisi; // Çalışan sayısını ekliyoruz
    return newBirim;
}

Birim *birimDiziOlustur(Calisan *birimDizi, int *birimSayisi, Birim yeniBirim)
{
    *birimSayisi = 1;
    // Yeni bellek bloğu tahsis etmek için geçici işaretçi oluştur
    Birim *yeniBirimDizi = realloc(birimDizi, sizeof(Birim) * (*birimSayisi));

    if (yeniBirimDizi == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        return birimDizi; // Eski diziyi geri döndür
    }

    // Yeni elemanı diziye kopyala (tüm üyeleri için kopya al)
    yeniBirimDizi[*birimSayisi - 1] = yeniBirim; // Yeni elemanı sona ekle
    *birimSayisi += 1;

    return yeniBirimDizi;
}

void calisanYazdir(Calisan *c)
{
    printf("Calisan Adi: %s\n", c->calisanAdi);
    printf("Calisan Soyadi: %s\n", c->calisanSoyadi);
    printf("Birim Kodu: %d\n", c->birimKodu);
    printf("Maas: %.2f\n", c->maas);
    printf("Giris Yili: %d\n", c->girisYili);
}

void birimYazdir(Birim *b)
{
    printf("Birim Adi: %s\n", b->birimAdi);
    printf("Birim Kodu: %d\n", b->birimKodu);
}

float birimCalisanMaasOrtalamaHesapla(Birim *b)
{
    float sum = 0;
    float ortalamaMaas = 0;
    for (int i = 0; i < b->calisanSayisi; i++)
    {
        sum += b->birimCalisanlar[i].maas;
    }
    ortalamaMaas = sum / b->calisanSayisi;
    return ortalamaMaas;
}

void *birimCalisanOrtalamaUstuMaas(Birim *b)
{
    float ortalamaMaas = birimCalisanMaasOrtalamaHesapla(b);
    int ortalamaUstuCalisanSayisi = 0; // Ortalama üstü çalışan sayısını tutacak değişken

    for (int i = 0; i < b->calisanSayisi; i++)
    {
        if (b->birimCalisanlar[i].maas > ortalamaMaas)
        {
            ortalamaUstuCalisanSayisi++;
        }
    }

    Calisan *ortalamaUstuCalisanlar = (Calisan *)malloc(sizeof(Calisan) * ortalamaUstuCalisanSayisi);

    // Ortalama üstü çalışanları yeni diziye kopyalayalım
    int j = 0;
    for (int i = 0; i < b->calisanSayisi; i++)
    {
        if (b->birimCalisanlar[i].maas > ortalamaMaas)
        {
            ortalamaUstuCalisanlar[j] = b->birimCalisanlar[i];
            j++;
        }
    }

    for (int i = 0; i < ortalamaUstuCalisanSayisi; i++)
    {
        printf("Calisan Adi: %s, Maas: %.2f\n", ortalamaUstuCalisanlar[i].calisanAdi, ortalamaUstuCalisanlar[i].maas);
    }

    free(ortalamaUstuCalisanlar);
}

void enYuksekMaas(Birim *b) {
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL) {
        printf("Birim geçersiz veya çalışan yok.\n");
        return;
    }
    float enyuksek = b->birimCalisanlar[0].maas; // İlk çalışanın maaşı ile başlat
    for (int i = 1; i < b->calisanSayisi; i++) {
        if (b->birimCalisanlar[i].maas > enyuksek) {
            enyuksek = b->birimCalisanlar[i].maas;
        }
    }
    printf("En Yuksek Maas Alan Calisan: %.2f\n", enyuksek); // \n eklendi ve format düzeltildi
}

#include <string.h> // strcmp için eklendi

void maasGuncelle(float yeniMaasDegeri, Birim *b) {
    if (b == NULL || b->birimCalisanlar == NULL || b->calisanSayisi <= 0) {
        return;
    }

    for (int i = 0; i < b->calisanSayisi; i++) {
        int girisYili = b->birimCalisanlar[i].girisYili;
        int sirkettekiYil = 2024 - girisYili;

        if (sirkettekiYil > 10 && b->birimCalisanlar[i].maas < yeniMaasDegeri) {
            b->birimCalisanlar[i].maas = yeniMaasDegeri;
        }
    }
}
