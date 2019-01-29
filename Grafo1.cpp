#include "Grafo1.h"


Grafo::Grafo()
{
	cout << "Passei em " << __FUNCTION__ << endl;
}

Grafo::~Grafo()
{	
	map<No*, list<as*> *>::iterator it1;
	for (it1 = arestas.begin(); it1 != arestas.end(); ++it1) {

		
		list<as*>::iterator itas;
		for (itas = (*(it1->second)).begin();
			itas != (*(it1->second)).end(); ++itas) {
			delete(*itas);
		}
		
	}

	for (list<No*>::iterator i = nolist.begin(); i != nolist.end(); i++)
	{
		delete(*i);
	}

	for (list<qwe*>::iterator it = listpessoas.begin(); it != listpessoas.end(); it++)
	{
		delete(*it);
	}

	listpessoas.clear();
	arestas.clear();
	nolist.clear();
	listavisitas.clear();

	cout << "Passei em " << __FUNCTION__ << endl;
}

//-------------------------------------------------------------------
//Método: Load
//Parametros:
// Entrada:
//     fich_grafo: Ficheiro dos dados do Grafo
//     fich_pessoas: Ficheiro das pessoas que querem fazer as viagens entre as fronteiras
// Retorno:
//    true/false, mediante a leitura correcta!
//-------------------------------------------------------------------
bool Grafo::Load(const string &fich_grafo, const string &fich_pessoas)
{
	string str;  //string armazenamento
	ifstream Ficheiro(fich_grafo.c_str());//abrir ficheiro grafo
	ifstream Ficheiro1(fich_pessoas.c_str());//abrir ficheiro pessoas
	int aux = 0;
	int n_vertices = 0;
	int n_arestas = 0;
	string campos="";
	Uteis U;
	
	for (int i = 0; i <2; i++)
	{
		if (i == 0) {
			getline(Ficheiro, str);
			U.split(str, "\n");
			n_vertices += atoi(U.GetElement(0).c_str());
		}

		if(i==1){
			getline(Ficheiro, str);
			U.split(str, "\n");
			n_arestas += atoi(U.GetElement(0).c_str());
		}
	}

	for (int j = 0; j < n_vertices; j++) {
		getline(Ficheiro, str);
		U.split(str, ";");
		int numero = atoi(U.GetElement(0).c_str()); // array to integer
		campos = U.GetElement(1);
		campos = U.GetElement(2);
		int tipo = atoi(U.GetElement(3).c_str());
		AddNo(numero, tipo);
	}

	for (int k = 0; k < n_arestas; k++)
	{
		getline(Ficheiro, str);
		U.split(str, ";");
		int nopartida = atoi(U.GetElement(0).c_str());
		int nochegada = atoi(U.GetElement(1).c_str());
		int custo = atoi(U.GetElement(2).c_str());
		as *as1 = new as(custo, searchno(nochegada));
		map<No*, list<as*> *>::iterator it = arestas.find(searchno(nopartida));
		list<as*> *Lista = NULL;

		if (it == arestas.end()) {    // não existe 
									  // criamos uma lista nova
			Lista = new list<as*>();
			arestas[searchno(nopartida)] = Lista;
		} 
		else
			Lista = it->second;

		Lista->push_back(as1);
	}
	 
	while (getline(Ficheiro1, str))
	{
		U.split(str, ";");
		string  nome = U.GetElement(1).c_str();
		int partida = atoi(U.GetElement(2).c_str());
		int destino = atoi(U.GetElement(3).c_str());
		AddPessoa(nome, partida, destino);
	}
		inicializar_Vertices_nonficheiro();
		inicializar_vistitaslist();
     	Ficheiro.close();
		Ficheiro1.close();
		return true;

}

int Grafo::ContarNos()
{
	return nolist.size();
}

int Grafo::ContarArcos()
{
	int aux = 0;
	map<No*, list<as*>*>::iterator it;
	for (it = arestas.begin(); it != arestas.end(); ++it)
	{
			aux += it->second->size();
	}

	return aux;
}

int Grafo::Memoria()
{
	//1-arestas.size*sizeof(No)
	//2-nolist.size*sizeof(No)
	//3-listpessoas.sizer*sizeof(qwe)
	//4- tamanho de todas as listas do map *sizeof(as)
	int n = 0;
	n = ContarArcos();
	

	return (arestas.size() * sizeof(No)) + (nolist.size() * sizeof(No)) + (listpessoas.size() * sizeof(qwe)) + (n * sizeof(as)) +((listavisitas.size()+2)*sizeof(int));
}

