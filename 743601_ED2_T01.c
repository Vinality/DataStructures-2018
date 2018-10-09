/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 01
 *
 * RA: 743601
 * Aluno: Vinicius Brandao Crepschi
 * ========================================================================== */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/* Tamanho dos campos dos registros */
#define TAM_PRIMARY_KEY	11
#define TAM_NOME 		51
#define TAM_MARCA 		51
#define TAM_DATA 		11
#define TAM_ANO 		3
#define TAM_PRECO 		8
#define TAM_DESCONTO 	4
#define TAM_CATEGORIA 	51


#define TAM_REGISTRO 	192
#define MAX_REGISTROS 	1000
#define MAX_CATEGORIAS 	30
#define TAM_ARQUIVO (MAX_REGISTROS * TAM_REGISTRO + 1)


/* Saídas para o usuario */
#define OPCAO_INVALIDA 				"Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE 		"Memoria insuficiente!"
#define REGISTRO_N_ENCONTRADO 		"Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO 				"Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA			"ERRO: Ja existe um registro com a chave primaria: %s.\n"
#define ARQUIVO_VAZIO 				"Arquivo vazio!"
#define INICIO_BUSCA 		 		"**********************BUSCAR**********************\n"
#define INICIO_LISTAGEM  			"**********************LISTAR**********************\n"
#define INICIO_ALTERACAO 			"**********************ALTERAR*********************\n"
#define INICIO_EXCLUSAO  			"**********************EXCLUIR*********************\n"
#define INICIO_ARQUIVO  			"**********************ARQUIVO*********************\n"
#define INICIO_ARQUIVO_SECUNDARIO	"*****************ARQUIVO SECUNDARIO****************\n"
#define SUCESSO  				 	"OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					 	"FALHA AO REALIZAR OPERACAO!\n"



/* Registro do Produto */
typedef struct {
	char pk[TAM_PRIMARY_KEY];
	char nome[TAM_NOME];
	char marca[TAM_MARCA];
	char data[TAM_DATA];	/* DD/MM/AAAA */
	char ano[TAM_ANO];
	char preco[TAM_PRECO];
	char desconto[TAM_DESCONTO];
	char categoria[TAM_CATEGORIA];
} Produto;


/*----- Registros dos Índices -----*/

/* Struct para índice Primário */
typedef struct primary_index{
  char pk[TAM_PRIMARY_KEY];
  int rrn;
} Ip;

/* Struct para índice secundário */
typedef struct secundary_index{
  char pk[TAM_PRIMARY_KEY];
  char string[TAM_NOME];
} Is;

/* Struct para índice secundário de preços */
typedef struct secundary_index_of_final_price{
  float price;
  char pk[TAM_PRIMARY_KEY];
} Isf;

/* Lista ligada para o Índice abaixo*/
typedef struct linked_list{
  char pk[TAM_PRIMARY_KEY];
  struct linked_list *prox;
} ll;

/* Struct para lista invertida */
typedef struct reverse_index{
  char cat[TAM_CATEGORIA];
  ll* lista;
} Ir;

/*----- GLOBAL -----*/
char ARQUIVO[TAM_ARQUIVO];

/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

/* Recebe do usuário uma string simulando o arquivo completo e retorna o número
 * de registros. */
int carregar_arquivo();

/* Exibe o Produto */
int exibir_registro(int rrn, char com_desconto);

/* Recupera do arquivo o registro com o rrn informado
 *  e retorna os dados na struct Produto */
Produto recuperar_registro(int rrn);

/* (Re)faz o índice respectivo */
// void criar_iprimary(Ip *indice_primario, int* nregistros);

/* Realiza os scanfs na struct Produto */
void ler_entrada(char* registro, Produto *novo);

/* Rotina para impressao de indice secundario */
void imprimirSecundario(Is* iproduct, Is* ibrand, Ir* icategory, Isf *iprice, int nregistros, int ncat);

// Insere no arquivo de dados o produto e preenche com #
void salvarProduto(char *file, Produto p);

// Insere a chave primaria no vetor iprimary
void inserePrimaria(Ip *iprimary, int *nregistros, char *pk);

// Le do teclado os dados de um novo produto
Produto inserir_produto();

// Gera a chave primaria a partir dos dados inseridos
void gerarChave(Produto *prod);

/* ==========================================================================
 * ========================= FUNCOES DE INSERCAO ============================
 * ========================================================================== */
