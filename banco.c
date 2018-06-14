#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"
#include <unistd.h> 
void main(){
    cliente *clientes=(cliente*)malloc(100*sizeof(cliente)); // alocando 100 espaços de vetor
    funcionario *funcionarios=(funcionario*)malloc(100*sizeof(funcionario)); // alocando 100 espaços de vetor
    int i=0,f=0,nconta=0,lg=0;
    /* i armazena a posição do cadastro do cliente no vetor
    f armazena a posição do cadastro do funcionario no vetor
    nconta numero do cadastro do cliente
    lg armazena qual o cliente está logado em sua conta */
    int *loginC=&lg,*cadastroF=&f,*numeroconta=&nconta; //ponteiros para controle de cadastro e login ativo no sistema
    setlocale(LC_ALL, "Portuguese");
    menu(clientes,funcionarios,loginC,&i,&f,&nconta);
}