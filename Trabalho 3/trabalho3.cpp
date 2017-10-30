//Trabalho 3 da Disciplina Teoria e Aplicação de Grafos - Turma A
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

vector<vector<int>> P (100);
vector<int> E;

typedef pair<int,int> Aresta; // Uma aresta eh um pair da seguinte forma: <Disciplina,Peso da Aresta>
typedef struct Vertice { //Definicao da estrutura de um vertice
  int pk;                //Identificador unico de cada vertice
  vector<int> adjacentes;    //Lista de conexoes (arestas)
}t_Vertice;

typedef vector<Vertice> Grafo; //Um grafo eh definido como um conjunto de vertices

//Funcao de leitura do arquivo
void leitura_arquivo() {
  string linha;
  string numero;
  ifstream input("entradaProj3TAG.txt");
  bool flag = false;

  int i, j = 0;

  for (i = 0; i < 3; i++) {
    getline(input, linha); // Ignora as tres primeira linhas do arquivo
  }

  while (getline(input, linha) && flag == false) {
    if (linha.length() == 0) {
      flag = true;
    }
    else {
      i = 0;
      while (linha[i] != ',') {
        i++;
      }

      while (linha[i] != ':') {
        if (linha[i] >= '0' && linha[i] <= '9') {
          numero = linha[i];
          P[j].push_back(stoi(numero));
          numero.clear();
        }
        i++;
      }

      while (linha[i] != ')') {
        i++;
        while (linha[i] != ',' && linha[i] != ')') {
          if (linha[i] >= '0' && linha[i] <= '9') {
            numero.push_back(linha[i]);
          }
          i++;
        }
        P[j].push_back(stoi(numero));
        numero.clear();
      }
      j++;
    }
  }

  getline(input, linha); // Ignora comentarios

  while (getline(input, linha)) {
    i = 0;
    while (linha[i] != ':') {
      i++;
    }

    while (linha[i] != ')') {
      if (linha[i] >= '0' && linha[i] <= '9') {
        numero = linha[i];
        E.push_back(stoi(numero));
        numero.clear();
      }
      i++;
    }
  }
  E.erase(E.begin()+50);

  for (i = 0; i < P.size(); i++) {
    reverse(P.begin(), P.end());
  }
}

void emparelhamento(Grafo &professores, Grafo &escolas) {
  bool profLivre = true;
  bool semPar = true;
  int i, j, k, l;
  int primeiraEscola;
  int primeiroProf;

  for (i = 0; i < 50; i++) {
    professores[i].pk = i+1;
    escolas[i].pk = i+1;
  }

  for (i = 50; i < 100; i++) {
    professores[i].pk = i+1;
  }

  i = 0;
  j = 0;


  while (profLivre && semPar) {
    profLivre = false;
    semPar = false;

    primeiraEscola = P[i][1];

    if (escolas[primeiraEscola-1].adjacentes.size() == 2 && P[escolas[primeiraEscola-1].adjacentes[1]-1].size() > 1) {
      professores[escolas[primeiraEscola-1].adjacentes[1]-1].adjacentes.clear();
      escolas[primeiraEscola-1].adjacentes.erase(escolas[primeiraEscola-1].adjacentes.begin()+1);
    }

    escolas[primeiraEscola-1].adjacentes.push_back(i+1);
    //reverse(escolas[primeiraEscola-1].adjacentes.begin(), escolas[primeiraEscola-1].adjacentes.end());

    professores[i].adjacentes.push_back(primeiraEscola);
    P[i].erase(P[i].begin()+1);
    

    for (k = 0; k < escolas.size(); k++) {
      for (l = 0; l < professores.size(); l++) {
        if(professores[k].adjacentes.size() == 0 && escolas[l].adjacentes.size() < 2) {
          i = k;
          semPar = true;
        }
      }
    }

    for (k = 0; k < professores.size(); k++) {
      if (professores[k].adjacentes.size() == 0) {
        i = k;
        profLivre = true;
      }
    }
  }

  for (i = 0; i < escolas.size(); i++) {
    while (escolas[i].adjacentes.size() > 2) {
      for (j = 0; j < escolas.size(); j++) {
        if (escolas[j].adjacentes.size() < 2) {
          k = j;
        }
      }
      professores[escolas[i].adjacentes[escolas[i].adjacentes.size()-1]].adjacentes.clear();
      professores[escolas[i].adjacentes[escolas[i].adjacentes.size()-1]].adjacentes.push_back(k+1);
      escolas[k].adjacentes.push_back(escolas[i].adjacentes[escolas[i].adjacentes.size()-1]);
      escolas[i].adjacentes.pop_back();
    }
  }
}

int main () {
  Grafo professores(100);
  Grafo escolas(50);
  int i, j;
  vector<int> cnt(51);

  leitura_arquivo();

  emparelhamento(professores, escolas);
//  for (i = 0; i < escolas.size(); i++) {
  //  cout << i+1 << " " << escolas[i].adjacentes[0] << " " << escolas[i].adjacentes[1] << endl;
  //}

  cout << "##### PROFESSORES #####" << endl << endl;

  for (i = 0; i < professores.size(); i++) {
    cout << "P" << professores[i].pk << " | " << "E" << professores[i].adjacentes[0] << endl;
  }

  cout << endl << "##### ESCOLAS #####" << endl << endl;

  for (i = 0; i < escolas.size(); i++) {
    cout << "E" << escolas[i].pk << " | " << "P" << escolas[i].adjacentes[0] << " | " << "P" << escolas[i].adjacentes[1] << endl;
  }
}