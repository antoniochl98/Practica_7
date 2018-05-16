
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdlib.h>
using namespace std;


class Dni{
private:
  unsigned long numidentidad_;
  char letra_;
  bool clave_;
public:
  Dni();
  Dni(bool);
  Dni(int,char);
  ~Dni();
  friend bool operator==(Dni a,Dni b);
  friend bool operator<(Dni a, Dni b);
  operator unsigned long();
  friend ostream& operator<<(ostream& os,Dni a);
  ostream& write(ostream& os);
};
