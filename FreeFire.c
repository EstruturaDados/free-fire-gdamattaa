// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// =========================
// STRUCTS
// =========================

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =========================
// VARIÁVEIS GLOBAIS
// =========================

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Lista
No* mochilaLista = NULL;

// Contadores
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =========================
// FUNÇÕES AUXILIARES
// =========================

// Função para limpar buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// =========================
// ===== VETOR ============
// =========================

// ---------------------------------------------------------------------------
// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
// ---------------------------------------------------------------------------
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;

    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochilaVetor[totalItensVetor++] = novo;
}

// ---------------------------------------------------------------------------
// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
// ---------------------------------------------------------------------------
void listarVetor() {
    if (totalItensVetor == 0) {
        printf("Vetor vazio.\n");
        return;
    }

    for (int i = 0; i < totalItensVetor; i++) {
        printf("%s | %s | %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

// ---------------------------------------------------------------------------
// Busca sequencial pelo nome do item:
// Retorna posição ou -1 se não encontrado
// ---------------------------------------------------------------------------
int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// Ordenação por nome (Bubble Sort):
// --------------------------------------------------------------------------- 
void ordenarVetor() {
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome,
                       mochilaVetor[j+1].nome) > 0) {

                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome.\n");
}

//-------------------------------------------------------------------------
// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
//---------------------------------------------------------------------
int buscaBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;

    int inicio = 0;
    int fim = totalItensVetor - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}


// =========================
// ===== LSITA ============
// =========================

void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();

    novo->proximo = mochilaLista;
    mochilaLista = novo;
}


void listarLista() {
    if (mochilaLista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    No* atual = mochilaLista;

    while (atual != NULL) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}


No* buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;

    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;

        atual = atual->proximo;
    }

    return NULL;
}

// =========================
// ===== MAIN =============
// =========================
// ---------------------------------------------------------------------------
// Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

// A estrutura switch trata cada opção chamando a função correspondente.
// A ordenação e busca binária exigem que os dados estejam bem organizados.
// ---------------------------------------------------------------------------
int main() {

    int estrutura;
    int opcao;

    printf("Escolha a estrutura:\n");
    printf("1 - Vetor\n");
    printf("2 - Lista Encadeada\n");
    scanf("%d", &estrutura);
    limparBuffer();

    do {
        printf("\n1 - Inserir\n");
        printf("2 - Listar\n");
        printf("3 - Buscar (Sequencial)\n");
        if (estrutura == 1)
            printf("4 - Ordenar + Busca Binaria\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (estrutura == 1) {

            switch (opcao) {
                case 1:
                    inserirItemVetor();
                    break;

                case 2:
                    listarVetor();
                    break;

                case 3: {
                    char nome[30];
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    int pos = buscarSequencialVetor(nome);
                    printf("Comparações: %d\n", comparacoesSequencial);

                    if (pos != -1)
                        printf("Encontrado!\n");
                    else
                        printf("Não encontrado.\n");
                    break;
                }

                case 4: {
                    if (totalItensVetor == 0) {
                        printf("Vetor vazio.\n");
                        break;
                    }

                    ordenarVetor();

                    char nome[30];
                    printf("Nome para busca binaria: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    int pos = buscaBinariaVetor(nome);
                    printf("Comparações (Binaria): %d\n", comparacoesBinaria);

                    if (pos != -1)
                        printf("Encontrado!\n");
                    else
                        printf("Não encontrado.\n");
                    break;
                }

                case 0:
                    printf("Encerrando...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
            }

        } else {

            switch (opcao) {
                case 1:
                    inserirItemLista();
                    break;

                case 2:
                    listarLista();
                    break;

                case 3: {
                    char nome[30];
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    No* encontrado = buscarSequencialLista(nome);
                    printf("Comparações: %d\n", comparacoesSequencial);

                    if (encontrado)
                        printf("Encontrado!\n");
                    else
                        printf("Não encontrado.\n");
                    break;
                }

                case 0:
                    printf("Encerrando...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
            }
        }

    } while (opcao != 0);

    return 0;
}