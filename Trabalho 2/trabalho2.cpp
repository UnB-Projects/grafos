//Trabalho 2 da Disciplina Teoria e Aplicação de Grafos - Turma A
//Integrantes
//Nome: Igor Figueira Pinheiro da Silva
//Matricula: 15/0129921

//Nome: Tiago Rodrigues da Cunha Cabral
//Matricula: 15/0150296

// Lista de bibliotecas incluidas
#include <iostream> // biblioteca de input e output padrao do c++
#include <string> // biblioteca padrao de strings do c++
#include <fstream> // Utilizado o ifstream, para leitura do arquivo
#include <vector> // Estrutura do vector, utilizada no grafo
#include <iomanip> // Metodo setw
#include <algorithm> // Metodo sort

using namespace std;

#define MAX 50 // Tamanho do grafo.
int SizeGraph = MAX; // A principio tem o tamanho maximo permitido.

typedef pair<int,int> Aresta; // Uma aresta eh um pair da seguinte forma: <Disciplina,Peso da Aresta>
typedef struct Vertice { //Definicao da estrutura de um vertice
  int codigo;                //Identificador unico de cada vertice
  vector<Aresta> disciplinas;    //Lista de conexoes (arestas)
}t_Vertice;

typedef vector<Vertice> Grafo; //Um grafo eh definido como um conjunto de vertices

//Prototipos de funcoes

vector<string> leitura_arquivo();
void montaGrafo(Grafo&);
void adicionaVertice(Grafo&, string, int);
void adicionaAresta(Grafo&, string, int, int, int);
void mostra_grafo(Grafo);

//Funcao de leitura do arquivo
vector<string> leitura_arquivo() {
  vector<string> linhas(MAX);
  string linha;
  ifstream input( "file.txt" );
  int i,j=0;
  while (getline( input, linha )) { // Pega uma linha inteira do arquivo e coloca na string linha
    for (i=0;i<(int)linha.size();i++) {
      if ((linha[i] >= 'A' && linha[i] <= 'Z')) {
        while (linha[i] != '|') {
          i++;
        }
      }else {
        linhas[j].push_back(linha[i]);
      }
    }
    j++;
  }

  SizeGraph = j; // Variavel global para mostrar apenas os elementos ocupados do grafo.
  // Se quiser pode mudar Igor.

  return linhas;
}

void montaGrafo(Grafo &g) {

  int i,j;
  int vetor_creditos[SizeGraph], dificuldadeAux;
  vector<string> linhas(SizeGraph);
  linhas = leitura_arquivo();
  string auxiliar, ch;

  for (i=0;i<SizeGraph;i++) {
    for (j=0;linhas[i][j] != ' ';j++) {
      auxiliar.push_back(linhas[i][j]);
    }
    adicionaVertice(g,auxiliar,i);
    auxiliar.clear();
  }
  for (i=0;i<SizeGraph;i++) {
    // 9 eh a posicao do numero de creditos, e guarda estes em um vetor auxiliar.
    ch = linhas[i][9];
    vetor_creditos[i] = atoi(ch.c_str());
  }
  ch.clear();
  for (i=0;i<SizeGraph;i++) {
    for (j=12;j<(int)linhas[i].size();j++) {
      if (linhas[i][j] >= '0' && linhas[i][j] <= '9') {
        while (linhas[i][j] >= '0' && linhas[i][j] <= '9') {
          auxiliar.push_back(linhas[i][j]);
          j++;
        }
        while (!(linhas[i][j] >= '0' && linhas[i][j] <= '9')) {
          j++;
        }
        ch = linhas[i][j];
        dificuldadeAux = atoi(ch.c_str());
        adicionaAresta(g,auxiliar,dificuldadeAux,i,vetor_creditos[i]);
      }
      auxiliar.clear();
      ch.clear();
    }
  }
}


void adicionaVertice(Grafo &g, string ch, int i) { //Funcao que adiciona um vertice a lista de vertices
  g[i].codigo = atoi(ch.c_str());
}

void adicionaAresta(Grafo &g, string auxiliar, int dificuldadeAux, int i, int creditos) {
  string ch;
  ch = auxiliar;
  int aux = atoi(ch.c_str());
  g[i].disciplinas.push_back(make_pair(aux,dificuldadeAux*creditos));
}

void mostra_grafo(Grafo g) { //Funcao que recebe um grafo e o imprime na tela

  int i,j;
  for (i = 0; i < SizeGraph; i++) {
    cout << g[i].codigo << " -> ";
    for (j=0;j<(int)g[i].disciplinas.size();j++) {
      if (j != (int)g[i].disciplinas.size() - 1) {
        cout << " ( " << g[i].disciplinas[j].first << "," << g[i].disciplinas[j].second << " )" << " -> ";
      }else {
        cout << " ( " << g[i].disciplinas[j].first << "," << g[i].disciplinas[j].second << " )";
      }
    }
    cout << endl;
  }
}

int main () {

  Grafo g(MAX);

  montaGrafo(g);

  mostra_grafo(g);

  return 0;
}