void printaChaves(Ip *iprimary, int nregistros); // Imprime todas as chaves primarias do vetor iprimary
void insereSecundariaNome(Is *iproduct, int nregistros, char *pk, char *nome); // Insere no vetor iproduct a chave secundaria
void insereSecundariaMarca(Is *ibrand, int nregistros, char *pk, char *marca); // Insere no vetor ibrand a chave secundaria
void insereSecundariaPreco(Isf *iprice, int nregistros, char *pk, char *preco); // Insere no vetor iprice a chave secundaria
void insereSecundariaCat(Ir *icategory, int *ncat, char *categoria, char *pk); // Insere no vetor icategory um elemento de categoria

// Inserir elemento novo na lista ligada
void inserirLista(ll *lista, char *pk);

/* ==========================================================================
 * ========================= FUNCOES DE ORDENACAO ===========================
 * ========================================================================== */
void ordenaPrimaria(Ip *iprimary, int nregistros); // Ordena o vetor de chaves primarias
void ordenaProduct(Is *iproduct, int nregistros); // Ordena o vetor de chaves secundarias iproduct
void ordenaBrand(Is *ibrand, int nregistros); // Ordena o vetor de chaves secundarias ibrand
void ordenaPreco(Isf *iprice, int nregistros); // Ordena o vetor de chaves secundarias iprice
void ordenaCategoria(Ir *icategory, int ncat);

/* ==========================================================================
 * ========================= FUNCOES DE COMPARACAO ==========================
 * ========================================================================== */
// Funcoes auxiliares de comparacao para o qsort e bsearch
int compara(const void *a, const void *b);
int comparaProductBrand(const void *a, const void *b);
int comparaStringIprimary(const void *a, const void *b);
int comparaPreco(const void *a, const void *b);
int comparaCategoria(const void *a, const void *b);

// Funcao para buscar um elemento a partir de sua chave primaria
int buscarChave(Ip* iprimary, char *key, int nregistros);
/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */
int main(){
  /* Arquivo */
	int carregarArquivo = 0, nregistros = 0, ncat = 0;
	Produto novo;
	scanf("%d%*c", &carregarArquivo); /* 1 (sim) | 0 (nao) */
	if (carregarArquivo)
		nregistros = carregar_arquivo();

	/* Índice primário */
	Ip *iprimary = (Ip *) malloc (MAX_REGISTROS * sizeof(Ip));
  	if (!iprimary) {
		perror(MEMORIA_INSUFICIENTE);
		exit(1);
	}
	// criar_iprimary(iprimary, &nregistros);

	/*Alocar e criar índices secundários*/
	Is *ibrand = (Is *) malloc (MAX_REGISTROS * sizeof(Is));
	Is *iproduct = (Is *) malloc (MAX_REGISTROS * sizeof(Is));
	Isf *iprice = (Isf *) malloc (MAX_REGISTROS * sizeof(Isf));
	Ir *icategory = (Ir *) malloc (MAX_REGISTROS * sizeof(Ir));
	/* Execução do programa */
	int opcao = 0;
	while(1)
	{
		scanf("%d%*c", &opcao);
		switch(opcao)
		{
			case 1:
				novo = inserir_produto();
				if(buscarChave(iprimary, novo.pk, nregistros)){
					printf(ERRO_PK_REPETIDA, novo.pk);
				}
				else{
					inserePrimaria(iprimary, &nregistros, novo.pk);
					insereSecundariaNome(iproduct, nregistros, novo.pk, novo.nome);
					insereSecundariaMarca(ibrand, nregistros, novo.pk, novo.marca);
					insereSecundariaPreco(iprice, nregistros, novo.pk, novo.preco);
					insereSecundariaCat(icategory, &ncat, novo.categoria, novo.pk);
					salvarProduto(ARQUIVO, novo);
					printaChaves(iprimary, nregistros);
				}
			break;
			case 2:
				/*alterar desconto*/
				printf(INICIO_ALTERACAO);
				/*
				if(alterar([args]))
					printf(SUCESSO);
				else
					printf(FALHA);
				*/
			break;
			case 3:
				/*excluir produto*/
				printf(INICIO_EXCLUSAO);
				/*
				if(remover([args]))
					printf(SUCESSO);
				else
					printf(FALHA);
				*/
			break;
			case 4:
				/*busca*/
				printf(INICIO_BUSCA );
			break;
			case 5:
				/*listagens*/
				printf(INICIO_LISTAGEM);
			break;
			case 6:
				/*libera espaço*/
			break;
			case 7:
				/*imprime o arquivo de dados*/
				printf(INICIO_ARQUIVO);
				printf("%s\n", ARQUIVO);
			break;
			case 8:
				/*imprime os índices secundários*/
				imprimirSecundario(iproduct, ibrand, icategory, iprice, nregistros, ncat);
			break;
			case 9:
	      		/*Liberar memória e finalizar o programa */
				return 0;
			break;
			default:
				printf(OPCAO_INVALIDA);
			break;
		}
	}
	return 0;
}

