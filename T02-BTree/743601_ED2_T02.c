/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 02 - Árvore B
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
#define TAM_PRIMARY_KEY 11
#define TAM_NOME 51
#define TAM_MARCA 51
#define TAM_DATA 11
#define TAM_ANO 3
#define TAM_PRECO 8
#define TAM_DESCONTO 4
#define TAM_CATEGORIA 51
#define TAM_STRING_INDICE (TAM_MARCA + TAM_NOME)


#define TAM_REGISTRO 192
#define MAX_REGISTROS 1000
#define MAX_ORDEM 150
#define TAM_ARQUIVO (MAX_REGISTROS * TAM_REGISTRO + 1)


/* Saídas do usuário */
#define OPCAO_INVALIDA 				"Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE 		"Memoria insuficiente!\n"
#define REGISTRO_N_ENCONTRADO 		"Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO 				"Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA 			"ERRO: Ja existe um registro com a chave primaria: %s.\n"
#define ARQUIVO_VAZIO 				"Arquivo vazio!"
#define INICIO_BUSCA 				"********************************BUSCAR********************************\n"
#define INICIO_LISTAGEM				"********************************LISTAR********************************\n"
#define INICIO_ALTERACAO 			"********************************ALTERAR*******************************\n"
#define INICIO_ARQUIVO				"********************************ARQUIVO*******************************\n"
#define INICIO_INDICE_PRIMARIO      "***************************INDICE PRIMÁRIO****************************\n"
#define INICIO_INDICE_SECUNDARIO    "***************************INDICE SECUNDÁRIO**************************\n"
#define SUCESSO  				 	"OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					 	"FALHA AO REALIZAR OPERACAO!\n"
#define NOS_PERCORRIDOS_IP 			"Busca por %s. Nos percorridos:\n"
#define NOS_PERCORRIDOS_IS 			"Busca por %s.\nNos percorridos:\n"


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


/*Estrutura da chave de um nó do Índice Primário*/
typedef struct Chaveip
{
	char pk[TAM_PRIMARY_KEY];
	int rrn;
} Chave_ip;

/*Estrutura da chave de um  do Índice Secundário*/
typedef struct Chaveis
{
	char string[TAM_STRING_INDICE];
	char pk[TAM_PRIMARY_KEY];
} Chave_is;

/* Estrutura das Árvores-B */
typedef struct nodeip
{
	int num_chaves;		/* numero de chaves armazenadas*/
	Chave_ip *chave;		/* vetor das chaves e rrns [m-1]*/
	int *desc;	/* ponteiros para os descendentes, *desc[m]*/
	char folha;			/* flag folha da arvore*/
} node_Btree_ip;

typedef struct nodeis
{
	int num_chaves;		/* numero de chaves armazenadas*/
	Chave_is *chave;	/* vetor das chaves e rrns [m-1]*/
	int *desc;			/* ponteiros para os descendentes, *desc[m]*/
	char folha;			/* flag folha da arvore*/
} node_Btree_is;

typedef struct {
	int raiz;
} Indice;

typedef struct {
	char *pk;
	int rrn_pagina;
	int rrn;
} PromoIp;

typedef struct {
	char *pk;
	char *string;
	int rrn_pagina;
} PromoIs;

/* Variáveis globais */
char ARQUIVO[MAX_REGISTROS * TAM_REGISTRO + 1];
char ARQUIVO_IP[2000*sizeof(Chave_ip)];
char ARQUIVO_IS[2000*sizeof(Chave_is)];
/* Ordem das arvores */
int ordem_ip;
int ordem_is;
int nregistros;
int nregistrosip; /*Número de nós presentes no ARQUIVO_IP*/
int nregistrosis; /*Número de nós presentes no ARQUIVO_IS*/
/*Quantidade de bytes que ocupa cada nó da árvore nos arquivos de índice:*/
int tamanho_registro_ip;
int tamanho_registro_is;
/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */
// Gera a chave primaria do produto
void gerarChave(Produto *prod);
// Le do teclado as informacoes do produto
void inserir_produto(Produto *novo);
// Escreve as informacoes do produto no arquivo de dados
void salvarProduto(Produto p);
// Insercao auxiliar para o indice primario
PromoIp *insere_aux_ip(Indice *iprimary, Produto p);
// Operacao de split para o indice primario
PromoIp *divide_no_ip(Indice *iprimary, Produto p, int rrn, int *filho);
// Insercao auxiliar para o indice secundario
PromoIs *insere_aux_is(Indice *ibrand, Produto p);
// Operacao de split para o indice secundario
PromoIs *divide_no_is(Indice *iprimary, Produto p, int *filho);
// Busca pela chave primaria e imprime o progresso caso desejado
int *buscarChave(Indice *no, Produto p, int print);
// Busca por marca e nome retornando a chave primaria caso encontre
char *buscarSecundario(Indice *no, Produto p, int print);
// Chama o inserir para refazer os indices
void cadastra_indices(Indice *iprimary, Indice *ibrand);
// Imprime em pre ordem o indice primario
void printIp(int rrn, int altura);
// Imprime em in order o indice secundario
void printIs(int rrn, int altura);
/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

 /********************FUNÇÕES DO MENU*********************/
 void cadastrar(Indice* iprimary, Indice* ibrand);

 int alterar(Indice iprimary);

 void buscar(Indice iprimary,Indice ibrand);

 void listar(Indice iprimary,Indice ibrand);

 /*******************************************************/

 /* Recebe do usuário uma string simulando o arquivo completo e retorna o número
  * de registros. */
 int carregar_arquivo();

/* (Re)faz o Cria iprimary*/
void criar_iprimary(Indice *iprimary);

