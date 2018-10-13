/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "pop.h"

Boolean pop_init(Pop_list **pop)
{
	/* TO DO */
	*pop = safeMalloc(sizeof(Pop_list));
	(*pop)->head = NULL;
	(*pop)-> count = 0;
	return FALSE;
}

void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef)
{
	/* TO DO */
	p->create_rand_chrom = cf;
	p->mutate_gene = mf;
	p->crossover_genes = cof;
	p->evaluate_fn = ef;
}

void pop_print_fittest(Pop_list *p)
{
	/* TO DO */
	gene_print(p->head->gene);
}

/* TO DO - other functions as appropriate */

Pop_node *create_node(Pop_list *pop, int numAlleles)
{
	Pop_node *newNode = safeMalloc(sizeof(Pop_node));
	newNode->gene = gene_create_rand_gene(numAlleles, pop->create_rand_chrom);
	newNode->next = NULL;
	return newNode;
}

void add_node(Pop_list *pop, Pop_node *newNode)
{
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

void create_first_gen(Pop_list *pop, int popSize, int geneWidth, InVTable *invTab)
{
	int counter;
	for (counter = 0; counter <popSize; counter++){
		add_node(pop, create_node(pop, geneWidth));
	}
}

void new_generation(Pop_list *parent_gen, Pop_list *child_gen)
{
	Gene *geneX, *geneY, *geneZ;
	int counter = 1;
	Pop_node *fittest = safeMalloc(sizeof(Pop_node));
	fittest->next = NULL;

	/*Ensuring the fittest survive from parent_gen*/
	fittest->gene = copy_gene(parent_gen->head->gene);
	add_node(child_gen,fittest);

	while(counter<parent_gen->count){

		/*Find first random gene through roulette selection*/
		geneX = roulette_gene(parent_gen);

		/*If percentage is 5% or below, mutate it*/
		if(randomPercentage() <= 5){
			geneZ = parent_gen->mutate_gene(geneX);
			increase_pop(child_gen, geneZ);
		}
		else{

			/*Find second random gene through roulette selection*/
			geneY = roulette_gene(parent_gen);

			/*Crossoever geneX and geneY */
			geneZ = parent_gen->crossover_genes(geneX,geneY);
			increase_pop(child_gen, geneZ);
		}
		counter ++;
	}
}

void increase_pop(Pop_list *pop, Gene *newGene)
{
	Pop_node *newNode = safeMalloc(sizeof(Pop_node));
	newNode->gene = newGene;
 	add_node(pop,newNode);
}

Gene *roulette_gene(Pop_list *pop)
{
	Pop_node *pointer = pop->head;
	double randomFitness = MAX_RANGE * (((double)rand()) / (double)((unsigned)RAND_MAX));
	double fitnessSum = 0.00;

	while (pointer!=NULL){
		fitnessSum += gene_get_fitness(pointer->gene);
		if (fitnessSum >= randomFitness){
			return pointer->gene;
		}
		else
			pointer = pointer->next;
	}
	return NULL;
}

void normalise_pop_fitness(Pop_list *pop, InVTable *invTab)
{
	Pop_node *pointer = pop->head;
	double totalFitness = 0;

	/*Calculate total fitness*/
	while ( pointer != NULL) {

		/*Calculating fitness of every gene*/
		gene_calc_fitness(pointer->gene, pop->evaluate_fn, invTab);
		totalFitness += pointer->gene->fitness;
		pointer = pointer->next;
	}

	/*Normalising population fitness*/
	pointer = pop->head;
	while ( pointer != NULL ) {

		/*Normalising fitness of every gene*/
		gene_normalise_fitness(pointer->gene, totalFitness);
		pointer = pointer->next;
	}
}

void sort_pop(Pop_list *pop)
{
	Pop_node *pointer = pop->head;
	Boolean sort = FALSE;

	/*Utilizing bubble-sort*/
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

Gene *copy_gene(Gene *gene)
{
	Gene *copy = safeMalloc(sizeof(Gene));
	int num_alleles = gene->num_alleles;
	copy->num_alleles = gene->num_alleles;
	copy->chromosome = safeMalloc(sizeof(int*)*num_alleles);

	/*Making sure to copy the chromosome to the gene copy*/
	memcpy(copy->chromosome,gene->chromosome,sizeof(int)*num_alleles);
	copy->fitness = gene->raw_score = 0;
	return copy;
}

void switch_current_pop(Pop_list *currentPop, Pop_list *nextPop)
{
	Pop_node *tmpHead = currentPop->head;
	currentPop->head = nextPop->head;
	nextPop->head = tmpHead;
}

void print_pop_list(Pop_list *popList)
{
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

void free_Pop(Pop_list *pop)
{
	Pop_node *pointer = pop->head;

	while (pointer != NULL){
		pop->head = pointer->next;
		gene_free(pointer->gene);
		free(pointer);
		pointer = pop->head;
	}
	free(pop);
}
