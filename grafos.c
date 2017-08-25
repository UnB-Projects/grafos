#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
	int dado;
	struct elemento *proximo;
} t_elemento;


typedef struct lista {
	t_elemento *primeiro;
	t_elemento *ultimo;
} t_lista;

typedef struct elementoV {	
	int vertice;
	struct elementoV *adjacente;
	t_lista *lista;
} t_elementoV;

typedef struct listaV {
	t_elementoV *primeiro;
	t_elementoV *ultimo;
} t_listaV;

typedef struct {
	char amigo;
	int qtd;
} t_amigos;

void insereInicio (int valor, t_lista *l) {
	t_elemento *novoprimeiro;

	novoprimeiro = (t_elemento*) malloc(sizeof(t_elemento));
	novoprimeiro->dado = valor;								
	novoprimeiro->proximo = l->primeiro;
	l->primeiro = novoprimeiro;									

	if (l->ultimo == NULL) {									
		l->ultimo = novoprimeiro;
	}
}

void insereFinal (int valor, t_lista *l) {
	t_elemento *novoultimo;

	novoultimo = (t_elemento*) malloc(sizeof(t_elemento));		
	novoultimo->dado = valor;									
	novoultimo->proximo = NULL;									

	if (l->primeiro == NULL) {									
		l->primeiro = novoultimo;
	}
	else {
		l->ultimo->proximo = novoultimo;						
	}
	l->ultimo = novoultimo;										
}

void inserir (int pos, int valor, t_lista *l) {					
	t_elemento *atual;
	t_elemento *novo;
	int i;

	if (pos <= 0) {												
		insereInicio (valor, l);
	}
	else {
		atual = l->primeiro;									
		i = 0;
		while (i < (pos-1) && atual != NULL) {					
			atual = atual->proximo;
			i++;
		}

		if (atual == NULL || atual == l->ultimo) {				
			insereFinal (valor, l);
		}
		else {
			novo = (t_elemento*) malloc(sizeof(t_elemento));	
			novo->dado = valor;									
			novo->proximo = atual->proximo;						
			atual->proximo = novo;								
		}
	}
}

int estaVazia (t_lista *l) {
	if (l->primeiro == NULL) {									
		return 1;
	}
	else {
		return 0;
	}
}

int removeInicio (t_lista *l) {
	int tmp;
	t_elemento *removido;

	if (estaVazia(l))	{
		return -1;
	}

	tmp = l->primeiro->dado;									
	removido = l->primeiro;										
	l->primeiro = l->primeiro->proximo;							
	free (removido);
	return tmp;
}

int removeFinal (t_lista *l) {
	int tmp;
	t_elemento *fim;
	t_elemento *penultimo;

	if (estaVazia (l)) {
		return -1;
	}

	tmp = l->ultimo->dado;							
	fim = l->primeiro;								
	penultimo = NULL;								

	while (fim->proximo != NULL) {					
		penultimo = fim;
		fim = fim->proximo;
	}

	if (penultimo != NULL) {						
		penultimo->proximo = NULL;					
		l->ultimo = penultimo;
	}
	else {
		l->primeiro = NULL;
		l->ultimo = NULL;
	}
	free (fim);
	return tmp;
}

int remover (int elemento_removido, t_lista *l) {
	t_elemento *primeiro;
	t_elemento *segundo;

	if (estaVazia(l)) {
		return -1;
	}
	primeiro = NULL;
	segundo = l->primeiro;
	while (segundo != NULL && segundo->dado != elemento_removido) {
		primeiro = segundo;
		segundo = segundo->proximo;
	}
	if (segundo == NULL) {
		return -1;
	}
	if (segundo == l->primeiro) {
		removeInicio(l);
	}
	else if (segundo == l->ultimo) {
		removeFinal(l);
	}
	else {
		primeiro->proximo = segundo->proximo;
		free(segundo);
	}
	return 1;
}

t_listaV* criarGrafo() {
	t_listaV* grafo;
	grafo = (t_listaV*)malloc(sizeof(t_listaV));
	grafo->primeiro = NULL;
	grafo->ultimo = NULL;
	return grafo;
}

void adicionarVertice (t_listaV* grafo, int vertice) {
	t_elementoV *novoElemento;
	t_elementoV *verifica;

	verifica = grafo->primeiro;
	while (verifica != NULL && verifica->vertice != vertice) {
		verifica = verifica->adjacente;
	}
	if (verifica != NULL) {
		printf ("Este vertice ja existe no grafo\n");
		getchar();
		getchar();
		return;
	}
	novoElemento = (t_elementoV*)malloc(sizeof(t_elementoV));
	novoElemento->vertice = vertice;
	novoElemento->lista = NULL;
	novoElemento->adjacente = grafo->primeiro;
	grafo->primeiro = novoElemento;									
	if (grafo->ultimo == NULL) {									
		grafo->ultimo = novoElemento;
	}
}

