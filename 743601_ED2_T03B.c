/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 03A - Hashing com encadeamento
 *
 * RA: 743601
 * Aluno: Vinicius Brandao Crepschi
 * ========================================================================== */

/* Bibliotecas */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* Tamanho dos campos dos registros */
#define TAM_PRIMARY_KEY 11
#define TAM_NOME 51
#define TAM_MARCA 51
#define TAM_DATA 11
#define TAM_ANO 3
#define TAM_PRECO 8
#define TAM_DESCONTO 4
#define TAM_CATEGORIA 51

#define TAM_REGISTRO 192
#define MAX_REGISTROS 1000
#define TAM_ARQUIVO (MAX_REGISTROS * TAM_REGISTRO + 1)

/* Saídas do usuário */
#define OPCAO_INVALIDA "Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE "Memoria insuficiente!\n"
#define REGISTRO_N_ENCONTRADO "Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO "Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA "ERRO: Ja existe um registro com a chave primaria: %s.\n\n"
#define ARQUIVO_VAZIO "Arquivo vazio!"
#define INICIO_BUSCA 							 "********************************BUSCAR********************************\n"
#define INICIO_LISTAGEM						  "********************************LISTAR********************************\n"
#define INICIO_ALTERACAO 						"********************************ALTERAR*******************************\n"
#define INICIO_ARQUIVO					    "********************************ARQUIVO*******************************\n"
#define INICIO_EXCLUSAO  "**********************EXCLUIR*********************\n"
#define SUCESSO  				 "OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA 					 "FALHA AO REALIZAR OPERACAO!\n"
#define REGISTRO_INSERIDO "Registro %s inserido com sucesso.\n\n"



/* Registro do jogo */
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

/* Registro da Tabela Hash
 * Contém a chave primária, o RRN do registro atual e o ponteiro para o próximo
 * registro. */
typedef struct chave {
	char pk[TAM_PRIMARY_KEY];
	int rrn;
	struct chave *prox;
} Chave;

/* Estrutura da Tabela Hash */
typedef struct {
  int tam;
  Chave **v;
} Hashtable;

/* Variáveis globais */
char ARQUIVO[TAM_ARQUIVO];
int nregistros;

/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

/* Recebe do usuário uma string simulando o arquivo completo. */
void carregar_arquivo();


/* Exibe o jogo */
int exibir_registro(int rrn);

/*Função de Hash*/
short hash(const char* chave, int tam);


/*Auxiliar para a função de hash*/
short f(char x);

/*Retorna o primeiro número primo >= a*/
int  prox_primo(int a);

/*Funções do Menu*/
void carregar_tabela(Hashtable* tabela);
void cadastrar(Hashtable* tabela);
int alterar(Hashtable tabela);
void buscar(Hashtable tabela);
int remover(Hashtable* tabela);
void liberar_tabela(Hashtable* tabela);

/* <<< DECLARE AQUI OS PROTOTIPOS >>> */
void gerarChave(Produto *prod);
Produto recuperar_registro(int rrn);
void inserir_produto(Produto *novo);
void salvarProduto(Produto p);
int ehPrimo(int n);
void imprimir_tabela(Hashtable tabela);
void criar_tabela(Hashtable *tabela, int tam);
void liberar_tabela(Hashtable* tabela);
void inserir_hash(Hashtable *tabela, int pos, Produto p);
int validaDesc(char *alt);

/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */

int main()
{

	/* Arquivo */
	int carregarArquivo = 0;
	scanf("%d%*c", &carregarArquivo); // 1 (sim) | 0 (nao)
	if (carregarArquivo)
		carregar_arquivo();

	/* Tabela Hash */
	int tam;
	scanf("%d%*c", &tam);
	tam = prox_primo(tam);

	Hashtable tabela;
	criar_tabela(&tabela, tam);
	if (carregarArquivo)
		carregar_tabela(&tabela);

	/* Execução do programa */
	int opcao = 0;
	while(opcao != 6) {
		scanf("%d%*c", &opcao);
		switch(opcao) {

		case 1:
			cadastrar(&tabela);
			break;
		case 2:
			printf(INICIO_ALTERACAO);
			if(alterar(tabela))
				printf(SUCESSO);
			else
				printf(FALHA);
			break;
		case 3:
			printf(INICIO_BUSCA);
			buscar(tabela);
			break;
		case 4:
			printf(INICIO_EXCLUSAO);
			printf("%s", (remover(&tabela)) ? SUCESSO : FALHA );
			break;
		case 5:
			printf(INICIO_LISTAGEM);
			imprimir_tabela(tabela);
			break;
		case 6:
			liberar_tabela(&tabela);
			break;

		case 10:
			printf(INICIO_ARQUIVO);
			printf("%s\n", (*ARQUIVO!='\0') ? ARQUIVO : ARQUIVO_VAZIO);
			break;

		default:
			printf(OPCAO_INVALIDA);
			break;
		}
	}
	return 0;
}


