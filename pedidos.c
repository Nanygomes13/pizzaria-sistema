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

        char nomeCliente[40] = "Desconhecido";
        for (int u = 0; u < totalUsers; u++) {
            if (users[u].id == p.user_id_cliente) {
                strncpy(nomeCliente, users[u].username, sizeof(nomeCliente) - 1);
                nomeCliente[sizeof(nomeCliente) - 1] = '\0'; // garante terminação
                break;
            }
        }

        char nomePizza[60] = "Desconhecido";
        float precoPizza = 0.0;
        for (int k = 0; k < totalPizzas; k++) {
            if (pizzas[k].id == p.pizza_id) {
                strncpy(nomePizza, pizzas[k].sabor, sizeof(nomePizza) - 1);
                nomePizza[sizeof(nomePizza) - 1] = '\0';
                precoPizza = pizzas[k].preco;
                break;
            }
        }

        char data[30] = "Desconhecido";
        time_t t = (time_t)p.timestamp;
        struct tm infoTempo;
        if (localtime_r(&t, &infoTempo) != NULL) { // versão thread-safe
            strftime(data, sizeof(data), "%d/%m/%Y %H:%M:%S", &infoTempo);
        }

        printf("\nPedido ID: %d\n", p.id);
        printf("Cliente: %s\n", nomeCliente);
        printf("Pizza: %s\n", nomePizza);
        printf("Quantidade: %d\n", p.quantidade);
        printf("Total: R$ %.2f\n", p.total);
        printf("Data/Hora: %s\n", data);
    }
}
