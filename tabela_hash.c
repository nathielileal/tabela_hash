#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_TABELA 100
#define TAMANHO_NOME 50

// Estrutura para armazenar os contatos
typedef struct Contato {
    char nome[TAMANHO_NOME];
    char telefone[15];
    struct Contato* proximo;
} Contato;

// Tabela hash
Contato* tabelaHash[TAMANHO_TABELA];

// Função hash
unsigned int funcaoHash(const char* nome) {
    unsigned int hash = 0;
    while (*nome) {
        hash = (hash * 31) + *nome;
        nome++;
    }
    return hash % TAMANHO_TABELA;
}

// Adicionar contato
void adicionarContato() {
    char nome[TAMANHO_NOME], telefone[15];

    printf("Digite o nome: ");
    scanf(" %49[^\n]s", nome);
    printf("Digite o telefone: ");
    scanf(" %14s", telefone);

    unsigned int indice = funcaoHash(nome);

    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = NULL;

    if (tabelaHash[indice] == NULL) {
        tabelaHash[indice] = novoContato;
    } else {
        Contato* atual = tabelaHash[indice];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoContato;
    }

    printf("Contato adicionado com sucesso!\n");
}


// Buscar contato
void buscarContato() {
    char nome[TAMANHO_NOME];

    printf("Digite o nome para buscar: ");
    scanf(" %49[^\n]s", nome);

    unsigned int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Telefone de %s: %s\n", atual->nome, atual->telefone);
            return;
        }
        atual = atual->proximo;
    }

    printf("Contato não encontrado.\n");
}

// Remover contato
void removerContato() {
    char nome[TAMANHO_NOME];

    printf("Digite o nome para remover: ");
    scanf(" %49[^\n]s", nome);

    unsigned int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];
    Contato* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                tabelaHash[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Contato não encontrado.\n");
}

// Exibir todos os contatos
void exibirContatos() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* atual = tabelaHash[i];
        while (atual != NULL) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

// Medir tempo
void medirTempo(void (*funcao)()) {
    clock_t inicio, fim;
    inicio = clock();
    funcao();
    fim = clock();
    printf("Tempo de execução: %.3f ms\n", ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000);
}

int main() {
    int opcao;

    // Inicializar tabela hash
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i] = NULL;
    }

    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                medirTempo(adicionarContato);
                break;
            case 2:
                medirTempo(buscarContato);
                break;
            case 3:
                medirTempo(removerContato);
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberar memória
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* atual = tabelaHash[i];
        while (atual != NULL) {
            Contato* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    return 0;
}
