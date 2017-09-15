/* Function implementations for ECE 209 Program 4 */
/* *****YOUR NAME GOES HERE*******                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

/*
 * Print a single pokemon to stream
 */
void printPokemon(struct pokemon *p, FILE *stream) {
  //printf("=======printPokemon implemented.\n");
  char * none = "NONE";
  if (strcmp(p->type2,none)==0){
      printf("%03d %-10s %s\n", p->index, p->name, p->type1);
  }
  else {
      printf("%03d %-10s %s/%s\n", p->index, p->name, p->type1,p->type2);
  }
  return;
}

/*
 * Print a single sighting to stream
 */
void printSighting(struct sighting *s, FILE *stream, struct pokemon p[]) {
  //printf("printSighting not implemented.\n");
    double tempf = s->temperature*1.8 + 32;
    char * pokeName;
    int i;
    for (i=0;i<151;i++) {
        if (s->id == p[i].index)
            pokeName = p[i].name;
    }
    
    printf("%s %02d:%02d %-10s (%.2f,%.2f) << %s, %s, %.2f >>\n",
            s->date, s->hrs, s->mins, pokeName, s->where.latitude, s->where.longitude,
            s->timeofday, s->weather, tempf);
    
  return;
}

/*
 * Read all pokemon information from file.
 */
int readPokemon(FILE *stream, struct pokemon p[]) {
  printf("=======readPokemon implemented.\n");
  int count=0;
  int i=0;
  int uselessnum;
  while(fscanf(stream,"%d",&p[i].index)!=EOF) {
      fscanf(stream,"%s",p[i].name);
      fscanf(stream,"%s",p[i].type1);
      fscanf(stream,"%s",p[i].type2);
      fscanf(stream,"%d",&uselessnum);
      fscanf(stream,"%d",&uselessnum);
      i++;
      count++;
  }
  
  return count;
}

/*
 * Read all sighting information from file.
 * Creates new sightings list.
 */
struct sNode * readSightings(FILE *stream, int *n) {
  printf("=======readSightings implemented.\n");
  n=0;
  struct sNode * head = (struct sNode*)malloc(sizeof(struct sNode));
  struct sNode * new = (struct sNode*)malloc(sizeof(struct sNode));
  struct sNode * p;
  
  fscanf(stream,"%d",&head->s.id);
  fscanf(stream,"%lf",&head->s.where.latitude);
  fscanf(stream,"%lf",&head->s.where.longitude);
  fscanf(stream,"%s",head->s.date);
  fscanf(stream,"%d:%d",&head->s.hrs,&head->s.mins);
  fscanf(stream,"%s",head->s.timeofday);
  fscanf(stream,"%s",head->s.weather);
  fscanf(stream,"%lf",&head->s.temperature);
  
  head->next = new;
  while (fscanf(stream,"%d",&new->s.id)!=EOF) {
       fscanf(stream,"%lf",&new->s.where.latitude);
       fscanf(stream,"%lf",&new->s.where.longitude);
       fscanf(stream,"%s",new->s.date);
       fscanf(stream,"%d:%d",&new->s.hrs,&new->s.mins);
       fscanf(stream,"%s",new->s.timeofday);
       fscanf(stream,"%s",new->s.weather);
       fscanf(stream,"%lf",&new->s.temperature);
       
       p = (struct sNode*)malloc(sizeof(struct sNode));
       new->next = p;
       new = p;
       n++;
  }
  
  /*struct sNode * current = (struct sNode*)malloc(sizeof(struct sNode));
  current = head;
  while (current->next!=NULL) {
      printf("%d ", current->s.id);
      printf("(%.2f,%.2f) ", current->s.where.latitude, current->s.where.longitude);
      printf("%s ", current->s.date);
      printf("%d:%d\n",current->s.hrs,current->s.mins);
      current = current->next;
  }*/
  return head;
}

/*
 * Sort pokemon array, alphabetically by name.
 */
void sortPokemonByName(struct pokemon p[]) {
  printf("=======sortPokemonByName not implemented\n");
  
  struct pokemon temp;
  int i,j;
  for (i=0;i<151;i++) {
      for (j=150;j>=i+1;j--) {
          if (strcmp(p[j].name,p[j-1].name)<0) {
              temp = p[j];
              p[j] = p[j-1];
              p[j-1] = temp;
          }
      }
  }
  
  return;
}

/*
 * Sort pokemon array, low to high by index.
 */
