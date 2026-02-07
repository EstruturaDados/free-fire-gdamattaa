// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// ---------------------------------------------------------------------------
// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
// ---------------------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ---------------------------------------------------------------------------
// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
// ---------------------------------------------------------------------------
Item mochila[MAX_ITENS];
int totalItens = 0;

// ---------------------------------------------------------------------------
// Função para limpar buffer do teclado
// ---------------------------------------------------------------------------
void limparBuffer() {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}

// ---------------------------------------------------------------------------
// Busca sequencial pelo nome do item:
// Retorna posição ou -1 se não encontrado
// ---------------------------------------------------------------------------
int buscarItem(char nome[]) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
// ---------------------------------------------------------------------------
void listarItens() {
    printf("\n========= ITENS NA MOCHILA =========\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("-----------------------------\n");
    }
}

// ---------------------------------------------------------------------------
// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
// ---------------------------------------------------------------------------
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
}

Item novo;

    printf("\nNome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo (arma, munição, cura, ferramenta...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochila[totalItens++] = novo;

    printf("Item adicionado com sucesso!\n");
    listarItens();
}

// ---------------------------------------------------------------------------
// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
// ---------------------------------------------------------------------------
void removerItem() {
    char nome[30];

    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int pos = buscarItem(nome);

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = pos; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("Item removido com sucesso!\n");
    listarItens();
}

// ---------------------------------------------------------------------------
// Mostrar dados de um item específico
// ---------------------------------------------------------------------------
void procurarItem() {
    char nome[30];

    printf("Digite o nome do item para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int pos = buscarItem(nome);

    if (pos == -1) {
        printf("Item não encontrado.\n");
        return;
}

    printf("\nItem encontrado!\n");
    printf("Nome: %s\n", mochila[pos].nome);
    printf("Tipo: %s\n", mochila[pos].tipo);
    printf("Quantidade: %d\n", mochila[pos].quantidade);
}

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
    int opcao;

    do {
        printf("\n=========== INVENTÁRIO ===========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                procurarItem();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
// ---------------------------------------------------------------------------

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
