#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pedidos.h"
#include "arquivos.h"
#include "structs.h"
#include "dados.h"
#include "pizza.h"
#include "clientes.h"

void listarPedidos() {
    if (totalPedidos == 0) {
        printf("\nNenhum pedido realizado ainda.\n");
        return;
    }

    printf("\n======= LISTA DE PEDIDOS =======\n");

    for (int i = 0; i < totalPedidos; i++) {
        Pedido p = pedidos[i];

        char nomeCliente[40] = "Desconhecido";
        for (int u = 0; u < totalClientes; u++) {
            if (clientes[u].id == p.user_id_cliente) {
                strncpy(nomeCliente, clientes[u].nome, sizeof(nomeCliente) - 1);
                nomeCliente[sizeof(nomeCliente) - 1] = '\0';
                break;
            }
        }


        char nomePizza[60] = "Desconhecido";
        float precoPizza = 0.0;
        int encontrou = 0;
        for (int k = 0; k < totalPizzas; k++) {
            if (pizzas[k].id == p.pizza_id) {
                strncpy(nomePizza, pizzas[k].sabor, sizeof(nomePizza) - 1);
                nomePizza[sizeof(nomePizza) - 1] = '\0';
                precoPizza = pizzas[k].preco;
                encontrou = 1;
                break;
            }
        }
        if (!encontrou) {
            printf("Aviso: pizza com ID %d nao encontrada!\n", p.pizza_id);
        }

        char data[30] = "Desconhecido";
        time_t t = (time_t)p.timestamp;
        struct tm *infoTempo = localtime(&t);
        if (infoTempo != NULL) {
            strftime(data, sizeof(data), "%d/%m/%Y %H:%M:%S", infoTempo);
        }

        printf("\nPedido ID: %d\n", p.id);
        printf("Cliente: %s\n", nomeCliente);
        printf("Pizza: %s\n", nomePizza);
        printf("Quantidade: %d\n", p.quantidade);
        printf("Total: R$ %.2f\n", p.total);
        printf("Data/Hora: %s\n", data);
    }
}

void cadastrarPedido() {
    if (totalClientes == 0 || totalPizzas == 0) {
        printf("Nao ha clientes ou pizzas cadastrados.\n");
        return;
    }

    Pedido p;
    p.id = gerarIdPedido();

    listarClientes();
    printf("Digite o ID do cliente: ");
    scanf("%d", &p.user_id_cliente);
    getchar();

    mostrarCardapio();
    printf("Digite o ID da pizza: ");
    scanf("%d", &p.pizza_id);
    getchar();

    printf("Digite a quantidade: ");
    scanf("%d", &p.quantidade);
    getchar();

    p.total = 0.0;
    for (int i = 0; i < totalPizzas; i++) {
        if (pizzas[i].id == p.pizza_id) {
            p.total = pizzas[i].preco * p.quantidade;
            break;
        }
    }

    p.timestamp = time(NULL);

    pedidos[totalPedidos] = p;
    totalPedidos++;

    salvarPedidos();

    printf("Pedido cadastrado com sucesso! ID: %d\n", p.id);
}

void editarPedido() {
    int id;
    printf("Digite o ID do pedido que deseja editar: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Pedido nao encontrado.\n");
        return;
    }

    printf("Nova quantidade: ");
    scanf("%d", &pedidos[pos].quantidade);
    getchar();

    for (int i = 0; i < totalPizzas; i++) {
        if (pizzas[i].id == pedidos[pos].pizza_id) {
            pedidos[pos].total = pizzas[i].preco * pedidos[pos].quantidade;
            break;
        }
    }

    pedidos[pos].timestamp = time(NULL);

    salvarPedidos();

    printf("Pedido atualizado com sucesso.\n");
}

void excluirPedido() {
    int id;
    printf("Digite o ID do pedido que deseja excluir: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Pedido nao encontrado.\n");
        return;
    }

    for (int i = pos; i < totalPedidos - 1; i++) {
        pedidos[i] = pedidos[i + 1];
    }

    totalPedidos--;

    salvarPedidos();

    printf("Pedido removido com sucesso.\n");
}
