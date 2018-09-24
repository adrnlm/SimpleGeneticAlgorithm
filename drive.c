/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "drive.h"
#include "invector.h"
#include "pop.h"
#include "gene.h"
#include <time.h>


int main(int argc, char *argv[])
{
	srand(SRAND_SEED);
/* 	srand(time(NULL)); */

	if (argc < 1)
	{
		printf("At least one argument expected.\n");
		exit(EXIT_FAILURE);
	}
	if (argc > CMD_ARG_MAX)
	{
		printf("Too many arguments!\n");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	if (strcmp(argv[geneType], CMD_ARG_MINFN) == 0)
	{
		test_minfn();
	}
	if (strcmp(argv[geneType], CMD_ARG_PCBMILL) == 0)
	{
		test_pcbmill();
	}

#endif
	return EXIT_SUCCESS;
}

#ifdef DEBUG
	void test_pcbmill(void)
	{
	Gene *gene, *mutant, *child, *parent1, *parent2;

	/* Create a random pcbmill gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN and prints */
	printf("PCBMILL gene:\n");
	gene = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	gene_print(gene);

	/* Create a mutant copy of the gene using mutate_pcbmill and prints the mutant gene */
	printf("\nMutate:\n");
	mutant = mutate_pcbmill(gene);
	gene_print(mutant);

	/* Free the original gene and the mutant */
	printf("\n");
	gene_free(gene);
	gene_free(mutant);

	/* Creates 2 random pcbmill 'parent' genes using calls to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN & prints each gene out */
	printf("PCBMILL genes:\n");
	parent1 = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	printf("Parent 1 => "); /*DEBUG PURPOSES*/
	gene_print(parent1);
	parent2 = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	printf("Parent 2 => "); /*DEBUG PURPOSES*/
	gene_print(parent2);

	/* Produce a new gene by calling crossover_pcbmill
	   with the parent genes & prints new child gene and prints */
	printf("\nCrossover:\n");
	child = crossover_pcbmill(parent1, parent2);
	gene_print(child);

	/* Free both parents and the child gene */
	printf("\n");
	gene_free(child);
	gene_free(parent1);
	gene_free(parent2);
}

	void test_minfn(void)
	{
	Gene *gene, *mutant, *child, *parent1, *parent2;

	/* Create a random minfn gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN and prints */
	printf("MINFN gene:\n");
	gene = gene_create_rand_gene(TEST_ALLELE_LEN, create_minfn_chrom);
	gene_print(gene);

	/* Create a mutant copy of the gene using mutate_minfn and prints the mutant gene */
	printf("\nMutate:\n");
	mutant = mutate_minfn(gene);
	gene_print(mutant);

	/* Free the original gene and the mutant */
	printf("\n");
	gene_free(gene);
	gene_free(mutant);

	/* Creates 2 random minfn 'parent' genes using calls to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN & prints each gene out */
	printf("MINFN genes:\n");
	parent1 = gene_create_rand_gene(TEST_ALLELE_LEN, create_minfn_chrom);
	printf("Parent 1 => "); /*DEBUG PURPOSES*/
	gene_print(parent1);
	parent2 = gene_create_rand_gene(TEST_ALLELE_LEN, create_minfn_chrom);
	printf("Parent 2 => "); /*DEBUG PURPOSES*/
	gene_print(parent2);

	/* Produce a new gene by calling crossover_minfn
	   with the parent genes & prints new child gene and prints */
	printf("\nCrossover:\n");
	child = crossover_minfn(parent1, parent2);
	gene_print(child);

	/* Free both parents and the child gene */
	printf("\n");
	gene_free(child);
	gene_free(parent1);
	gene_free(parent2);
}

#endif
