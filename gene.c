/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"
#include "utility.h"

int *create_pcbmill_chrom(int numAlleles)
{
	int index, randomValue;
	int *pcbmill_chrom = safeMalloc(sizeof(*pcbmill_chrom) * numAlleles);

	index = 0;

	while (index < numAlleles)
	{
		do
		{
			randomValue = getRandomValue(numAlleles);
		} while (contains(pcbmill_chrom, (index + 1), randomValue) == TRUE);
		pcbmill_chrom[index] = randomValue;
/* 		printf("Current value of index [%d] = %d\n", index, randomValue); DEBUG PURPOSES */
		index++;
	}
	return pcbmill_chrom;
}

int *create_minfn_chrom(int numAlleles)
{
	int i;
	int *minfn_chrom = safeMalloc(sizeof(*minfn_chrom) * numAlleles);

	for (i = 0; i < numAlleles; i++)
	{
		minfn_chrom[i] = getRandomValue(MINFN_MAX + 1);
	}
	return minfn_chrom;
}

Gene *mutate_pcbmill(Gene *g)
{
	int i, j, random1 = 0, random2 = 0, index1, index2;
	Gene *mutant_pcbmill = safeMalloc(sizeof(*mutant_pcbmill));
	mutant_pcbmill->raw_score = mutant_pcbmill->fitness = 0;
	mutant_pcbmill->num_alleles = g->num_alleles;
	mutant_pcbmill->chromosome = safeMalloc(sizeof(*mutant_pcbmill->chromosome) * mutant_pcbmill->num_alleles);

	for (i = 0; i < (mutant_pcbmill->num_alleles); i++)
	{
		mutant_pcbmill->chromosome[i] = g->chromosome[i];
	}
	do
	{
		random1 = getRandomValue(mutant_pcbmill->num_alleles);
		random2 = getRandomValue(mutant_pcbmill->num_alleles);
	} while (random1 == random2);

	for (j = 0; j < mutant_pcbmill->num_alleles; j++)
	{
		if (mutant_pcbmill->chromosome[j] == random1)
		{
			index1 = j;
		}
		if (mutant_pcbmill->chromosome[j] == random2)
		{
			index2 = j;
		}
	}
	mutant_pcbmill->chromosome[index1] = random2;
	mutant_pcbmill->chromosome[index2] = random1;

	return mutant_pcbmill;
}

Gene *mutate_minfn(Gene *g)
{
	int i;
	Gene *mutant_minfn = safeMalloc(sizeof(*mutant_minfn));

	mutant_minfn->raw_score = mutant_minfn->fitness = 0;
	mutant_minfn->num_alleles = g->num_alleles;
	mutant_minfn->chromosome = safeMalloc(sizeof(*mutant_minfn->chromosome) * mutant_minfn->num_alleles);

	for (i = 0; i < mutant_minfn->num_alleles; i++)
	{
		mutant_minfn->chromosome[i] = g->chromosome[i];
	}
	mutant_minfn->chromosome[getRandomValue(mutant_minfn->num_alleles)] = getRandomValue(MINFN_MAX + 1);

	return mutant_minfn;
}

Gene *crossover_pcbmill(Gene *g1, Gene *g2)
{
	int i, j, childIndex = 0, index1 = 0, index2 = 0;

	Gene *child_pcbmill = safeMalloc(sizeof(*child_pcbmill));
	child_pcbmill->raw_score = child_pcbmill->fitness = 0;
	child_pcbmill->num_alleles = g1->num_alleles;
	child_pcbmill->chromosome = safeMalloc(sizeof(*child_pcbmill->chromosome) * child_pcbmill->num_alleles);

	while (index2 <= index1)
	{
		index1 = getRandomValue(child_pcbmill->num_alleles);
		index2 = getRandomValue(child_pcbmill->num_alleles);
	}
	printf("Value of index 1 = %d and index 2 = %d\n", index1, index2); /*DEBUG PURPOSES*/

	for (i = childIndex; i <= (index2 - index1); i++)
	{
		child_pcbmill->chromosome[i] = g1->chromosome[index1 + i];
		childIndex++;
	}
	for (j = 0; j < g2->num_alleles; j++)
	{
		if (contains(child_pcbmill->chromosome, childIndex, g2->chromosome[j]) == FALSE)
		{
			child_pcbmill->chromosome[childIndex] = g2->chromosome[j];
			childIndex++;
		}
	}
	return child_pcbmill;
}

Gene *crossover_minfn(Gene *g1, Gene *g2)
{
	int i, index, childIndex = 0;
	Gene *child_minfn = safeMalloc(sizeof(*child_minfn));

	child_minfn->raw_score = child_minfn->fitness = 0;
	child_minfn->num_alleles = g1->num_alleles;
	child_minfn->chromosome = safeMalloc(sizeof(*child_minfn->chromosome) * child_minfn->num_alleles);

	index = getRandomValue(child_minfn->num_alleles);

	printf("Value of index is %d\n", index); /*DEBUG PURPOSES*/

	for (i = childIndex; i <= index; i++)
	{
		child_minfn->chromosome[i] = g1->chromosome[i];
		childIndex++;
	}
	for (i = childIndex; i < (child_minfn->num_alleles); i++)
	{
		child_minfn->chromosome[childIndex] = g2->chromosome[i];
		childIndex++;
	}
	return child_minfn;
}

double eval_pcbmill(InVTable *invt, Gene *gene)
{
	/* TO DO */
	return 0.0;
}

double eval_minfn(InVTable *invt, Gene *gene)
{
	int i;
	double rawScore, totalRawScore = 0;

	for (i = 0; i < invt->tot; i++)
	{
		int *vector = invt->table[i];
		int j;
		rawScore = 0;

		for (j = 0; j < (gene->num_alleles); j++)
		{
			rawScore += vector[j] * gene->chromosome[j];
		}
		rawScore -= vector[gene->num_alleles];
		totalRawScore += fabs(rawScore);
	}
	return totalRawScore;
}

Gene *gene_create_rand_gene(int numAlleles, CreateFn create_chrom)
{
	Gene *gene = safeMalloc(sizeof(*gene));
	gene->raw_score = gene->fitness = 0;
	gene->num_alleles = numAlleles;
	gene->chromosome = create_chrom(gene->num_alleles);
	return gene;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab)
{
	/* TO DO */
}

void gene_normalise_fitness(Gene *gene, double total_fitness)
{
	/* TO DO */
}

void gene_free(Gene *gene)
{
	free(gene->chromosome);
	free(gene);
}

double gene_get_fitness(Gene *gene)
{
	/* TO DO */
	return 0.0;
}

void gene_print(Gene *gene)
{
	int i;

	printf("chrom: ");
	for (i = 0; i < (gene->num_alleles); i++)
	{
		printf("%d", gene->chromosome[i]);
		if (i < ((gene->num_alleles) - 1))
		{
			printf(",");
		}
		printf(" ");
	}
	printf("fit: %.3f, raw: %.3f \n", gene->fitness, gene->raw_score);
}

Boolean contains(int *array, int arraySize, int value)
{
	int i = 0;

	while (i < arraySize)
	{
		if (array[i] == value)
		{
			return TRUE;
		}
		i++;
	}
	return FALSE;
}

int getRandomValue(int numAlleles)
{
	int randomValue;
	randomValue = rand() % numAlleles;
	return randomValue;
}
