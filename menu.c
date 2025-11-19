#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "user.h"
#include "dados.h"
#include "structs.h"
#include "pizza.h"
#include "clientes.h"
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
                    if (strcmp(users[pos].cargo, "gerente") == 0) {
                        menuGerente();
                    } else if (strcmp(users[pos].cargo, "atendente") == 0) {
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

void menuAtendente(int pos) {
    int opc;

    do {
        printf("\n===== MENU ATENDENTE =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Fazer Pedido\n");
        printf("4 - Listar Pedidos\n");
        printf("5 - Editar Pedido\n");
        printf("6 - Excluir Pedido\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                cadastrarCliente();
                break;

            case 2:
                listarClientes();
                break;

            case 3:
                cadastrarPedido();
                break;

            case 4:
                listarPedidos();
                break;

            case 5:
                editarPedido();
                break;

            case 6:
                excluirPedido();
                break;

            case 0:
                printf("Voltando ao menu anterior...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 0);
}


void menuGerente() {
    int opc;

    do {
        printf("\n\n MENU GERENTE \n");
        printf("1 - Gerenciar Usuarios\n");
        printf("2 - Gerenciar Clientes\n");
        printf("3 - Gerenciar Pizzas\n");
        printf("4 - Gerenciar Pedidos\n");
        printf("5 - Relatorios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {

            case 1: {
                int ou;
                do {
        printf("\n\n--- GERENCIAR USUARIOS ---\n");
        printf("1 - Cadastrar Usuario\n");
        printf("2 - Listar Usuarios\n");
        printf("3 - Editar Usuario\n");
        printf("4 - Excluir Usuario\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &ou);
        getchar();

        switch (ou) {
            case 1:
                cadastrarUser();
                break;

            case 2:
                listarUsers();
                break;

            case 3:
                editarUser();
                break;

            case 4:
                excluirUser();
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (ou != 0);
            } break;

            case 2: {
                int oc;
                do {
                    printf("\n--- GERENCIAR CLIENTES ---\n");
                    printf("1 - Cadastrar Cliente\n");
                    printf("2 - Listar Clientes\n");
                    printf("0 - Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &oc);
                    getchar();

                    if (oc == 1) cadastrarCliente();
                    else if (oc == 2) listarClientes();

                } while (oc != 0);
            } break;

            case 3: {
                int op;
                do {
                    printf("\n--- GERENCIAR PIZZAS ---\n");
                    printf("1 - Cadastrar Pizza\n");
                    printf("2 - Listar Pizzas\n");
                    printf("3 - Editar Pizza\n");
                    printf("4 - Excluir Pizza\n");
                    printf("0 - Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &op);
                    getchar();

                    switch (op) {
                        case 1: cadastrarPizza(); break;
                        case 2: listarPizzas(); break;
                        case 3: editarPizza(); break;
                        case 4: excluirPizza(); break;
                    }

                } while (op != 0);
            } break;

            case 4: {
                int op;
                do {
                    printf("\n--- GERENCIAR PEDIDOS ---\n");
                    printf("1 - Fazer Pedido\n");
                    printf("2 - Listar Pedidos\n");
                    printf("3 - Editar Pedido\n");
                    printf("4 - Excluir Pedido\n");
                    printf("0 - Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &op);
                    getchar();

                    switch (op) {
                        case 1: cadastrarPedido(); break;
                        case 2: listarPedidos(); break;
                        case 3: editarPedido(); break;
                        case 4: excluirPedido(); break;
                    }

                } while (op != 0);
            } break;

            case 5:
                gerarRelatorios();
                break;

            case 0:
                printf("Voltando ao menu anterior...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opc != 0);
}

void gerarRelatorios() {
    printf("\n===== RELATORIOS =====\n");
    printf("Total de Usuarios: %d\n", totalUsers);
    printf("Total de Clientes: %d\n", totalClientes);
    printf("Total de Pizzas: %d\n", totalPizzas);
    printf("Total de Pedidos: %d\n", totalPedidos);
}