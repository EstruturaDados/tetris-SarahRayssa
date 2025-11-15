#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

typedef struct {
    char tipo;
    int id;
} Peca;

#define MAX_FILA 5

typedef struct {
    Peca pecas[MAX_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

#define MAX_PILHA 3
Peca pilha[MAX_PILHA];
int topo = -1;

// Controle de IDs
int proximoID = 1;


// ============================
//        FILA - FUNÇÕES
// ============================

void inicializarFila() {
    frente = 0;
    tras = 0;
    quantidadeFila = 0;
}

bool filaVazia() {
    return quantidadeFila == 0;
}

bool filaCheia() {
    return quantidadeFila == MAX_FILA;
}

char gerarTipoAleatorio() {
    char tipos[] = {'I', 'L', 'O', 'T', 'Z'};
    return tipos[rand() % 5];
}

Peca gerarPeca() {
    Peca p;
    p.tipo = gerarTipoAleatorio();
    p.id = proximoID++;
    return p;
}

void enqueue(Peca p) {
    if (filaCheia()) {
        printf("Fila cheia! Nao foi possivel adicionar.\n");
        return;
    }
    fila[tras] = p;
    tras = (tras + 1) % MAX_FILA;
    quantidadeFila++;
}

Peca dequeue() {
    if (filaVazia()) {
        printf("Fila vazia!\n");
        Peca vazia = {'-', -1};
        return vazia;
    }
    Peca removida = fila[frente];
    frente = (frente + 1) % MAX_FILA;
    quantidadeFila--;
    return removida;
}

void mostrarFila() {
    printf("\nFila de Pecas Futuras: ");
    if (filaVazia()) {
        printf("[vazio]\n");
        return;
    }

    printf("\n");
    int indice = frente;
    for (int i = 0; i < quantidadeFila; i++) {
        printf("(%c %d) ", fila[indice].tipo, fila[indice].id);
        indice = (indice + 1) % MAX_FILA;
    }
    printf("\n");
}

// ============================
//        PILHA - FUNÇÕES
// ============================

void inicializarPilha() {
    topo = -1;
}

bool pilhaVazia() {
    return topo == -1;
}

bool pilhaCheia() {
    return topo == MAX_PILHA - 1;
}

void push(Peca p) {
    if (pilhaCheia()) {
        printf("Pilha cheia! Nao foi possivel adicionar.\n");
        return;
    }
    pilha[++topo] = p;
}

Peca pop() {
    if (pilhaVazia()) {
        printf("Pilha vazia!\n");
        Peca vazia = {'-', -1};
        return vazia;
    }
    return pilha[topo--];
}

void mostrarPilha() {
    printf("\nPilha de Reserva: ");
    if (pilhaVazia()) {
        printf("[vazia]\n");
        return;
    }

    printf("\n");
    for (int i = topo; i >= 0; i--) {
        printf("(%c %d) ", pilha[i].tipo, pilha[i].id);
    }
    printf("\n");
}

// ============================
//      TROCAS (NÍVEL MESTRE)
// ============================

// Troca a peça da frente da fila com o topo da pilha
void trocarFrenteComTopo() {
    if (filaVazia()) {
        printf("Nao ha pecas na fila.\n");
        return;
    }
    if (pilhaVazia()) {
        printf("Nao ha pecas na pilha.\n");
        return;
    }

    int indiceFrente = frente;
    Peca temp = fila[indiceFrente];
    fila[indiceFrente] = pilha[topo];
    pilha[topo] = temp;

    printf("Troca realizada com sucesso!\n");
}

// Troca 3 primeiros da fila com os 3 da pilha
void trocar3Com3() {
    if (quantidadeFila < 3) {
        printf("A fila precisa ter pelo menos 3 pecas.\n");
        return;
    }
    if (topo != 2) { // topo = 2 significa exatamente 3 peças
        printf("A pilha precisa ter exatamente 3 pecas.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int indiceFila = (frente + i) % MAX_FILA;

        Peca temp = fila[indiceFila];
        fila[indiceFila] = pilha[i];
        pilha[i] = temp;
    }

    printf("As 3 pecas da fila foram trocadas com as 3 da pilha!\n");
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

int main() {
    srand(time(NULL));

    inicializarFila();
    inicializarPilha();

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;

    do {
        printf("\n\n===== TETRIS STACK =====\n");
        mostrarFila();
        mostrarPilha();

        printf("\nMenu:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Enviar peca da fila para a pilha\n");
        printf("3 - Usar peca da pilha (pop)\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar 3 da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca jogada = dequeue();
                if (jogada.id != -1) {
                    printf("Voce jogou a peca (%c %d)\n", jogada.tipo, jogada.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 2: {
                if (filaVazia()) {
                    printf("Fila vazia, nao ha peca para enviar.\n");
                    break;
                }
                Peca frentePeca = dequeue();
                push(frentePeca);
                enqueue(gerarPeca());
                printf("Peca enviada para a reserva!\n");
                break;
            }

            case 3: {
                Peca usada = pop();
                if (usada.id != -1)
                    printf("Voce usou a peca (%c %d)\n", usada.tipo, usada.id);
                break;
            }

            case 4:
                trocarFrenteComTopo();
                break;

            case 5:
                trocar3Com3();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

    return 0;
}
