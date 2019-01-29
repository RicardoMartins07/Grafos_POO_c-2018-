#include "Pessoa.h"






Pessoa::Pessoa(string nome)
{
	this->nome = nome;
}

Pessoa::~Pessoa()
{
	//cout << "Pessoa destruido  com sucesso" << endl;
}

string Pessoa::getNome()
{
	return nome;
}
