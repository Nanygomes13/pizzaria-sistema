#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "dados.h"
#include "arquivos.h"

void cadastrarCliente() {

    if (totalClientes >= MAX_CLIENTES) {
        printf("\nERRO: limite máximo de clientes atingido!\n");
        return;
    }

    Cliente c;

    printf("\n=== CADASTRO DE CLIENTE ===\n");

    c.id = gerarIdCliente();

    printf("Nome completo: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;

    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = 0;

    printf("Endereço: ");
    fgets(c.endereco, sizeof(c.endereco), stdin);
    c.endereco[strcspn(c.endereco, "\n")] = 0;

    clientes[totalClientes] = c;
    totalClientes++;

    salvarClientes();
    
    printf("\nCliente cadastrado com sucesso! ID: %d\n", c.id);
}

void listarClientes() {
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    printf("\n===== LISTA DE CLIENTES =====\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("ID: %d | Nome: %s | Telefone: %s | Endereco: %s\n",
               clientes[i].id,
               clientes[i].nome,
               clientes[i].telefone,
               clientes[i].endereco);
    }
}