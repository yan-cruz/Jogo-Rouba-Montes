/******************************************************************************
                            Trabalho Prático - AED's II

                Universidade do Estado de Minas Gerais - 12/2023

                                Aluno: Yan Cruz
                    2º período, Eng. da Computação, 2EngCM16.

                        Professor: Edwaldo Rodrigues


                    “Poucas pessoas percebem que a sorte é criada."

                                                    -- Robert Kiyosaki

*******************************************************************************/


// Incluindo as Bibliotecas - Início
    #include <stdio.h>
    #include <string.h>
    #include <time.h>
    #include <stdlib.h>
    #include <locale.h>
    #include <windows.h>
// Incluindo as Bibliotecas - Fim


// Structs - Início
    // Definição da struct para representar as cartas
    typedef struct cartas {
        int numero; // Armazena o número da carta. Varia de 1 ao 13
        char naipe; // Armazena o naipe da carta. Varia entre {E, C, O, P}
        struct cartas *proximo; // Ponteiro para o próximo elemento/ carta
    } tCarta;

    // Definição da struct para representar a pilha/ monte
    typedef struct pilha{
        tCarta *topo; // Ponteiro para o topo da pilha
    } tPilha;

    // Definição da struct para representar a lista/ descarte
    typedef struct lista{
        tCarta *inicio; // Ponteiro para o topo da lista
    } tLista;

    // Definição da struct para representar o jogador
    typedef struct jogadores {
        tPilha *monte; // Ponteiro para o monte do jogador
        char nome[31]; // Armazena o nome do jogador
        int quantCartas; // Armazena a quantidade de cartas no monte final do jogador. Usado apenas para o ranking
    } tJogador;
// Structs - Fim


// Protótipo das Funções - Início
    // Funções para manipulação de pilha - Início
        // Função para verificar se uma pilha está vazia
        int pilhaVazia (tPilha *P);

        // Função para verificar o tamanho de uma pilha
        int tamanhoPilha (tPilha *P);

        // Função para remover do topo da pilha
        int removeTopo (tPilha *P, tCarta *cartaVez);

        // Função para criar uma nova pilha
        tPilha* criaPilha();

        // Função para empilhar na pilha
        int empilhaTopo (tPilha *P, int num, char naipe);

        // Função para liberar uma pilha
        int limparPilha (tPilha *P);

    // Funções para manipulação de pilha - Fim


    // Funções para manipulação de lista - Início
        // Função para criar uma lista
        tLista *criaLista ();

        // Função para verificar se uma lista está vazia
        int listaVazia (tLista *L);

        // Função para limpar uma lista
        int limparLista (tLista *L);

        // Função para inserir no final da lista
        int insereFinal (tLista *L, tCarta *cartaVez);

        // Função para contar o tamanho de uma lista
        int tamanhoLista (tLista *L);

        // Função para remover por posição, em uma lista
        int removePosicao (tLista *L, int posicao, tCarta *cartaVez);

        // Função para remover o inicio de uma lista
        int removeInicio (tLista *L, tCarta *cartaRetirada);

        // Função para recuperar por chave, em uma lista
        int recuperarChave (tLista *L, tCarta cartaVez);
    // Funções para manipulação de lista - Início


    // Funções para criação dos baralhos - Início
        // Função para embaralhar um único baralho
        void embaralharBaralho(tCarta baralho[], int tamanho, int seed);

        // Função para criar os baralhos, de acordo com a quantidade solicitada
        tPilha* criarBaralhos(int numBaralhos);
    // Funções para criação dos baralhos - Fim


    // Funções para impressão - Início
        // Imprime o menu do jogo
        void imprimeMenu ();

        // Imprime as regras do jogo
        void imprimeInstrucoes();

        // Função para imprimir uma carta
        void imprimeCarta(int i, int numero, char naipe, int key);

        // Função para imprimir os topos de cada jogador
        void imprimeTopos (tJogador *jogadores, int quantJogadores, tPilha *pilhaCompra, int rodadas);

        // Função para imprimir uma pilha já existente
        void imprimePilha (tPilha *P, int key, int y);

        // Função para imprimir uma lista
        void imprimeLista (tLista *L, int key);

        // Função para imprimir os dados de um jogador
        void imprimeJogador (int id, tJogador *jogadores);
    // Funções para impressão - Início


    // Funções para impresão do ranking/ Resultados do jogo - Início
        // Função para ordenar um vetor
        void ordenaVetor(int *V, int tam);

        // Função para ordenar os montes dos jogadores
        void ordenaMontes (tJogador *jogadores, int quantJogadores);

        // Função para determinar os ganhadores, bem como imprimir os resultados
        int ganhadores(tJogador *jogadores, int quantJogadores, tLista *descarte);

    // Funções para impresão do ranking/ Resultados do jogo - Fim


    // Funções para operações do jogo - Início
        // Função para verificar se a carta da vez combina com alguma carta no jogo
        int comparaCartaVez(tCarta *cartaVez, tLista *listaDescarte, tJogador *jogadores, int quantJogadores, int jogadorAtual);

        // Função para empilhar. Se a carta da vez combina com alguma carta na área de descarte
        int roubaDescarte(tCarta *cartaVez, tLista *listaDescarte, tJogador *jogadores, int posicao, int jogadorAtual);

        // Função para roubar monte. Se a carta da vez combina com o topo de algum jogador
        int roubaMonte(tCarta *cartaVez, int jogadorAtual, tJogador *jogadores, int quantJogadores, int donoMonte);

        // Função para empilhar. Se a carta da vez combina com o topo do próprio jogador
        int empilhaMonte(tCarta *cartaVez, tJogador *jogadores, int jogadorAtual);

        // Função para descartar. Se a carta da vez não combina com nenhuma outra carta
        void descarta(tCarta *cartaVez, tLista *listaDescarte);
    // Funções para operações do jogo - Fim
