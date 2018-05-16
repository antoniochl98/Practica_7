/*
 * arbolAVL.hpp
 *
 *  Created on: 16/05/2018
 *      Author: antonio
 */

#ifndef arbol_HPP_
#define arbol_HPP_

#include <iostream>
#include "nodoAVL.hpp"
#include <queue>
#include <utility>

using namespace std;

template<class T>
class ArbolAVL{
private:
    nodoAVL<T> *raiz;


public:
    ArbolAVL();
    ~ArbolAVL();
    bool search(T val);
    bool searchBranch(nodoAVL<T>* nodo, T val);
    //insert
    void insert(T val);
    //remove
    void remove(T val);
    //balanceo
    void insert_rebalancing_left(nodoAVL<T>* &nodo, bool& increase);
    void insert_rebalancing_right(nodoAVL<T>* &nodo, bool& increase);
    void remove_rebalancing_left(nodoAVL<T>* &nodo, bool &decrease);
    void remove_rebalancing_right(nodoAVL<T>* &nodo, bool &decrease);
    //Visualizar
	void write(ostream& os=cout);
private:
	void destroy(nodoAVL<T>* &nodo);
	//insert
	void inserta_bal_(nodoAVL<T>* &nodo, nodoAVL<T>* nuevo,bool& increase);
	//remove
	void removeBranch(nodoAVL<T>* &nodo, T val, bool& decrease);
	void swap(nodoAVL<T>* &eliminado, nodoAVL<T>* &sust, bool &decrease);
	 //Rotar
	void rotation_LL(nodoAVL<T>* &nodo);
	void rotation_RR(nodoAVL<T>* &nodo);
	void rotation_LR(nodoAVL<T>* &nodo);
	void rotation_RL(nodoAVL<T>* &nodo);

};

template<class T>
ArbolAVL<T>::ArbolAVL(): raiz(NULL){
    }

template<class T>
ArbolAVL<T>::~ArbolAVL(){
    destroy(raiz);
}

template<class T>
void ArbolAVL<T>::destroy(nodoAVL<T>* &nodo){
    if(nodo == NULL){
        return;
    }
    destroy(nodo->left_); //Poda el subarbol izquierdo
    destroy(nodo->right_); //Poda el subarbol derecho
    delete nodo; //Elimina el nodo
    nodo = NULL;
}

template<class T>
bool ArbolAVL<T>::search(T val){
    return searchBranch(raiz, val);
}

template<class T>
bool ArbolAVL<T>::searchBranch(nodoAVL<T> *nodo, T val){
    if(nodo == NULL){
        return false;
    }

    if(val == nodo->val_){
        return true;
    }

    if(val < nodo->val_){
        return searchBranch(nodo->left_, val);
    }

    return searchBranch(nodo->right_, val);
}

template<class T>
void ArbolAVL<T>::insert(T val){
    nodoAVL<T> *nuevo = new nodoAVL<T>(val);
    bool increase = false;
    inserta_bal_(raiz, nuevo, increase);
}

template<class T>
void ArbolAVL<T>::inserta_bal_(nodoAVL<T>* &nodo, nodoAVL<T>* nuevo, bool& increase){
    if(nodo == NULL){
        nodo = nuevo;
        increase = true;
    }
    else if(nuevo->val_ < nodo->val_){
        inserta_bal_(nodo->left_, nuevo, increase);
        if(increase){
            insert_rebalancing_left(nodo, increase);
        }
    }
    else{
        inserta_bal_(nodo->right_, nuevo, increase);
        if(increase){
            insert_rebalancing_right(nodo, increase);
        }
    }
}

template<class T>
void ArbolAVL<T>::remove(T val){
    bool decrease = false;
    removeBranch(raiz, val, decrease);
}

template<class T>
void ArbolAVL<T>::removeBranch(nodoAVL<T>* &nodo, T val, bool& decrease){
    if(nodo == NULL){
        return;
    }
    if(val < nodo->val_){
        removeBranch(nodo->left_, val, decrease);
        if(decrease)
        {
            remove_rebalancing_left(nodo, decrease);
        }
    }
    else if(val > nodo->val_){
        removeBranch(nodo->right_, val, decrease);
        if(decrease){
            remove_rebalancing_right(nodo, decrease);
        }
    }
    else{
        nodoAVL<T> *Eliminando = nodo;
        if(nodo->left_ == NULL){
            nodo = nodo->right_;
            decrease = true;
        }
        else if(nodo->right_ == NULL){
            nodo = nodo->left_;
            decrease = true;
        }
        else{
            swap(Eliminando, nodo->left_, decrease);
            if(decrease){
                remove_rebalancing_left(nodo, decrease);
            }
        }
        delete (Eliminando);
    }
}

template<class T>
void ArbolAVL<T>::swap(nodoAVL<T>* &eliminado, nodoAVL<T>* &sust, bool &decrease){
    if(sust->right_ != NULL){
        swap(eliminado, sust->right_, decrease);
        if(decrease){
            remove_rebalancing_right(sust, decrease);
        }
    }
    else{
        eliminado->val_ = sust->val_;
        eliminado = sust;
        sust = sust->left_;
        decrease = true;
    }
}

