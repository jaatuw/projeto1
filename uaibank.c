#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct usuario // declarando a struct
    {
        char nome[100];
        int idade;
        float saldo;
    };
int escolha;

void SalvaUser(struct usuario *grupo, int *idVetor, int id) {
    
    FILE *dados;
    dados = fopen("dados.txt", "a");
    if (dados == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    fprintf(dados, "ID: %d\nNome: %s\nIdade: %d\nSaldo: %.2f\n\n", id+1, grupo[id].nome, grupo[id].idade, grupo[id].saldo);

    fclose(dados);
}

void menu() { 
    
    printf("1.Insercao de um novo usuario: \n");
    printf("2.Insercao de varios usuarios: \n");
    printf("3.Busca de um usuario por id: \n");
    printf("4.Transferencias entre usuarios: \n");
    printf("5.Remocao de um usuario por id: \n");
    printf("6.Sair \n");
    
    do {
        scanf("%d", &escolha);
    }while(escolha < 1 || escolha > 6);
    
   
}

int confereid(int *idVetor, int *qtdu) {
    for (int i = 0; i < (*qtdu)+1; i++){
    if (idVetor[i] == 1 || i == (*qtdu)) { 
        //adicionar memoria
    } else {
        return i;
    }
}
}

void insereuser(struct usuario *grupo, int *idVetor, int *qtdu) {
    int id = confereid(idVetor, qtdu);
    do {
        printf("Insira seus dados da seguinte maneira: Nome, Idade(0-100), Valor da conta\n");
        scanf(" %[^,], %d, %f", grupo[id].nome, &grupo[id].idade, &grupo[id].saldo);
    }while (grupo[id].idade < 0 || grupo[id].idade > 100);
    idVetor[id] = 1;
    printf("Seu ID cadastrado eh %d\n", id+1);
    (*qtdu)++;
    SalvaUser(grupo, idVetor, id);
}

void inserevariosuser(struct usuario *grupo, int *idVetor, int *qtdu) {
    printf("Quantos usuarios quer inserir?\n");
    int quantidade;
    scanf("%d", &quantidade);
    for (int i = 0; i < quantidade; i++) {
        insereuser(grupo, idVetor, qtdu);
    }
}


void buscauser(struct usuario *grupo, int *idVetor, int *qtdu) {
    printf("Qual usuario quer buscar?\n");
    int idprocurado;
    scanf("%d", &idprocurado);
    if (idVetor[idprocurado-1] == 1)
    {
        printf("%s, %d, %.2f\n", grupo[idprocurado-1].nome, grupo[idprocurado-1].idade, grupo[idprocurado-1].saldo);
    }
    else
        printf("O ID nao esta cadastrado\n");   
}

void removeuser(struct usuario *grupo, int *idVetor, int *qtdu) {
    printf("Qual usuario voce quer remover?\n");
    int removerid;
    scanf("%d", &removerid);
    if (idVetor[(removerid-1)] == 0) {
        printf("Erro: Usuário não encontrado.\n");
    }
    else {
        idVetor[(removerid-1)] = 0;
        (*qtdu)--;
        printf("Usuario %d removido com sucesso", removerid);
    }
}

int main () {


    int *idVetor;
    idVetor = (int *) calloc(10, sizeof(int));
    int qtdu = 0;
    struct usuario *grupo = (struct usuario*) malloc(10*sizeof(struct usuario));

    if(idVetor == NULL || grupo == NULL) {
        printf("Falha ao alocar memoria");
        exit(1);
    }

    do {
    menu();
        switch (escolha)
        {
        case 1:
            insereuser(grupo, idVetor, &qtdu);
            break;
        case 2:
            inserevariosuser(grupo, idVetor, &qtdu);
            break;
        case 3:
            buscauser(grupo, idVetor, &qtdu);
            break;
        case 4:
            //transferencia();
            break;
        case 5:
            removeuser(grupo, idVetor, &qtdu);
            break;
        case 6:
            exit(0);
            break;
        }
    } while (escolha != 6);
    free(idVetor);
    free(grupo);
}