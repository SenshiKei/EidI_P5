//
// Created by belah on 29.12.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Sudoku.h"
#include "List.h"
#include "config_util.h"

struct SudokuNode *SudokuNode_New(int value)
{
    struct SudokuNode *newNode = malloc(sizeof(struct SudokuNode));

    if (newNode == NULL) exit_with_output("Malloc");

    newNode->currentNumber = value;

    struct List2D *options = List2D_New();

    newNode->options = options;

    return newNode;
}

struct SudokuNode **initialisiereSpielfeld(int quadrantengroesse)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;
    struct SudokuNode **spielfeld = (struct SudokuNode **) malloc(spielfeldgroesse * sizeof(struct SudokuNode*));

    if (spielfeld == NULL) exit_with_output("Malloc");

    for (int i = 0; i < spielfeldgroesse; ++i)
    {
        spielfeld[i] = (struct SudokuNode*) malloc(spielfeldgroesse * sizeof(struct SudokuNode));
        if (spielfeld[i] == NULL) exit_with_output("Malloc");
    }

    return spielfeld;
}

void erstelleSudoku(int startwert, struct SudokuNode **spielfeld, int quadrantengroesse)
{
    int laufIndex = startwert;
    int startvalue = laufIndex;
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < spielfeldgroesse; i++)
    {

        for (int j = 0; j < spielfeldgroesse; j++)
        {

            spielfeld[i][j] = *SudokuNode_New(laufIndex);
            laufIndex++;
            if (laufIndex > spielfeldgroesse) laufIndex = 1;
        }

        if ((i + 1) % quadrantengroesse == 0 && i != 0)
        {
            startvalue = startvalue % spielfeldgroesse + 1;
            laufIndex = startvalue;
        } else
        {
            laufIndex = (laufIndex + quadrantengroesse - 1) % spielfeldgroesse + 1;
        }
    }

}

void druckeSudoku(struct SudokuNode **spielfeld, int quadrantengroesse, int zahlenraum)
{
    int feldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < feldgroesse; i++)
    {

        for (int j = 0; j < feldgroesse; j++)
        {

            if (zahlenraum == DEC)
            {
                if (spielfeld[i][j].currentNumber == -1)
                {
                    printf(" __ ");
                    continue;
                }
                printf("%2d  ", spielfeld[i][j].currentNumber);
            } else if (zahlenraum == Hex)
            {
                if (spielfeld[i][j].currentNumber == -1)
                {
                    printf(" __ ");
                    continue;
                }
                printf("%2x  ", spielfeld[i][j]);
            }
        }
        printf("\n\n");
    }
}

void loescheSpielfeld(struct SudokuNode **spielfeld, int quadrantengroesse)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < spielfeldgroesse; i++)
    {
        for (int j = 0; j < spielfeldgroesse; j++) {
            List2D_Clear(spielfeld[i][j].options);
            free(&spielfeld[i][j]);
        }
        free(spielfeld[i]);
    }
    free(spielfeld);
}

void blendeAus(struct SudokuNode **spielfeld, int quadrantengroesse)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;
    srand((unsigned) time(NULL));

    for (int i = 0; i < quadrantengroesse; ++i)
    {
        int x = rand() % spielfeldgroesse;
        int y = rand() % spielfeldgroesse;

        if (spielfeld[x][y].currentNumber == -1)
        {
            i--;
            continue;
        }

        spielfeld[x][y].currentNumber = -1;
    }

}

int istVoll(struct SudokuNode **spielfeld, int quadrantengroesse)
{
    int feldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < feldgroesse; i++)
    {

        for (int j = 0; j < feldgroesse; j++)
        {
            if (spielfeld[i][j].currentNumber == -1) return 0;
        }

    }

    return 1;
}

int validerInput(struct SudokuNode **spielfeld, int quadrantengroesse, int zahlenraum)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    int x = 0, y = 0, feldzahl = 0;

    //X Axis
    printf("Bitte geben Sie eine Y-Koordinate ein:\n");
    scanf(" %d", &x);

    x--;
    if (x >= spielfeldgroesse)
    {
        puts("Y-Koordinate ausserhalb des Spielfeldes");
        return 0;
    }


    //Y Axis
    printf("Bitte geben Sie eine X-Koordinate ein:\n");
    scanf(" %d", &y);

    y--;
    if (y >= spielfeldgroesse)
    {
        puts("X-Koordinate ausserhalb des Spielfeldes");
        return 0;
    }

    //Check if choosen field is hidden
    if (spielfeld[x][y].currentNumber != -1)
    {
        puts("Feld ist bereits ausgefuellt");
        return 0;
    }

    //Fieldvalue
    printf("Bitte geben Sie den Wert des Feldes an:\n");
    if (zahlenraum == DEC)
    {
        scanf(" %d", &feldzahl);
    } else if (zahlenraum == Hex)
    {
        scanf(" %x", &feldzahl);
    }

    if (
            !validerInputZeile(spielfeld, quadrantengroesse, feldzahl, y)
            || !validerInputSpalte(spielfeld, quadrantengroesse, feldzahl, x)
            || !validerInputQuadrant(spielfeld, quadrantengroesse, feldzahl, x, y)
            )
    {
        puts("Invalider input");
        return 0;
    }

    printf("Korrekt! %d ist die richtige Eingabe!\n\n", feldzahl);

    InputXY(spielfeld, 9, x, y, feldzahl);

    return 1;
}

