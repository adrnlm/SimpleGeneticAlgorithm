/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

int * create_pcbmill_chrom(int numAlleles){
	/* TO DO */
	return NULL;
}

int * create_minfn_chrom(int numAlleles){
	/* TO DO */
	return NULL;
}

Gene * mutate_pcbmill(Gene *g){
	/* TO DO */
	return NULL;
}

Gene * mutate_minfn(Gene *g){
	/* TO DO */
	return NULL;
}

Gene * crossover_pcbmill(Gene *g1, Gene *g2){
	/* TO DO */
	return NULL;
}

Gene * crossover_minfn(Gene *g1, Gene *g2){
	/* TO DO */
	return NULL;
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
	return NULL;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab){
	/* TO DO */
}

void gene_normalise_fitness(Gene *gene, double total_fitness){
	/* TO DO */
}

void gene_free(Gene *gene){
	/* TO DO */
}


double gene_get_fitness(Gene *gene){
	/* TO DO */
	return 0.0;
}

void gene_print(Gene *gene) {
	/* TO DO */
}
