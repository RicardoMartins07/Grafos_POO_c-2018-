#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include <list>
#include <map>
#include "as.h"
#include "No.h"
#include "qwe.h"
#include "Pessoa.h"
#include "Uteis.h"
#include <queue>
#include <functional>
#include "XMLWriter.h"
#include <stack>
#define INF 0x3f3f3f3f
#define NINF INT_MIN



// iPair ==>  Integer Pair 
typedef pair<int, int> iPair;

class Grafo
{
	map<No*, list<as*>*> arestas;  // lista adjacencia
	list<No*> nolist; //lista de todos os nos
	list<qwe*> listpessoas; //lista pessoas que vao percorrer o grafo
	list<pair<int, int>> listavisitas; //lista que vai guardar as visitas em cada vertice (1-no,2-visitas)

public:

	Grafo();
	//Implemente o destrutor do Grafo;
	~Grafo();
	//Carregar os dados de ficheiros (do grafo e de pessoas);
	bool Load(const string &fich_grafo, const string &fich_pessoas);//Feito
	//Contar o n�mero de n�s/fronteiras do grafo;
	int ContarNos();//Feito
	//Contar o n�mero de arestas/arcos do grafo;
	int ContarArcos();//Feito
	//Determinar toda a mem�ria ocupada;
	int Memoria();
	//Determinar qual o n�/fronteira que tem mais arcos/aresta, se existirem v�rios devolve uma lista deles;
	list<int> *NoMaisArcos();//Feito

	//Verificar se um n� � adjacente de outro n� do Grafo;
	bool Adjacencia(int v1, int v2);//Feito
	//Determinar um caminho(n�o interessa se � o mais r�pido!, � qualquer um!) de um n�/fronteira para outro.... //devolvendo o custo total;
	list<int> *Caminho(int v1, int v2, double &custo_total);
	//Determinar quais os v�rtices que est�o isolados (Um v�rtice � isolado se n�o existe nenhum caminho at� ele!);
	list<int> *VerticesIsolados();//Feito
	//Verificar se um dado v�rtice existe
	bool Search(int v);//Feito
	//Remover um dado v�rtice, tamb�m ser� necess�rio remover todas as arestas;
	bool RemoverVertice(int v);//Feito(rework)
	//Remover a aresta que liga 2 v�rtices;
	bool RemoverAresta(int v1, int v2);//Feito(rework)
	//Gravar para ficheiro em formato XML todas as informa��es do Grafo;
	void EscreverXML(const string &s);//Feito
	//Ler de um ficheiro em formato XML todo o Grafo (antes de ler deve ser apagado tudo o que estiver no Grafo); Se leu corretamente devolve //true, sen�o devolve false;
	bool LerXML(const string &s);
	//Devolver uma lista de todos os v�rtices/fronteiras de um dado tipo;
	list<int> *DevolveVerticesTipo(const string &tipo); //Feito
	//Determinar o caminho m�nimo entre 2 n�s, devolvendo o custo total;
	list<int> *CaminhoMinimo(int v1, int v2, double &custo_total);
	//Determinar o caminho m�ximo entre 2 n�s (passando somente uma vez em cada v�rtice), devolvendo o custo total;
	list<int> *CaminhoMaximo(int v1, int v2, double &custo_total);
	//Ser� poss�vel ir de uma fronteira(v1) a outra(v2), passando somente por fronteiras de um dado tipo?
	bool PossivelCaminho(int v1, int v2, int TipoFronteira);
	//Assumindo que todas as pessoas (do ficheiro) andaram em viagem, qual foi a fronteira com menos tr�fego/visitas? (No caso de serem v�rias,// deve devolver uma lista com as fronteiras);
	void FronteirasMenosVisitadas(list<int> &Lv);

	//Dada uma fronteira (v1), determinar todas as fronteiras onde n�o � poss�vel chegar apartir de v1. Deve devolver uma lista dessas fronteiras!;
	void SitiosInacessiveisAPartirDe(int V1, list<int> &Lv);



	void Mostrarlistapessoas();
	bool AddNo(int numero, int tipo);
	bool AddNo(No *n);
	bool AddPessoa(string nome,int partida,int chegada);
	bool AddPessoa(qwe *p);
	void listarno();
	No* searchno(int numero);
	qwe* searchqwe(int partida);
	void Mostrar();
	int determinar_maximo();
	void VerticesIsolados_search(int v, bool visited[]);
	void printCaminhoUtil(int u, int d, bool visited[],int path[], int &path_index,list<int> *l);
	bool SitiosInacessiveisUTIL(int v, int d);
	void Percorrer_Pessoas_grafo();
	void Percorrer_Pessoas_grafoUtil(int partida,int chegada , int mercadoria,qwe *p);
	void Percorrer_Pessoas_grafoUtil1(int u, int d, bool visited[], int path[], int &path_index,qwe *p);
	void colocarvisitas(int x);

	void inicializar_Vertices_nonficheiro();
	void inicializar_vistitaslist();
	void calcula_custoutil(int p, int c, double &custo);
	void calcula_custo(list<int> *l, double &custo);
	int determinar_minimo();
	bool possivel_caminhoutil(int u, int d, bool visited[], int path[], int &path_index, int tipo);
	void Escrever_caminho(int parent[], int j,list<int> *l);
	void Escrever_caminhomax(int parent[], int j, list<int> *l);
	void Inserir_listamax(int parent[], int j, list<int> *l);
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
	void positivo_negativo();
	
};