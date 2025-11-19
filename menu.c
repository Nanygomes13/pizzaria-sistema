#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "user.h"
#include "dados.h"
#include "structs.h"
#include "pizza.h"
#include "pedidos.h"

void menuInicial() {
    int opc;

    do {
        printf("\n       SISTEMA PIZZAFONY    \n");
        printf("1 - Login\n");
        printf("2 - Cadastro\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar(); 

        switch (opc) {
            case 1: {
                int pos = login();
                if (pos != -1) {  
                    if (strcmp(users[pos].role, "gerente") == 0) {
                        menuGerente(pos);
                    } else if (strcmp(users[pos].role, "atendente") == 0) {
                        menuAtendente(pos);
                    } 
                }
                break;
            }
            case 2:
                cadastrarUser();
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opc != 0);
}

void menuAtendente(int posUser) {
    int opc;

    do {
        printf("\n\n MENU ATENDENTE \n");
        printf("1 - Ver pedidos\n");
        printf("2 - Ver cardapio\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar(); 

        switch (opc) {
            case 1:
                listarPedidos();
                break;

            case 2:
                mostrarCardapio();
                break;

            case 0:
                printf("Saindo do menu atendente...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 0);
}

void menuGerente(int posUser) {
    int opc;

    do {
        printf("\n\n MENU GERENTE \n");
        printf("1 - Cadastrar pizza\n");
        printf("2 - Ver cardapio\n");
        printf("3 - Ver pedidos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                cadastrarPizza();
                break;

            case 2:
                mostrarCardapio();
                break;

            case 3:
                listarPedidos();
                break;

            case 0:
                printf("Saindo do menu gerente...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 0);
}