list<int>* Grafo::NoMaisArcos()
{
	int aux = 0;
	int no;
	int tamanho = determinar_maximo();
	map<No*, list<as*>*>::iterator it;
	list<int> *ListaNo_arcos = NULL;
	ListaNo_arcos = new list<int>();
	for (it = arestas.begin(); it != arestas.end(); ++it)
	{	
		if ((*it->second).size() == tamanho)
		{
			no = it->first->getnumero();
			ListaNo_arcos->push_back(no);
		}
	}
	list<int>::iterator itNo;
	return ListaNo_arcos;
}

bool Grafo::Adjacencia(int v1, int v2) // sao adjacentes se tiver uma ligacao de x para y(tirar duvida)
{
	map<No*, list<as*> *>::iterator it=arestas.find(searchno(v1));
			list<as*>::iterator itas;
			for (itas = (*(it->second)).begin();
				itas != (*(it->second)).end(); ++itas) {
				No *no = (*itas)->getno();
				int x = no->getnumero();
				if (x==v2)
				{
					return true;
				}
			}

			return false;
}


list<int>* Grafo::Caminho(int v1, int v2, double & custo_total)
{
	list<int> *Lista_caminho = NULL;
	Lista_caminho = new list<int>();
		
	if (!SitiosInacessiveisUTIL(v1, v2)) {
		cout << "Nao existe caminho de " << v1 << " para " << v2<<endl;
		return Lista_caminho;
	}

	bool *visited = new bool[nolist.size()];

	// Criar um array para guardar caminhos
	int *path = new int[nolist.size()];
	int path_index = 0; // inicializar vazio

						// Inicializar todos os vertices como nao visitados
	for (int i = 1; i <= nolist.size(); i++)
		visited[i] = false;
 
	printCaminhoUtil(v1, v2, visited, path, path_index,Lista_caminho);
	calcula_custo(Lista_caminho,custo_total);
	list<int>::iterator i;
	cout << "=============== CAMINHO ================" << endl;
	cout << "Caminho de "<<v1<<" para "<<v2<<": ";
	for ( i =Lista_caminho->begin(); i!= Lista_caminho->end(); i++)
	{
		cout << *i<<"->";
	}
	cout << "\ncusto Total: " << custo_total<<endl;
	cout << "========================================" << endl;
	return Lista_caminho;
}

void Grafo::calcula_custo(list<int> *l, double &custo) {
	list<int>::iterator it;
	for ( it = l->begin(); it!=l->end(); it++)
	{
		int x = *it;
		it++;
		if (it == l->end())break;
		int y = *it;
		it--;
		calcula_custoutil(x, y, custo);
	}
}

void Grafo::calcula_custoutil(int p,int c, double &custo) {
	map<No*, list<as*>*>::iterator it = arestas.find(searchno(p));

	list<as*> ::iterator itas;
	for ( itas = it->second->begin(); itas != it->second->end(); itas++)
	{
		No *no = (*itas)->getno();
		int x = no->getnumero();
		if (x==c)
		{
			custo += (*itas)->getcusto();
		}
	}
}


list<int>* Grafo::VerticesIsolados()
{
	list <int> *listvert;
	listvert = new list<int>();
	bool *visited = new bool[nolist.size()]; //cria um array booleano para controlar as "visitas"
	for (int i = 1; i <= nolist.size(); i++)
		visited[i] = false; //coloca todas as posiçoes falsas porque ainda nenhuma foi visitada

	for (int i = 1; i <= nolist.size(); i++)
	{
		if (visited[i] == false) //se for falsa 
		{
			VerticesIsolados_search(i, visited); //chama a função que vai colocar todos os atingiveis nos a true e volta 
			listvert->push_back(i);//percorrer o ciclo for e verificar quais ficaram a falso e insere na lista
		}
	}

	return listvert;
}


bool Grafo::Search(int v)
{
	list<No*>::iterator itNo;
	for (itNo = nolist.begin(); itNo != nolist.end(); itNo++) {
		if ((*itNo)->getnumero()==v)
		{
			return true;
		}
	}
	return false;
}

