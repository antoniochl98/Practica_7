/*
 * nodoAVL.hpp
 *
 *  Created on: 16/05/2018
 *      Author: antonio
 */

#ifndef NODOAVL_HPP_
#define NODOAVL_HPP_

#include <iostream>

using namespace std;

template<class T>
class nodoAVL
{
public:
	T val_;
	nodoAVL<T> *left_;
	nodoAVL<T> *right_;
	int bal_;
	nodoAVL(T);
    nodoAVL(T, nodoAVL *, nodoAVL *);
    virtual ~nodoAVL();
    virtual void write(ostream& os=cout);
};

template<class T>
nodoAVL<T>::nodoAVL(T val):
val_(val),
left_(NULL),
right_(NULL),
bal_(0){}

template<class T>
nodoAVL<T>::nodoAVL(T val, nodoAVL *lft, nodoAVL *rgt):
val_(val),
left_(lft),
right_(rgt),
bal_(0){}

template<class T>
nodoAVL<T>::~nodoAVL(){
	left_=NULL;
	right_=NULL;
}

template<class T>
void nodoAVL<T>::write(ostream& os)
{
    os << val_ << " ";
}
#endif /* NODOAVL_HPP_ */
