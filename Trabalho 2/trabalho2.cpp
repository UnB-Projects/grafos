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

typedef int Aresta[2]; // Uma aresta eh um array da seguinte forma: [Disciplina,Peso da Aresta]
typedef struct Vertice { //Definicao da estrutura de um vertice
  int codigo;                //Identificador unico de cada vertice
  vector<Aresta> disciplinas;    //Lista de conexoes (arestas)
}t_Vertice;

typedef vector<Vertice> Grafo; //Um grafo eh definido como um conjunto de vertices

//Prototipos de funcoes

vector<string> leitura_arquivo();
void montaGrafo(Grafo&);

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

  int i;

  vector<string> linhas(MAX);
  linhas = leitura_arquivo();


  for (i=0;i<SizeGraph;i++) {
    cout << linhas[i] << endl;
  }

}

int main () {

  Grafo g(MAX);

  montaGrafo(g);

  return 0;
}
