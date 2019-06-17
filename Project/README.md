# trabintegrado-ed1poo
repositório do trabalho integrado de estrutura de dados 1 e programação orientada a objeto

O trabalho é sobre um corretor que dentro possui um dicionario, segue a descriçao do trabalho realizado por Pedro Coelho, Vinícius Crepschi, Natham Coracini e João Victor Montefusco:

A sua equipe foi contratada para desenvolver um corretor ortográfico. O corretor
deverá permitir a verificação de erros num texto comparando as palavras no arquivo de texto com as palavras num dicionário. Palavras que não fazem parte do dicionário são potenciais erros de escrita. Assim, caso o corretor encontre uma palavra que não faça parte do dicionário, ele deverá permitir ao usuário: corrigir a palavra, ignorar o erro, selecionar uma palavra a partir de uma lista de palavras semelhantes ou adicionar a palavra no dicionário. Ao apresentar um erro para ser corrigido, o corretor deverá apresentar também ao usuário, o contexto em que o erro ocorreu (a palavra anterior e a palavra seguinte ao erro). O corretor deverá também manter uma lista dos erros encontrados no texto (corrigidos ou não). Essa lista deverá conter apenas uma entrada para cada palavra errada e deverá manter o número de vezes que o mesmo erro ocorreu no texto. O Corretor deverá ser uma classe que contenha um dicionário, um texto e a lista das palavras erradas.

A classe Texto deverá conter uma lista de palavras, o nome do arquivo original do
texto e permitir carregar um texto a partir de um arquivo, percorrer o texto, palavra por
palavra, alterar uma palavra e gravar o texto em um arquivo (não necessariamente o
original).

A classe Dicionário deverá armazenar as palavras obtidas do arquivo "dict.txt" e
deverá permitir consulta e inclusão de palavras e fornecer uma lista de palavras semelhantes à uma determinada palavra (considerar palavras semelhantes aquelas que começam com as mesmas 2 letras). O relacionamento entre as classes Dicionário e Palavra deverá ser implementado por meio de uma árvore balanceada. Você poderá escolher entre AVL e vermelho-preta.

A classe Palavra deverá conter ao menos a palavra, um método que verifique se duas
palavras são semelhantes e ter o operador == sobrecarregado para verificar se duas
palavras são idênticas.

O sistema deverá conter pelo menos as classes Corretor, Dicionário, Texto, Palavra e
Arvore. A classe corretor deverá conter métodos para a interação com o usuário e também para manipular as classes dicionário e texto.

A classe Arvore deve ter na interface apenas os métodos: vazia, insere, remove e
Busca.


