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
    int diziBoyutu = 0; // Başlangıçta dizinin boyutu sıfır
    Calisan *calisanlar = NULL;
    Calisan calisan1 = *calisanOlustur("Ali", "Veli", 101, 5000.0, 2015);
    calisanlar = calisanDiziOlustur(calisanlar, &diziBoyutu, calisan1);
    Calisan calisan2 = *calisanOlustur("Ahmet", "Ok", 102, 50000.0, 2013);
    calisanlar = calisanDiziOlustur(calisanlar, &diziBoyutu, calisan2);
    for (int i = 0; i < diziBoyutu; i++)
    {
        printf("%s", calisanlar[i].calisanAdi);
    }
    free(calisanlar);
}
