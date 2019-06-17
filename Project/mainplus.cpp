//Vinicius Brandao Crepschi   RA: 743601
#include "avltree.h"
#include <iostream>
#include <string>

int main(){
    AvlTree t;
    string buffer;
    ifstream arquivo("dict3.txt");

    // if(arquivo){
    //     while(getline(arquivo, buffer)){
    //         t.inserir(buffer);
    //     }
    // }

    for(int i = 0; i < 3; i++){
        string a;
        cin >> a;
        Palavra b(a);
        t.inserir(b);
    }
    // string plv1 = "the";
    // string plv2 = "of";   //Testando insercao manual
    // // scanf("%s", plv2); //ad
    // string plv3 = "to";
    // // scanf("%s", plv3); //eb
    // string plv4 = "and";
    // string plv5 = "a";
    // // string plv6 = "hêin";
    // // string plv7 = "são";
    // //
    // t.inserir(plv1);
    // t.inserir(plv2);
    // t.inserir(plv3);
    // t.inserir(plv4);
    // t.inserir(plv5);
    // t.inserir(plv6);
    // t.inserir(plv7);
    string aba = "a";
    Palavra find(aba);
    t.mostrar();
    if(t.busca(find)){
        cout << "ACHOU" << endl;
    }

    return 0;
}
