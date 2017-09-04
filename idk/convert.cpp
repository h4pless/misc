#include "convert.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int N_BITS = 8;

string toBinary(int n){ // FUNÇAO QUE TRANSFORMA INTEIRO EM BINARIO

    string aux;

    if(n == 0){         // CONTROLE DA QUANTIDADE DE BITS
        do{
            aux = "0" + aux;
        }while(aux.size() < N_BITS);
        return aux;
    }

    string r;
    int x = n;
    int flag = 0;

    if(n < 0){
        flag = -1;
        n *= -1;
    }

    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}      // ALIMENTANDO A STRING R COM 0 OU 1 DE ACORDO COM A RESPOSTA DO IF PARA FORMAR O BINARIO
    if(r.at(0) == '1' ){
        while(r.size() < N_BITS){
        r = "0" + r;
        }
    }
    if(x < 0){
        r = binToComp2(r);          //CASO NUMERO SEJA NEGATIVO, A FUNÇAO BINTOCOMP2 TRANSFORMA EM COMPLEMENTO DE 2
        }


    return r;
}


string binToComp2(string bin){      //FUNÇAO QUE TRANSFORMA UM NUMERO BINARIO EM COMPLEMENTO DE 2

    int i;

    for(i = 0; i <= bin.size()-1 ; i++){     //
        if(bin.at(i) == '0')                 //
            bin.at(i) = '1';                 // Inverte os numeros na string bin
        else                                 //
            bin.at(i) = '0';                 //
    }                                        //

    incBin(&bin, bin.size()-1);        // INCREMENTA 1 UNIDADE NA STRING APOS INVERTER TODOS OS OUTROS CARACTERES

    return bin;

}


void incBin(string *bin, int indice){       //FUNCAO DE INCREMENTO BINARIO QUE AUXILIA NA FUNCAO BINTOCOMP2 E TAMBEM NA DE SOMA
                                            //O PARAMETRO "INT INDICE" ME PERMITE ESCOLHER EM QUAL BIT VAI SER INCREMENTADO
    int j;

    for(int i = indice; i >=0; i--){        // PERCORRE A STRING, AO ACHAR O NUMERO 0 ELE TROCA POR 1 E DEPOIS TRATA DO RESTO DA STRING NO PROXIMO FOR
        if((*bin).at(i) == '0'){
            (*bin).at(i) = '1';
            j = i;
            break;
        }
    }

    j++;

    for(j ; j <= indice; j++){
        (*bin).at(j) = '0';
    }
}


void soma(string *bin, string bin2){        //FUNCAO SOMA UTILIZANDO O METODO INC BIN,
                                            //UM FOR PERCORRE A STRING COM O BINARIO QUE SERA SOMADO, E TODA VEZ QUE ENCONTRA 1, ACIONA O INCBIN COM O INDICE PROPICIO
    int j = 0;

    for(int i = bin2.size()-1; i >= 0; i--){
        if(bin2.at(i) == '1')
            incBin(bin, (*bin).size()-1 -j);
        j++;
    }
}


void subtrai(string *bin, string bin2){     // FUNCAO DE SUBTRAI USANDO O MESMO PRINCIPIO E UTILIZANDO O DECREBIN
                                            // NAO USEI ESSA FUNCAO PRA NADA
    int j = 0;

    for(int i = bin2.size()-1; i >= 0; i--){
        if(bin2.at(i) == '1')
            decreBin(bin, (*bin).size()-1 -j);
        j++;
    }
}


int achaIndice(string bin){                 // não usei essa funcao.

    for(int i = bin.size()-1; i >=0; i--){
        if(bin.at(i) == '1')
            return i;
    }

    return -1;

}