void sortPokemonByIndex(struct pokemon p[]) {
  printf("=======sortPokemonByInde: implemented\n");
    
  struct pokemon temp;
  int i,j;
  for (i=0;i<151;i++){
      for (j=150;j>=i+1;j--) {
          if (p[j].index<p[j-1].index) {
              temp = p[j];
              p[j]=p[j-1];
              p[j-1]=temp;
          }
      }
  }
  return;
}

/*
 * Sort pokemon array, alphabetically by type.
 */
void sortPokemonByType(struct pokemon p[]) {

  struct pokemon temp;
  char * none = "NONE";
  int i,j;
  for (i=0;i<151;i++) {
      for (j=150;j>=i+1;j--) {
          if (strcmp(p[j].type1,p[j-1].type1)<0) {
              temp = p[j];
              p[j] = p[j-1];
              p[j-1] = temp;
          }
          if (strcmp(p[j].type1,p[j-1].type1)==0) {  
              if (strcmp(p[j].type2,p[j-1].type2)==0) {
                  if (p[j].index<p[j-1].index) {
                      temp = p[j];
                      p[j] = p[j-1];
                      p[j-1] = temp;
                  }
              }
          }
      }
  }
  
  for (i=0;i<151;i++) {
      for (j=150;j>=i+1;j--) {
          if (strcmp(p[j].type1,p[j-1].type1)==0) {
              if (strcmp(p[j].type2,none)==0 && strcmp(p[j-1].type2,none)!=0) {
                  temp = p[j];
                  p[j] = p[j-1];
                  p[j-1] = temp;
              }
              else if (strcmp(p[j].type2,p[j-1].type2)<0 && strcmp(p[j-1].type2,none)!=0) {
                  temp = p[j];
                  p[j] = p[j-1];
                  p[j-1] = temp;
              }
          }
      }
  }
  
  return;
}

/*
 * Print pokemon array, one per line.
 */
void printPokemonArray(struct pokemon p[], FILE *stream) {
  printf("=======printPokemonArray implemented\n");
  
  int i;
  for (i=0;i<151;i++) {
      printPokemon(p+i,stream);
  }
  return;
}

/*
 * Print sightings list, one per line.
 */
void printSightingList(struct sNode *s, FILE *stream, struct pokemon p[]) {
  printf("=======printSightingList implemented\n");
  
  struct sNode * current = (struct sNode*)malloc(sizeof(struct sNode));
  current = s;
  while (current->next!=NULL) {
      printSighting(&current->s,stream,p);
      current = current->next;
  }
  return;
}

/*
 * Create new list of sightings that match name.
 * Result list is sorted by date, then time, then time.
 */
struct sNode *findSightingsByName(struct sNode *s, char *name,
				  struct pokemon p[]) {
  printf("=====findSightingsByName not implemented\n");
  
  int i;
  int check = 0;
  int id;
  struct sNode * head = (struct sNode*)malloc(sizeof(struct sNode));
  struct sNode * new = (struct sNode*)malloc(sizeof(struct sNode));
  struct sNode * temp;
  
  for (i=0;i<151;i++) {
      if (strcmp(name,p[i].name)==0) {
          id = p[i].index;
      }
  }
  struct sNode * current = (struct sNode*)malloc(sizeof(struct sNode));
  current = s;
  while (check==0) {
      while (current->next!=NULL) {
          if (id==current->s.id) {
              head = current;
              check++;
              break;
          }
          current = current->next;
      }
      printf("Couldn't Find pokemon in this sightings list.\n");
      break;
  }
  current=current->next;
  head->next = new;
  while (current->next!=NULL) {
      if (id==current->s.id) {
          new = current;
          temp = (struct sNode*)malloc(sizeof(struct sNode));
          new->next = temp;
          new = temp;
      }
      current = current->next;
  }
  
  struct sNode * loop = (struct sNode*)malloc(sizeof(struct sNode));
  loop = head;
  while (loop->next!=NULL) {
      printf("%d\n", loop->s.id);
      loop = loop->next;
  }
  return head;
}

/*
 * Create new list of sightings that match type.
 */
struct sNode *findSightingsByType(struct sNode *s, char *type,
				  struct pokemon p[]) {
  printf("fineSightingsByType not implemented\n");
  return NULL;
}

/*
 * Prints counts for each pokemon sighted, high to low.
 */
void countSightingsByName(struct sNode *s, FILE *stream, struct pokemon p[]) {
  printf("countSightingsByName not implemented\n");
  
  int id;
  int count;
  struct sNode * current = (struct sNode*)malloc(sizeof(struct sNode));
  current = s;
  
  while (current->next!=NULL) {
      if (current)
  }
  
  return;
}



