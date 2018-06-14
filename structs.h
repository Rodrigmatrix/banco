typedef struct{
    char nome[20],sobrenome[100],rua[100],cep[8],num[6],numero[15],data[10],cpf[12],senha[7];
    int errosenha,numerocliente,agencia,conta,ativo;
    float saldocorrente;
}cliente;
typedef struct{
    char nome[20],sobrenome[60],rua[100],cep[8],data[10],num[6],cpf[12],senha[15],usuario[20],cargo[20],numero[15];
    int tipo,numfun;
}funcionario;