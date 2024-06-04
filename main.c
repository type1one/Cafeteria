/*---------------------- Bibliotecas ----------------------*/
#include <stdio.h> // Biblioteca padrão de entrada e saída
#include <stdlib.h> // Biblioteca padrão do sistema
#include <locale.h> // Biblioteca para definir a localização
#include <string.h> // Biblioteca para manipulação de strings
#include <time.h> // Biblioteca para manipulação de tempo
#include <unistd.h> // Biblioteca para a função sleep
#ifdef _WIN32 /* Verifica se o sistema operacional é Windows */
#include <windows.h> // Para Sleep() no Windows
#endif

/*---------------------- VARIAVEIS GLOBAis  ----------------------*/

int numContas = 1; // Armazena o número atual de contas
int operador_conta = 1; // Operador de contas

// Definindo a estrutura para uma conta de usuário
struct Conta {
    char usuario[50]; // Nome de usuário
    char senha[30];   // Senha
};

struct Conta contas[100]; // Array para armazenar as contas de usuário

// Estrutura que armazena a quantidade de itens
typedef struct { // Definindo a estrutura para um item
    char NomeProduto[30]; // Nome do produto
    float Valor; // Valor do produto
    int quantidade;  // Quantidade do produto
} Item; // Nome da estrutura
Item produtos[9]; // Array para armazenar os produtos

/*------------------------  -------------------------------*/

void loginCliente(); // Declaração da função de login
void registrarConta(struct Conta contas[], int *numContas); // Declaração da função de registro
void acessarConta(struct Conta contas[], int numContas); // Declaração da função de acesso
void esqueceuSenha(struct Conta contas[], int numContas); // Declaração da função de recuperação de senha
void salvarConta(struct Conta conta); // Declaração da função de salvar conta
void inicializandoProdutos(); // Declaração da função de inicialização de produtos
void menusdeAlimentacao(); // Declaração da função de alimentação
void feedback(); // Declaração da função de feedback
void metodoPagamento(); // Declaração da função de pagamento
int verificarUsuarioExistente(char usuario[], int numContas);  // Declaração da função de verificação de usuário
int verificarUsuarioArquivo(char usuario[]); // Declaração da função de verificação de usuário no arquivo
int carregarContas(struct Conta contas[], int *numContas); // Declaração da função de carregamento de contas
void mostrarCarregamento(); // Declaração da função de carregamento
void gerarAquivoPodutos(); // Declaração da função de geração de arquivo de produtos
void consultarProdutos(); // Declaração da função de consulta de produtos
void loginAdmin(); // Declaração da função de login do administrador


#define RED     "\033[31m" // Definindo a cor vermelha
#define GREEN   "\033[32m"  // Definindo a cor verde
#define YELLOW  "\033[33m" // Definindo a cor amarela
#define BLUE    "\033[34m" // Definindo a cor azul
#define MAGENTA "\033[35m" // Definindo a cor magenta
#define CYAN    "\033[36m" // Definindo a cor ciano
#define RESET   "\033[0m" // Definindo a cor padrão

