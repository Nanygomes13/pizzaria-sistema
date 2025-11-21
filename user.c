#include <stdio.h>
#include <string.h>
#include "user.h"
#include "arquivos.h"  
#include "dados.h"
#include "structs.h"


int login() {
    char username[40];
    char password[40];

    printf("\n==== LOGIN ====\n");

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Senha: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {

            printf("\nLogin realizado com sucesso! Bem-vindo, %s.\n", users[i].username);
            return i; 
        }
    }

    printf("\nUsername ou senha incorretos!\n");
    return -1; 
}

void cadastrarUser() {
    int opcao;

    printf("\n==== CADASTRO ====\n");
    printf("1 - Gerente\n");
    printf("2 - Atendente\n");
    printf("Escolha o tipo de usuario: ");
    scanf("%d", &opcao);
    getchar(); 

    if (opcao < 1 || opcao > 2) {
        printf("Opcao invalida!\n");
        return;
    }

    User novo;
    novo.id = gerarIdUser();

    printf("Digite um username: ");
    fgets(novo.username, sizeof(novo.username), stdin);
    novo.username[strcspn(novo.username, "\n")] = 0;

    printf("Digite uma senha: ");
    fgets(novo.password, sizeof(novo.password), stdin);
    novo.password[strcspn(novo.password, "\n")] = 0;

    switch (opcao) {
        case 1:
            strcpy(novo.cargo, "gerente");
            break;
        case 2:
            strcpy(novo.cargo, "atendente");
            break;
    }

    users[totalUsers] = novo;
    totalUsers++;

    salvarUsers();

    printf("\nUsuario cadastrado com sucesso! ID: %d\n", novo.id);

}

void listarUsers() {
    printf("\n==== LISTA DE USUARIOS ====\n");

    if (totalUsers == 0) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalUsers; i++) {
        printf("\nID: %d", users[i].id);
        printf("\nUsername: %s", users[i].username);
        printf("\nCargo: %s\n", users[i].cargo);
    }
}

void editarUser() {
    int id;
    printf("\nDigite o ID do usuario que deseja editar: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    printf("Novo username: ");
    fgets(users[pos].username, sizeof(users[pos].username), stdin);
    users[pos].username[strcspn(users[pos].username, "\n")] = 0;

    printf("Nova senha: ");
    fgets(users[pos].password, sizeof(users[pos].password), stdin);
    users[pos].password[strcspn(users[pos].password, "\n")] = 0;

    salvarUsers();

    printf("Usuario atualizado!\n");
}

void excluirUser() {
    int id;
    printf("\nDigite o ID do usuario que deseja excluir: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    for (int i = pos; i < totalUsers - 1; i++) {
        users[i] = users[i + 1];
    }

    totalUsers--;

    salvarUsers();

    printf("Usuario removido com sucesso.\n");
}