/* <<< IMPLEMENTE AQUI AS FUNCOES >>> */

/* Recebe do usuário uma string simulando o arquivo completo. */
void carregar_arquivo() {
	scanf("%[^\n]\n", ARQUIVO);
	nregistros = strlen(ARQUIVO) / TAM_REGISTRO;
}

/*Auxiliar para a função de hash*/
short f(char x)
{
	return (x < 59) ? x - 48 : x - 54;
}

short hash(const char* chave, int tam){
    int soma = 0;
    for(int i = 1; i <= 8; i++){
        soma += i*f(chave[i-1]);
    }
    return soma%tam;
}

/* Exibe o jogo */
int exibir_registro(int rrn)
{
	if(rrn<0)
		return 0;
	float preco;
	int desconto;
	Produto j = recuperar_registro(rrn);
  	char *cat;
	char *categorias = (char*)calloc(TAM_CATEGORIA, sizeof(char));
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
	strncpy(categorias, j.categoria, strlen(j.categoria));
  	for (cat = strtok (categorias, "|"); cat != NULL; cat = strtok (NULL, "|"))
    printf("%s ", cat);
	printf("\n");
	return 1;
}

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

int ehPrimo(int n){
    if (n == 2 || n == 3)
        return 1;

    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= n){
        if (n % (divisor - 1) == 0)
            return 0;

        if (n % (divisor + 1) == 0)
            return 0;

        divisor += 6;
    }
    return 1;
}

int prox_primo(int tam){
    if(ehPrimo(tam))
        return tam;
    while (!ehPrimo(++tam)){}
       return tam;
}

void criar_tabela(Hashtable *tabela, int tam){
    tabela->v = (Chave**) malloc(tam * sizeof(Chave*));
    tabela->tam = tam;
    for(int i=0; i<tam; i++){
		tabela->v[i] = NULL;
    }
}

void cadastrar(Hashtable *tabela){
    Produto p;
    inserir_produto(&p);

	Chave *novo = (Chave *)malloc(sizeof(Chave));
	strcpy(novo->pk, p.pk);
	novo->rrn = nregistros;
	novo->prox = NULL;

    int pos = hash(p.pk, tabela->tam);

	Chave *chaveaux = tabela->v[pos];

	if(tabela->v[pos] != NULL){
		chaveaux = tabela->v[pos];
		while(chaveaux != NULL){
			if(strcmp(chaveaux->pk, p.pk) == 0){
				printf(ERRO_PK_REPETIDA, p.pk);
				return;
			}
			chaveaux = chaveaux->prox;
		}
	}

   if(tabela->v[pos] == NULL || strcmp(tabela->v[pos]->pk, novo->pk) >= 0){
	   novo->prox = tabela->v[pos];
	   tabela->v[pos] = novo;
   }

   else{
		chaveaux = tabela->v[pos];
		while(chaveaux->prox != NULL && strcmp(chaveaux->prox->pk, novo->pk) < 0){
			chaveaux = chaveaux->prox;
		}
		novo->prox = chaveaux->prox;
		chaveaux->prox = novo;
	}

    salvarProduto(p);
	nregistros++;
    printf(REGISTRO_INSERIDO, p.pk);
}

void imprimir_tabela(Hashtable tabela){
	for(int i = 0 ; i < tabela.tam ; i++){
		Chave *aux = tabela.v[i];
		printf("[%d]", i);
		while(aux != NULL){
			printf(" %s", aux->pk);
			aux = aux->prox;
		}
		printf("\n");
	}
}

void liberar_tabela(Hashtable* tabela){
	free(tabela->v);
}

void carregar_tabela(Hashtable *tabela){
    int nreg = nregistros;
    for(nregistros = 0; nregistros < nreg;){
        Produto temp = recuperar_registro(nregistros);
        inserir_hash(tabela, hash(temp.pk, tabela->tam), temp);
    }
}

