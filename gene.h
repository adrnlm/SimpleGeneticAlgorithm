/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef GENE_H
#define GENE_H
#include "utility.h"
#include "invector.h"

/* Alleles in the chromosome for the MINFUNCT problem can have values
 * in the range 0..29 (inclusive) */
#define MINFN_MAX 29

typedef struct gene
{
	/* A chromosome consists of a series of (integer) alleles */
	int *chromosome;
	int num_alleles;
	/* Raw score is set by the chromosome evaluation function */
	double raw_score;
	/* The raw score is inverted and normalised to produce the fitness
 	   The fitness is used to rank chromosomes for reproduction */
	double fitness;
} Gene;

/* A pointer type to a function for creating a random chromosome */
typedef int * (*CreateFn)(int);

/* Create a random chromosome of length num_alleles for a pcbmill gene */
int * create_pcbmill_chrom(int num_alleles);

/* Create a random chromosome of length num_alleles for a minfunct gene */
int * create_minfn_chrom(int num_alleles);

/* A pointer type to a function for mutating a gene */
typedef Gene * (*MutateFn)(Gene*);

/* Create a mutated copy of a pcbmill gene */
Gene * mutate_pcbmill(Gene*);

/* Create a mutated copy of a minfunct gene */
Gene * mutate_minfn(Gene*);

/* A pointer type to a function for performing crossover of two genes */
typedef Gene * (*CrossOverFn)(Gene*, Gene*);

/* Takes two parent genes and performs a crossover operation to
 * create a new child gene */
Gene * crossover_pcbmill(Gene *g1, Gene *g2);

Gene * crossover_minfn(Gene *g1, Gene *g2);

/* A pointer type to a function for evaluating the chromosome of a gene */
typedef double (*EvalFn)(InVTable *invtab, Gene *gene);

double eval_pcbmill(InVTable *invt, Gene *gene);

double eval_minfn(InVTable *invt, Gene *gene);

/* Attempts to create a new gene of length num_alleles, by calling a function
 * for creating the gene chromosome (create_chrom is a pointer to that
 * function). Returns NULL if the gene can't be created */
Gene * gene_create_rand_gene(int num_alleles, CreateFn create_chrom);

/* Takes a pointer to a function for evaluating a gene's chromosome, the gene
 * and a table of input vectors. The raw_score is set to the evaluation
 * function result. The fitness is the inverted raw_score: 1/(raw_score + 1.0)
 * */
void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab);

/* The fitness of the gene is normalised against the population's
 * total_fitness */
void gene_normalise_fitness(Gene *gene, double total_fitness);

void gene_free(Gene*);

double gene_get_fitness(Gene *gene);

/* The following function should be the only code for printing out
 * a gene, either to file or to standard output */
void gene_print(Gene*);

#endif
