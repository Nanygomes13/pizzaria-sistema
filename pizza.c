#include <stdio.h>
#include <string.h>
#include "pizza.h"
#include "dados.h"    
#include "structs.h"  
#include "menu.h" 

void cadastrarPizza() {
    Pizza p;

    p.id = gerarIdPizza();

    printf("\n\n Cadastro de Pizza \n");

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
    printf("\n CARDAPIO \n");
    for (int i = 0; i < totalPizzas; i++) {
        printf("%d - %s (R$ %.2f)\n", pizzas[i].id, pizzas[i].sabor, pizzas[i].preco);
    }
}

void listarPizzas() {
    if (totalPizzas == 0) {
        printf("\nNenhuma pizza cadastrada.\n");
        return;
    }

    printf("\n===== LISTA DE PIZZAS =====\n");
    for (int i = 0; i < totalPizzas; i++) {
        printf("ID: %d | Sabor: %s | Preco: R$ %.2f\n",
               pizzas[i].id, pizzas[i].sabor, pizzas[i].preco);
    }
}

void editarPizza() {
    int id;
    printf("Digite o ID da pizza que deseja editar: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < totalPizzas; i++) {
        if (pizzas[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Pizza nao encontrada.\n");
        return;
    }

    printf("Novo sabor: ");
    fgets(pizzas[pos].sabor, sizeof(pizzas[pos].sabor), stdin);
    pizzas[pos].sabor[strcspn(pizzas[pos].sabor, "\n")] = 0;

    printf("Novo preco: ");
    scanf("%f", &pizzas[pos].preco);
    getchar();

    printf("Pizza atualizada com sucesso!\n");
}

void excluirPizza() {
    int id;
    printf("Digite o ID da pizza que deseja excluir: ");
    scanf("%d", &id);
    getchar();

    int pos = -1;
    for (int i = 0; i < totalPizzas; i++) {
        if (pizzas[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Pizza nao encontrada.\n");
        return;
    }

    for (int i = pos; i < totalPizzas - 1; i++) {
        pizzas[i] = pizzas[i + 1];
    }

    totalPizzas--;
    printf("Pizza removida com sucesso.\n");
}