bool Grafo::RemoverVertice(int v)
{
		map<No*, list<as*> *>::iterator it = arestas.find(searchno(v));
		if (it == arestas.end())return false;
		arestas.erase(it); //remover o vertice v (Removeu todas as arestas que tinha com ele)
		for (it = arestas.begin(); it != arestas.end(); ++it) {
			
				list<as*>::iterator itas;
				for (itas = (*(it->second)).begin();
					itas != (*(it->second)).end(); ++itas) {
					No *no = (*itas)->getno();
					int x = no->getnumero();
					if (x == v)
					{
						(*(it->second)).erase(itas);
						break;
						//return true;
					}
				}
			}
		
}

bool Grafo::RemoverAresta(int v1, int v2)
{
	map<No*, list<as*> *>::iterator it;
	for (it = arestas.begin(); it != arestas.end(); ++it) { // it no começo do map
		if ((it->first)->getnumero() == v1 || (it->first)->getnumero() == v2)
		{
			list<as*>::iterator itas;
			for (itas = (*(it->second)).begin();
				itas != (*(it->second)).end(); ++itas) {
				No *no = (*itas)->getno();
				int x = no->getnumero();
				if (x == v2|| x==v1)
				{	
					(*(it->second)).erase(itas);//apaga da lista nao destroi (as)
					break;
				}
			}
		}
	}
	return false;

}

void Grafo::EscreverXML(const string & s)
{
	XMLWriter xml;
	map<No*, list<as*>*>::iterator it;
	list<as*>::iterator itas;
	list <No*>::iterator itno;
	if (xml.open(s)) {

		xml.writeOpenTag("Dados");
		for (itno = nolist.begin(); itno != nolist.end(); ++itno) {
			xml.write_endl();
			xml.writeOpenTag("Vertice");
			string x = to_string((*itno)->getnumero());
			string y = to_string((*itno)->get_tipo());
			xml.writeStartElementTag("Fronteira"); xml.writeString(x); xml.writeEndElementTag();
			xml.writeStartElementTag("Tipo"); xml.writeString(y); xml.writeEndElementTag();
			xml.writeCloseTag();
		}

		for (it = arestas.begin(); it != arestas.end(); ++it) {
			for (itas = (*(it->second)).begin();
				itas != (*(it->second)).end(); ++itas) {
				No *no = (*itas)->getno();
				string k = to_string(it->first->getnumero());
				string x = to_string(no->getnumero());
				string y = to_string(no->get_tipo());
				string z= to_string((*itas)->getcusto());
				xml.writeOpenTag("Arestas");
				xml.writeStartElementTag("Partida"); xml.writeString(k); xml.writeEndElementTag();
				xml.writeStartElementTag("Chegada"); xml.writeString(x); xml.writeEndElementTag();
				xml.writeStartElementTag("Tipo"); xml.writeString(y); xml.writeEndElementTag();
				xml.writeStartElementTag("Custo"); xml.writeString(z); xml.writeEndElementTag();
				xml.writeCloseTag();
			}
		}

		

		xml.writeCloseTag();

		xml.close();
		
	}
	else {
		std::cout << "Erro ao Abrir ficheiro.\n";
	}
	cout << "Passei em " << __FUNCTION__ << endl;
}

