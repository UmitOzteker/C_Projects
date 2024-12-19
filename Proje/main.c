#include <stdio.h>
#include "proje1.h"
#include <stdlib.h>

/**
 * @file main.c
 * @description Programınızın açıklaması ne yaptığına dair.
 * @assignment 1
 * @date 11.12.2024
 * @author Ümit Özteker | umit.ozteker@stu.fsm.edu.tr
 */

int main()
{
    Calisan *calisan1 = calisanOlustur("Ahmet", "Yilmaz", 101, 7500.50, 2010);
    Calisan *calisan2 = calisanOlustur("Mehmet", "Demir", 101, 8200.75, 2015);
    Calisan *calisan3 = calisanOlustur("Ayse", "Kaya", 101, 9200.00, 2008);

    if (calisan1 == NULL || calisan2 == NULL || calisan3 == NULL)
    {
        printf("Bellek tahsisi basarisiz. Program sonlandiriliyor.\n");
        return 1;
    }

    // 2. Çalışan dizisi oluşturma
    int calisanSayisi = 0;
    Calisan *calisanDizisi = NULL;
    calisanDizisi = calisanDiziOlustur(calisanDizisi, &calisanSayisi, calisan1);
    calisanDizisi = calisanDiziOlustur(calisanDizisi, &calisanSayisi, calisan2);
    calisanDizisi = calisanDiziOlustur(calisanDizisi, &calisanSayisi, calisan3);

    // 3. Yeni bir birim oluşturma
    Birim *birim1 = birimOlustur("Muhasebe", 101, calisanDizisi, calisanSayisi);
    if (birim1 == NULL)
    {
        printf("Birim olusturulamadi. Program sonlandiriliyor.\n");
        free(calisanDizisi);
        return 1;
    }

    // 4. Birim ve çalışan bilgilerini yazdırma
    printf("--- Birim Bilgileri ---\n");
    birimYazdir(birim1);
    printf("\n--- Birim Calisanlari ---\n");
    for (int i = 0; i < birim1->calisanSayisi; i++)
    {
        calisanYazdir(&birim1->birimCalisanlar[i]);
        printf("\n");
    }

    // 5. Maaş ortalamasını hesaplama
    float ortalamaMaas = birimCalisanMaasOrtalamaHesapla(birim1);
    printf("Birimdeki Ortalama Maas: %.2f\n", ortalamaMaas);

    // 6. Ortalama üstü maaş alan çalışanları listeleme
    printf("\n--- Ortalama Ustu Maas Alan Calisanlar ---\n");
    birimCalisanOrtalamaUstuMaas(birim1);

    // 7. En yüksek maaşı bulma
    printf("\n--- Birimdeki En Yuksek Maas ---\n");
    enYuksekMaas(birim1);

    // 8. Maaş güncelleme testi
    printf("\n--- Maas Guncelleme Testi ---\n");
    maasGuncelle(10000.00, birim1);
    printf("Guncellenmis Maaslar:\n");
    for (int i = 0; i < birim1->calisanSayisi; i++)
    {
        calisanYazdir(&birim1->birimCalisanlar[i]);
        printf("\n");
    }

    // Bellek temizleme
    free(birim1->birimCalisanlar);
    free(birim1);
    free(calisanDizisi);
    free(calisan1);
    free(calisan2);
    free(calisan3);

    return 0;
}
