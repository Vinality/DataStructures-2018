/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Estruturas de Dados 2
 * Prof. Tiago A. de Almeida
 *
 * Trabalho 03A - Hashing com reespalhamento linear
 *
 * RA: Vinicius Brandao Crepschi
 * Aluno: 743601
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


#define POS_OCUPADA     "[%d] Ocupado: %s\n"
#define POS_LIVRE         "[%d] Livre\n"
#define POS_REMOVIDA     "[%d] Removido\n"

/* Estado das posições da tabela hash */
#define LIVRE       0
#define OCUPADO     1
#define REMOVIDO    2

/* Saídas do usuário */
#define OPCAO_INVALIDA "Opcao invalida!\n"
#define MEMORIA_INSUFICIENTE "Memoria insuficiente!\n"
#define REGISTRO_N_ENCONTRADO "Registro(s) nao encontrado!\n"
#define CAMPO_INVALIDO "Campo invalido! Informe novamente.\n"
#define ERRO_PK_REPETIDA "ERRO: Ja existe um registro com a chave primaria: %s.\n\n"
#define ARQUIVO_VAZIO "Arquivo vazio!"
#define INICIO_BUSCA                              "********************************BUSCAR********************************\n"
#define INICIO_LISTAGEM                          "********************************LISTAR********************************\n"
#define INICIO_ALTERACAO                         "********************************ALTERAR*******************************\n"
#define INICIO_ARQUIVO                        "********************************ARQUIVO*******************************\n"
#define INICIO_EXCLUSAO                          "**********************EXCLUIR*********************\n"

#define SUCESSO                   "OPERACAO REALIZADA COM SUCESSO!\n"
#define FALHA                      "FALHA AO REALIZAR OPERACAO!\n"
#define ERRO_TABELA_CHEIA         "ERRO: Tabela Hash esta cheia!\n\n"
#define REGISTRO_INSERIDO         "Registro %s inserido com sucesso. Numero de colisoes: %d.\n\n"


/* Registro do jogo */
typedef struct {
    char pk[TAM_PRIMARY_KEY];
    char nome[TAM_NOME];
    char marca[TAM_MARCA];
    char data[TAM_DATA];    /* DD/MM/AAAA */
    char ano[TAM_ANO];
    char preco[TAM_PRECO];
    char desconto[TAM_DESCONTO];
    char categoria[TAM_CATEGORIA];
} Produto;

/* Registro da Tabela Hash
 * Contém o estado da posição, a chave primária e o RRN do respectivo registro */
typedef struct {
    int estado;
    char pk[TAM_PRIMARY_KEY];
    int rrn;
} Chave;

