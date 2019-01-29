#pragma once
#include<string>
#include<iostream>

using namespace std;
class Pessoa
{
	string nome = "";
public:
	Pessoa(string nome);
	~Pessoa();
	string getNome();
};

