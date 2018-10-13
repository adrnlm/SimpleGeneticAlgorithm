/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef POP_H
#define POP_H

#include "gene.h"
#include "invector.h"

#define MUTATE_RATE 5
#define MAX_RANGE 1.0

typedef struct pop_node {
	Gene *gene;
	struct pop_node *next;
} Pop_node;

typedef struct pop_list {
	/* the head of the population list */
	Pop_node *head;
	/* the size of the population */
	int count;
	/* pointers to functions to perform
 	 * gene chromosome creation, mutation,
 	 * crossover and evaluation */
	CreateFn create_rand_chrom;
	MutateFn mutate_gene;
	CrossOverFn crossover_genes;
	EvalFn evaluate_fn;
} Pop_list;

/* Create and initialise the population list to a safe state.
 * Returns TRUE on success */
Boolean pop_init(Pop_list **);

/* Set the function pointers of a population list */
void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef);

/* This function causes details of the fittest gene of the generation to
 * be printed out.
 * The function also prints out the number of the current generation.
 * This function must not be able to access any generation value outside
 * of the function. */
void pop_print_fittest(Pop_list *p);

/* TO DO - other functions as appropriate */

/*Create a new node*/
Pop_node *create_node();

/*Add node to a population list*/
void add_node();

/*Create the initial generation*/
void create_first_gen();

/*Create a new generation*/
void new_generation();

/*Increase the population*/
void increase_pop();

/*Select a random gene*/
Gene *roulette_gene();

/*Normalise the fitness of the population*/
void normalise_pop_fitness();

/*Utilize bubble-sort to sort the genes based on fittest first*/
void sort_pop();

/*Produce a copy of a given gene*/
Gene *copy_gene();

/*Switch the pointer between two population*/
void switch_current_pop();

/*Print the popluation*/
void print_pop_list();

/*Free the population*/
void free_Pop();

#endif
