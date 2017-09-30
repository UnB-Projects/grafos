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
#include <algorithm> // Metodo atoi

using namespace std;

#define MAX 35 // Numero de disciplinas obrigatorias, consequentemente eh o tamanho do grafo.

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
  return linhas;
}

void montaGrafo(Grafo &g) {

  int i,j,k;
  int vetor_creditos[MAX], dificuldadeAux, vetor_posicoes[MAX];
  vector<string> linhas(MAX);
  linhas = leitura_arquivo();
  string auxiliar, ch;

  for (i=0;i<MAX;i++) {
    for (j=0;linhas[i][j] != ' ';j++) {
      auxiliar.push_back(linhas[i][j]);
    }
    k=j;
    while (!(linhas[i][k] >= '0' && linhas[i][k] <= '9')) { // Procura a posicao do proximo numero
      k++;
    }
    vetor_posicoes[i] = k; // E coloca no vetor a posicao do proximo numero

    adicionaVertice(g,auxiliar,i);
    auxiliar.clear();
  }
  for (i=0;i<MAX;i++) {
    ch = linhas[i][vetor_posicoes[i]];
    vetor_creditos[i] = atoi(ch.c_str());
    vetor_posicoes[i]++; // Avancamos o vetor de posicoes em 1, para ler a partir da proxima posicao
  }
  ch.clear();
  for (i=0;i<MAX;i++) {
    for (j=vetor_posicoes[i];j<(int)linhas[i].size();j++) {
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
  for (i = 0; i < (int)g.size(); i++) {
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

bool existe_na_lista(vector<Aresta> lista, int codigo) {
  int i;

  for (i = 0; i < (int)lista.size(); i++) {
    if (codigo == lista[i].first) {
      return true;
    }
  }
  return false;
}

Grafo ordenacao_topologica(Grafo g) {
  int i, j;
  int codigo; 
  bool flag;
  Grafo ordem;

  while (g.size() > 0) {
    for (i = 0; i < (int)g.size(); i++) {
      codigo = g[i].codigo;
      flag = false;

      for (j = 0; j < (int)g.size(); j++) {
        if (existe_na_lista(g[j].disciplinas, codigo)) {
          j = (int)g.size();
          flag = true;
        }
      }

      if (flag == false) {
        ordem.push_back(g[i]);
        g.erase(g.begin() + i);
        i--;
      }
    }
  }
  return ordem;
}

void mostra_caminho(Grafo grafo) { 
  int i;

  for (i = 0; i < (int)grafo.size(); i++) {
    if (i > 0) {
      cout << " -> ";
    }
    cout << grafo[i].codigo;
  }
  cout << endl;
}

int calculaDificuldade(Grafo ordem, Vertice vertice, vector<int> finalizar) {
  unsigned int i, j;
  int codigo = vertice.codigo;
  int dificuldade = 0;

  for (i = 0; i < ordem.size(); i++) {
    for (j = 0; j < ordem[i].disciplinas.size(); j++) {
      if (ordem[i].disciplinas[j].first == codigo) {
        dificuldade = max(dificuldade, finalizar[i] + ordem[i].disciplinas[j].second);
      }
    }
  }
  return dificuldade;
}

vector<int> dificuldade_de_finalizar(Grafo ordem) {
  vector<int> finalizar(MAX);
  unsigned int i;

  for (i = 0; i < finalizar.size(); i++) {
    finalizar[i] = calculaDificuldade(ordem, ordem[i], finalizar);
  }

  for (i = 0; i < finalizar.size(); i++) {
    cout << ordem[i].codigo << " Dificuldade associada: " << finalizar[i] << " " << endl;
  }

  return finalizar;
}

Grafo caminho_critico(Grafo ordem, vector<int> finalizar) {
  unsigned int i, j;
  int mais_dificil = 0;
  Vertice vertice;
  int codigo;
  int dificuldade;
  int maior;
  int index;
  bool flag;
  Grafo caminho;


  for (i = 0; i < finalizar.size(); i++) {
    if (finalizar[i] > mais_dificil) {
      mais_dificil = finalizar[i];
      index = i;
    }
  }

  vertice = ordem[index];
  codigo = vertice.codigo;

  caminho.push_back(vertice);

  for (i = 0; i < ordem.size(); i++) {
    dificuldade = -1;
    flag = false;
    for (j = 0; j < ordem[i].disciplinas.size(); j++) {
      if (ordem[i].disciplinas[j].first == codigo && finalizar[i] > dificuldade) {
        maior = i;
        dificuldade = finalizar[i];
        flag = true;
      }
    }

    if (flag == true) {
      caminho.insert(caminho.begin(), ordem[maior]);
      codigo = ordem[maior].codigo;
      i = -1;
    }
  }

  return caminho;
}

int main () {
  Grafo g(MAX);
  Grafo ordemTopologica;
  Grafo caminhoCritico;
  vector<int> finalizar;

  montaGrafo(g);
  cout << "===== GRAFO MONTADO =====" << endl << endl;

  mostra_grafo(g);

  ordemTopologica = ordenacao_topologica(g);

  cout << endl << "===== ORDENACAO TOPOLOGICA =====" << endl << endl;
  mostra_caminho(ordemTopologica);

  cout << endl << "===== DIFICULDADE ASSOCIADA A CADA VERTICE =====" << endl << endl;
  finalizar = dificuldade_de_finalizar(ordemTopologica);

  caminhoCritico = caminho_critico(ordemTopologica, finalizar);
  cout << endl << "===== CAMINHO CRITICO =====" << endl << endl;
  mostra_caminho(caminhoCritico);

  return 0;
}
