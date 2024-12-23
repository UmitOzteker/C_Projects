
/**
 * @file main.c
 * @description Projede kullanılan fonksiyonların test edildiği c dosyası
 * @assignment 1
 * @date 11.12.2024
 * @author Ümit Özteker | umit.ozteker@stu.fsm.edu.tr
 */

#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Calisan **calisanlar = NULL;
    Birim **birimler = NULL;
    int calisanSayisi = 0;
    int birimSayisi = 0;

    // Command Line Parameters.
    if (argc < 3)
    {
        printf("%s <calisanlar_dosyasi> <birimler_dosyasi>\n", argv[0]);
        return 1;
    }

    // Dosyadan çalışan ve birim bilgilerini oku
    DosyaOku(argv[1], argv[2], &calisanlar, &birimler, &calisanSayisi, &birimSayisi);

    printf("\n=== CALISANLAR ===\n");
    for (int i = 0; i < calisanSayisi; i++)
    {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    printf("\n=== BIRIMLER ===\n");
    for (int i = 0; i < birimSayisi; i++)
    {
        birimYazdir(birimler[i]);
        printf("\n");
    }

    // Bir calisanin maasini guncelleyin
    printf("\n=== Maas Guncelleme ===\n");
    float yeniMaas = 17000;
    maasGuncelle(yeniMaas, calisanlar, calisanSayisi);

    // Guncellenmis calisan maaslarini yazdirin
    printf("\n=== Guncellenmis Calisan Maaslari ===\n");
    for (int i = 0; i < calisanSayisi; i++)
    {
        calisanYazdir(calisanlar[i]);
        printf("\n");
    }

    // Her birim icin maas ortalamasini hesaplayin ve yazdirin
    printf("\n=== Maas Ortalamalari ===\n");
    for (int i = 0; i < birimSayisi; i++)
    {
        float ortalamaMaas = birimCalisanMaasOrtalamaHesapla(birimler[i]);
        printf("%s Birimi Maas Ortalamasi: %.2f\n", birimler[i]->birimAdi, ortalamaMaas);
    }

    // Ortalama maasin ustunde maas alan calisanlari yazdirin
    printf("\n=== Ortalama Ustu Maas Alanlar ===\n");
    for (int i = 0; i < birimSayisi; i++)
    {
        printf("\n%s Birimi:\n", birimler[i]->birimAdi);
        birimCalisanOrtalamaUstuMaas(birimler[i]);
    }

    // En yuksek maas alan calisani bulun ve yazdirin
    printf("\n=== En Yuksek Maas Alan Calisanlar ===\n");
    for (int i = 0; i < birimSayisi; i++)
    {
        printf("\n%s Birimi:\n", birimler[i]->birimAdi);
        enYuksekMaas(birimler[i]);
    }

    // Dosyaya yaz
    DosyaYazdir(argv[1], argv[2], calisanlar, birimler, calisanSayisi, birimSayisi);

    // Yeni çalışanları yazdır
    printf("Yeni Calisanlar:\n");
    for (int i = 0; i < calisanSayisi; i++)
    {
        calisanYazdir(calisanlar[i]);
    }
    
    // Yeni birimleri yazdır
    printf("\nYeni Birimler:\n");
    for (int i = 0; i < birimSayisi; i++)
    {
        birimYazdir(birimler[i]);
    }
    
    // Bellek temizliği
    for (int i = 0; i < calisanSayisi; i++)
    {
        free(calisanlar[i]);
    }
    free(calisanlar);

    for (int i = 0; i < birimSayisi; i++)
    {
        free(birimler[i]->birimCalisanlar);
        free(birimler[i]);
    }
    free(birimler);

    return 0;
}