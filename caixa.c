#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"
#include <unistd.h>
void caixa(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    //FUNÇÃO CAIXA ELETRÔNICO
    char senhad[7],aux=0,count;
    int opcao,numcliente=0,agencia,conta,s=0;
    setlocale(LC_ALL, "Portuguese");
    limpar();
    printf("\nBem vindo ao Banco FUP \n");
    printf("Digite a agência: \n");
    scanf("%d",&agencia);
    printf("Digite a conta: \n");
    scanf("%d",&conta);
        for(count=0;count<*i;count++){
            if( (agencia==clientes[count].agencia) && (conta==clientes[count].conta)){
                numcliente=count;
                aux=1;
                break;
            }
        }
        if(aux==0 || clientes[numcliente].ativo==0){
            printf("Agência ou Conta não encontrados\n");
            sleep(4);
            //tentar novamente
            return;
        }
        //procurar por dados em agencia e conta
        printf("Digite a senha: \n");
        //verificar senha correta
        scanf("%s",senhad);
        getchar();
        s=strcmp(senhad,clientes[numcliente].senha);
        if(clientes[numcliente].errosenha==0){
            printf("Sua conta está bloqueada. Entre em contato com o seu gerente\n");
            sleep(4);
            return;  
        }
        if( (s==0) && (clientes[numcliente].errosenha!=0) ){
            *loginC=numcliente;
            clientes[numcliente].errosenha=3;
            while(opcao!=6){
            limpar();
            printf("\nBem Vindo %s\n",clientes[numcliente].nome);
            printf("Digite a operação desejada:\n");
            printf(" 1-Transferência\n 2-Depósito\n 3-Pagamento de conta\n 4-Saldo da conta\n 5-Saque\n 6-Sair\n");
                scanf("%d",&opcao);
                switch (opcao){
                    case 1:
                    limpar();
                    transferencia(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 2:
                    limpar();
                    deposito(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 3:
                    limpar();
                    pagamento(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 4:
                    limpar();
                    saldo(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 5:
                    limpar();
                    saque(clientes,funcionarios,loginC,i,f,nconta);
                    break;
                    case 6:
                    return;
                    break;

                    default:
                    limpar();
                    printf("Opção Inválida");
                    return;
                    break;
                }
            }
        }
        else{
            //salvar no banco de dados do cliente o erro
            clientes[numcliente].errosenha--;
            limpar();
            printf(" Senha Incorreta.\n Número de tentativas restantes: %d\n",clientes[numcliente].errosenha);
            continuar();
            return;
        }    
}
void transferencia(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int lg=*loginC;
    limpar();
    int contatrans;
    float valor;
    printf("Digite as unformações da conta em que o dinheiro será transferido:\n");
    contatrans=infocliente(clientes,funcionarios,loginC,i,f,nconta);
    printf("Digite o valor da transferência:");
    scanf("%f",&valor);
    if(valor>clientes[lg].saldocorrente){
        printf("Saldo Indisponível.\nOperação Cancelada.\n");
        continuar();
    }
    else{
        clientes[lg].saldocorrente-=valor;
        clientes[contatrans].saldocorrente+=valor;
        printf("Tranferência Realizada com sucesso. Novo Saldo da sua conta:%.2f",clientes[lg].saldocorrente);
        continuar();
    }
}
void deposito(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    float deposito,d;
    int lg=*loginC;
    printf("Digite o valor do depósito:");
    scanf("%f",&deposito);
    printf("\nInsira o envelope na máquina e digite 1:");
    scanf("%d",&d);
    clientes[lg].saldocorrente+=deposito;
    printf("Depósito realizado com sucesso. Novo saldo da conta:%.2f",clientes[lg].saldocorrente);
    continuar();
}
void pagamento(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int lg=*loginC;
    float valor;
    limpar();
    printf("Digite o valor do boleto:\n");
    scanf("%f",&valor);
    if(valor<=clientes[lg].saldocorrente){
        clientes[lg].saldocorrente-=valor;
        limpar();
        printf("Pagamento realizado com sucesso.\nNovo Saldo da conta:%.2f\n",clientes[lg].saldocorrente);
        continuar();
    }
    else{
        limpar();
        printf("Saldo Insuficiente.\n Operação Cancelada\n");
        continuar();
    }
}
void saque(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    float saque;
    int lg=*loginC;
    limpar();
    printf("Digite o valor do saque:\n");
    scanf("%f",&saque);
    if(saque>clientes[lg].saldocorrente){
        limpar();
        printf("Saldo Insuficiente.\n Operação Cancelada\n");
        sleep(4);
    }
    else{
        clientes[lg].saldocorrente-=saque;
        limpar();
        printf("Operação realizada com sucesso.\n Retire o dinheiro.\n");
        printf("Novo Saldo da conta:%.2f\n",clientes[lg].saldocorrente);
        continuar();
    }
}
void saldo(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    //exibir saldo de acordo com o cliente
    int lg=*loginC;
    limpar();
    printf("Saldo disponível na conta corrente:%.2f\n",clientes[lg].saldocorrente);
    continuar();
}
