/*
 * main.cpp
 *
 *  Created on: 27/04/2018
 *      Author: antonio
 */
#include "arbolAVL.hpp"
#include "dni.hpp"
#include <vector>

using namespace std;

int main(){
	extern int contador;
	srand(time(NULL));
	bool mode;
	cout<<"[0] MODO DEMOSTRACIÓN  [1] MODO ESTADÍSTICO"<<endl<<"Elige una opción:";
	cin>>mode;
	ArbolAVL<Dni> tree;
	if(!mode){
		int op;
		do{
			cout<<"[0]SALIR"<<endl<<"[1]INSERTAR UN ELEMENTO"<<endl<<"[2]ELIMINAR UN ELEMENTO"<<endl;
			cin>>op;
			while(op<0 || op>2){
				cout<<"---------------OPCIÓN INVÁLIDA------------------"<<endl;
				cout<<"[0]SALIR"<<endl<<"[1]INSERTAR UN ELEMENTO"<<endl<<"[2]ELIMINAR UN ELEMENTO"<<endl;
				cin>>op;
			}
			if(op!=0){
				int val;
				char letra;
				cout<<"INTRODUZCA EL NÚMERO DEL DNI: ";
				cin>>val;
				cout<<"INTRODUZCA LA LETRA DEL DNI: ";
				cin>>letra;
				Dni a(val, letra);
				if(op==1){
					tree.insert(a);
				}
				else{
					tree.remove(a);
				}
				cout<<"ARBOL:"<<endl;
				tree.write();
				cout<<endl;
			}
		}while(op!=0);
	}
	else{
		int N, nPruebas, min, max;
		double med=0;
		cout<<"INTRODUZCA EL TAMAÑO DEL ÁRBOL: ";
		cin>>N;
		cout<<"INTRODUZCA EL NÚMERO DE PRUEBAS A EJECUTAR: ";
		cin>>nPruebas;
		vector<Dni> data_base;
		for(int i=0;i<2*N;i++){
			Dni a;
			data_base.push_back(a);
		}
		for(int i=0;i<N;i++){
			tree.insert(data_base[rand()%N]);
		}
		for(int i=0;i<nPruebas;i++){
			contador=0;
			tree.search(data_base[rand()%N]);
			if(i==0){
				min=contador;
				max=contador;
			}
			else{
				if(contador<min)
					min=contador;
				if(contador>max)
					max=contador;
			}
			double tmp=contador;
			med+=(tmp/nPruebas);
		}
		cout<<"		N	PRUEBAS	MIN	MAX	MED"<<endl;
		cout<<"BÚSQUEDA	"<<N<<"	"<<nPruebas<<"	"<<min<<"	"<<max<<"	"<<(int)med<<endl;

		med=0;
		for(int i=0;i<nPruebas;i++){
			contador=0;
			tree.insert(data_base[(rand()%N)+N]);
			if(i==0){
				min=contador;
				max=contador;
			}
			else{
				if(contador<min)
					min=contador;
				if(contador>max)
					max=contador;
			}
			double tmp=contador;
			med+=(tmp/nPruebas);
		}
		cout<<"		N	PRUEBAS	MIN	MAX	MED"<<endl;
		cout<<"INSERCION	"<<N<<"	"<<nPruebas<<"	"<<min<<"	"<<max<<"	"<<(int)med<<endl;
	}
}