/* (Re)faz o índice dos produtos  */
void criar_ibrand(Indice *ibrand);

/*Escreve um nó da árvore no arquivo de índice,
* O terceiro parametro serve para informar qual indice se trata */
void write_btree(void *salvar, int rrn, char ip);

/*Lê um nó do arquivo de índice e retorna na estrutura*/
void *read_btree(int rrn, char ip);

/* Aloca um nó de árvore para ser utilizado em memória primária, o primeiro parametro serve para informar que árvore se trata
* É conveniente que essa função também inicialize os campos necessários com valores nulos*/
void *criar_no(char ip);

/*Libera todos os campos dinâmicos do nó, inclusive ele mesmo*/
void libera_no(void *node, char ip);

/*
*   Caro aluno,
*   caso não queira trabalhar com void*, é permitido dividir as funções que utilizam
* em duas, sendo uma para cada índice...
* Um exemplo, a write_btree e read_btree ficariam como:
*
*   void write_btree_ip(node_Btree_ip *salvar, int rrn),  node_Btree_ip *read_btree_ip(int rrn),
*   void write_btree_is(node_Btree_is *salvar, int rrn) e node_Btree_is *read_btree_is(int rrn).
*/

/* Atualiza os dois índices com o novo registro inserido */
void inserir_registro_indices(Indice *iprimary, Indice *ibrand, Produto p);

/* Exibe o Produto */
int exibir_registro(int rrn);
Produto recuperar_registro(int rrn);

int main()
{
	char *p; /* # */
  /* Arquivo */
	int carregarArquivo = 0; nregistros = 0, nregistrosip = 0, nregistrosis = 0;
	scanf("%d\n", &carregarArquivo); /* 1 (sim) | 0 (nao) */
	if (carregarArquivo)
		nregistros = carregar_arquivo();

	scanf("%d %d%*c", &ordem_ip, &ordem_is);

	tamanho_registro_ip = ordem_ip*3 + 4 + (-1 + ordem_ip)*14;
	// tamanho_registro_is = ordem_is*3 + 4 + (-1 + ordem_is)* (TAM_STRING_INDICE +9);
	tamanho_registro_is = 3 + (ordem_is - 1) * (10 + 101) + 1 + ordem_is * 3;

	/* Índice primário */
	Indice iprimary;
	criar_iprimary(&iprimary);

	/* Índice secundário de nomes dos Produtos */
	Indice ibrand;
	criar_ibrand(&ibrand);

	cadastra_indices(&iprimary, &ibrand);
	/* Execução do programa */
	int opcao = 0;
	while(1)
	{
		scanf("%d%*c", &opcao);
		switch(opcao) {
		case 1: /* Cadastrar um novo Produto */
			cadastrar(&iprimary, &ibrand);
			break;
		case 2: /* Alterar o desconto de um Produto */
			printf(INICIO_ALTERACAO);
			if (alterar(iprimary))
				printf(SUCESSO);
			else
				printf(FALHA);
			break;
		case 3: /* Buscar um Produto */
			printf(INICIO_BUSCA);
			buscar(iprimary, ibrand);
			break;
		case 4: /* Listar todos os Produtos */
			printf(INICIO_LISTAGEM);
			listar(iprimary, ibrand);
			break;
		case 5: /* Imprimir o arquivo de dados */
			printf(INICIO_ARQUIVO);
			printf("%s\n", (*ARQUIVO!='\0') ? ARQUIVO : ARQUIVO_VAZIO);
			break;
		case 6: /* Imprime o Arquivo de Índice Primário*/
			printf(INICIO_INDICE_PRIMARIO);
			if(!*ARQUIVO_IP)
				puts(ARQUIVO_VAZIO);
			else
				for(p = ARQUIVO_IP; *p!='\0'; p+=tamanho_registro_ip)
				{
					fwrite( p , 1 ,tamanho_registro_ip,stdout);
					puts("");
				}
			break;
		case 7: /* Imprime o Arquivo de Índice Secundário*/
			printf(INICIO_INDICE_SECUNDARIO);
			if(!*ARQUIVO_IS)
				puts(ARQUIVO_VAZIO);
			else
				for(p = ARQUIVO_IS; *p!='\0'; p+=tamanho_registro_is)
				{
					fwrite( p , 1 ,tamanho_registro_is,stdout);
					puts("");

				}
			break;
		case 8: /*Libera toda memória alocada dinâmicamente (se ainda houver) e encerra*/
			return 0;
		default: /* exibe mensagem de erro */
			printf(OPCAO_INVALIDA);
			break;
		}
	}
	return -1;
}

/* ==========================================================================
 * ================================= FUNÇÕES ================================
 * ========================================================================== */

/* Recebe do usuário uma string simulando o arquivo completo e retorna o número
 * de registros. */
int carregar_arquivo(){
	scanf("%[^\n]\n", ARQUIVO);
	return strlen(ARQUIVO) / TAM_REGISTRO;
}


/* Exibe o Produto */
int exibir_registro(int rrn){
	if(rrn < 0)
		return 0;

	float preco;
	int desconto;
	Produto j = recuperar_registro(rrn);
    char *cat, categorias[TAM_CATEGORIA];

	printf("%s\n", j.pk);
	printf("%s\n", j.nome);
	printf("%s\n", j.marca);
	printf("%s\n", j.data);
	printf("%s\n", j.ano);
	sscanf(j.desconto,"%d",&desconto);
	sscanf(j.preco,"%f",&preco);
	preco = preco *  (100-desconto);
	preco = ((int) preco)/ (float) 100 ;
	printf("%07.2f\n",  preco);
	strcpy(categorias, j.categoria);

	for (cat = strtok (categorias, "|"); cat != NULL; cat = strtok (NULL, "|"))
    	printf("%s ", cat);
	printf("\n");

	return 1;
}

