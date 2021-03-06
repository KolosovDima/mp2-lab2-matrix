﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize() const  { return Size;       } // размер вектора
  int GetStartIndex()const{ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos) const;             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s<1)||(si<0))
		throw "negative_size_or_startindex";
	else if ((s>MAX_VECTOR_SIZE)||(si>MAX_VECTOR_SIZE))
		throw "size_or_startindex_more_MAX_VECTOR_SIZE";
	else
	{
		Size=s;
		StartIndex=si;
		pVector= new ValType[Size];
		/*cout << "Vector constr, pVector" << pVector << "\n";*/
		// (int i=StartIndex;i<Size+StartIndex;i++)
		//	(*this)[i] = ValType();
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size=v.GetSize();
	StartIndex=v.GetStartIndex();
	pVector= new ValType[Size];
	for (int i=StartIndex;i<Size+StartIndex;i++)
		(*this)[i]=v[i];

} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	/*cout << "Vector destr, pVector" << pVector << "\n";*/
	if (pVector!=NULL)
			delete [] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) const
{
	if (pos<0)
		throw "negative_index";
	else if (pos>=Size+StartIndex)
		throw "index_more_SIZE";
	else if (pos<StartIndex)
		return *new ValType();
	else
		return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	bool sr=true;
	if (Size != v.GetSize())
		return sr=false;
	else
	{
		if (StartIndex != v.GetStartIndex())
			sr=false;
		for(int i=StartIndex;i<Size+StartIndex;i++)
			if(pVector[i]!=v.pVector[i])
				sr=false;
		return sr;
	}

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (Size != v.GetSize())
	{
		delete []pVector;
		pVector= new ValType[v.GetSize()];
	}
	Size = v.GetSize();
	StartIndex = v.GetStartIndex();
	for (int i=StartIndex;i<Size+StartIndex;i++)
		(*this)[i] = v[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> Nv(*this);
	for(int i=StartIndex;i<Size+StartIndex;i++)
		Nv[i]+=val;
	return Nv;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> Nv(*this);
	for(int i=StartIndex;i<Size+StartIndex;i++)
		Nv[i]-=val;
	return Nv;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{	
	TVector<ValType> Nv(*this);
	for(int i=StartIndex;i<Size+StartIndex;i++)
		Nv[i]*=val;
	return Nv;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if((Size == v.GetSize())&&(StartIndex == v.GetStartIndex()))
	{
		TVector <ValType> Nv(*this);
		for(int i=StartIndex;i<Size+StartIndex;i++)
			Nv[i]=Nv[i]+v[i];
		return Nv;
	}
	else 
		throw "size_or_startindex_no_match";
		
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if((Size == v.GetSize())&&(StartIndex == v.GetStartIndex()))
	{
		TVector <ValType> Nv(*this);
		for(int i=StartIndex;i<Size+StartIndex;i++)
			Nv[i]=Nv[i]-v[i];
		return Nv;
	}
	else 
		throw "size_or_startindex_no_match";

} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if((Size != v.GetSize())||(StartIndex != v.GetStartIndex()))
			throw "size_or_startindex_no_match";
	else 
	{
		ValType sum = 0;
		for(int i=StartIndex;i<Size+StartIndex;i++)
			sum=sum+(*this)[i]*v[i];
		return sum;
	}
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  TMatrix  operator* (const TMatrix<ValType> &m2);

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	StartIndex=0;
	Size=s;
	if (s<0)
		throw ("negative_size");
	else if (s>MAX_MATRIX_SIZE) 
		throw ("size_more_MAX_MATRIX_SIZE");
	else
		for (int i = StartIndex; i < s+StartIndex; i++) 
			pVector[i] = TVector<ValType>(Size-i, i);

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
  {
  }

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this==&mt)
		return true;
	else if (Size != mt.GetSize())
		return false;
	else
	{
		for (int i = StartIndex; i < Size+StartIndex; i++) 
			if (pVector[i]!=mt[i])
				return false;
		return true;
	}

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this==mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this!=&mt)
	{
		if (Size != mt.Size) 
		{

			//for (int i = StartIndex; i < Size+StartIndex; i++)
			//	delete &(pVector[i]);
			delete [] pVector;
			Size = mt.Size;
			pVector = new TVector<ValType>[mt.Size];
		}
		StartIndex = mt.StartIndex;
		for (int i = StartIndex; i < Size+StartIndex; i++)
			pVector[i] = mt.pVector[i];
	}
return *this;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size) 
		throw "No_equal_size";
	else
	{
		TMatrix<ValType> sum(*this);
		for (int i = StartIndex; i < Size+StartIndex; i++)
			sum[i] = sum[i]+ mt[i];
		return sum;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size)
		throw "No_equal_size";
	else
	{
		TMatrix<ValType> sum(*this);
		for (int i = StartIndex; i < Size+StartIndex; i++)
			sum[i] = sum[i]- mt[i];
		return sum;
	}
} /*-------------------------------------------------------------------------*/
template <class ValType> // умножение
TMatrix<ValType> TMatrix<ValType>::operator* (const TMatrix<ValType> &m2)
{
if (Size != m2.GetSize())
	throw "No_equal_size";
else
{
TMatrix<ValType> sr(Size);
for (int i = 0; i < (*this).GetSize(); i++)

for (int j = i; j < (*this).GetSize(); j++)
		for (int k = 0; k <= j; k++)	
			sr[i][j] = sr[i][j] + ((*this)[i][k])*(m2[k][j]);
return sr;
}
}/*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
