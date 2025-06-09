#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct 
{
    char nome[100];
    int idade;
    float saldo;
} usuario;

int escolha;
int users_max = 2;

int conferememoria(usuario **grupo, int **idVetor, int *qtdu);
void lebanco(int *qtdu, usuario **grupo, int **idVetor);
void transferencia(usuario *grupo, int *idVetor);
void removeusertexto(int iddeletado);
void SalvaUser(usuario *grupo, int id);
void removeuser(int *idVetor, int *qtdu);
void buscauser(usuario *grupo, int *idVetor);
void mudarSaldo(int id1, int id2, float quantia);
void inserevariosuser(usuario **grupo, int **idVetor, int *qtdu);
void menu();
void insereuser(usuario **grupo, int **idVetor, int *qtdu);
int confereid(usuario **grupo, int **idVetor, int *qtdu);

void lebanco(int *qtdu, usuario **grupo, int **idVetor)
{
    FILE *bd;
    bd = fopen("dados.txt", "r");
    if (bd == NULL)
    {
        return;
    }

    int contadorlinhas = 0;
    char nome[100];
    int idade;
    float saldo;
    char linha[1000];
    int usuarioslidos = 0;

    while (fgets(linha, sizeof(linha), bd))
    {
        if (contadorlinhas >= users_max)
        {
            conferememoria(grupo, idVetor, &usuarioslidos);
        }

        if (sscanf(linha, " %[^,], %d, %f", nome, &idade, &saldo) == 3)
        {
            strcpy((*grupo)[contadorlinhas].nome, nome);
            (*grupo)[contadorlinhas].idade = idade;
            (*grupo)[contadorlinhas].saldo = saldo;
            (*idVetor)[contadorlinhas] = 1; 
            usuarioslidos++;
        }
        
        contadorlinhas++;
    }
    
    *qtdu = usuarioslidos;
    fclose(bd);
}

int conferememoria(usuario **grupo, int **idVetor, int *qtdu)
{
    int oldusersmax = users_max;
    users_max *= 2;

    usuario* tempgrupo = realloc(*grupo, users_max * sizeof(usuario));
    if (tempgrupo == NULL) {
        printf("realloc para grupo falhou!\n");
        exit(1);
    }
    *grupo = tempgrupo;

    int* tempidVetor = realloc(*idVetor, users_max * sizeof(int));
     if (tempidVetor == NULL) {
        printf("realloc para idVetor falhou!\n");
        exit(1);
    }
    *idVetor = tempidVetor;
    
    for (int i = oldusersmax; i < users_max; i++) {
        (*idVetor)[i] = 0;
    }
    return 0;
}

int confereid(usuario **grupo, int **idVetor, int *qtdu)
{
    for (int i = 0; i < users_max; i++)
    {
        if ((*idVetor)[i] == 0)
        {
            return i;
        }
    }
    
    conferememoria(grupo, idVetor, qtdu);
    
    int idlivre = users_max / 2;
    return idlivre;
}

void insereuser(usuario **grupo, int **idVetor, int *qtdu)
{
    int id = confereid(grupo, idVetor, qtdu);
    int entradas;
    char linha[200];
    char nome[100];
    int idade;
    float saldo;

    do
    {
        printf("Insira seus dados da seguinte maneira: Nome, Idade(0-100), Valor da conta\n");

        if (fgets(linha, sizeof(linha), stdin) == NULL)
        {
            printf("Erro na leitura da entrada. Tente novamente.\n");
            continue;
        }

        linha[strcspn(linha, "\n")] = '\0';
        entradas = sscanf(linha, " %99[^,], %d, %f", nome, &idade, &saldo);

        if (entradas != 3)
        {
            printf("Entrada invalida. Certifique-se de digitar no formato correto.\n");
            continue;
        }
        if (idade < 0 || idade > 100)
        {
            printf("Idade invalida. Deve estar entre 0 e 100.\n");
            continue;
        }

        strcpy((*grupo)[id].nome, nome);
        (*grupo)[id].idade = idade;
        (*grupo)[id].saldo = saldo;
        break;
    } while (1);

    (*idVetor)[id] = 1;
    printf("Seu ID cadastrado: %d\n", id + 1);
    (*qtdu)++;
    SalvaUser(*grupo, id);
}

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

void SalvaUser(usuario *grupo, int id)
{
    FILE *dados;
    FILE *temp;
    dados = fopen("dados.txt", "r");
    temp = fopen("temp.txt", "w");
    if (temp == NULL) { 
        if(dados) fclose(dados);
        printf("Erro ao criar arquivo temporario!\n");
        return;
    }
    if (dados == NULL) { 
        fclose(temp);
        dados = fopen("dados.txt", "w");
        if(dados) {
            fprintf(dados, "%s, %d, %.2f\n", grupo[id].nome, grupo[id].idade, grupo[id].saldo);
            fclose(dados);
        }
        return;
    }
    char linha[1000];
    int contador = 0;
    int usuarioatualizado = 0;
    while (fgets(linha, sizeof(linha), dados))
    {
        if (contador != id)
        {
            fputs(linha, temp);
        }
        else
        {
            fprintf(temp, "%s, %d, %.2f\n", grupo[id].nome, grupo[id].idade, grupo[id].saldo);
            usuarioatualizado = 1;
        }
        contador++;
    }
    if (!usuarioatualizado)
    {
        fprintf(temp, "%s, %d, %.2f\n", grupo[id].nome, grupo[id].idade, grupo[id].saldo);
    }
    fclose(dados);
    fclose(temp);
    remove("dados.txt");
    rename("temp.txt", "dados.txt");
}

