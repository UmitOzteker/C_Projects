#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file main.c
 * @description Çalışan ve birim yönetimi için tanımlamalar ve fonksiyonların uygulandığı dosya.
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
    newCalisan->calisanAdi = strdup(calisanAdi);       // Kopyalama
    newCalisan->calisanSoyadi = strdup(calisanSoyadi); // Kopyalama

    if (newCalisan->calisanAdi == NULL || newCalisan->calisanSoyadi == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        free(newCalisan->calisanAdi); // Önceki tahsisi serbest bırak
        free(newCalisan->calisanSoyadi);
        free(newCalisan);
        return NULL; // Hata durumunda NULL döndür
    }

    newCalisan->birimKodu = birimKodu;
    newCalisan->maas = maas;
    newCalisan->girisYili = girisYili;

    printf("Yeni calisan eklendi.\n");
    printf("-------------------------\n");
    return newCalisan;
}

void birimeCalisanEkle(Calisan *calisan, Birim *birim) {
    if (calisan == NULL || birim == NULL) {
        printf("Calisan veya birim bilgisi eksik.\n");
        return; // NULL kontrolü
    }

    // Çalışan için birim çalışanlar dizisini genişlet
    Calisan **yeniCalisanlar = realloc(birim->birimCalisanlar, sizeof(Calisan *) * (birim->calisanSayisi + 1));
    if (yeniCalisanlar == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return;
    }

    birim->birimCalisanlar = yeniCalisanlar; // Yeni diziyi atama
    birim->birimCalisanlar[birim->calisanSayisi] = calisan; // Yeni çalışanı ekle
    birim->calisanSayisi++; // Çalışan sayısını güncelle

    printf("Calisan %s %s, birim %s'e eklendi.\n", calisan->calisanAdi, calisan->calisanSoyadi, birim->birimAdi);
}


Calisan **calisanDiziOlustur(Calisan *calisan, Calisan ***calisanlar, int *calisanSayisi)
{
    // Çalışan sayısını artır
    (*calisanSayisi)++;

    // Yeni bellek bloğu tahsis et
    Calisan **yeniCalisanDizi = realloc(*calisanlar, sizeof(Calisan *) * (*calisanSayisi));

    if (yeniCalisanDizi == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        (*calisanSayisi)--; // Çalışan sayısını geri al
        return *calisanlar; // Mevcut dizi döndürülüyor.
    }

    *calisanlar = yeniCalisanDizi;
    yeniCalisanDizi[*calisanSayisi - 1] = calisan; // Yeni çalışanı ekle

    return *calisanlar; // Güncellenmiş dizi döndürülüyor.
}

Birim *birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan **birimCalisanlar, int calisanSayisi)
{
    Birim *newBirim = malloc(sizeof(Birim));
    if (newBirim == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        return NULL; // Hata durumunda NULL döndür
    }

    newBirim->birimAdi = strdup(birimAdi); // Kopyalama
    newBirim->birimKodu = birimKodu;
    newBirim->birimCalisanlar = malloc(sizeof(Calisan *) * calisanSayisi); // Düzeltildi

    if (newBirim->birimCalisanlar == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        free(newBirim->birimAdi); // Önceki tahsisi serbest bırak
        free(newBirim);           // Birimi serbest bırak
        return NULL;              // Hata durumunda NULL döndür
    }

    for (int i = 0; i < calisanSayisi; i++)
    {
        newBirim->birimCalisanlar[i] = birimCalisanlar[i]; // Çalışanları kopyala
    }

    newBirim->calisanSayisi = calisanSayisi; // Çalışan sayısını ekliyoruz
    printf("Yeni birim olusturuldu.\n");
    printf("-------------------------\n");
    return newBirim;
}

void birimYazdir(const Birim *birim)
{
    if (birim == NULL)
    {
        printf("Birim bilgileri mevcut degil.\n");
        return; // NULL kontrolü
    }

    printf("Birim Adi: %s\n", birim->birimAdi);
    printf("Birim Kodu: %d\n", birim->birimKodu);
    printf("Birimdeki Calisanlar:\n");

    for (int i = 0; i < birim->calisanSayisi; i++)
    {
        printf("  - %s %s, Maas: %.2f\n",
               birim->birimCalisanlar[i]->calisanAdi,
               birim->birimCalisanlar[i]->calisanSoyadi,
               birim->birimCalisanlar[i]->maas);
    }
    printf("-------------------------\n");
}

