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
	Gene *gene1, *gene2, *gene3;
	printf("\nPCBMILL gene:\n");
	/* TO DO - create a random pcbmill gene by calling create_rand_gene
		 The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	/* TO DO - print the gene using gene_print */
	gene_print(gene1);
	printf("\nMutate: ");
	/* TO DO - create a mutant copy of the gene using mutate_pcbmill */
	gene2 = mutate_pcbmill(gene1);
	/* TO DO - print the mutant gene using gene_print */
	gene_print(gene2);
	printf("\n");
	/* TO DO - free the original gene and the mutant */
	gene_free(gene2);
	gene_free(gene1);
	printf("PCBMILL genes:\n");
	/* TO DO - create 2 random pcbmill 'parent' genes using calls
		 to create_rand_gene
		 The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	gene2 = gene_create_rand_gene(TEST_ALLELE_LEN, create_pcbmill_chrom);
	/* TO DO - print each gene */
	gene_print(gene1);
	gene_print(gene2);
	printf("\nCrossover: ");
	/* TO DO produce a new gene by calling crossover_pcbmill
		 with the parent genes */
	gene3 = crossover_pcbmill(gene1, gene2);
	/* TO DO - print the new gene */
	gene_print(gene3);
	printf("\n");
	/* TO DO - free both parents and the child gene */
	gene_free(gene3);
	gene_free(gene2);
	gene_free(gene1);
}

void test_minfn(void){
	/* TO DO */
	Gene *gene1, *gene2, *gene3;

	printf("\nMINFN gene:\n");
	/* TO DO - create a random minfn gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN,create_minfn_chrom);
	/* TO DO - print the gene */
	gene_print(gene1);
	printf("\nMutate:");
	/* TO DO - create a mutant copy of the gene using mutate_minfn */
	gene2 = mutate_minfn(gene1);
	/* TO DO - print the mutant gene */
	gene_print(gene2);
	/* TO DO - free the original gene and the mutant */
	gene_free(gene1);
	gene_free(gene2);

	printf("\nMINFN genes:\n");
	/* TO DO - create 2 random minfn 'parent' genes using calls
	   to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene1 = gene_create_rand_gene(TEST_ALLELE_LEN,create_minfn_chrom);
	gene2 = gene_create_rand_gene(TEST_ALLELE_LEN,create_minfn_chrom);
	/* TO DO - print each gene */
	gene_print(gene1);
	gene_print(gene2);

	printf("\nCrossover:");
	/* TO DO produce a new gene by calling crossover_minfn
	   with the parent genes */
	gene3 = crossover_minfn(gene1, gene2);
	/* TO DO - print the new gene */
	gene_print(gene3);
	printf("\n");
	/* TO DO - free both parents and the child gene */
	gene_free(gene1);
	gene_free(gene2);
	gene_free(gene3);
}
#endif

void minfn(FILE *file, int alleleSize, int popSize, int numGen){
	int counter = 0;
	char line[INV_LEN];
	InVTable *newTable = NULL;
	Pop_list *currentGen = NULL;
	Pop_list *nextGen = NULL;
	newTable = safeMalloc(sizeof(InVTable));
	invector_init(newTable);

	fgets(line, sizeof(line), file);

	read_line(line, alleleSize, newTable->table[counter], counter);
	newTable->width = alleleSize+1;

	while (counter < numGen){
		if (counter == 0){
			/*Initialise new population*/
			pop_init(&currentGen);
			/*Prepare pop for MINFN*/
			pop_set_fns(currentGen, create_minfn_chrom, mutate_minfn, crossover_minfn, eval_minfn);
			/*Create first generation*/
			create_first_gen(currentGen, popSize, alleleSize, newTable);
			/*Print first generation*/
			printf("Gen %d: ", counter);
			pop_print_fittest(currentGen);
		}
		else {
			pop_init(&nextGen);
			pop_set_fns(nextGen, create_minfn_chrom, mutate_minfn, crossover_minfn, eval_minfn);
			newGeneration(currentGen, nextGen, newTable);
			switch_current_pop(currentGen, nextGen);
			printf("Gen %d: ", counter);
			pop_print_fittest(currentGen);
			free_Pop(nextGen);
		}
		counter++;
	}
	free_Pop(currentGen);
}

void pcbmill(FILE *file, int alleleSize, int popSize, int numGen){
	int counter = 0;
	char line[INV_LEN];
	InVTable *newTable = NULL;
	newTable = safeMalloc(sizeof(InVTable));
	invector_init(newTable);

	printf("PCBMILL\n" );

	while (fgets(line, sizeof(line), file) != NULL) {
		read_line(line, alleleSize, newTable->table[counter], counter);
		counter++;
		/*printf("TEST: %d\n", newTable->table[6][0] );*/
	}
}

int main(int argc, char *argv[]){
	/* TO DO */
	#ifdef DEBUG
		printf("DEBUG\n");
			test_minfn();
			test_pcbmill();
	#else
		char *geneType = argv[1], *inputFile = argv[5];
		int alleleSize = stringToInt(argv[2]), popSize = stringToInt(argv[3]), numGen = stringToInt(argv[4]);
		FILE *file;
		file = fopen(inputFile,"r");

		/* The only point at which srand should be called */
		srand(SRAND_SEED);
		printf("NOT DEBUG\n");

		checkInt(alleleSize);
		checkInt(popSize);
		checkInt(numGen);

		if ( strcmp(geneType,"minfn") == FALSE || strcmp(geneType,"pcbmill") == FALSE){
			minfn(file, alleleSize, popSize, numGen);
		}
		else{
			printf("WRONG COMMAND\n" );
			exit(0);
		}


	#endif


	return EXIT_SUCCESS;
}

void set_function(char *type, Pop_list *pop){
	if(strcmp(type,CMD_ARG_MINFN)==0){
			pop_set_fns(pop, create_minfn_chrom, mutate_minfn, crossover_minfn, eval_minfn);
	}
	else if (strcmp(type,CMD_ARG_PCBMILL)==0){
		pop_set_fns(pop, create_pcbmill_chrom, mutate_pcbmill, crossover_pcbmill, eval_pcbmill);
	}
	else{
		printf("WRONG COMMAND\n" );
		exit(0);
	}
}
