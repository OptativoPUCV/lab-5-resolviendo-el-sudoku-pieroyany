#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int seen[10];
    for(int i = 0; i < 9; i++){
        for(int k = 0; k < 10; k++) seen[k] = 0;
        for(int j = 0; j < 9; j++){
            int num = n->sudo[i][j];
            if(num == 0) continue;
            if(seen[num]) return 0;
            seen[num] = 1;
        }
    }

    for(int j = 0; j < 9; j++){
        for(int k = 0; k < 10; k++) seen[k] = 0;
        for(int i = 0; i < 9; i++){
            int num = n->sudo[i][j];
            if(num == 0) continue;
            if(seen[num]) return 0;
            seen[num] = 1;
        }
    }

    for(int k = 0; k < 9; k++){
        for(int i = 0; i < 10; i++) seen[i] = 0;
        for(int p = 0; p < 9; p++){
            int row = 3*(k/3) + (p/3);
            int col = 3*(k%3) + (p%3);
            int num = n->sudo[row][col];
            if(num == 0) continue;
            if(seen[num]) return 0;
            seen[num] = 1;
        }
    }
    return 1;
}



List* get_adj_nodes(Node* n){
    List* list = createList();
    int row = -1, col = -1;

    for(int i = 0; i < 9 && row == -1; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                row = i;
                col = j;
                break;
            }
        }
    }
    
    if(row == -1) return list;

    for(int num = 1; num <= 9; num++){
        Node* new_node = (Node*) malloc(sizeof(Node));
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                new_node->sudo[i][j] = n->sudo[i][j];
            }
        }

        new_node->sudo[row][col] = num;

        if(is_valid(new_node)) {
            pushBack(list, new_node);
        } else {
            free(new_node);
        }
    }

    return list;
}


int is_final(Node* n){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0)
                return 0;
        }
    }
    return 1;
}


Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/