#include <stdio.h>
#include <stdlib.h>
#include "complementar.h"

void trocar(int *vetor, int a, int b) {
        int aux = vetor[a];
        vetor[a] = vetor[b];
        vetor[b] = aux;
}

void printVetor(int *vetor, int b) {
	for (int i = 0; i < b; i++)
		printf("%d ", vetor[i]);
	printf("\n");
}

int nodoEsq(int idxNodo) { return (idxNodo << 1) + 1; }

int nodoDir(int idxNodo) { return (idxNodo << 1) + 2; }

void maxHeapify(int *heap, int idxNodo, int tam, unsigned long *comps) {
        int esq = nodoEsq(idxNodo);
        int dir = nodoDir(idxNodo);
        int max;
        if (esq <= tam && heap[esq] > heap[idxNodo])
                max = esq;
        else
                max = idxNodo;
        if (dir <= tam && heap[dir] > heap[max])
                max = dir;
	*comps = *comps + 2;
        if (max != idxNodo) {
                trocar(heap, idxNodo, max);
                maxHeapify(heap, max, tam, comps);
        }
}

void constroiMaxHeap(int *vetor, int n, unsigned long *comps) {
	for (int i = (n / 2); i >= 0; i--)
		maxHeapify(vetor, i, n, comps);
}

void hpSort(int *vetor, int n, unsigned long *comps) {
	constroiMaxHeap(vetor, n, comps);
	for (int i = n; i >= 1; i--) {
		trocar(vetor, 0, i);
		maxHeapify(vetor, 0, i - 1, comps);
	}
}

int particaoQS(int *vetor, int a, int b, unsigned long *comps) {
        if (a >= b)
                return 0;
        int pivo = vetor[b - 1];
        int novoPivo = a;
        for (int i = a; i < b - 1; i++) {
                (*comps)++;
		if (vetor[i] <= pivo) {
                        trocar(vetor, novoPivo, i);
                        novoPivo++;
                }
	}
        trocar(vetor, novoPivo, b - 1);

        return novoPivo;
}

void qkSort(int *vetor, int a, int b, unsigned long *comps) {
	if (a >= b)
		return;
	int idxPivo = particaoQS(vetor, a, b, comps);
	qkSort(vetor, a, idxPivo, comps);
	qkSort(vetor, idxPivo + 1, b, comps);
}

void merge(int *vetor, int a, int b, int meio, unsigned long *comps) {
	if (a >= b)
		return;
	int i, j, k, *vetorAux;
	vetorAux = (int *)malloc(b * sizeof(int));
        i = a;
	j = meio + 1;
	k = a;
	while (i < meio && j < b) {
		(*comps)++;
		if (vetor[i] <= vetor[j]) {
			vetorAux[k] = vetor[i];
			i++;
			k++;
		} else {
			vetorAux[k] = vetor[j];
			j++;
			k++;
		}
	}
	while (i <= meio) {
		vetorAux[k] = vetor[i];
		i++;
		k++;
	}
	while (j < b) {
		vetorAux[k] = vetor[j];
		j++;
		k++;
	}
	for (int p = a; p < b; p++)
		vetor[p] = vetorAux[p];
        free(vetorAux);
        vetorAux = NULL;
}

void mrgSort(int *vetor, int a, int b, unsigned long *comps) {
        if (a >= b)
                return;
        int meio = (a + b) / 2;
        mrgSort(vetor, a, meio, comps);
        mrgSort(vetor, meio + 1, b, comps);
        merge(vetor, a, b, meio, comps);
}