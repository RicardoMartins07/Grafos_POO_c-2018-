#include "as.h"





as::as(int custo, No * no)
{
	this->custo = custo;
	this->no = no;
}

as::~as()
{
	
	//cout << "No as destruido  com sucesso" << endl;
}

void as::Mostrar()
{
	cout << "MOSTRAR" << endl;
	no->mostrar();
	cout << "Ja mostrou" << endl;
	cout << "Custo:"<< custo << endl;

}

No * as::getno()
{
	return no;
}

int as::getcusto()
{
	return custo;
}

void as::alterarcusto()
{
	this->custo = (custo*-1);
}


