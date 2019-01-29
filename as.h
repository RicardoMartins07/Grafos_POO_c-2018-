#pragma once
#include "No.h"
class as
{
	No *no; 
	int custo;
public:
	as(int custo, No *no);
	~as();
	void Mostrar();
	No* getno();
	int getcusto();
	void alterarcusto();
	
};