// Protótipo das Funções - Fim


// Função principal - Início
    int main (){
        setlocale(LC_ALL, "portuguese");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("\n\n                  Seja bem-vindo ao ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Rouba");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        printf("-");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Montes!\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        // O menu do jogo, feito com um switch case
        int opcaoMenu;
        do {
            imprimeMenu();
            scanf("%d", &opcaoMenu);
            switch (opcaoMenu) {
                case 3:
                    printf("\n\n  Obrigado por jogar! Encerrando o jogo...");
                    Sleep(1000);
                    exit(0);
                    printf("\n\n");
                    system("pause");


                case 2:
                    imprimeInstrucoes();
                    printf("\n\n");

                case 1:
                break;
            }
        } while (opcaoMenu != 1);

        // Armazena a quantidade de jogadores que irão jogar
        int quantJogadores;
        do {
            printf("\n\n  Digite a quantidade de jogadores: ");
            scanf("%d", &quantJogadores);
        } while (quantJogadores <= 1);

        // Cria um vetor, dinamicamente, para armazenar os jogadores. Do tipo "tJogador"
        tJogador *players = (tJogador*)malloc(quantJogadores * sizeof(tJogador));
        if (players == NULL){
            printf("\n\n  Erro ao alocar memória para os jogadores.");
            return 0;
        }

        // Loop para capturar o nome de cada jogador
        for (int i = 0; i < quantJogadores; i++){
            setbuf(stdin, NULL);
            printf("\n  Digite o nome do %dº jogador: ", i+1);
            setbuf(stdin, NULL);
            fgets(players[i].nome, 31, stdin);
            players[i].nome[strcspn(players[i].nome, "\n")] = '\0';
            // Cria o monte do jogador, inicialmente vazio
            players[i].monte = criaPilha();
        }

        // Armazena a quantidade de baralhos do jogo
        int quantBaralhos;
        do {
            printf("\n\n  Digite a quantidade de baralhos: ");
            scanf("%d", &quantBaralhos);
        } while (quantBaralhos <= 0);

        printf("\n\n  Gerando baralho para %d jogadores...\n\n", quantJogadores);
        Sleep(1000);

        // Cria a pilha de compra, de acordo com a quantidade de baralhos
        tPilha *pilhaCompra = criarBaralhos(quantBaralhos);

        // Cria a área de descarte, uma lista, inicialmente vazia
        tLista *listaDescarte = criaLista();

        // Cria a uma "carta". Será a carta da rodada, tirada da pilha de compra
        tCarta *cartaVez = (tCarta*)malloc(sizeof(tCarta));
        if (cartaVez == NULL) {
            printf("\n\n  Erro ao alocar memória para o jogo.");
            return 0;
        }

        // Quatro variáveis para controle do jogo
        int rodadas = 1;
        char acionaCompra;
        int verify;
        int jogaNovamente;

        // O loop principal do jogo, irá parar quando a pilha de compra ficar vazia
        while (tamanhoPilha(pilhaCompra) > 0) {

            // Um loop interno, usado para capturar o jogador da rodada
            for (int jogadorAtual = 0; jogadorAtual < quantJogadores; jogadorAtual++){

                // Iprime o topo de cada monte dos jogadores
                imprimeTopos (players, quantJogadores, pilhaCompra, rodadas);

                // Reseta a variável de controle
                jogaNovamente = 0;

                // Captura o 'enter', para retirar uma carta
                printf("\n  |");
                printf("\n  |  %s, tecle 'enter' para comprar uma carta: ", players[jogadorAtual].nome);
                setbuf(stdin, NULL);
                acionaCompra = getchar();

                // Percorre ao menos uma vez. Usado para garantir que o jogador tecle só 'enter'
                do {

                    // Se a tecla for correta, faz as ações do jogo
                    if (acionaCompra == '\n'){

                        // Retira a carta do topo da pilha de compra
                        verify = removeTopo(pilhaCompra, cartaVez);
                        if (verify == 0){
                            printf("\n  Erro ao remover carta!");
                        }

                        // Mostra a carta retirada
                        printf("  |");
                        printf("\n  |  Carta retirada: ");
                        imprimeCarta(-1, cartaVez->numero, cartaVez->naipe, 0);
                        printf("\n");

                        // Compara a carta com os montes e descarte. Vai definir pra onde a carta vai
                            // -1 se ela combinar com o topo de algum monte
                            // 0 se ela não combinar com um monte, nem do descarte
                            // A posição da carta equivalente na lista de descarte
                        verify = comparaCartaVez(cartaVez, listaDescarte, players, quantJogadores, jogadorAtual);

                        // Se a carta da vez combina com o monte de outro jogador
                        if (verify >= 92){
                            int jogadorRoubado = verify-92;
                            // Se combina com um monte, rouba ele
                            verify = roubaMonte(cartaVez, jogadorAtual, players, quantJogadores, jogadorRoubado);
                            printf("  |");
                            printf("\n  |  %s, você roubou o monte de %s!", players[jogadorAtual].nome, players[jogadorRoubado].nome);

                            // O jogador deverá jogar novamente
                            jogaNovamente++;
                        }

                        // Se a carta da vez combina com a área de descarte
                        else if (verify != 0 && verify < 92){

                            // 'posição' é criada para armazenar a posição da carta equivalente no descarte
                            int posicao;
                            posicao = verify;

                            // Empilha a carta equivalente do descarte
                            verify = roubaDescarte(cartaVez, listaDescarte, players, posicao, jogadorAtual);
                            printf("  |");
                            printf("\n  |  %s, você pegou uma carta do descarte e empilhou as duas em seu monte!", players[jogadorAtual].nome);
                            // O jogador deverá jogar novamente
                            jogaNovamente++;
                        }

                        // Se a carta da vez não combina com nenhuma carta do descarte, nem dos montes dos outros jogadores
                        else if (verify == 0) {

                            // Verifica se a carta deverá ser descartada ou empilhada em seu monte
                                // 0 se ela for diferente do topo de seu monte
                                // 1 se ela for igual ao topo do seu monte
                            verify = empilhaMonte(cartaVez, players, jogadorAtual);

                            // A carta será descartada
                            if (verify == 0){
                                descarta(cartaVez, listaDescarte);
                                printf("  |");
                                printf("\n  |  %s, você descartou a carta!", players[jogadorAtual].nome);
                            }

                            // A carta será empilhada em seu próprio monte
                            else {
                                printf("  |");
                                printf("\n  |  %s, você empilhou a carta em seu monte!", players[jogadorAtual].nome);
                                jogaNovamente++;
                            }
                        }
                    }

                    // Se a tecla não for correta, irá repetir até que seja
                    else {
                        printf("  Tecla inválida! Tecle 'enter' para lançar o dado: ");
                        setbuf(stdin, NULL);
                        acionaCompra = getchar();
                    }
                } while (acionaCompra != '\n');

                // Imprime o descarte
                imprimeLista(listaDescarte, 1);

                // Incrementa 'rodadas'
                rodadas++;

                // Caso o jogador tenha empilhado a carta ou roubado um monte, joga novamente
                if (jogaNovamente != 0){
                    jogadorAtual--;
                }

                // Se a pilha de compra acabar, temina o jogo imediatamente
                if (tamanhoPilha(pilhaCompra) == 0) {
                    printf("\n\n  Baralho de compras esgotado. O jogo acabou!");
                break;
                }
            }
        }

        // Chama a função final, imprimindo o ranking e finalizando o jogo
        verify = ganhadores(players, quantJogadores, listaDescarte);

        // Libera toda memória alocada dinâmicamente
        limparLista(listaDescarte);
        limparPilha(pilhaCompra);
        free(players);
        free(cartaVez);

        printf("\n\n");
        system("pause");

        return 0;

    };
