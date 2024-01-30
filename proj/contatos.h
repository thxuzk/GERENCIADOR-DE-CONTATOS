#ifndef _CONTATOS_H_
#define _CONTATOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTATO 10000

struct Contato{
    char nome[50];
    char telefone[50];
    char email[50];
};

typedef struct Contato Contato;

#define GREEN "\e[32m"
#define RED "\e[31m"
#define YELLOW "\e[33m"
#define WHITE "\e[37m"
#define BLUE "\e[34m"
#define FIM_COR "\e[0m"

void limparTerminal();
void limparBuffer();
int verificarNumero(char *numero);
int verificarEmail(char *email);
void esperarEntrada();
void adicionarContato(Contato contatos[MAX_CONTATO], int *numcontatos);
void salvarContatos(Contato contatos[MAX_CONTATO], int numcontatos);
void lerContatos(Contato contatos[MAX_CONTATO], int *numcontatos);
void exibirContatos(Contato contatos[], int numcontatos);

#endif