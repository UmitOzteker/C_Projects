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
    if (newCalisan == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return NULL; // Hata durumunda NULL döndür
    }
    newCalisan->calisanAdi = strdup(calisanAdi);
    newCalisan->calisanSoyadi = strdup(calisanSoyadi);
    newCalisan->birimKodu = birimKodu;
    newCalisan->maas = maas;
    newCalisan->girisYili = girisYili;
    return newCalisan;
}

Calisan *calisanDiziOlustur(Calisan *calisanDizi, int *calisanSayisi, Calisan yeniCalisan)
{
    // Dizinin boyutunu artır
    *calisanSayisi += 1;

    // Yeni bellek bloğu tahsis etmek için geçici işaretçi oluştur
    Calisan *yeniDizi = realloc(calisanDizi, sizeof(Calisan) * (*calisanSayisi));

    // Eğer realloc başarısız olursa
    if (yeniDizi == NULL)
    {
        // Hata mesajı veya uygun işlem
        printf("Bellek tahsisi başarısız!\n");
        // Eski diziyi geri döndür (veya başka bir işlem yap)
        *calisanSayisi -= 1; // Boyutu geri al
        return calisanDizi;  // Eski diziyi geri döndür
    }

    // Yeni elemanı diziye ekle
    yeniDizi[*calisanSayisi - 1] = yeniCalisan;

    // Yeni diziyi geri döndür
    return yeniDizi;
}

Birim *birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan *birimCalisanlar, int calisanSayisi)
{
    Birim *newBirim = malloc(sizeof(Birim));
    if (newBirim == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return NULL; // Hata durumunda NULL döndür
    }
    newBirim->birimAdi = strdup(birimAdi);
    newBirim->birimKodu = birimKodu;
    newBirim->birimCalisanlar = malloc(sizeof(Calisan) * calisanSayisi);
    if (newBirim->birimCalisanlar == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        free(newBirim); // Önceki tahsisi serbest bırak
        return NULL; // Hata durumunda NULL döndür
    }
    for (int i = 0; i < calisanSayisi; i++)
    {
        newBirim->birimCalisanlar[i] = birimCalisanlar[i];
    }

    newBirim->calisanSayisi = calisanSayisi; // Çalışan sayısını ekliyoruz
    return newBirim;
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
    printf("Calisanlar:\n");
    
}
