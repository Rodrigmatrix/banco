#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "structs.h"
#include <time.h>
int login(funcionario funcionarios[100],cliente clientes[100]);
int cadastro();
int cadastrofuncionario();
int infofuncionario();
int infocliente();
int info();
int atualizar();
char verificarcpf();
int transferencia();
int caixa(cliente clientes[100]);
int deposito();
int pagamento();
int saldo();
int saque();
void limpar();
/* open – opens a text file.
fclose – closes a text file.
feof – detects end-of-file marker in a file.
fscanf – reads formatted input from a file.
fprintf – prints formatted output to a file.
fgets – reads a string from a file.
fputs – prints a string to a file.
fgetc – reads a character from a file.
fputc – prints a character to a file. */

int main(){
    int posicaocadastrocliente=0,posicaocadastrofuncionario=0,agencia=0,conta=0;
    cliente clientes[100];
    funcionario funcionarios[100];
    //Ponteiro para acessar txt
FILE *file;
file=fopen("banco.txt", "r+");
    if (file==NULL){
        printf("Não foi possível abrir o banco de dados. O sistema será encerrado");
        return 0;
    }
setlocale(LC_ALL, "Portuguese");
    int modo;
    clientes[0].agencia=0;
    clientes[0].conta=0;
    clientes[0].errosenha=3;
    limpar();
    printf("Bem Vindo ao Banco FUP.\n");
    printf("Digite o Modo de operação:\n 1-Administrador\n 2-Caixa Eletrônico\n 3-Sair\n");
    scanf("%d",&modo);
        switch(modo){
            case 1:
            limpar();
            login(funcionarios,clientes);
            break;
           
            case 2:
            limpar();
            caixa(clientes);
            break;

            case 3:
            return 0;
            break;

            default:
            limpar();
            printf("Opção Inválida.");
            return 0;
            break;
        }
   fclose(file);
}
int login(funcionario funcionarios[100],cliente clientes[100]){
    int opcao,count,n=0,aux=0;
    char usuario[20],senha[15];
    setlocale(LC_ALL, "Portuguese");
    //inicio do sistema
    limpar();
    printf("Bem Vindo ao sistema de gerenciamento do Banco FUP.\n");
    printf("Digite o usuário: ");
    scanf("%s",usuario);
    getchar();
        for(count=0;count<100;count++){
            if(usuario==funcionarios[count].usuario){
                //posicao do funcionario no vetor
                n=count;
                //certeza de que encontrou um funcionario
                aux=1;
            }
        }
        if(usuario[0]=='r'){
            aux=1;
        }
        if(aux=0){
            printf("Usuário não encontrado");
            return 0;
        }
    //verificar senha do usuario
    printf("Digite a senha: ");
    scanf("%s",senha);
    getchar();
    //verificar se a senha está correta
        if(senha==funcionarios[n].senha || senha[0]=='r' && usuario[0]=='r'){
            limpar();
            //printf("Bem vindo %s\n",funcionarios[n].nome);
            printf("Digite a opção desejada:\n");
            printf(" 1-Cadastro de Cliente\n 2-Cadastro de Funcionário\n");
            printf(" 3-Pesquisa de Cliente no sistema\n 4-Atualizar Cadastro de cliente ou funcionário\n 5-Sair\n");
            scanf("%d",&opcao);
            //Opções para alternar entre as funções 
                switch (opcao){
                    case 1:
                    limpar();
                    cadastro();
                    break;

                    case 2:
                    limpar();
                    cadastrofuncionario();
                    break;

                    case 3:
                    limpar();
                    info();
                    break;

                    case 4:
                    limpar();
                    atualizar();
                    break;

                    case 5:
                    limpar();
                    printf("Sistema encerrado.\n");
                    return 0;
                    break;
                    
                    default:
                    limpar();
                    printf("Opção Inválida\n");
                    return 0;
                    break;
                }
        }
        else{
            limpar();
            printf("Senha Incorreta\n");
            return 0;
        }
}
int caixa(cliente clientes[100]){
    char senha[6],aux=0,count;
    int opcao,numcliente=0,agencia,conta;
    setlocale(LC_ALL, "Portuguese");
    limpar();
    printf("\nBem vindo ao Banco FUP \n");
    printf("Digite a agência: \n");
    scanf("%d",&agencia);
    printf("Digite a conta: \n");
    scanf("%d",&conta);
        for(count=0;count<100;count++){
            if( (agencia==clientes[count].agencia) && (conta==clientes[count].conta)){
                numcliente=count;
                aux=1;
                break;
            }
        }
        if(aux==0){
            printf("Agência ou Conta não encontrados\n");
            //tentar novamente
            return 0;
        }
        //procurar por dados em agencia e conta
        printf("Digite a senha: \n");
        //verificar senha correta
        scanf("%s",senha);
        getchar();
        if(clientes[numcliente].errosenha==0){
            printf("Sua conta está bloqueada. Entre em contato com o seu gerente\n");
            return 0;
        }
        if( (senha==clientes[numcliente].senha) && (clientes[numcliente].errosenha!=0) ){
            clientes[numcliente].errosenha=3;
            system("clear");
            printf("\nBem Vindo %s\n",clientes[numcliente].nome);
            printf("Digite a operação desejada:\n");
            printf(" 1-Transferência\n 2-Depósito\n 3-Pagamento de conta\n 4-Saldo da conta\n 5-Saque\n");
            scanf("%d",&opcao);
                switch (opcao){
                    case 1:
                    limpar();
                    transferencia();
                    break;

                    case 2:
                    limpar();
                    deposito();
                    break;

                    case 3:
                    limpar();
                    pagamento();
                    break;

                    case 4:
                    limpar();
                    saldo();
                    break;

                    case 5:
                    limpar();
                    saque();
                    break;
            
                    default:
                    limpar();
                    printf("Opção Inválida");
                    return 0;
                    break;
                }
        }
        else{
            //salvar no banco de dados do cliente o erro
            clientes[numcliente].errosenha--;
            limpar();
            printf(" Senha Incorreta.\n Número de tentativas restantes: %d\n",clientes[numcliente].errosenha);
            return 0;
        }
}
int cadastro(int posicaocadastrocliente,cliente clientes[100],int agencia,int conta){
    //função de cadastro de cliente
    int numero;
        limpar();
        printf("Digite o primeiro nome do cliente:\n");
        scanf("%s",clientes[posicaocadastrocliente].nome);
        getchar();
        printf("Digite o sobrenome do cliente:\n");
        scanf("%s",clientes[posicaocadastrocliente].sobrenome);
        getchar();
        printf("Endereço:\n");
        scanf("%s",clientes[posicaocadastrocliente].rua);
        getchar();
        printf("Número da Casa/Apt:\n");
        scanf("%s",clientes[posicaocadastrocliente].numero);
        getchar();
        printf("CEP sem pontos e traços:\n");
        //cep>8 invalido
        scanf("%s",clientes[posicaocadastrocliente].cep);
        printf("Digite o CPF do cliente:\n");
        verificarcpf();
        printf("Digite a data de nascimento no formato 00/00/0000: \n");
        scanf("%s",clientes[posicaocadastrocliente].data);
        getchar();
        limpar();
        printf("Cadastro Realizado com sucesso\n");
        printf("Número da Agência= %d\n",agencia);
        printf("Número da conta= %d\n",conta);
        clientes[posicaocadastrocliente].errosenha=3;
        clientes[posicaocadastrocliente].saldocorrente=0;
        clientes[posicaocadastrocliente].numerocliente=posicaocadastrocliente;
        clientes[posicaocadastrocliente].agencia=agencia;
        clientes[posicaocadastrocliente].conta=conta;
        conta++;
        posicaocadastrocliente++;
}
int cadastrofuncionario(int posicaocadastrofuncionario,funcionario funcionarios[100]){
    system("clear");
    //função para cadastrar funcionário
        int numero;
        char usuario,senha,senhaanterior;
        int codigogerente=1,codigoatendente=1;
        printf("Digite o primeiro nome do Funcionário:\n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].nome);
        getchar();
        printf("Digite o sobrenome:\n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].sobrenome);
        printf("Endereço:\n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].rua);
        printf("Número da Casa/Apt:\n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].num);
        printf("CEP sem pontos e traços:\n");
        //cep>8 invalido
        scanf("%s",funcionarios[posicaocadastrofuncionario].cep);
        printf("Digite o CPF do funcionário:\n");
        verificarcpf();
        printf("Digite a data de nascimento no formato 00/00/0000: \n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].data);
        printf("Digite o cargo do funcionário:");
        scanf("%s",funcionarios[posicaocadastrofuncionario].cargo);
        printf("Digite o usuário para login no sistema\n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].usuario);
        getchar();
        printf("Digite a senha:\n");
        scanf("%s",funcionarios[posicaocadastrofuncionario].senha);
        funcionarios[posicaocadastrofuncionario].numfun=posicaocadastrofuncionario;
        printf("Cadastro realizado com sucesso. Número do gerente: %d",funcionarios[posicaocadastrofuncionario].numfun);
        posicaocadastrofuncionario++;
}
int info(cliente clientes[100],funcionario funcionarios[100]){
    //função para pesquisar cliente ou funcionário no banco de dados
    int n,cliente,funcionario,count,aux=0,numero=0,op,qtd=0,vf=1;
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
            printf("Digite o nome do cliente: ");
            scanf("%s",nome);
            getchar();
            printf("Resultado da busca:\n");
                for(count=0;count<100;count++){
                    vf=strcmp(nome,clientes[count].nome);
                    if(vf==0){
                        qtd++;
                        printf("%d-%s %s\n",qtd,clientes[count].nome,clientes[count].sobrenome);
                        printf("  Rua:%s Cep:%s Telefone:%s\n",clientes[count].rua,clientes[count].cep,clientes[count].numero);
                        printf("  Cpf:%s Data de Nascimento:%s Número Gerente:%d\n",clientes[count].cpf,clientes[count].data,clientes[count].gerente);
                        printf("  Saldo Conta:%f Agência:%d Conta:%d\n\n",clientes[count].saldocorrente,clientes[count].agencia,clientes[count].conta);
                    }  
                }
                if(qtd==0){
                    printf("Nenhum cliente com o nome %s encontrado.\n",nome);
                }
            break;

            case 2:
            limpar();
            printf("Digite o número do cliente: ");
            scanf("%d",&cliente);
            printf("Resultado da busca:\n");
            for(count=0;count<100;count++){
                if(cliente==clientes[count].numerocliente){
                    numero=count;
                    aux=1;
                }
            }
            if(aux==0){
                printf("Cliente não encontrado.\n");
                return 0;
            }
            else{
                printf("Cliente %s %s. Número do cliente: %d\n",clientes[numero].nome,clientes[numero].sobrenome,clientes[numero].numerocliente);
                return 0;
            }
            break;

            default:
            printf("Opção Inválida.\n");
            return 0;
        }
        

        case 2:
        limpar();
        printf("1-Pesquisa por nome\n2-Pesquisar por número.\n");
        switch(op){
            case 1:

            case 2:
            limpar();
            printf("Digite o número do funcionário: ");
            scanf("%d",&funcionario);
            printf("Resultado da busca:\n");
                for(count=0;count<100;count++){
                    if(funcionario==funcionarios[count].numfun){
                    aux=1;
                    numero=count;
                    }
                }
                if(aux==0){
                    printf("Funcionário não encontrado.\n");
                    return 0;
                }
                else{
                    printf("Funcionário %s %s. Número do funcionário: %d\n",funcionarios[numero].nome,funcionarios[numero].sobrenome,funcionarios[numero].numfun);
                }
            
            break;
        }

        default:
        printf("Opção Inválida.\n");
        return 0;
        break;

    }
}
int atualizar(){
    //função para atualizar cadastro de cliente ou funcionário
    limpar();

}
char verificarcpf(){
    //função para verificar se o cpf é válido
    char cpf[12]; 
    int icpf[12]; 
    int i,somador=0,digito1,result1,result2,digito2,valor; 
    scanf("%s",cpf); 
    getchar();
        for(i=0;i<11;i++){ 
            icpf[i]=cpf[i]-48; 
        } 
    //Primeiro Digito
        for(i=0;i<9;i++){ 
            somador+=icpf[i]*(10-i); 
        } 
        result1=somador%11; 
        if((result1==0)||(result1==1)){ 
            digito1=0; 
        } 
        else{ 
            digito1 = 11-result1; 
        } 
        //Segundo Digito
        somador=0; 
        for(i=0;i<10;i++){ 
            somador+=icpf[i]*(11-i); 
        } 
        valor=(somador/11)*11; 
        result2=somador-valor; 
        if((result2==0)||(result2==1)){ 
            digito2=0; 
        } 
        else{ 
            digito2=11-result2; 
        } 
        if((digito1==icpf[9]) && (digito2==icpf[10])){ 
            return cpf[12];
        } 
        else{ 
        printf("CPF Inválido\n");
        printf("Digite o CPF do cliente:\n");
        return verificarcpf();
        }
}
int transferencia(){
    limpar();
    printf("Digite o número da conta:\n");
    printf("Digite a Agência: ");
}
int deposito(){
    printf("Digite o número da conta:\n");
    printf("Digite a Agência: ");
}
int pagamento(){
    float valor;
    limpar();
    printf("Digite o valor do boleto:\n");
    scanf("%f",&valor);
    /*if(valor<clientes[].saldocorrente){
        clientes[].saldocorrente-=saque;
        limpar();
        printf("Pagamento realizado com sucesso.\n");
    }
    else{
        limpar();
        printf("Saldo Insuficiente.\n Operação Cancelada\n");
    }
    */
}
int saque(){
    float saque;
    limpar();
    printf("Digite o valor do saque:\n");
    scanf("%f",saque);
    /*if(saque<clientes[].saldocorrente){
        clientes[].saldocorrente-=saque;
        limpar();
        printf("Operação realizada com sucesso.\n Retire o dinheiro.\n");
    }
    else{
        limpar();
        printf("Saldo Insuficiente.\n Operação Cancelada\n");
    }*/
}
int saldo(){
    limpar();
    printf("Aguarde...");
    //printf("Saldo disponível na conta corrente= %f\n",clientes[].saldocorrente);
    //delay(3);
    //exibir saldo de acordo com o cliente 
    //printf("Saldo disponível na conta corrente: %.2f\n Saldo disponível na conta poupança: %.2f",saldocorrente,saldopoup);
}
void limpar(){
    system("clear");
    printf("----------------------------------------------------\n");
    printf("----------------------Banco FUP---------------------\n");
    printf("----------------------------------------------------\n");
}
int infofuncionario(funcionario funcionarios[100]){
    int codigo,aux=0,count,n=0;
    limpar();
    printf("Digite o código do funcionário:\n");
    scanf("%d",&codigo);
    for(count=0;count<100;count++){
        if(funcionarios[count].numfun==codigo){
            n=count;
            aux=1;
        }
    }
    if(aux==0){
        printf("Funcionário não encontrado.\n");
    }
    else{
        return n;
    }
}
int infocliente(cliente clientes[100]){
    int codigo,aux=0,count,n=0,ag,ct;
    limpar();
    //numero da conta de agencia
    printf("Digite a agência:\n");
    scanf("%d",&ag);
    printf("Digite a conta:\n");
    scanf("%d",&ct);
    for(count=0;count<100;count++){
        if(clientes[count].agencia==ag && clientes[count].conta==ct){
            n=count;
            aux=1;
        }
    }
    if(aux==0){
        printf("Cliente não encontrado.\n");
        return 0;
    }
    else{
        return n;
    }
}