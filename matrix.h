//
// Created by brueni on 27.10.19.
//

#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H

#include <map>
#include "CRElement.h"

/*
 * This is a template for a matrix where you can delete columns and/or rows and insert them.
 */

template< class T>
class Matrix {
    T* _matrix;
    std::map<int, CRElement*> rowMap{};
    std::map<int, CRElement*> columnmap{};
    CRElement _firstRow;
    CRElement _firstColumn;
    void resize(bool isCalledByUser=true);
public:
    Matrix();
    Matrix(int columns, int rows);
    ~Matrix();
    bool insertRow(int row = -1);
    bool deleteRow(int row);
    bool insertColumn(int column = -1);
    bool deleteColumn(int column);
    bool insertElement(T &elem, int row, int column);
    T& getElement(int row, int column);
    T& getElement(CRElement row, CRElement column);
    T* getElementPointer(CRElement row, CRElement column);
    int DEFAULT_SIZE = 25;
    int _maxAmountColumns = 0;
    int _maxAmountRows = 0;

};



#endif //UNTITLED1_MATRIX_H
