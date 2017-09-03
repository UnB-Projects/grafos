//Trabalho 1 da Disciplina Teoria e Aplicação de Grafos - Turma A
//Integrantes
//Nome: Igor Figueira Pinheiro da Silva
//Matricula: 15/0129921

//Nome: Tiago Rodrigues da Cunha Cabral
//Matricula: 15/0150296

#include <bits/stdc++.h>

using namespace std;

#define MAX 49

typedef struct Vertice { //Definicao da estrutura de um vertice
  string Nome;           //Nome dos alunos
  int pk;                //Identificador unico de cada vertice
  vector<int> amigos;    //Lista de conexoes (arestas)
}t_Vertice;

typedef vector<Vertice> Grafo; //Um grafo eh definido como um conjunto de vertices

//Prototipos de funcoes

vector<string> leitura_arquivo();
void adicionaVertice(Grafo&, string, int);
void adicionaAresta(Grafo&, string, int);
void adicionaNome(Grafo&, string, int);
void montaGrafo(Grafo&);
void mostra_grafo(Grafo);
void mostraGrafoDecrescente(Grafo);
void mostraCliques();
void bronKerbosch (Grafo, Grafo, Grafo, Grafo);
Grafo uniaoVertices(Grafo, Grafo);
Grafo intersecaoVertices(Grafo, Grafo);
Grafo complementarVertices(Grafo, Grafo);
Grafo vizinhosVertice(Grafo, Vertice);
bool comparaAmigos(Vertice, Vertice);
bool comparaPK(Vertice, Vertice);
bool comparaCliques(Grafo, Grafo);

//Grafo de cliques maximos

vector<Grafo> maximalCliques; 

int main () {
  Grafo g(MAX);
  Grafo R;
  Grafo X;

  montaGrafo(g);

  cout << "////// Listas de Adjacencias //////" << endl << endl;
  mostra_grafo(g);

  cout << endl << "////// Grafo ordenado por numero de amigos //////" << endl << endl;
  mostraGrafoDecrescente(g);

  bronKerbosch(g, R, g, X);
  mostraCliques();
}

//Funcao de leitura do arquivo
vector<string> leitura_arquivo() {
  vector<string> linhas(50);
  string linha;
  ifstream input( "amigos_tag20172.txt" );
  int i, j = 0;

  while (getline( input, linha )) { // Pega uma linha inteira do arquivo e coloca na string linha
    for (i = 0; i < (int)linha.size(); i++) {
      if (linha[i] != '|' && (linha[i] != ' ')) { // Pega o caracter e coloca na string
        linhas[j].push_back(linha[i]); // Seleciona apenas os caracteres e numeros da linha e coloca na string linhas.
      }
      else {
        if (*linhas[j].rbegin() != ' ') { // Tira dois espaços, que vem das primeiras duas barras (|) do arquivo texto
          linhas[j].push_back(' '); // É só frescura msm '-'
        }
      }
    }
    j++;
  }
  return linhas;
}

//Funcoes principais do trabalho
void montaGrafo(Grafo &g) {
  vector<string> linhas(50);
  int i, j, k, size;
  string ch;

  linhas = leitura_arquivo();
  size = linhas.size();

  for (i = 0; i < size; i++) {
    for (j = 0; j < (int)linhas[i].size(); j++) {
      if (linhas[i][j] >= '0' && linhas[i][j] <= '9') { //Se for digito numerico
        ch.push_back(linhas[i][j]);
      }
      else if (linhas[i][j] == ' ') {
        if (j <= 2) { //Eh um dos digitos identificadores
          adicionaVertice(g, ch, i);
        }
        else if (ch.compare("0") != 0) { //Se o identificador numerico nao for de zero amigos
          adicionaAresta(g, ch, i);
        }
        ch.clear();
      }
      else if (linhas[i][j] >= 'A' && linhas[i][j] <= 'Z') { // Se for caractere
        // Loop que coloca em uma string auxiliar ch, todos os caracteres até o final do arquivo
        for (k = j; k <(int)linhas[i].size(); k++) {
          ch.push_back(linhas[i][k]);
        }
        adicionaNome(g, ch, i);
        ch.clear();
        j = k;
      }
    }
  }
}

