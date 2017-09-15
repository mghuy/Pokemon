/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pokemon.h
 * Author: Leng
 *
 * Created on December 2, 2016, 3:12 AM
 */

/* Header file for ECE 209 Program 4 */
/* G. Byrd, Fall 2016 */

#define NUMPOKEMON  151

struct pokemon {
  int index;       /* unique ID of this pokemon class */
  char name[11];
  char type1[11];  /* type of pokemon -- will not be NONE */
  char type2[11];  /* second type -- may be NONE */
};

struct location {
  double latitude;
  double longitude;
};

struct sighting {
  int id;         /* index of sighted pokemon */
  struct location where;  /* location of sighting */
  char date[11];          /* yyyy-mm-dd */
  int hrs;                /* time of sighting: hours (0-23) */
  int mins;               /* time of sighting: mins (0-59) */
  char timeofday[10];     /* morning, afternoon, evening, night */
  char weather[25];       /* e.g., Cloudy, Breezy */
  double temperature;     /* degrees Celsius */
};

/* node for building a list of sightings */
struct sNode {
  struct sighting s;
  struct sNode *next;
};

/* functions -- implemented in pokemon.c */
/* See descriptions in document. */

void printPokemon(struct pokemon *p, FILE *stream);
void printSighting(struct sighting *s, FILE *stream, struct pokemon p[]);

int readPokemon(FILE *stream, struct pokemon p[]);
struct sNode * readSightings(FILE *stream, int *n);

void sortPokemonByName(struct pokemon p[]);
void sortPokemonByIndex(struct pokemon p[]);
void sortPokemonByType(struct pokemon p[]);

void printPokemonArray(struct pokemon p[], FILE *stream);
void printSightingList(struct sNode *s, FILE *stream, struct pokemon p[]);

struct sNode *findSightingsByName(struct sNode *s, char *name,
				  struct pokemon p[]);
struct sNode *findSightingsByType(struct sNode *s, char *type,
				  struct pokemon p[]);
void countSightingsByName(struct sNode *s, FILE *stream, struct pokemon p[]);




