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

void normalise_pop_fitness(Pop_list *pop, InVTable *invTab){
	Pop_node *pointer = pop->head;
	double totalFitness = 0;
	/*Calculate total fitness*/
	while ( pointer != NULL) {
		gene_calc_fitness(pointer->gene, pop->evaluate_fn, invTab);
		totalFitness += pointer->gene->fitness;
		pointer = pointer->next;
	}

	/*Normalising population fitness*/
	pointer = pop->head;
	while ( pointer != NULL ) {
		gene_normalise_fitness(pointer->gene, totalFitness);
		pointer = pointer->next;
	}
}

Pop_node *create_node(Pop_list *pop, int numAlleles){
	Pop_node *newNode = safeMalloc(sizeof(Pop_node));
	newNode->gene = gene_create_rand_gene(numAlleles, pop->create_rand_chrom);
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
		pop->count++;
	}
}

void create_first_gen(Pop_list *pop, int popSize, int geneWidth, InVTable *invTab){
	int counter;
	for (counter = 0; counter <popSize; counter++){
		add_node(pop, create_node(pop, geneWidth));
	}
	/*Normalise pop fitness */
	normalise_pop_fitness(pop, invTab);
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
	Pop_node *pointer = pop->head;

	while (pointer->next != NULL){
		pop->head = pointer->next;
		gene_free(pointer->gene);
		free(pointer);
		pointer = pop->head;
	}
	gene_free(pointer->gene);
	free(pointer);
	free(pop);
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

void newGeneration(Pop_list *parent_gen, Pop_list *child_gen, InVTable *invTab){
	Gene *geneZ = NULL;
	Pop_node *fittest = safeMalloc(sizeof(Pop_node));
	int counter = 1;
	/*Duplicate population size*/
	child_gen->count = parent_gen->count;
	/*Ensuring the fittest survive from parent_gen*/
	fittest->gene = copy_gene(parent_gen->head->gene);
	fittest->next = NULL;
	child_gen->head = fittest;
	while(counter<child_gen->count){
		/*Find first random gene through roulette*/
		Gene *geneX = roulette_gene(parent_gen);
		/*If percentage is 5% or below, mutate it*/
		if(randomPercentage() <= 5){
			geneZ = parent_gen->mutate_gene(geneX);
			increase_pop(child_gen, geneZ, invTab);
		}
		else{
			/*Find second random gene through roulette*/
			Gene *geneY = roulette_gene(parent_gen);
			/*Crossoever geneX and geneY */
			geneZ = parent_gen->crossover_genes(geneX,geneY);
			increase_pop(child_gen, geneZ, invTab);
		}
		counter ++;
	}
	normalise_pop_fitness(child_gen, invTab);
	sort_pop(child_gen);
	print_pop_list(child_gen);
}

void increase_pop(Pop_list *pop, Gene *newGene, InVTable *invTab){
	Pop_node *newNode = safeMalloc(sizeof(Pop_node));
	newNode->gene = newGene;
	newNode->next = pop->head;
	pop->head = newNode;
}

Gene *copy_gene(Gene *gene){
	Gene *copy = safeMalloc(sizeof(Gene));
	int num_alleles = gene->num_alleles;
	copy->num_alleles = gene->num_alleles;
	copy->chromosome = safeMalloc(sizeof(int)*num_alleles);
	memcpy(copy->chromosome,gene->chromosome,sizeof(int)*num_alleles);
	copy->fitness = gene->raw_score = 0;
	return copy;
}

Gene *roulette_gene(Pop_list *pop){
	Pop_node *pointer = pop->head;
	double randomFitness = MAX_RANGE * (((double)rand()) / (double)((unsigned)RAND_MAX));
	double fitnessSum = 0.00;
	while (pointer!=NULL){
		fitnessSum += gene_get_fitness(pointer->gene);
		if (fitnessSum >= randomFitness){
			Gene *selection = copy_gene(pointer->gene);
			return selection;
		}
		else
			pointer = pointer->next;
	}
	return NULL;
}

void switch_current_pop(Pop_list *currentPop, Pop_list *nextPop){
	Pop_node *tmpHead = currentPop->head;
	currentPop->head = nextPop->head;
	nextPop->head = tmpHead;
}
