#pragma once
#include "Pessoa.h"
#include<iostream>
class qwe
{
	int partida = 0, chegada = 0, mercadoria = 0;
	Pessoa *P=NULL;
public:
	qwe(int partida , int chegada,Pessoa *p);
	~qwe();
	int getpartida();
	int getchegada();
	int getmercadoria();
	void mostrar();
	void atualizarmercadoria();
};

