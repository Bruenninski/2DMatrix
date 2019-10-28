//
// Created by brueni on 27.10.19.
//

#include <vector>
#include <algorithm>
#include "matrix.h"
template<typename T>
Matrix<T>::Matrix(){
    _matrix = new T[Matrix::DEFAULT_SIZE * Matrix::DEFAULT_SIZE];
    _maxAmountColumns = DEFAULT_SIZE;
    _maxAmountRows = DEFAULT_SIZE;
}

template<typename T>
Matrix<T>::Matrix(int columns, int rows) {
    _matrix = new T[Matrix::DEFAULT_SIZE * Matrix::DEFAULT_SIZE];
    //the max is a bit over the actual value, so there is space for adding new lines and rows
    _maxAmountColumns = columns * 1.1;
    _maxAmountRows = rows * 1.1;
    {
        _firstRow = new CRElement;
        CRElement* actualElement = _firstRow;
        actualElement->index = 0;
        //the element on position 0 is initialized above
        rowMap[0] = actualElement;
        for(int i=1; i< rows; ++i){
            CRElement* newElement = new CRElement();
            //creates the link between the two elements, newElement->next is still nullptr
            newElement->previous = actualElement;
            actualElement->next = newElement;
            newElement->index = i;
            rowMap[i] = newElement;
        }
    }
    {
        _firstColumn = new CRElement;
        CRElement* actualElement = _firstColumn;
        actualElement->index = 0;
        //the element on position 0 is initialized above
        columnmap[0] = actualElement;
        for(int i=1; i< rows; ++i){
            CRElement* newElement = new CRElement();
            //creates the link between the two elements, newElement->next is still nullptr
            newElement->previous = actualElement;
            actualElement->next = newElement;
            newElement->index = i;
            columnmap[i] = newElement;
        }
    }
}

/*
 * returns true if the insertion was a success, false otherwise
 */
template<typename T>
bool Matrix<T>::insertElement(T& elem, int row, int column) {
    //the position is: row*_maxAmountColumn + column where row and column are the result of the map as the position there is maybe not the actual position
    if(rowMap.find(row) && columnmap.find(column)){
        _matrix[ rowMap[row] * _maxAmountColumns + columnmap[column] ] = elem;
        return true;
    }
    return false;
}

template<typename T>
T& Matrix<T>::getElement(int column, int row) {
    return _matrix[rowMap[row] * _maxAmountColumns + columnmap[column] ];
}

template <typename T>
T& Matrix<T>::getElement(CRElement row, CRElement column) {
    return _matrix[row.index * _maxAmountColumns + column.index];
}

template <typename T>
T* Matrix<T>::getElementPointer(CRElement row, CRElement column) {
    return *_matrix[row.index * _maxAmountColumns + column.index];
}

template <typename T>
bool Matrix<T>::deleteColumn(int column) {
    if( !(column != -1 && columnmap.find(column)) ){
        return false;
    }
    CRElement* columnToDelete = columnmap.find(column);
    columnToDelete->next->previous = columnToDelete->previous;
    columnToDelete->previous->next = columnToDelete->next;
    columnmap.erase(columnToDelete);

    CRElement* rowElem = _firstRow;
    while(rowElem){
        delete getElementPointer(rowElem, columnToDelete);
        rowElem = rowElem->next;
    }
    delete columnToDelete;
    return true;
}

template<typename T>
bool Matrix<T>::deleteRow(int row) {
    if( !(row != -1 && rowMap.find(row)) ){
        return false;
    }
    CRElement* rowToDelete = rowMap.find(row);
    rowToDelete->next->previous = rowToDelete->previous;
    rowToDelete->previous->next = rowToDelete->next;
    columnmap.erase(rowToDelete);

    CRElement* columnElem = _firstColumn;
    while(columnElem){
        delete getElementPointer(rowToDelete, columnElem);
        columnElem = columnElem->next;
    }
    delete rowToDelete;
    return true;
}

template <typename T>
bool Matrix<T>::insertRow(int row) {
    int counter{0};
    CRElement *elem = _firstRow;
    std::vector<int> elementNumbers{};
    while(elem){
        elementNumbers.push_back(elem->index);
        elem = elem->next;
    }
    std::sort(elementNumbers.begin(), elementNumbers.end());
    //todo:: insert the CRElement: 1. is there is enough space? 2. what is the first free position? use it to add the CRElement with that index
}

template <typename T>
Matrix<T>::~Matrix() {
    //todo: delete CRElements, maps
    for(int i=0; i < _maxAmountColumns * _maxAmountRows; ++i){
        delete _matrix[i];
    }
    delete[] _matrix;
}

template<typename T>
void Matrix<T>::resize() {
    //todo: creates a bigger matrix (1.5* max sizes when they are nearly full), actualize all values
}
