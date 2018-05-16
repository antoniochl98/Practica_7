#include"dni.hpp"
#include<iostream>
using namespace std;
int contador=0;

//variable global para las comparaciones
//rand() te genera un entero, como las claves DNI son numeros de 8 digitos , usamos unsigned long, que almacena numeros positivos muy grandes
//conviene tener un operador de conversion para poder transformar en unsigned long para cuando quieras transformar en unsigned long desde otra clase, por ejemplo, al hacer unsigned long = Dni b
  Dni::Dni(){

    numidentidad_= rand()%100000000;
    letra_='A'+(rand()%26);
    clave_=true;
  }
  Dni::Dni(bool b){

     numidentidad_= rand()%100000000;
     letra_='A'+(rand()%26);
     clave_=b;
   }

  Dni::Dni(int v,char c){
	  numidentidad_=v;
	  letra_=c;
	  clave_=true;
  }
  Dni::~Dni(){}
  bool operator==(Dni a, Dni b){
    contador++;
    if(a.numidentidad_==b.numidentidad_){
      return true;
    }
    else{
      return false;
    }
  }
  bool operator<(Dni a, Dni b){
    contador++;
    if(a.clave_){
    return a.numidentidad_<b.numidentidad_;
    }
    else{
      return a.letra_<b.letra_;
    }
  }
  Dni::operator unsigned long(){
    return this->numidentidad_;
  }
  ostream& Dni::write(ostream& os){
    os<<numidentidad_;
    os<<letra_;
    return os;
  }

  ostream& operator<<(ostream& os,Dni a){
	  a.write(os);
	  return os;
  }