/* Estrutura da Tabela Hash */
typedef struct {
    int tam;
    Chave *v;
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
int  alterar(Hashtable tabela);
void buscar(Hashtable tabela);
int  remover(Hashtable* tabela);
void liberar_tabela(Hashtable* tabela);


/* <<< DECLARE AQUI OS PROTOTIPOS >>> */
void gerarChave(Produto *prod); // Gera chave primaria para o produto
Produto recuperar_registro(int rrn); // Recupera o produto a partir do seu rrn
void inserir_produto(Produto *novo); // Le do teclado os dados do produto novo
void salvarProduto(Produto p); // Insere no arquivo de dados o produto novo
int ehPrimo(int n); // Verifica se o inteiro e primo
int prox_primo(int tam); // Determina o proximo primo caso ja nao seja
void criar_tabela(Hashtable *tabela, int tam); // Inicializa a hash table
void imprimir_tabela(Hashtable tabela); // Imprime a tabela hash
int inserir_hash(Hashtable *tabela, int pos, Produto p, int *colisao); // Insere um produto na tabela hash
int validaDesc(char *alt); // Verifica se e valido o campo desconto inserido

/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */
int main()
{
    /* Arquivo */
    int carregarArquivo = 0;
    scanf("%d\n", &carregarArquivo); // 1 (sim) | 0 (nao)
    if (carregarArquivo)
        carregar_arquivo();

    /* Tabela Hash */
    int tam;
    scanf("%d", &tam);
    tam = prox_primo(tam);

    Hashtable tabela;
    criar_tabela(&tabela, tam);
    if (carregarArquivo)
        carregar_tabela(&tabela);

    /* Execução do programa */
    int opcao = 0;
    while(opcao != 6) {
            scanf("%d%*c", &opcao);
            switch(opcao)
            {
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
                    if(remover(&tabela))
                        printf(SUCESSO);
                    else
                        printf(FALHA);
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

// Retorna o produto a partir do rrn
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

// Determina se um inteiro e primo
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

// Pega um inteiro e caso nao seja primo, encontra o proximo primo
int prox_primo(int tam){
    if(ehPrimo(tam))
        return tam;
    while (!ehPrimo(++tam)){}
       return tam;
}

// Inicializa a tabela hash e seus valores
void criar_tabela(Hashtable *tabela, int tam){
    tabela->v = (Chave*)malloc(tam * sizeof(Chave));
    tabela->tam = tam;
    for(int i=0; i<tam; i++){
        tabela->v[i].estado = 0;
        tabela->v[i].rrn = -1;
    }
}

// Funcao para cadastro de produtos
void cadastrar(Hashtable *tabela){
    Produto p;
    int colisao = 0;
    inserir_produto(&p);
    int pos = hash(p.pk, tabela->tam);
    for(int i = pos; i<pos + tabela->tam; i++){
        if(tabela->v[i % tabela->tam].estado != LIVRE){
            if(strcmp(tabela->v[i % tabela->tam].pk, p.pk)==0 && tabela->v[i % tabela->tam].rrn != -1){
                printf(ERRO_PK_REPETIDA, p.pk);
                return;
            }
        }
        else
            break;
    }
    if(inserir_hash(tabela, pos, p, &colisao)){
        salvarProduto(p);
        printf(REGISTRO_INSERIDO, p.pk, colisao);
    }
}

// Insere o produto na tabela hash
int inserir_hash(Hashtable *tabela, int pos, Produto p, int *colisao){
    // Caso o estado nao esteja ocupado, apenas insere
    if(tabela->v[pos].estado != OCUPADO){
        strcpy(tabela->v[pos].pk, p.pk);
        tabela->v[pos].estado = OCUPADO;
        tabela->v[pos].rrn = nregistros;
        nregistros++;
        return 1;
    }
    else{
        // Do contrario procura nas proximas posicoes uma livre
        *colisao = 0;
        for(int i = pos; i < pos + tabela->tam; i++){
            if(tabela->v[i % tabela->tam].estado != OCUPADO){
                strcpy(tabela->v[i % tabela->tam].pk, p.pk);
                tabela->v[i % tabela->tam].estado = OCUPADO;
                tabela->v[i % tabela->tam].rrn = nregistros;
                nregistros++;
                return 1;
            }
            *colisao = *colisao + 1;
        }
    }
    printf(ERRO_TABELA_CHEIA);
    return 0;
}

// Imprime a tabela hash seguindo o modelo
void imprimir_tabela(Hashtable tabela){
    for(int i=0; i < tabela.tam; i++){
        switch (tabela.v[i].estado){
            case LIVRE:
                printf(POS_LIVRE, i);
                break;
            case OCUPADO:
                printf(POS_OCUPADA, i, tabela.v[i].pk);
                break;
            case REMOVIDO:
                printf(POS_REMOVIDA, i);
                break;
        }
    }
}

// Libera a memoria alocada pela tabela
void liberar_tabela(Hashtable* tabela){
    free(tabela->v);
}

// Le cada registro do arquivo e insere na tabela hash
void carregar_tabela(Hashtable *tabela){
    int colisao = 0;
    int nreg = nregistros;
    for(nregistros = 0; nregistros < nreg;){
        Produto temp = recuperar_registro(nregistros);
        colisao = 0;
        inserir_hash(tabela, hash(temp.pk, tabela->tam), temp, &colisao);
    }
}

// Procura pela chave primaria e remove da tabela hash
int remover(Hashtable *tabela){
    char rem[TAM_PRIMARY_KEY];
    int flag = 0;
    int pos;
    scanf("%s", rem);
    rem[TAM_PRIMARY_KEY-1] = '\0';

    for(int i = 0; i<tabela->tam; i++){
        if(strcmp(tabela->v[i].pk, rem)==0 && tabela->v[i].rrn != -1){
            pos = (tabela->v[i].rrn)*192;
            ARQUIVO[pos] = '*';
            ARQUIVO[pos+1] = '|';
            tabela->v[i % tabela->tam].estado = REMOVIDO;
            tabela->v[i % tabela->tam].rrn = -1;
            flag = 1;
        }
    }
    if(flag)
        return 1;
    else
        printf(REGISTRO_N_ENCONTRADO);
    return 0;
}

// Busca pela chave primaria e exibe o registros
void buscar(Hashtable tabela){
    char find[TAM_PRIMARY_KEY];
    scanf("\n%[^\n]s", find);
    find[TAM_PRIMARY_KEY-1] = '\0';
    int pos = hash(find, tabela.tam);
    for(int i = pos; i < pos + tabela.tam; i++){
        if(tabela.v[i % tabela.tam].estado == LIVRE){
            printf(REGISTRO_N_ENCONTRADO);
            return;
        }
        if(strcmp(tabela.v[i % tabela.tam].pk, find)==0 && tabela.v[i % tabela.tam].rrn != -1){
            exibir_registro(tabela.v[i].rrn);
            return;
        }
    }
    printf(REGISTRO_N_ENCONTRADO);
}

// Encontra a chave primaria, acessa pelo rrn e modifica o valor do desconto
int alterar(Hashtable tabela){
    char find[TAM_PRIMARY_KEY];
    char alt[TAM_DESCONTO];
    int i, flag = 0;
    scanf("\n%[^\n]s", find);
    find[TAM_PRIMARY_KEY-1] = '\0';
    int pos = hash(find, tabela.tam);
    for(i = pos; i < pos + tabela.tam; i++){
        if(tabela.v[i % tabela.tam].estado == LIVRE){
            printf(REGISTRO_N_ENCONTRADO);
            return 0;
        }
        if(strcmp(tabela.v[i % tabela.tam].pk, find)==0 && tabela.v[i % tabela.tam].rrn != -1){
            flag = 1;
            break;
        }
    }

    if(flag == 0){
        printf(REGISTRO_N_ENCONTRADO);
        return 0;
    }

    do{
		scanf("\n%[^\n]s", alt);
		if(!validaDesc(alt))
			printf(CAMPO_INVALIDO);
	}while(!validaDesc(alt));

    Produto prod;
    prod = recuperar_registro(tabela.v[i].rrn);
    float precofinal = atof(prod.preco);
    int desc = atoi(alt);
    precofinal = (precofinal *  (100-desc))/100.0;
    precofinal = precofinal*100;
    precofinal = ((int) precofinal)/ (float) 100;

    char temp[193], *p;
    strncpy(temp, ARQUIVO + (tabela.v[i % tabela.tam].rrn*192), 192);
    int tam = (tabela.v[i % tabela.tam].rrn)*192;
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

// Funcao auxiliar para verificar se e valida a entrada no campo desconto
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
