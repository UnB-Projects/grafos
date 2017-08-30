#include <bits/stdc++.h>

using namespace std;

#define MAX 49

typedef struct Vertice {
  string Nome;
  int pk;
  vector<int> amigos;
}t_Vertice;

typedef vector<Vertice> Grafo;

vector<Grafo> maximalCliques; 

//Funcoes extras

bool comparaAmigos(Vertice a, Vertice b) {
  return a.amigos.size() > b.amigos.size();
}

bool comparaPK(Vertice a, Vertice b) {
  return a.pk < b.pk;
}

//Funcoes de grafo

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

vector<string> leitura_arquivo() {
  vector<string> linhas(50);
  string linha;
  ifstream input( "amigos_tag20172.txt" );
  int i, j = 0;

  for (;getline( input, linha );) { // Pega uma linha inteira do arquivo e coloca na string linha
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

void adicionaVertice(Grafo &g, string ch, int i) {
  g[i].pk = atoi(ch.c_str());
}

void adicionaAresta(Grafo &g, string ch, int i) {
  g[i].amigos.push_back(atoi(ch.c_str()));
}

void adicionaNome(Grafo &g, string ch, int i) {
  g[i].Nome = ch;
}

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

void mostraGrafoDecrescente(Grafo g) {
  int i;

  sort(g.begin(), g.end(), comparaAmigos);
  for (i = 0; i < (int)g.size(); i++) {
    cout << "Vertice: " << setw(2) << g[i].pk << " " 
         << "Grau: "    << setw(2) << g[i].amigos.size() << endl;
  }
}

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

void bronKerbosch (Grafo clique, Grafo adjacentes, Grafo repetidos) {
  Vertice pivo;

  if (adjacentes.empty() && repetidos.empty()) {
    maximalCliques.push_back(clique);
  }
  sort(adjacentes.begin(), adjacentes.end(), comparaAmigos);
  pivo =  adjacentes[0];
}

int main () {
  Grafo g(MAX);
  Grafo teste;
  Grafo teste2;
  Vertice testeVertice;

  montaGrafo(g);

  cout << "Inicio mostra_grafo" << endl;
  mostra_grafo(g);
  cout << "Fim mostra_grafo" << endl << endl;

  cout << "Inicio mostra_grafo decrescente" << endl;
  mostraGrafoDecrescente(g);
  cout << "Fim mostra_grafo decrescente" << endl << endl;


  //inicializacao de testes
  testeVertice.pk = 50;
  teste.push_back(testeVertice);
  testeVertice.pk = 0;
  teste.push_back(testeVertice);

  cout << "Inicio uniao" << endl;
  teste = uniaoVertices(teste, g);
  mostra_grafo(teste);
  cout << "Fim uniao" << endl;

  testeVertice.pk = 48;
  teste2.push_back(testeVertice);
  cout << "Inicio intersecao" << endl;
  teste = intersecaoVertices(g, teste2);
  mostra_grafo(teste);
  cout << "Fim intersecao" << endl;
}
