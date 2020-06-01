//
//  main.c
//  trabalhofinal
//
//  Created by IAm TheSenate on 19/01/2020.
//  Copyright © 2020 IAm TheSenate. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CLI 10

typedef struct
{
    int cod[3];
    char nome[40];
    char morada[40];
    char numero[20];
}tcliente;

tcliente Clientes[CLI];

int get_opcao(int *ClienteEl){
    char *campo;
    campo = (char*)malloc(100 * sizeof(char));
    int i=0;
    int alg_ver=0;
    int breaker=0;

    while(breaker==0){
        printf("\nEscolha um cliente registado:\n(Prima 'r' para regressar ao menu...)\n");
        fgets(campo, 256, stdin);
        strtok(campo, "\n");
        //volta ao menu caso desejado pelo utilizador
        if (campo[0]=='r'){
            *ClienteEl=-1;
            breaker=1;
            break;
        }
        //tem 2 char ou menos
        if (strlen(campo)<3){
            //determina o verificador
            for (i=0;i<2;++i){
                if (campo[i]>=48 && campo[i]<=57){
                    ++alg_ver;
                }
            }
        //consoante o verificador; escalavel com nest e barra no ultimo aceitavel ver de cliente disp no final
            //caso dois algarismos
            if(strlen(campo)==2 && alg_ver==2 && campo[0]==49 && campo[1]==48){
                *ClienteEl=10;
                if(Clientes[*ClienteEl-1].nome[0]!='\0'){
                    breaker=1;
                }
                else{
                    printf("O cliente nao existe");
                }
            }
            //caso 1 algarismo
            else if (strlen(campo)==1 && campo[0]>=48 && campo[0]<=57){
                *ClienteEl=campo[0]-48;
                if(Clientes[*ClienteEl-1].nome[0]!='\0'){
                    breaker=1;
                }
                else{
                    printf("O cliente nao existe");
                }
            }
            else{
                printf("O cliente nao existe");
            }
        }
        else{
            printf("O cliente nao existe");
        }
    }
    free(campo);
    return 0;
}

