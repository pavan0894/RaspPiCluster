/*
Author Name: Pavan Amarnath
Program : TO compute the run time of the program

   DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

   Copyright 2009 Sun Microsystems, Inc. All rights reserved.

   The contents of this file are subject to the terms of the BSD License("BSD")(the "License"). 
   You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt

   The BSD License

   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:

       * Redistribution of source code must retain the above copyright 
         notice, this list of conditions and the following disclaimer.
       * Redistribution in binary form must reproduce the above copyright 
         notice, this list of conditions and the following disclaimer in 
         the documentation and/or other materials provided with the 
         distribution.
       * Neither the name of Sun Microsystems, Inc. or the names of 
         contributors may be used to endorse or promote products derived 
         from this software without specific prior written permission.

   This software is provided "AS IS," without a warranty of any kind. ALL 
   EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY 
   IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
   NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND 
   ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A 
   RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. 
   IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT 
   OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR 
   PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
   ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS 
   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   You acknowledge that this software is not designed, licensed or intended for 
   use in the design, construction, operation or maintenance of any nuclear facility. 

*/

#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

void mxv(int row, int col, double *  a,
         double *  b, double *  c);

int main(int argc, char *argv[])
    
{
   double *a,*b,*c;//initlization
   int i, j, row,col, numOfThr, start, end;//initilization

   omp_set_num_threads(16);//changing the number of threads

   printf("Please Enter the Dimension of the Matrix row and col : ");
   scanf("%d %d",&row,&col);//reading the value
   printf("\n"); //new line

   if ( (a=(double *)malloc(row*sizeof(double))) == NULL )
      perror("memory allocation for a");//memory allocation
   if ( (b=(double *)malloc(row*col*sizeof(double))) == NULL )
      perror("memory allocation for b"); //memory allocation
   if ( (c=(double *)malloc(col*sizeof(double))) == NULL )
      perror("memory allocation for c");

   printf("\n Initializing matrix B and vector c\n"); //print statement
   for (j=0; j<col; j++)//computation of matrix multiplication
      c[j] = 2.0;
   for (i=0; i<row; i++)
      for (j=0; j<col; j++)
         b[i*col+j] = i; //execusion of matrixmul

   printf("\n Executing mxv function for row = %d col = %d\n",row,col);
   // start = omp_get_wtime();

   (void) mxv(row,col, a, b, c);

   // end = omp_get_wtime();
   // printf("Time of computation: %f\n", end - start);

   free(a);free(b);free(c); //freeing the memory that was allocated before in the program
   return(0);
}

void mxv(int row, int col, double *a, double *b, double *c)
{

   int i, j; 
  double start_time, end_time;

   start_time = omp_get_wtime(); //starttime computation

#pragma omp parallel for default(none) \
        shared(row,col,a,b,c) private(i,j)
  
   for (i=0; i<row; i++)
   {
      a[i] = 0.0;
      for (j=0; j<col; j++)
         a[i] += b[i*col+j]*c[j];
   } /*-- End of omp parallel for --*/

   end_time = omp_get_wtime(); //end time for time computation
  printf("\n Time of computation: %f sec\n", (end_time - start_time));//printing the time in milli seconf
   // printf("\nTime of Computation: %f\n ",end_time - start_time);
   printf("\n Time of computation: %f milli sec\n", (end_time - start_time)*1000);//printing the time in milli seconf
  printf("\n Time of computation: %f micro sec\n", (end_time - start_time)*1000000);//printing the time in micro second
  printf("\n Time of computation: %f nano sec\n", (end_time - start_time)*1000000000);//printing the time in nano second
  printf("\n Time of computation: %f pico sec\n", (end_time - start_time)*1000000000000);//printing the time in peco second

}
