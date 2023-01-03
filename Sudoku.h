//
// Created by belah on 29.12.2022.
//

#ifndef EIDI_P5_SUDOKU_H
#define EIDI_P5_SUDOKU_H

struct SudokuNode
{
    int currentNumber;
    struct List2D *options;
};

struct SudokuNode *SudokuNode_New(int value);

struct SudokuNode **initialisiereSpielfeld(int quadrantengroesse);

void erstelleSudoku(int startwert, struct SudokuNode **spielfeld, int quadrantengroesse);

void erstelleSudokuStatisch(struct SudokuNode **spielfeld);

void druckeSudoku(struct SudokuNode **spielfeld, int quadrantengroesse, int zahlenraum);

void loescheSpielfeld(struct SudokuNode **spielfeld, int quadrantengroesse);

void blendeAus(struct SudokuNode **spielfeld, int quadrantengroesse);

int istVoll(struct SudokuNode **spielfeld, int quadrantengroesse);

int validerInput(struct SudokuNode **spielfeld, int quadrantengroesse, int zahlenraum);

int validerInputZeile(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int y);

int validerInputSpalte(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int x);

int validerInputQuadrant(struct SudokuNode **spielfeld, int quadrantengroesse, int input, int x, int y);


#endif //EIDI_P5_SUDOKU_H
