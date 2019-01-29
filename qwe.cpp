#include "qwe.h"





qwe::qwe(int partida, int chegada, Pessoa * p)
{
	this->partida = partida;
	this->chegada = chegada;
	this->mercadoria = 0;
	this->P = p;
}

qwe::~qwe()
{
	delete(P);
	//cout << "qwe destruido  com sucesso" << endl;
}

int qwe::getpartida()
{
	return partida;
}

int qwe::getchegada()
{
	return chegada;
}

int qwe::getmercadoria()
{
	return  mercadoria;
}

void qwe::mostrar()
{
	cout << "NOME:" << P->getNome()<<endl;
	cout << "Partida" << partida << endl;
	cout << "Chegada:" << chegada<<endl;
	cout << "Mercadoria:" << mercadoria<<endl;
}

void qwe::atualizarmercadoria()
{
	mercadoria++;
}
