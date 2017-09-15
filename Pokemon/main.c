/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Leng
 *
 * Created on December 2, 2016, 3:12 AM
 */

/* User interface for ECE 209 Program 4 */
/* G. Byrd, Fall 2016 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"


FILE *getoutstream();

int main() 
{
  struct pokemon allPokemon[NUMPOKEMON];
  char sfilename[30];
  FILE *pokefile;
  FILE *sfile;
  FILE *out;
  int n;
  struct sNode * sightings = NULL;  /* empty list */
  struct sNode * sList = NULL;
  char command[25];  /* buffer to read command */

  pokefile = fopen("pokemon.txt", "r");
  if (!pokefile) {
    printf("ERROR: could not open pokemon.txt\n");
    return EXIT_FAILURE;
  }

  printf("Enter sightings file: "); fflush(stdout);
  scanf("%29s", sfilename);
  sfile = fopen(sfilename, "r");
  if (!sfile) {
    printf("ERROR: could not open sightings file: %s\n", sfilename);
    return EXIT_FAILURE;
  }

  /* read file data */
  printf("Reading files...\n");

  n = readPokemon(pokefile, allPokemon);
  if (n != NUMPOKEMON) {
    printf("ERROR: expected to read %d pokemon, but read %d\n",
	   NUMPOKEMON, n);
    fclose(pokefile);
    fclose(sfile);
    return EXIT_FAILURE;
  }
  printf("%d pokemon\n", n);
  fclose(pokefile);

  sightings = readSightings(sfile, &n);
  if (!sightings) {
    printf("ERROR: no sightings read from file\n");
    fclose(sfile);
    return EXIT_FAILURE;
  }
  printf("%d sightings\n", n);
  fclose(sfile);
 
  /* command loop -- keep going until quit command */
  while (1) {
    printf("Command: "); fflush(stdout);
    scanf("%s", command);
    if (strcmp(command, "print") == 0) {
      out = getoutstream();
      sortPokemonByIndex(allPokemon);
      printPokemonArray(allPokemon, out);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "pname") == 0) {
      out = getoutstream();
      sortPokemonByName(allPokemon);
      printPokemonArray(allPokemon, out);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "ptype") == 0) {
      out = getoutstream();
      sortPokemonByType(allPokemon);
      printPokemonArray(allPokemon, out);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "sprint") == 0) {
      out = getoutstream();
      printSightingList(sightings, out, allPokemon);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "sname") == 0) {
      scanf("%s", command);
      out = getoutstream();
      sList = findSightingsByName(sightings, command, allPokemon);
      printSightingList(sList, out, allPokemon);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "stype") == 0) {
      scanf("%s", command);
      out = getoutstream();
      sList = findSightingsByType(sightings, command, allPokemon);
      printSightingList(sList, out, allPokemon);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "count") == 0) {
      out = getoutstream();
      countSightingsByName(sightings, out, allPokemon);
      if (out) fclose(out);
      out = NULL;
    }
    else if (strcmp(command, "quit") == 0) {
      break;
    }
    else {
      printf("Unknown command.\n\n");
    }
  }
  return EXIT_SUCCESS;
}


FILE *getoutstream() {
  char fname[25];
  char next;
  FILE *out = NULL;

  do {
    scanf("%c", &next);
  } while ((next != '\n') && (next != ' '));
  
  if (next == '\n') {
    out = NULL;
  }
  else {
    scanf("%s", fname);
    out = fopen(fname, "w");
    if (!out) {
      printf("ERROR: Can't open file: %s\n", fname);
    }
  }
  return out;
}

