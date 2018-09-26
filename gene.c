/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

int * create_pcbmill_chrom(int numAlleles){
	int counter, *chromosome, randomValue;

	/*Checker*/
	if ((chromosome = malloc(sizeof(int) * numAlleles))==NULL)
	return NULL;

	for (counter = 0; counter < numAlleles; counter++){
	}


	return chromosome;
}

int * create_minfn_chrom(int numAlleles){
	int counter, *chromosome;

	/*Checker*/
	if ((chromosome = malloc(sizeof(int) * numAlleles))==NULL)
	return NULL;

	for (counter = 0; counter < numAlleles; counter ++ )
	{
		chromosome[counter] = rand() % MINFN_MAX;
	}
	return chromosome;
}

Gene * mutate_pcbmill(Gene *g){
	/* TO DO */
	return NULL;
}

Gene * mutate_minfn(Gene *g){
	/* TO DO */
	Gene *mutated_gene;
	int mutatationPoint, counter=0;

	#ifdef DEBUG
	mutatationPoint = 2;
	#else
	mutatationPoint = rand() % g->num_alleles;
	#endif

	/*Checker*/
	if ((mutated_gene = malloc(sizeof(Gene))) == NULL)
	return NULL;
	if ((mutated_gene->chromosome = malloc(sizeof(int) * g->num_alleles)) == NULL)
	return NULL;

	while (counter< g->num_alleles) {
		mutated_gene->chromosome[counter] = g->chromosome[counter];
		counter ++;
	}
	mutated_gene->num_alleles = g->num_alleles;
	mutated_gene->raw_score = mutated_gene->fitness = 0;

	mutated_gene->chromosome[mutatationPoint] = rand() % MINFN_MAX;

	return mutated_gene;
}

Gene * crossover_pcbmill(Gene *g1, Gene *g2){
	/* TO DO */
	return NULL;
}

Gene * crossover_minfn(Gene *g1, Gene *g2){
	int crossoverPoint, debugPoint;
	Gene *child_gene;

	/*Debug purposes*/
	#ifdef DEBUG
	debugPoint = 3;
	#else
	debugPoint = rand() % g1->num_alleles;
	#endif

	/*Checker*/
	if ((child_gene = malloc(sizeof(Gene)))== NULL)
	return NULL;
	if ((child_gene->chromosome = malloc(sizeof(int) * g1->num_alleles))== NULL)
	return NULL;

	/*Creating child gene*/
	child_gene->chromosome = g1->chromosome;
	for (crossoverPoint = debugPoint; crossoverPoint < g1->num_alleles; crossoverPoint++){
		child_gene->chromosome[crossoverPoint] = g2->chromosome[crossoverPoint];
	}
	child_gene->num_alleles = g1->num_alleles;
	child_gene->raw_score = child_gene->fitness = 0;

	return child_gene;
}

double eval_pcbmill(InVTable *invt, Gene *gene){
	/* TO DO */
	return 0.0;
}

double eval_minfn(InVTable *invt, Gene *gene){
	/* TO DO */
	return 0.0;
}

Gene * gene_create_rand_gene(int numAlleles, CreateFn create_chrom){
	/* TO DO */
	Gene *random_gene;

	/*Checker*/
	if ((random_gene = malloc(sizeof(Gene)))== NULL)
	return NULL;
	if ((random_gene->chromosome = malloc(sizeof(int) * numAlleles))== NULL)
	return NULL;

	/*Create Random gene*/
	random_gene->chromosome = create_chrom(numAlleles);
	random_gene->num_alleles = numAlleles;
	random_gene->raw_score = random_gene->fitness = 0;

	return random_gene;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab){
	/* TO DO */
}

void gene_normalise_fitness(Gene *gene, double total_fitness){
	/* TO DO */
}

void gene_free(Gene *gene){
	free(gene->chromosome);
	free(gene);
}

double gene_get_fitness(Gene *gene){
	/* TO DO */
	return 0.0;
}

void gene_print(Gene *gene) {
	/* TO DO */
	int counter;

	printf("Chrom: ");
	for (counter = 0; counter < gene->num_alleles; counter++){
		if (counter < ((gene->num_alleles) - 1))
			printf("%d, ", gene->chromosome[counter]);
		else
		printf("%d ", gene->chromosome[counter]);
	}
	printf("fit: %.3f, raw: %.3f \n", gene->fitness, gene->raw_score);
}
