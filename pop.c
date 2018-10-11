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
	gene_print(p->head->gene);
}

/* TO DO - other functions as appropriate */

void normalise_pop_fitness(Pop_list *pop){
	Pop_node *pointer = pop->head;
	double totalFitness = 0, testfit = 0;
	int j = 1;
	int i = 1;
	/*Calculate total fitness*/
	while (pointer->next != NULL) {
		printf("1TEST %d\n",j );
		j++;
		totalFitness += pointer->gene->fitness;
		pointer = pointer->next;
	}
	printf("1TEST %d\n\n",j );
	totalFitness += pointer->gene->fitness;
	/*Normalising population fitness*/

	pointer = pop->head;
	while (pointer->next != NULL) {
		printf("2TEST %d\n",i );
		i++;
		gene_normalise_fitness(pointer->gene, totalFitness);

		testfit += pointer->gene->fitness;

		pointer = pointer->next;
	}
	printf("2TEST %d\n\n",i );
	gene_normalise_fitness(pointer->gene, totalFitness);

	testfit += pointer->gene->fitness;
	printf("TOTAL FITNESS: %f\n", testfit);
}

Pop_node *create_node(Pop_list *pop, int numAlleles, InVTable *invTab){
	Pop_node *newNode = safeMalloc(sizeof(Pop_node));
	newNode->gene = gene_create_rand_gene(numAlleles, pop->create_rand_chrom);
	gene_calc_fitness(newNode->gene, pop->evaluate_fn, invTab);
	newNode->next = NULL;
	return newNode;
}

void add_node(Pop_list *pop, Pop_node *newNode){
	if (pop->head == NULL){
		pop->head = newNode;
		pop->count++;
	}
	else{
		newNode->next = pop->head;
		pop->head = newNode;
	}

}

void create_pop(Pop_list *pop, int popSize, int geneWidth, InVTable *invTab){
	int counter;
	for (counter = 0; counter <popSize; counter++){
		add_node(pop, create_node(pop, geneWidth, invTab));
	}
	/*Sort the pop upon creation*/
	sort_pop(pop);
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

void free_Pop(Pop_list *pop){
	Pop_node *head = pop->head;
	Pop_node *pointer = pop->head;
	int i = 1;

	while (head->next != NULL){
		printf("%d\n",i );

		pointer = head->next;
		free(head->gene);
		free(head);
		head = pointer;
		i++;
	}
	printf("%d\n",i );
	free(pointer->gene);
	free(pointer);
}

void sort_pop(Pop_list *pop){
	Pop_node *pointer = pop->head;
	Boolean sort = FALSE;

	while(sort==FALSE){
		sort = TRUE;
		while(pointer->next != NULL){
			double fitness1, fitness2;
			fitness1 = gene_get_fitness(pointer->gene);
			fitness2 = gene_get_fitness(pointer->next->gene);
			if(fitness1 < fitness2){
				Gene *tmpGene = pointer->gene;
				pointer->gene = pointer->next->gene;
				pointer->next->gene = tmpGene;
				sort = FALSE;
			}
			else{
				pointer = pointer->next;
			}
		}
		pointer = pop->head;
	}
}
