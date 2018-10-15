//rows and columns should be zero indexed!!

typedef struct sp_lils_col_node //a node in the list of columns in a row list.
{
	int idx_c;	//the current column
    double value;	//the element value at the current row and column
    struct sp_lils_col_node * next; 

} sp_lils_col_node;

typedef struct sp_lils_row_node //a node in the row list of sp_lils
{
    int idx_r; //the current row
    sp_lils_col_node * col_list_head; //list of columns in current row
    struct sp_lils_row_node * next; 

} sp_lils_row_node;


typedef struct sp_lils // list of lists format - stores a list of rows, each of which contains a list of columns.
{
    int m; //# of rows
    int n; //# of cols
    int nz; //# of non-zero entries in matrix

    sp_lils_row_node * row_list_head; //list of rows

} sp_lils;

// Read an input file and return a matrix
sp_lils * load_lils(char* input_file);

//given a matrix, return the value of the element in the matrix that corresponds to the given coordinates. coordinates are 0 indexed.
double gv_lils(sp_lils * mat_l,int row,int col);

//given a matrix, set the value of the element that corresponds to the given coordinates.
void set_lils(sp_lils * mat_l, int row, int col, double value); 

//Save the matrix to a text file.
void save_lils(char * file_name,sp_lils * mat_l);

//return a matrix that is the sum of matA and matB.
sp_lils * add_lils(sp_lils * matA, sp_lils * matB);

//return a matrix that is the product of matA and matB. Beware that matrix multiplication is not commutative e.g. matA*matB != matB*matA
//sp_lils * mult_lils(sp_lils * matA, sp_lils * matB);

//free any and all allocated space associated with the given matrix.
void destroy_lils(sp_lils * mat_l);

