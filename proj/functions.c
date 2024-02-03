#include "contatos.h"

void limparTerminal(){
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int verificarNumero(char *numero){

    if(numero == NULL || strlen(numero) != 17){
        return 0;
    }

    int i;

    for(i=0;i<17;i++){

        if((i == 0 && numero[i] == '+') || ((i == 1 || i == 2) && numero[i] == '5') ||
        ((i == 3 || i == 6) && numero[i] == ' ') || (i == 12 && numero[i] == '-') ||
        (numero[i] >= '0' && numero[i] <= '9')) {
        continue;
        }
        else{
            return 0;
        }
    }

    return 1;
}

int verificarEmail(char *email){

    if(email == NULL || strlen(email) < 11){
        return 0;
    }

    int tamanho = strlen(email);

    int i;

    for (i=0; i<10; i++){

        if(email[tamanho - 10 + i] != "@gmail.com"[i] && "@hotmail.com" && "@outlook.com"){
            return 0;
        }
    }

    return 1;
}

void esperarEntrada(){
    limparBuffer();
    printf(YELLOW"\nPressione Enter para continuar..."FIM_COR);
    getchar();
}

void adicionarContato(Contato contatos[MAX_CONTATO], int *numcontatos){

    if(*numcontatos < MAX_CONTATO){

        limparTerminal();
        printf(WHITE"Nome: "FIM_COR);
        limparBuffer();
        scanf("%[^\n]", contatos[*numcontatos].nome);
        limparBuffer();

        printf(WHITE"Telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
        scanf("%[^\n]", contatos[*numcontatos].telefone);
        limparBuffer();

        while(verificarNumero(contatos[*numcontatos].telefone) != 1){

            limparTerminal();
            printf(RED"\nNumero invalido. Pressione Enter para digitar novamente..."FIM_COR);
            getchar();
            limparTerminal();
            printf(WHITE"Nome: "FIM_COR);
            printf("%s\n", contatos[*numcontatos].nome);
            printf(WHITE"Telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
            scanf("%[^\n]", contatos[*numcontatos].telefone);
            limparBuffer();
        }

        printf(WHITE"Email: "FIM_COR);
        scanf("%s", contatos[*numcontatos].email);
        limparBuffer();

        while(verificarEmail(contatos[*numcontatos].email) != 1){

            limparTerminal();
            printf(RED"\nEmail invalido. Pressione Enter para digitar novamente..."FIM_COR);
            getchar();
            limparTerminal();
            printf(WHITE"Nome: "FIM_COR);
            printf("%s\n", contatos[*numcontatos].nome);
            printf(WHITE"Telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
            printf("%s\n", contatos[*numcontatos].telefone);
            printf(WHITE"Email: "FIM_COR);
            scanf("%s", contatos[*numcontatos].email);
            limparBuffer();
        }

        limparTerminal();
        printf(WHITE"Nome: "FIM_COR);
        printf("%s\n", contatos[*numcontatos].nome);
        printf(WHITE"Telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
        printf("%s\n", contatos[*numcontatos].telefone);
        printf(WHITE"Email: "FIM_COR);
        printf("%s\n", contatos[*numcontatos].email);
        (*numcontatos)++;
        printf(GREEN"\nContato adicionado com sucesso!"FIM_COR);
        getchar();
    }
    else{

        printf(RED"Limite maximo de contatos atingido.\n"FIM_COR);
        esperarEntrada();
    }
}

void salvarContatos(Contato contatos[MAX_CONTATO], int numcontatos){

    FILE *arquivo;
    arquivo = fopen("contatos.txt", "a");

    if(arquivo == NULL){

        printf(RED"\nErro ao salvar o arquivo. Pressione Enter para continuar...\n");
        getchar();
        getchar();
        return;
    }

    int i;

    for(i=0;i<numcontatos;i++){

        fprintf(arquivo, "Nome: %s\n", contatos[i].nome);
        fprintf(arquivo, "Telefone: %s\n", contatos[i].telefone);
        fprintf(arquivo, "Email: %s\n", contatos[i].email);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void lerContatos(Contato contatos[MAX_CONTATO], int *numcontatos){

    FILE *arquivo;
    char linha[10000];
    int indice = 0;
    arquivo = fopen("contatos.txt", "r");

    if(arquivo == NULL){

        printf(RED"\nErro ao abrir o arquivo. Pressione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo) != NULL){

        if(strstr(linha, "Nome: ") != NULL){

            sscanf(linha, "Nome: %[^\n]", contatos[indice].nome);
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Telefone: %[^\n]", contatos[indice].telefone);
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "Email: %[^\n]", contatos[indice].email);
            indice++;
            (*numcontatos)++;
        }
    }

    fclose(arquivo);

    printf(GREEN"\nContatos carregados com sucesso. Pressione Enter para continuar...");
    getchar();
    getchar();
}

void exibirContatos(Contato contatos[], int numcontatos){

    if(numcontatos == 0){

        limparTerminal();
        printf(RED"\nNenhum contato encontrado. Pressione Enter para voltar..."FIM_COR);
        getchar();
        getchar();
    }
    else{

        printf(YELLOW"\nLista de Contatos:\n"FIM_COR);

        int i;

        for(i=0;i<numcontatos;i++){

            printf(YELLOW"\nNome: "FIM_COR);
            printf("%s\n", contatos[i].nome);
            printf(YELLOW"Telefone: "FIM_COR);
            printf("%s\n", contatos[i].telefone);
            printf(YELLOW"Email: "FIM_COR);
            printf("%s\n", contatos[i].email);
        }

        esperarEntrada();
    }
}

void editarContato(Contato contatos[], int numcontatos) {
    char nome[51];
    int encontrado = 0, i;

    limparTerminal();
    printf(WHITE"Digite o nome do contato que deseja editar: "FIM_COR);
    limparBuffer();
    scanf("%[^\n]", nome);

    for (i=0;i<numcontatos;i++) {
        if (strcmp(nome, contatos[i].nome) == 0) {
            limparTerminal();
            printf(YELLOW"\nContato encontrado:\n"FIM_COR);
            printf(YELLOW"Nome: "FIM_COR"%s\n", contatos[i].nome);
            printf(YELLOW"Telefone: "FIM_COR"%s\n", contatos[i].telefone);
            printf(YELLOW"Email: "FIM_COR"%s\n", contatos[i].email);

            printf(WHITE"\nDigite o novo nome: "FIM_COR);
            limparBuffer();
            scanf("%[^\n]", contatos[i].nome);

            printf(WHITE"Digite o novo telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
            limparBuffer();
            scanf("%[^\n]", contatos[i].telefone);

            while (verificarNumero(contatos[i].telefone) != 1) {
                limparTerminal();
                printf(RED"\nNúmero inválido. Pressione Enter para digitar novamente..."FIM_COR);
                getchar();
                limparTerminal();
                printf(WHITE"Nome: "FIM_COR);
                printf("%s\n", contatos[i].nome);
                printf(WHITE"Telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
                scanf("%[^\n]", contatos[i].telefone);
                limparBuffer();
            }

            limparBuffer();

            printf(WHITE"Digite o novo email: "FIM_COR);
            scanf("%s", contatos[i].email);
            getchar();

            while (verificarEmail(contatos[i].email) != 1) {
                limparTerminal();
                printf(RED"\nEmail inválido. Pressione Enter para digitar novamente..."FIM_COR);
                getchar();
                limparTerminal();
                printf(WHITE"Nome: "FIM_COR);
                printf("%s\n", contatos[i].nome);
                printf(WHITE"Telefone (formato +55 xx xxxx-xxxx): "FIM_COR);
                printf("%s\n", contatos[i].telefone);
                printf(WHITE"Email: "FIM_COR);
                scanf("%s", contatos[i].email);
                limparBuffer();
            }

            limparBuffer();

            printf(GREEN"\nContato editado com sucesso! Pressione enter para continuar..."FIM_COR);
            getchar();
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        limparTerminal();
        printf(RED"\nContato não encontrado. Pressione Enter para voltar..."FIM_COR);
        getchar();
    }
}