int adicionarArco (t_listaV *grafo, int v, int w) {
	t_elementoV *alvo;
	t_elementoV *verifica;
	t_lista *arco;
	t_elemento *verifica_arco;

	alvo = grafo->primeiro;
	while (alvo != NULL && alvo->vertice != v) {
		alvo = alvo->adjacente;
	}
	verifica = grafo->primeiro;
	while (verifica != NULL && verifica->vertice != w) {
		verifica = verifica->adjacente;
	}
	if (alvo == NULL || verifica == NULL) {
		printf ("Um dos elementos nao pertence ao grafo\n");
		getchar();
		getchar();
		return 0;
	}
	arco = alvo->lista;
	if (arco == NULL) {
		arco = (t_lista*)malloc(sizeof(t_lista));
		arco->primeiro = NULL;
		arco->ultimo = NULL;
		alvo->lista = arco;
	}
	verifica_arco = arco->primeiro;
	while (verifica_arco != NULL && verifica_arco->dado != w) {
		verifica_arco = verifica_arco->proximo;
	}
	if (verifica_arco != NULL) {
		printf ("Este arco ja existe\n");
		getchar();
		getchar();
		return 0;	
	}
	insereInicio(w, arco);
	return 1;	
}

int removerArco (t_listaV *grafo, int v, int w) {
	t_elementoV *alvo;
	t_lista *arco;

	alvo = grafo->primeiro;
	while (alvo != NULL && alvo->vertice != v) {
		alvo = alvo->adjacente;
	}
	if (alvo == NULL) {
		printf ("Este vertice nao existe no grafo\n");
		getchar();
		getchar();
		return 0;
	}
	arco = alvo->lista;
	if (arco == NULL) {
		printf ("Este arco nao existe no grafo\n");
		getchar();
		getchar();
		return 0;
	}
	remover (w,arco);
	return 1;
}

int removerVertice (t_listaV *grafo, int v) {
	t_elementoV *alvo;
	t_elementoV *anterior;
	t_lista *arco;

	anterior = NULL;
	alvo = grafo->primeiro;
	while (alvo != NULL && alvo->vertice != v) {
		anterior = alvo;
		alvo = alvo->adjacente;
	}
	if (alvo == NULL) {
		printf ("Este vertice nao existe no grafo\n");
		getchar();
		getchar();
		return 0;
	}
	arco = alvo->lista;
	if (arco != NULL) {
		while (!estaVazia (arco)) {
			removeInicio(arco);
		}
		free (arco);
	}
	if (anterior != NULL) {
		anterior->adjacente = alvo->adjacente;
	}
	else {
		grafo->primeiro = alvo->adjacente;
	}
	free(alvo);
	alvo = grafo->primeiro;
	while (alvo != NULL) {
		arco = alvo->lista;
		if (arco != NULL) {
			remover(v, arco);
		}
		alvo = alvo->adjacente;
	}
	return 1;
}

void imprimeGrafo (t_listaV *grafo) {
	t_elementoV *alvo;
	t_lista *lista;
	t_elemento *arco;

	if (grafo->primeiro == NULL) {
		printf ("Este grafo nao possui elementos\n");
		return;
	}
	system("clear");
	alvo = grafo->primeiro;
	while (alvo != NULL) {
		printf ("%d->", alvo->vertice);
		lista = alvo->lista;
		if (lista != NULL) {
			arco = lista->primeiro;
			while (arco != NULL) {
				printf ("%d->", arco->dado);
				arco = arco->proximo;
			}
		}
		printf ("\\\n");
		alvo = alvo->adjacente;
	}
}

void esvaziaGrafo (t_listaV *grafo) {
	t_elementoV *anterior;
	t_elementoV *alvo;

	alvo = grafo->primeiro; 
	while (grafo->primeiro != NULL) {
		anterior = alvo;
		alvo = alvo->adjacente;
		removerVertice(grafo, anterior->vertice);
	}
}

void copiaGrafo (t_listaV *copia, t_listaV *grafo) {
	t_elementoV* alvo;
	t_elemento* arco;

	alvo = grafo->primeiro;
	while (alvo != NULL) {
		adicionarVertice(copia, alvo->vertice);
		alvo = alvo->adjacente;
	}
	alvo = grafo->primeiro;
	while (alvo != NULL) {
		if (alvo->lista != NULL) {
			arco = alvo->lista->primeiro;
			while (arco != NULL) {
				adicionarArco(copia, alvo->vertice, arco->dado);
				arco = arco->proximo;
			}
		}
		alvo = alvo->adjacente;
	}
}