/* Exibe o Produto */
int exibir_registro(int rrn, char com_desconto)
{
	if(rrn<0)
		return 0;
	float preco;
	int desconto;
	Produto j = recuperar_registro(rrn);
  	char *cat, categorias[TAM_CATEGORIA];
	printf("%s\n", j.pk);
	printf("%s\n", j.nome);
	printf("%s\n", j.marca);
	printf("%s\n", j.data);
	if(!com_desconto)
	{
		printf("%s\n", j.preco);
		printf("%s\n", j.desconto);
	}
	else
	{
		sscanf(j.desconto,"%d",&desconto);
		sscanf(j.preco,"%f",&preco);
		preco = preco *  (100-desconto);
		preco = ((int) preco)/ (float) 100 ;
		printf("%07.2f\n",  preco);

	}
	strcpy(categorias, j.categoria);

	cat = strtok (categorias, "|");

	while(cat != NULL){
		printf("%s", cat);
		cat = strtok (NULL, "|");
		if(cat != NULL){
			printf(", ");
		}
	}

	printf("\n");

	return 1;
}


int carregar_arquivo()
{
	scanf("%[^\n]\n", ARQUIVO);
	return strlen(ARQUIVO) / TAM_REGISTRO;
}


/* Recupera do arquivo o registro com o rrn
 * informado e retorna os dados na struct Produto */
Produto recuperar_registro(int rrn)
{
	char temp[193], *p;
	strncpy(temp, ARQUIVO + ((rrn)*192), 192);
	temp[192] = '\0';
	Produto j;
	p = strtok(temp,"@");
	strcpy(j.nome,p);
	p = strtok(NULL,"@");
	strcpy(j.marca,p);
	p = strtok(NULL,"@");
	strcpy(j.data,p);
	p = strtok(NULL,"@");
	strcpy(j.ano,p);
	p = strtok(NULL,"@");
	strcpy(j.preco,p);
	p = strtok(NULL,"@");
	strcpy(j.desconto,p);
	p = strtok(NULL,"@");
	strcpy(j.categoria,p);
	gerarChave(&j);
	return j;
}


/* Imprimir indices secundarios */
void imprimirSecundario(Is* iproduct, Is* ibrand, Ir* icategory, Isf *iprice, int nregistros, int ncat){
	int opPrint = 0;
	ll *aux;
	printf(INICIO_ARQUIVO_SECUNDARIO);
	scanf("%d", &opPrint);
	if(!nregistros)
		printf(ARQUIVO_VAZIO);
	switch (opPrint) {
		case 1:
			for(int i = 0; i < nregistros; i++){
				printf("%s %s\n",iproduct[i].pk, iproduct[i].string);
			}
		break;
		case 2:
			for(int i = 0; i < nregistros; i++){
				printf("%s %s\n",ibrand[i].pk, ibrand[i].string);
			}
		break;
		case 3:
			for(int i = 0; i < ncat; i++){
				printf("%s", icategory[i].cat);
				aux =  icategory[i].lista;
				while(aux != NULL){
					printf(" %s", aux->pk);
					aux = aux->prox;
				}
				printf("\n");
			}
		break;

		case 4:
		for(int i = 0; i < nregistros; i++){
			printf("%s %.2f\n",iprice[i].pk, iprice[i].price);
		}
		break;
	}
}

void gerarChave(Produto *prod){
	prod->pk[0] = prod->nome[0];
	prod->pk[1] = prod->nome[1];
	prod->pk[2] = prod->marca[0];
	prod->pk[3] = prod->marca[1];
	prod->pk[4] = prod->data[0];
	prod->pk[5] = prod->data[1];
	prod->pk[6] = prod->data[3];
	prod->pk[7] = prod->data[4];
	prod->pk[8] = prod->ano[0];
	prod->pk[9] = prod->ano[1];
	prod->pk[10] = '\0';

	// maiusculo(prod->pk);
}

Produto inserir_produto(){
	Produto novo;
	scanf("\n%[^\n]s", novo.nome);
	scanf("\n%[^\n]s", novo.marca);
	scanf("\n%[^\n]s", novo.data);
	scanf("\n%[^\n]s", novo.ano);
	scanf("\n%[^\n]s", novo.preco);
	scanf("\n%[^\n]s", novo.desconto);
	scanf("\n%[^\n]s", novo.categoria);
	gerarChave(&novo);
	return novo;
}

void inserePrimaria(Ip *iprimary, int *nregistros, char *pk){
	strcpy(iprimary[*nregistros].pk, pk);
	iprimary[*nregistros].rrn = *nregistros;
	(*nregistros)++;
	ordenaPrimaria(iprimary, *nregistros);
}

