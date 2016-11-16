#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa{
    char nome[50];
    char tel[20];
    char email[30];
    char cidade[20];
    char estado[2];
};

struct Pessoa array[100];
int quant = 0;

void imprimiHeader(){
    printf("\n|======================|");
    printf("\n\n     Hello World!\n");
    printf("   Bem vindo a agenda.\n\n");
    printf("|======================|\n");
}

void lerArquivo(){
    int i;

    FILE * db;
    db = fopen("agenda.db","r");

    for(i = 0; ; i++){

        if(fgets(array[i].nome,51,db) == NULL) break;
        fgets(array[i].tel,21,db);
        fgets(array[i].email,31,db);
        fgets(array[i].cidade,21,db);
        fgets(array[i].estado,3,db);

        quant ++;

    }

    fclose(db);


}

void escreverArquivo(){

    int i;

    FILE * db;
    db = fopen("agenda.db","w");

    for(i = 0; i < 100 ; i++){

        if(!strlen(array[i].nome)) continue;
        fprintf(db,"%s", array[i].nome);
        fprintf(db,"%s", array[i].tel);
        fprintf(db,"%s", array[i].email);
        fprintf(db,"%s", array[i].cidade);
        fprintf(db,"%s", array[i].estado);


    }

    fclose(db);

}

int busca(char *coisa){

    int i;

    for(i = 0; i < 100; i++) {

        if(strcmp(coisa, array[i].nome) == 0){
            return i + 1;
        }

    }

    return 101;

}

int adicionaUsuario(){
    
    system("cls");
    puts("==> Voce esta adicionando um novo usuário...");
    fflush(stdin);

    puts("Insira um nome: ");
    fgets(array[quant].nome, 51, stdin);

    puts("Insira um telefone: ");
    fgets(array[quant].tel, 21, stdin);

    fflush(stdin);

    puts("Insira um email: ");
    fgets(array[quant].email, 31, stdin);

    fflush(stdin);

    puts("Insira um cidade: ");
    fgets(array[quant].cidade, 21, stdin);

    fflush(stdin);

    puts("Insira um estado: ");
    fgets(array[quant].estado, 3, stdin);

    printf("\n Voce cadastrou um usuario com nome: %s\n", array[quant].nome);
    system("PAUSE");
    system("cls");


    quant ++;
    return 1;

}

int removerUsuario(int id){

    strcpy(array[id].nome,"");
    strcpy(array[id].tel,"");
    strcpy(array[id].email,"");
    strcpy(array[id].cidade,"");
    strcpy(array[id].estado,"");

    printf("\nContato deletado com sucesso...\n");
    system("PAUSE");
    system("cls");

    quant --;
    return 1;

}

int alterarUsuario(int id){
    int opcao;

    system("cls");
    printf("\n==> Voce esta alterando o usuario %s", array[id].nome);

    printf("\n\nO que voce deseja alterar?");
    printf("\n\n1) Nome   | 2) Telefone   | 3) Email   | 4) Cidade   | 5) Estado\n\n");

    printf("Opcao: ");
    scanf("%d", &opcao);
    fflush(stdin);

    if(opcao == 1) {

        printf("\n\nDigite o novo nome: ");
        fgets(array[id].nome,51,stdin);

    }else if(opcao == 2){

        printf("\n\nDigite o novo telefone: ");
        fgets(array[id].tel,21,stdin);

    }else if(opcao == 3){

        printf("\n\nDigite o novo email: ");
        fgets(array[id].email,31,stdin);

    }else if(opcao == 4){

        printf("\n\nDigite o nova cidade: ");
        fgets(array[id].cidade,21,stdin);

    }else if(opcao == 5){

        printf("\n\nDigite o novo estado: ");
        fgets(array[id].estado,3,stdin);

    }else {

        printf("\n\n Digite uma opcao valida...");

    }

    printf("Deseja alterar mais algum campo? (1 - SIM | 0 - NAO)");
    scanf("%d", &opcao);

    if(opcao == 1) alterarUsuario(id);
    else {
        system("cls");
        return 1;
    }


}

int buscarUsuario(){

    int escolha;
    char nome[50];
    system("cls");

    puts("==> Voce esta buscando um usuario pelo nome...");
    printf("\n\n  Digite o nome do usuario:  ");

    fflush(stdin);
    fgets(nome, 50, stdin);
    int i = busca(nome) - 1;

    if(i != 100){
        printf("\n               Achamos um usuario...");
        printf("\n Nome: %s", array[i].nome);
        printf(" Telefone: %s", array[i].tel);
        printf(" Email: %s", array[i].email);
        printf(" Cidade: %s", array[i].cidade);
        printf(" Estado: %s\n", array[i].estado);

        
        puts("Deseja alterar, remover esse contato? (2 - ALTERAR | 1 - REMOVER | 0 - VOLTAR AO MENU)");
        scanf("%d", &escolha);

        if(escolha == 2) return alterarUsuario(i);
        else if(escolha == 1) return removerUsuario(i);
        else {

            system("PAUSE");
            system("cls");

            return 1;

        }
        

    }else {
        puts("Nao achamos nada...");

        system("PAUSE");

        return 1;
    }

}

int imprimiMenu(){

    int escolha = 0;

    printf("\n     Escolha uma das opcoes:\n");
    printf("0) Sair do programa\n");
    printf("1) Adicionar contato\n");
    printf("2) Buscar, alterar ou remover um contato\n");

    printf("\n\n Ja escolheu? Digite o numero correspondente: ");

    fflush(stdin);
    scanf("%d", &escolha);

    if (escolha == 0) return 0;
    else if(escolha == 1) return adicionaUsuario();
    else if(escolha == 2) return buscarUsuario();

}

int main(int argc, const char * argv[]){

    lerArquivo();
    imprimiHeader();
    while(imprimiMenu() != 0){}
    escreverArquivo();

    return 0;
}