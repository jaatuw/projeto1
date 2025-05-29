#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


typedef struct // declarando a struct
    {
        char nome[100];
        int idade;
        float saldo;
    } usuario;
int escolha;


void removeusertexto (int iddeletado) {
    FILE *dados;
    FILE *temp;
    dados = fopen("dados.txt", "r");
    temp = fopen("temp.txt", "w");
    if (dados == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    char linha[100];
    char nome[100];
    int idade;
    float saldo;
    int contador = 0;
    
    while (fgets(linha, sizeof(linha), dados))
    {
        if (contador == iddeletado)
        {
            fprintf(temp, "\n"); 
        } else if(sscanf(linha, " %[^,], %d, %f", nome, &idade, &saldo) != 3) {
            fputs(linha, temp);
        } else {
            fprintf(temp, "%s, %d, %.2f\n", nome, idade, saldo);
        }
        contador++;
    }

    fclose(dados);
    fclose(temp);

    remove("dados.txt");
    rename("temp.txt", "dados.txt");
}


void SalvaUser(usuario *grupo, int *idVetor, int id, int *qtdu) {
    
    FILE *dados;
    FILE *temp;
    dados = fopen("dados.txt", "r");
    temp = fopen("temp.txt", "w");
    if (dados == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[100];
    char nome[100];
    int idade;
    float saldo;
    int contador = 0;
    int usuarioatualizado = 0;

    while (fgets(linha, sizeof(linha), dados)) {
        if (contador != id)
        {
            fputs(linha, temp);
        } else {
            sscanf(linha, " %[^,], %d, %f", nome, &idade, &saldo);
            fprintf(temp, "%s, %d, %.2f\n", grupo[id].nome, grupo[id].idade, grupo[id].saldo);
            usuarioatualizado = 1;
        }
        contador++;
    }

    if (!usuarioatualizado) {
        fprintf(temp, "%s, %d, %.2f\n", grupo[id].nome, grupo[id].idade, grupo[id].saldo);
    }

    fclose(dados);
    fclose(temp);

    remove("dados.txt");
    rename("temp.txt", "dados.txt");
}


void mudarSaldo(int id1, int id2, float quantia) {

    FILE *dados;
    FILE *temp;
    dados = fopen("dados.txt", "r");
    temp = fopen("temp.txt", "w");
    if (dados == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    char linha[100];
    char nome[100];
    int idade;
    float saldo;
    int contador = 0;
    
    while (fgets(linha, sizeof(linha), dados))
    {
        sscanf(linha, " %[^,], %d, %f", nome, &idade, &saldo);

        if (contador == id1) {
            saldo -= quantia;
            fprintf(temp, "%s, %d, %.2f\n", nome, idade, saldo);
        } else if (contador == id2) {
            saldo += quantia;
            fprintf(temp, "%s, %d, %.2f\n", nome, idade, saldo);
        } else {
            fputs(linha, temp);
        }
        contador++;
        
    }

    fclose(dados);
    fclose(temp);

    remove("dados.txt");
    rename("temp.txt", "dados.txt");
}

void menu() { 
    
    char linha[10];

    printf("\n\n[1.] Insercao de um novo usuario: \n");
    printf("[2.] Insercao de varios usuarios: \n");
    printf("[3.] Busca de um usuario por id: \n");
    printf("[4.] Transferencias entre usuarios: \n"); 
    printf("[5.] Remocao de um usuario por id: \n");
    printf("[6.] Sair \n\n");
    
    do {
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("Erro na leitura. Tente novamente.\n");
            linha[strcspn(linha, "\n")] = 0;
            continue;
        }
        if (sscanf(linha, "%d", &escolha) != 1) {
            printf("Entrada invalida. Digite um numero de 1 a 6.\n");
            continue;
        }
        } while(escolha < 1 || escolha > 6);
    } 

int confereid(int *idVetor, int *qtdu) {
    for (int i = 0; i < (*qtdu)+1; i++){
    if (idVetor[i] == 1) { 
        //adicionar memoria
    } else {
        return i;
    }
}
}

void insereuser(usuario *grupo, int *idVetor, int *qtdu) {
    int id = confereid(idVetor, qtdu);
    int entradas;
    char linha[200];
    char nome[100];
    int idade;
    float saldo;

    do {
        printf("Insira seus dados da seguinte maneira: Nome, Idade(0-100), Valor da conta\n");

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("Erro na leitura da entrada. Tente novamente.\n");
            continue;
        }

        linha[strcspn(linha, "\n")] = '\0';

        entradas = sscanf(linha, " %99[^,], %d, %f", nome, &idade, &saldo);

        if (entradas != 3) {
            printf("Entrada invalida. Certifique-se de digitar no formato correto.\n");
            continue;
        }

        if (idade < 0 || idade > 100) {
            printf("Idade inválida. Deve estar entre 0 e 100.\n");
            continue;
        }

        strcpy(grupo[id].nome, nome);
        grupo[id].idade = idade;
        grupo[id].saldo = saldo;

        break;

    } while (1);

    idVetor[id] = 1;
    printf("Seu ID cadastrado: %d\n", id + 1);
    (*qtdu)++;
    SalvaUser(grupo, idVetor, id, qtdu);
}

void inserevariosuser(usuario *grupo, int *idVetor, int *qtdu) {
    
    printf("Quantos usuarios quer inserir?\n");
    int quantidade;
    scanf("%d", &quantidade);

    while (getchar() != '\n'); 

    for (int i = 0; i < quantidade; i++) {
        insereuser(grupo, idVetor, qtdu);
    }
}


void buscauser(usuario *grupo, int *idVetor, int *qtdu) {

    printf("Qual usuario quer buscar?\n");

    int idprocurado;
    scanf("%d", &idprocurado);

    while (getchar() != '\n'); 

    if (idVetor[idprocurado-1] == 1)
    {
        printf("%s, %d, %.2f\n", grupo[idprocurado-1].nome, grupo[idprocurado-1].idade, grupo[idprocurado-1].saldo);
    }
    else
        printf("O ID nao esta cadastrado\n");   
}

void removeuser(usuario *grupo, int *idVetor, int *qtdu) {
    printf("Qual usuario voce quer remover?\n");
    int removerid;
    scanf("%d", &removerid);

    while (getchar() != '\n'); 

    if (idVetor[(removerid-1)] == 0) {
        printf("Erro: Usuario nao encontrado.\n");
    }
    else {
        idVetor[(removerid-1)] = 0;
        (*qtdu)--;
        printf("Usuario %d removido com sucesso\n", removerid);
    }
    removeusertexto(removerid-1);
}

void transferencia(usuario *grupo, int *idVetor) {

    printf("Insira de qual usuario quer retirar, depositar e quantia (<retirada> <depositar> <quantia>)\n");
    int usuario1, usuario2;
    float quantia;

    scanf("%d %d %f", &usuario1, &usuario2, &quantia);

    while (getchar() != '\n'); 

    if (idVetor[usuario1-1] == 0 || idVetor[usuario2-1] == 0)
    {
        printf("Algum ou ambos dos usuarios nao existem");
        return;
    }
    
    if (grupo[usuario1-1].saldo < quantia)
    {
        printf("Saldo Insuficiente\n");
        return;
    } else {
        grupo[usuario1-1].saldo -= quantia;
        grupo[usuario2-1].saldo += quantia;
        printf("A sua transferencia de R$ %.2f foi realizada do usuario %d para o usuario %d!", quantia, usuario1, usuario2);
    } 

    mudarSaldo(usuario1-1, usuario2-1, quantia);
    
}
int main () {

    setlocale(LC_ALL, "Portuguese_Brazil");

    int *idVetor;
    idVetor = (int *) calloc(10, sizeof(int));
    int qtdu = 0;
    usuario *grupo = (usuario*) malloc(10*sizeof(usuario));

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
            transferencia(grupo, idVetor);
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