//.h --> declara
//.c --> implementa

#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "dados.h"
#include "user.h"

int login() {
    char username[40];
    char password[40];

    printf("\n=== LOGIN ===\n");

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

    printf("\n=== CADASTRO ===\n");
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
            strcpy(novo.role, "gerente");
            break;
        case 2:
            strcpy(novo.role, "atendente");
            break;
    }

    users[totalUsers] = novo;
    totalUsers++;

    printf("\nUsuario cadastrado com sucesso! ID: %d\n", novo.id);

}