int imprime_menu(void){
    printf("\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    printf("\t\t<<<ESCOLHA UMA DAS SEGUINTES OPCOES>>>\n\n");
    printf("\t\t(1)──────────────────═════════════>LISTAR Clientes\n");
    printf("\t\t(2)──────────────────>CRIAR um Cliente\n");
    printf("\t\t(3)─────────────────>EDITAR um Cliente\n");
    printf("\t\t(4)───────────────>ELIMINAR um Cliente\n");
    printf("\t\t(5)──────────────────────────────>SAIR\n\n");
    printf("\t\tESCOLHA->");
    return 0;
}

tcliente abrir_popular(tcliente *Clientes){
    FILE *fp;
    char ch;
    int i=0;
    int j=0;

    fp=fopen("clientes.txt","r");

    if (fp==NULL){
        printf("\nSe queres teclar, mas não tens par, chama o Antonio, chama o Antonio...\n\n");
        exit(0);
    }

    ch=fgetc(fp);

    while(ch!=EOF)
    {
        while (ch!=';')
        {
            Clientes[i].cod[j]=ch;
            ch=fgetc(fp);
            ++j;
        }
        j=0;
        ch=fgetc(fp);
        while (ch!=';')
        {
            Clientes[i].nome[j]=ch;
            ch=fgetc(fp);
            ++j;
        }
        j=0;
        ch=fgetc(fp);
        while (ch!=';')
        {
            Clientes[i].morada[j]=ch;
            ch=fgetc(fp);
            ++j;
        }
        j=0;
        ch=fgetc(fp);
        while (ch!=EOF && ch!='\n')
        {
            Clientes[i].numero[j]=ch;
            ch=fgetc(fp);
            ++j;
        }
        ch=fgetc(fp);
        j=0;
        ++i;
    }
    return *Clientes;
}

int abrir_popular_backup(tcliente *Clientes) {
    FILE *fp;
    char *linha;
    linha = (char*)malloc(300 * sizeof(char));
    char *token;
    int i=0,j=0;
    char delimitador[]="\n\r;";

    fp=fopen("clientes.txt","r");

    //caso o ficheiro não exista
    if (fp==NULL){
        printf("\nSe queres teclar, mas não tens par, chama o Antonio, chama o Antonio...\n\n");
        exit(0);
    }

    //popula a string
    for (i=0;i<CLI;++i){
        token=fgets(linha, 1000, fp);

        token=strtok(token, delimitador);
        j=0;
        while(token[j]!='\0'){
            Clientes[i].cod[j]=token[j];
            ++j;
        }

        token=strtok(NULL, delimitador);
        if (token!=NULL){
            strcpy(Clientes[i].nome, token);
        }

        token=strtok(NULL, delimitador);
        if (token!=NULL){
            strcpy(Clientes[i].morada, token);
        }

        token=strtok(NULL, delimitador);
        if (token!=NULL){
            strcpy(Clientes[i].numero, token);
        }
    }
    free(linha);
    return 0;
}

int linha_de_separacao(tcliente *Clientes, int *lin, int *car, int *tot_car_cod, int *tot_car_nome, int *tot_car_morada, int *tot_car_contacto){
    int i=0;
    printf("├");
    for (i=0;i<*tot_car_cod+1;++i){
        printf("─");
    }
    printf("┼");
    for (i=0;i<*tot_car_nome;++i){
        printf("─");
    }
    printf("┼");
    for (i=0;i<*tot_car_morada;++i){
        printf("─");
    }
    printf("┼");
    for (i=0;i<*tot_car_contacto;++i){
        printf("─");
    }
    printf("┤\n");
    return 0;
}

int listar_cliente(tcliente *Clientes){

    int k=0, ultima_linha=0, i=0,largura=0;
    //tamanho da tabela dinamico // em desenvolvimento // a implementar na versao 2.0
    int lin=0, car=0,tot_car_cod=0, tot_car_nome=0, tot_car_morada=0, tot_car_contacto=0;
    char espaco[]=" ";

    for (lin=0;lin<10;++lin){
        while (Clientes[lin].cod[car]!='\0'){
            ++car;
        }
        if(car>tot_car_cod){
            tot_car_cod=car;
        }
        car=0;
        while (Clientes[lin].nome[car]!='\0'){
            ++car;
        }
        if(car>tot_car_nome){
            tot_car_nome=car;
        }
        car=0;
        while ((Clientes[lin].morada[car]!='\0')){
            ++car;
        }
        if(car>tot_car_morada){
            tot_car_morada=car;
        }
        car=0;
        while ((Clientes[lin].numero[car]!='\0')){
            ++car;
        }
        if(car>tot_car_contacto){
            tot_car_contacto=car;
        }
        car=0;
    }

    //ultima linha preenchida (k)
    for (k=0;k<10;++k){
        if (Clientes[k].nome[0]!='\0'){
            ultima_linha=k;
        }
    }

    //imprime tabela consoante o numero de clientes
    largura=tot_car_cod+tot_car_nome+tot_car_morada+tot_car_contacto+4;
    //linha superior da tabela
    printf("\n");
    printf("┌");
    for (i=0;i<tot_car_cod+1;++i){
        printf("─");
    }
    printf("┬");
    for (i=0;i<tot_car_nome;++i){
        printf("─");
    }
    printf("┬");
    for (i=0;i<tot_car_morada;++i){
        printf("─");
    }
    printf("┬");
    for (i=0;i<tot_car_contacto;++i){
        printf("─");
    }
    printf("┐\n");
    //topo da tabela
    printf("│Nº │%*s",tot_car_cod,espaco+1);
    printf("%*sNome│",tot_car_nome-6,espaco);
    printf("%*sMorada│",tot_car_morada-6,espaco);
    printf("%*sContacto│\n",tot_car_contacto-10, espaco);
    //linha de separacao
    linha_de_separacao(Clientes, &lin, &car, &tot_car_cod, &tot_car_nome, &tot_car_morada, &tot_car_contacto);
        //segunda linha
    linha_de_separacao(Clientes, &lin, &car, &tot_car_cod, &tot_car_nome, &tot_car_morada, &tot_car_contacto);
    //podia imprimir cod em for com escalabilidade, bem como altura da celula dinamica| fica para a 2.0
    for (k=0;k<ultima_linha;++k){
        if (Clientes[k].nome[0]!='\0'){
            //cliente
            printf("│%*d│%*s│%*s│%*s│\n", tot_car_cod+1, *Clientes[k].cod-48, tot_car_nome, Clientes[k].nome,tot_car_morada,  Clientes[k].morada, tot_car_contacto, Clientes[k].numero);
            //linha de separacao
            linha_de_separacao(Clientes, &lin, &car, &tot_car_cod, &tot_car_nome, &tot_car_morada, &tot_car_contacto);
        }
    }
    // impressao do cod da ultima linha, consoante o cod do cliente, substituivel por for
    if (k==9){
        printf("│%*c%c│%*s│%*s│%*s│\n", tot_car_cod, Clientes[ultima_linha].cod[0], Clientes[ultima_linha].cod[1], tot_car_nome, Clientes[k].nome,tot_car_morada,  Clientes[k].morada, tot_car_contacto, Clientes[k].numero);
    }
    else{
        printf("│%*d│%*s│%*s│%*s│\n", tot_car_cod+1, *Clientes[k].cod-48, tot_car_nome, Clientes[k].nome,tot_car_morada,  Clientes[k].morada, tot_car_contacto, Clientes[k].numero);
        }
    //ultima linha
    printf("└");
    for (i=0;i<tot_car_cod+1;++i){
        printf("─");
    }
    printf("┴");
    for (i=0;i<tot_car_nome;++i){
        printf("─");
    }
    printf("┴");
    for (i=0;i<tot_car_morada;++i){
        printf("─");
    }
    printf("┴");
    for (i=0;i<tot_car_contacto;++i){
        printf("─");
    }
    printf("┘\n");

    printf("\n\n");
    return 0;
}

int adicionar_cliente(tcliente *Clientes){

    //procura cliente livre
    int k=0;
    char nome[80],morada[80],numero[40],espaco[]=" ";

    //e verifica vaga na base de dados
    while (Clientes[k].nome[0]!='\0'){
        ++k;
        if (k==10){
            printf("\n\n--->A base de dados está cheia. Escolher outra opção.<---\n\n");
            return 0;
        }
    }

    //adquire e guarda cliente
    printf("\nQual é o nome do novo Cliente?");
    fgets(nome, 256, stdin);
    strtok(nome, "\n");
    //acautelar enter e branco
    while (nome[0]=='\n' || nome[0]==' '){
        printf("Não são permitidos nomes em branco\n");
        printf("Qual é o nome do novo Cliente?");
        fgets(nome, 256, stdin);
        strtok(nome, "\n");
    }
    strcpy(Clientes[k].nome, nome);
    printf("Qual é a morada do novo Cliente?");
    fgets(morada, 1024, stdin);
    strtok(morada, "\n");
    //acautelar enter
    if (morada[0]=='\n'){
        morada[0]='\0';
    }
    strcpy(Clientes[k].morada, morada);
    printf("Qual é o contacto do novo Cliente?");
    fgets(numero, 256, stdin);
    strtok(numero, "\n");
    //acautelar enter
    if (numero[0]=='\n'){
        numero[0]='\0';
    }
    strcpy(Clientes[k].numero, numero);


        //caso nao seja introduzido um nome de cliente
    if(Clientes[k].nome[0]=='\0'){
        printf("\n%20sNENHUM CLIENTE ADICIONADO!!!",espaco);
    }
    else{
        //imprime confirmação de cliente adicionado
        printf("\n\\\\\\\\\\\\\\\\\\\\\\Contacto Novo Criado\n");
        if(k==9){
            printf("Numero de Cliente:_%c%c\nNome:______________%s\nMorada:____________%s\nContacto:__________%s\n", Clientes[k].cod[0], Clientes[k].cod[1], Clientes[k].nome, Clientes[k].morada, Clientes[k].numero);
        }
        else{
            printf("Numero de Cliente:_%c\nNome:______________%s\nMorada:____________%s\nContacto:__________%s\n\n", Clientes[k].cod[0], Clientes[k].nome, Clientes[k].morada, Clientes[k].numero);
        }
    }

    return 0;
}

int imprime_confirma(tcliente *Clientes, int *clienteEd){
    if(*clienteEd>9){
        printf("Numero de Cliente:_%c%c\nNome:______________%s\nMorada:____________%s\nContacto:__________%s\n", Clientes[*clienteEd-1].cod[0], Clientes[*clienteEd-1].cod[1], Clientes[*clienteEd-1].nome, Clientes[*clienteEd-1].morada, Clientes[*clienteEd-1].numero);
    }
    else{
        printf("Numero de Cliente:_%c\nNome:______________%s\nMorada:____________%s\nContacto:__________%s\n", Clientes[*clienteEd-1].cod[0], Clientes[*clienteEd-1].nome, Clientes[*clienteEd-1].morada, Clientes[*clienteEd-1].numero);
    }
    return 0;
}

int editar_cliente(tcliente *Clientes){
    char nome[80],morada[80],numero[40];
    int clienteEd;
    char escolha_edi[10];

    get_opcao(&clienteEd);

    if(clienteEd!=-1){
        //editar todos os campos || um a um
        printf("\nPretende editar um campo ou todos os campos?\n");
        printf("1-Todos os campos\n2-Campo especifico");
        fgets(escolha_edi, 256, stdin);
        strtok(escolha_edi, "\n");
        while(strlen(escolha_edi)!=1 && (escolha_edi[0]!='1' || escolha_edi[0]!='2')){
            printf("\n\nEscolha apenas o numero inteiro (n)- associado a opçao...");
            fgets(escolha_edi, 256, stdin);
            strtok(escolha_edi, "\n");
        }

        //todos os campos
        if (escolha_edi[0]=='1'){
            printf("Qual é o novo nome do Cliente?");
            fgets(nome, 256, stdin);
            strtok(nome, "\n");
            //acautelar enter e branco
            while (nome[0]=='\n' || nome[0]==' '){
                printf("Não são permitidos nomes em branco\n");
                printf("Qual é o nome do novo Cliente?");
                fgets(nome, 256, stdin);
                strtok(nome, "\n");
            }
            strcpy(Clientes[clienteEd-1].nome, nome);
            printf("Qual é a nova morada do Cliente?");
            fgets(morada, 256, stdin);
            strtok(morada, "\n");
            //acautelar enter
            if (morada[0]=='\n'){
                morada[0]='\0';
            }
            strcpy(Clientes[clienteEd-1].morada, morada);
            printf("Qual é o novo contacto do Cliente?");
            fgets(numero, 256, stdin);
            strtok(numero, "\n");
            //acautelar enter
            if (numero[0]=='\n'){
                numero[0]='\0';
            }
            strcpy(Clientes[clienteEd-1].numero, numero);
            //imprime coonfirmação
            printf("\\\\\\\\\\\\\\\\\\\\\\Cliente Editado\n");
            imprime_confirma(Clientes,&clienteEd);
        }
        //um em especifico
        else if (escolha_edi[0]=='2'){
            printf("\nQual o campo que pretende editar?\n");
            printf("1-Nome\n2-Morada\n3-Contacto");
            fgets(escolha_edi, 256, stdin);
            strtok(escolha_edi, "\n");
            while( strlen(escolha_edi)!=1 || (escolha_edi[0]!='1' && escolha_edi[0]!='2' && escolha_edi[0]!='3')){
                printf("\n\nEscolha apenas o numero inteiro (n)- associado a opçao...\n");
                printf("1-Nome\n2-Morada\n3-Contacto");
                fgets(escolha_edi, 256, stdin);
                strtok(escolha_edi, "\n");
            }
            switch (escolha_edi[0]){
                case '1':
                    printf("Qual é o nome do novo Cliente?");
                    fgets(nome, 256, stdin);
                    strtok(nome, "\n");
                    //acautelar enter e branco
                    while (nome[0]=='\n' || nome[0]==' '){
                        printf("Não são permitidos nomes em branco\n");
                        printf("Qual é o nome do novo Cliente?");
                        fgets(nome, 256, stdin);
                        strtok(nome, "\n");
                    }
                    strcpy(Clientes[clienteEd-1].nome, nome);
                    printf("\\\\\\\\\\\\\\\\\\\\\\Nome Editado\n");
                    imprime_confirma(Clientes,&clienteEd);
                    break;
                case '2':
                    printf("Qual é a morada do novo Cliente?");
                    fgets(morada, 256, stdin);
                    strtok(morada, "\n");
                    //acautelar enter
                    if (morada[0]=='\n'){
                        morada[0]='\0';
                    }
                    strcpy(Clientes[clienteEd-1].morada, morada);
                    printf("\\\\\\\\\\\\\\\\\\\\\\Morada Editada\n");
                    imprime_confirma(Clientes,&clienteEd);
                    break;
                case '3':
                    printf("Qual é o contacto do novo Cliente?");
                    fgets(numero, 256, stdin);
                    strtok(numero, "\n");
                    //acautelar enter
                    if (numero[0]=='\n'){
                        numero[0]='\0';
                    }
                    strcpy(Clientes[clienteEd-1].numero, numero);
                    printf("\\\\\\\\\\\\\\\\\\\\\\Contacto Editado\n");
                    imprime_confirma(Clientes,&clienteEd);
                    break;
            }
        }
    }
    else{
        return 0;
    }
    return 0;
}

int eliminar_cliente(tcliente *Clientes){
    int clienteEl;
    int clientesre=0;
    int i=0;
    char escolha[100];

    //quantos clientes existem
    for (i=0;i<10;++i){
        if (Clientes[i].nome[0]!='\0'){
            ++clientesre;
        }
    }
    //havendo clientes a eliminar
    if (clientesre!=0){
        // escolha de cliente
        get_opcao(&clienteEl);
        if(clienteEl!=-1){
            //confirma a eliminação
            printf("De certeza que pretende eliminar o cliente:\n");
            imprime_confirma(Clientes, &clienteEl);
            printf("1-Eliminar\n2-Não Eliminar");
            fgets(escolha, 256, stdin);
            strtok(escolha, "\n");
            while(strlen(escolha)!=1 && (escolha[0]!='1' || escolha[0]!='2')){
                printf("\n\nEscolha apenas o numero inteiro (n)- associado a opçao...");
                fgets(escolha, 256, stdin);
                strtok(escolha, "\n");
            }

            // guardar a ediçao de cliente
            if (escolha[0]=='1'){
                Clientes[clienteEl-1].nome[0]='\0';
                Clientes[clienteEl-1].morada[0]='\0';
                Clientes[clienteEl-1].numero[0]='\0';
                //imprime coonfirmação
                printf("\n\t\tO cliente %d FOI eliminado!",clienteEl);
            }
            else if (escolha[0]=='2'){
                printf("\n\t\tO cliente %d NAO foi eliminado!",clienteEl);
            }
        }
        else{
            return 0;
        }
    }
    //se nao houver clientes a eliminar
    else {
        printf("Não ha clientes a eliminar!");
    }
    return 0;
}

int gravar_struct(tcliente *Clientes){
    FILE *fp;
    int i;
    int j=0;
    fp=fopen("clientes.txt","w");

    for (i=0;i<10;++i)
    {
        while (Clientes[i].cod[j]!='\0')
        {
            fputc(Clientes[i].cod[j],fp);
            ++j;
        }
        j=0;
        fputc(';',fp);
        while (j<strlen(Clientes[i].nome))
        {
            fputc(Clientes[i].nome[j],fp);
            ++j;
        }
        j=0;
        fputc(';',fp);
        while (j<strlen(Clientes[i].morada))
        {
            fputc(Clientes[i].morada[j],fp);
            ++j;
        }
        j=0;
        fputc(';',fp);
        while (j<strlen(Clientes[i].numero))
        {
            fputc(Clientes[i].numero[j],fp);
            ++j;
        }
        fputc('\n',fp);
        j=0;
    }
    fclose(fp);
    return 0;
}

int main()
{
    char escolha[2];
    // menu
    printf("\t\t   ######################################\n");
    printf("\t\t  #BEM VINDO AO SEU REGISTO DE CLIENTES#\n");
    printf("\t\t######################################\n\n");
    while (1){
        //imprime menu
        imprime_menu();
        //recepcao de opcao escolhida
        fgets(escolha, 256, stdin);
        strtok(escolha, "\n");
        if (strlen(escolha)<2){
            if(escolha[0]=='1' || escolha[0]=='2' || escolha[0]=='3' || escolha[0]=='4' || escolha[0]=='5'){
                switch(escolha[0]){
                    case '1':
                        //abre o ficheiro e popula
                        abrir_popular_backup(Clientes);
                        //lista os clientes
                        listar_cliente(Clientes);
                        // fecha o ficheiro
                        gravar_struct(Clientes);
                        break;
                    case '2':
                        //abre o ficheiro e popula
                        abrir_popular(Clientes);
                        //adiciona cliente
                        adicionar_cliente(Clientes);
                        // gravar e fechar o ficheiro
                        gravar_struct(Clientes);
                        break;
                    case '3':
                        //abre o ficheiro e popula
                        abrir_popular(Clientes);
                        //edita o cliente
                        editar_cliente(Clientes);
                        // gravar e fechar o ficheiro
                        gravar_struct(Clientes);
                        break;
                    case '4':
                        //abre o ficheiro e popula
                        abrir_popular(Clientes);
                        //elimina o cliente
                        eliminar_cliente(Clientes);
                        // gravar e fechar o ficheiro
                        gravar_struct(Clientes);
                        break;
                    case '5':
                        break;
                }
                if (escolha[0]=='5'){
                    break;
                }
            }
            else{
                printf("\n\nEscolha apenas o numero inteiro n-> associado a opçao...");
            }
        }
        else{
            printf("\n\nEscolha apenas o numero inteiro n-> associado a opçao...");
        }
        printf("\n");
    }
    return 0;
}
