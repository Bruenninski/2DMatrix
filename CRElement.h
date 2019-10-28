//
// Created by brueni on 27.10.19.
//
/*
 * The C(olumn)R(ow)Element yields the information of the field index for the columns and rows and can be used like an iterator
 */
#ifndef UNTITLED1_CRELEMENT_H
#define UNTITLED1_CRELEMENT_H

class CRElement{
public:
    CRElement* next = nullptr;
    CRElement* previous = nullptr;
    int index;
};

#endif //UNTITLED1_CRELEMENT_H