void ordenamentoTopologico (t_listaV *grafo) {
	t_elementoV *alvo;
	t_elementoV *aux;
	t_elemento *arco;
	t_listaV *copia;
	t_lista *semAresta;
	t_lista *ordenados;
	int flag;

	semAresta = (t_lista*)malloc(sizeof(t_lista));
	semAresta->primeiro = NULL;
	semAresta->ultimo = NULL;

	ordenados = (t_lista*)malloc(sizeof(t_lista));
	ordenados->primeiro = NULL;
	ordenados->ultimo = NULL;

	copia = criarGrafo();
	copiaGrafo(copia, grafo);
	while (copia->primeiro != NULL && copia->ultimo != NULL) {
		alvo = copia->primeiro;
		while (alvo != NULL) {
			aux = copia->primeiro;
			flag = 0;
			while (aux != NULL && flag == 0) {
				if (aux->lista != NULL) {
					arco = aux->lista->primeiro;
					while (arco != NULL) {
						if (arco->dado == alvo->vertice) {
							flag = 1;
						}
						arco = arco->proximo;
					}
				}
				aux = aux->adjacente;
			}
			if (flag == 0) {
				insereFinal(alvo->vertice, semAresta);
			}
			alvo = alvo->adjacente;
		}
		if (estaVazia(semAresta)) {
			printf ("Grafo tem pelo menos um ciclo\n");
			esvaziaGrafo(copia);
			return;
		}
		while (!estaVazia(semAresta)) {
			removerVertice(copia,semAresta->primeiro->dado);
			insereFinal(removeInicio(semAresta), ordenados);
		}
	}
	printf ("Ordenamento Topologico\n");
	while (!estaVazia(ordenados)) {
		printf ("%d ", removeInicio(ordenados));
	}
	free(copia);
	free(ordenados);
	free(semAresta);
	printf ("\n");
}

/*void procuraAmigos (t_listaV *grafo, int v, int n) {
	t_lista *lista_amigos;
	t_listaV *alvo;
	t_lista *arco;
	t_amigos amigos[50];
	int i, cnt;

	alvo = grafo->primeiro;
	while (alvo != NULL && alvo->vertice != v) {

	}
	if (alvo == NULL) {
		printf ("Vertice nao encontrado\n");
		getchar();
		getchar();
		return;
	}
	lista_amigos = (t_lista*)malloc(sizeof(t_lista));
	lista_amigos->primeiro = NULL;
	lista_amigos->ultimo = NULL;
	arco = alvo->lista;
	cnt = 0;
	while (arco != NULL) {
		insereFinal(arco->dado, lista_amigos);
		amigos.amigo = arco->dado;
		arco = arco->proximo;
	}
	for (i = 0; i < 50; i++) {
		amigos.qtd = 0;
	}
	while (lista_amigos != NULL) {
		alvo = grafo->primeiro;
		while (alvo->vertice != lista_amigos->primeiro) {
			alvo = alvo->adjacente;
		}
		arco = alvo->lista;

	}
}*/

int menu () {
	int opcao;

	system("clear");
	printf ("1 - Inserir vertice\n");
	printf ("2 - Remover vertice\n");
	printf ("3 - Inserir arco\n");
	printf ("4 - Remover arco\n");
	printf ("5 - Imprimir grafo\n");
	printf ("6 - Ordenamento Topologico\n");
	printf ("7 - Limpar grafo\n");
	printf ("8 - Sair\n");
	printf ("\nDigite sua opcao: ");
	scanf ("%d", &opcao);
	return opcao;
}

int main () {
	t_listaV *grafo;
	int opcao;
	int v, w;

	grafo = criarGrafo();
	do {
		opcao = menu();
		getchar();
		if (opcao == 1) {
			printf ("Digite o valor de 'v' a ser inserido: ");
			scanf ("%d", &v);
			adicionarVertice(grafo, v);
		}
		else if (opcao == 2) {
			printf ("Digite o valor de 'v' a ser removido: ");
			scanf ("%d", &v);
			removerVertice(grafo,v);
		}
		else if (opcao == 3) {
			printf ("Digite o valor de v e w a serem inseridos: ");
			scanf ("%d %d", &v, &w);
			adicionarArco(grafo, v, w);
		}
		else if (opcao == 4) {
			printf ("Digite o valor de v e w a serem removidos: ");
			scanf ("%d %d", &v, &w);
			removerArco(grafo, v, w);	
		}
		else if (opcao == 5) {
			system ("clear");
			imprimeGrafo(grafo);
			printf ("Tecle <ENTER> para voltar ao menu\n");
			getchar();
		}
		else if (opcao == 6) {
			system ("clear");
			ordenamentoTopologico(grafo);
			printf ("Tecle <ENTER> para voltar ao menu\n");
			getchar();
		}
		else if (opcao == 7) {
			system ("clear");
			esvaziaGrafo(grafo);
			printf ("O grafo foi esvaziado\n");
			printf ("Tecle <ENTER> para voltar ao menu\n");
			getchar();
		}
	}while (opcao != 8);
	esvaziaGrafo(grafo);
	free (grafo);
	return 0;
}