template<class T>
void ArbolAVL<T>::insert_rebalancing_left(nodoAVL<T>* &nodo, bool& increase){
    switch(nodo->bal_){
    case -1:{
            nodo->bal_ = 0;
            increase = false;
        }break;
    case 0:{
            nodo->bal_ = 1;
        }break;
    case 1:{
            nodoAVL<T>* nodo1 = nodo->left_;
            if(nodo1->bal_ == 1)
            {
                rotation_LL(nodo);
            }
            else
            {
                rotation_LR(nodo);
            }
            increase = false;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::insert_rebalancing_right(nodoAVL<T>* &nodo, bool& increase){
    switch(nodo->bal_){
    case 1:{
            nodo->bal_ = 0;
            increase = false;
        }break;
    case 0:{
            nodo->bal_ = -1;
        }break;
    case -1:{
            nodoAVL<T>* nodo1 = nodo->right_;
            if(nodo1->bal_ == -1)
            {
                rotation_RR(nodo);
            }
            else
            {
                rotation_RL(nodo);
            }
            increase = false;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::remove_rebalancing_left(nodoAVL<T>* &nodo, bool &decrease)
{
    switch(nodo->bal_){
    case -1:{
            nodoAVL<T> *nodo1 = nodo->right_;
            if(nodo1->bal_ > 0){
                rotation_RL(nodo);
            }
            else{
                if(nodo1->bal_ == 0){
                    decrease = false;
                }
                rotation_RR(nodo);
            }
        }break;
    case 0:{
            nodo->bal_ = -1;
            decrease = false;
        }break;
    case 1:{
            nodo->bal_ = 0;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::remove_rebalancing_right(nodoAVL<T>* &nodo, bool &decrease)
{
    switch(nodo->bal_){
    case 1:{
            nodoAVL<T> *nodo1 = nodo->left_;
            if(nodo1->bal_ < 0){
                rotation_LR(nodo);
            }
            else{
                if(nodo1->bal_ == 0){
                    decrease = false;
                }
                rotation_LL(nodo);
            }
        }break;
    case 0:{
            nodo->bal_ = 1;
            decrease = false;
        }break;
    case -1:{
            nodo->bal_ = 0;
        }break;
    }
}

template<class T>
void ArbolAVL<T>::rotation_LL(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->left_;
    nodo->left_ = nodo1->right_;
    nodo1->right_ = nodo;

    if(nodo1->bal_ == 1){
        nodo->bal_ = 0;
        nodo1->bal_ = 0;
    }
    else{
        nodo->bal_ = 1;
        nodo1->bal_ = -1;
    }
    nodo = nodo1;
}

template<class T>
void ArbolAVL<T>::rotation_RR(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->right_;
    nodo->right_ = nodo1->left_;
    nodo1->left_ = nodo;

    if(nodo1->bal_ == -1){
        nodo->bal_ = 0;
        nodo1->bal_ = 0;
    }
    else{
        nodo->bal_ = -1;
        nodo1->bal_ = 1;
    }
    nodo = nodo1;
}

template<class T>
void ArbolAVL<T>::rotation_LR(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->left_;
    nodoAVL<T>* nodo2 = nodo1->right_;
    nodo->left_ = nodo2->right_;
    nodo2->right_ = nodo;
    nodo1->right_ = nodo2->left_;
    nodo2->left_ = nodo1;

    if(nodo2->bal_ == -1){
        nodo1->bal_ = 1;
    }
    else{
        nodo1->bal_ = 0;
    }
    if(nodo2->bal_ == 1){
        nodo->bal_ = -1;
    }
    else{
        nodo->bal_ = 0;
    }
    nodo2->bal_ = 0;
    nodo = nodo2;
}

template<class T>
void ArbolAVL<T>::rotation_RL(nodoAVL<T>* &nodo){
    nodoAVL<T>* nodo1 = nodo->right_;
    nodoAVL<T>* nodo2 = nodo1->left_;
    nodo->right_ = nodo2->left_;
    nodo2->left_ = nodo;
    nodo1->left_ = nodo2->right_;
    nodo2->right_ = nodo1;

    if(nodo2->bal_ == 1){
        nodo1->bal_ = -1;
    }
    else{
        nodo1->bal_ = 0;
    }
    if(nodo2->bal_ == -1){
        nodo->bal_ = 1;
    }
    else{
        nodo->bal_ = 0;
    }
    nodo2->bal_ = 0;
    nodo = nodo2;
}

template<class T>
void ArbolAVL<T>::write(ostream& os){
    queue<pair<nodoAVL<T>*,int>* > cola;
    nodoAVL<T> *nodo;

    int n_level = 0;
    int level = 0;

    cola.push(new pair<nodoAVL<T>*,int>(raiz,0));
    os <<"nivel "<<level<<":";
    while(!cola.empty()){
        n_level = cola.front()->second;
        nodo = cola.front()->first;
        cola.pop();
        if(n_level > level){
            level = n_level;
            os << endl;
            os <<"nivel "<<level<<":";
        }
        if(nodo != NULL){
        	nodo->write(os);
            cola.push(new pair<nodoAVL<T>*,int>(nodo->left_, n_level+1));
            cola.push(new pair<nodoAVL<T>*,int>(nodo->right_, n_level+1));
        }
        else{
            os << "[.]";
        }
    }
}

#endif /* arbol_HPP_ */
