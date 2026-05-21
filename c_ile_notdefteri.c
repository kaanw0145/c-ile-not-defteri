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
void notEkle(FILE *dosya)
{
    struct Not yeniNot, temp;

    int sonID = 0;

    rewind(dosya);

    while (fread(&temp, sizeof(struct Not), 1, dosya))
    {
        if (temp.id > sonID)
        {
            sonID = temp.id;
        }
    }

    yeniNot.id = sonID + 1;
    yeniNot.aktif = 1;

    printf("Not gir: ");
    fgets(yeniNot.yazi, 300, stdin);

    yeniNot.yazi[strcspn(yeniNot.yazi, "\n")] = '\0';

    fseek(dosya, 0, SEEK_END);

    fwrite(&yeniNot, sizeof(struct Not), 1, dosya);

    printf("Not eklendi. ID: %d\n", yeniNot.id);
}
void notListele(FILE *dosya)
{

    struct Not not;

    rewind(dosya);

    printf("\n===== NOTLAR =====\n");

    while (fread(&not, sizeof(struct Not), 1, dosya))
    {
        if (not.aktif == 1)
        {
            printf("%d) %s\n", not.id, not.yazi);
            printf("-------------------\n");
        }
    }
}
void notSil(FILE *dosya)
{
    struct Not not;
    int silinecekID;

    printf("Silinecek not ID: ");
    scanf("%d", &silinecekID);

    rewind(dosya);

    while (fread(&not, sizeof(struct Not), 1, dosya))
    {
        if (not.id == silinecekID && not.aktif == 1)
        {
            not.aktif = 0;

            fseek(dosya, -sizeof(struct Not), SEEK_CUR);

            fwrite(&not, sizeof(struct Not), 1, dosya);
            printf("Not silindi.\n");

            return;
        }
    }

    printf("Not bulunamadi.\n");
}