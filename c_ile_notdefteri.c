#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct Not
{
    int id;
    int aktif;
    char yazi[300];
};

int menu();
void notEkle(FILE *dosya);
void notListele(FILE *dosya);
void notSil(FILE *dosya);

int main()
{
    FILE *dosya;
    int secim;

    dosya = fopen("notlar.dat", "rb+");

    if (dosya == NULL)
    {
        dosya = fopen("notlar.dat", "wb+");

        if (dosya == NULL)
        {
            printf("Dosya acilamadi.\n");
            return 1;
        }
    }

    while ((secim = menu()) != 4)
    {
        switch (secim)
        {
        case 1:
            notEkle(dosya);
            break;

        case 2:
            notListele(dosya);
            break;

        case 3:
            notSil(dosya);
            break;

        default:
            printf("Gecersiz secim.\n");
        }
    }

    fclose(dosya);

    return 0;
}

int menu()
{
    int secim;

    printf("\n===== NOT DEFTERI =====\n");
    printf("1 - Not Ekle\n");
    printf("2 - Notlari Listele\n");
    printf("3 - Not Sil\n");
    printf("4 - Cikis\n");
    printf("Secim: ");

    scanf("%d", &secim);
    getchar();

    return secim;
}
void notEkle(FILE *dosya) {}
void notListele(FILE *dosya) {}
void notSil(FILE *dosya) {};