void insereSecundariaNome(Is *iproduct, int nregistros, char *pk, char *nome){
	strcpy(iproduct[nregistros-1].pk, pk);
	strcpy(iproduct[nregistros-1].string, nome);
	ordenaProduct(iproduct, nregistros);
}

void insereSecundariaMarca(Is *ibrand, int nregistros, char *pk, char *marca){
	strcpy(ibrand[nregistros-1].pk, pk);
	strcpy(ibrand[nregistros-1].string, marca);
	ordenaBrand(ibrand, nregistros);
}

void insereSecundariaPreco(Isf *iprice, int nregistros, char *pk, char *preco){
	strcpy(iprice[nregistros-1].pk, pk);
	iprice[nregistros-1].price = atof(preco);
	ordenaPreco(iprice, nregistros);
}

void insereSecundariaCat(Ir *icategory, int *ncat, char *categoria, char *pk){
	Ir* aux = (Ir*)bsearch(categoria, icategory, *ncat, sizeof(Ir), comparaCategoria);
	if(aux){
		inserirLista(aux->lista, pk);
	}
	else{
		strcpy(icategory[*ncat].cat, categoria);
		(*ncat)++;
	}
	ordenaCategoria(icategory, *ncat);
}

void inserirLista(ll *lista, char *pk){
	ll *novo = (ll*)malloc(sizeof(ll));
   	ll *aux = lista;
   	strcpy(novo->pk, pk);

   if(lista == NULL){
	   novo->prox = aux;
	   aux = novo;
   }

   else{
	   if(strcmp(aux->pk, novo->pk) > 0){
		   novo->prox = aux;
		   aux = novo;
		   return;
	   }

	   while(aux->prox != NULL && strcmp(aux->pk, novo->pk) != 0){
		   if(strcmp(novo->pk, aux->prox->pk) < 0){
			   novo->prox = aux->prox;
			   aux->prox = novo;
			   return;
		   }
		   else
			   aux = aux->prox;
	   }

	   if(strcmp(aux->pk, novo->pk) != 0){
		   novo->prox = aux->prox;
		   aux->prox = novo;
	   }
   }
}

void salvarProduto(char *file, Produto p){
	char temp[192];
	sprintf(temp, "%s@%s@%s@%s@%s@%s@%s@", p.nome, p.marca, p.data, p.ano, p.preco,
	p.desconto, p.categoria);
	if(strlen(temp) < 192){
		for(int i = 0; i < 192 - strlen(temp); i++){
			strcat(temp, "#");
		}
	}
	strcat(file, temp);
}

void ordenaPrimaria(Ip *iprimary, int nregistros){
	qsort(iprimary, nregistros, sizeof(Ip), compara);
}

void ordenaProduct(Is *iproduct, int nregistros){
	qsort(iproduct, nregistros, sizeof(Is), comparaProductBrand);
}

void ordenaBrand(Is *ibrand, int nregistros){
	qsort(ibrand, nregistros, sizeof(Is), comparaProductBrand);
}

void ordenaPreco(Isf *iprice, int nregistros){
	qsort(iprice, nregistros, sizeof(Isf), comparaPreco);
}

void ordenaCategoria(Ir *icategory, int ncat){
	qsort(icategory, ncat, sizeof(Ir), comparaCategoria);
}

int compara(const void *a, const void *b){
	Ip *aux1 = (Ip *)a;
	Ip *aux2 = (Ip *)b;

	return strcmp(aux1->pk, aux2->pk);
}

int comparaProductBrand(const void *a, const void *b){
	Is *aux1 = (Is *)a;
	Is *aux2 = (Is *)b;
	int result;
	result = strcmp(aux1->string, aux2->string);
	if(result != 0)
		return result;
	else{
		return strcmp(aux1->pk, aux2->pk);
	}

}

int comparaPreco(const void *a, const void *b){
	Isf *aux1 = (Isf *)a;
	Isf *aux2 = (Isf *)b;
	if(aux1->price < aux2->price)
		return -1;
	else if(aux1->price > aux2->price)
		return 1;
	else
		return strcmp(aux1->pk, aux2->pk);
}

int comparaStringIprimary(const void *a, const void *b){
	return strcmp((char *)a, ((const Ip *)b)->pk);
}

int comparaCategoria(const void *a, const void *b){
	return strcmp((char *)a, ((const Ir *)b)->cat);
}

void printaChaves(Ip *iprimary, int nregistros){
	for(int i = 0; i<nregistros; i++){
		printf("%s\n", (iprimary[i]).pk);
	}
}

int buscarChave(Ip* iprimary, char *key, int nregistros){
	if((Ip*)bsearch(key, iprimary, nregistros, sizeof(Ip), comparaStringIprimary))
		return 1;
	else
		return 0;
}
