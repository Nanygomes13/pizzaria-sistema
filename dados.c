//.h --> declara
//.c --> implementa

#include "dados.h"

// Definição dos arrays
User users[MAX_USERS];
Cliente clientes[MAX_CLIENTES];
Pizza pizzas[MAX_PIZZAS];
Pedido pedidos[MAX_PEDIDOS];

// Definição dos contadores
int totalUsers = 0;
int totalClientes = 0;
int totalPizzas = 0;
int totalPedidos = 0;

//Para gerar os IDs automáticamente
int gerarIdUser() { 
    return totalUsers + 1;
}

int gerarIdCliente() {
    return totalClientes + 1;
}

int gerarIdPizza() {
    return totalPizzas + 1;
}

int gerarIdPedido() {
    return totalPedidos + 1;
}
