//header guard: evita rodar esse arquivo mais de uma vez

#ifndef STRUCTS_H
#define STRUCTS_H

//nosso código
typedef struct {
    int id;
    char username[40];
    char password[40];
    char role[20]; 
} User;

typedef struct {
    int user_id;
    char nome[60];
    char telefone[30];
} Cliente;

typedef struct {
    int id;
    char sabor[60];
    float preco;
} Pizza;

typedef struct {
    int id;
    int user_id_cliente;
    int pizza_id;
    int quantidade;
    double total;
    long timestamp;
} Pedido;

#endif
// fim do header guard