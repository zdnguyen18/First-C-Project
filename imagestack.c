/** CS310 Project 1
File: imagestack.c
Name: Uyen Nguyen 
Date: 17th Oct
*/
#include<stdio.h>
#include <stdlib.h>
//cal index of col
int ind(int r, int c, int i, int n_cols, int n_mat) {
  return r * n_cols * n_mat + c * n_mat + i;
}

int comparator(const void *p, const void *q) 
{ 
    // Get the values at given addresses 
    int l = *(const int *)p; 
    int r = *(const int *)q; 
  
    // both odd, put the greater of two first. 
    if ((l&1) && (r&1)) 
        return (r-l); 
  
    // both even, put the smaller of two first 
    if ( !(l&1) && !(r&1) ) 
        return (l-r); 
  
    // l is even, put r first 
    if (!(l&1)) 
        return 1; 
  
    // l is odd, put l first 
    return -1; 
}
int main(int argc, char**argv)
{
    int n_rows=0, n_cols=0,n_mat= argc-2; 
    //n_mat total number of input files; 
    //argc is the total number of arguments in command line which is 2 more than n_mat 
    FILE *pmg_file1 = fopen(argv[1], "r");
    fscanf(pmg_file1,"P2\n%d %d \n255\n", &n_rows, &n_cols);
    fclose(pmg_file1);
    //create an array which has enough space to store all values in 9 input files
    int *arr = malloc(sizeof(int)*n_rows*n_cols*n_mat);
    //open each input file through for loop
    for (int i=0; i< n_mat; i++){
        //open the file at the same for reading
        FILE *pmg_file = fopen(argv[i+1], "r");
        fscanf(pmg_file,"P2\n%d %d\n255\n", &n_rows, &n_cols);
        //take one specific pixel with index func
	    for(int r = 0; r < n_rows; r++) {
	        for(int c = 0; c < n_cols; c++) {   
                fscanf(pmg_file, "%d\n", &arr[ind(r, c, i, n_cols, n_mat)]);
            }
        }
        fclose(pmg_file);
    }
//open a file for writing 
    FILE *output_file = fopen(argv[argc-1], "w"); 
    fprintf(output_file,"P2\n%d %d\n255\n", n_rows, n_cols); 
    for(int r = 0; r < n_rows; r++) {
        for(int c = 0; c < n_cols; c++) {
            //create new array to store n_mat values
            int *arr_median = malloc(sizeof(int)*n_mat);
            for (int i=0; i<n_mat; i++){
                //take value from pmg_file to value in new array
                //each input file has 1 index in the arr_median
                arr_median[i] = arr[ind(r, c, i, n_cols, n_mat)]; 
            }
            //sort the arr_median ASC using quick sort
            qsort(arr_median, n_mat, sizeof(int),comparator);
            //array has odd size -> median
            int median_value = arr_median[n_mat/2];
            //array has even size -> find median
            if ((n_mat%2)==0){
                median_value = (arr_median[n_mat/2-1] + arr_median[n_mat/2])/2;
            }
            fprintf(output_file, "%d\n", median_value);
            free(arr_median);
        }   
    }
    fclose(output_file);
  free(arr); //always need to free *arr after using malloc func
}