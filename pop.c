/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "pop.h"

Boolean pop_init(Pop_list **pop){
	/* TO DO */
	*pop = safeMalloc(sizeof(Pop_list));
	(*pop)->head = NULL;
	(*pop)-> count = 0;
	return FALSE;
}

void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef){
	/* TO DO */
	p->create_rand_chrom = cf;
	p->mutate_gene = mf;
	p->crossover_genes = cof;
	p->evaluate_fn = ef;
}

void pop_print_fittest(Pop_list *p){
	/* TO DO */
}

/* TO DO - other functions as appropriate */
Pop_node *create_node(Pop_list *pop, int numAlleles){
	Pop_node *newNode = safeMalloc(sizeof(Pop_node));
	newNode->gene = gene_create_rand_gene(numAlleles, pop->create_rand_chrom);
	newNode->next = NULL;
	return newNode;
}

void add_node(Pop_list *pop, Pop_node *node){
	if (pop->head == NULL){
		pop->head = node;
		pop->count++;
	}
	else{
		node->next = pop->head;
		pop->head = node;
	}

}

void create_pop(Pop_list *pop, int popSize, int geneWidth){
	int counter;
	for (counter = 0; counter <popSize; counter++){
		add_node(pop, create_node(pop, geneWidth));
	}
}

void print_pop_list(Pop_list *popList){
    Pop_node *current = popList->head;
    if( current == NULL){
        printf("null list");
        return;
    }
    while(current != NULL){
        gene_print(current->gene);
        current = current->next;
    }
}