int main() { // Função principal
    strcpy(contas[0].usuario, "ADMIN"); // Definindo o nome de usuário e senha do administrador
    strcpy(contas[0].senha, "123+"); // Definindo o nome de usuário e senha do administrador
    mostrarCarregamento(); // Chama a função de carregamento
}
/* Função de Carregamento */
void mostrarCarregamento() {  // Função de carregamento
    int i, j; // Variáveis de controle
    printf("\033[H\033[J"); // Limpa a tela

    printf(GREEN "\n\n Carregando: \n\n" RESET); // Imprime a mensagem de carregamento

    struct timespec ts; // Estrutura de tempo
    ts.tv_sec = 0; // Segundos
    ts.tv_nsec = 1;     // Nanosegundos

    for (i = 0; i <= 100; i++) { // Loop de 0 a 100
        printf("\r  %d%% ", i); // Imprime a porcentagem
        
        // Imprime a barra de progresso
        for (j = 0; j < i; j++) { // Loop de 0 a i
            printf("%c", 219); // Imprime o caractere de bloco
        }
        for (j = i; j < 100; j++) { // Loop de i a 100
            printf(" "); // Imprime um espaço
        }
        printf("]"); // Imprime o caractere de fechamento da barra

        fflush(stdout); // Limpa o buffer de saída
        nanosleep(&ts, NULL); // Pausa por 0.5 milissegundo
    }

    printf("\n\n Finalizando...\n"); // Imprime a mensagem de finalização
#ifdef _WIN32 // Verifica se o sistema operacional é Windows
    Sleep(1000); // Pausa por 1 segundo
#else // Se não for Windows
    sleep(1); // Pausa por 1 segundo
#endif // Fim da verificação do sistema operacional
    printf("\n Aguarde mais um pouco...\n"); // Imprime a mensagem de aguarde
#ifdef _WIN32 // Verifica se o sistema operacional é Windows
    Sleep(1000); // Pausa por 1 segundo
#else // Se não for Windows
    sleep(1); // Pausa por 1 segundo
#endif // Fim da verificação do sistema operacional
    printf("\n Carregamento concluido.\n\n\n\n"); // Imprime a mensagem de carregamento concluído
#ifdef _WIN32 // Verifica se o sistema operacional é Windows
    Sleep(1000); // Pausa de 1 segundo
#else // Se não for Windows
    sleep(1); // Pausa de 1 segundo
#endif // Fim da verificação do sistema operacional

    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    strcpy(contas[0].usuario, "ADMIN"); // Definindo o nome de usuário e senha do administrador
    strcpy(contas[0].senha, "123+"); // Definindo o nome de usuário e senha do administrador

    inicializandoProdutos(); // Chama a função de inicialização de produtos
    carregarContas(contas, &numContas); // Chama a função de carregamento de contas
    loginCliente(); // Chama a função de login

}

/* Início dos menus */
void loginCliente() { // Função de login
    int opcao; // Variável de opção

    do {
        // Menu de opções ( todos os printf são para imprimir o menu na tela)
        printf("\033[H\033[J");
        printf("|--------------------------------------------|\n");
        printf("|              Acesso a conta                |\n");
        printf("|                                            |\n");
        printf("|  [1] Registrar conta    [2] Acessar conta  |\n");
        printf("|                                            |\n");
        printf("|  [3] Esqueceu a senha   [4] Fechar painel  |\n");
        printf("|                                            |\n");
        printf("|--------------------------------------------|\n");
        sleep(1);

        scanf("%d", &opcao); // Lendo a opção escolhida pelo usuário
        while (getchar() != '\n'); // Limpa o buffer do teclado

        switch(opcao) { // Verifica a opção escolhida
            case 1: // Caso a opção seja 1
                registrarConta(contas, &numContas); // Chama a função de registro de conta
                break;  // Sai do switch
            case 2: // Caso a opção seja 2
                acessarConta(contas, numContas); // Chama a função de acesso à conta
                break; // Sai do switch
            case 3: // Caso a opção seja 3
                esqueceuSenha(contas, numContas); // Chama a função de recuperação de senha
                break; // Sai do switch
            case 4:     // Caso a opção seja 4
                printf("Fechando painel...\n"); // Imprime a mensagem de fechamento
                sleep(1); // Pausa por 1 segundo
                break; // Sai do switch

            case 5: // Caso a opção seja 5
                loginAdmin(); // Chama a função de login do administrador
                break; // Sai do switch
            default: // Caso a opção seja diferente das anteriores
                printf("Opcao invalida. Tente novamente.\n");
                sleep(1);
        }
           printf("Digite para continuar: ");
           scanf("%d", &opcao);
           while (getchar() != '\n');
    } while (opcao != 4); // O loop continua até que o usuário escolha fechar o programa
}

