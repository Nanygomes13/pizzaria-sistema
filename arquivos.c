#include <stdio.h>
#include <string.h>
#include "arquivos.h"
#include "dados.h"
#include "structs.h"

#define LINE_BUF 256

void salvarUsers() {
    FILE *f = fopen("users.txt", "w");
    if (!f) return;

    for (int i = 0; i < totalUsers; i++) {
        fprintf(f, "%d;%s;%s;%s\n",
            users[i].id,
            users[i].username,
            users[i].password,
            users[i].cargo
        );
    }

    fclose(f);
}

void carregarUsers() {
    FILE *f = fopen("users.txt", "r");
    if (!f) return;

    totalUsers = 0;
    while (fscanf(f, "%d;%[^;];%[^;];%[^\n]\n",
                  &users[totalUsers].id,
                  users[totalUsers].username,
                  users[totalUsers].password,
                  users[totalUsers].cargo) == 4) {
        totalUsers++;
    }

    fclose(f);
}

// ========================= CLIENTES =========================

void salvarClientes() {
    FILE *f = fopen("clientes.txt", "w");
    if (!f) return;

    for (int i = 0; i < totalClientes; i++) {
        fprintf(f, "%d;%s;%s;%s\n",
            clientes[i].id,
            clientes[i].nome,
            clientes[i].telefone,
            clientes[i].endereco
        );
    }

    fclose(f);
}

void carregarClientes() {
    FILE *f = fopen("clientes.txt", "r");
    if (!f) return;

    totalClientes = 0;
    while (fscanf(f, "%d;%[^;];%[^;];%[^\n]\n",
                  &clientes[totalClientes].id,
                  clientes[totalClientes].nome,
                  clientes[totalClientes].telefone,
                  clientes[totalClientes].endereco) == 4) {
        totalClientes++;
    }

    fclose(f);
}


void salvarPizzas() {
    FILE *f = fopen("pizzas.txt", "w");
    if (!f) return;

    for (int i = 0; i < totalPizzas; i++) {
        fprintf(f, "%d;%s;%.2f\n",
            pizzas[i].id,
            pizzas[i].sabor,
            pizzas[i].preco
        );
    }

    fclose(f);
}

void carregarPizzas() {
    FILE *f = fopen("pizzas.txt", "r");
    if (!f) return;

    char line[LINE_BUF];
    totalPizzas = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;
        Pizza tmp;
        // espera: id;sabor;preco
        if (sscanf(line, "%d;%59[^;];%f",
                   &tmp.id,
                   tmp.sabor,
                   &tmp.preco) == 3) {
            pizzas[totalPizzas++] = tmp;
            if (totalPizzas >= MAX_PIZZAS) break;
        }
    }

    fclose(f);
}


void salvarPedidos() {
    FILE *f = fopen("pedidos.txt", "w");
    if (!f) return;

    for (int i = 0; i < totalPedidos; i++) {
        fprintf(f, "%d;%d;%d;%d;%.2f;%ld\n",
            pedidos[i].id,
            pedidos[i].user_id_cliente,
            pedidos[i].pizza_id,
            pedidos[i].quantidade,
            pedidos[i].total,
            pedidos[i].timestamp
        );
    }

    fclose(f);
}

void carregarPedidos() {
    FILE *f = fopen("pedidos.txt", "r");
    if (!f) return;

    char line[LINE_BUF];
    totalPedidos = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;
        Pedido tmp;
        if (sscanf(line, "%d;%d;%d;%d;%lf;%ld",
                   &tmp.id,
                   &tmp.user_id_cliente,
                   &tmp.pizza_id,
                   &tmp.quantidade,
                   &tmp.total,
                   &tmp.timestamp) == 6) {
            pedidos[totalPedidos++] = tmp;
            if (totalPedidos >= MAX_PEDIDOS) break;
        }
    }

    fclose(f);
}
