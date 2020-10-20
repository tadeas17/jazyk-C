#include <stdio.h>
#include <string.h>

//Funkce pro načtení 103 znaků ze stdin
void read_line(char *line) {
    memset(line, 0, 103);
    fgets(line, 103, stdin);
    return;;
}

//Začne načítat znaky ze stdin dokud se nedostane na nový řádek.
void skip_line(char *line) {
    while (!(strlen(line) < 101 || line[100] == '\n')) {
        read_line(line);
    }
    return;
}

//Funkce, která zkontroluje jestli je řádek validní.
//Validní řádek má méně než 100 znaků.
//Pokud je validní vrátí 1 jinak 0.
int is_line_valid(char *line) {
    if (strlen(line) < 101 || line[100] == '\n') {
        return 1;
    } else {
        return 0;
    }
}

//Vytiskne řádek bez znaku nového řádku
int print_line(char *line) {
    for (int i = 0; i < 103; i++) {
        if (line[i] == '\0' || line[i] == '\n') {
            break;
        }
        putchar(line[i]);
    }
    return 1;
}

//Funkce pro vytisknutí validního řádku ve formátu: "jméno", "číslo".
void print_contact(char *name, char *numb) {
    print_line(name);
    printf(", ");
    print_line(numb);
    printf("\n");
    return;
}

//Funkce pro převod znaku na číslo.
//Vrací danou číslici, pokud nebyla nalezena vrátí původní znak.
char letter_to_number(char letter) {
    int ascii_letter = (int) letter;
    if (('A' <= ascii_letter && ascii_letter <= 'C') || ('a' <= ascii_letter && ascii_letter <= 'c')) {
        return '2';
    }
    if (('D' <= ascii_letter && ascii_letter <= 'F') || ('d' <= ascii_letter && ascii_letter <= 'f')) {
        return '3';
    }
    if (('G' <= ascii_letter && ascii_letter <= 'I') || ('g' <= ascii_letter && ascii_letter <= 'i')) {
        return '4';
    }
    if (('J' <= ascii_letter && ascii_letter <= 'L') || ('j' <= ascii_letter && ascii_letter <= 'l')) {
        return '5';
    }
    if (('M' <= ascii_letter && ascii_letter <= 'O') || ('m' <= ascii_letter && ascii_letter <= 'o')) {
        return '6';
    }
    if (('P' <= ascii_letter && ascii_letter <= 'S') || ('p' <= ascii_letter && ascii_letter <= 's')) {
        return '7';
    }
    if (('T' <= ascii_letter && ascii_letter <= 'V') || ('t' <= ascii_letter && ascii_letter <= 'v')) {
        return '8';
    }
    if (('W' <= ascii_letter && ascii_letter <= 'Z') || ('w' <= ascii_letter && ascii_letter <= 'z')) {
        return '9';
    }
    if (ascii_letter == '+') {
        return '0';
    }
    return letter;
}

//Funkce pro zjištění jestli se nachází hledané číslice ve jménu nebo číslu.
//Vrací 1 pokud nalezne alespoň u jednoho shodu.
//Vrátí 0 pokud se tam dané znaky nevyskytují.
int include(char *name, char *numb, char *find) {
    int size_find = strlen(find);
    int size_name = strlen(name);
    int size_numb = strlen(numb);
    int index_find_name = 0;
    int index_find_numb = 0;

    if (find[0] == '\0') { //Pokud není podle čeho hledat tak vrátí vždy 1.
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        if (i < size_numb && numb[i] == find[index_find_numb]) { //Kontroluje jestli se hledané číslo nachází v čísle.
            index_find_numb++;
        }
        if (i < size_name && (letter_to_number(name[i]) == find[index_find_name] || name[i] == find[index_find_name])) { //Kontroluje jestli se číslo nachází ve jménu.
            index_find_name++;
        }
        if (!(i < size_name || i < size_numb)) { //Pokud se již zkontrolovalo celé jméno i celé číslo je proces hledání ukončen.
            break;
        }
        if (index_find_numb == size_find || index_find_name == size_find) { //Pokud je nalezena kompletní shoda jak ve jménu nebo v čísle vrátí 1.
            return 1;
        }

    }
    return 0;
}

//Funkce pro zkontrolování zda=li je číslo validni.
//Validní řádek obsahuje pouze znaky číslic a je kratší než 100 znaků, protože nejdelší validní data mají maximálně 100 znaků
int is_find_number_valid(char *numb) {
    int size_line = strlen(numb);
    if (size_line > 101) {
        fprintf(stderr, "Vstupni parametr je delsi nez 100 znaku, tedy nebude moct vyhledat zadny kontakt.\n");
        return 0;
    }
    for (int i = 0; i < size_line; i++) {
        switch (numb[i]) { //Zjišťuje jestli je poze číslo.
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            default:
                fprintf(stderr, "Vstupni parametr neobsahuje pouze cislice.\n");
                return 0;
                break;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {

    char name[103];
    char number[103];
    int exist = 0;
    int is_number = 0;
    int have;

    if (argc > 1) {
        if (argc > 2) { //Polud je předáno více vstupních parametrů program vypíše chybu
            fprintf(stderr, "Nespravny pocet vstupnich parametru.\n");
            return 1;
        }
        if (is_find_number_valid(argv[1]) == 0) { //Zkontroluje jestli jsou vatupní data platná.
            return 1;
        }
    }
    char *find = (argc == 2 ? argv[1] : "\0");  //Pokud nebyl předán žádný parametr, tak vytvoří string o nulové délce

    while (!feof(stdin)) { //Dokud budou ve stdin nějáká data

        if (is_number) { //Pokud je na řádku číslo
            read_line(number);
            if (!(is_line_valid(number))) { //Pokud řádek není validní tak se bere jako prázdný řádek.
                skip_line(number);
                memset(number, 0, 103);
            }
            have = include(name, number, find);
            if (have) {
                print_contact(name, number);
                exist = 1;

            }
            is_number = 0;
        } else { //Pokud je na řádku jméno
            read_line(name);
            if (!(is_line_valid(name))) { //Pokud řádek není validní tak se bere jako prázdný řádek.
                skip_line(name);
                memset(name, 0, 103);
            }
            is_number = 1;
        }
    }

    if (exist == 0) { //Jestli nebyla nalezena žádná schoda.
        printf("Not found\n");
        return 1;
    }

    return 0;
}