bool Grafo::LerXML(const string & s) // forma nao otimizada
{
	//1-Remover espaços brancos do inicio
	//2-Verificar se dentro da string se encontra a palavra Vertice se  sim colocar begin_tag true(para poder passar a leitura)
	//3-Verificar se dentro da string aparece a palavra Fronteira(armazenar o que esta la dentro)
	//4-Verificar se dentro da string aparece a palavra Tipo(armazenar o que esta la dentro)
	//5-Verificar se aparece a palavra arestas se sim colocar begin_tag2 true(para poder ler as arestas)
	//6- Armazenar as variaveis das arestas


	
	string line;
	ifstream in(s);
	if (!in.is_open())
	{
		cout << "Arquivo  nao existe ou erro na abertura!" << endl;
		cout << "Passei em " << __FUNCTION__ << endl;
		return false;
	}

	int numero1=0, tipo1=0, partida1=0, chegada1=0, custo1=0;
	bool begin_tag2 = false;
	bool begin_TagF = false;
	bool begin_TagT = false;
	bool begin_TagTp = false;
	bool begin_TagC = false;
	bool begin_TagP = false;
	bool begin_TagCu = false;
	bool begin_tag = false; 
	bool begin_Tagno = false;
	bool begin_Tagare = false;
	arestas.clear();
	nolist.clear();



	while (getline(in, line))
	{

		string tmp; // strip whitespaces from the beginning
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ' && tmp.size() == 0)
			{

			}
			else
			{
				tmp += line[i];
			}
		}

		//cout << "-->" << tmp << "<--" << endl;

		if (tmp == "<Vertice>")
		{
			begin_tag = true;
			continue;
		}
		else if (tmp == "</Vertice>")
		{
			begin_tag = false;
		}

		if (tmp == "<Arestas>")
		{
			begin_tag2 = true;
			continue;
		}
		else if (tmp == "</Arestas>")
		{
			begin_tag2 = false;
		}

		if (begin_tag)
		{
			if (tmp == "<Fronteira>") { begin_TagF = true; continue; }
			if (tmp == "</Fronteira>")begin_TagF = false;
			if (begin_TagF) { /*cout << "Esta e a fronteira " << tmp << endl; */numero1 = atoi(tmp.c_str()); }
			if (tmp == "<Tipo>") { begin_TagT = true; continue; }
			if (tmp == "</Tipo>") { begin_TagT = false; begin_Tagno = true; }
			if (begin_TagT) { /*cout << "Este e o Tipo " << tmp << endl;*/  tipo1 = atoi(tmp.c_str()); }
			if (begin_Tagno)
			{
				AddNo(numero1, tipo1);
				begin_Tagno = false;
			}
		}

		if (begin_tag2)
		{
			begin_tag = false;
			if (tmp == "<Partida>") { begin_TagP = true; continue; }
			if (tmp == "</Partida>")begin_TagP = false;
			if (begin_TagP) {/* cout << "Esta e a Partida " << tmp << endl;*/ partida1 = atoi(tmp.c_str()); }
			if (tmp == "<Chegada>") { begin_TagC = true; continue; }
			if (tmp == "</Chegada>")begin_TagC = false;
			if (begin_TagC) { /*cout << "Este e a Chegada " << tmp << endl;*/ chegada1 = atoi(tmp.c_str()); }
			if (tmp == "<Tipo>") { begin_TagTp = true; continue; }
			if (tmp == "</Tipo>")begin_TagTp = false;
			if (begin_TagTp) { /*cout << "Este e o Tipo da chegada " << tmp << endl;*/ tipo1 = atoi(tmp.c_str()); }
			if (tmp == "<Custo>") { begin_TagCu = true; continue; }
			if (tmp == "</Custo>") { begin_TagCu = false; begin_Tagare = true; }
			if (begin_TagCu) { /*cout << "Este e o Custo " << tmp << endl;*/ custo1 = atoi(tmp.c_str()); }
			if (begin_Tagare)
			{
				as *as1 = new as(custo1, searchno(chegada1));
				map<No*, list<as*> *>::iterator it = arestas.find(searchno(partida1));
				list<as*> *Lista = NULL;

				if (it == arestas.end()) {    // não existe 
											  // criamos uma lista nova
					Lista = new list<as*>();
					arestas[searchno(partida1)] = Lista;
				} //deixa de fazer sentido pois em cima colocamos todos no map
				else
					Lista = it->second;

				Lista->push_back(as1);
				begin_Tagare = false;
			}
		}
	}
	inicializar_Vertices_nonficheiro();
	cout << "Passei em " << __FUNCTION__ << endl;
	return true;
}






list<int>* Grafo::DevolveVerticesTipo(const string &tipo)
{
	list<No*>::iterator itNo;
	int aux = 0;
	list<int> *Listatipo =NULL;
	Listatipo= new list<int>();
	for (itNo = nolist.begin(); itNo != nolist.end(); itNo++) {
		if (to_string((*itNo)->get_tipo()) == tipo)
		{
			aux = (*itNo)->getnumero();
			Listatipo->push_back(aux);
		}
	}
	return Listatipo;
}

