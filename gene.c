/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

int * create_pcbmill_chrom(int numAlleles){
	int counter, *chromosome, randomValue;

	/*Memory Allocation*/
	/*if ((chromosome = malloc(sizeof(int) * numAlleles))==NULL)
	return NULL;*/
	chromosome = safeMalloc(sizeof(int) * numAlleles);

	for (counter = 0; counter < numAlleles; counter++){
		do {
			randomValue = rand() % numAlleles;
		} while( checkValue(chromosome, counter, randomValue)==FALSE );
		chromosome[counter] = randomValue;
	}
	return chromosome;
}

int * create_minfn_chrom(int numAlleles){
	int counter, *chromosome;

	/*Memory Allocation*/
	/*if ((chromosome = malloc(sizeof(int) * numAlleles))==NULL)
	return NULL;*/
	chromosome = safeMalloc(sizeof(int) * numAlleles);

	for (counter = 0; counter < numAlleles; counter ++ )
	{
		chromosome[counter] = rand() % MINFN_MAX;
	}
	return chromosome;
}

Gene * mutate_pcbmill(Gene *g){
	/* TO DO */
	Gene *mutated_gene;
	int mutationPoint1, mutationPoint2, counter=0, tempPoint;

	#ifdef DEBUG
	mutationPoint1 = 2;
	mutationPoint2 = 4;
	#else
	mutationPoint1 = rand() % g->num_alleles;
	do {
		mutationPoint2 = rand() % g->num_alleles;
	} while(mutationPoint2 == mutationPoint1);
	#endif
	printf(" index1: %d index2: %d\n", mutationPoint1, mutationPoint2 );

	/*Memory Allocation*/
	mutated_gene = safeMalloc(sizeof(Gene));
	mutated_gene->chromosome = safeMalloc(sizeof(int) * g->num_alleles);

	/*Copying gene before mutation*/
	while (counter < g->num_alleles) {
		mutated_gene->chromosome[counter] = g->chromosome[counter];
		counter ++;
	}
	mutated_gene->num_alleles = g->num_alleles;
	mutated_gene->raw_score = mutated_gene->fitness = 0;

	/*Mutating the gene*/
	tempPoint = mutated_gene->chromosome[mutationPoint1];
	mutated_gene->chromosome[mutationPoint1] = mutated_gene->chromosome[mutationPoint2];
	mutated_gene->chromosome[mutationPoint2] = tempPoint;

	return mutated_gene;
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
	printf(" index: %d\n", mutatationPoint );

	/*Memory Allocation*/
	/*if ((mutated_gene = malloc(sizeof(Gene))) == NULL)
	return NULL;
	if ((mutated_gene->chromosome = malloc(sizeof(int) * g->num_alleles)) == NULL)
	return NULL;*/
	mutated_gene = safeMalloc(sizeof(Gene));
	mutated_gene->chromosome = safeMalloc(sizeof(int) * g->num_alleles);

	while (counter < g->num_alleles) {
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
	int crossoverPoint, Point;
	Gene *child_gene;

	/*Debug purposes*/
	#ifdef DEBUG
	Point = 3;
	#else
	Point = rand() % g1->num_alleles;
	#endif
	printf(" index: %d\n", Point-1 );

	/*Memory Allocation*/
	/*if ((child_gene = malloc(sizeof(Gene)))== NULL)
	return NULL;
	if ((child_gene->chromosome = malloc(sizeof(int) * g1->num_alleles))== NULL)
	return NULL;*/
	child_gene = safeMalloc(sizeof(Gene));
	child_gene->chromosome = safeMalloc(sizeof(int) * g1->num_alleles);

	/*Creating child gene*/
	child_gene->chromosome = g1->chromosome;
	for (crossoverPoint = Point; crossoverPoint < g1->num_alleles; crossoverPoint++){
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

	/*Memory Allocation*/
	/*if ((random_gene = malloc(sizeof(Gene)))== NULL)
	return NULL;
	if ((random_gene->chromosome = malloc(sizeof(int) * numAlleles))== NULL)
	return NULL;*/
	random_gene = safeMalloc(sizeof(Gene));
	random_gene->chromosome = safeMalloc(sizeof(int) * numAlleles);

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

Boolean checkValue(int *array, int arraySize, int value) {
	int counter = 0;

	while (counter < arraySize)
	{
		if (array[counter] == value)
		{
			return FALSE;
		}
		counter++;
	}
	return TRUE;
}