Birim **birimDiziOlustur(Birim *birim, Birim ***birimDizi, int *birimSayisi)
{
    // Yeni bellek bloğu tahsis etmek için geçici işaretçi oluştur
    Birim **yeniBirimDizi = realloc(*birimDizi, sizeof(Birim *) * (*birimSayisi + 1));

    if (yeniBirimDizi == NULL)
    {
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

void calisanYazdir(const Calisan *c)
{
    if (c == NULL)
    {
        printf("Calisan bilgileri mevcut degil.\n");
        return; // NULL kontrolü
    }

    printf("Calisan Adi: %s\n", c->calisanAdi);
    printf("Calisan Soyadi: %s\n", c->calisanSoyadi);
    printf("Birim Kodu: %d\n", c->birimKodu);
    printf("Maas: %.2f\n", c->maas);
    printf("Giris Yili: %d\n", c->girisYili);
    printf("-------------------------\n");
}

float birimCalisanMaasOrtalamaHesapla(const Birim *b)
{
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL)
    {
        printf("Birim geçersiz veya çalışan yok.\n");
        return 0; // Geçersiz durum için 0 döndür
    }

    float sum = 0;
    for (int i = 0; i < b->calisanSayisi; i++)
    {
        sum += b->birimCalisanlar[i]->maas; // Dereferans işlemi
    }

    float ortalamaMaas = sum / b->calisanSayisi; // Ortalama hesaplama
    return ortalamaMaas;
}

void birimCalisanOrtalamaUstuMaas(const Birim *b)
{
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL)
    {
        printf("Birim geçersiz veya çalışan yok.\n");
        return;
    }

    float ortalamaMaas = birimCalisanMaasOrtalamaHesapla(b);
    int ortalamaUstuCalisanSayisi = 0; // Ortalama üstü çalışan sayısını tutacak değişken

    // Ortalama üstü çalışan sayısını hesapla
    for (int i = 0; i < b->calisanSayisi; i++)
    {
        if (b->birimCalisanlar[i]->maas > ortalamaMaas)
        {
            ortalamaUstuCalisanSayisi++;
        }
    }

    // Ortalama üstü çalışanlar için bellek tahsisi
    Calisan **ortalamaUstuCalisanlar = (Calisan **)malloc(sizeof(Calisan *) * ortalamaUstuCalisanSayisi);
    if (ortalamaUstuCalisanlar == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        return;
    }

    // Ortalama üstü çalışanları yeni diziye kopyalayalım
    int j = 0;
    for (int i = 0; i < b->calisanSayisi; i++)
    {
        if (b->birimCalisanlar[i]->maas > ortalamaMaas)
        {
            ortalamaUstuCalisanlar[j] = b->birimCalisanlar[i]; // İşaretçiyi kopyala
            j++;
        }
    }

    // Ortalama üstü çalışanları yazdır
    for (int i = 0; i < ortalamaUstuCalisanSayisi; i++)
    {
        printf("Calisan Adi: %s, Maas: %.2f\n", ortalamaUstuCalisanlar[i]->calisanAdi, ortalamaUstuCalisanlar[i]->maas);
    }
    printf("-------------------------\n");

    // Bellek temizliği
    free(ortalamaUstuCalisanlar);
}

void enYuksekMaas(const Birim *b)
{
    if (b == NULL || b->calisanSayisi <= 0 || b->birimCalisanlar == NULL)
    {
        printf("Birim geçersiz veya çalışan yok.\n");
        return;
    }

    // İlk çalışanın maaşı ile başlat
    float enYuksek = b->birimCalisanlar[0]->maas;
    Calisan *enYuksekCalisan = b->birimCalisanlar[0]; // En yüksek maaş alan çalışanı tutmak için

    // Çalışanları kontrol et
    for (int i = 1; i < b->calisanSayisi; i++)
    {
        if (b->birimCalisanlar[i]->maas > enYuksek)
        {
            enYuksek = b->birimCalisanlar[i]->maas;
            enYuksekCalisan = b->birimCalisanlar[i]; // En yüksek maaş alan çalışanı güncelle
        }
    }

    // En yüksek maaş alan çalışanın bilgilerini yazdır
    printf("En Yuksek Maas Alan Calisan: %s %s, Maas: %.2f\n",
           enYuksekCalisan->calisanAdi,
           enYuksekCalisan->calisanSoyadi,
           enYuksek);

    printf("-------------------------\n");
}

void maasGuncelle(float yeniMaas, Calisan **calisanlar, int calisanSayisi)
{
    // Yıl bilgisi.
    int yil = 2024;
    // Tüm çalışanları gez.
    for (size_t i = 0; i < calisanSayisi; i++)
    {
        // Eğer i. çalışan 10 yıldan fazla çalışıyor ve maaşı da yeni maaştan az ise maaşını güncelle.
        if (yil - calisanlar[i]->girisYili > 10 && calisanlar[i]->maas < yeniMaas)
        {
            calisanlar[i]->maas = yeniMaas;
        }
    }
}

