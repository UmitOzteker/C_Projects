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
    
    // Bellek tahsisi ve kopyalama
    newCalisan->calisanAdi = calisanAdi;
    newCalisan->calisanSoyadi = calisanSoyadi;
    
    if (newCalisan->calisanAdi == NULL || newCalisan->calisanSoyadi == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        free(newCalisan->calisanAdi); // Önceki tahsisi serbest bırak
        free(newCalisan->calisanSoyadi);
        free(newCalisan);
        return NULL; // Hata durumunda NULL döndür
    }

    newCalisan->birimKodu = birimKodu;
    newCalisan->maas = maas;
    newCalisan->girisYili = girisYili;
    return newCalisan;
}

Calisan **calisanDiziOlustur(Calisan *calisan, Calisan ***calisanlar, int *calisanSayisi) {
    // Çalışan sayısını artır
    (*calisanSayisi)++;

    // Yeni bellek bloğu tahsis et
    Calisan **yeniCalisanDizi = realloc(*calisanlar, sizeof(Calisan*) * (*calisanSayisi));

    if (yeniCalisanDizi == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        (*calisanSayisi)--; // Çalışan sayısını geri al
        return *calisanlar; // Mevcut dizi döndürülüyor.
    }

    *calisanlar = yeniCalisanDizi;
    yeniCalisanDizi[*calisanSayisi - 1] = calisan; // Yeni çalışanı ekle

    return *calisanlar; // Güncellenmiş dizi döndürülüyor.
}


Birim *birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan **birimCalisanlar, int calisanSayisi) {
    Birim *newBirim = malloc(sizeof(Birim));
    if (newBirim == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return NULL; // Hata durumunda NULL döndür
    }
    
    newBirim->birimAdi = birimAdi; // Birim adını kopyala
    newBirim->birimKodu = birimKodu;
    newBirim->birimCalisanlar = malloc(sizeof(Calisan) * calisanSayisi);
    
    if (newBirim->birimCalisanlar == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        free(newBirim->birimAdi); // Önceki tahsisi serbest bırak
        free(newBirim); // Birimi serbest bırak
        return NULL; // Hata durumunda NULL döndür
    }

    for (int i = 0; i < calisanSayisi; i++) {
        newBirim->birimCalisanlar[i] = birimCalisanlar[i]; // Çalışanları kopyala
    }

    newBirim->calisanSayisi = calisanSayisi; // Çalışan sayısını ekliyoruz
    return newBirim;
}

void birimYazdir(Birim *birim) {
    if (birim == NULL) {
        printf("Birim bilgileri mevcut degil.\n");
        return; // NULL kontrolü
    }
    
    printf("Birim Adi: %s\n", birim->birimAdi);
    printf("Birim Kodu: %d\n", birim->birimKodu);
    printf("Birimdeki Calisanlar:\n");
    
    for (int i = 0; i < birim->calisanSayisi; i++) {
        // Dereferans işlemi ile çalışan bilgilerine erişim
        printf("  - %s %s, Maas: %.2f\n", 
               birim->birimCalisanlar[i]->calisanAdi, 
               birim->birimCalisanlar[i]->calisanSoyadi, 
               birim->birimCalisanlar[i]->maas);
    }
}

Birim **birimDiziOlustur(Birim *birim, Birim ***birimDizi, int *birimSayisi) {
    // Yeni bellek bloğu tahsis etmek için geçici işaretçi oluştur
    Birim **yeniBirimDizi = realloc(*birimDizi, sizeof(Birim*) * (*birimSayisi + 1));

    if (yeniBirimDizi == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return *birimDizi; // Eski diziyi geri döndür (önemli!)
    }

    // Yeni elemanı diziye ekle (memcpy kullanmak daha güvenli)
    yeniBirimDizi[*birimSayisi] = birim;

    // Birim sayısını artır
    (*birimSayisi)++;

    // Güncellenmiş dizi işaretçisini geri döndür
    return yeniBirimDizi;
}


