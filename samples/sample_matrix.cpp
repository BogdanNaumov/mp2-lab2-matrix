// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
    int i, j, size;

    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класс работы с матрицами" << endl;
    cout << "Введите размер вектора: ";
    cin >> size;
    TDynamicVector<int> Va(size);
    TDynamicVector<int> Vb(size);
    TDynamicVector<int> Vc(size);
    for (i = 0; i < size; i++) {
        Va[i] = rand() % 100 + 1;
        Vb[i] = rand() % 100 + 1;
    }
    cout << "Вектор а = " << endl << Va << endl;
    cout << "Вектор b = " << endl << Vb << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Скалярные операции:" << endl;
    Vc = Va + 10;
    cout << "Вектор c = а + 10" << endl << Vc << endl << endl;

    Vc = Va - 10;
    cout << "Вектор c = а - 10" << endl << Vc << endl << endl;

    Vc = Va * 3;
    cout << "Вектор c = а * 3" << endl << Vc << endl << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Векторные операции:" << endl;
    Vc = Va + Vb;
    cout << "Вектор c = а + b" << endl << Vc << endl << endl;

    Vc = Va - Vb;
    cout << "Вектор c = а - b" << endl << Vc << endl << endl;

    int res = Va * Vb;
    cout << "res = а * b" << endl << res << endl << endl;
    cout << "----------------------------------------------------" << endl;





    cout << "Введите размер матрицы: ";
    cin >> size;
    TDynamicVector<int> Vres(size);
    TDynamicVector<int> Vd(size);
    TDynamicMatrix<int> Ma(size);
    TDynamicMatrix<int> Mb(size);
    TDynamicMatrix<int> Mc(size);
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
        {
            Ma[i][j] = rand() % 100;
            Mb[i][j] = rand() % 100;
            Vd[i] = rand() % 100;
        }
    if (size <= 10) cout << "Матрица а = " << endl << Ma << endl;
    if (size <= 10) cout << "Матрица b = " << endl << Mb << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Матрично-скалярные операции:" << endl;
    Mc = Ma * 3;
    if (size <= 10) cout << "Матрица c = а * 3" << endl << Mc << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Матрично-векторные операции:" << endl;
    if (size <= 10) cout << "Вектор d = " << endl << Vd << endl;
    Vres = Ma * Vd;
    if (size <= 10) cout << "Вектор res = а * d" << endl << Vres << endl;
    cout << "----------------------------------------------------" << endl;

    cout << "Матрично-матричные операции:" << endl;

    Mc = Ma + Mb;


    if (size <= 10) cout << "Матрица c = а + b" << endl << Mc << endl;


    Mc = Ma - Mb;
    if (size <= 10) cout << "Матрица c = а - b" << endl << Mc << endl;

    clock_t start1 = clock();
    Mc = Ma * Mb;
    clock_t stop1 = clock();
    double seconds = (double)(stop1 - start1) / CLOCKS_PER_SEC;
   // cout << "Времени ушло на сложение:" << endl << seconds << endl;
    if (size <= 10) cout << "Матрица c = а * b" << endl << Mc << endl;
}
//---------------------------------------------------------------------------