void mudarSaldo(int id1, int id2, float quantia)
{
    FILE *dados;
    FILE *temp;
    dados = fopen("dados.txt", "r");
    temp = fopen("temp.txt", "w");
    if (dados == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    char linha[1000];
    char nome[100];
    int idade;
    float saldo;
    int contador = 0;
    while (fgets(linha, sizeof(linha), dados))
    {
        if (sscanf(linha, " %[^,], %d, %f", nome, &idade, &saldo) == 3) {
            if (contador == id1) {
                saldo -= quantia;
                fprintf(temp, "%s, %d, %.2f\n", nome, idade, saldo);
            } else if (contador == id2) {
                saldo += quantia;
                fprintf(temp, "%s, %d, %.2f\n", nome, idade, saldo);
            } else {
                fputs(linha, temp);
            }
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

void menu()
{
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
            linha[strcspn(linha,"\n")] = '\0';
            continue;
        }
    } while (escolha < 1 || escolha > 6);
}

void inserevariosuser(usuario **grupo, int **idVetor, int *qtdu)
{
    printf("Quantos usuarios quer inserir?\n");
    int quantidade;
    scanf("%d", &quantidade);
    while (getchar() != '\n');
    for (int i = 0; i < quantidade; i++)
    {
        insereuser(grupo, idVetor, qtdu);
    }
}

void buscauser(usuario *grupo, int *idVetor)
{
    printf("Qual usuario quer buscar?\n");
    int idprocurado;
    scanf("%d", &idprocurado);
    while (getchar() != '\n');
    if (idprocurado > 0 && idprocurado <= users_max && idVetor[idprocurado - 1] == 1)
    {
        printf("%s, %d, %.2f\n", grupo[idprocurado - 1].nome, grupo[idprocurado - 1].idade, grupo[idprocurado - 1].saldo);
    }
    else
        printf("O ID nao esta cadastrado\n");
}

void removeuser(int *idVetor, int *qtdu)
{
    printf("Qual usuario voce quer remover?\n");
    int removerid;
    scanf("%d", &removerid);
    while (getchar() != '\n');
    if (removerid > 0 && removerid <= users_max && idVetor[(removerid - 1)] == 1)
    {
        idVetor[(removerid - 1)] = 0;
        (*qtdu)--;
        printf("Usuario %d removido com sucesso\n", removerid);
        removeusertexto(removerid - 1);
    }
    else
    {
        printf("Erro: Usuario nao encontrado.\n");
    }
}

void transferencia(usuario *grupo, int *idVetor)
{
    printf("Insira de qual usuario quer retirar, depositar e quantia (<retirada> <depositar> <quantia>)\n");
    int usuario1, usuario2;
    float quantia;
    scanf("%d %d %f", &usuario1, &usuario2, &quantia);
    while (getchar() != '\n');
    if (usuario1 <= 0 || usuario1 > users_max || usuario2 <= 0 || usuario2 > users_max || idVetor[usuario1 - 1] == 0 || idVetor[usuario2 - 1] == 0)
    {
        printf("Algum ou ambos dos usuarios nao existem");
        return;
    }
    if (grupo[usuario1 - 1].saldo < quantia)
    {
        printf("Saldo Insuficiente\n");
        return;
    }
    else
    {
        grupo[usuario1 - 1].saldo -= quantia;
        grupo[usuario2 - 1].saldo += quantia;
        printf("A sua transferencia de R$ %.2f foi realizada do usuario %d para o usuario %d!", quantia, usuario1, usuario2);
    }
    mudarSaldo(usuario1 - 1, usuario2 - 1, quantia);
}

int main()
{
    int qtdu = 0;
    usuario *grupo = malloc(users_max * sizeof(usuario));
    if (grupo == NULL) {
        printf("Erro ao alocar memória para grupo\n");
        return 1;
    }
    int *idVetor = calloc(users_max, sizeof(int));
    if (idVetor == NULL) {
        printf("Erro ao alocar memória para id\n");
        free(grupo);
        return 1;
    }
    lebanco(&qtdu, &grupo, &idVetor);
    do
    {
        menu();
        switch (escolha)
        {
        case 1:
            insereuser(&grupo, &idVetor, &qtdu);
            break;
        case 2:
            inserevariosuser(&grupo, &idVetor, &qtdu);
            break;
        case 3:
            buscauser(grupo, idVetor);
            break;
        case 4:
            transferencia(grupo, idVetor);
            break;
        case 5:
            removeuser(idVetor, &qtdu);
            break;
        case 6:
            exit(0);
            break;
        }
    } while (escolha != 6);
    free(idVetor);
    free(grupo);
    return 0;
}