void calisanYazdir(Calisan *c)
{
    if (c == NULL) {
        printf("Calisan bilgileri mevcut degil.\n");
        return; // NULL kontrolü
    }
    
    printf("Calisan Adi: %s\n", c->calisanAdi);
    printf("Calisan Soyadi: %s\n", c->calisanSoyadi);
    printf("Birim Kodu: %d\n", c->birimKodu);
    printf("Maas: %.2f\n", c->maas);
    printf("Giris Yili: %d\n", c->girisYili);
}

float birimCalisanMaasOrtalamaHesapla(Birim *b) {
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL) {
        printf("Birim geçersiz veya çalışan yok.\n");
        return 0; // Geçersiz durum için 0 döndür
    }

    float sum = 0;
    for (int i = 0; i < b->calisanSayisi; i++) {
        sum += b->birimCalisanlar[i]->maas; // Dereferans işlemi
    }

    float ortalamaMaas = sum / b->calisanSayisi; // Ortalama hesaplama
    return ortalamaMaas;
}

void birimCalisanOrtalamaUstuMaas(Birim *b) {
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL) {
        printf("Birim geçersiz veya çalışan yok.\n");
        return;
    }

    float ortalamaMaas = birimCalisanMaasOrtalamaHesapla(b);
    int ortalamaUstuCalisanSayisi = 0; // Ortalama üstü çalışan sayısını tutacak değişken

    // Ortalama üstü çalışan sayısını hesapla
    for (int i = 0; i < b->calisanSayisi; i++) {
        if (b->birimCalisanlar[i]->maas > ortalamaMaas) {
            ortalamaUstuCalisanSayisi++;
        }
    }

    // Ortalama üstü çalışanlar için bellek tahsisi
    Calisan **ortalamaUstuCalisanlar = (Calisan **)malloc(sizeof(Calisan *) * ortalamaUstuCalisanSayisi);
    if (ortalamaUstuCalisanlar == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return;
    }

    // Ortalama üstü çalışanları yeni diziye kopyalayalım
    int j = 0;
    for (int i = 0; i < b->calisanSayisi; i++) {
        if (b->birimCalisanlar[i]->maas > ortalamaMaas) {
            ortalamaUstuCalisanlar[j] = b->birimCalisanlar[i]; // İşaretçiyi kopyala
            j++;
        }
    }

    // Ortalama üstü çalışanları yazdır
    for (int i = 0; i < ortalamaUstuCalisanSayisi; i++) {
        printf("Calisan Adi: %s, Maas: %.2f\n", ortalamaUstuCalisanlar[i]->calisanAdi, ortalamaUstuCalisanlar[i]->maas);
    }

    // Bellek temizliği
    free(ortalamaUstuCalisanlar);
}

void enYuksekMaas(Birim *b) {
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL) {
        printf("Birim geçersiz veya çalışan yok.\n");
        return;
    }

    // İlk çalışanın maaşı ile başlat
    float enYuksek = b->birimCalisanlar[0]->maas; 
    Calisan *enYuksekCalisan = b->birimCalisanlar[0]; // En yüksek maaş alan çalışanı tutmak için

    // Çalışanları kontrol et
    for (int i = 1; i < b->calisanSayisi; i++) {
        if (b->birimCalisanlar[i]->maas > enYuksek) {
            enYuksek = b->birimCalisanlar[i]->maas;
            enYuksekCalisan = b->birimCalisanlar[i]; // En yüksek maaş alan çalışanı güncelle
        }
    }

    // En yüksek maaş alan çalışanın bilgilerini yazdır
    printf("En Yuksek Maas Alan Calisan: %s %s, Maas: %.2f\n", 
           enYuksekCalisan->calisanAdi, 
           enYuksekCalisan->calisanSoyadi, 
           enYuksek);
}

void maasGuncelle(float yeniMaas, Calisan **calisanlar, int calisanSayisi) {
    // Yıl bilgisi.
    int yil = 2024;
    // Tüm çalışanları gez.
    for (size_t i = 0; i < calisanSayisi; i++) {
        // Eğer i. çalışan 10 yıldan fazla çalışıyor ve maaşı da yeni maaştan az ise maaşını güncelle.
        if (yil - calisanlar[i]->girisYili > 10 && calisanlar[i]->maas < yeniMaas) {
            calisanlar[i]->maas = yeniMaas;
        }
    }
}
