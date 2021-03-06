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
#define ARQUIVO_VAZIO 				"Arquivo vazio!\n"
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
void criar_iprimary(Ip *indice_primario, int* nregistros);
void criar_iproduct(Is *isecondary, int* nregistros);
void criar_ibrand(Is *isecondary, int* nregistros);
void criar_isfprice(Isf *iprice, int *nregistros);
void criar_icategory(Ir *icategory, int *ncat, int nregistros);

/* Rotina para impressao de indice secundario */
void imprimirSecundario(Is* iproduct, Is* ibrand, Ir* icategory, Isf *iprice, int nregistros, int ncat);

// Insere no arquivo de dados o produto e preenche com #
void salvarProduto(char *file, Produto p);

// Le do teclado os dados de um novo produto
Produto inserir_produto();

// Gera a chave primaria a partir dos dados inseridos
void gerarChave(Produto *prod);

int remover(Ip* iprimary, int nregistros);

int alterar(Ip *iprimary, int nregistros, Isf *iprice);
/* ==========================================================================
 * ========================= FUNCOES DE INSERCAO ============================
 * ========================================================================== */
// void printaChaves(Ip *iprimary, int nregistros); // Imprime todas as chaves primarias do vetor iprimary
void inserePrimaria(Ip *iprimary, int *nregistros, char *pk); // Insere a chave primaria no vetor iprimary
void insereSecundariaNome(Is *iproduct, int nregistros, char *pk, char *nome); // Insere no vetor iproduct a chave secundaria
void insereSecundariaMarca(Is *ibrand, int nregistros, char *pk, char *marca); // Insere no vetor ibrand a chave secundaria
void insereSecundariaPreco(Isf *iprice, int nregistros, char *pk, char *preco, char *desconto); // Insere no vetor iprice a chave secundaria
void insereSecundariaCat(Ir *icategory, int *ncat, char *categoria, char *pk); // Insere no vetor icategory um elemento de categoria

// Inserir elemento novo na lista ligada
void inserirLista(ll **lista, char *pk);

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
int comparaStringIsecondary(const void *a, const void *b);

// Funcao para buscar um elemento a partir de sua chave primaria
int buscarChave(Ip* iprimary, char *key, int nregistros);
void buscarProduto(Ip *iprimary, Is *iproduct, Is *ibrand, Ir *icategory, int nregistros, int ncat);
void imprimirProduto(Produto a);
void imprimirProdutoSemAno(Produto a);
void listarProdutos(Ip *iprimary, Isf *iprice, Is *ibrand, Ir *icategory, int nregistros, int ncat);
void printaMarcas(Ip *iprimary, Is *ibrand, int nregistros);
void printaPreco(Ip *iprimary, Isf *iprice, int nregistros);
void printaCategoria(Ip *iprimary, Ir *icategory, int nregistros, int ncat, char *find);

