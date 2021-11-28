/*
This MP involved us exploring a data structure called Tuples, which stores sparse matrices.
This is a more efficient storage than a 2-D array as it saves space on the heap.
It stores data in a list of rows, which then inturn store a list of non-zero elements.
This programme has several functions, each of which have different uses- including addition.
They return the value of the element at the given row and column.
MP Partners: ddamani2 and ronitk2.
*/
#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
sp_tuples * load_tuples(char* input_file)
{
  int i; // Initialising Variables
  int rows, cols;
  int row, col;
  double value;
  FILE *open;
  open = fopen(input_file, "r"); // Opening file
  fscanf(open, "%d %d", &rows, &cols); // Inputting Values
  sp_tuples *new_tuple = (sp_tuples *)malloc(sizeof(struct sp_tuples));
  new_tuple->m = rows; // Assigning pointers to variables
  new_tuple->n = cols;
  new_tuple->nz = 0;
  sp_tuples_node *head_node = NULL;
  sp_tuples_node *next_node = NULL;
  while (fscanf(open, "%d %d %lf", &row, &col, &value) != EOF){  // While loop to check if values are not zero
    if (value != 0){
      head_node = (sp_tuples_node *)malloc(sizeof(struct sp_tuples_node)); // assigning memory for Tuple
      head_node->row = row; // Assigning values to variables
      head_node->col = col;
      head_node->value = value;
      head_node->next = next_node;
      new_tuple->nz++;
      next_node = head_node;
    }
  }
  fclose(open);
  new_tuple->tuples_head = next_node;
  sp_tuples_node *temp_node = NULL; // Assigning NULL Pointers
  sp_tuples_node *head_updater = NULL;
  sp_tuples_node *last_node = NULL;
  sp_tuples_node *new_node = NULL;
  sp_tuples_node *middle_node = NULL;
  for (i = 0; i < new_tuple->nz; i++){ // For loop for all non-zero tuples
    new_node = next_node;
    temp_node = new_node;
    last_node = NULL;
    middle_node = NULL;
    while (new_node != NULL){
      if (new_node->row * new_tuple->m + new_node->col > temp_node->row * new_tuple->m + temp_node->col){
        temp_node = new_node;
        last_node = middle_node;
      }
      middle_node = new_node;
      new_node = new_node->next;
    }
    if (temp_node == next_node){
      next_node = next_node->next;
    }
    if (last_node != NULL){
      last_node->next = temp_node->next;
    }
    temp_node->next = head_updater;
    head_updater = temp_node;
  }
  new_tuple->tuples_head = head_updater;
  return new_tuple;
}
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
  sp_tuples_node *next_node;
  next_node = mat_t->tuples_head;
  while(next_node->next != NULL){
    if(next_node->row == row && next_node->col == col) // Finding the row list
      return next_node->value;
    next_node = next_node->next;
  }
  return 0;
}
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  sp_tuples_node *last_node = NULL;
  sp_tuples_node *next_node = mat_t->tuples_head;
  int match = 0;
  while(next_node->next != NULL){ // Finding all non-zero values
    if(next_node->row >= row && next_node->col >= col && match == 0){
      sp_tuples_node *add_node = (sp_tuples_node *)malloc(sizeof(struct sp_tuples_node));
      add_node->row = row; // Setting variable values
      add_node->col = col;
      add_node->value = value;
      add_node->next = next_node;
      last_node->next = add_node;
    }
    if(next_node->row == row && next_node->col == col){
      match = 1;
      if(value == 0){
        last_node->next = next_node->next;
        free(next_node); // Deleting zero-valued nodes
      }
      else{
        next_node->value = value;
      }
    }
    last_node = next_node;
    next_node = next_node->next;
  }
  return;
}
void save_tuples(char * file_name, sp_tuples * mat_t){
  if(mat_t != NULL){ // Finding all non-zero tuples
    FILE *open;
    open = fopen(file_name, "w"); // Opening file to write
    fprintf(open, "%d %d\n", mat_t->m, mat_t->n); // Printing values to label the matrix
    sp_tuples_node *ctuple = mat_t->tuples_head;
    while (ctuple != NULL){
      fprintf(open, "%d %d %lf\n", ctuple->row, ctuple->col, ctuple->value); // Printing rows, columns and values
      ctuple = ctuple->next;
    }
    fclose(open); // Closing file
  }
  return;
}
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  if(matA == NULL || matB == NULL || matA->m != matB->m || matA->n != matB->n)
    return NULL; // Base Case
  sp_tuples *sum = (sp_tuples *)malloc(sizeof(struct sp_tuples)); // Allocating memory for new tuple, with pointer
  sum->m = matA->m;
  sum->n = matA->n;
  sum->nz = 0;
  sp_tuples_node *anode = matA->tuples_head;
  sp_tuples_node *bnode = matB->tuples_head;
  sp_tuples_node *last_node = NULL;
  int tracker = 1;
  while(anode != NULL || bnode != NULL){ // Finding non-zero nodes
    sp_tuples_node *next_node = (sp_tuples_node *)malloc(sizeof(struct sp_tuples_node));
    if(anode == NULL){ // Finding NULL nodes in matA
      next_node->row = bnode->row; // Setting variable values
      next_node->col = bnode->col;
      next_node->value = bnode->value;
      next_node->next = NULL;
      if(last_node != NULL)
        last_node->next = next_node;
      last_node = next_node;
      bnode = bnode->next;
    }
    else if(bnode == NULL){ // Finding NULL nodes in matB
      next_node->row = anode->row; // Setting variable values
      next_node->col = anode->col;
      next_node->value = anode->value;
      next_node->next = NULL;
      if(last_node != NULL)
        last_node->next = next_node;
      last_node = next_node;
      anode = anode->next;
    }
    else if(anode->row < bnode->row){ // Code condition for rows for row matA and row matB
      next_node->row = anode->row; // Setting variable values
      next_node->col = anode->col;
      next_node->value = anode->value;
      next_node->next = NULL;
      if(last_node != NULL)
        last_node->next = next_node;
      last_node = next_node;
      anode = anode->next;
    }
    else if(bnode->row < anode->row){ // Code condition for rows for row matB and row matA
      next_node->row = bnode->row; // Setting variable values
      next_node->col = bnode->col;
      next_node->value = bnode->value;
      next_node->next = NULL;
      if(last_node != NULL)
        last_node->next = next_node;
      last_node = next_node;
      bnode = bnode->next;
    }
    else{
      if(anode->col < bnode->col){ // Loop checking rules for cols for matA and matB
        next_node->row = anode->row; // Setting variable values
        next_node->col = anode->col;
        next_node->value = anode->value;
        next_node->next = NULL;
        if(last_node != NULL)
          last_node->next = next_node;
        last_node = next_node;
        anode = anode->next;
      }
      else if(bnode->col < anode->col){ // Code condition for cols for col matA and col matB
        next_node->row = bnode->row; // Setting variable values
        next_node->col = bnode->col;
        next_node->value = bnode->value;
        next_node->next = NULL;
        if(last_node != NULL)
          last_node->next = next_node;
        last_node = next_node;
        bnode = bnode->next;
      }
      else{
        next_node->row = bnode->row; // Setting variable values
        next_node->col = bnode->col;
        next_node->value = anode->value + bnode->value;
        next_node->next = NULL;
        if(last_node != NULL)
          last_node->next = next_node;
        last_node = next_node;
        anode = anode->next;
        bnode = bnode->next;
      }
    }
    sum->nz++; // Incrementing sum
    if (tracker == 1){
      sum->tuples_head = next_node; // Setting next_node
      tracker = 0;
    }
  }
  return sum;
}
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
  sp_tuples *retmat = malloc(sizeof(sp_tuples));
  retmat->tuples_head = NULL;
  return retmat;
}
void destroy_tuples(sp_tuples * mat_t){
  if (mat_t != NULL){ // Finding all non-zero tuples
    sp_tuples_node *ctuple = mat_t->tuples_head;
    sp_tuples_node *ftuple = NULL;
    while (ctuple != NULL){
      ftuple = ctuple;
      ctuple = ctuple->next;
      free(ftuple); // Freeing all non-zero elements
    }
    free(mat_t->tuples_head); // Freeing entire tuple and matrix.
  }
  return;
}
