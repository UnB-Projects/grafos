#include <bits/stdc++.h>

using namespace std;

#define MAX 49

typedef struct Vertice {
  string Nome;
  int pk;
  vector<int> amigos;
}t_Vertice;

typedef vector<Vertice> Grafo;

//prototipos

bool comparaAmigos(Vertice, Vertice);
bool comparaPK(Vertice, Vertice);
void mostra_grafo(Grafo);
vector<string> leitura_arquivo();
void adicionaVertice(Grafo&, string, int);
void adicionaAresta(Grafo&, string, int);
void adicionaNome(Grafo&, string, int);
void montaGrafo(Grafo&);
void mostraGrafoDecrescente(Grafo);
Grafo uniaoVertices(Grafo, Grafo);
Grafo intersecaoVertices(Grafo, Grafo);
Grafo complementarVertices(Grafo, Grafo);
Grafo vizinhosVertice(Grafo, Vertice);
void bronKerbosch (Grafo, Grafo, Grafo, Grafo);
bool comparaCliques(Grafo, Grafo);
void mostraCliques();

//Grafo de cliques maximos

vector<Grafo> maximalCliques; 

int main () {
  Grafo g(MAX);
  Grafo R;
  Grafo X;
  Grafo teste;
  Grafo teste2;
  Grafo teste3;
  Vertice testeVertice;

  montaGrafo(g);

  cout << "Inicio mostra_grafo" << endl;
  mostra_grafo(g);
  cout << "Fim mostra_grafo" << endl << endl;

  cout << "Inicio mostra_grafo decrescente" << endl;
  mostraGrafoDecrescente(g);
  cout << "Fim mostra_grafo decrescente" << endl << endl;

  bronKerbosch(g, R, g, X);

  sort(maximalCliques.begin(), maximalCliques.end(), comparaCliques);

  mostraCliques();
}

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
        // Loop que coloca em uma string auxiliar ch todos os caracteres, até o final do arquivo
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

void adicionaVertice(Grafo &g, string ch, int i) {
  g[i].pk = atoi(ch.c_str());
}

void adicionaAresta(Grafo &g, string ch, int i) {
  g[i].amigos.push_back(atoi(ch.c_str()));
}

void adicionaNome(Grafo &g, string ch, int i) {
  g[i].Nome = ch;
}

void mostra_grafo(Grafo g) {
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

  sort(g.begin(), g.end(), comparaAmigos);
  for (i = 0; i < (int)g.size(); i++) {
    cout << "Vertice: " << setw(2) << g[i].pk << " " 
         << "Grau: "    << setw(2) << g[i].amigos.size() << endl;
  }
}

void mostraCliques() {
  int i;

  cout << "Clique Maximal do grafo por nomes:" << endl << endl;
  for (i = 0; i < (int)maximalCliques[8].size(); i++) {
    if (i > 0) {
      cout << " - ";
    }
    cout << maximalCliques[8][i].Nome;
  }
  cout << endl << endl;

  cout << "Clique Maximo do grafo por nomes:" << endl << endl;
  for (i = 0; i < (int)maximalCliques[0].size(); i++) {
    if (i > 0) {
      cout << " - ";
    }
    cout << maximalCliques[0][i].Nome;
  }
  cout << endl;
}

void bronKerbosch (Grafo g, Grafo R, Grafo P, Grafo X) {
  Vertice pivo;
  Grafo uniao;
  Grafo vizinhosPivo;
  Grafo verticesComplementares;
  Grafo conjuntoV;
  int i = 0;

  if (P.empty() && X.empty()) {
    maximalCliques.push_back(R);
    return;
  }

  uniao = uniaoVertices(P, X);
  sort(uniao.begin(), uniao.end(), comparaAmigos);
  pivo = uniao[0];

  vizinhosPivo = vizinhosVertice(g, pivo);


  verticesComplementares = complementarVertices(P, vizinhosPivo);

  for (i = 0; i < (int)verticesComplementares.size(); i++) {
    conjuntoV.push_back(verticesComplementares[i]);

    bronKerbosch(g, uniaoVertices(R, conjuntoV),
                 intersecaoVertices(P, vizinhosVertice(g, verticesComplementares[i])),
                 intersecaoVertices(X, vizinhosVertice(g, verticesComplementares[i])));

    P = complementarVertices(P, conjuntoV);
    X = uniaoVertices(X, conjuntoV);

    conjuntoV.clear();
  }
}

//Funcoes auxiliares de Bron Kerbosch
Grafo uniaoVertices(Grafo x, Grafo y) {
  Grafo uniao;
  int i, j;

  uniao = x;

  i = 0;
  j = 0;

  while (i < (int)x.size() && j < (int)y.size()) {
    if (y[j].pk < uniao[i].pk) {
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

Grafo intersecaoVertices(Grafo x, Grafo y) {
  Grafo intersecao;
  int i, j;

  i = 0;
  j = 0;
  while (i < (int)x.size() && j < (int)y.size()) {
    if (x[i].pk < y[j].pk) {
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

Grafo complementarVertices(Grafo x, Grafo y) {
  Grafo intersecao;
  Grafo complementar;
  int i, j;

  intersecao = intersecaoVertices(x, y);

  i = 0;
  j = 0;
  while (i < (int)x.size() && j < (int)intersecao.size()) {
    while (i < (int)x.size() && x[i].pk < intersecao[j].pk) {
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

Grafo vizinhosVertice(Grafo g, Vertice v) {
  int i;
  Grafo vizinhos;

  for (i = 0; i < (int)v.amigos.size(); i++) {
    vizinhos.push_back(g[v.amigos[i]-1]);
  }

  return vizinhos;
}

//Funcoes de comparacao
bool comparaAmigos(Vertice a, Vertice b) {
  return a.amigos.size() > b.amigos.size();
}

bool comparaPK(Vertice a, Vertice b) {
  return a.pk < b.pk;
}

bool comparaCliques(Grafo a, Grafo b) {
  return a.size() > b.size();
}
