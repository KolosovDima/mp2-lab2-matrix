// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы
#include <time.h>
#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{
	clock_t start, end;
	const int size=900;

  //TMatrix<int> a(size), b(size), c(size);
  //int i, j;
	TMatrix<int> l1(size), l2(size);
	int i, j;

  //setlocale(LC_ALL, "Russian");
  //cout << "Тестирование программ поддержки представления треугольных матриц"
  //  << endl;
  //for (i = 0; i < 5; i++)
  //  for (j = i; j < 5; j++ )
  //  {
  //    a[i][j] =  i * 10 + j;
  //    b[i][j] = (i * 10 + j) * 100;
  //  }
  //c = a + b;
  //cout << "Matrix a = " << endl << a << endl;
  //cout << "Matrix b = " << endl << b << endl;
  //cout << "Matrix c = a + b" << endl << c << endl;
	start = clock();
			for ( i=0;i<size;i++)
				for ( j=0;j<size-i;j++)
					l1[i][j]=j;
	l2 = l1*l1;
	end = clock();
cout << "Time: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << endl;
//system("pause");
}
//---------------------------------------------------------------------------
