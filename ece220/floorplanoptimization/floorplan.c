//Partners: ddamani2, ronitk2
#include "floorplan.h"
// This MP uses trees and traversal to implement a floorplanner to layout a set
// of rectangles to optimize the packing area. Several functions are used in
// this process. Is_leaf_node returns whether the node is a leaf (does it have
// children?) or not. Is_internal_node returns if the node is internal (opposite
// of leaf) or not. Is_in_subtree returns whether one node is in the direct
// "family tree" of the other node or not. Rotate switches the height and width.
// Recut switches the orientation from vertical to horizontal and vice versa.
// Swap_module switches the modules of two nodes. Swap_topology switches the
// "family trees" or subtrees of two nodes. Get_total_resource returns the sum
// of all resources on the tree. Init_slicing_tree uses recursion to slice a
// tree either vertically or horizontally one at a time. Get_expression uses a
// helper function postfix_traversal to assign expressions to the nodes.
// partners: gtandon3, ddamani2
// Global variables. The global variables will be effectice after the input has been parsed
// by calling the procedure read_module.
int num_modules;                                            // # of input modules.
module_t* modules;                                          // Array for modules.
// Procedure: floorplan
// The major procedure of the floorplan. The procedure concists of the following major steps:
// - initialize the slicing tree.
// - print the information of the slicing tree.
// - perform the optimization process.
void floorplan(const char file[]) {
 
  /*printf("\n********************************** MP11 **********************************\n");
  // Read the modules from the given input file.
  read_modules(file);
  // Initialize the slicing tree. You can replace the function init_slicing_tree with the function
  // challenge_init_slicing_tree if you accomplish the challenge implementation.
  node_t* root = init_slicing_tree(NULL, 0);
  int num_nodes = (num_modules << 1) - 1;
  printf("Initial slicing tree: Root=%p, num_nodes=%d, num_modules=%d\n", root, num_nodes, num_modules);
  // Obtain the expression of the initial slicing tree.
  expression_unit_t* expression = (expression_unit_t*)calloc(num_nodes, sizeof(expression_unit_t));
  get_expression(root, num_nodes, expression);
  printf("Initial expression: ");
  pnt_expression(expression, num_nodes);    
  double area = packing(expression, num_nodes);
  printf("Initial area: %.5e\n", area);
  draw_modules("init.png");
  free(expression);
  // Perform the optimization process.
  printf("Perform optimization...\n");
  area = optimize(root, num_nodes);
  pnt_modules();
  printf("Packing area = %.5e (has overlapped? %d (1:yes, 0:no))\n", area, is_overlapped());
  // Output your floorplan.
  printf("Draw floorplan to %s\n", outfile);
  draw_modules(outfile);
 
  printf("********************************** END ***********************************\n");*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS/PROCEDURES YOU HAVE TO FINISH.                                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////
// Function: is_leaf_node
// Return 1 if the given slicing tree node is a leave node, and 0 otherwise.
int is_leaf_node(node_t* ptr) {
  // TODO: (remember to modify the return value appropriately)
  if (ptr->left == NULL && ptr->right == NULL)  // if node has no children
    return 1;  // is a leaf
  return 0; // else is not a leaf
}
// Function: is_internal_node
// Return 1 if the given slicing tree node is an internal node, and 0 otherwise.
int is_internal_node(node_t* ptr) {
  // TODO: (remember to modify the return value appropriately)
  if (ptr->left == NULL && ptr->right == NULL)  // if node has no children
    return 0;  // is not internal node
  return 1;  // else is internal node
}
// Function: is_in_subtree
// Return 1 if the given subtree rooted at node 'b' resides in the subtree rooted at node 'a'.
int is_in_subtree(node_t* a, node_t* b) {
  // TODO: (remember to modify the return value appropriately)
  if (a == b)  // if a and b are the same node
    return 1;  // b is in subtree of a
  if (is_internal_node(a) == 1)  // if a is internal node
    return is_in_subtree(a->left,b) + is_in_subtree(a->right,b);  // check if b is in subtree
  return 0;  // b is not in subtree
}
// Procedure: rotate
// Rotate a module from a given leave node of the slicing tree by 90 degree. That is, the height
// and the width of the modules are swapped.
void rotate(node_t* ptr) {
  // TODO:
  int storage = ptr->module->h;  // storage variable for height
  ptr->module->h = ptr->module->w;  // store width in height
  ptr->module->w = storage;  // store height in width from storage
}
// Procedure: recut
// Change the cutline of a module in a given internal node of the slicing tree.
// If the original cutline is a vertical cutline, the resulting cutline should be changed to
// horizontal and vice versa.
void recut(node_t* ptr) {
  if(!is_internal_node(ptr)) return;
  assert(ptr->module == NULL && ptr->cutline != UNDEFINED_CUTLINE);
  // TODO:
  if (ptr->cutline == H)  // if cutline is horizontal
    ptr->cutline = V;  // make cutline vertical
  else if (ptr->cutline == V)  // if cutline is vertical
    ptr->cutline = H;  // make cutline horizontal
  return;
}
// Procedure: swap_module
// Swap the two modules between two given leave nodes in the slicing tree.
void swap_module(node_t* a, node_t* b) {
  if(!is_leaf_node(a) || !is_leaf_node(b)) return;
  assert(a->module != NULL && a->cutline == UNDEFINED_CUTLINE);
  assert(b->module != NULL && b->cutline == UNDEFINED_CUTLINE);
  // TODO:
  module_t *storage = b->module;  // use storage variable for b module
  b->module = a->module;  // store a module in b module
  a->module = storage;  // store b module in a module using storage
}
// Procedure: swap_topology
// Swap the topology of two subtrees rooted at two given nodes of the slicing tree.
// The procedure applies "is_in_subtree" first to tell if any of the subtree belongs
// to a part of the other.
void swap_topology(node_t* a, node_t* b) {
  if(a == NULL || b == NULL) return;
  if(a->parent == NULL || b->parent == NULL) return;
  if(is_in_subtree(a, b) || is_in_subtree(b, a)) return;
  assert(a->parent != NULL && b->parent != NULL);
 
  // TODO:
  node_t *storage = a;  // use storage variable for node a
  node_t *storageA = a->parent;  // use storage variable for node a parent
  node_t *storageB = b->parent;  // use storage variable for node b parent
  if (a->parent->right == a){  // if a is the right node
    storageA->right = b;  // make b the right child of a parent
    b->parent = storageA;  // place a parent in place of b parent
  }
  else if (a->parent->left == a){  // if a is the left node
    storageA->left = b;  // make b the left child of a parent
    b->parent = storageA;  // place a parent in place of b parent
  }
  if (storageB->right == b){  // if b is the right node
    storageB->right = storage;  // make a the right child of b parent
    storage->parent = storageB;  // place b parent in place of a parent
  }
  else if (storageB->left == b){  // if b is the left node
    storageB->left = storage;  // make a the left child of b parent
    storage->parent = storageB;  // place b parent in place of a parent
  }
}
// Procedure: get_expression
// Perform the post-order traversal on the given slicing tree and stores the polish expression
// into the given expression array. You should assume the expression array is pre-allocated with
// size N. In other words, you don't have to perform dynamic memory allocation. In fact, there
// is no need for you to add any code here, but it would be better if you can understand the
// details of this procedure especially the last two lines where the procedure postfix_traversal
// is called internally to obtain the expression.
void get_expression(node_t* root, int N, expression_unit_t* expression) {
  int i;  // declare int
  // Clear the expression.
  for(i=0; i<N; ++i) {  // traverse through array
    expression[i].module = NULL; // set module to NULL
    expression[i].cutline = UNDEFINED_CUTLINE;  // set cutline to UNDEFINED_CUTLINE
  }
  // Obtain the expression using the postfix traversal.
  int nth = 0;  // initialize nth
  postfix_traversal(root, &nth, expression);  // traverse through array
}
// Procedure: postfix_traversal
// Perform the postfix traversal on the slicing tree and store the corresponding polish expression
// to the given expression array. You should use the pointer "nth" to find out the index of the
// expression array and write the data accordingly. Notice that the expression array is a sequence
// of expression units which could be either a module pointer or the cutline type. If the module
// pointer exists in the expression unit, you should set the corresponding cutline type to
// "UNDEFINED_CUTLINE". On the other hand, if the expression unit is a cutline type, you should
// assign NULL to the corresponding module pointer.
void postfix_traversal(node_t* ptr, int* nth, expression_unit_t* expression) {
 
  if(ptr == NULL) return;
  // TODO:
  postfix_traversal(ptr->left, nth, expression);  // traverse through left children
  postfix_traversal(ptr->right, nth, expression);  // traverse through right children
  int i = *nth;  // initialize variable for data at nth address
  if (ptr->module != NULL){  // if module is not NULL
    expression[i].cutline = UNDEFINED_CUTLINE;  // set cutline to UNDEFINED_CUTLINE
    expression[i].module = ptr->module;  // set module to ptr module
  }
  if (ptr->cutline != UNDEFINED_CUTLINE){  // if cutline is not UNDEFINED_CUTLINE
    expression[i].cutline = ptr->cutline;  // set cutline to ptr cutline
    expression[i].module = NULL;  // set module to NULL
  }
  (*nth)++;  // increment data at nth address
  return;
}
// get_total_resource
// traverse through the tree and return the sum of all resource for each module
int get_total_resource(node_t* ptr)
{
  // TODO:
  int resources = 0;  // initialize variable
  if (ptr->right == NULL && ptr->left == NULL)  // if ptr has no children
    return ptr->module->resource;  // return resource at ptr module
  if (ptr->right != NULL)  // if ptr has right child
    resources = resources + get_total_resource(ptr->right);  // add resource
  if (ptr->left != NULL)  // if ptr has left child
    resources = resources + get_total_resource(ptr->left);  // add resource
  return resources;  // return sum of resources
}
// Procedure: init_slicing_tree
// Initialize the slicing tree by aligning modules along the horizontal line. In this procedure
// you should produce a left-skewed tree. The right child of any internal node should be a leave
// node and the subtree is recursively expanded down to the left. Take 5 modules for an example.
// The resulting tree should look like:
/*
                      root
                      /  \
                     i1  m0
                    /  \
                   i2  m1
                  /  \
                 i3  m2
                /  \
               m4  m3
*/ 
// where the prefix i denotes an internal node (including root), and the prefix m denotes a leave
// node. Notice that each node is either an internal in which the cutline type is specified or
// a leave in which the module pointer is assigned. For an internal node, the value of its module
// pointer should be assigned by NULL. For a leave node, the value of its cutline type should be
// specified as "UNDEFINED_CUTLINE".
//
// In each recursive step of this function, you are passed by a parent pointer pointing to the
// parent node of which node you will generate at this step, as well as an integer index n
// indicating the depth of the current recursion and the index of the module array to which the
// module pointer of the leave node should point to.
//
node_t* init_slicing_tree(node_t* par, int n) {
 
  assert(n >= 0 && n < num_modules);
  // TODO:
  if (n == num_modules - 1){ // if the index equals  modules - 1
    node_t* left_node = (node_t*)malloc(sizeof(node_t)); // allocate memory for left node
    left_node->cutline = UNDEFINED_CUTLINE;  // set cutline
    left_node->module = &(modules[n]);  // set module to pointer
    left_node->right = NULL;  // set right child
    left_node->left = NULL;  // set left child
    left_node->parent = par;  // set parent
    par->left = left_node;  // set node as child of par
    node_t* right_node = (node_t*)malloc(sizeof(node_t));  // allocate memory for right node
    right_node->cutline = UNDEFINED_CUTLINE;  // set cutline
    right_node->module = &(modules[n-1]);  // set module to pointer
    right_node->right = NULL;  // set right child
    right_node->left = NULL;  // set left child
    right_node->parent = par;  // set parent
    par->right = right_node;  // set node as child of par
    return left_node;  // return node
  }
  node_t* left_node = (node_t*)malloc(sizeof(node_t));  // allocate memory for left node
  left_node->cutline = V;  // set cutline to vertical
  left_node->module = NULL;  // set module
  left_node->parent = par;  // set parent
  if (par != NULL){  // if there is a parent
    node_t* right_node = (node_t*)malloc(sizeof(node_t));  // allocate memory for right node
    right_node->cutline = UNDEFINED_CUTLINE;  // set cutline
    right_node->module = &(modules[n-1]);  // set module to pointer
    right_node->right = NULL;  // set right child
    right_node->left = NULL;  // set left child
    par->left = left_node;  // set parent to left node
    right_node->parent = par;  // set parent of right node to par
    par->right = right_node;  // set child of par to right node
  }
  init_slicing_tree(left_node,n+1);  // use recursion to continue slicing
  return left_node;  // return node
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// PREDEFINED FUNCTIONS AND PROCEDURES.                                                          //
// PLEASE DO NOT MODIFY ANY FIELD STARTING HERE.                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////
// Function: is_overlapped
// Return 1 if any overlaps among modules, and 0 otherwise.
int is_overlapped() {
  int i, j;
  int llxi, llyi, urxi, uryi;
  int llxj, llyj, urxj, uryj;
  int flag = 0;
  for(i=0; i<num_modules; ++i) {
    llxi = modules[i].llx;
    llyi = modules[i].lly;
    urxi = llxi + modules[i].w;
    uryi = llyi + modules[i].h;      
    for(j=i+1; j<num_modules; ++j) {
     llxj = modules[j].llx;
     llyj = modules[j].lly;
     urxj = llxj + modules[j].w;
     uryj = llyj + modules[j].h;
     int rxu = MIN(urxi, urxj);
     int ryu = MIN(uryi, uryj);
     int rxl = MAX(llxi, llxj);
     int ryl = MAX(llyi, llyj);
     if(rxu>rxl && ryu>ryl) {
       flag = 1;
       printf("module %d and %d overlaps.\n", modules[i].idx, modules[j].idx);
     }
    }
  }
  return flag;
}
// Procedure: pnt_expression
// Print the expression to the display.
void pnt_expression(expression_unit_t *expression, int N) {
  if(!is_valid_expression(expression, N)) {
    printf("Invalid expression. Can't print. Please check your get_expression procedure.\n");  
    return;
  }
  int i;
  for(i=0; i<N; ++i) {
    if(expression[i].cutline == UNDEFINED_CUTLINE) {
      assert(expression[i].module != NULL);
      printf("%d", expression[i].module->idx);
    }
    else {
      assert(expression[i].module == NULL);
      printf("%c", expression[i].cutline == V ? 'V' : 'H');
    }
  }
  putchar('\n');
}
// Procedure: pnt_modules
// Print the coordinates of each module.
void pnt_modules() {
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("Module %d is placed at (%d, %d) with height=%d and width=%d\n",
            modules[i].idx,
            modules[i].llx,
            modules[i].lly,
            modules[i].h,
            modules[i].w);
  }
}
// Procedure: write_modules
// Write the coordinates of each module into a file.
void write_modules(const char file[]) {
  FILE *ofp = fopen(file, "w");
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("%d %d %d %d %d\n",
            modules[i].idx,
            modules[i].llx,
            modules[i].lly,
            modules[i].h,
            modules[i].w);
  }
  fclose(ofp);
}
// Function: get_module
// Return the module pointer to the module with the given idx.
module_t* get_module(int idx) {
  int i;
  for(i=0; i<num_modules; ++i) {
    if(idx == modules[i].idx) return &modules[i];
  }
  return NULL;
}
// Function: packing
// The main procedure of packing modules. The procedure takes the expression from the
// current slicing tree and then compute the coordinate of each module.
double packing(expression_unit_t* expression, int N) {
  if(!is_valid_expression(expression, N)) {
    return FLT_MAX;
  }
  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));
  // Iterates through the expression
  int i, j;
  cluster_t cluster, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      assert(expression[i].cutline == UNDEFINED_CUTLINE);      
      // Adjust the coordinate of the module.
      expression[i].module->llx = 0;
      expression[i].module->lly = 0;
      // Create a cluster.
      cluster.beg = i;
      cluster.end = i;
      cluster.w = expression[i].module->w;
      cluster.h = expression[i].module->h;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      assert(expression[i].cutline != UNDEFINED_CUTLINE);
      assert(stack_top >= 2);
      // Extract the top two clusters.
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];
     
      // Create a new cluster.
      cluster.beg = cluster_l.beg;
      cluster.end = cluster_r.end;
      // Horizontal cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - x coordinate doesn't change.
      if(expression[i].cutline == H) {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->lly += cluster_l.h;
        }
        cluster.w = cluster_l.w > cluster_r.w ? cluster_l.w : cluster_r.w;
        cluster.h = cluster_l.h + cluster_r.h;
      }
      // Vertical cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - y coordinate doesn't change.
      else {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->llx += cluster_l.w;
        }
        cluster.w = cluster_l.w + cluster_r.w;
        cluster.h = cluster_l.h > cluster_r.h ? cluster_l.h : cluster_r.h;
      }
      // Insert the cluster into the stack.
      stack[stack_top++] = cluster;
    }
  }
  assert(stack_top == 1);
  double area = (double)stack[stack_top - 1].w * (double)stack[stack_top - 1].h;
 
  free(stack);
  return area;
}
// Function: is_valid_expression
int is_valid_expression(expression_unit_t* expression, int N) {
  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));
  // Iterates through the expression
  int i;
  cluster_t cluster = {0, 0, 0, 0}, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      if(expression[i].cutline != UNDEFINED_CUTLINE) return 0;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      if(expression[i].cutline == UNDEFINED_CUTLINE) return 0;
      if(stack_top < 2) return 0;
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];
      stack[stack_top++] = cluster;
    }
  }
  free(stack);
  return stack_top == 1;
}
// Procedure: read_modules
// Read the modules from a given input file and initialize all required data structure.
void read_modules(const char file[]) {
 
  int i;
  FILE* ifp = fopen(file, "r");
  assert(ifp != NULL);
 
  // Read the number of modules.
  assert(fscanf(ifp, "%d", &num_modules) == 1);
  assert(num_modules >= 2);
 
  // Allocate the memory.
  modules = (module_t*)malloc(num_modules*sizeof(module_t));
  // Read the modules one by one.
  for(i=0; i<num_modules; ++i) {
    assert(fscanf(ifp, "%d %d %d %d", &modules[i].idx, &modules[i].w, &modules[i].h, &modules[i].resource) == 4);
    modules[i].llx = 0;
    modules[i].lly = 0;
  }
  fclose(ifp);
}
// Procedure: copy_expression
void copy_expression(expression_unit_t* lhs, expression_unit_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(expression_unit_t));
}
// Procedure: copy_modules
void copy_modules(module_t* lhs, module_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(module_t));
}
// Function: accept_proposal
// Accept the proposed solution.
int accept_proposal(double current, double proposal, double temperature) {
  if(proposal < current) return 1;
  if(temperature <= FROZEN) return 0;
  double prob = exp(-(double)(proposal - current) / temperature);
  return rand()/(double)RAND_MAX < prob;
}
// Function: get_rand_internal
node_t* get_rand_internal(node_t** internals, int num_internals) {
  return internals[rand()%num_internals];
}
// Function: get_rand_leave
node_t* get_rand_leave(node_t** leaves, int num_leaves) {
  return leaves[rand()%num_leaves];
}
// Function: get_random_node
node_t* get_rand_node(node_t** internals, int num_internals, node_t** leaves, int num_leaves) {
  if(rand()%2) {
    return get_rand_leave(leaves, num_leaves);
  }
  return get_rand_internal(internals, num_internals);
}
// Function: optimize
// Optimize the area of the floorplanner.
double optimize(node_t *root, int num_nodes) {
 
  // Storage for leave and internal nodes.
  int head = 0;
  int tail = 0;
  int num_leaves = 0;
  int num_internals = 0;
  node_t** queue = (node_t**)malloc(num_nodes*sizeof(node_t*));
  node_t** leaves = (node_t**)malloc(num_modules*sizeof(node_t*));
  node_t** internals = (node_t**)malloc((num_modules-1)*sizeof(node_t*));
  node_t* u;
  queue[tail++] = root;
  while(tail - head) {
    u = queue[head++];
   
    if(u->module) {
      assert(u->cutline == UNDEFINED_CUTLINE);
      leaves[num_leaves++] = u;
    }
    else {
      assert(u->cutline != UNDEFINED_CUTLINE);
      internals[num_internals++] = u;
    }
    if(u->left) queue[tail++] = u->left;
    if(u->right) queue[tail++] = u->right;
  }
  assert(num_leaves == num_modules);
  assert(num_internals == num_modules - 1);
  // Simulated annealing.
  srand(time(0));
  expression_unit_t* best_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  expression_unit_t* curr_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  module_t* best_modules = (module_t*)malloc(num_modules*sizeof(module_t));
 
  int i, key;
  double best_area, curr_area;
  double temperature = 100.0;
  node_t* a;
  node_t* b;
  // Initialization.
  get_expression(root, num_nodes, best_expression);
  best_area = packing(best_expression, num_nodes);
  memcpy(best_modules, modules, num_modules*sizeof(module_t));
  while(temperature > FROZEN) {
   
    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {
      key = rand()%4;
     
      switch(key) {
        // Perform recut.
        case 0:
          recut(get_rand_internal(internals, num_internals));
        break;
       
        // Perform rotate.
        case 1:
          rotate(get_rand_leave(leaves, num_leaves));
        break;
       
        // Perform swap_module.
        case 2:
          do {
            a = get_rand_leave(leaves, num_leaves);
            b = get_rand_leave(leaves, num_leaves);
          } while(a == b);
          swap_module(a, b);
        break;
       
        // Perform swap_topology.
        default:
          do {        
            a = get_rand_node(internals, num_internals, leaves, num_leaves);
            b = get_rand_node(internals, num_internals, leaves, num_leaves);
          } while(is_in_subtree(a, b) || is_in_subtree(b, a));
          swap_topology(a, b);
        break;
      }
      // Evaluate the area.
      get_expression(root, num_nodes, curr_expression);
      curr_area = packing(curr_expression, num_nodes);
      if(curr_area < best_area) {
        best_area = curr_area;
        copy_expression(best_expression, curr_expression, num_nodes);
        memcpy(best_modules, modules, num_modules*sizeof(module_t));
        //copy_modules(best_modules, modules, num_modules);
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }
  memcpy(modules, best_modules, num_modules*sizeof(module_t));
  best_area = packing(best_expression, num_nodes);
 
  /*// Secondary optimization.
  temperature = 100.0;
  while(temperature > FROZEN) {
   
    // Start at a step.
    copy_expression(curr_expression, best_expression, num_nodes);
    copy_modules(modules, best_modules, num_modules);
   
    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {
      copy_expression(next_expression, curr_expression, num_nodes);
      key = rand()%4;
     
      switch(key) {
        // Perform recut.
        case 0:
          do{
            j = rand() % num_nodes;
          } while(next_expression[j].cutline == UNDEFINED_CUTLINE);
          next_expression[j].cutline = next_expression[j].cutline == V ? H : V;
        break;
       
        // Perform rotate.
        case 1:
          do{
            j = rand() % num_nodes;
          } while(next_expression[j].module == NULL);
          next_expression[j].module->w = next_expression[j].module->w ^ next_expression[j].module->h;
          next_expression[j].module->h = next_expression[j].module->w ^ next_expression[j].module->h;
          next_expression[j].module->w = next_expression[j].module->w ^ next_expression[j].module->h;
         
        break;
       
        // Perform swap_module.
        case 2:
          do {
            j = rand() % num_nodes;
            k = rand() % num_nodes;
          } while(j == k || next_expression[j].module == NULL || next_expression[k].module == NULL);
          tmp = next_expression[k].module;
          next_expression[k].module = next_expression[j].module;
          next_expression[j].module = tmp;
        break;
       
        // Perform swap_topology.
        default:
          do {
            do{
              j = rand() % num_nodes;
              k = rand() % num_nodes;
            } while(j == k);
            e = next_expression[k];
            next_expression[k] = next_expression[j];
            next_expression[j] = e;
          } while (!is_valid_expression(next_expression, num_nodes));
        break;
      }
      // Evaluate the area.
      curr_area = packing(curr_expression, num_nodes);
      next_area = packing(next_expression, num_nodes);
      if(accept_proposal(curr_area, next_area, temperature)){
        if(next_area < best_area) {
          best_area = next_area;
          copy_expression(best_expression, next_expression, num_nodes);
        }
        copy_expression(curr_expression, next_expression, num_nodes);
        curr_area = next_area;
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }
  best_area = packing(best_expression, num_nodes);*/
 
  free(queue);
  free(leaves);
  free(internals);
  free(best_expression);
  free(curr_expression);
  free(best_modules);
  return best_area;
}
