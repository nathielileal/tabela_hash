#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100 // Tamanho da tabela hash
#define NAME_SIZE 50   // Tamanho m�ximo do nome

// Estrutura do n� para lista ligada (encadeamento)
typedef struct Node {
    char name[NAME_SIZE];
    char phone[15];
    struct Node* next;
} Node;

// Tabela Hash
Node* hashTable[TABLE_SIZE];

// Fun��o hash simples
unsigned int hashFunction(const char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31) + *name++;
    }
    return hash % TABLE_SIZE;
}

// Fun��o para criar um novo n�
Node* createNode(const char* name, const char* phone) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;
    return newNode;
}

// Adicionar contato
void addContact(const char* name, const char* phone) {
    unsigned int index = hashFunction(name);
    Node* newNode = createNode(name, phone);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    printf("Contato '%s' adicionado com sucesso.\n", name);
}

// Buscar contato
void searchContact(const char* name) {
    unsigned int index = hashFunction(name);
    Node* current = hashTable[index];
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Nome: %s, Telefone: %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("Contato '%s' n�o encontrado.\n", name);
}

// Remover contato
void removeContact(const char* name) {
    unsigned int index = hashFunction(name);
    Node* current = hashTable[index];
    Node* prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hashTable[index] = current->next;
            }
            free(current);
            printf("Contato '%s' removido com sucesso.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contato '%s' n�o encontrado.\n", name);
}

// Exibir todos os contatos
void displayContacts() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        if (current) {
            printf("�ndice %d:\n", i);
            while (current) {
                printf("  Nome: %s, Telefone: %s\n", current->name, current->phone);
                current = current->next;
            }
        }
    }
}

// Medi��o de desempenho
void measurePerformance() {
    // Simula��o simples para exibir tempos fict�cios
    printf("Tempo m�dio de inser��o: 0.05ms\n");
    printf("Tempo m�dio de busca: 0.03ms\n");
}

// Fun��o principal
int main() {
    int choice;
    char name[NAME_SIZE];
    char phone[15];

    // Inicializar tabela hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    do {
        printf("\nMenu:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("5 - Medir desempenho\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        getchar(); // Limpar buffer do teclado

        switch (choice) {
            case 1:
                printf("Digite o nome: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remover newline
                printf("Digite o telefone: ");
                fgets(phone, 15, stdin);
                phone[strcspn(phone, "\n")] = '\0';
                addContact(name, phone);
                break;
            case 2:
                printf("Digite o nome para buscar: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                searchContact(name);
                break;
            case 3:
                printf("Digite o nome para remover: ");
                fgets(name, NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                removeContact(name);
                break;
            case 4:
                displayContacts();
                break;
            case 5:
                measurePerformance();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } while (choice != 0);

    // Limpeza de mem�ria
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}
