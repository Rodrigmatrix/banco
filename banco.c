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
    int *loginC=&lg,*cadastroF=&f,*numeroconta=&nconta; //ponteiros para controle de cadastro e login ativo no sistema
    setlocale(LC_ALL, "Portuguese");
    menu(clientes,funcionarios,loginC,&i,&f,&nconta);
}
void menu(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int modo;
    while(1){
    limpar();
    printf("Bem Vindo ao Banco FUP.\n");
    printf("Digite o Modo de operação:\n 1-Administrador\n 2-Caixa Eletrônico\n 3-Sair\n");
    scanf("%d",&modo);
        switch(modo){
            case 1:
            limpar();
            login(clientes,funcionarios,loginC,i,f,nconta);
            break;
           
            case 2:
            limpar();
            caixa(clientes,funcionarios,loginC,i,f,nconta);
            break;

            case 3:
            limpar();
            printf("Sistema Encerrado.\n");
            return;
            break;

            default:
            limpar();
            printf("Opção Inválida.\n");
            break;
        }
    }
}
void limpar(){
    system("clear");
    printf("----------------------------------------------------\n");
    printf("----------------------Banco FUP---------------------\n");
    printf("----------------------------------------------------\n");
}
void continuar(){
    char sair;
    printf("\nContinuar:(S/N)");
    scanf(" %c",&sair);
}
