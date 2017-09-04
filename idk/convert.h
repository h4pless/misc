#include <string>
#ifndef _CONVERT_H_
#define _CONVERT_H_

using namespace std;

string toBinary(int n);
string binToComp2(string bin);
string toString(string s1, string s2, string s3);
string deslocaDireita(string s1);
string deslocaEsquerda(string s1);
string toString(string s1, string s2);

int toDec(string bin);
int achaIndice(string bin);
int multiplica(string num1, string num2);
int divide(string num1, string num2);

void toComp2(string bin);
void incBin(string *bin, int indice);
void soma(string *bin, string bin2);
void recuperaValores(string s0, string *s1, string *s2, string *s3);
void recuperaValores(string s0, string *s1, string *s2);
void decreBin(string *bin, int indice);
void subtrai(string *bin, string bin2);




#endif