void limparArquivo(Ip *iprimary, int *nregistros, Is *iproduct, Is *ibrand, Isf *iprice, Ir *icategory, int *ncat);
void liberarMemoria(Ip *iprimary, Is *iproduct, Is *ibrand, Isf *iprice, Ir *icategory, int nregistros, int ncat);
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
	criar_iprimary(iprimary, &nregistros);

	/*Alocar e criar índices secundários*/
	Is *ibrand = (Is *) malloc (MAX_REGISTROS * sizeof(Is));
	Is *iproduct = (Is *) malloc (MAX_REGISTROS * sizeof(Is));
	Isf *iprice = (Isf *) malloc (MAX_REGISTROS * sizeof(Isf));
	Ir *icategory = (Ir *) malloc (MAX_REGISTROS * sizeof(Ir));
	criar_iproduct(iproduct, &nregistros);
	criar_ibrand(ibrand, &nregistros);
	criar_isfprice(iprice, &nregistros);
	criar_icategory(icategory, &ncat, nregistros);
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
					insereSecundariaPreco(iprice, nregistros, novo.pk, novo.preco, novo.desconto);
					salvarProduto(ARQUIVO, novo);
					insereSecundariaCat(icategory, &ncat, novo.categoria, novo.pk);
					// printaChaves(iprimary, nregistros);
				}
			break;
			case 2:
				/*alterar desconto*/
				printf(INICIO_ALTERACAO);
				if(alterar(iprimary, nregistros, iprice))
					printf(SUCESSO);
				else
					printf(FALHA);
			break;
			case 3:
				/*excluir produto*/
				printf(INICIO_EXCLUSAO);
				if(remover(iprimary, nregistros))
					printf(SUCESSO);
				else
					printf(FALHA);
			break;
			case 4:
				/*busca*/
				printf(INICIO_BUSCA );
				buscarProduto(iprimary, iproduct, ibrand, icategory, nregistros, ncat);
			break;
			case 5:
				/*listagens*/
				printf(INICIO_LISTAGEM);
				listarProdutos(iprimary, iprice, ibrand, icategory, nregistros, ncat);
			break;
			case 6:
				/*libera espaço*/
				limparArquivo(iprimary, &nregistros, iproduct, ibrand, iprice, icategory, &ncat);
			break;
			case 7:
				/*imprime o arquivo de dados*/
				printf(INICIO_ARQUIVO);
				if(nregistros == 0)
					printf(ARQUIVO_VAZIO);
				else
					printf("%s\n", ARQUIVO);
			break;
			case 8:
				/*imprime os índices secundários*/
				imprimirSecundario(iproduct, ibrand, icategory, iprice, nregistros, ncat);
			break;
			case 9:
	      		/*Liberar memória e finalizar o programa */
				liberarMemoria(iprimary, iproduct, ibrand, iprice, icategory, nregistros, ncat);
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
		preco = ((int) preco)/ (float) 100;
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

void insereSecundariaPreco(Isf *iprice, int nregistros, char *pk, char *preco, char *desconto){
	int desc = 0;
	float precofinal = 0;
	strcpy(iprice[nregistros-1].pk, pk);
	sscanf(desconto,"%d",&desc);
	sscanf(preco,"%f",&precofinal);
	precofinal = (precofinal * (100-desc))/100;
	precofinal = precofinal*100;
	precofinal = ((int) precofinal)/ (float) 100;
	iprice[nregistros-1].price = precofinal;
	ordenaPreco(iprice, nregistros);
}

void insereSecundariaCat(Ir *icategory, int *ncat, char *categoria, char *pk){
	char *auxcat = categoria;
	char *cat = strtok (auxcat, "|");

	while(cat != NULL){
		Ir* aux = (Ir*)bsearch(cat, icategory, *ncat, sizeof(Ir), comparaCategoria);
		if(aux != NULL){
			inserirLista(&aux->lista, pk);
		}
		else{
			strcpy(icategory[*ncat].cat, cat);
			inserirLista(&icategory[*ncat].lista, pk);
			(*ncat)++;
			ordenaCategoria(icategory, *ncat);
		}
		cat = strtok (NULL, "|");
	}
	ordenaCategoria(icategory, *ncat);
}

//Insere na lista ligada
void inserirLista(ll **lista, char *pk){
	ll *novo = (ll*)malloc(sizeof(ll));
   	ll *aux = *lista;
   	strcpy(novo->pk, pk);

   if(*lista == NULL || strcmp((*lista)->pk, novo->pk) >= 0){
	   novo->prox = *lista;
	   *lista = novo;
   }

   else{
	   	aux = *lista;
	  	while(aux->prox != NULL && strcmp(aux->prox->pk, novo->pk) < 0){
		  	aux = aux->prox;
	  	}
	  	novo->prox = aux->prox;
	  	aux->prox = novo;
  	}
}