void loginAdmin(){

    int opcao;
    do{
        system("cls");
        printf("<--------------------------------------------------->\n");
        printf("|                 "MAGENTA"ÁREA DE ADMINISTAÇÃO"RESET"              |\n");
        printf("|                                                   |\n");
        printf("|  [1] Verificar Contas    [2] Consultar Produtos   |\n");
        printf("|                                                   |\n");
        printf("|                 "RED"[0] Logout Da Conta"RESET"               |\n");
        printf("<--------------------------------------------------->\n");
        scanf("%d",&opcao);
        while (getchar() != '\n');

        switch (opcao){

            case 0:
                loginCliente();
                break;
            case 1:
                printf("<----------------------------------->\n");
                printf("|  "GREEN"Contas Registradas: %-2d"RESET"       |\n",numContas-1);
                printf("<----------------------------------->\n");
                printf("Digite para continuar: ");
                scanf("%d", &opcao);
                while (getchar() != '\n');
                break;
            case 2:
                consultarProdutos();
                break;
            default:
                printf("<----------------------------------->\n");
                printf("|          "RED"OPÇÃO INVALIDA!"RESET"          |\n");
                printf("<----------------------------------->\n");
                sleep(2);
                break;
        }
    }while(opcao!=0);


}

void registrarConta(struct Conta contas[], int *numContas) { // Função de registro de conta
    char usuario[50]; // Variável para o nome de usuário
    printf("Digite o nome de usuario: ");  // Imprime a mensagem para digitar o nome de usuário
    sleep(1);
    scanf("%s", usuario); // Lendo o nome de usuário

    if (verificarUsuarioExistente(usuario, *numContas) || verificarUsuarioArquivo(usuario)) { // Verifica se o usuário já existe
        printf("Usuario ja existe. Tente um nome de usuario diferente.\n");
        sleep(1);
        return;
    }

    strcpy(contas[*numContas].usuario, usuario); // Copiando o nome de usuário para a estrutura de conta
    printf("Digite a senha: ");
    sleep(1);
    scanf("%s", contas[*numContas].senha);   // Lendo a senha

    salvarConta(contas[*numContas]); // Salva a nova conta no arquivo
    (*numContas)++; // Incrementando o número total de contas
    printf("Conta registrada com sucesso!\n");
    sleep(1);

    menusdeAlimentacao();
}

int verificarUsuarioExistente(char usuario[], int numContas) {
    for (int i = 0; i < numContas; i++) {
        if (strcmp(usuario, contas[i].usuario) == 0) {
            return 1;
        }
    }
    return 0;
}

