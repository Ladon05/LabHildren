#include <stdio.h>
#include <string.h>
#include <conio.h>

int main()
{
    char cedula[20];
    int i = 0;
    char caracter;

    printf("ingresa tu cedula\n");

    while (strlen(cedula) < 8)
    {
        if (kbhit())
        {
            caracter = getch();
            if ((caracter >= 48) && (caracter <= 57))
            {
                cedula[i] = caracter;
                i++;
                printf("%c", caracter);
            }

            else if (caracter == '\r')
            {
                cedula[i] = '\0';
                break;
            }

            else if (caracter == '\b')
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }

            fflush(stdin);
        }
    }

    printf("\ncedula = %s", cedula);

    return 0;
}