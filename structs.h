typedef struct{
    char nome[20],sobrenome[100],rua[100],cep[8],num[6],numero[11],data[10],cpf[12],senha[6];
    int errosenha,gerente,numerocliente,agencia,conta;
    float saldocorrente;
}cliente;
typedef struct{
    char nome[20],sobrenome[60],rua[100],cep[8],data[10],num[6],cpf[12],senha[15],usuario[20],cargo[20];
    int tipo,numfun;
}funcionario;