int verificarUsuarioArquivo(char usuario[]) { // Função para verificar se o usuário já existe no arquivo
    FILE *file = fopen("contas.txt", "r"); // Abre o arquivo para leitura
    if (file == NULL) { // Verifica se o arquivo foi aberto corretamente
        return 0; // Retorna 0
    }

    struct Conta temp;
    while (fscanf(file, "%s %s", temp.usuario, temp.senha) != EOF) { // Lê o arquivo linha por linha
        if (strcmp(temp.usuario, usuario) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void acessarConta(struct Conta contas[], int numContas) { // Função de acesso à conta
    char usuario[50]; // Variável para o nome de usuário
    char senha[30];  // Variável para a senha
    printf("Digite o nome de usuario: ");
    sleep(1);
    scanf("%s", usuario); // Lendo o nome de usuário
    printf("Digite a senha: ");
    sleep(1);
    scanf("%s", senha);   // Lendo a senha

     if(strcmp(usuario,contas[0].usuario) == 0 && strcmp(senha,contas[0].senha) == 0){ // Verifica se o usuário é o administrador
        loginAdmin(); // Chama a função de login do administrador
    }

    // Procurando a conta no array de contas
    for (int i = 0; i < numContas; i++) { // Loop de 0 até o número total de contas
        if (strcmp(usuario, contas[i].usuario) == 0 && strcmp(senha, contas[i].senha) == 0) { // Verifica se o usuário e a senha estão corretos
            printf("Conta acessada com sucesso!\n");
            sleep(1);
            menusdeAlimentacao();
            return;
        }
    }

    // Verificando a conta no arquivo
    FILE *file = fopen("contas.txt", "r"); // Abre o arquivo para leitura
    if (file == NULL) { // Verifica se o arquivo foi aberto corretamente
        printf("Nome de usuario ou senha incorretos.\n");
        sleep(1);
        return;
    }
 
    struct Conta temp; // Variável temporária para armazenar a conta
    while (fscanf(file, "%s %s", temp.usuario, temp.senha) != EOF) { // Lê o arquivo linha por linha
        if (strcmp(usuario, temp.usuario) == 0 && strcmp(senha, temp.senha) == 0) {
            printf("Conta acessada com sucesso!\n");
            sleep(1);
            fclose(file);
            menusdeAlimentacao();
            return;
        }
    }

    fclose(file); // Fecha o arquivo
    printf("Nome de usuario ou senha incorretos.\n");
    sleep(1);
}

void esqueceuSenha(struct Conta contas[], int numContas) {
    char usuario[50];
    printf("Digite o nome de usuario: ");
    sleep(1);
    scanf("%s", usuario); // Lendo o nome de usuário

    // Procurando o nome de usuário no array de contas
    for (int i = 0; i < numContas; i++) {
        if (strcmp(usuario, contas[i].usuario) == 0) {
            printf("Para recuperar a senha do user: '%s', entre em contato com algum administrador. [Gilson, Pablo, Luiza, Joao Carlos]\n", contas[i].usuario, contas[i].senha);
            sleep(1);
            return;
        }
    }

    // Procurando o nome de usuário no arquivo
    FILE *file = fopen("contas.txt", "r");
    if (file == NULL) {
        printf("Nome de usuario nao encontrado.\n");
        sleep(1);
        return;
    }

    struct Conta temp;
    while (fscanf(file, "%s %s", temp.usuario, temp.senha) != EOF) {
        if (strcmp(usuario, temp.usuario) == 0) {
            printf("Para recuperar a senha do user: '%s', entre em contato com algum administrador. [Gilson, Pablo, Luiza, Joao Carlos]\n", temp.usuario, temp.senha);
            sleep(1);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Nome de usuario nao encontrado.\n");
    sleep(1);
}

void salvarConta(struct Conta conta) {
    FILE *file = fopen("contas.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        sleep(1);
        return;
    }

    fprintf(file, "%s %s\n", conta.usuario, conta.senha);
    fclose(file);
}

void inicializandoProdutos() {
    strcpy(produtos[0].NomeProduto, "Cafe"); // Definindo o nome do produto
    produtos[0].Valor = 1.50; // Definindo o valor do produto
    produtos[0].quantidade = 10; // Definindo a quantidade do produto

    strcpy(produtos[1].NomeProduto, "Cafe com Leite");
    produtos[1].Valor = 2.50;
    produtos[1].quantidade = 10;

    strcpy(produtos[2].NomeProduto, "Cafe Premium");
    produtos[2].Valor = 4.0;
    produtos[2].quantidade = 10;

    strcpy(produtos[3].NomeProduto, "Capuccino");
    produtos[3].Valor = 6.0;
    produtos[3].quantidade = 10;

    strcpy(produtos[4].NomeProduto, "Pao");
    produtos[4].Valor = 1.50;
    produtos[4].quantidade = 10;

    strcpy(produtos[5].NomeProduto, "Salgado");
    produtos[5].Valor = 5.50;
    produtos[5].quantidade = 10;

    strcpy(produtos[6].NomeProduto, "Bolo");
    produtos[6].Valor = 7.0;
    produtos[6].quantidade = 10;

    strcpy(produtos[7].NomeProduto, "Bolo de Chocolate");
    produtos[7].Valor = 9.0;
    produtos[7].quantidade = 10;

    gerarAquivoPodutos();

}

void gerarAquivoPodutos(){ // Função para gerar o arquivo de produtos

    FILE *file = fopen("Produtos.txt", "w"); // Abre o arquivo para escrita
    
    int i;

    for(i=0;i<8;i++){ // Loop de 0 a 8
        fprintf(file,"\n"); // Imprime uma linha em branco
        fprintf(file,"<----------------------------------->\n"); // Imprime a linha de separação
        fprintf(file,"|             Produto %-14d|\n", i+1); // Imprime o número do produto
        fprintf(file,"<----------------------------------->\n"); // Imprime a linha de separação

        fprintf(file,"<----------------------------------->\n");
        fprintf(file,"| Tipo: %-27s |\n",produtos[i].NomeProduto); // Imprime o nome do produto
        fprintf(file,"| Valor: %-27.2f|\n",produtos[i].Valor); // Imprime o valor do produto
        fprintf(file,"| Quantidade: %-22d|\n",produtos[i].quantidade); // Imprime a quantidade do produto
        fprintf(file,"<----------------------------------->\n");
    }
    fclose(file);
}

void consultarProdutos(){

    char linhaArquivo[500];
    int opcao;
    system("cls");
    // Abre o arquivo para leitura

    FILE *file = fopen ("Produtos.txt","r");
    printf("<----------------------------------->\n");
    printf("|                                   |\n");
    printf("|        "GREEN"CONSULTANDO ARQUIVO"RESET"        |\n");
    printf("|                                   |\n");
    printf("<----------------------------------->\n");
    
    

    while(fgets(linhaArquivo, sizeof(linhaArquivo),file)!=NULL){ // Lê o arquivo linha por linha
        printf("%s",linhaArquivo); // Imprime a linha
    } 
    fclose(file);
    do{
        printf("<----------------------------------->\n");
        printf("| "RED"Digite '0' para sair"RESET"            |\n");
        printf("<----------------------------------->\n");
        scanf("%d",&opcao);
    }while(opcao!=0);
    loginAdmin();
}

void menusdeAlimentacao() {
    int opcao;

    do {
        printf("\033[H\033[J");
        printf("|--------------------------------------------|\n");
        printf("|                 Cardapio                   |\n");
        printf("|                                            |\n");
        for (int i = 0; i < 8; i++) {
        printf("|   [%d]%-25s R$:%.2f     |\n", i + 1, produtos[i].NomeProduto, produtos[i].Valor);
        printf("|                                            |\n");
        }
        printf("|                                            |\n");
        printf("|             [0]Cancelar Pedido             |\n");
        printf("|--------------------------------------------|\n");
        sleep(1);

        scanf("%d", &opcao);
        while (getchar() != '\n');

        if (opcao >= 1 && opcao <= 8) {
            if(produtos[opcao - 1].quantidade == 0){
                printf("Produto esgotado!\n");
                sleep(1);
                continue;
            }

            printf("Voce selecionou: %s por R$%.2f\n", produtos[opcao - 1].NomeProduto, produtos[opcao - 1].Valor);
            produtos[opcao - 1].quantidade--;
            sleep(1);
            metodoPagamento(); // Chama a função metodoPagamento após a seleção do produto
            feedback(); // Chama a função feedback após o pagamento
            return; // Sai da função após o feedback
        } else if (opcao != 0) {
            printf("Opcao invalida. Tente novamente.\n");
            sleep(1);
        }
    } while (opcao != 0);
}

void metodoPagamento(){
    int opcao;
    do{
        printf("\033[H\033[J");
        printf("|--------------------------------------------|\n");
        printf("|                 Pagamento                  |\n");
        printf("|                                            |\n");
        printf("|     [1]Dinheiro          [2]Cartao         |\n");
        printf("|                                            |\n");
        printf("|     [3]Pix               [4]Fechar painel  |\n");
        printf("|                                            |\n");
        printf("|--------------------------------------------|\n");

        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch(opcao){
            case 1:
            printf("\033[H\033[J");
            printf("Verificando cedulas!\n");
            sleep(1);
            printf("Pagamento efetuado com sucesso!\n");
            sleep(1);
            opcao = 4; // Para sair do loop e finalizar
            break;
            case 2:
            printf("\033[H\033[J");
            printf("Insira o cartao!\n");
            sleep(1);
            printf("Verificando com a bandeira do cartao! Aguarde...\n");
            sleep(2);
            printf("Aguarde...\n");
            sleep(2);
            printf("Pagamento efetuado com sucesso!\n");
            opcao = 4; // Para sair do loop e finalizar
            break;
            case 3:
                printf("\033[H\033[J");
                printf("Realize o pagamento atraves do QR CODE:\n");
                printf("                                       \n");
                printf("                                       \n");
                sleep(1); // Pausa de 1 segundos
                printf("Aguarde o QR CODE ser gerado...\n");
                printf("                                       \n");
                sleep(3); // Pausa de 1 segundos
                printf("##############  @@####     ##  ##  ++##############\n");
                printf("##          ##           ####  ##  ++##          ##\n");  
                printf("##  ######  ##  @@mm ########      ++##  ######  ##\n");  
                printf("##  ######  ##  @@#####  ##  ####  ++##  ######  ##\n");  
                printf("##  ######  ##  @@###### ########  ++##  ######  ##\n");  
                printf("##          ##    #    ##  ##  ##  ++##          ##\n");  
                printf("#############  m  ##  ##  ##   ##  ++##############\n");  
                printf("                   ..##  ##    ##  ##              \n");  
                printf("@@@@@@@@ @@  mmmm          ##@@##@@++    @@@@@@  @@\n");  
                printf("mm####...mm..mm++..        mmmm####++  ..mmmmmm..mm\n");
                printf("   ###    ####    ..##    ##  ##  ####++    ##  ###\n");
                printf("# #####    ####mm    ##    ##    ##++  ####      ##\n");
                printf("                 ##mm    ##      ####        ##  ##\n");
                printf("++++++++++  ++::++  ++++  ++++##  --++  ++++++++++ \n");
                printf("##############  ..##  ##  ##  ##  ++ ##############\n");
                printf("##          ##  ..##         ####    ##          ##\n");
                printf("##  ######  ##    ..##    ##  #####  ##  ######  ##\n");
                printf("##  ######  ##  @@mm  ####  ##    ++ ##  ######  ##\n");
                printf("##  ######  ##  @@####  ##  ##  #### ##  ######  ##\n");
                printf("##          ##  @@mm  ####  ## ## ## ##          ##\n");
                printf("##############  @@mm      ######     ##############\n");
                sleep(3); // Pausa de 3 segundos
                printf("                                       \n");
                printf("                                       \n");
                printf("Aguardando Pagamento...\n");
                sleep(3); // Pausa de 3 segundos
                printf("                                       \n");
                printf("                                       \n");
                printf("Pagamento efetuado com sucesso!\n");
                sleep(1);
                opcao = 4; // Para sair do loop e finalizar
                break;
            case 4:
                printf("Fechando painel...\n");
                sleep(1);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                sleep(1);
        }
    } while(opcao != 4);

}

void feedback() {
    int opcao;

    do {
        printf("\033[H\033[J");
        printf("|--------------------------------------------|\n");
        printf("|                Avaliacao                   |\n");
        printf("|                                            |\n");
        printf("|     [1]1-2               [2]3-4            |\n");
        printf("|                                            |\n");
        printf("|     [3]5                 [4]Fechar painel  |\n");
        printf("|                                            |\n");
        printf("|--------------------------------------------|\n");
        sleep(1);

        scanf("%d", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
            case 2:
            case 3:
                printf("Obrigado pela sua avaliacao!\n");
                sleep(1);
                printf("Deslogado, acesse sua conta novamente.\n");
                sleep(1);
                opcao = 4; // Para sair do loop e finalizar
                break;
            case 4:
                printf("Fechando painel...\n");
                sleep(1);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                sleep(1);
                break;
        }
    } while (opcao != 4);
}

int carregarContas(struct Conta contas[], int *numContas) {
    FILE *file = fopen("registros.txt", "r");
    if (file == NULL) {
        return 0;
    }

    while (fscanf(file, "%s %s", contas[*numContas].usuario, contas[*numContas].senha) != EOF) {
        (*numContas)++;
    }

    fclose(file);
    return 1;
}
