#include "No.h"





No::No(int numero, int tipo)
{
	this->numero = numero;
	this->tipo = tipo;
	//cout << "No criado com sucesso" << endl;
}

No::~No()
{
	//cout<<"No destruido  com sucesso"<<endl;
}

void No::mostrar()
{
	cout << "======== NO ========" << endl;
	cout << numero << endl;
	cout << tipo << endl;
}

int No::getnumero()
{
	return numero;
}

int No::get_tipo()
{
	return tipo;
}


