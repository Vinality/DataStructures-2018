import math

hashlist = []
tam = input("Tamanho da hash: ")
num_items = input("Numero de elementos: ")
for i in range(num_items):
    hashlist.insert(i, input(str(i) + ": "))

def hash_div_lin(item_list, table_size):
    hash_table = dict([(i, None) for i,x in enumerate(range(table_size))])
    for item in item_list:
        i = item % table_size
        # print("A posicao de " + str(item) + " na hash e " + str(i))
        if hash_table[i] != None:
            print("Houve colisao e Reespalhamento linear do %d\n" % item)
            x = i+1
            for x in range(0, table_size):
                pos = (item + x) % hash_table
                if hash_table[pos] == None:
                    hash_table[pos] = item
                    break

            if x == table_size:
                print("Hash table cheia!\n")
        else:
            hash_table[i] = item

    return hash_table

def hash_div_quad(item_list, table_size):
    hash_table = dict([(i, None) for i,x in enumerate(range(table_size))])
    for item in item_list:
        i = item % table_size
        # i = math.floor(table_size * ((item * 0.618 ) % 1)) for different hash function
        if hash_table[i] != None:
            print("Houve colisao e Reespalhamento quadratico do %d\n" % item)
            for x in range(0, table_size):
                pos = (item  + x*x) % table_size
                if hash_table[pos] == None:
                    hash_table[pos] = item
                    break
        else:
            hash_table[i] = item

    return hash_table


tipo = input("1- Metodo da divisao com Reespalhamento Linear\n2- Metodo da divisao com Reespalhamento Quadratico\n")

if tipo == 1:
    hash_table = hash_div_lin(hashlist, tam)
else:
    hash_table = hash_div_quad(hashlist, tam)

print(hash_table)