void adicionaVertice(Grafo &g, string ch, int i) { //Funcao que adiciona um vertice a lista de vertices
  g[i].pk = atoi(ch.c_str());
}

void adicionaAresta(Grafo &g, string ch, int i) { //Funcao que adiciona um vertice a uma lista de adjacencias de outros vertice, formando uma aresta
  g[i].amigos.push_back(atoi(ch.c_str()));
}

void adicionaNome(Grafo &g, string ch, int i) { //Funcao que adiciona o atributo nome de determinado vertice
  g[i].Nome = ch;
}

void mostra_grafo(Grafo g) { //Funcao que recebe um grafo e o imprime na tela
  int size = g.size();
  int size2;
  int i, j;

  for (i = 0; i < size; i++) {
    size2 = g[i].amigos.size();
    cout << g[i].pk << " ";
    cout << g[i].Nome;
    cout << " -> ";
    for (j = 0; j < size2; j++) {
      if (j != size2-1) {
        cout << g[i].amigos[j] << " -> ";
      }
      else {
        cout << g[i].amigos[j];
      }
    }
    cout << endl;
  }
}

void mostraGrafoDecrescente(Grafo g) {
  int i;

  sort(g.begin(), g.end(), comparaAmigos); //Ordenacao de grafo por grau dos vertices
  for (i = 0; i < (int)g.size(); i++) {
    cout << "Vertice: " << setw(2) << g[i].pk << " " 
         << "Grau: "    << setw(2) << g[i].amigos.size() << endl;
  }
}

void mostraCliques() { //Funcao que mostra dois dos cliques guardados na variavel maximalCliques
  int i;

  sort(maximalCliques.begin(), maximalCliques.end(), comparaCliques); //Ordenacao da lista de cliques por numero de ligacoes simultaneas em cada clique

  cout << endl << "////// Clique maximal do grafo por nomes //////" << endl << endl;
  for (i = 0; i < (int)maximalCliques[8].size(); i++) { //O clique 8 foi escolhido como representante de um clique maximal
    if (i > 0) {
      cout << " - ";
    }
    cout << maximalCliques[8][i].Nome;
  }
  cout << endl << endl;

  cout << "////// Clique Maximo do grafo por nomes //////" << endl << endl;
  for (i = 0; i < (int)maximalCliques[0].size(); i++) { //O clique 0 foi escolhido como exemplo de um clique maximo
    if (i > 0) {
      cout << " - ";
    }
    cout << maximalCliques[0][i].Nome;
  }
  cout << endl;
}

void bronKerbosch (Grafo g, Grafo R, Grafo P, Grafo X) { //Implementacao do algoritmo de BronKerbosch com pivotamento
  Vertice pivo;
  Grafo uniao;
  Grafo vizinhosPivo;
  Grafo verticesComplementares;
  Grafo conjuntoV;
  int i = 0;

  if (P.empty() && X.empty()) { //Caso o conjunto de vertices P e X estejam vazios, o conjunto de vertices R eh um clique
    maximalCliques.push_back(R);
    return;
  }

  uniao = uniaoVertices(P, X); //A variavel uniao recebe a uniao do conjunto de vertices P e X
  sort(uniao.begin(), uniao.end(), comparaAmigos); //Lista de uniao eh ordenada de acordo com o grau de cada vertice
  pivo = uniao[0]; //O pivo selecionado eh o vertice de maior grau

  vizinhosPivo = vizinhosVertice(g, pivo); //vizinhosPivo recebe todos os vertices que estao na lista de adjacencia do pivo


  verticesComplementares = complementarVertices(P, vizinhosPivo); //verticesComplementares recebe o conjunto de vertices complementares P (complementar) Vizinhos(pivo)

  for (i = 0; i < (int)verticesComplementares.size(); i++) { //Havera uma chamada recursiva de bronKerbosch para cada vertice no conjunto complementar P \ Vizinhos(pivo)
    conjuntoV.push_back(verticesComplementares[i]); //O vertice da atual iteracao eh encapsulado em um conjunto de vertices para ser usado nas funcoes de conjunto

    bronKerbosch(g, uniaoVertices(R, conjuntoV), //Cada chamada recursiva de bronKerbosch recebe o grafo principal para consultas, (R (uniao) vertice atual do loop)
                 intersecaoVertices(P, vizinhosVertice(g, verticesComplementares[i])), // P (intersecao) vizinhos do vertice atual do loop
                 intersecaoVertices(X, vizinhosVertice(g, verticesComplementares[i])));// X (intersecao) vizinhos do vertice atual do loop

    P = complementarVertices(P, conjuntoV); //No final das chamadas recursivas do loop, P recebe P (complementar) vertice atual do loop
    X = uniaoVertices(X, conjuntoV); // X recebe X (uniao) vertice atual do loop

    conjuntoV.clear(); //conjuntoV eh esvaziado para ser conter apenas um vertice no loop seguinte
  }
}

