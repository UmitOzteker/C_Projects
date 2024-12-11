#include "proje1.h"
#include <stdio.h>

/**
 * @file main.c
 * @description Programınızın açıklaması ne yaptığına dair.
 * @assignment 1
 * @date 11.12.2024
 * @author Ümit Özteker | umit.ozteker@stu.fsm.edu.tr
 */

Calisan calisanOlustur(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili)
{
    Calisan newCalisan;
    newCalisan.calisanAdi = calisanAdi;
    newCalisan.calisanSoyadi = calisanSoyadi;
    newCalisan.birimKodu = birimKodu;
    newCalisan.maas = maas;
    newCalisan.girisYili = girisYili;
    return newCalisan;
}

Birim birimOlustur(char *birimAdi, unsigned short int birimKodu, Calisan *birimCalisanlar)
{
    Birim newBirim;
    newBirim.birimAdi = birimAdi;
    newBirim.birimKodu = birimKodu;
    newBirim.birimCalisanlar = *birimCalisanlar;
    return newBirim;
}

void diziyeEkle(Calisan *calisanDizi, int *calisanSayisi, Birim *birimDizi, int *birimSayisi){
    

}