int validerInputXY(struct SudokuNode **spielfeld, int quadrantengroesse, int x, int y, int input)
{
    if
    (
            !validerInputZeile(spielfeld, quadrantengroesse, input, y)
            || !validerInputSpalte(spielfeld, quadrantengroesse, input, x)
            || !validerInputQuadrant(spielfeld, quadrantengroesse, input, x, y)
    )
    {
        return 0;
    }

    return 1;
}

int validerInputZeile(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int y)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < spielfeldgroesse; ++i)
    {
        if (spielfeld[i][y].currentNumber == input) return 0;
    }

    return 1;
}

int validerInputSpalte(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int x)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < spielfeldgroesse; ++i)
    {
        if (spielfeld[x][i].currentNumber == input) return 0;
    }

    return 1;
}

int validerInputQuadrant(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int x, int y)
{
    int quadrantX = x / quadrantengroesse;
    int quadrantY = y / quadrantengroesse;

    for (int i = 0; i < quadrantengroesse; ++i)
    {

        for (int j = 0; j < quadrantengroesse; ++j)
        {
            if (spielfeld[quadrantX * quadrantengroesse + i][quadrantY * quadrantengroesse + j].currentNumber == input) return 0;
        }

    }

    return 1;
}

//Statisches Sudoku
void erstelleSudokuStatisch(struct SudokuNode **spielfeld)
{
    for (int i = 0; i < 9; ++i)
    {

        for (int j = 0; j < 9; ++j)
        {
            spielfeld[i][j] = *SudokuNode_New(-1);
        }

    }

    spielfeld[0][1] = *SudokuNode_New(3);
    spielfeld[1][3] = *SudokuNode_New(1);
    spielfeld[1][4] = *SudokuNode_New(9);
    spielfeld[1][5] = *SudokuNode_New(5);
    spielfeld[2][2] = *SudokuNode_New(8);
    spielfeld[2][7] = *SudokuNode_New(6);
    spielfeld[3][0] = *SudokuNode_New(8);
    spielfeld[3][4] = *SudokuNode_New(6);
    spielfeld[4][0] = *SudokuNode_New(4);
    spielfeld[4][3] = *SudokuNode_New(8);
    spielfeld[4][8] = *SudokuNode_New(1);
    spielfeld[5][4] = *SudokuNode_New(2);
    spielfeld[6][1] = *SudokuNode_New(6);
    spielfeld[6][6] = *SudokuNode_New(2);
    spielfeld[6][7] = *SudokuNode_New(8);
    spielfeld[7][3] = *SudokuNode_New(4);
    spielfeld[7][4] = *SudokuNode_New(1);
    spielfeld[7][5] = *SudokuNode_New(9);
    spielfeld[7][8] = *SudokuNode_New(5);
    spielfeld[8][7] = *SudokuNode_New(7);

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {
            if (spielfeld[i][j].currentNumber != -1) continue;
            SetzeOptionen(spielfeld,i,j);
        }
    }
}

void SetzeOptionen(struct SudokuNode** spielfeld, int x, int y)
{
    for (int i = 0; i < 9; i++) {
        if(validerInputXY(spielfeld,3,x,y,i+1))
            List2D_Append(spielfeld[x][y].options, Node2D_New(i+1));
    }
}

void InputXY(struct SudokuNode **spielfeld, int quadrantengroesse, int x, int y, int input)
{
    spielfeld[x][y].currentNumber = input;
    List2D_Clear(spielfeld[x][y].options);
    spielfeld[x][y].options = List2D_New();
    puts("test1");
    InputZeile(spielfeld, 9, input, y);
    puts("test2");
    InputQuadrant(spielfeld, 9, input, x, y);
    puts("test3");
    InputSpalte(spielfeld, 9, input, x);
    puts("test4");
}

void InputZeile(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int y)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < spielfeldgroesse-1; i++)
    {
        puts("zeile");
        if (spielfeld[i][y].currentNumber != -1) continue;
        List2D_Remove(spielfeld[i][y].options, input);
        if (List2D_Length(spielfeld[i][y].options) == 1){
            puts("test");
            InputXY(spielfeld, 9, i, y, spielfeld[i][y].options->first->value);
        }
    }
}

void InputSpalte(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int x)
{
    int spielfeldgroesse = quadrantengroesse * quadrantengroesse;

    for (int i = 0; i < spielfeldgroesse-1; i++)
    {

        if (spielfeld[x][i].currentNumber != -1) continue;
        List2D_Remove(spielfeld[x][i].options, input);
        if (List2D_Length(spielfeld[x][i].options) == 1){
            puts("test");
            InputXY(spielfeld, 9, x, i, spielfeld[x][i].options->first->value);}
    }

}

void InputQuadrant(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int x, int y)
{
    int quadrantX = x / quadrantengroesse;
    int quadrantY = y / quadrantengroesse;

    for (int i = 0; i < quadrantengroesse-1; i++)
    {

        for (int j = 0; j < quadrantengroesse-1; j++)
        {
            if (spielfeld[i][j].currentNumber != -1) continue;

            List2D_Remove(spielfeld[i][j].options, input);
            if (List2D_Length(spielfeld[i][j].options) == 1){
                puts("test");
                InputXY(spielfeld, 9, i, j, spielfeld[x][i].options->first->value);}
        }

    }
}