//Funcoes auxiliares de Bron Kerbosch
Grafo uniaoVertices(Grafo x, Grafo y) { //Funcao que recebe dois conjuntos de vertices e retorna a uniao deles
  Grafo uniao;
  int i, j;

  uniao = x;

  i = 0;
  j = 0;

  while (i < (int)x.size() && j < (int)y.size()) {
    if (y[j].pk < uniao[i].pk) { //O numero identificar de cada vertice eh utilizado na escolha dos vertices da uniao
      uniao.push_back(y[j]);
      j++;
    }
    else if (y[j].pk > uniao[i].pk) {
      i++;
    }
    else {
      i++;
      j++;
    }
  }

  while (j < (int)y.size()) {
    uniao.push_back(y[j]);
    j++;
  }

  sort(uniao.begin(), uniao.end(), comparaPK);

  return uniao;
}

Grafo intersecaoVertices(Grafo x, Grafo y) { //Funcao que recebe dois conjuntos de vertices e retorna a intersecao deles
  Grafo intersecao;
  int i, j;

  i = 0;
  j = 0;
  while (i < (int)x.size() && j < (int)y.size()) {
    if (x[i].pk < y[j].pk) { //O numero identificar de cada vertice eh utilizado na escolha dos vertices da intersecao
      i++;
    }
    else if (x[i].pk > y[j].pk) {
      j++;
    }
    else {
      intersecao.push_back(x[i]);
      i++;
      j++;
    }
  }

  return intersecao;
}

Grafo complementarVertices(Grafo x, Grafo y) { //Funcao que recebe dois conjuntos de vertices e retorna primeiro (complementar) segundo
  Grafo intersecao;
  Grafo complementar;
  int i, j;

  intersecao = intersecaoVertices(x, y);

  i = 0;
  j = 0;
  while (i < (int)x.size() && j < (int)intersecao.size()) {
    while (i < (int)x.size() && x[i].pk < intersecao[j].pk) { //O numero identificar de cada vertice eh utilizado na escolha dos vertices complementares
      complementar.push_back(x[i]);
      i++;
    }
    if (x[i].pk != intersecao[j].pk) {
      complementar.push_back(x[i]);
    }
    else {
      i++;
    }
    j++;
  }

  while (i < (int)x.size()) {
    complementar.push_back(x[i]);
    i++;
  }

  return complementar;
}

Grafo vizinhosVertice(Grafo g, Vertice v) { //Funcao que recebe o grafo princial para consulta e um vertice V, e retorna um conjunto de vertices com os vizinhos de v
  int i;
  Grafo vizinhos;

  for (i = 0; i < (int)v.amigos.size(); i++) {
    vizinhos.push_back(g[v.amigos[i]-1]);
  }

  return vizinhos;
}

//Funcoes de comparacao
bool comparaAmigos(Vertice a, Vertice b) { //Compara por grau (decrescente)
  return a.amigos.size() > b.amigos.size();
}

bool comparaPK(Vertice a, Vertice b) {    //Compara por identificador (crescente)
  return a.pk < b.pk;
}

bool comparaCliques(Grafo a, Grafo b) {   //Compara por numero de vertices (decrescente)
  return a.size() > b.size();
}