list<int>* Grafo::CaminhoMinimo(int v1, int v2, double & custo_total) //Djikstra algorithm 
{
	list<int> *ListaCaminho_minimo = NULL;
	ListaCaminho_minimo = new list<int>();
	custo_total = 0;

	if (!SitiosInacessiveisUTIL(v1,v2))
	{
		cout << "Nao existe caminho de " << v1 << " para " << v2 << endl;
		return false;
	}

	int k = nolist.size();
	int parent[25];
	parent[v1] = -1;

	//Crear umaa priority queue para guardar os vertices que vao ser processados
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

	// vetor de distancias Iniciados todos a INF (Djikstra)
	vector<int> dist(nolist.size()+1, INF);

	// Inserir a partida na priority queue 
	// Distancia a ele mesmo 0 
	pq.push(make_pair(0, v1));
	dist[v1] = 0;

	// Correr enquanto a queue nao estiver vazia ou quando todas as distancias forem finalizadas
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		// 'i' Para ver a adjacencia
		map<No*, list<as*>*>::iterator i = arestas.find(searchno(u));
		list<as*>::iterator itas;
		for (itas = (*(i->second)).begin();
			itas != (*(i->second)).end(); ++itas) {
			
			No *no = (*itas)->getno();
			int v = no->getnumero();
			int weight = (*itas)->getcusto();
			//  Se houver algum caminho mais curto para v atraves de u 
			if (dist[v] > dist[u] + weight)
			{
				// atualizar distancia v
				parent[v] = u;
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	ListaCaminho_minimo->push_back(v1);
	custo_total = dist[v2];
	cout << "============================== Caminho minimo =======================================" << endl;
	cout << "Vertice\t" <<"Distancia Minima \t" << "Caminho" << endl;
	cout << v1 << "->" << v2 << "\t\t" << dist[v2];
	cout << "\t\t"<<v1; Escrever_caminho(parent, v2,ListaCaminho_minimo);
	cout << endl;
	cout << "=====================================================================================" << endl;

	/*for (list<int>::iterator i = ListaCaminho_minimo->begin(); i !=ListaCaminho_minimo->end() ; i++)
	{
		cout << "aqui dentro esta" << *i << endl;
	}*/


	return ListaCaminho_minimo;
}

list<int>* Grafo::CaminhoMaximo(int v1, int v2, double & custo_total)
{
	list<int> *ListaCaminho_maximo = NULL;
	ListaCaminho_maximo = new list<int>();
	custo_total = 0;

	if (!SitiosInacessiveisUTIL(v1, v2))
	{
		cout << "Nao existe caminho de " << v1 << " para " << v2 << endl;
		return false;
	}

	int parent[25];
	parent[v1] = -1;

	stack<int> Stack;
	int dist[25];

	// Mark all the vertices as not visited 
	bool* visited = new bool[25];
	for (int i = 0; i <nolist.size(); i++)
		visited[i] = false;

	// Call the recursive helper function to store Topological 
	// Sort starting from all vertices one by one 
	for (int i = 0; i < nolist.size(); i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	// Initialize distances to all vertices as infinite and 
	// distance to source as 0 
	for (int i = 0; i < nolist.size(); i++)
		dist[i] = NINF;
	dist[v1] = 0;

	// Process vertices in topological order 
	while (Stack.empty() == false) {
		// Get the next vertex from topological order 
		int u = Stack.top();
		Stack.pop();

		// Update distances of all adjacent vertices 
		map<No*, list<as*>*>::iterator it = arestas.find(searchno(u));
		if (dist[u] != NINF) {
			list<as*>::iterator i;
			for (i = (*(it->second)).begin(); i != (*(it->second)).end(); ++i) {
				No *no = (*i)->getno();
				int v = no->getnumero();
				if (dist[v] < dist[u] + (*i)->getcusto()) {
					dist[v] = dist[u] + (*i)->getcusto();
					parent[v] = u;
				}
			}
		}
	}

	

	ListaCaminho_maximo->push_back(v1);
	Inserir_listamax(parent, v2, ListaCaminho_maximo);
	calcula_custo(ListaCaminho_maximo, custo_total);
	cout << "============================== Caminho maximo =======================================" << endl;
	cout << "Vertice\t" << "Distancia Maximo \t" << "Caminho" << endl;
	cout << v1 << "->" << v2 << "\t\t" << custo_total;
	cout << "\t\t" << v1; Escrever_caminhomax(parent, v2, ListaCaminho_maximo);
	cout << endl;
	cout << "=====================================================================================" << endl;
	

	/*for (list<int>::iterator i = ListaCaminho_maximo->begin(); i !=ListaCaminho_maximo->end() ; i++)
	{
	cout << "aqui dentro esta" << *i << endl;
	}*/


	return ListaCaminho_maximo;
	
}

void Grafo::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
	// Mark the current node as visited
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	map<No*, list<as*>*>::iterator i = arestas.find(searchno(v));
	for ( i ; i!=arestas.end(); i++)
	{
		list<as*>::iterator itas;
		for (itas = (*(i->second)).begin();
			itas != (*(i->second)).end(); ++itas) {
			No* no = (*itas)->getno();
			int x = no->getnumero();
			if (!visited[x])
				topologicalSortUtil(x, visited, Stack);
		}
	}
	

	// Push current vertex to stack which stores topological sort
	Stack.push(v);
}

void Grafo::Escrever_caminho(int parent[], int j,list<int> *l) {
	
		// Base Case : If j is source
		if (parent[j] == -1)
			return;

		Escrever_caminho(parent, parent[j],l);
		l->push_back(j);
		cout << "->";
		cout << j;
		
	
}

void Grafo::Escrever_caminhomax(int parent[], int j, list<int> *l) {

	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	Escrever_caminhomax(parent, parent[j], l);
	cout << "->";
	cout << j;


}

void Grafo::Inserir_listamax(int parent[], int j, list<int>* l)
{
	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	Inserir_listamax(parent, parent[j], l);
	l->push_back(j);
}





int Grafo::determinar_minimo() {

	int aux = 0;
	list<pair<int, int>>::iterator itpa=listavisitas.begin();
	aux=itpa->second;
	for (itpa = listavisitas.begin(); itpa != listavisitas.end(); itpa++)
	{
		if (itpa->second<aux)
		{
			aux = itpa->second;
		}

	}
	return aux;
}

bool Grafo::possivel_caminhoutil(int u, int d, bool visited[], int path[], int & path_index, int tipo)
{
	// Marcar como visitado e guardar em path[] 
	visited[u] = true;
	path[path_index] = u;
	path_index++;
	bool n = false;
	
	


	// se for o vertice de destino entao escreve
	//  path[] 
	if (u == d)
	{
		
		return true;
	}

	else // se nao for o vertice de destino
	{

		// verificar todos os vertices adjacentes a este vertice 
		map<No*, list<as*>*>::iterator i = arestas.find(searchno(u));

		list<as*>::iterator it1;
		for (it1 = (*(i->second)).begin(); it1 != (*(i->second)).end(); ++it1) {
			No *no = (*it1)->getno();
			int x = no->getnumero();
			map<No*, list<as*>*>::iterator it = arestas.find(searchno(x));
			
				if (!visited[x]) {
					if (no->get_tipo() == tipo)
					{
						return possivel_caminhoutil(x, d, visited, path, path_index, tipo);
						
					
					}

				}


		}
		return false;
	}


	//Nao esta a executar sequer Problema aqui!!!
	// Remover vertice de path[] e marcar como nao visitado
	path_index--;
	visited[u] = false;
	
}


bool Grafo::PossivelCaminho(int v1, int v2, int TipoFronteira)
{ 
	bool *visited = new bool[nolist.size()];

	// Criar um array para guardar caminhos
	int *path = new int[nolist.size()];
	int path_index = 0; // inicializar vazio

						// Inicializar todos os vertices como nao visitados
	for (int i = 1; i <= nolist.size(); i++)
		visited[i] = false;

	if (!SitiosInacessiveisUTIL(v1, v2)) {
		cout << "Nao existe caminho de " << v1 << " para " << v2 << endl;
		return false;
	}

	else if (possivel_caminhoutil(v1,v2, visited, path, path_index,TipoFronteira))return true;
	return false;
}

void Grafo::FronteirasMenosVisitadas(list<int>& Lv)//corigir
{
	int n = determinar_minimo();
	list<pair<int, int>>::iterator itpa;
	Percorrer_Pessoas_grafo();
	for ( itpa =listavisitas.begin(); itpa!=listavisitas.end(); itpa++)
	{ 
		if (itpa->second== n)
		{
			Lv.push_back(itpa->first);
		}
		
	}
	
}

void Grafo::SitiosInacessiveisAPartirDe(int V1, list<int>& Lv)
{
	cout << "===================== Sitios Inacessiveis Apartir de "<< V1 <<" ========================" << endl;
	for (int i = 1; i <= nolist.size(); i++)
	{
		if (!SitiosInacessiveisUTIL(V1, i)) { Lv.push_back(i);  cout <<"No "<< i << endl; };
	}
	cout << "==================================================================================" << endl;
}

void Grafo::Mostrarlistapessoas()
{
	list<qwe*> ::iterator it;
	for ( it=listpessoas.begin(); it!=listpessoas.end(); it++)
	{
		(*it)->mostrar();
	}
}

bool Grafo::AddNo(int numero, int tipo)
{
		AddNo(new No(numero,tipo));
		return true;
}

bool Grafo::AddPessoa(qwe *p)
{
	if (p == NULL)return false;
	listpessoas.push_back(p);
	return true;
}

bool Grafo::AddPessoa(string nome,int partida,int chegada)
{
	Pessoa *p =new Pessoa(nome);
	AddPessoa(new qwe(partida,chegada,p));
	return true;
}

bool Grafo::AddNo(No * n)
{
	if (n == NULL)return false;
	nolist.push_back(n);
	return true;
}
void Grafo::listarno() {
	list<No*>::iterator itNo;
	for (itNo = nolist.begin(); itNo != nolist.end(); itNo++) {
		(*itNo)->mostrar();
	}
}

No* Grafo::searchno(int numero)
{
	list<No*>::iterator itNo;
	for (itNo = nolist.begin(); itNo != nolist.end(); itNo++) {
		if ((*itNo)->getnumero()==numero)
		{
			return (*itNo);
		}
	}
	return NULL;
}

qwe* Grafo::searchqwe(int partida) {
	list<qwe*>::iterator itP;
	for (itP = listpessoas.begin(); itP != listpessoas.end(); itP++) {
		if ((*itP)->getpartida() == partida)
		{
			return (*itP);
		}
	}
	return NULL;
}

void Grafo::Mostrar()
{
	
	// percorrer todos nos
	map<No*, list<as*> *>::iterator it;
	for (it = arestas.begin(); it != arestas.end(); ++it) {
		(it->first)->mostrar();

		// para cada no mostrar caminho
		list<as*>::iterator itas;
		for (itas = (*(it->second)).begin();
			itas != (*(it->second)).end(); ++itas) {
			(*itas)->Mostrar(); 
		}
	}
}

int Grafo::determinar_maximo()
{
	int aux = 0;
	map<No*, list<as*>*>::iterator it;
	for (it = arestas.begin(); it != arestas.end(); ++it)
	{
		if ((*it->second).size() > aux)
		{
			aux = (*it->second).size();
		}
	}
	return aux;
}


void Grafo::VerticesIsolados_search(int v, bool visited[])
{
	visited[v] = true;  //coloca v a true (como se tivesse sido visitado)
	
	map<No*, list<as*>*>::iterator i;
	for (i = arestas.begin(); i != arestas.end(); ++i) {
			list<as*>::iterator it;
			for (it = (*(i->second)).begin(); it != (*(i->second)).end(); ++it) {
				No *no = (*it)->getno();
				int x = no->getnumero();
				if (!visited[x]) { 
					VerticesIsolados_search(x, visited);//Recursividade , caso seja falso visited[x] vai chamar a função
										//e coloca a true
				}
			}
		}
}

void Grafo::printCaminhoUtil(int u, int d, bool visited[], int path[], int & path_index,list<int> *l)
{
	int aux = 0;
	// Marcar como visitado e guardar em path[] 
	visited[u] = true;
	path[path_index] = u;
	path_index++;


	// se for o vertice de destino entao escreve
	//  path[] 
	if (u == d)
	{
		for (int i = 0; i < path_index; i++) 
			l->push_back(path[i]);
		
		return;
	}

	else // se nao for o vertice de destino
	{

		// verificar todos os vertices adjacentes a este vertice 
		map<No*, list<as*>*>::iterator i = arestas.find(searchno(u));
		
			list<as*>::iterator it1;
			for (it1 = (*(i->second)).begin(); it1 != (*(i->second)).end(); ++it1) {
				No *no = (*it1)->getno();
				int x = no->getnumero();
				map<No*, list<as*>*>::iterator it = arestas.find(searchno(x));
					if (!visited[x]) {
						//custo += (*it1)->getcusto(); // dar fix do custo
						//aux = (*it1)->getcusto();
						printCaminhoUtil(x, d, visited, path, path_index, l);
						
					}
					
				
					
			}
		}

	
	
	// Remover vertice de path[] e marcar como nao visitado
	path_index--;
	visited[u] = false;

}



bool Grafo::SitiosInacessiveisUTIL(int v, int d)
{
	// Base case 
	if (v == d)
		return true;

	// Mark all the vertices as not visited 
	bool *visited = new bool[nolist.size()];
	for (int i = 1; i <= nolist.size(); i++)
		visited[i] = false;

	// Create a queue for BFS 
	list<int> queue;

	// Mark the current node as visited and enqueue it 
	visited[v] = true;
	queue.push_back(v);

	// it will be used to get all adjacent vertices of a vertex 
	map<No*, list<as*>*>::iterator i = arestas.find(searchno(v));
	if (i == arestas.end())//Se vertice v nao tiver nenhuma ligacao com outro vertice return false
	{
		return false;
	}

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		v = queue.front();
		queue.pop_front();
		i = arestas.find(searchno(v));

		// Get all adjacent vertices of the dequeued vertex s 
		// If a adjacent has not been visited, then mark it visited 
		// and enqueue it 
	

			int x;
			list<as*>::iterator it1 = (*(i->second)).begin(); //erro aqui verificar
			for (it1; it1 != (*(i->second)).end(); ++it1) {
				No *no = (*it1)->getno();
				x = no->getnumero();
				map<No*, list<as*>*>::iterator it = arestas.find(searchno(x));
	
					// If this adjacent node is the destination node, then  
					// return true 
					if (x == d) {
						return true;
					}


					// Else, continue to do BFS 
					if (!visited[x])
					{
						visited[x] = true;
						queue.push_back(x);
					}

			}
			 
		}
	

	// If BFS is complete without visiting d 
	return false;
	
}

void Grafo::Percorrer_Pessoas_grafo()
{
	list<qwe*>::iterator itp;
	for ( itp = listpessoas.begin(); itp!= listpessoas.end(); itp++)
	{
		int partida=(*itp)->getpartida();
		int chegada=(*itp)->getchegada();
		int mercadoria=(*itp)->getmercadoria();
		qwe *p = searchqwe(partida);
		Percorrer_Pessoas_grafoUtil(partida, chegada, mercadoria,p);
	}
}

void Grafo::Percorrer_Pessoas_grafoUtil(int partida, int chegada, int mercadoria,qwe *p)
{
	if (!SitiosInacessiveisUTIL(partida, chegada)) {
		cout << "Nao existe caminho de " << partida << " para " << chegada << endl;
		return;
	}

	bool *visited = new bool[nolist.size()];

	// Criar um array para guardar caminhos
	int *path = new int[nolist.size()];
	int path_index = 0; // inicializar vazio

						// Inicializar todos os vertices como nao visitados
	for (int i = 1; i <= nolist.size(); i++)
		visited[i] = false;

	Percorrer_Pessoas_grafoUtil1(partida, chegada, visited, path, path_index,p);
	
}

void Grafo::Percorrer_Pessoas_grafoUtil1(int u, int d, bool visited[], int path[], int & path_index,qwe *p)
{
	int aux = 0;
	// Marcar como visitado e guardar em path[] 
	visited[u] = true;
	path[path_index] = u;
	path_index++;
	
	

	// se for o vertice de destino entao escreve
	//  path[] 
	if (u == d)
	{
		return;
	}

	else // se nao for o vertice de destino
	{

		// verificar todos os vertices adjacentes a este vertice 
		map<No*, list<as*>*>::iterator i = arestas.find(searchno(u));

		list<as*>::iterator it1;
		for (it1 = (*(i->second)).begin(); it1 != (*(i->second)).end(); ++it1) {
			No *no = (*it1)->getno();
			int x = no->getnumero();
			int y = no->get_tipo();
			map<No*, list<as*>*>::iterator it = arestas.find(searchno(x));

			if (!visited[x]) {
				if (p->getmercadoria()>10)
				{
					break;
				}
				if (y==2)
				{
					p->atualizarmercadoria();
				}
				colocarvisitas(x);
				Percorrer_Pessoas_grafoUtil1(x, d, visited, path, path_index,p);

			}


		}
	}


	//Nao esta a executar sequer Problema aqui!!!
	// Remover vertice de path[] e marcar como nao visitado
	path_index--;
	visited[u] = false;

}

void Grafo::colocarvisitas(int x)
{
	list<pair<int, int>>::iterator i;
	for ( i = listavisitas.begin(); i != listavisitas.end(); i++)
	{
		if (i->first == x)
		{
			i->second++;
		}
	}
}

void Grafo::inicializar_Vertices_nonficheiro()
{
	list<No*>::iterator i = nolist.begin();
	for ( i ; i != nolist.end(); i++)
	{
		int x=(*i)->getnumero();
		map<No*, list<as*> *>::iterator it = arestas.find(searchno(x));
		list<as*> *Lista = NULL;

		if (it == arestas.end()) {    // não existe 
									  // criamos uma lista nova
			Lista = new list<as*>();
			arestas[searchno(x)] = Lista;
		}
	}
}

void Grafo::inicializar_vistitaslist()
{
	list<pair<int, int>>::iterator itpair;
	int i = 1;
	
	while (i<=nolist.size())
	{
		listavisitas.push_back(make_pair(i,0));
		i++;
	}

}






