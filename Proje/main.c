#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Calisan **calisanlar = NULL;
    Birim **birimler = NULL;
    int calisanSayisi = 0;
    int birimSayisi = 0;

    // Dosyadan çalışan ve birim bilgilerini oku
    DosyaOku("calisanlar.txt", "birimler.txt", &calisanlar, &birimler, &calisanSayisi, &birimSayisi);

    // Yeni çalışanlar oluştur
    Calisan *yeniCalisan1 = calisanOlustur("Enes", "Erden", 203, 5000.0, 2010);
    Calisan *yeniCalisan2 = calisanOlustur("Ekrem", "Bas", 203, 4500.0, 2012);

    // Yeni çalışanları diziye ekle
    calisanlar = calisanDiziOlustur(yeniCalisan1, &calisanlar, &calisanSayisi);
    calisanlar = calisanDiziOlustur(yeniCalisan2, &calisanlar, &calisanSayisi);

    // Yeni birim oluştur
    Calisan *birimCalisanlar[] = {yeniCalisan1, yeniCalisan2}; // Birimdeki yeni çalışanlar
    Birim *yeniBirim = birimOlustur("Yeni Birim", 203, birimCalisanlar, 2);

    // Yeni birimi diziye ekle
    birimler = birimDiziOlustur(yeniBirim, &birimler, &birimSayisi);

    printf("\n=== CALISANLAR ===\n");
    for (int i = 0; i < calisanSayisi; i++) {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    printf("\n=== BIRIMLER ===\n");
    for (int i = 0; i < birimSayisi; i++) {
        birimYazdir(birimler[i]);
        printf("\n");
    }

    // Bir calisanin maasini guncelleyin (ornek kullanim)
    printf("\n=== Maas Guncelleme ===\n");
    float yeniMaas = 12000;
    maasGuncelle(yeniMaas, calisanlar, calisanSayisi);

    // Guncellenmis calisan maaslarini yazdirin
    printf("\n=== Guncellenmis Calisan Maaslari ===\n");
    for (int i = 0; i < calisanSayisi; i++) {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    // Her birim icin maas ortalamasini hesaplayin ve yazdirin
    printf("\n=== Maas Ortalamalari ===\n");
    for (int i = 0; i < birimSayisi; i++) {
        float ortalamaMaas = birimCalisanMaasOrtalamaHesapla(birimler[i]);
        printf("%s Birimi Maas Ortalamasi: %.2f\n", birimler[i]->birimAdi, ortalamaMaas);
    }

    // Ortalama maasin ustunde maas alan calisanlari yazdirin
    printf("\n=== Ortalama Ustu Maas Alanlar ===\n");
    for (int i = 0; i < birimSayisi; i++) {
        printf("\n%s Birimi:\n", birimler[i]->birimAdi);
        birimCalisanOrtalamaUstuMaas(birimler[i]);
    }

    // En yuksek maas alan calisani bulun ve yazdirin
    printf("\n=== En Yuksek Maas Alan Calisanlar ===\n");
    for (int i = 0; i < birimSayisi; i++) {
        printf("\n%s Birimi:\n", birimler[i]->birimAdi);
        enYuksekMaas(birimler[i]);
    }

    // Dosyaya yaz
    DosyaYazdir("calisanlar.txt", "birimler.txt", calisanlar, birimler, calisanSayisi, birimSayisi);

    // Yeni çalışanları yazdır
    printf("Yeni Calisanlar:\n");
    for (int i = 0; i < calisanSayisi; i++) {
        calisanYazdir(calisanlar[i]);
    }

    // Yeni birimleri yazdır
    printf("\nYeni Birimler:\n");
    for (int i = 0; i < birimSayisi; i++) {
        birimYazdir(birimler[i]);
    }

    // Bellek temizliği
    for (int i = 0; i < calisanSayisi; i++) {
        free(calisanlar[i]);
    }
    free(calisanlar);

    for (int i = 0; i < birimSayisi; i++) {
        free(birimler[i]->birimCalisanlar);
        free(birimler[i]);
    }
    free(birimler);

    return 0;
}