/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

int * create_pcbmill_chrom(int numAlleles)
{
	int counter, *chromosome, randomValue;

	/*Memory Allocation*/
	chromosome = safeMalloc(sizeof(int) * numAlleles);

	for (counter = 0; counter < numAlleles; counter++){
		do {
			randomValue = rand() % numAlleles;
		} while( checkValue(chromosome, counter, randomValue)==0 );
		chromosome[counter] = randomValue;
	}
	return chromosome;
}

int * create_minfn_chrom(int numAlleles)
{
	int counter, *chromosome;

	/*Memory Allocation*/
	chromosome = safeMalloc(sizeof(int) * numAlleles);

	for (counter = 0; counter < numAlleles; counter ++ )
	{
		chromosome[counter] = rand() % MINFN_MAX;
	}
	return chromosome;
}

Gene * mutate_pcbmill(Gene *g)
{
	Gene *mutated_gene;
	int mutationPoint1, mutationPoint2, counter=0, tempPoint;

	/*Debug purposes*/
	#ifdef DEBUG
	mutationPoint1 = 2;
	mutationPoint2 = 4;
	printf(" index1: %d index2: %d\n", mutationPoint1, mutationPoint2 );
	#else
	mutationPoint1 = rand() % g->num_alleles;
	do {
		mutationPoint2 = rand() % g->num_alleles;
	} while(mutationPoint2 == mutationPoint1);
	#endif

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

Gene * mutate_minfn(Gene *g)
{
	Gene *mutated_gene;
	int mutatationPoint, counter=0;

	#ifdef DEBUG
	mutatationPoint = 2;
	printf(" mutaion point: %d\n", mutatationPoint );
	#else
	mutatationPoint = rand() % g->num_alleles;
	#endif

	/*Memory Allocation*/
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

Gene * crossover_pcbmill(Gene *g1, Gene *g2)
{
	int crossoverPoint1=0, crossoverPoint2=0, counter=0, stopPoint=0, sizeOfCrossover=0;
	Gene *child_gene=NULL;

	/*Debug purposes*/
	#ifdef DEBUG
	crossoverPoint1 = 2;
	crossoverPoint2 = 4;
	printf(" index1: %d index2: %d\n", crossoverPoint1, crossoverPoint2 );
	#else
	crossoverPoint1 = rand() % g2->num_alleles;
	do {
		crossoverPoint2 = rand() % g1->num_alleles;
	} while(crossoverPoint1 > crossoverPoint2);
	#endif


	/*Memory Allocation*/
	child_gene = safeMalloc(sizeof(Gene));
	child_gene->chromosome = safeMalloc(sizeof(int) * g1->num_alleles);

	/*Determining the size of chromosomes to crossover*/
	sizeOfCrossover = (crossoverPoint2 - crossoverPoint1)+ZERO_PLACE;

	/*Copying data from g1 point1 -> point2 and placing it into child _gene */
	for (counter = 0; counter < g1->num_alleles; counter++){
		if(counter < sizeOfCrossover)
		{
			child_gene->chromosome[counter] = g1->chromosome[counter+crossoverPoint1];
			stopPoint = counter;
		}
		else
		{
			child_gene->chromosome[counter] = 0;
		}
	}
	/*Finding the rest of the child_gene from g2 */
	for (counter = 0; counter < g1->num_alleles; counter++){
		if((checkValue(child_gene->chromosome, g1->num_alleles, g2->chromosome[counter])) == TRUE){
			child_gene->chromosome[stopPoint+ZERO_PLACE] = g2->chromosome[counter];
			stopPoint++;
		}
	}
	child_gene->num_alleles = g1->num_alleles;
	child_gene->raw_score = child_gene->fitness = 0;

	return child_gene;
}

Gene * crossover_minfn(Gene *g1, Gene *g2)
{
	int crossoverPoint, Point, counter;
	Gene *child_gene;

	/*Debug purposes*/
	#ifdef DEBUG
	Point = 3;
	printf(" crossover point: %d\n", Point );
	#else
	Point = rand() % g1->num_alleles;
	#endif

	/*Memory Allocation*/
	child_gene = safeMalloc(sizeof(Gene));
	child_gene->chromosome = safeMalloc(sizeof(int) * g1->num_alleles);

	/*Creating child gene*/
	for (counter = 0; counter < g1->num_alleles; counter ++){
		child_gene->chromosome[counter] = g1->chromosome[counter];
	}
	for (crossoverPoint = Point; crossoverPoint < g1->num_alleles; crossoverPoint++){
		child_gene->chromosome[crossoverPoint] = g2->chromosome[crossoverPoint];
	}
	child_gene->num_alleles = g1->num_alleles;
	child_gene->raw_score = child_gene->fitness = 0;

	return child_gene;
}

double eval_pcbmill(InVTable *invt, Gene *gene)
{
	int curPtr, nextPtr, max_count = gene->num_alleles-1;
	double evaluation = 0;

	for (curPtr = 0; curPtr<max_count; curPtr++){
		int corA, corB;
		double distance;
		nextPtr = curPtr;
		nextPtr++;

		corA = gene->chromosome[curPtr];
		corB = gene->chromosome[nextPtr];

		/*Formula based of the given specification*/
		distance =
		sqrt((pow((invt->table[corB][0])-(invt->table[corA][0]),2)+pow((invt->table[corB][1])-(invt->table[corA][1]),2)));

		evaluation += distance;
	}
	return evaluation;
}

double eval_minfn(InVTable *invt, Gene *gene)
{
	int counter, value1, value2, tempScore = 0;
	double score = 0;
	int width = invt->width - 1;
	for (counter=0; counter<width; counter++){
		value1 = invt->table[0][counter];
		value2 = gene->chromosome[counter];
		tempScore += (value1 * value2);
	}

	score = abs(tempScore - (invt->table[0][counter]));

	return score;
}

Gene * gene_create_rand_gene(int numAlleles, CreateFn create_chrom)
{
	Gene *random_gene=NULL;

	/*Memory Allocation*/
	random_gene = safeMalloc(sizeof(Gene));

	/*Create Random gene*/
	random_gene->chromosome = create_chrom(numAlleles);
	random_gene->num_alleles = numAlleles;
	random_gene->raw_score = random_gene->fitness = 0;

	return random_gene;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab)
{
	gene->raw_score = evaluate_fn(invTab, gene);
	gene->fitness = 1/(gene->raw_score + 1.0);
}

void gene_normalise_fitness(Gene *gene, double total_fitness)
{
	gene->fitness = gene_get_fitness(gene)/total_fitness;
}

void gene_free(Gene *gene)
{
	free(gene->chromosome);
	free(gene);
}

double gene_get_fitness(Gene *gene){
	double fitness;
	fitness = gene->fitness;
	return fitness;
}

void gene_print(Gene *gene) {
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
