#include <stdio.h>
#include <stdlib.h>

struct usuario // declarando a struct
    {
        char nome[100];
        int idade;
        float saldo;
    };
    
int escolha;

int id = 1;

void SalvaUser(struct usuario *grupo, int *idVetor) {
    FILE *dados;
    dados = fopen("dados.txt", "w");
    if (dados == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(dados, "Nome: %s\nIdade: %d\nSaldo: %.2f\n\n", 
            grupo[id].nome, grupo[id].idade, grupo[id].saldo);

    fclose(dados);
}

void menu() { 
    
    printf("1.Insercao de um novo usuario: \n");
    printf("2.Insercao de varios usuarios: \n");
    printf("3.Busca de um usuario por id: \n");
    printf("4.Transferencias entre usuarios: \n");
    printf("5.Remocao de um usuario por id: \n");

    do 
    {
    scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 5);
}
void confereid(int *idVetor, int *qtdu) {
    for (int i = 0; i < qtdu; i++){
    if (idVetor[i] == 0) { 
        id = i;
    } else {
        continue;
    }
}
}

void insereuser(struct usuario *grupo, int *idVetor, int *qtdu) {
    scanf(" %[^,], %d, %f", grupo[id].nome, &grupo[id].idade, &grupo[id].saldo);
    printf("%s, %d, %.2f\n", grupo[id].nome, grupo[id].idade, grupo[id].saldo);
    idVetor[id] = id;
    id++;
    qtdu++;
}


void inserevariosuser(struct usuario *grupo, int *idVetor, int *qtdu) {
    printf("Quantos usuarios quer inserir?\n");
    int quantidade;
    scanf("%d", &quantidade);
    for (int i = 0; i < quantidade; i++) {
        scanf(" %[^,], %d, %f", grupo[id].nome, &grupo[id].idade, &grupo[id].saldo);
        idVetor[id] = id;
        id++;
        qtdu++;
    }
}


void buscauser(struct usuario *grupo, int *idVetor, int *qtdu) {
    printf("Qual usuario quer buscar?\n");
    int idprocurado;
    scanf("%d", &idprocurado);
    if (idprocurado == idVetor[idprocurado])
    {
         printf("%s, %d, %.2f\n", grupo[idprocurado].nome, grupo[idprocurado].idade, grupo[idprocurado].saldo);
    }
    else
        printf("O ID nao esta cadastrado\n");   
}


int main () {

    int *idVetor;
    idVetor = (int *) calloc(10, sizeof(int));
    int qtdu = 0;
    struct usuario *grupo = (struct usuario*) malloc(10*sizeof(struct usuario));

    do {
    menu();
        switch (escolha)
        {
        case 1:
            insereuser(grupo, idVetor, &qtdu);
            SalvaUser(grupo, idVetor);
            break;
        case 2:
            inserevariosuser(grupo, idVetor, &qtdu);
            break;
        case 3:
            buscauser(grupo, idVetor, &qtdu);
            break;
        case 4:
            break;
        case 5:
            //removeuser();
            break;
        default:
            break;
        }
    } while (escolha > 1 || escolha < 5);
}