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
public:
    size_t sz;
public:
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz < 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw "cant_create_too_large_vector";
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        //assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        if (v.pMem == nullptr) {
            sz = 0;
            pMem = nullptr;
        }
        else {
            sz = v.sz;
            pMem = new T[sz];
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;

        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr) {
            delete[] pMem;
            sz = 0;
        }
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            if (pMem != nullptr) {
                delete[] pMem;
            }
            if (v.pMem == nullptr) {
                sz = 0;
                pMem = nullptr;
            }
            else {

                sz = v.sz;
                pMem = new T[sz];
                std::copy(v.pMem, v.pMem + sz, pMem);
            }
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            if (pMem != nullptr) {
                delete[] pMem;
            }
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;

    }

    size_t size() const noexcept {
        return sz;
    }

    // индексация
    T& operator[](int ind)
    {
        return this->pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (pMem == nullptr) {
            throw "error 0";
        }
        if (ind < 0 || ind >= sz) {
            throw "error";
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        {
            if (pMem == nullptr) {
                throw "Error";
            }
            if (ind < 0 || ind >= sz) {
                throw "Error";
            }
            return pMem[ind];
        }
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        {
            if (sz != v.sz) {
                return true;
            }
            for (int i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) {
                    return true;
                }
            }
            return false;
        }
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] += val;
        }
        return *this;
    }
    TDynamicVector operator-(T val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] -= val;
        }
        return *this;
    }
    TDynamicVector operator*(T val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] *= val;
        }
        return *this;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            TDynamicVector tmp(sz);
            for (int i = 0; i < sz; i++) {
                tmp[i] = pMem[i] + v.pMem[i];
            }
            return tmp;
        }
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            TDynamicVector tmp(sz);
            for (int i = 0; i < sz; i++) {
                tmp[i] = pMem[i] - v.pMem[i];
            }
            return tmp;
        }
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            T sum = 0;
            for (int i = 0; i < sz; i++) {
                sum = sum + pMem[i] * v.pMem[i];
            }
            return sum;
        }
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
        if (sz < 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_MATRIX_SIZE) {
            throw "cant_create_too_large_matrix";
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];


    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        for (int i = 0; i < sz; i++) {
            pMem[i] = pMem[i] * val;
        }
        return *this;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz) {
            throw "sizes of Vectors are different";
        }
        else {
            TDynamicVector<T> sum(sz);
            for (int i = 0; i < sz; i++) {
                sum = sum + pMem[i] * v.pMem[i];
            }
            return sum;
        }
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw "sizes of Matrix are different";
        }
        else {
            TDynamicMatrix tmp(sz);
            for (int i = 0; i < sz; i++) {
                tmp.pMem[i] = pMem[i] + m.pMem[i];
            }
            return tmp;
        }
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw "sizes of Matrix are different";
        }
        else {
            TDynamicMatrix tmp(sz);
            for (int i = 0; i < sz; i++) {
                tmp.pMem[i] = pMem[i] - m.pMem[i];
            }
            return tmp;
        }
    }
    TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& m)
    {
        if (sz != m.sz) {
            throw "sizes of Matrix are different";
        }
        else {
            TDynamicMatrix tmp(sz);
            for (int i = 0; i < sz; i++) {
                for (int j = i + 1; j < sz; j++) {
                    int q = m.pMem[i][j];
                    m.pMem[i][j] = m.pMem[j][i];
                    m.pMem[j][i] = q;
                }
            }
            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    tmp.pMem[i][j] = pMem[i] * m.pMem[j];
                }
            }
            return tmp;
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i] << std::endl; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << std::endl; // требуется оператор<< для типа T
        return ostr;
    }
};

#endif
