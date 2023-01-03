#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "List.h"
#include "Sudoku.h"
#include "config_util.h"


int main(void)
{
    int spielart = ermittleSpielart();

    int quadrantengroesse;
    int zahlenraum;
    int startwert;
    struct SudokuNode **spielfeld;

    if (spielart == Dyn)
    {
        quadrantengroesse = ermittleQuadrantengroesse();
        zahlenraum = ermittleZahlenraum();
        startwert = ermittleStartwert(zahlenraum);

        spielfeld = initialisiereSpielfeld(quadrantengroesse);


        erstelleSudoku(startwert, spielfeld, quadrantengroesse);

        blendeAus(spielfeld, quadrantengroesse);
    } else
    {
        quadrantengroesse = 3;
        zahlenraum = DEC;
        startwert = 1;

        spielfeld = initialisiereSpielfeld(quadrantengroesse);

        if (spielfeld == NULL) return EXIT_FAILURE;

        erstelleSudokuStatisch(spielfeld);
    }

    druckeSudoku(spielfeld, quadrantengroesse, zahlenraum);

    //Gameloop
    do
    {
        puts("---------------------------------");
        if (validerInput(spielfeld, quadrantengroesse, zahlenraum))
            druckeSudoku(spielfeld, quadrantengroesse, zahlenraum);

        int weitermachen = 0;
        puts("Willst du weiter machen?\n\tJa: 1\n\tNein: 2");
        scanf(" %d", &weitermachen);
        if (weitermachen != 1)
        {
            puts("Exiting..");
            return 0;
        }
    } while (!istVoll(spielfeld, quadrantengroesse));

    puts("Herzlichen Glueckwunsch! Sie haben das Sudoku geloest!");
    loescheSpielfeld(spielfeld, quadrantengroesse);

    return EXIT_SUCCESS;
}

int ermittleSpielart()
{
    int spielart;

    printf("Bitte waehlen Sie den Spielart:\n\tDynamisch: 1\n\tStatisch: 2\n");
    scanf(" %d", &spielart);

    if (spielart != Dyn && spielart != Sta)
    {
        printf("Bitte waehlen Sie ein validen Input\n");
        spielart = ermittleSpielart();
    }

    return spielart;
}


int ermittleQuadrantengroesse()
{
    int quadrantengroesse;

    printf("Bitte waehlen Sie die Quadrantengroesse:\n");
    scanf(" %d", &quadrantengroesse);

    return quadrantengroesse;
}

int ermittleStartwert(int zahlenraum)
{
    int startwert = 0;

    printf("Bitte geben Sie einen Startwert ein:");
    if (zahlenraum == DEC)
    {
        scanf(" %d", &startwert);
    } else if (zahlenraum == Hex)
    {
        scanf(" %x", &startwert);
    }

    return startwert;
}

int ermittleZahlenraum()
{
    int zahlenraum;

    printf("Bitte waehlen Sie den Zahlenraum:\n\tDecimal: 1\n\tHexadecimal: 2\n");
    scanf(" %d", &zahlenraum);

    if (zahlenraum != DEC && zahlenraum != Hex)
    {
        printf("Bitte waehlen Sie ein validen Input\n");
        zahlenraum = ermittleZahlenraum();
    }

    return zahlenraum;
}