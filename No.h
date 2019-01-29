#pragma once
#include<iostream>
#include<string>
#include<list>
using namespace std;
class No
{
	int numero;
	int tipo;
public:
	No(int numero , int tipo);
	~No();
	void mostrar();
	int getnumero();
	int get_tipo();
};

