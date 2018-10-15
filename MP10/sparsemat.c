#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


//Introductory paragraph starts here
//This program stores a sparse matrixby storing only nonzero elements
//it uses a data structure List of lists,
//that stores sparse matrices more efficiently than a 2-D array.
//The structure stores a list of rows, each of which sotres a list of nonzero elements in that row
//The program has several functions such as adding 2 matrices, returning value of
//the element at the given row and column, etc.
//Please read the program in Atom, or the format might look weird in other editors.




// Read an input file and return a matrix
sp_lils * load_lils(char* input_file)
{
    int row, col;
    double value;
    FILE *stream;
    stream = fopen(input_file, "r");  //create a stream
    sp_lils *list = (sp_lils *)malloc(sizeof(sp_lils));
    list->m = 0;
    list->n = 0;
    list->nz = 0;
    list->row_list_head = NULL;

    fscanf(stream, "%d %d", &list->m, &list->n);  //get number of rows and cols
    while(fscanf(stream, "%d %d %lf", &row, &col, &value) != EOF){
      set_lils(list, row, col, value);
    }
    return list;

}







//returns the value of the element at the given row and column within the matrix
double gv_lils(sp_lils * mat_l,int row,int col)
{
    sp_lils_row_node *current_row;
    sp_lils_col_node *current_col;


    current_row = mat_l->row_list_head;

    while(current_row != NULL){
      if(current_row->idx_r == row){  //find the row list
        current_col = current_row->col_list_head;
        while(current_col != NULL){
          if(current_col->idx_c == col){  //find the col node
            return current_col->value;
          }
          current_col = current_col->next;
        }
      }
      current_row = current_row->next;
    }
    return 0; //if the node with given row & col does not exist, return 0
}








//given a matrix, set the value of the element that corresponds to the given coordinates.
void set_lils(sp_lils * mat_l, int row, int col, double value)
{
  int done = 0;
  int isFirst = 1;

  sp_lils_row_node *current_row;
  sp_lils_col_node *current_col;
  sp_lils_col_node *prev_col;



  if(value == 0){ //if value is 0
    if(gv_lils(mat_l, row, col) != 0){  //if the node at row and col exists
      //delete the node from the list
      current_row = mat_l->row_list_head;
      while(current_row != NULL){
        if(current_row->idx_r == row){  //find the row list
          current_col = current_row->col_list_head;
          prev_col = current_row->col_list_head;
          while(current_col != NULL){
            if(current_col->idx_c == col){  //find the col node
              if(isFirst == 1 && current_col->next == NULL){ //if it is the last entry, delete the row

              }
              else{ //delete the col node
                prev_col->next = current_col->next;
                free(current_col);
                mat_l->nz --;
              }
            }
            prev_col = current_col;
            current_col = current_col->next;
            isFirst = 0;
          }
        }
        current_row = current_row->next;
      }
    }
  }


  else{ //for any other value
    if(gv_lils(mat_l, row, col) != 0){ //if the node at row and col exists
      //replace the value
      current_row = mat_l->row_list_head;
      while(current_row != NULL){
        if(current_row->idx_r == row){  //find the row list
          current_col = current_row->col_list_head;
          while(current_col != NULL){
            if(current_col->idx_c == col){  //find the col node
              current_col->value = value;  //replace the value
            }
            current_col = current_col->next;
          }
        }
        current_row = current_row->next;
      }
    }


    else{ //if the entry does not exist, create & insert a new node

      //first check whether the row node exists
      current_row = mat_l->row_list_head;
      while(current_row != NULL){
        if(current_row->idx_r == row){  //if the row is found, we only need to create & insert a col node
          sp_lils_col_node *new_col = (sp_lils_col_node *)malloc(sizeof(sp_lils_col_node));
          new_col->idx_c = col;
          new_col->value = value;

          //insert the col node into the right space
          current_col = current_row->col_list_head;
          while(current_col->next != NULL && current_col->next->idx_c < new_col->idx_c){
            current_col = current_col->next;
          }
          new_col->next = current_col->next;
          current_col->next = new_col;
          done = 1;
          mat_l->nz++;
        }
        current_row = current_row->next;
      }

      if(done != 1){  //if the row node is not found, then we create a row node and a col node
        sp_lils_row_node *new_row = (sp_lils_row_node *)malloc(sizeof(sp_lils_row_node));
        new_row->idx_r = row;

        current_row = mat_l->row_list_head;
        //if this is the first row node created
        if (current_row == NULL || current_row->idx_r > new_row->idx_r){
          new_row->next = NULL;
          mat_l->row_list_head = new_row;
        }
        else{
          while(current_row->next != NULL && current_row->next->idx_r < new_row->idx_r){
            current_row = current_row->next;
          }
          new_row->next = current_row->next;
          current_row->next = new_row;
        }
        //create col node
        sp_lils_col_node *new_col = (sp_lils_col_node *)malloc(sizeof(sp_lils_col_node));
        new_col->idx_c = col;
        new_col->value = value;
        new_col->next = new_row->col_list_head; //insert the new col node to the start
        new_row->col_list_head = new_col;
        mat_l->nz ++;
      }


    }
  }
	return;
}





