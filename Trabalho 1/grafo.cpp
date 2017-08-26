#include <bits/stdc++.h>

using namespace std;
#define MAX 49

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

typedef struct Vertice {
  string Nome;
  int pk;
  vector<int> parentes;
}t_Vertice;

void mostra_grafo(vector<Vertice> g) {
  int size = g.size(),size2,i,j;

  for (i = 0; i < size; i++) {
    size2 = g[i].parentes.size();
    cout << g[i].pk << " ";
    cout << g[i].Nome;
    cout << " -> ";
    for (j=0;j<size2;j++) {
      if (j != size2-1) {
        cout << g[i].parentes[j] << " -> ";
      }
      else {
        cout << g[i].parentes[j];
      }
    }
    cout << endl;
  }
}

vector<string> leitura_arquivo() {
  vector<string> linhas(50);
  string linha;
  ifstream input( "nomes.txt" );
  int i, j = 0;

  for (;getline( input, linha );) {
    for (i = 0; i < (int)linha.size(); i++) {
      if (linha[i] != '|' && (linha[i] != ' ')) { // Pega o caracter e coloca na string
        linhas[j].push_back(linha[i]);
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

int main () {
  vector<Vertice> g(MAX);
  vector<string> linhas(50);  
  int i, j, k, size;
  string ch;
  
  linhas = leitura_arquivo();

  size = linhas.size();
  for (i = 0; i < size; i++) {
    for (j = 0; j < (int)linhas[i].size(); j++) {
      if (linhas[i][j] >= 48 && linhas[i][j] <= 57) {
        ch.push_back(linhas[i][j]);
      }
      else if (linhas[i][j] == ' ') {
        if (j<=2) {
          g[i].pk = atoi(ch.c_str());
        }
        else {
          g[i].parentes.push_back(atoi(ch.c_str()));
        }
        ch.clear();
      }
      else if (linhas[i][j] >= 65 && linhas[i][j] <= 90) {
        for (k=j;k<(int)linhas[i].size();k++) {
          g[i].Nome.push_back(linhas[i][k]);
        }
        j=k;
      }
    }
  }
  mostra_grafo(g);
}
