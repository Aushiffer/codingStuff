#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"

int main() {
	struct pilha p = createStack();
	struct fila f = createQueue();
	int valSearch;
	printf("Entre com um valor para ser buscado na pilha e na fila: ");
	scanf("%d", &valSearch);
	push(&p, 10);
	push(&p, 15);
	push(&p, 5);
	enqueue(&f, 5);
	enqueue(&f, 10);
	enqueue(&f, 15);
	dequeue(&f);
	dequeue(&f);
	pop(&p);
	pop(&p);
	printf("item (topo) e topo da pilha: %d %d\n", p.itens[p.top], p.top);
	printf("primeiro e último da fila: %d %d (índices %d e %d)\n", f.itens[f.first], f.itens[f.last], f.first, f.last);
	int posStack = searchStack(p, valSearch);
	int posQueue = searchQueue(f, valSearch);
	printf("Posição do elemento %d na pilha: %d\n", valSearch, posStack);
	printf("Posição do elemento %d na fila: %d\n", valSearch, posQueue);
	if (posStack == -1)
		printf("%d n está na pilha\n", valSearch);
	if (posQueue == -1)
		printf("%d n está na fila\n", valSearch);
	printf("A fila tem %d elementos\n", countItensQueue(f));

	return 0;	
}
