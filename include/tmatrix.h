// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      if (v.pMem == nullptr) { size = 0; pMem = nullptr;}
      else 
      {
          sz = v.size;
          pMem = new T[sz];
          copy(v.pMem, arr + sz, pMem);
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
  }
  ~TDynamicVector()
  {
      if (pMem != nullptr) 
      {
          delete[] pMem;
          sz = 0;
      }
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) 
      {
          if ((pMem != nullptr) || (pMem == nullptr))
          {
              delete[] pMem;
          }
          else
          {
              sz = v.sz;
              pMem = new T[sz];
              copy(v.pMem, v.pMem + sz, pMem);
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v)
      {
          if (pMem != nullptr) {delete[] pMem }
          if (pMem == nullptr) {sz = 0; pMem = nullptr;}
          else
          {
              sz = v.sz;
              pMem = new T[sz];
              copy(v.pMem, v.pMem + sz, pMem);
          }
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (pMem == nullptr) { throw ""; }
      if ((ind < 0) || (ind >= sz)) { throw ""; }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (pMem == nullptr) { throw ""; }
      if ((ind < 0) || (ind >= sz)) { throw ""; }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) { return false; }
      for (int i = 0; i < sz; i++) { if (pMem[i] != v.pMem[i]) { return false; }}
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) { return true; }
      for (int i = 0; i < sz; i++) { if (pMem[i] != v.pMem[i]) { return true; } }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> res(*this);
      for (int i = 0; i < this.sz; i++) { res.pMem[i] += val; }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> res(*this);
      for (int i = 0; i < this.sz; i++) { res.pMem[i] -= val; }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> res(*this);
      for (int i = 0; i < this.sz; i++) { res.pMem[i] *= val; }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      TDynamicVector<T> res(*this);
      if (this->sz != v.sz) { throw "ERROR: Vector diffirent size"; }
      else 
      {
          for (int i = 0; i < this.sz; i++) { res.pMem = this.pMem[i] += v.pMem[i]; }
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      TDynamicVector<T> res(*this);
      if (this->sz != v.sz) { throw "ERROR: Vector diffirent size"; }
      else
      {
          for (int i = 0; i < this.sz; i++) { res.pMem = this.pMem[i] -= v.pMem[i]; }
      }
      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      TDynamicVector<T> res(*this);
      if (this->sz != v.sz) { throw "ERROR: Vector diffirent size"; }
      else
      {
          for (int i = 0; i < this.sz; i++) { res.pMem = this.pMem[i] *= v.pMem[i]; }
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