void DosyaYazdir(const char *calisanlarDosyaAd, const char *birimlerDosyaAd, Calisan **calisanlar, Birim **birimler, int calisanSayisi, int birimSayisi)
{
    printf("Dosya yazma islemi Baslatildi.\n");
    printf("-------------------------\n");

    FILE *calisanlarDosya = fopen(calisanlarDosyaAd, "w");
    FILE *birimDosya = fopen(birimlerDosyaAd, "w");

    if (birimDosya == NULL || calisanlarDosya == NULL)
    {
        printf("Dosyalar acilamadi.\n");
        if (calisanlarDosya != NULL)
            fclose(calisanlarDosya);
        if (birimDosya != NULL)
            fclose(birimDosya);
        return;
    }

    if (calisanSayisi > 0 && calisanlar != NULL)
    {
        // Çalışanları dosyaya yaz
        for (int i = 0; i < calisanSayisi; i++)
        {
            fprintf(calisanlarDosya, "%s;%s;%d;%.2f;%d\n",
                    calisanlar[i]->calisanAdi,
                    calisanlar[i]->calisanSoyadi,
                    calisanlar[i]->birimKodu,
                    calisanlar[i]->maas,
                    calisanlar[i]->girisYili);
        }
    }

    if (birimSayisi > 0 && birimler != NULL)
    {
        // Birimleri dosyaya yaz
        for (int i = 0; i < birimSayisi; i++)
        {
            fprintf(birimDosya, "%s;%d;%d\n",
                    birimler[i]->birimAdi,
                    birimler[i]->birimKodu,
                    birimler[i]->calisanSayisi);
        }
    }

    fclose(calisanlarDosya);
    fclose(birimDosya);
    printf("Dosya yazma islemi tamamlandi.\n");
    printf("-------------------------\n");
}

void DosyaOku(const char *calisanlarDosyaAdi, const char *birimlerDosyaAdi, Calisan ***calisanlar, Birim ***birimler, int *calisanSayisi, int *birimSayisi)
{
    printf("Dosyadan okuma islemi başlatiliyor...\n");
    printf("-------------------------\n");

    // Dosyaların işaretçileri (pointer).
    FILE *calisanlarDosya = fopen(calisanlarDosyaAdi, "r");
    FILE *birimlerDosya = fopen(birimlerDosyaAdi, "r");

    // Eğer dosyalar açılmazsa hata döndür.
    if (calisanlarDosya == NULL || birimlerDosya == NULL)
    {
        perror("Dosyalar açılamadı");
        return;
    }

    // Satırı saklamak için değişken.
    char satir[256];

    // Birimleri dosyadan oku.
    while (fgets(satir, sizeof(satir), birimlerDosya))
    {
        char birimAdi[256];
        unsigned short int birimKodu;

        // Satır formatı: BirimAdi;BirimKodu
        if (sscanf(satir, "%[^;];%hu", birimAdi, &birimKodu) == 2)
        {
            // Yeni birim oluştur ve birimler dizisine ekle.
            Birim *yeniBirim = birimOlustur(birimAdi, birimKodu, NULL, 0); // Çalışanlar henüz yok
            if (yeniBirim != NULL)
            {
                *birimler = birimDiziOlustur(yeniBirim, birimler, birimSayisi);
            }
        }
        else
        {
            printf("Satır formatı hatalı: %s\n", satir);
        }
    }

    // Birim dosyasını kapat
    fclose(birimlerDosya);

    // Çalışanları dosyadan oku.
    while (fgets(satir, sizeof(satir), calisanlarDosya))
    {
        char calisanAdi[256];
        char calisanSoyadi[256];
        unsigned short int birimKodu;
        float maas;
        int girisYili;

        // Satır formatı: CalisanAdi;CalisanSoyadi;BirimKodu;Maas;GirisYili
        if (sscanf(satir, "%[^;];%[^;];%hu;%f;%d", calisanAdi, calisanSoyadi, &birimKodu, &maas, &girisYili) == 5)
        {
            // Yeni çalışan oluştur ve çalışanlar dizisine ekle.
            Calisan *yeniCalisan = calisanOlustur(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);
            if (yeniCalisan != NULL)
            {
                *calisanlar = calisanDiziOlustur(yeniCalisan, calisanlar, calisanSayisi);
            }
        }
        else
        {
            printf("Satır formatı hatalı: %s\n", satir);
        }
    }

    for (int i = 0; i < *birimSayisi; i++)
    {
        for (int j = 0; j < *calisanSayisi; j++)
        {
            // Eğer i. birim ile j. çalışanın birim kodu eşleşiyorsa çalışanın referansını birime ekle
            if ((*birimler)[i]->birimKodu == (*calisanlar)[j]->birimKodu)
            {
                // Birimin çalışan sayısını artır ve yeni dizi tahsis et
                (*birimler)[i]->birimCalisanlar = realloc((*birimler)[i]->birimCalisanlar, sizeof(Calisan *) * ((*birimler)[i]->calisanSayisi + 1));

                // Çalışanı birime ekle
                (*birimler)[i]->birimCalisanlar[(*birimler)[i]->calisanSayisi] = (*calisanlar)[j];

                // Çalışan sayısını güncelle
                (*birimler)[i]->calisanSayisi++;
            }
        }
    }

    // Çalışan dosyasını kapat.
    fclose(calisanlarDosya);

    // Dosyadan okuma işleminin başarılı olduğunu bildir.
    printf("Dosyadan okuma islemi basarili!\n");
    printf("-------------------------------\n");
}