int multiplica(string num1, string num2){       //FUNÇAO QUE UTILIZA O ALGORITIMO DE BOOTH PARA FAZER A MULTIPLICAÇAO

    string q1, a, m, q, aux, resposta;
    int contador, d_a, d_q1, d_m;

    for(int i = 0; i < N_BITS; i++){            //PREENCHO A VARIAVEL A COM O NUMERO CERTO DE BITS, DE ACORDO COM A VARIAVEL
        a.push_back('0');                       //GLOBAL N_BITS
    }

    q1 = "0";
    m = num1;
    q = num2;

    cout << "valores          A              Q                  M" << endl;
    cout << "              "<< a << "       " << q << "           " << m << "\n\n" << endl; // PRINTA OS VALORES PRA CADA INTERAÇAO COM O FOR

    for(int i = 0; i<N_BITS; i++){

        if(q.at(q.size()-1) == q1.at(0)){       //PROCEDIMENTO CASO Q0Q-1 == 11 OU Q0Q-1 == 00
            aux = toString(a, q, q1);           //JUNTO TODOS OS VALORES EM UMA STRING SÓ PARA FAZER
            aux = deslocaDireita(aux);          //O DESLOCAMENTO
            recuperaValores(aux, &a, &q, &q1);  //E DEPOIS RECUPERO OS VALORES
        }
        else{
            if(q.at(q.size()-1) == '1' && q1.at(0) == '0'){  // CASO O Q0Q-1 SEJA = 10

                soma(&a, binToComp2(m));        // A <- A - M

                aux = toString(a, q, q1);       //JUNTA TUDO
                aux = deslocaDireita(aux);      //DESLOCA
                recuperaValores(aux, &a, &q, &q1);  //RECUPERA OS VALORES
            }
            else{
                if(q.at(q.size()-1) == '0' && q1.at(0) == '1'){ // CASO O Q0Q-1 SEJA = 01

                    d_a = toDec(a);
                    d_m = toDec(m);     // A <- A + M
                    d_a = d_a + d_m;
                    a = toBinary(d_a);

                    aux = toString(a, q, q1);   // JUNTA TUDO EM UMA STRING
                    aux = deslocaDireita(aux);  // DESLOCA PRA DIREITA
                    recuperaValores(aux, &a, &q, &q1);  // RECUPERA OS VALORES
                }

            }

        }

        cout << "valores          A              Q                  M" << endl;
        cout << "              "<< a << "       " << q << "           " << m << "\n\n" << endl; // PRINTA OS VALORES PRA CADA INTERAÇAO COM O FOR

    }



    resposta = a+q;             // JUNTA AS STRINGS PARA FORMAR A RESPOSTA
    return toDec(resposta);

}


int divide(string num1, string num2){   //FUNÇAO DE DIVISAO QUE UTILIZA O ALGORITIMO DE BOOTH

    string a, m, q, aux;
    int dec_a, dec_m;                      //DECLARAÇAO DAS VARIAVEIS
    int flag = 0;
    for(int i = 0; i < N_BITS; i++){        //PREENCHIMENTO DE A COM A QUANTIDADE DE BITS
        a.push_back('0');
    }

    if(num1.at(0) == '1'){                  //VERIFICA SE NUM1 É UM NUMERO NEGATIVO PARA ATIVAR A FLAG E
        num1 = binToComp2(num1);            //PARA FAZER O COMPLEMENTO DE 2 DE NUM1 PARA FACILITAR
        flag = -1;
    }
    if(num2.at(0) == '1'){                  //VERIFICA SE NUM2 É NUMERO NEGATIVO PARA ATUALIZAR A FLAG
        num2 = binToComp2(num2);
        if(flag == -1)
            flag = 0;
        else
            flag = -1;
    }
    q = num1;
    m = num2;

    for(int i = 0; i < N_BITS; i++){        //GARANTINDO QUE O NUMERO DE INTERAÇOES SERA O MESMO NUMERO DA QUANTIDADE DE BITS

        cout << "valores          A              Q                  M" << endl;
        cout << "              "<< a << "       " << q << "           " << m << "\n\n" << endl;

        aux = toString(a, q);               // JUNTANDO TUDO EM UMA STRING PARA DESLOCAR PARA A ESQUERDA E DEPOIS
        aux = deslocaEsquerda(aux);
        recuperaValores(aux, &a, &q);       //RECUPERAR OS VALORES

        dec_a = toDec(a);
        dec_m = toDec(binToComp2(m));       // A <- A+M
        dec_a = dec_a + dec_m;
        a = toBinary(dec_a);

        if(a.at(0) == '1'  ){               // SE A < 0

            q.at(q.size()-1) = '0';         // Q0 <- 0
            dec_a = dec_a + toDec(m);       //ATUALIZA A
            a = toBinary(dec_a);

        }
        else{                               // SE A >= 0
                q.at(q.size()-1) = '1';     // Q0 <- 1
        }

    }
        cout << "valores          A              Q                  M" << endl;
        cout << "              "<< a << "       " << q << "           " << m << "\n\n" << endl;

    if(flag == 0)                           // VERIFICAÇAO DA FLAG ANTES DO RETURN
        return toDec(q);
    else
        return toDec(binToComp2(q));
}