// Função principal - Fim

// Corpo das funções - Início
    int pilhaVazia (tPilha *P){
        // Verifica se o topo da pilha aponta para nulo
        if (P->topo == NULL){
            // Se sim, a pilha está vazia
            return 1;
        }
        else{
            // Se sim, a pilha possue elemento
            return 0;
        }
    };

    int tamanhoPilha (tPilha *P){
        // Verifica de cara se a pilha é vazia, se sim, retorna tamanho 0
        if (pilhaVazia(P)){
            return 0;
        }

        // Cria uma carta auxiliar, igual ao topo da pilha
        tCarta *aux;
        aux = P->topo;

        // Cria um contador e percorre toda a pilha, incrementando-o
        int cont = 1;
        while (aux->proximo!= NULL){
            aux = aux->proximo;
            cont++;
        }

        // Retorna o contador, equivalente ao tamanho da pilha
        return cont;
    };

    int removeTopo (tPilha *P, tCarta *cartaVez){
        if (pilhaVazia(P)){
            // Verifica de cara se a pilha é vazia, se sim, retorna o erro ao remover
            return 0;
        }

        // Cria uma carta auxiliar, igual ao topo da pilha
        tCarta *aux = P->topo;

        // Aponta o topo da pilha para o próximo elemento dela, atualizando-o
        P->topo = P->topo->proximo;

        // Isola o elemento à ser removido
        aux->proximo = NULL;

        // Retorna a carta removida para o main
        *cartaVez = *aux;

        // Exclui, definitivamente, o elemento removido
        free(aux);

        return 1;

    };

    void imprimeCarta(int i, int numero, char naipe, int key){

        // Vetor para converter '1' em 'Ás', '2' em 'Dois', assim por diante
        char numNaipe[13][10] = {"Ás", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"};

        // O 'i' é uma variável de controle, pois essa função tem duas finalidades
            // i < 0 se for pra imprimir uma carta avulsa. Apenas número e naipe
            // i >= 0 se for pra imprimir uma carta dentro de uma pilha ou lista. Número da carta na lista, bem como número e naipe
        if (i < 0){
            if (naipe =='E'){
                printf("%s - %s", numNaipe[numero-1], "Espadas");
            }
            else if (naipe =='P'){
                printf("%s - %s", numNaipe[numero-1], "Paus");
            }
            else if (naipe == 'C'){
                printf("%s - %s", numNaipe[numero-1], "Copas");
            }
            else if (naipe == 'O'){
                printf("%s - %s", numNaipe[numero-1], "Ouros");
            }
        }
        else if (key == 7){
            if (naipe =='E'){
                printf("\n  %dº Carta: %s - %s", i, numNaipe[numero-1], "Espadas");
            }
            else if (naipe =='P'){
                printf("\n  %dº Carta: %s - %s", i, numNaipe[numero-1], "Paus");
            }
            else if (naipe == 'C'){
                printf("\n  %dº Carta: %s - %s", i, numNaipe[numero-1], "Copas");
            }
            else if (naipe == 'O'){
                printf("\n  %dº Carta: %s - %s", i, numNaipe[numero-1], "Ouros");
            }
        }
        else {
            if (naipe =='E'){
                printf("\n  |  %dº Carta: %s - %s", i, numNaipe[numero-1], "Espadas");
            }
            else if (naipe =='P'){
                printf("\n  |  %dº Carta: %s - %s", i, numNaipe[numero-1], "Paus");
            }
            else if (naipe == 'C'){
                printf("\n  |  %dº Carta: %s - %s", i, numNaipe[numero-1], "Copas");
            }
            else if (naipe == 'O'){
                printf("\n  |  %dº Carta: %s - %s", i, numNaipe[numero-1], "Ouros");
            }
        }
    };

    void imprimeTopos (tJogador *jogadores, int quantJogadores, tPilha *pilhaCompra, int rodadas){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (rodadas < 10){
            printf("\n\n  +---------------------------------+\n");
            printf("  |  Topo dos Jogadores - Rodada 0%d |\n", rodadas);
            printf("  +---------------------------------+\n");
        }
        else if (rodadas >= 10 && rodadas <100){
            printf("\n\n  +---------------------------------+\n");
            printf("  |  Topo dos Jogadores - Rodada %d |\n", rodadas);
            printf("  +---------------------------------+\n");
        }
        else if (rodadas >= 100){
            printf("\n\n  +----------------------------------+\n");
            printf("  |  Topo dos Jogadores - Rodada %d |\n", rodadas);
            printf("  +----------------------------------+\n");
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN );
        printf("  |");

        // Percorre o topo dos montes dos jogadores e imprime a carta
        for (int i = 0; i < quantJogadores; i++){
            printf("\n  |  Topo do monte de %s: ", jogadores[i].nome);
            if (jogadores[i].monte->topo == NULL){
                printf("NULO");
            }
            else {
                imprimeCarta(-1, jogadores[i].monte->topo->numero, jogadores[i].monte->topo->naipe, 0);
            }
        }

        // Imprime a quantidade de cartas presente na pilha de compra
        printf("\n  |");
        printf("\n  |  Pilha de compra: %d cartas", tamanhoPilha(pilhaCompra));
        printf("\n  |");
    };

    void imprimeInstrucoes(){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        printf("\n\n  +-----------------------------+\n");
        printf("  |       Regras do jogo:       |\n");
        printf("  +-----------------------------+\n");
        printf("  |\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN );
        printf("  | Os jogadores revezam em retirar cartas da pilha de compras. Se a carta\n");
        printf("  | retirada combinar com uma carta na área de descarte, o jogador adiciona as\n");
        printf("  | duas ao seu monte.\n");
        printf("  |\n");
        printf("  |\n");
        printf("  | Se a carta retirada combinar com a carta superior de outro monte, o jogador\n");
        printf("  | 'rouba' esse monte. Se a carta retirada for igual à carta superior do \n");
        printf("  | próprio monte, ela é adicionada ao topo.\n");
        printf("  |\n");
        printf("  |\n");
        printf("  | Se não houver combinação, a carta vai para a área de descarte.\n");
        printf("  |\n");
        printf("  |\n");
        printf("  | O objetivo é terminar o jogo com a maior quantidade de cartas.\n");
        printf("  |\n");
        printf("  +------------------+\n");
    };

    void imprimeMenu (){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        printf("\n\n  +--------------------------+\n");
        printf("  |       Menu Inicial       |\n");
        printf("  +--------------------------+");
        printf("\n  |");
        printf("\n  |");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("  1. ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Iniciar Jogo");
        printf("\n  |");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        printf("  2. ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Instruções");
        printf("\n  |");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
        printf("  3. ");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Sair");
        printf("\n  |");
        printf("\n  +--------------------------+\n");
        printf("\n\n  Escolha uma opção: ");
    };

    void imprimePilha (tPilha *P, int key, int y){
        // Verifica se a pilha está vazia
        if (pilhaVazia(P)){
            // O 'key' é uma variável de controle, pois essa função tem duas finalidades
                // key = 7 se for pra se referir à um monte
                // key != 7 se for pra se referir à uma pilha
            if (key == 7){
                printf("\n  O monte está vazio!");
            }
            else{
                printf("\n  A pilha está vazia!");
            }
        }

        // Cria uma variável aux, igual ao topo da pilha
        tCarta *aux = P->topo;
        if (key == 7){
            printf("\n  Monte:");
        }
        else{
            printf("\n  A pilha é: ");
        }

        // Equanto existir cartas, irá imprimir
        int i = 1;
        while (aux->proximo != NULL) {
            imprimeCarta(i, aux->numero, aux->naipe, y);
            aux = aux->proximo;
            i++;
        }
        imprimeCarta(i, aux->numero, aux->naipe, y);
    };

    tPilha* criaPilha(){
        // Aloca memória para uma pilha
        tPilha *novaPilha;
        novaPilha = (tPilha*)malloc(sizeof(tPilha));

        if (novaPilha == NULL) {
            printf("\n\n  Erro ao alocar memória para o jogo.");
            return 0;
        }

        // Define seu topo como nulo
        novaPilha->topo = NULL;

        // Retorna a pilha
        return novaPilha;
    };

    int empilhaTopo (tPilha *P, int num, char naipe){
        // Aloca memória para o novo elemento
        tCarta *novo;
        novo = (tCarta*)malloc(sizeof(tCarta));
        if (novo == NULL) {
            printf("\n\n  Erro ao alocar memória para o jogo.");
            return 0;
        }

        // Define o novo elemento
        novo->numero = num;
        novo->naipe = naipe;

        // Aponta seu 'próximo' para o topo da pilha
        novo->proximo = P->topo;

        // Define novo como o novo topo
        P->topo = novo;

        return 1;
    };

    int limparPilha (tPilha *P){
        // Enquanto tiver elementos, cria um aux para exclui-los
        while (P->topo != NULL){
            tCarta *aux;
            aux = P->topo;
            P->topo = aux->proximo;
            aux->proximo = NULL;
            free(aux);
        }

        // Se a pilha estiver vazia, exclui ela
        if (pilhaVazia(P)){
            free(P);
            return 1;
        }

        return 0;
    };

    void embaralharBaralho(tCarta baralho[], int tamanho, int seed) {
        // Define a semente de geração como 'seed', gerada previamente
        srand(seed);

        // Percorre todo baralho, iniciando na última posição e continuando enquanto houver cartas sem embaralhar
        for (int i = tamanho - 1; i > 0; i--) {

            // Define 'j' como um número aleatório entre o tamanho total do baralho e 1
            int j = rand() % (i + 1);

            // Inverte as posições com o auxilio de uma carta temporária
            tCarta temp = baralho[i];
            baralho[i] = baralho[j];
            baralho[j] = temp;
        }
    };

    tPilha* criarBaralhos(int numBaralhos) {
        // Cria um vetor para representar os naipes
        char naipes[4] = {'E', 'C', 'P', 'O'}; // Espadas, Copas, Ouros, Paus

        // Define o tamanho total do baralho e gera um vetor com esse tamanho
        int tamanhoTotal = numBaralhos * 52;
        tCarta *baralhos = (tCarta*)malloc(tamanhoTotal * sizeof(tCarta));

        // Verifica se a geração foi bem feita
        if (baralhos == NULL) {
            printf("\n\n  Erro ao alocar memória para os baralhos.");
            return 0;
        }

        // Gera as cartas do baralho. Todos os números e naipes, em ordem, quantas vezes precisar
        for (int i = 0; i < numBaralhos; i++) {
            for (int naipe = 0; naipe < 4; naipe++) {
                for (int numero = 1; numero <= 13; numero++) {
                    baralhos[i * 52 + (naipe * 13 + numero - 1)].numero = numero;
                    baralhos[i * 52 + (naipe * 13 + numero - 1)].naipe = naipes[naipe];
                }
            }
        }

        // Embaralha o baralho n vezes, sendo n = número de baralhos. Garante um melhor embaralhamento
        for (int i = 0; i < numBaralhos; i++) {

            // Cria uma semente única, com base no tempo atual e i.
                // O i é usado para, caso seja mais de 1 baralho, eles serem distintos
            int seed = (int)time(NULL) + i;

            // Embaralha usando a semente gerada
            embaralharBaralho(&baralhos[i * 52], 52, seed);
        }

        // Cria uma pilha, futura pilha de compra
        tPilha *pilhaCompra = criaPilha();

        // Empilha todos as cartas, já embaralhadas, na pilha de compra
        for (int i = 0; i < tamanhoTotal; i++) {
            empilhaTopo(pilhaCompra, baralhos[i].numero, baralhos[i].naipe);
        }

        // Libera a memória do vetor
        free(baralhos);

        // Retorna a pilha
        return pilhaCompra;
    };

    tLista *criaLista (){
        // Aloca memória para uma lista
        tLista *L = (tLista*)malloc(sizeof(tLista));
        if (L == NULL){
            printf("\n\n  Erro ao alocar memória para o jogo.");
            return NULL;
        }

        // Define seu início como nulo e a retorna
        L->inicio = NULL;

        return L;
    };

    int listaVazia (tLista *L){
        // Se o início for nulo, ela está vazia
        if (L->inicio == NULL){
            return 1;
        }
        return 0;
    };

    int limparLista (tLista *L){
        // Um loop percorre a lista enquanto houver elementos
        while (L->inicio != NULL){

            // Cria uma variável que recebe o início da lista
            tCarta *aux;
            aux = L->inicio;

            // Redefine o inicio como o próximo elemento
            L->inicio = aux->proximo;

            // Isola a auxiliar e libera sua memória
            aux->proximo = NULL;
            free(aux);
        }

        // Se a lista estiver vazia, libera a memória da lista
        if (listaVazia(L)){
            free(L);
            return 1;
        }
        return 0;
    };

    int insereFinal (tLista *L, tCarta *cartaVez){
        // Se a lista tiver vazia, irá inserir no início
        if (listaVazia(L)){

            // Aloca o novo elemento e verifica sucesso
            tCarta *novo = (tCarta*)malloc(sizeof(tCarta));
            if (novo == NULL) {
                printf("\n\n  Erro ao alocar memória para o jogo.");
                return 0;
            }

            // Define o novo elemento com os paramentros da carta que será inserida
            novo->numero = cartaVez->numero;
            novo->naipe = cartaVez->naipe;

            // Insere o elemento
            L->inicio = novo;
            novo->proximo = NULL;

            return 1;
        }

        // Se não, cria uma auxiliar e a define igual o início da lista
        tCarta *aux;
        aux = L->inicio;

        // Percorre toda a lista até chegar no final
        while (aux->proximo != NULL){
            aux = aux->proximo;
        }

        // Aloca memória para o novo elemento e verifica sucesso
        tCarta *novo = (tCarta*)malloc(sizeof(tCarta));
        if (novo == NULL) {
            printf("\n\n  Erro ao alocar memória para o jogo.");
            return 0;
        }

        // Define o novo elemento com os paramentros da carta que será inserida
        novo->numero = cartaVez->numero;
        novo->naipe = cartaVez->naipe;

        // Insere o elemento no final
        aux->proximo = novo;
        novo->proximo = NULL;

        return 1;
    };

    int tamanhoLista (tLista *L){
        // Se a lista estiver vazia, seu tamanho é zero
        if (listaVazia(L)){
            return 0;
        }

        // Cria uma auxiliar e a define igual ao início
        tCarta *aux;
        aux = L->inicio;

        // Cria uma cariável contadora
        int cont = 1;

        // Percorre toda a lista, incrementando o contador
        while (aux->proximo != NULL){
            cont++;
            aux = aux->proximo;
        }

        // Retorna o contador
        return cont;
    };

    int removePosicao (tLista *L, int posicao, tCarta *cartaVez){

        // Verifica se a lista está vazia e se a posição é inválida, retorna o erro
        if (listaVazia(L)){
            return 0;
        }
        if (tamanhoLista(L) < posicao){
            return 0;
        }

        // Cria duas variáveis auxiliares
        tCarta *aux;
        aux = L->inicio;
        tCarta *ant;

        // Percorre a lista até que aux seja a posição desejada
        for (int i = 1; i < posicao; i++){
            ant = aux;
            aux = aux->proximo;
        }

        // Retorna os valores da carta retirada
        cartaVez->numero = aux->numero;
        cartaVez->naipe = aux->naipe;

        // Faz a carta anterior 'pular' a auxiliar, removendo-a da lista
        ant->proximo = aux->proximo;
        aux->proximo = NULL;

        // Libera aux
        free(aux);

        return 1;
    };

    int removeInicio (tLista *L, tCarta *cartaRetirada){
        // Verifica se a lista está vazia, retorna o erro
        if (listaVazia(L)){
            return 0;
        }

        // Cria uma variável auxiliar e define-a como o início
        tCarta *aux;
        aux = L->inicio;

        // Retorna os valores da carta retirada
        cartaRetirada->numero = aux->numero;
        cartaRetirada->naipe = aux->naipe;

        // Faz com que o início seja o próximo valor da lista
        L->inicio = aux->proximo;

        // Isola aux e libera sua memória
        aux->proximo = NULL;
        free(aux);

        return 1;
    };

    int recuperarChave (tLista *L, tCarta cartaVez){
        // Verifica se a lista está vazia e retorna o erro
        if (listaVazia(L)){
            return 0;
        }

        // Cria uma auxiliar igual o início
        tCarta *aux;
        aux = L->inicio;

        // Cria uma variável para verificar a posição
        int posicao = 1;

        // Percorre todas as cartas até achar a correspondente, incrementa 'posição'
        while (aux != NULL){

            // Retorna a posição da carta certa
            if (aux->numero == cartaVez.numero){
                return posicao;
            }

            posicao++;
            aux = aux->proximo;
        }
        return 0;
    };

    void imprimeLista (tLista *L, int key){
        // Se a lista estvier vazia, imprime a informação de acordo com a chave passada
        if (listaVazia(L)){
            if (key == 7){
                printf("\n\n\n  O descarte terminou vazio!");
            }
            else {
                printf("\n  O descarte está vazio!");
            }
        }

        // Cria uma auxiliar
        tCarta *aux;
        aux = L->inicio;

        // Cria uma variável para capturar a posição da carta
        int i = 1;

        if (key == 7){
            printf("\n\n\n  O descarte terminou assim: ");

            // Percorre toda a lista, imprimindo as cartas
            while (aux->proximo != NULL) {
                imprimeCarta(i, aux->numero, aux->naipe, 7);
                aux = aux->proximo;
                i++;
            }

            // Imprime a última carta
            imprimeCarta(i, aux->numero, aux->naipe, 7);
        }
        else {
            printf("\n  |");
            printf("\n  |");
            printf("\n  |  O descarte é: ");

            // Percorre toda a lista, imprimindo as cartas
            while (aux->proximo != NULL) {
                imprimeCarta(i, aux->numero, aux->naipe, 0);
                aux = aux->proximo;
                i++;
            }

            // Imprime a última carta
            imprimeCarta(i, aux->numero, aux->naipe, 0);

            printf("\n  |");
            printf("\n  +---------------------------------+\n");

        }

    };

    void ordenaVetor(int *V, int tam){
        // Um algorítmo de ordenação por inserção

        // Cria as variáveis necessária
        int i, aux, j;

        // Percorre da segunda posição do vetor até a penúltima, pois os extremos já estão ordenados
        for (i = 1; i < tam; i++) {

            // Define 'aux' como a carta a ser ordenada e 'j' como a última posição ordenada
            aux = V[i];
            j = i - 1;

            // Verifica a posição correta de aux e insere
            while (j >= 0 && V[j] < aux) {
                V[j+1] = V[j];
                j--;
            }
            V[j+1] = aux;
        }
    };

    void ordenaMontes (tJogador *jogadores, int quantJogadores){

        // Percorre todos os jogadores
        for (int jogadorAtual = 0; jogadorAtual < quantJogadores; jogadorAtual++){

            // Só irá ordenar se o monte for maior que 1
            if (jogadores[jogadorAtual].quantCartas > 1){
                
                // Cria uma variável para capturar o tamanho do monte do jogador
                int quantCartas = jogadores[jogadorAtual].quantCartas;

                // Cria um vetor do tamanho do monte
                tCarta *monte;
                monte = (tCarta*)malloc(quantCartas * sizeof(tCarta));

                // Uma variável para percorrer o monte
                int i = 0;
                tCarta *aux;
                aux = jogadores[jogadorAtual].monte->topo;

                // Preeche o vetor como cada elemento do monte
                while (aux->proximo != NULL){
                    monte[i].numero = aux->numero;
                    monte[i].naipe = aux->naipe;
                    aux = aux->proximo;
                    i++;
                }
                monte[i].numero = aux->numero;
                monte[i].naipe = aux->naipe;

                // Utiliza um método de ordenação por inserção para ordenar o vetor em ordem decrescente
                for (i = 1; i < quantCartas; i++){
                    aux->numero = monte[i].numero;
                    aux->naipe = monte[i].naipe;

                    int j = i - 1;
                    while (aux->numero < monte[j].numero && j >= 0){
                        monte[j+1].numero = monte[j].numero;
                        monte[j+1].naipe = monte[j].naipe;
                        j--;
                    }
                    monte[j+1].numero = aux->numero;
                    monte[j+1].naipe = aux->naipe;
                }
                
                // Exclui o monte do jogador e cria outro, para evitar resíduos
                limparPilha(jogadores[jogadorAtual].monte);
                jogadores[jogadorAtual].monte = criaPilha();

                // Preenche o monte com os elementos do vetor, empilhando
                for (i = 0; i < quantCartas; i++){
                    int Yan = empilhaTopo(jogadores[jogadorAtual].monte, monte[i].numero, monte[i].naipe);
                }

                // Libera a memória alocada para o vetor
                free(monte);
            }
        }
    };

    void imprimeJogador (int id, tJogador *jogadores){
        // Imprime o nome do jogador e suas cartas
        printf("\n  Nome: %s", jogadores[id].nome);
        if (jogadores[id].quantCartas == 0){
            printf("\n  Quantidade de cartas no monte: Monte vazio!");
            return;
        }
        printf("\n  Quantidade de cartas no monte: %d", jogadores[id].quantCartas);
        imprimePilha(jogadores[id].monte, 7, 7);
    };

    int ganhadores(tJogador *jogadores, int quantJogadores, tLista *descarte){
        // Cria um vetor de maneira dinâmica, do tamanho da quantidade de jogadores e verifica sucesso
        int *ganhadores = (int*)malloc(quantJogadores * sizeof(int));
        if (ganhadores == NULL) {
            printf("\n\n  Erro ao alocar memória para o jogo.");
            return 0;
        }

        // Percorre todos os jogadores, definindo sua quantidade de cartas e armazenando em 'ganhadores'
        for (int i = 0; i < quantJogadores; i++){
            jogadores[i].quantCartas = tamanhoPilha(jogadores[i].monte);
            ganhadores[i] = jogadores[i].quantCartas;
        }

        // Ordena o monte em ordem descrescente
        ordenaMontes(jogadores, quantJogadores);

        // Ordena o vetor em ordem descrescente
        ordenaVetor (ganhadores, quantJogadores);

        int cont = 0;
        int maior = ganhadores[0];

        // Verifica se existe mais de um ganhador
        for (int i = 0; i < quantJogadores; i++){
            if (ganhadores[i] == maior){
                cont++;
            }
        }

        // Imrpime os vencedores e suas pilhas
        if (cont > 1){
            printf("\n\n  Os vencedores são:");
            for (int i = 0; i < quantJogadores; i++){
                if (jogadores[i].quantCartas == maior){
                    imprimeJogador(i, jogadores);
                }
                else {
                    break;
                }
            }
        }

        if (cont == 1){
            cont = 0;
        }

        // Imprime o resto dos jogadores
        for (int i = cont; i < quantJogadores; i++){
            int j = 0;
            while (ganhadores[i] != jogadores[j].quantCartas){
                j++;
            }
            printf("\n\n\n  %dº colocado:", i + 1);
            imprimeJogador(j, jogadores);
            jogadores[j].quantCartas = -1;
        }

        // Imprime o descarte
        imprimeLista(descarte, 7);

        // Libera o vetor auxiliar
        free(ganhadores);

        return 1;
    };

    int comparaCartaVez(tCarta *cartaVez, tLista *listaDescarte, tJogador *jogadores, int quantJogadores, int jogadorAtual) {
        // Cria um aux apontando pro descarte
        tCarta *aux = listaDescarte->inicio;

        int posicao = 1;

        // Verifica se a carta da vez é igual à alguma do descarte
        while (aux != NULL) {
            if (aux->numero == cartaVez->numero) {

                // Se sim , retorna a posicao da carta
                return posicao;
            }
            aux = aux->proximo;
            posicao++;
        }

        // Verifica se a carta da vez combina com o topo do monte de algum jogador
        for (int i = 0; i < quantJogadores; i++) {

            // Ignora o monte do jogador atual
            if (i != jogadorAtual) {

                // Se a carta da vez combina com o monte de outro jogador, retorna -1
                if (jogadores[i].monte->topo != NULL && cartaVez->numero == jogadores[i].monte->topo->numero) {
                    return i + 92;
                }
            }
        }

        return 0; // A carta da vez não combina com nenhuma carta na área de descarte ou no topo dos montes dos outros jogadores
    };

    int roubaDescarte(tCarta *cartaVez, tLista *listaDescarte, tJogador *jogadores, int posicao, int jogadorAtual) {
        // Se a carta for a primeira do descarte
        if(posicao == 1){

            // Cria uma variável auxiliar para receber esses valores
            tCarta cartaRetirada;

            // Remove a carta no início
            removeInicio (listaDescarte, &cartaRetirada);

            // Empilha ambas no monte do jogador
            empilhaTopo(jogadores[jogadorAtual].monte, cartaRetirada.numero, cartaRetirada.naipe);
            empilhaTopo(jogadores[jogadorAtual].monte, cartaVez->numero, cartaVez->naipe);

            return 1;
        }

        // Cria a auxiliar
        tCarta cartaRetirada;

        // Remove a carta na posição dela
        removePosicao(listaDescarte, posicao, &cartaRetirada);

        // Empilha ambas no monte do jogador
        empilhaTopo(jogadores[jogadorAtual].monte, cartaRetirada.numero, cartaRetirada.naipe);
        empilhaTopo(jogadores[jogadorAtual].monte, cartaVez->numero, cartaVez->naipe);

        return 1;
    };

    int roubaMonte(tCarta *cartaVez, int jogadorAtual, tJogador *jogadores, int quantJogadores, int donoMonte) {
        // Rouba o monte do jogador, empilhando as cartas no monte do jogador atual
        while (jogadores[donoMonte].monte->topo != NULL) {
            tCarta cartaRoubada;
            removeTopo(jogadores[donoMonte].monte, &cartaRoubada);
            empilhaTopo(jogadores[jogadorAtual].monte, cartaRoubada.numero, cartaRoubada.naipe);
        }

        // Coloca a carta da vez no topo do monte do jogador atual
        empilhaTopo(jogadores[jogadorAtual].monte, cartaVez->numero, cartaVez->naipe);

        return 1;
    };

    int empilhaMonte(tCarta *cartaVez, tJogador *jogadores, int jogadorAtual) {
        // Se a carta da vez for igual ao topo do monte, empilha
        if (jogadores[jogadorAtual].monte->topo != NULL &&  cartaVez->numero == jogadores[jogadorAtual].monte->topo->numero){
            empilhaTopo(jogadores[jogadorAtual].monte, cartaVez->numero, cartaVez->naipe);

            return 1;
        }

        // A carta da vez não combina com o topo do monte do jogador atual
        return 0; 
    };

    void descarta(tCarta *cartaVez, tLista *listaDescarte) {
        // Coloca a carta da vez na área de descarte
        insereFinal(listaDescarte, cartaVez);
    };
// Corpo das funções - Fim