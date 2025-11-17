#include <stdio.h>
#include <string.h>
#include <time.h>

#include "pedidos.h"
#include "structs.h"
#include "dados.h"   

void listarPedidos() {
    if (totalPedidos == 0) {
        printf("\nNenhum pedido realizado ainda.\n");
        return;
    }

    printf("\n======= LISTA DE PEDIDOS =======\n");

    for (int i = 0; i < totalPedidos; i++) {
        Pedido p = pedidos[i];

        char nomeCliente[40];
        strcpy(nomeCliente, "Desconhecido");

        for (int u = 0; u < totalUsers; u++) {
            if (users[u].id == p.user_id_cliente) {
                strcpy(nomeCliente, users[u].username);
                break;
            }
        }

        char nomePizza[60];
        float precoPizza = 0.0;

        for (int k = 0; k < totalPizzas; k++) {
            if (pizzas[k].id == p.pizza_id) {
                strcpy(nomePizza, pizzas[k].sabor);
                precoPizza = pizzas[k].preco;
                break;
            }
        }

        char data[30];
        struct tm *infoTempo = localtime(&p.timestamp);
        strftime(data, 30, "%d/%m/%Y %H:%M:%S", infoTempo);

        printf("\nPedido ID: %d\n", p.id);
        printf("Cliente: %s\n", nomeCliente);
        printf("Pizza: %s\n", nomePizza);
        printf("Quantidade: %d\n", p.quantidade);
        printf("Total: R$ %.2f\n", p.total);
        printf("Data/Hora: %s\n", data);
    }
}
