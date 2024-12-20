#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Calisan **calisanlar = NULL;
    int calisanSayisi = 0;

    // Calisanlari olustur
    Calisan *c1 = calisanOlustur("Ahmet", "Yilmaz", 101, 45000.0f, 2010);
    Calisan *c2 = calisanOlustur("Ayse", "Demir", 102, 60000.0f, 2012);
    Calisan *c3 = calisanOlustur("Mehmet", "Kaya", 101, 35000.0f, 2015);
    Calisan *c4 = calisanOlustur("Fatma", "Can", 103, 70000.0f, 2005);
    Calisan *c5 = calisanOlustur("Ali", "Ozturk", 102, 55000.0f, 2013);

        if (!c1 || !c2 || !c3 || !c4 || !c5) {
        printf("Bellek tahsisi hatasi!\n");
        return 1;
    }

    // Calisanlari diziye ekle
    calisanlar = calisanDiziOlustur(c1, &calisanlar, &calisanSayisi);
    calisanlar = calisanDiziOlustur(c2, &calisanlar, &calisanSayisi);
    calisanlar = calisanDiziOlustur(c3, &calisanlar, &calisanSayisi);
    calisanlar = calisanDiziOlustur(c4, &calisanlar, &calisanSayisi);
    calisanlar = calisanDiziOlustur(c5, &calisanlar, &calisanSayisi);

    Birim **birimler = NULL;
    int birimSayisi = 0;

    // Birimlere calisan eklemek icin gecici diziler
    Calisan *birim1Calisanlar[] = {c1, c3};
    Calisan *birim2Calisanlar[] = {c2, c5};
    Calisan *birim3Calisanlar[] = {c4};

    // Birimleri olustur
    Birim b1 = {"Yazilim", 101,birim1Calisanlar, 2};
    Birim b2 = {"Pazarlama", 102, birim2Calisanlar, 2};
    Birim b3 = {"Finans", 103, birim3Calisanlar, 1};


    // Birimleri diziye ekle
    birimler = birimDiziOlustur(&b1, &birimler, &birimSayisi);
    birimler = birimDiziOlustur(&b2, &birimler, &birimSayisi);
    birimler = birimDiziOlustur(&b3, &birimler, &birimSayisi);

    // Calisanlari yazdir
    printf("Calisanlar:\n");
    for (int i = 0; i < calisanSayisi; i++) {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    // Birimleri yazdir ve diger fonksiyonlari cagir
    printf("\nBirimler:\n");
    for (int i = 0; i < birimSayisi; i++) {
        birimYazdir(birimler[i]);
        printf("Birim Maas Ortalamasi: %.2f\n", birimCalisanMaasOrtalamaHesapla(birimler[i]));
        printf("Ortalama Ustu Maas Alan Calisanlar:\n");
        birimCalisanOrtalamaUstuMaas(birimler[i]);
        enYuksekMaas(birimler[i]);
        printf("\n");
    }

    // Maas guncellemesini test et
    printf("\nMaas Guncellemesi Oncesi Calisanlar:\n");
    for (int i = 0; i < calisanSayisi; i++) {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    maasGuncelle(100000.0f, calisanlar, calisanSayisi);

    printf("\nMaas Guncellemesi Sonrasi Calisanlar:\n");
    for (int i = 0; i < calisanSayisi; i++) {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    // Bellek temizleme (cok onemli!)
    for (int i = 0; i < calisanSayisi; i++) {
        free(calisanlar[i]->calisanAdi);
        free(calisanlar[i]->calisanSoyadi);
        free(calisanlar[i]);
    }
    free(calisanlar);

    for (int i = 0; i < birimSayisi; i++) {
        //birimOlustur fonksiyonunda birimAdi için malloc kullanılmadığı için free gereksiz
        //birimOlustur fonksiyonu düzeltilirse bu kısım değişebilir.
        free(birimler[i]->birimCalisanlar);
        free(birimler[i]);
    }
    free(birimler);

    return 0;
}