void inserir_hash(Hashtable *tabela, int pos, Produto p){
	Chave *novo = (Chave *)malloc(sizeof(Chave));
	strcpy(novo->pk, p.pk);
	novo->rrn = nregistros;
	novo->prox = NULL;

	Chave *chaveaux = tabela->v[pos];

	if(tabela->v[pos] != NULL){
		chaveaux = tabela->v[pos];
		while(chaveaux != NULL){
			if(strcmp(chaveaux->pk, p.pk) == 0){
				printf(ERRO_PK_REPETIDA, p.pk);
				return;
			}
			chaveaux = chaveaux->prox;
		}
	}

   if(tabela->v[pos] == NULL || strcmp(tabela->v[pos]->pk, novo->pk) >= 0){
	   novo->prox = tabela->v[pos];
	   tabela->v[pos] = novo;
   }

   else{
		chaveaux = tabela->v[pos];
		while(chaveaux->prox != NULL && strcmp(chaveaux->prox->pk, novo->pk) < 0){
			chaveaux = chaveaux->prox;
		}
		novo->prox = chaveaux->prox;
		chaveaux->prox = novo;
	}
	nregistros++;
}

void buscar(Hashtable tabela){
    char find[TAM_PRIMARY_KEY];
    scanf("\n%[^\n]s", find);
    find[TAM_PRIMARY_KEY-1] = '\0';
    int pos = hash(find, tabela.tam);

	Chave *chaveaux = tabela.v[pos];

	if(chaveaux == NULL){
		printf(REGISTRO_N_ENCONTRADO);
		return;
	}

	else{
		while(chaveaux != NULL){
			if(strcmp(chaveaux->pk, find) == 0){
				exibir_registro(chaveaux->rrn);
				return;
			}
			chaveaux = chaveaux->prox;
		}
	}
    printf(REGISTRO_N_ENCONTRADO);
}

int remover(Hashtable *tabela){
	char rem[TAM_PRIMARY_KEY];
	scanf("\n%[^\n]s", rem);
	rem[TAM_PRIMARY_KEY-1] = '\0';
	int pos = hash(rem, tabela->tam);

	Chave *chaveaux = tabela->v[pos];
	Chave *anterior;

	// Caso a chave removida seja a primeira
	if(chaveaux != NULL && strcmp(chaveaux->pk, rem) == 0){
	        tabela->v[pos] = chaveaux->prox;
	        free(chaveaux);
	        return 1;
	}
	// Procura a chave a ser removida
	while(chaveaux != NULL && strcmp(chaveaux->pk, rem) != 0){
	   anterior = chaveaux;
	   chaveaux = chaveaux->prox;
   	}
	// Caso se atinja o final da lista sem encontrar, retorna 0
	if(chaveaux == NULL){
		printf(REGISTRO_N_ENCONTRADO);
		return 0;
	}
	// Remove o no
	anterior->prox = chaveaux->prox;
	free(chaveaux);

	return 1;
}

int alterar(Hashtable tabela){
    char alt[TAM_PRIMARY_KEY];
    scanf("\n%[^\n]s", alt);
    alt[TAM_PRIMARY_KEY-1] = '\0';
    int pos = hash(alt, tabela.tam);
	int rrn, flag = 0;
	Chave *chaveaux = tabela.v[pos];

	if(chaveaux == NULL){
		printf(REGISTRO_N_ENCONTRADO);
		return 0;
	}

	else{
		while(chaveaux != NULL){
			if(strcmp(chaveaux->pk, alt) == 0){
				rrn = chaveaux->rrn;
				flag = 1;
			}
			chaveaux = chaveaux->prox;
		}
	}
	if(flag == 0){
    	printf(REGISTRO_N_ENCONTRADO);
		return 0;
	}
	else{
		do{
			scanf("\n%[^\n]s", alt);
			if(!validaDesc(alt))
				printf(CAMPO_INVALIDO);
		}while(!validaDesc(alt));

		Produto prod;
		prod = recuperar_registro(rrn);
		float precofinal = atof(prod.preco);
		int desc = atoi(alt);
		precofinal = (precofinal *  (100-desc))/100.0;
		precofinal = precofinal*100;
		precofinal = ((int) precofinal)/ (float) 100;

		char temp[193], *p;
		strncpy(temp, ARQUIVO + (rrn*192), 192);
		int tam = (rrn)*192;
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
}

int validaDesc(char *alt){
    if(strlen(alt) != TAM_DESCONTO-1){
        return 0;
    }
    if(alt[0] < '0' || alt[0] > '9'){
        return 0;
    }
    else if(alt[1] < '0' || alt[1] > '9'){
        return 0;
	}
	else if(alt[2] < '0' || alt[2] > '9'){
        return 0;
    }

    return 1;
}
