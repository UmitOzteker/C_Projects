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
    int calisanDiziBoyutu = 0;
    int birimDiziBoyutu = 0; // Başlangıçta dizinin boyutu sıfır
    Calisan *calisanlar = NULL;
    Calisan calisan1 = *calisanOlustur("Ali", "Veli", 101, 5000.0, 2015);
    calisanlar = calisanDiziOlustur(calisanlar, &calisanDiziBoyutu, calisan1);
    Calisan calisan2 = *calisanOlustur("Ahmet", "Ok", 102, 10000.0, 2013);
    calisanlar = calisanDiziOlustur(calisanlar, &calisanDiziBoyutu, calisan2);
    Birim *birimler = NULL;
    Birim birim1 = *birimOlustur("IT", 132, calisanlar, 2);
    birimler = birimDiziOlustur(birimler, &birimDiziBoyutu, birim1);
    printf("%f\n", birimCalisanMaasOrtalamaHesapla(&birim1));
    birimCalisanOrtalamaUstuMaas(&birim1);
    free(calisanlar);
    free(birimler);
}