void salvarProduto(char *file, Produto p){
	char temp[193];
	sprintf(temp, "%s@%s@%s@%s@%s@%s@%s@", p.nome, p.marca, p.data, p.ano, p.preco,
	p.desconto, p.categoria);
	int tam = strlen(temp);
	if(tam < 192){
		for(; tam < 192; tam++){
			strcat(temp, "#");
		}
	}
	if(file != NULL)
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

int comparaStringIsecondary(const void *a, const void *b){
	return strcmp((char *)a, ((const Is *)b)->string);
}

int comparaCategoria(const void *a, const void *b){
	return strcmp((char *)a, ((const Ir *)b)->cat);
}

int comparaPkIprice(const void *a, const void *b){
	return strcmp((char *)a, ((const Isf *)b)->pk);
}

void printaMarcas(Ip *iprimary, Is *ibrand, int nregistros){
	Ip *ipaux;
	int flag = 0;
	for(int i = 0; i<nregistros; i++){
		for(int j = 0; j<nregistros; j++){
			if(strcmp(ibrand[i].pk, iprimary[j].pk)==0){
				ipaux = &iprimary[j];
				if(flag){
					printf("\n");
					flag = 0;
				}
				if(exibir_registro(ipaux->rrn, 0))
					flag = 1;
			}
		}
	}
}

void printaPreco(Ip *iprimary, Isf *iprice, int nregistros){
	Ip *ipaux;
	int flag = 0;

	for(int i = 0; i<nregistros; i++){
		for(int j = 0; j<nregistros; j++){
			if(strcmp(iprice[i].pk, iprimary[j].pk)==0){
				ipaux = &iprimary[j];
				if(flag && ipaux->rrn != -1){
					printf("\n");
					flag = 0;
				}
				if(exibir_registro(ipaux->rrn, 1))
					flag = 1;
			}
		}
	}
}

void printaCategoria(Ip *iprimary, Ir *icategory, int nregistros, int ncat, char *find){
	Ir *iraux;
	ll *aux = NULL;
	int flag = 0;

	iraux = (Ir*)bsearch(find, icategory, ncat, sizeof(Ir), comparaCategoria);

	if(!iraux){
		printf(REGISTRO_N_ENCONTRADO);
		return;
	}

	aux = iraux->lista;

	while(aux != NULL){
		Ip *ipaux = (Ip*)bsearch(aux->pk, iprimary, nregistros, sizeof(Ip), comparaStringIprimary);
		if(flag){
			printf("\n");
			flag = 0;
		}
		if(exibir_registro(ipaux->rrn, 0))
			flag = 1;

		aux = aux->prox;
	}
}

int buscarChave(Ip* iprimary, char *key, int nregistros){
	for(int i = 0; i<nregistros; i++){
		if(strcmp(iprimary[i].pk, key)==0)
			if(iprimary[i].rrn != -1)
				return 1;
	}
	return 0;
}

void criar_iprimary(Ip *iprimary, int *nregistros){
	if(nregistros == 0)
		return;

	Produto temp;
	for(int i = 0; i < *nregistros; i++){
		temp = recuperar_registro(i);
		strcpy(iprimary[i].pk, temp.pk);
		iprimary[i].rrn = i;
	}
	ordenaPrimaria(iprimary, *nregistros);
}

void criar_iproduct(Is *isecondary, int* nregistros){
	if(nregistros == 0)
		return;

	Produto temp;
	for(int i = 0; i < *nregistros; i++){
		temp = recuperar_registro(i);
		strcpy(isecondary[i].string, temp.nome);
		strcpy(isecondary[i].pk, temp.pk);
	}
	ordenaProduct(isecondary, *nregistros);
}

void criar_ibrand(Is *isecondary, int* nregistros){
	if(nregistros == 0)
		return;

	Produto temp;
	for(int i = 0; i < *nregistros; i++){
		temp = recuperar_registro(i);
		strcpy(isecondary[i].string, temp.marca);
		strcpy(isecondary[i].pk, temp.pk);
	}
	ordenaProduct(isecondary, *nregistros);
}

void criar_isfprice(Isf *iprice, int *nregistros){
	if(nregistros == 0)
		return;

	int desc;
	float precofinal;
	Produto temp;
	for(int i = 0; i < *nregistros; i++){
		temp = recuperar_registro(i);
		sscanf(temp.desconto,"%d",&desc);
		sscanf(temp.preco,"%f",&precofinal);
		precofinal = (precofinal *  (100-desc))/100.0;
		precofinal = precofinal*100;
		precofinal = ((int) precofinal)/ (float) 100;
		iprice[i].price = precofinal;
		strcpy(iprice[i].pk, temp.pk);
	}
	ordenaPreco(iprice, *nregistros);
}

void criar_icategory(Ir *icategory, int *ncat, int nregistros){
	if(nregistros == 0 && *ncat == 0)
		return;

	if(*ncat != 0){
		for(int i = 0; i < *ncat; i++){
			free(icategory[i].lista);
			icategory[i].lista = NULL;
			strcpy(icategory[i].cat, "\0");
		}
	}

	Produto temp;
	*ncat = 0;
	for(int i = 0; i < nregistros; i++){
		temp = recuperar_registro(i);
		insereSecundariaCat(icategory, ncat, temp.categoria, temp.pk);
	}
}

void buscarProduto(Ip *iprimary, Is* iproduct, Is *ibrand, Ir* icategory, int nregistros, int ncat){
	int opBusca = 0;
	int flag = 0;
	Ip *ipaux;
	Is *isaux;
	Ir *iraux;
	ll *listaux;
	char aux[TAM_PRIMARY_KEY];
	char aux2[TAM_NOME];
	char aux3[TAM_MARCA];
	char aux4[TAM_CATEGORIA];
	scanf("%d", &opBusca);
	switch (opBusca){
		case 1:
			scanf("%s", aux);
			ipaux = (Ip*)bsearch(aux, iprimary, nregistros, sizeof(Ip), comparaStringIprimary);

			if(ipaux && ipaux->rrn != -1){
				exibir_registro(ipaux->rrn, 0);
			}
			else
				printf(REGISTRO_N_ENCONTRADO);
			break;

		case 2:
			scanf("%*c%[^\n]s", aux2);
			isaux = iproduct;

			for(int i = 0; i<nregistros; i++){
				if(strcmp(isaux[i].string, aux2)==0){
					for(int j = 0; j<nregistros; j++){
						if(strcmp(isaux[i].pk, iprimary[j].pk) == 0){
							ipaux = &iprimary[j];
							if(flag && ipaux->rrn != -1){
								printf("\n");
								flag = 0;
							}
							if(exibir_registro(ipaux->rrn, 0))
								flag = 1;
						}
					}
				}
			}

			if(!flag)
				printf(REGISTRO_N_ENCONTRADO);
			break;

		case 3:
			scanf("\n%[^\n]s", aux3);
			scanf("\n%[^\n]s", aux4);
			iraux = (Ir*)bsearch(aux4, icategory, ncat, sizeof(Ir), comparaCategoria);

			if(iraux){
				listaux = iraux->lista;
				isaux = ibrand;

				for(int i = 0; i<nregistros; i++){
					if(strcmp(isaux[i].string, aux3)==0){
						listaux = iraux->lista;
						while(listaux != NULL){
							if(strcmp(listaux->pk, isaux[i].pk)==0){
								for(int j = 0; j<nregistros; j++){
									if(strcmp(isaux[i].pk, iprimary[j].pk)==0){
										ipaux = &iprimary[j];
										if(flag && ipaux->rrn != -1){
											printf("\n");
											flag = 0;
										}
										if(exibir_registro(ipaux->rrn, 0))
											flag = 1;
									}
								}
							}
							listaux = listaux->prox;
						}
					}
				}
			}
			if(!flag)
				printf(REGISTRO_N_ENCONTRADO);
			break;
	}
}

void listarProdutos(Ip *iprimary, Isf* iprice, Is *ibrand, Ir* icategory, int nregistros, int ncat){
	int opListar = 0;
	int i;
	int flag = 0;
	int flag2 = 0;
	char auxcat[TAM_CATEGORIA];
	scanf("%d", &opListar);

	switch(opListar){
		case 1:
			for(i=0; i<nregistros; i++){
				if(flag){
					printf("\n");
					flag = 0;
				}
				if(exibir_registro(iprimary[i].rrn,0)){
					flag = 1;
					flag2 = 1;
				}
			}
			if(!flag2)
				printf(REGISTRO_N_ENCONTRADO);
			break;

		case 2:
			scanf("\n%[^\n]s", auxcat);
			printaCategoria(iprimary, icategory, nregistros, ncat, auxcat);
			break;

		case 3:
			printaMarcas(iprimary, ibrand, nregistros);
			break;

		case 4:
			printaPreco(iprimary, iprice, nregistros);
			break;
	}
}

int remover(Ip* iprimary, int nregistros){
	char rem[TAM_PRIMARY_KEY];
	int flag = 0;
	int pos;
	scanf("%s", rem);

	for(int i = 0; i<nregistros; i++){
		if(strcmp(iprimary[i].pk, rem)==0 && iprimary[i].rrn != -1){
			pos = (iprimary[i].rrn)*192;
			ARQUIVO[pos] = '*';
			ARQUIVO[pos+1] = '|';
			iprimary[i].rrn = -1;
			flag = 1;
		}
	}
	if(flag)
		return 1;
	else
		printf(REGISTRO_N_ENCONTRADO);
	return 0;
}

int alterar(Ip *iprimary, int nregistros, Isf *iprice){
	Ip *aux;
	int valido = 0;
	int tam = 0;
	char altpk[TAM_PRIMARY_KEY];
	char alt[TAM_DESCONTO];
	scanf("%s", altpk);
	aux = (Ip*)bsearch(altpk, iprimary, nregistros, sizeof(Ip), comparaStringIprimary);
	if(!aux || aux->rrn == -1){
		printf(REGISTRO_N_ENCONTRADO);
		return 0;
	}

	while(!valido){
		scanf("%s", alt);
		if(strcmp(alt, "000") < 0 || strcmp(alt, "100") > 0)
			printf(CAMPO_INVALIDO);
		else
			valido = 1;
	}

	Produto prod;
	prod = recuperar_registro(aux->rrn);
	float precofinal = atof(prod.preco);
	int desc = atoi(alt);
	precofinal = (precofinal *  (100-desc))/100.0;
	precofinal = precofinal*100;
	precofinal = ((int) precofinal)/ (float) 100;

	for(int i = 0; i < nregistros; i++){
		if(strcmp(altpk, iprice[i].pk)==0)
			iprice[i].price = precofinal;
	}

	ordenaPreco(iprice, nregistros);

	char temp[193], *p;
	strncpy(temp, ARQUIVO + ((aux->rrn)*192), 192);
	tam = (aux->rrn)*192;
	temp[192] = '\0';
	p = strtok(temp,"@");
	tam+=strlen(p);
	p = strtok(NULL,"@");
	tam+=strlen(p);
	p = strtok(NULL,"@");
	tam+=strlen(p);
	p = strtok(NULL,"@");
	tam+=strlen(p);
	p = strtok(NULL,"@");
	tam+=strlen(p);
	tam+=5;
	ARQUIVO[tam] = alt[0];
	ARQUIVO[tam+1] = alt[1];
	ARQUIVO[tam+2] = alt[2];
	return 1;
}

void limparArquivo(Ip *iprimary, int *nregistros, Is *iproduct, Is *ibrand, Isf *iprice, Ir *icategory, int *ncat){
	char arq[TAM_ARQUIVO];
	int count = 0;
	Produto temp;
	strcpy(arq, "");
	for(int i = 0; i < *nregistros; i++){
		temp = recuperar_registro(i);
		if(!(temp.nome[0]=='*' && temp.nome[1]=='|')){
			salvarProduto(arq, temp);
			count++;
		}
	}
	(*nregistros)=count;
	arq[sizeof(arq)-1] = '\0';
	strcpy(ARQUIVO, arq);

	criar_iprimary(iprimary, nregistros);
	criar_iproduct(iproduct, nregistros);
	criar_ibrand(ibrand, nregistros);
	criar_isfprice(iprice, nregistros);
	criar_icategory(icategory, ncat, *nregistros);
}

void liberarMemoria(Ip *iprimary, Is *iproduct, Is *ibrand, Isf *iprice, Ir *icategory, int nregistros, int ncat){
	int i;

	free(iprimary);
	free(iproduct);
	free(ibrand);
	free(iprice);

	for(i = 0; i < ncat; i++){
		ll *node = icategory[i].lista;
		ll *temp;
		while(node != NULL){
		    temp = node;
		    node = node->prox;
		    free(temp);
		}
		icategory[i].lista = NULL;
	}
	free(icategory);
}
