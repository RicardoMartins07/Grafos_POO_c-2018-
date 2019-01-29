#include <iostream>
using namespace std;
#include "Grafo1.h"
#include"No.h"

int main()
{
	cout << "Inicio do Programa" << endl;
	//while (true)
	//{
		Grafo *GF;
		double custo_total = 0;
		list <int> li;
		list <int> lv;
		GF = new Grafo();
		GF->Load("grafo_3.txt", "pessoas.txt");//Trocar para grafo_2.txt e grafo_3.txt para testar varios grafos
		cout << "Numero de nos:" << GF->ContarNos() << endl;
		cout << "Numero de arcos:" << GF->ContarArcos() << endl;
		cout << "Memoria total ocupada :" << GF->Memoria() << " bytes" << endl;
		GF->NoMaisArcos();
		if (GF->Adjacencia(1, 2)) cout << "sao adjacentes" << endl;
		else cout << "Nao sao adjacentes" << endl;
		GF->Caminho(1, 6, custo_total);
		GF->VerticesIsolados();
		if (GF->Search(6)) cout << "Existe este vertice" << endl;
		else cout << "Nao existe o vertice" << endl;
		GF->RemoverVertice(10);
		GF->RemoverAresta(6, 5);
		GF->EscreverXML("dados.xml");
		GF->LerXML("dados.xml");
		GF->DevolveVerticesTipo("2");
		GF->CaminhoMinimo(12,8,custo_total);
		GF->CaminhoMaximo(12,8,custo_total);
		if (GF->PossivelCaminho(21, 19, 2))cout << "E possivel Percorrer este caminho por o tipo de fronteira indicado" << endl;
		else cout << "Nao e possivel Percorrer este caminho por o tipo de fronteira indicado" << endl;
		GF->FronteirasMenosVisitadas(lv);
		GF->SitiosInacessiveisAPartirDe(12, li);//(VERIFICAR AMANHA)

		delete GF;
	//}

	return 1;
}