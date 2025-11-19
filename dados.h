//header guard: evita rodar esse arquivo mais de uma vez

#ifndef DADOS_H
#define DADOS_H

#include "structs.h"

#define MAX_USERS 100
#define MAX_CLIENTES 100
#define MAX_PIZZAS 100
#define MAX_PEDIDOS 200

extern User users[MAX_USERS];
extern Cliente clientes[MAX_CLIENTES];
extern Pizza pizzas[MAX_PIZZAS];
extern Pedido pedidos[MAX_PEDIDOS];

extern int totalUsers;
extern int totalClientes;
extern int totalPizzas;
extern int totalPedidos;

int gerarIdUser();
int gerarIdCliente();
int gerarIdPizza();
int gerarIdPedido();

#endif
// fim do header guard