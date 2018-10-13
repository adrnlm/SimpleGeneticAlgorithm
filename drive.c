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

int main(int argc, char *argv[]){
	InVTable *invTab;
	int allele_Size;
	int pop_Size = stringToInt(argv[popSize]);
	int num_Gen = stringToInt(argv[numGen]);
	char *input_File = argv[inputFile];
	FILE *file = fopen(input_File, "r");
	invTab = safeMalloc(sizeof(InVTable));
	invector_init(invTab);

	/* TO DO */
	#ifdef DEBUG
		printf("DEBUG\n");
			test_minfn();
			test_pcbmill();
	#else
		/* The only point at which srand should be called */
		srand(SRAND_SEED);
		printf("NOT DEBUG\n");

		if (check_arguments(argc, argv, file, invTab) == TRUE){
			if(argc == CMD_ARG_MAX){
	        file = freopen(argv[outputFile],"w",stdout);
	        if( file == NULL){
	            return EXIT_FAILURE;
	        }
	    }
			allele_Size = get_allele_size(argv[geneType], invTab);
			genetic_algorithm(invTab, argv[geneType], allele_Size, pop_Size, num_Gen);
			fclose(file);
			free(invTab);
		}
	#endif

	return EXIT_SUCCESS;
}

void genetic_algorithm(InVTable *invTab, char *gene_Type, int allele_Size, int pop_Size, int num_Gen){
	int counter = 0;
	Pop_list *currentGen, *nextGen;

	while(counter<num_Gen){
		if(counter == 0){
			pop_init(&currentGen);

			set_function(gene_Type,currentGen);
			create_first_gen(currentGen,pop_Size,allele_Size,invTab);
		}
		else{
			pop_init(&nextGen);
			set_function(gene_Type,nextGen);
			newGeneration(currentGen,nextGen);
			switch_current_pop(currentGen, nextGen);
			free_Pop(nextGen);
		}
		normalise_pop_fitness(currentGen,invTab);
		sort_pop(currentGen);
		pop_print_fittest(currentGen);
		counter++;
	}
	free_Pop(currentGen);

}

void read_file(char* argv[], FILE *file, InVTable *invTab){
	char line[INV_LEN];
	int numOfPar = stringToInt(argv[alleleSize]);
	int lineNumber = 0, counter = 0;
	char *gene_Type = argv[geneType];
	while(fgets(line, INV_LEN, file ) != NULL){

		if(read_line(line, numOfPar, invTab->table[counter], lineNumber, gene_Type) == -1){
			perror("Error");
			fclose(file);
			exit(EXIT_FAILURE);
		}
		lineNumber++;
		invTab->tot ++;
		counter++;
	}
	if (strcmp(gene_Type,CMD_ARG_PCBMILL) == 0){
		if(numOfPar != invTab->tot){
			printf("[COUNT MISMATCH: %d] \n", numOfPar );
			exit(EXIT_FAILURE);
		}
	}
}

int get_allele_size(char *gene_Type, InVTable *invTab ){
	if(strcmp(gene_Type,CMD_ARG_MINFN)==0){
			return invTab->width-1;
	}
	else if (strcmp(gene_Type,CMD_ARG_PCBMILL)==0){
			return invTab->tot;
	}
	return -1;
}

Boolean check_arguments(int argc, char *argv[], FILE *file, InVTable *invTab ){
	char *gene_Type = argv[geneType];
	int arg_Allele = stringToInt(argv[alleleSize]);
	int arg_Pop = stringToInt(argv[popSize]);

	if(!(argc == CMD_ARG_MAX || argc == CMD_ARG_MAX - 1)){
		printf("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if(file == NULL){
		printf("Invalid file\n");
		exit(EXIT_FAILURE);
	}
	if(strcmp(gene_Type,CMD_ARG_MINFN)!=0 && strcmp(gene_Type,CMD_ARG_PCBMILL)!=0){
		printf("Invalid gene type\n");
		exit(EXIT_FAILURE);
	}
	if(strcmp(gene_Type,CMD_ARG_MINFN)==0){
		if(arg_Allele <=0 || arg_Allele >= INVT_WIDTH){
			printf("Invalid second argument\n");
			exit(EXIT_FAILURE);
		}
	}
	if(strcmp(gene_Type,CMD_ARG_PCBMILL)==0){
		if(arg_Allele <0 || arg_Allele > INVT_MAX){
			printf("Invalid second argument\n");
			exit(EXIT_FAILURE);
		}
	}
	if(arg_Pop <2){
		printf("Too little population\n");
		exit(EXIT_FAILURE);
	}
	read_file(argv, file, invTab);
	invTab->width = arg_Allele+1;
	return TRUE;
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
