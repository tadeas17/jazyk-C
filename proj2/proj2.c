#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double calculate_ip(double up) { //Funkce pro výpočet ip.
    return 1e-12 * (exp(up / 0.0258563) - 1);
}

double calculate_up(double u0, double r, double up) { //Funkce pro výpočet up.
    return calculate_ip(up) - ((u0 - up) / r);
}

double diode(double u0, double r, double eps) {
    double up = 0;
    double lower_limit = 0;
    double upper_limit = u0;
    double result;
    double up_last = 0;

    while (upper_limit - lower_limit > eps) { //Bude se provádět dokud odchylka eps bude větší než rozsah.
        up = (upper_limit + lower_limit) / 2;
        if (up == up_last) { //Kontrola jestli se up stále neopakuje a celý ciklus se nezaciklil.
            break;
        }
        up_last = up;
        result = calculate_up(u0, r, up);

        if (result > 0) { //Posouvá horní hranici.
            upper_limit = up;
        }
        if (result < 0) { //Posouvá dolní hranici.
            lower_limit = up;
        }
        if (result == 0) { //Pokud je výsledek spočítán přesně.
            break;
        }
    }
    return up;
}

int validate_arguments(int argc, char *argv[]) { //Funce pro validaci vstupních argumentů.
    char *end;
    double result;

    if (argc != 4) { //Zjišťuje jestli není předáno víc vstupních dat.
        return 0;
    }
    for (int i = 1; i <= 3; i++) {
        result = strtod(argv[i], &end); //Do result se nahraje číslo ze stringu a do end zbytek stringu.
        if (result < 0 || *end != '\0') { //Kontroluje jestli jsou zadány pouze čísla a větší než nula.
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {

    int is_arguments_valid = validate_arguments(argc, argv);
    if (!is_arguments_valid) { //Pokud nejsou validní vstupní argumenty je vypsána chyba.
        fprintf(stderr, "error: invalid arguments\n");
        return 1;
    }
    double up = diode(atof(argv[1]), atof(argv[2]), atof(argv[3]));
    double ip = calculate_ip(up);
    printf("Up=%g V\nIp=%g A\n", up, ip);

    return 0;
}
