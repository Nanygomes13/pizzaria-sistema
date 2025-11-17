#include <stdio.h>
#include <string.h>
#include "pizza.h"
#include "dados.h"    
#include "structs.h"  
#include "menu.h" 

void cadastrarPizza() {
    Pizza p;

    p.id = gerarIdPizza();

    printf("\n=== Cadastro de Pizza ===\n");

    printf("Sabor da pizza: ");
    fgets(p.sabor, sizeof(p.sabor), stdin);
    p.sabor[strcspn(p.sabor, "\n")] = 0;

    printf("Preco: ");
    scanf("%f", &p.preco);
    getchar(); 

    pizzas[totalPizzas] = p;
    totalPizzas++;

    printf("\nPizza cadastrada com sucesso! ID: %d\n", p.id);
}

void mostrarCardapio() {
    printf("==== CARDÁPIO ====\n");
    for (int i = 0; i < totalPizzas; i++) {
        printf("%d - %s (R$ %.2f)\n", pizzas[i].id, pizzas[i].sabor, pizzas[i].preco);
    }
}