void recuperaValores(string s0, string *s1, string *s2, string *s3){        // FUNÇAO AUXILIAR PARA RECUPERAR OS VALORES APOS
                                                                            // A DESLOCAÇAO
    *s1 = s0.substr(0,N_BITS);
    *s2 = s0.substr(N_BITS,N_BITS);
    *s3 = s0.at(2*N_BITS);
}


void recuperaValores(string s0, string *s1, string *s2){                    // FUNCAO AUXILIAR PARA RECUPERAR OS VALORES APOS
    *s1 = s0.substr(0, N_BITS);                                             // A DESLOCAÇAO
    *s2 = s0.substr(N_BITS, N_BITS);
}


string toString(string s1, string s2){           // FUNCAO AUXILIAR PARA JUNTAR VARIAS STRINGS EM 1 SÓ
    return s1+s2;
}


string toString(string s1, string s2, string s3){       //FUNCAO AUXILIAR PARA JUNTAR VARIAS STRINGS EM 1 SÓ
    return s1+s2+s3;
}


int toDec(string bin){          // FUNÇAO DE CONVERSÃO DE BINARIO PARA DECIMAL,

    int aux = 0;
    int aux2 = bin.size()-1;

    int flag = 0;

    if(bin.at(0) == '1'){         //CASO SEJA NEGATIVO O NUMERO, ATUALIZA A FLAG E FAZ O COMPLEMENTO DE 2
        bin = binToComp2(bin);
        flag = -1;
    }

    for(int i = 0; i < bin.size(); i++){      // AUX VAI ACUMULANDO O VALOR PRA CADA INTERAÇAO DO FOR PRA DAR O VALOR EM DECIMAL
        if(bin.at(aux2) == '1')
            aux += pow(2, i);
        aux2--;
    }
    if(flag == -1){             // VERIFICAÇAO DA FLAG PRA ATUALIZAÇAO DO NUMERO EM DECIMAL
        aux *= -1;
    }
    return aux;

}


string deslocaDireita(string s1){       // FUNÇAO DE DESLOCAÇAO BINARIA A DIREITA

    string aux;
    for(int i = 0; i<= s1.size()-1; i++)     //CRIAÇAO DE UMA STRING AUXILIAR E PREENCHIMENTO DA MESMA COM A QUANTIDADE DE BITS
        aux.push_back('0');                  // USADA

    for(int j = 1; j<= s1.size()-1; j++)     //DESLOCAÇAO
        aux.at(j) = s1.at(j-1);
    if(s1.at(0) == '0')
        aux.at(0) = '0';
    else
        aux.at(0) = '1';

    return aux;
}


string deslocaEsquerda(string s1){      // FUNCAO DE DESLOCAÇAO BINARIA A ESQUERDA

    string aux;              //STRING AUX CRIADA PRA AUXILIAR
    for(int i = 0; i<= s1.size()-1; i++)       //PREENCHIMENTO DA STRING AUX COM O VALOR DE BITS USADOS
        aux.push_back('0');
    for(int j = 0; j < s1.size()-1; j++){       //DESLOCAÇAO
        aux.at(j) = s1.at(j+1);
    }

    return aux;
}


void decreBin(string *bin, int indice){     // FUNÇAO DE DECREMENTO BINARIO SIMPLES, NÃO USEI PRA NADA

    int j;

    for(int i = indice; i >=0; i--){
        if((*bin).at(i) == '1'){
            (*bin).at(i) = '0';
            j = i;
            break;
        }
    }

    j++;

    for(j ; j <= indice; j++){
        (*bin).at(j) = '1';
    }
}
