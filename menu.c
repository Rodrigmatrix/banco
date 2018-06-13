#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"
#include <unistd.h>
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