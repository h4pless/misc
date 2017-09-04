#include <iostream>
#include <stdlib.h>
#include "convert.h"

using namespace std;


int main(void){


    int d1, d2, m1, m2;

    cout << "Insira o Dividendo:\n" << endl;
    cin >> d1;
    cout << "Insira o Divisor:\n" << endl;
    cin >> d2;


    cout << "\n\n###Resultado: " << divide(toBinary(d1), toBinary(d2)) << "\n\n" << endl;

    cout << "Insira o Multiplicador:\n" << endl;
    cin >> m1;
    cout << "Insira o Multiplicando:\n" << endl;
    cin >> m2;

    cout << "\n\n###Resultado: " << multiplica(toBinary(m1), toBinary(m2)) << "\n\n" << endl;

    return 0;
}
