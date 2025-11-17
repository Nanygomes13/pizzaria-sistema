#ifndef PIZZA_H
#define PIZZA_H

#include "structs.h"
#include "dados.h"

extern Pizza pizzas[100];
extern int totalPizzas;

int gerarIdPizza();
void cadastrarPizza();
void mostrarCardapio();

#endif
