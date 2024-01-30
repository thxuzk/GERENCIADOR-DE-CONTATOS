#include "contatos.h"

int main(){

    Contato contatos[MAX_CONTATO];
    int numcontatos = 0, escolha;

    do {
        limparTerminal();
        printf(BLUE"\t\t----------GERENCIADOR DE CONTATOS----------\n\n"FIM_COR);
        printf(BLUE"1. Adicionar Contato\n"FIM_COR);
        printf(BLUE"2. Salvar Contatos Adicionados\n"FIM_COR);
        printf(BLUE"3. Exibir Contatos\n"FIM_COR);
        printf(BLUE"4. Carregar Contatos Salvos\n"FIM_COR);
        printf(BLUE"5. Sair\n\n"FIM_COR);
        printf(BLUE"Escolha: "FIM_COR);

        if(scanf("%d", &escolha) != 1){
            printf(RED"\nEscolha invalida. Pressione Enter para selecionar novamente..."FIM_COR);
            getchar();
            getchar();
            limparTerminal();
            continue;
        }

        switch(escolha){
            case 1:
                limparTerminal();
                adicionarContato(contatos, &numcontatos);
                break;
            case 2:
                salvarContatos(contatos, numcontatos);
                printf(GREEN"\nContatos salvos com Sucesso. Pressione Enter para continuar...");
                getchar();
                getchar();
                break;
            case 3:
                limparTerminal();
                exibirContatos(contatos, numcontatos);
                break;
            case 4:
                lerContatos(contatos, &numcontatos);
                break;
            case 5:
                limparTerminal();
                printf(BLUE"\nObrigado por usar nosso programa!\n\n"FIM_COR);
                break;
            default:
                printf(RED"\nEscolha invalida. Pressione Enter para selecionar novamente..."FIM_COR);
                getchar();
                getchar();
                limparTerminal();
        }
    }
    while(escolha != 5);

    return 0;
}