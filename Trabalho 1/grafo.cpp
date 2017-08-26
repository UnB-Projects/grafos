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

vector<Vertice> g(MAX);

void mostra_grafo() {
  int sz = g.size(),sz2,i,j;
  for (i=0;i<sz;i++) {
    sz2 = g[i].parentes.size();
    cout << g[i].pk << " ";
    cout << g[i].Nome;
    cout << " -> ";
    for (j=0;j<sz2;j++) {
      if (j != sz2-1) {
        cout << g[i].parentes[j] << " -> ";
      }else {
        cout << g[i].parentes[j];
      }
    }
    cout << endl;
  }
}

int main () {
  int j=0,i,k,sz;
  ifstream input( "nomes.txt" );
  string linha, ch;
  vector<string> linhas(50);
  for (;getline( input, linha );) {
    for (int i=0;i<(int)linha.size();i++) {
      if (linha[i] != '|' && (linha[i] != ' ')) { // Pega o caracter e coloca na string
        linhas[j].push_back(linha[i]);
      }else {
        if (*linhas[j].rbegin() != ' ') { // Tira dois espaços, que vem das primeiras duas barras (|) do arquivo texto
          linhas[j].push_back(' '); // É só frescura msm '-'
        }
      }
    }
    j++;
  }
  sz = linhas.size();
  for (i=0;i<sz;i++) {
    for (j=0;j<(int)linhas[i].size();j++) {
      if (linhas[i][j] >= 48 && linhas[i][j] <= 57) {
        ch.push_back(linhas[i][j]);
      }
      else if (linhas[i][j] == ' ') {
        if (j<=2) {
          g[i].pk = atoi(ch.c_str());
        }else {
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
  mostra_grafo();
}
