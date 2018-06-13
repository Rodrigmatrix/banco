#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "structs.h"
#include "funcoes.h"
#include <unistd.h> 
void login(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int opcao,count,n=0,aux=0,s=1;
    char usuario[20],senha[15];
    //inicio do sistema
    limpar();
    printf("Bem Vindo ao sistema de gerenciamento do Banco FUP.\n");
    printf("Digite o usuário: ");
    scanf("%s",usuario);
    getchar();
        for(count=0;count<*f;count++){
            if(strcmp(usuario,funcionarios[count].usuario)==0){
                //posicao do funcionario no vetor
                n=count;
                //certeza de que encontrou um funcionario
                aux=1;
            }
        }
        if(strcmp(usuario,"root")==0){//acesso root
            aux=2;//diferenciando root de usuario comum
        }
        if(aux==0){
            printf("Usuário não encontrado");
            continuar();
            return;
        }
    //verificar senha do usuario
    printf("Digite a senha:");
    scanf("%s",senha);
    getchar();
    //verificar se a senha está correta
        if(strcmp(senha,funcionarios[n].senha)==0 || aux==2 && strcmp(senha,"root")==0){
            while(opcao!=5){
            limpar();
            if(aux==2){//verificando se quem esta logado é o root
                printf("Bem vindo root\n");
            }
            else{
                printf("Bem vindo %s\n",funcionarios[n].nome);
            }
            
            printf("Digite a opção desejada:\n");
            printf(" 1-Cadastro de Cliente\n 2-Cadastro de Funcionário\n");
            printf(" 3-Pesquisa de Cliente ou Funcionário no sistema\n 4-Remover cadastro ou desbloquear conta\n 5-Sair\n");
            scanf("%d",&opcao);
            //Opções para alternar entre as funções 
                switch (opcao){
                    case 1:
                    limpar();
                    cadastro(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 2:
                    limpar();
                    cadastrofuncionario(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 3:
                    limpar();
                    info(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 4:
                    limpar();
                    atualizar(clientes,funcionarios,loginC,i,f,nconta);
                    break;

                    case 5:
                    limpar();
                    printf("Sistema encerrado.\n");
                    return;
                    break;
                    
                    default:
                    limpar();
                    printf("Opção Inválida\n");
                    sleep(3);
                    return;
                    break;
                }
            }
        }
        else{
            limpar();
            printf("Senha Incorreta\n");
            sleep(4);
            return;
        }
}
void cadastro(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    //função de cadastro de cliente
    int numero,agenciac,count,aux=0;
        limpar();
        printf("%i\n",*i); // Int i, incrementar
        printf("%d\n",*nconta); // numero da conta, era pra incrementar
        printf("Digite o primeiro nome do cliente:\n");
        scanf("%s",clientes[*i].nome);
        getchar();
        printf("Digite o sobrenome do cliente:\n");
        scanf("%s",clientes[*i].sobrenome);
        getchar();
        printf("Endereço:\n");
        scanf("%s",clientes[*i].rua);
        getchar();
        printf("Número da Casa/Apt:\n");
        scanf("%s",clientes[*i].num);
        getchar();
        printf("CEP sem pontos e traços:\n");
        scanf("%s",clientes[*i].cep); //nao esta salvando
        getchar();
        printf("Digite o número de telefone no formato (00)00000-0000\n");
        scanf("%s",clientes[*i].numero);
        getchar();
        printf("Digite o CPF do cliente:\n"); 
        scanf("%s",clientes[*i].cpf);
        getchar();
        printf("Digite a data de nascimento no formato 00/00/0000: \n");
        scanf("%s",clientes[*i].data);
        getchar();
        printf("Digite a senha para a conta do cliente:");
        scanf("%s",clientes[*i].senha);
        getchar();
        printf("Digite a Agência:");
        scanf("%d",&agenciac);
        clientes[*i].errosenha=3;
        clientes[*i].saldocorrente=0;
        clientes[*i].numerocliente=*i;
        clientes[*i].agencia=agenciac;
        clientes[*i].conta=*nconta;
        clientes[*i].ativo=1;
        limpar();
        printf("Cadastro Realizado com sucesso\n");
        printf("Numero do Cliente:%d\n",clientes[*i].numerocliente);
        printf("Numero da Agencia:%d\n",agenciac);
        printf("Numero da conta:%d\n",*nconta);
        printf("Senha:%s\n",clientes[*i].senha);
        *nconta+=1;
        *i+=1;
        continuar();
}

void cadastrofuncionario(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
        //função para cadastrar funcionário
        int numero,aux=1,count;
        char usuariod[20];
        limpar();
        printf("Digite o nome completo do Funcionário:\n");
        scanf("%s",funcionarios[*f].nome);
        getchar();
        printf("Digite o sobrenome:\n");
        scanf("%s",funcionarios[*f].sobrenome);
        printf("Endereço:\n");
        scanf("%s",funcionarios[*f].rua);
        getchar();
        printf("Número da Casa/Apt:\n");
        scanf("%s",funcionarios[*f].num);
        getchar();
        printf("Digite o número de telefone no formato (00)00000-0000\n");
        scanf("%s",funcionarios[*f].numero);
        getchar();
        printf("CEP sem pontos e traços:\n");
        scanf("%s",funcionarios[*f].cep);
        getchar();
        printf("Digite o CPF do funcionário:\n");
        scanf("%s",funcionarios[*f].cpf);
        getchar();
        printf("Digite a data de nascimento no formato 00/00/0000: \n");
        scanf("%s",funcionarios[*f].data);
        getchar();
        printf("Digite o cargo do funcionário:\n");
        scanf("%s",funcionarios[*f].cargo);
        getchar();
        printf("Digite o usuário para login no sistema\n");
        scanf("%s",usuariod);
        getchar();
            for(count=0;count<*f;count++){ // Verifica se existe usuario repetido
				if(strcmp(usuariod,funcionarios[count].usuario)==0){
					printf("Usuário já existe\n");
                    exit(1);				
                }
			}
        strcpy(funcionarios[*f].usuario,usuariod);
        printf("Digite a senha:\n");
        scanf("%s",funcionarios[*f].senha);
        getchar();
        funcionarios[*f].numfun=*f;
        printf("Cadastro realizado com sucesso. Número do gerente: %d\n",funcionarios[*f].numfun);
        *f+=1;
        continuar();
}
void info(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    //função para pesquisar cliente ou funcionário no banco de dados
    int n,cliented,funcionario,count,aux=0,numero=0,op,qtd=0,s=1;
    char nome[20];
    printf("Digite 1 para cliente ou 2 para funcionário: ");
    scanf("%d",&n);
    switch(n){
        case 1:
        limpar();
        printf("1-Pesquisa por nome\n2-Pesquisar por número.\n");
        scanf("%d",&op);
        switch(op){
            case 1:
            limpar();
            printf("Digite o nome do cliente:");
            scanf("%s",nome);
            getchar();
            printf("Resultado da busca:\n");
                for(count=0;count<*i;count++){
                    s=strcmp(nome,clientes[count].nome);
                    if(s==0){
                        qtd++;
                        printf("%d-%s %s\n",qtd,clientes[count].nome,clientes[count].sobrenome);
                        printf("  Rua:%s Cep:%s Telefone:%s\n",clientes[count].rua,clientes[count].cep,clientes[count].numero);
                        printf("  Cpf:%s Data de Nascimento:%s",clientes[count].cpf,clientes[count].data);
                        printf("  Saldo Conta:%.2f Agência:%d Conta:%d\n\n",clientes[count].saldocorrente,clientes[count].agencia,clientes[count].conta);
                    }
                }
                if(qtd==0){
                    printf("Nenhum cliente com o nome %s encontrado.\n",nome);
                }
                continuar();
            break;

            case 2:
            limpar();
            printf("Digite o número do cliente: ");
            scanf("%d",&cliented);
            printf("Resultado da busca:\n");
            for(count=0;count<*i;count++){
                if(cliented==clientes[count].numerocliente){
                    numero=count;
                    aux=1;
                }
            }
            if(aux==0){
                printf("Cliente não encontrado.\n");
                continuar();
                return;
            }
            else{
                printf("%s %s\n",clientes[numero].nome,clientes[numero].sobrenome);
                printf("Rua:%s Cep:%s Telefone:%s\n",clientes[numero].rua,clientes[aux].cep,clientes[numero].numero);
                printf("Cpf:%s Data de Nascimento:%s",clientes[numero].cpf,clientes[numero].data);
                printf("Saldo Conta:%.2f Agência:%d Conta:%d\n\n",clientes[numero].saldocorrente,clientes[numero].agencia,clientes[numero].conta);
                continuar();
                return;
            }
            break;

            default:
            printf("Opção Inválida.\n");
            continuar();
            return;
        }
        break;
        
        case 2:
        limpar();
        printf("1-Pesquisa por nome\n2-Pesquisar por número.\n");
        scanf("%d",&op);
        switch(op){
            case 1:
            limpar();
            printf("Digite o nome do Funcionário:");
            scanf("%s",nome);
            getchar();
            printf("Resultado da busca:\n");
                for(count=0;count<*f;count++){
                    s=strcmp(nome,funcionarios[count].nome);
                    if(s==0){
                        qtd++;
                        printf("%d-%s %s\n",qtd,funcionarios[count].nome,funcionarios[count].sobrenome);
                        printf("  Rua:%s Cep:%s Telefone:%s\n",funcionarios[count].rua,funcionarios[count].cep,funcionarios[count].numero);
                        printf("  Cpf:%s Data de Nascimento:%s Número do Funcionário:%d\n",funcionarios[count].cpf,funcionarios[count].data,funcionarios[count].numfun);
                    }
                }
                if(qtd==0){
                    printf("Nenhum cliente com o nome %s encontrado.\n",nome);   
                }
            continuar();
            break;

            case 2:
            limpar();
            printf("Digite o número do funcionário: ");
            scanf("%d",&funcionario);
            printf("Resultado da busca:\n");
                for(count=0;count<*f;count++){
                    if(funcionario==funcionarios[count].numfun){
                    aux=1;
                    numero=count;
                    }
                }
                if(aux==0){
                    printf("Funcionário não encontrado.\n");
                    continuar();
                }
                else{
                    printf("Resultado da busca:\\n");
                    printf("%s %s\n",funcionarios[numero].nome,funcionarios[numero].sobrenome);
                    printf("Rua:%s Cep:%s Telefone:%s\n",funcionarios[numero].rua,funcionarios[numero].cep,funcionarios[numero].numero);
                    printf("Cpf:%s Data de Nascimento:%s Número do Funcionário:%d\n",funcionarios[numero].cpf,funcionarios[numero].data,funcionarios[numero].numfun);
                }
            continuar();
            break;
        }

        default:
        printf("Opção Inválida.\n");
        continuar();
        break;
    }
}
void atualizar(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int op,desbloqueio,remover;
    printf("1-Remover Cadastro de Cliente\n2-Remover Cadastro de Funcionário\n3-Desbloqueio de conta de cliente\n");
    scanf("%d",&op);
    switch(op){
        case 1:
        remover=infocliente(clientes,funcionarios,loginC,i,f,nconta);
        clientes[remover].agencia=-1;
        clientes[remover].conta=-1;
        clientes[remover].numerocliente=-1;
        printf("Cadastro removido com sucesso.\n");
        break;

        case 2:
        remover=infofuncionario(clientes,funcionarios,loginC,i,f,nconta);
        funcionarios[remover].numfun=-1;
        strcpy(funcionarios[remover].usuario,"0");
        printf("Cadastro removido com sucesso.\n");
        break;

        case 3:
        desbloqueio=infocliente(clientes,funcionarios,loginC,i,f,nconta);
            clientes[desbloqueio].errosenha=3;
            printf("Conta desbloqueada com sucesso.\n");
            continuar();
        break;

        default:
        printf("Opção Inválida.\n");
        continuar();
        break;
    }
    limpar();
}
int infocliente(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int codigo,aux=0,count,n=0,ag,ct;
    limpar();
    //numero da conta de agencia
    printf("Digite a agência:\n");
    scanf("%d",&ag);
    printf("Digite a conta:\n");
    scanf("%d",&ct);
    for(count=0;count<*i;count++){
        if(clientes[count].agencia==ag && clientes[count].conta==ct){
            n=count;
            aux=1;
        }
    }
    if(aux==0){
        printf("Cliente não encontrado.\n");
        continuar();
    }
    else{
        return n;
    }
}
int infofuncionario(cliente *clientes,funcionario *funcionarios,int *loginC,int *i, int *f, int *nconta){
    int codigo,aux=0,count,n=0;
    limpar();
    printf("Digite o código do funcionário:\n");
    scanf("%d",&codigo);
    for(count=0;count<*f;count++){
        if(funcionarios[count].numfun==codigo){
            n=count;
            aux=1;
        }
    }
    if(aux==0){
        printf("Funcionário não encontrado.\n");
        continuar();
    }
    else{
        return n;
    }
}