// Retorna um Produto a partir do seu RRN
Produto recuperar_registro(int rrn){
	char *temp, *p;
	temp = (char*)calloc(TAM_REGISTRO + 1, sizeof(char));
	strncpy(temp, ARQUIVO + ((rrn)*192), 192);
	temp[192] = '\0';
	Produto j;
	p = strtok(temp,"@");
	strcpy(j.pk,p);
	p = strtok(NULL,"@");
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

// Cria a chave primaria do produto
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

// Le do teclado os dados do produto
void inserir_produto(Produto *novo){
	scanf("\n%[^\n]s", novo->nome);
	scanf("\n%[^\n]s", novo->marca);
	scanf("\n%[^\n]s", novo->data);
	scanf("\n%[^\n]s", novo->ano);
	scanf("\n%[^\n]s", novo->preco);
	scanf("\n%[^\n]s", novo->desconto);
	scanf("\n%[^\n]s", novo->categoria);
	gerarChave(novo);
}

// Faz as chamadas necessarias do inserir_produto para inserir nas arvores B
void cadastrar(Indice* iprimary, Indice* ibrand){
	Produto *prod = (Produto *)malloc(sizeof(Produto));
	inserir_produto(prod);

	if(nregistros != 0){
		if(buscarChave(iprimary, *prod, 0) != NULL){
			printf(ERRO_PK_REPETIDA, prod->pk);
			free(prod);
			return;
		}
		else{
			inserir_registro_indices(iprimary, ibrand, *prod);
			nregistros++;
			salvarProduto(*prod);
			return;
		}
	}
	else{
		inserir_registro_indices(iprimary, ibrand, *prod);
		nregistros++;
		salvarProduto(*prod);
	}
}

// Escreve os dados do produto no arquivo de dados
void salvarProduto(Produto p){
	char temp[193];
	sprintf(temp, "%s@%s@%s@%s@%s@%s@%s@%s@", p.pk, p.nome, p.marca, p.data, p.ano, p.preco,
	p.desconto, p.categoria);
	int tam = strlen(temp);
	if(tam < 192){
		for(; tam < 192; tam++){
			strcat(temp, "#");
		}
	}
	strcat(ARQUIVO, temp);
}

// Aloca um no da arvore b
void *criar_no(char ip){
   switch (ip) {
	   case 'p':{
		   node_Btree_ip *no = (node_Btree_ip *)calloc(1, sizeof(node_Btree_ip));
		   no->num_chaves = 0;
		   no->chave = (Chave_ip *)calloc((ordem_ip -1), sizeof(Chave_ip));
		   no->desc = (int *)malloc(ordem_ip * sizeof(int));
		   no->folha = 'F';
		   return no;
	   break;
	   }

	   case 's':{
		   node_Btree_is *no = (node_Btree_is *)calloc(1, sizeof(node_Btree_is));
		   no->num_chaves = 0;
		   no->chave = (Chave_is *)calloc((ordem_is -1), sizeof(Chave_is));
		   no->desc = (int *)calloc(ordem_is, sizeof(int));
		   no->folha = 'F';
		   return no;
	   break;
	   }
   }
  return NULL;
}

// Inicializa a raiz da arvore primaria
void criar_iprimary(Indice *iprimary){
   iprimary->raiz = -1;
}

// Inicializa a raiz da arvore secundaria
void criar_ibrand(Indice *ibrand){
	ibrand->raiz = -1;
}

// Chama a funcao de insercao para construir as arvores a partir do caso em que o arquivo ja existe
void cadastra_indices(Indice *iprimary, Indice *ibrand){
	int nregaux = nregistros;
	Produto prod;
	for(nregistros = 0; nregistros < nregaux; nregistros++){
		prod = recuperar_registro(nregistros);
	    inserir_registro_indices(iprimary, ibrand, prod);
	}
}

// Funcao principal de insercao
void inserir_registro_indices(Indice *iprimary, Indice *ibrand, Produto p){
	// Caso da arvore vazia
	if(iprimary->raiz == -1){ //Cria uma pagina e insere os dados
		node_Btree_ip *no = criar_no('p');
		no->folha = 'F';
		no->num_chaves = 1;
		strcpy(no->chave[0].pk, p.pk);
		no->chave[0].rrn = nregistros;
		iprimary->raiz = 0;

		//Escreve no arquivo de indice primario
		write_btree(no, iprimary->raiz, 'p');
		libera_no(no, 'p');
		nregistrosip++;
	}

	else{ //Arvore nao vazia;
		PromoIp *aux = insere_aux_ip(iprimary, p);
		if(aux->pk != NULL){ //Houve promocao de chave
			node_Btree_ip *no = criar_no('p');
			no->folha = 'N';
			no->num_chaves = 1;
			strcpy(no->chave[0].pk, aux->pk);
			no->chave[0].rrn = aux->rrn;

			no->desc[0] = iprimary->raiz;
 			no->desc[1] = aux->rrn_pagina;

			iprimary->raiz = nregistrosip;
			write_btree(no, nregistrosip, 'p');
			nregistrosip++;
			libera_no(no, 'p');
			free(aux);
		}
	}

	//Insercao no ibrand
	if(ibrand->raiz == -1){
		node_Btree_is *no = criar_no('s');
 		no->folha = 'F';
 		no->num_chaves = 1;

 		strcpy(no->chave[0].pk, p.pk);
    	sprintf(no->chave[0].string, "%s$%s", p.marca, p.nome);
		ibrand->raiz = 0;

		write_btree(no, ibrand->raiz, 's');
		libera_no(no, 's');
		nregistrosis++;
	}

	else{
		PromoIs *aux = insere_aux_is(ibrand, p);

		if(aux->string != NULL){
			node_Btree_is *no = criar_no('s');
			no->folha = 'N';
			no->num_chaves = 1;
			strcpy(no->chave[0].pk, aux->pk);
			strcpy(no->chave[0].string, aux->string);

			no->desc[0] = ibrand->raiz;
 			no->desc[1] = aux->rrn_pagina;

			ibrand->raiz = nregistrosis;
			write_btree(no, ibrand->raiz, 's');
			nregistrosis++;
			libera_no(no, 's');
			free(aux);
		}
	}
}

// Funcao de insercao auxiliar para a arvore primaria
PromoIp *insere_aux_ip(Indice *iprimary, Produto p){
	node_Btree_ip *no = read_btree(iprimary->raiz, 'p');
 	PromoIp *nulo = (PromoIp *)calloc(1, sizeof(PromoIp));
 	nulo->pk = (char *)calloc(11, sizeof(char));
 	int i;

	//Se a chave for folha, verificar se ha espaco naquela pagina
	// e insere na posicao correta
	if(no->folha == 'F'){
		if(no->num_chaves < ordem_ip -1){
			i = no->num_chaves - 1;
			while(i >= 0 && strcmp(no->chave[i].pk, p.pk) > 0){
				no->chave[i+1] = no->chave[i];
				i--;
			}
			strcpy(no->chave[i+1].pk, p.pk);
			no->chave[i+1].rrn = nregistros;
			no->num_chaves++;

			write_btree(no, iprimary->raiz, 'p');
			libera_no(no, 'p');

			nulo->pk =  NULL;
			nulo->rrn = -1;
			nulo->rrn_pagina = -1;

			return nulo;
		}
		// Caso de overflow
		else{
			free(nulo->pk);
			free(nulo);
			return divide_no_ip(iprimary, p, nregistros, NULL);
		}
	}
	// Caso o no nao seja folha
	else{
		i = no->num_chaves - 1;
		while(i >= 0 && strcmp(no->chave[i].pk, p.pk) > 0){
			i--;
		}
		i++;
		Indice *aux = (Indice *)calloc(1, sizeof(Indice));
 		aux->raiz = no->desc[i];
		free(nulo->pk);
		free(nulo);

		nulo = insere_aux_ip(aux, p);

		//Caso houver promocao de chave
		if(nulo->pk != NULL){
			strcpy(p.pk, nulo->pk); //p recebe a chave promovida
			if(no->num_chaves < ordem_ip - 1){
				i = no->num_chaves - 1;
				while(i >= 0 && strcmp(no->chave[i].pk, p.pk) > 0){
					no->chave[i+1] = no->chave[i];
					no->desc[i+2] = no->desc[i+1];
					i--;
				}

				strcpy(no->chave[i+1].pk, p.pk);
				no->chave[i + 1].rrn = nulo->rrn;
				no->desc[i + 2] = nulo->rrn_pagina;
				no->num_chaves++;

				write_btree(no, iprimary->raiz, 'p');
				libera_no(no, 'p');

				nulo->pk = NULL;
				nulo->rrn = -1;
				nulo->rrn_pagina = -1;

				return(nulo);
			}
			else
				return divide_no_ip(iprimary, p, nulo->rrn, &nulo->rrn_pagina);
		}
		// Caso nao ocorra promocao
		else{
			write_btree(no, iprimary->raiz, 'p');
			libera_no(no, 'p');
			nulo->pk = NULL;
			nulo->rrn = -1;
			nulo->rrn_pagina = -1;
			return nulo;
		}
	}
}

// Funcao auxiliar para insercao na arvore secundaria
PromoIs *insere_aux_is(Indice *ibrand, Produto p){
	node_Btree_is *no = read_btree(ibrand->raiz, 's');
	Chave_is *aux = (Chave_is *)calloc(1, sizeof(Chave_is));
 	PromoIs *nulo = (PromoIs *)calloc(1, sizeof(PromoIs));
 	nulo->pk = (char *)calloc(11, sizeof(char));
	nulo->string = (char *)calloc(TAM_STRING_INDICE, sizeof(char));
 	int i;
	char *stringaux;
	sprintf(aux->string, "%s$%s", p.marca, p.nome);
	strcpy(aux->pk, p.pk);

	//Se a chave for folha, verificar se ha espaco naquela pagina
	// e insere na posicao correta
	if(no->folha == 'F'){
		if(no->num_chaves < ordem_is -1){
			i = no->num_chaves - 1;
			while(i >= 0 && strcmp(no->chave[i].string, aux->string) > 0){
				no->chave[i+1] = no->chave[i];
				i--;
			}
			strcpy(no->chave[i+1].pk, aux->pk);
			sprintf(no->chave[i+1].string, "%s", aux->string);
			no->num_chaves++;

			write_btree(no, ibrand->raiz, 's');
			libera_no(no, 's');

			nulo->pk =  NULL;
			nulo->string = NULL;
			nulo->rrn_pagina = -1;

			return nulo;
		}
		// Caso de overflow
		else{
			free(nulo->pk);
			free(nulo->string);
			free(nulo);
			return divide_no_is(ibrand, p, NULL);
		}
	}
	// Caso o no nao seja folha
	else{
		i = no->num_chaves - 1;
		while(i >= 0 && strcmp(no->chave[i].string, aux->string) > 0){
			i--;
		}
		i++;
		Indice *noaux = (Indice *)calloc(1, sizeof(Indice));
 		noaux->raiz = no->desc[i];

		free(nulo->pk);
		free(nulo->string);
		free(nulo);
		nulo = insere_aux_is(noaux, p);

		//Caso houver promocao de chave
		if(nulo->string != NULL){
			strcpy(aux->pk, nulo->pk); //aux recebe a chave promovida
			strcpy(aux->string, nulo->string);
			sprintf(p.pk, "%s", nulo->pk);
			stringaux = nulo->string;
			for(i = 0; stringaux[i] != '$'; i++);
			strncpy(p.marca, stringaux, i);
			p.marca[i] = '\0';
			stringaux = stringaux+i+1;
			strcpy(p.nome, stringaux);

			if(no->num_chaves < ordem_is - 1){
				i = no->num_chaves - 1;
				while(i >= 0 && strcmp(no->chave[i].string, aux->string) > 0){
					no->chave[i+1] = no->chave[i];
					no->desc[i+2] = no->desc[i+1];
					i--;
				}

				strcpy(no->chave[i+1].pk, aux->pk);
				strcpy(no->chave[i+1].string, aux->string);
				no->desc[i + 2] = nulo->rrn_pagina;
				no->num_chaves++;

				write_btree(no, ibrand->raiz, 's');
				libera_no(no, 's');

				nulo->pk = NULL;
				nulo->string = NULL;
				nulo->rrn_pagina = -1;

				return(nulo);
			}
			else
				return divide_no_is(ibrand, p, &nulo->rrn_pagina);
		}
		// Caso nao ocorra promocao
		else{
			write_btree(no, ibrand->raiz, 's');
			libera_no(no, 's');
			nulo->pk = NULL;
			nulo->string = NULL;
			nulo->rrn_pagina = -1;
			return nulo;
		}
	}
}

// Funcao para realizar split na arvore primaria
PromoIp *divide_no_ip(Indice *iprimary, Produto p, int rrn, int *filho){
	node_Btree_ip *aux = read_btree(iprimary->raiz, 'p');
	int i = aux->num_chaves - 1;
	int key = 0;

	node_Btree_ip *novo = criar_no('p');
	novo->folha = aux->folha;
	novo->num_chaves = (ordem_ip - 1)/2;

	for(int j = novo->num_chaves-1; j >= 0; j--){
		if(!key && strcmp(p.pk, aux->chave[i].pk) > 0){
			strcpy(novo->chave[j].pk, p.pk);
			novo->chave[j].rrn = rrn;
			if(filho != NULL)
				novo->desc[j+1] = *filho;
			else
				novo->desc[j+1] = -1;

			key = 1;
		}
		else{
			novo->chave[j] = aux->chave[i];
			novo->desc[j+1] = aux->desc[i+1];
			i--;
		}
	}

	if(!key){
		while(i >= 0 && strcmp(p.pk, aux->chave[i].pk) < 0){
			aux->chave[i+1] = aux->chave[i];
			aux->desc[i+2] = aux->desc[i+1];
			i--;
		}
		strcpy(aux->chave[i+1].pk , p.pk);
		aux->chave[i+1].rrn = rrn;
		if(filho != NULL)
			aux->desc[i+2] = *filho;
		else
			aux->desc[i+2] = -1;
	}
	PromoIp *promo = (PromoIp *)malloc(sizeof(PromoIp));
	promo->pk = (char*)calloc(TAM_PRIMARY_KEY, sizeof(char));
	strncpy(promo->pk, aux->chave[ordem_ip/2].pk, TAM_PRIMARY_KEY);
	promo->pk[10] = '\0';
	promo->rrn_pagina = nregistrosip;
	promo->rrn = aux->chave[ordem_ip/2].rrn;
	novo->desc[0] = aux->desc[ordem_ip/2+1];
	aux->num_chaves = ordem_ip/2;

	write_btree(aux, iprimary->raiz, 'p');
	write_btree(novo, nregistrosip, 'p');
	nregistrosip++;
	libera_no(aux, 'p');
	libera_no(novo, 'p');
	return(promo);
}

// Funcao para realizar split na arvore secundaria
PromoIs *divide_no_is(Indice *ibrand, Produto p, int *filho){
	node_Btree_is *aux = read_btree(ibrand->raiz, 's');
	int i = aux->num_chaves - 1;
	int key = 0;
	Chave_is *chaveaux = (Chave_is *)calloc(1, sizeof(Chave_is));
	sprintf(chaveaux->string, "%s$%s", p.marca, p.nome);
	// printf("chave: %s\n", chaveaux->string);
	strcpy(chaveaux->pk, p.pk);

	node_Btree_is *novo = criar_no('s');
	novo->folha = aux->folha;
	novo->num_chaves = (ordem_is - 1)/2;

	for(int j = novo->num_chaves-1; j >= 0; j--){
		if(!key && strcmp(chaveaux->string, aux->chave[i].string) > 0){
			strcpy(novo->chave[j].pk, chaveaux->pk);
			strcpy(novo->chave[j].string, chaveaux->string);
			if(filho != NULL)
				novo->desc[j+1] = *filho;
			else
				novo->desc[j+1] = -1;

			key = 1;
		}
		else{
			novo->chave[j] = aux->chave[i];
			novo->desc[j+1] = aux->desc[i+1];
			i--;
		}
	}

	if(!key){
		while(i >= 0 && strcmp(chaveaux->string, aux->chave[i].string) < 0){
			aux->chave[i+1] = aux->chave[i];
			aux->desc[i+2] = aux->desc[i+1];
			i--;
		}

		strcpy(aux->chave[i+1].pk , chaveaux->pk);
		strcpy(aux->chave[i+1].string , chaveaux->string);

		if(filho != NULL)
			aux->desc[i+2] = *filho;
		else
			aux->desc[i+2] = -1;
	}
	PromoIs *promo = (PromoIs *)calloc(1, sizeof(PromoIs));
	promo->pk = (char*)calloc(TAM_PRIMARY_KEY, sizeof(char));
	promo->string = (char*)calloc(TAM_STRING_INDICE, sizeof(char));

	strcpy(promo->pk, aux->chave[ordem_is/2].pk);
	strcpy(promo->string, aux->chave[ordem_is/2].string);

	promo->rrn_pagina = nregistrosis;
	novo->desc[0] = aux->desc[ordem_is/2+1];
	aux->num_chaves = ordem_is/2;

	write_btree(aux, ibrand->raiz, 's');
	write_btree(novo, nregistrosis, 's');
	nregistrosis++;
	libera_no(aux, 's');
	libera_no(novo, 's');
	return(promo);
}

// Funcao de busca por chave primaria ou por nome/marca
void buscar(Indice iprimary, Indice ibrand){
	int op;
	Produto p;
	char aux[TAM_STRING_INDICE];
	int *find;
	char *findis;
	scanf("%d%*c", &op);
	switch(op){
		case 1:
			scanf("\n%[^\n]s", p.pk);
			printf(NOS_PERCORRIDOS_IP, p.pk);
			if(iprimary.raiz == -1){
				printf(REGISTRO_N_ENCONTRADO);
				return;
			}
			find = buscarChave(&iprimary, p, 1);
			printf("\n");
			if(find != NULL){
				exibir_registro(*find);
			}
			else
				printf(REGISTRO_N_ENCONTRADO);
			break;

		case 2:
			scanf("\n%[^\n]s", p.marca);
			scanf("\n%[^\n]s", p.nome);
			sprintf(aux, "%s$%s", p.marca, p.nome);
			printf(NOS_PERCORRIDOS_IS, aux);
			if(ibrand.raiz == -1){
				printf(REGISTRO_N_ENCONTRADO);
				return;
			}
			findis = buscarSecundario(&ibrand, p, 1);
			printf("\n");
			if(findis != NULL){
				strcpy(p.pk, findis);
				find = buscarChave(&iprimary, p, 0);
				exibir_registro(*find);
			}
			else
				printf(REGISTRO_N_ENCONTRADO);
			break;
	}
}

// Busca pela chave primaria inserida e retorna seu rrn
int *buscarChave(Indice *no, Produto p, int print){
	node_Btree_ip *aux = read_btree(no->raiz, 'p');
	int i;
	if(print){
		for(i = 0; i < aux->num_chaves; i++){
			printf("%s", aux->chave[i].pk);
			if(i < aux->num_chaves - 1)
				printf(", ");
		}
		printf("\n");
	}
	for(i = 0; i <= aux->num_chaves -1 && strcmp(aux->chave[i].pk, p.pk) < 0; i++);

	if(i <= aux->num_chaves - 1 && strcmp(aux->chave[i].pk, p.pk) == 0){
		return &aux->chave[i].rrn;
	}

	if(aux->folha == 'F'){
		libera_no(aux, 'p');
		return NULL;
	}
	else{
		Indice *prox = (Indice *)calloc(1, sizeof(Indice));
		prox->raiz = aux->desc[i];
		libera_no(aux, 'p');
		return buscarChave(prox, p, print);
	}
}

// Busca por nome/marca, retorna uma chave primaria que deve ser buscada depois para conseguir o rrn
char *buscarSecundario(Indice *no, Produto p, int print){
	node_Btree_is *aux = read_btree(no->raiz, 's');
	Chave_is *chaveaux = (Chave_is *)calloc(1, sizeof(Chave_is));
    sprintf(chaveaux->string, "%s$%s", p.marca, p.nome);
	int i;
	if(print){
		for(i = 0; i < aux->num_chaves; i++){
			printf("%s", aux->chave[i].string);
			if(i < aux->num_chaves - 1)
				printf(", ");
		}
		printf("\n");
	}
	for(i = 0; i <= aux->num_chaves -1 && strcmp(aux->chave[i].string, chaveaux->string) < 0; i++);

	if(i <= aux->num_chaves - 1 && strcmp(aux->chave[i].string, chaveaux->string) == 0){
		return aux->chave[i].pk;
	}

	if(aux->folha == 'F'){
		libera_no(aux, 's');
		return NULL;
	}
	else{
		Indice *prox = (Indice *)calloc(1, sizeof(Indice));
		prox->raiz = aux->desc[i];
		libera_no(aux, 's');
		return buscarSecundario(prox, p, print);
	}
}

// Funcao de escrita no arquivo de indices
void write_btree(void *salvar, int rrn, char ip){
	//Escreve no arquivo de indice primario
	int buffer = 0, i;
	if(ip == 'p'){
		char *aux = (char *)calloc(tamanho_registro_ip + 1, sizeof(char));
		//Escreve num_chaves
		sprintf(aux, "%03d", ((node_Btree_ip*)salvar)->num_chaves);
		strncpy(&ARQUIVO_IP[tamanho_registro_ip*rrn], aux, strlen(aux));
		buffer += 3;

		//Escreve para cada chave a pk e o rrn
		for(i = 0; i < ((node_Btree_ip*)salvar)->num_chaves; i++){
			sprintf(aux, "%04d", ((node_Btree_ip*)salvar)->chave[i].rrn);
			strncpy(&ARQUIVO_IP[tamanho_registro_ip*rrn + buffer], ((node_Btree_ip*)salvar)->chave[i].pk, 10);
			buffer += 10;
			strncpy(&ARQUIVO_IP[tamanho_registro_ip*rrn + buffer], aux, strlen(aux));
			buffer += 4;
		}
		for (i = buffer; i < (ordem_ip - 1) * 14 + 3; i++){
			ARQUIVO_IP[tamanho_registro_ip*rrn + i] = '#';
			buffer++;
		}
		//Escreve o bool folha
		ARQUIVO_IP[tamanho_registro_ip*rrn + buffer] = ((node_Btree_ip*)salvar)->folha;
		buffer++;

		//Caso não seja folha escreve o rrn de seus descendentes
		if (((node_Btree_ip*)salvar)->folha == 'N'){
			for(i = 0; i < ((node_Btree_ip*)salvar)->num_chaves + 1; i++){
				sprintf(aux, "%03d", ((node_Btree_ip*)salvar)->desc[i]);
				strncpy(&ARQUIVO_IP[tamanho_registro_ip*rrn + buffer], aux, strlen(aux));
				buffer += 3;
			}
			for( ; i < ordem_ip; i++){
				sprintf(aux, "***");
				strncpy(&ARQUIVO_IP[tamanho_registro_ip*rrn + buffer], aux, strlen(aux));
				buffer += 3;
			}
		}
		else{
			//Caso o no seja folha
			for(i = 0; i < ordem_ip; i++){
				sprintf(aux, "***");
				strncpy(&ARQUIVO_IP[tamanho_registro_ip*rrn + buffer], aux, strlen(aux));
				buffer += 3;
			}
		}
		free(aux);
	}
	//Escreve no arquivo de indice secundario
	else{
		char *aux2 = (char*)calloc((tamanho_registro_is + 1), sizeof(char));
		buffer = 0;
		//Escreve num_chaves
		sprintf(aux2, "%03d", ((node_Btree_is*)salvar)->num_chaves);
		strncpy(&ARQUIVO_IS[tamanho_registro_is*rrn], aux2, strlen(aux2));
		buffer += 3;

		for(i = 0; i < ((node_Btree_is*)salvar)->num_chaves; i++){
			int tam = strlen(((node_Btree_is*)salvar)->chave[i].pk) + strlen(((node_Btree_is*)salvar)->chave[i].string);
			sprintf(aux2, "%s%s", ((node_Btree_is*)salvar)->chave[i].pk, ((node_Btree_is*)salvar)->chave[i].string);
			strncpy(&ARQUIVO_IS[tamanho_registro_is*rrn + buffer], aux2, strlen(aux2));
			for(; tam < 111; tam++){
				ARQUIVO_IS[tamanho_registro_is*rrn + buffer + tam] = '#';
			}
			buffer += 111;
		}

		for (; buffer < (ordem_is - 1) * 111 + 3; buffer++){
			ARQUIVO_IS[tamanho_registro_is*rrn + buffer] = '#';
		}
		//Escreve o bool folha
		ARQUIVO_IS[tamanho_registro_is*rrn + buffer] = ((node_Btree_is*)salvar)->folha;
		buffer++;

		//Caso seja um no interno
		if(((node_Btree_is*)salvar)->folha == 'N'){
			for (i = 0; i < ((node_Btree_is*)salvar)->num_chaves + 1; i++) {
				sprintf(aux2, "%03d", ((node_Btree_is*)salvar)->desc[i]);
				strncpy(&ARQUIVO_IS[tamanho_registro_is*rrn + buffer], aux2, strlen(aux2));
				buffer += 3;
			}
			for( ; buffer < tamanho_registro_is; buffer++){
				ARQUIVO_IS[tamanho_registro_is*rrn + buffer] = '*';
			}
		}
		else{
			for(i = 0 ; i < ordem_is; i++){
				sprintf(aux2, "***");
				strncpy(&ARQUIVO_IS[tamanho_registro_is*rrn + buffer], aux2, strlen(aux2));
				buffer += 3;
			}
		}
		free(aux2);
	}
}

// Funcao de leitura do arquivo de indices para reconstruir um no na ram
void *read_btree(int rrn, char ip){
	//Leitura na arvore iprimary
	int buffer = 0, i;
	if(ip == 'p'){
		node_Btree_ip *l = criar_no('p');
		// l->chave = malloc(sizeof(Chave_ip) * (ordem_ip - 1));
		// l->desc = malloc(sizeof(int) * ordem_ip);

		char aux[tamanho_registro_ip];
		for (i = 0; i < tamanho_registro_ip; i++) {
			aux[i] = ARQUIVO_IP[tamanho_registro_ip*rrn + i];
		}
		aux[i] = '\0';
		//Salva o numero de chaves do no
		sscanf(aux, "%3d", &l->num_chaves);
		buffer += 3;

		for(i = 0; i < l->num_chaves; i++){
			//Salva a pk
			strncpy(l->chave[i].pk, &aux[buffer], 10);
			l->chave[i].pk[10] = '\0';
			buffer += 10;
			//Salva o rrn
			sscanf(&aux[buffer], "%4d", &l->chave[i].rrn);
			buffer += 4;
		}
		//Le se o no e folha ou nao
		buffer += ((ordem_ip - 1) - l->num_chaves) * 14;
		l->folha = aux[buffer];
		buffer++;

		//Caso nao seja folha le os descendentes
		if(l->folha == 'N'){
			for(i = 0; i < ordem_ip; i++){
				sscanf(&aux[buffer], "%3d", &l->desc[i]);
				buffer += 3;
			}
		}
		return l;
	}
	//Leitura na arvore ibrand
	else{
		node_Btree_is *l = criar_no('s');
		char aux[tamanho_registro_is];
		for (i = 0; i < tamanho_registro_is; i++) {
			aux[i] = ARQUIVO_IS[tamanho_registro_is*rrn + i];
		}
		aux[i] = '\0';
		//Salva o numero de chaves do no
		free(l->chave);
		free(l->desc);
		l->chave = calloc((ordem_is - 1), sizeof(Chave_is));
		l->desc = malloc(sizeof (int) * ordem_is);
		sscanf(aux, "%3d", &l->num_chaves);
		buffer += 3;

		for(i = 0; i < l->num_chaves; i++){
			//Salva a pk
			strncpy(l->chave[i].pk, &aux[buffer], 10);
			l->chave[i].pk[10] = '\0';
			buffer += 10;
			//Salva o rrn
			sscanf(&aux[buffer] , "%[^#\n]", l->chave[i].string);
			buffer += 101;
		}
		//Le se o no e folha ou nao
		buffer += ((ordem_is - 1) - l->num_chaves) * 111;
		l->folha = aux[buffer];
		buffer++;

		//Caso seja folha le os descendentes
		if(l->folha == 'N'){
			for(i = 0; i < ordem_is; i++){
				sscanf(&aux[buffer], "%3d", &l->desc[i]);
				buffer += 3;
			}
		}
		return l;
	}
}

// Imprime as arvores
void listar(Indice iprimary, Indice ibrand){
	int op = 0;
	scanf("%d%*c", &op);
	switch(op){
		case 1:
			if(iprimary.raiz == -1){
				printf(REGISTRO_N_ENCONTRADO);
				return;
			}
			else
				printIp(iprimary.raiz, 1);
		break;

		case 2:
			if(ibrand.raiz == -1){
				printf(REGISTRO_N_ENCONTRADO);
				return;
			}
			else
				printIs(ibrand.raiz, 1);
		break;
	}
}

// Imprime a arvore primaria em pre-ordem
void printIp(int rrn, int altura){
	int i;
	node_Btree_ip *aux = read_btree(rrn, 'p');
	printf("%d - ", altura);
	for(i = 0; i < aux->num_chaves; i++){
		printf("%s", aux->chave[i].pk);
		if(i < aux->num_chaves - 1)
			printf(", ");
	}
	printf("\n");

	if(aux->folha == 'N'){
		for(i = 0; i < aux->num_chaves + 1; i++){
			printIp(aux->desc[i], altura+1);
		}
	}
	else{
		libera_no(aux, 'p');
		return;
	}
	libera_no(aux, 'p');
}

// Imprime a arvore secundaria em in-order
void printIs(int rrn, int altura){
	int i, j;
	node_Btree_is *aux = read_btree(rrn, 's');
	if(aux->folha == 'F'){
		char marca[TAM_MARCA], nome[TAM_NOME], string[TAM_STRING_INDICE];
		for(i = 0; i < aux->num_chaves; i++){
			strcpy(string, aux->chave[i].string);
			strcpy(marca, strtok(string, "$"));
			strcpy(nome, strtok(NULL, "$"));

			printf("%s", marca);
			for(int k = 0; k < 50 - strlen(marca); k++){
				printf("-");
			}
			printf(" ");

			printf("%s", nome);
			for(int k = 0; k < 50 - strlen(nome); k++){
				printf("-");
			}
			printf("\n");
		}
	}
	else{
		char marca[TAM_MARCA], nome[TAM_NOME], string[TAM_STRING_INDICE];
		for (j = 0; j < aux->num_chaves; j++){
			printIs(aux->desc[j], altura+1);

			strcpy(string, aux->chave[j].string);
			strcpy(marca, strtok(string, "$"));
			strcpy(nome, strtok(NULL, "$"));

			printf("%s", marca);
			for(int k = 0; k < 50 - strlen(marca); k++){
				printf("-");
			}
			printf(" ");

			printf("%s", nome);
			for(int k = 0; k < 50 - strlen(nome); k++){
				printf("-");
			}
			printf("\n");

		}
		printIs(aux->desc[j], altura +1);
	}
	libera_no(aux, 's');
}

// Desaloca os campos da struct do no da arvore
void libera_no(void *node, char ip){
	if (ip == 'p') {
		free(((node_Btree_ip*)node)->chave);
		free(((node_Btree_ip*)node)->desc);
		free(((node_Btree_ip*)node));
	}
	else {
		free(((node_Btree_is*)node)->chave);
		free(((node_Btree_is*)node)->desc);
		free(((node_Btree_is*)node));
	}
}

// Encontra o rrn pela chave primaria e altera o campo desconto no arquivo de dados
int alterar(Indice iprimary){
	int valido = 0;
	int *find;
	int tam;
	char altpk[TAM_PRIMARY_KEY];
	char alt[TAM_DESCONTO];
	Produto busca;
	scanf("%s", altpk);
	strcpy(busca.pk, altpk);

	if(iprimary.raiz == -1){
		printf(REGISTRO_N_ENCONTRADO);
		return 0;
	}

	find = buscarChave(&iprimary, busca, 0);
	if(!find){
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
	prod = recuperar_registro(*find);
	float precofinal = atof(prod.preco);
	int desc = atoi(alt);
	precofinal = (precofinal *  (100-desc))/100.0;
	precofinal = precofinal*100;
	precofinal = ((int) precofinal)/ (float) 100;

	char temp[193], *p;
	strncpy(temp, ARQUIVO + ((*find)*192), 192);
	tam = (*find)*192;
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
	p = strtok(NULL,"@");
	tam+=strlen(p);
	tam+=6;
	ARQUIVO[tam] = alt[0];
	ARQUIVO[tam+1] = alt[1];
	ARQUIVO[tam+2] = alt[2];

	return 1;
}
