/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "drive.h"
#include "invector.h"
#include "pop.h"
#include "gene.h"

#ifdef DEBUG
void test_pcbmill(void){
	/* TO DO */
	Gene *gene1, *gene2;
	printf("PCBMILL gene:\n");
	/* TO DO - create a random pcbmill gene by calling create_rand_gene
		 The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	/* TO DO - print the gene using gene_print */
	gene_print(gene1);
	printf("\nMutate: ");
	/* TO DO - create a mutant copy of the gene using mutate_pcbmill */
	/* TO DO - print the mutant gene using gene_print */
	printf("\n");
	/* TO DO - free the original gene and the mutant */
	gene_free(gene1);
	printf("PCBMILL genes:\n");
	/* TO DO - create 2 random pcbmill 'parent' genes using calls
		 to create_rand_gene
		 The length of the gene's chromosome should be TEST_ALLELE_LEN */
	/* TO DO - print each gene */
	printf("\nCrossover: ");
	/* TO DO produce a new gene by calling crossover_pcbmill
		 with the parent genes */
	/* TO DO - print the new gene */
	printf("\n");
	/* TO DO - free both parents and the child gene */
}

void test_minfn(void){
	/* TO DO */
	Gene *gene1, *gene2;

	printf("MINFN gene:\n");
	/* TO DO - create a random minfn gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN,create_minfn_chrom);
	/* TO DO - print the gene */
	gene_print(gene1);
	printf("\nMutate: \n");
	/* TO DO - create a mutant copy of the gene using mutate_minfn */
	gene2 = mutate_minfn(gene1);
	/* TO DO - print the mutant gene */
	gene_print(gene2);
	printf("\n");
	/* TO DO - free the original gene and the mutant */
	gene_free(gene1);
	gene_free(gene2);

	printf("MINFN genes:\n");
	/* TO DO - create 2 random minfn 'parent' genes using calls
	   to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN,create_minfn_chrom);
	gene2 = gene_create_rand_gene(TEST_ALLELE_LEN,create_minfn_chrom);
	/* TO DO - print each gene */
	printf("Parent 1 => ");
	gene_print(gene1);
	printf("Parent 2 => ");
	gene_print(gene2);

	printf("\nCrossover: ");
	/* TO DO produce a new gene by calling crossover_minfn
	   with the parent genes */
	gene1 = crossover_minfn(gene1, gene2);
	/* TO DO - print the new gene */
	gene_print(gene1);
	printf("\n");
	/* TO DO - free both parents and the child gene */
	gene_free(gene1);
	gene_free(gene2);
}
#endif

int main(int argc, char *argv[]){


	/* TO DO */
	#ifdef DEBUG
			test_minfn();
			test_pcbmill();
	#else
			printf("NOT DEBUG\n");
	#endif
	/* The only point at which srand should be called */
	srand(SRAND_SEED);

	return EXIT_SUCCESS;
}