//Save the matrix to a text file.
void save_lils(char * file_name,sp_lils * mat_l)
{
  FILE *outstream = fopen(file_name, "w");
  fprintf(outstream, "%d %d\n", mat_l->m, mat_l->n);  //print number of rows and cols

  sp_lils_row_node *current_row;
  sp_lils_col_node *current_col;


  current_row = mat_l->row_list_head;

  while(current_row != NULL){
      current_col = current_row->col_list_head;
      while(current_col != NULL){
        fprintf(outstream, "%d %d %lf\n", current_row->idx_r, current_col->idx_c, current_col->value);
        current_col = current_col->next;
      }
    current_row = current_row->next;
  }
	return;
}



//return a matrix that is the sum of matA and matB.
sp_lils * add_lils(sp_lils * matA, sp_lils * matB){

  sp_lils *matC = (sp_lils *)malloc(sizeof(sp_lils));
  matC->m = 0;
  matC->n = 0;
  matC->nz = 0;
  matC->row_list_head = NULL;

  matC->m = matA->m;  //duplicate number of rows and cols to the new matrix
  matC->n = matA->n;
  //first duplicate matA to matC since matC is empty
  sp_lils_row_node *current_row;
  sp_lils_col_node *current_col;

  current_row = matA->row_list_head;

  while(current_row != NULL){
      current_col = current_row->col_list_head;
      while(current_col != NULL){
        set_lils(matC, current_row->idx_r, current_col->idx_c, current_col->value);
        current_col = current_col->next;
      }
    current_row = current_row->next;
  }
  //add matB to the matrix
  current_row = matB->row_list_head;
  while(current_row != NULL){
      current_col = current_row->col_list_head;
      while(current_col != NULL){ //find a nonzero value
        if(gv_lils(matC, current_row->idx_r, current_col->idx_c) == 0){ //if matA does not have it
          set_lils(matC, current_row->idx_r, current_col->idx_c, current_col->value);
        }
        else{ //if matA has a value at same location
          set_lils(matC, current_row->idx_r, current_col->idx_c, current_col->value + gv_lils(matC, current_row->idx_r, current_col->idx_c));
        }
        current_col = current_col->next;
      }
    current_row = current_row->next;
  }
	return matC;
}







void destroy_lils(sp_lils * mat_l){
  sp_lils_row_node *current_row;
  sp_lils_col_node *current_col;


  current_row = mat_l->row_list_head;

  while(current_row != NULL){
      current_col = current_row->col_list_head;
      while(current_col != NULL){
        current_col = current_col->next;
        free(current_col);
      }
    current_row = current_row->next;
    free(current_row);
  }
  free(mat_l);
    return;
}
