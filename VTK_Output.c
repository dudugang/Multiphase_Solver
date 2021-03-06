#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

#include "fvm.h"

void Write_VTK(int q,Domain domain,Constant constant)
{
  
  char filename[30]; 
  sprintf(filename, "output_%05d.vtk",q);
  FILE *fp = fopen(filename, "w");

  int Nx = domain.p->N_x+1;
  int Ny = domain.p->N_y+1;
  int Nz = 2; //N_cells_z+1;
  
  int N_cells_y = domain.p->N_y;
  int N_cells_x = domain.p->N_x;
  int N_cells_z = domain.p->N_z;
  int N_cells = N_cells_x * N_cells_y * N_cells_z;
  
  fprintf(fp,"# vtk DataFile Version 3.0\n");     
  fprintf(fp,"particle point data\n");           
  fprintf(fp,"ASCII\n");                         
  fprintf(fp,"DATASET STRUCTURED_GRID\n");       
  fprintf(fp,"DIMENSIONS %d %d %d\n",Nx,Ny,Nz);  
  fprintf(fp,"POINTS %d double\n",Nx*Ny*Nz);
  
  int i,j,k;
  
  for(k = 0; k<Nz; k++)
  {
    for(j = 0; j<Ny; j++)
    {
      for(i = 0; i<Nx ;i++)
      {
        fprintf(fp,"%2.8lf %2.8lf %2.8lf\n",i*constant.dx , j*constant.dy, k*1.0);
      }
    }
  }
  
  fprintf(fp,"CELL_DATA %d\n SCALARS pressure double \n LOOKUP_TABLE default\n",N_cells);  
  
  for(j = 0; j<N_cells_y ; j++)
  {
    for(i = 0; i<N_cells_x; i++)
    {
      fprintf(fp,"%2.8lf\n",domain.p->val[j*N_cells_x + i]);
    }
  }
  
  fprintf(fp,"SCALARS density double \n LOOKUP_TABLE default\n");  
  
  for(j = 0; j<N_cells_y ; j++)
  {
    for(i = 0; i<N_cells_x; i++)
    {
      fprintf(fp,"%2.8lf\n",domain.rho->val[j*N_cells_x + i]);
    }
  }
  
  fprintf(fp,"SCALARS viscosity double \n LOOKUP_TABLE default\n");  
  
  for(j = 0; j<N_cells_y ; j++)
  {
    for(i = 0; i<N_cells_x; i++)
    {
      fprintf(fp,"%2.8lf\n",domain.mu->val[j*N_cells_x + i]);
    }
  }

  fprintf(fp,"SCALARS Void_Fraction double \n LOOKUP_TABLE default\n");  
  
  for(j = 0; j<N_cells_y ; j++)
  {
    for(i = 0; i<N_cells_x; i++)
    {
      fprintf(fp,"%2.8lf\n",domain.C->val[j*N_cells_x + i]);
    }
  }

  fprintf(fp,"VECTORS velocity double \n");  
  
  for(j = 0; j<domain.v->N_y ; j++)
  {
    for(i = 0; i<domain.u->N_x; i++)
    {
      fprintf(fp,"%2.8lf %2.8lf %2.8lf \n",domain.u->val[j*domain.u->N_x + i],
                                       domain.v->val[j*domain.v->N_x + i], 0.0 );
    }
  }
  
  fprintf(fp,"VECTORS Normal double \n");  
  
  for(j = 0; j<domain.v->N_y ; j++)
  {
    for(i = 0; i<domain.u->N_x; i++)
    {
      fprintf(fp,"%2.8lf %2.8lf %2.8lf \n",domain.nx->val[j*domain.nx->N_x + i],
                                       domain.ny->val[j*domain.ny->N_x + i], 0.0 );
    }
  }
  //  fprintf(fp,"%2.8lf %2.8lf %2.8lf\n", x.x, x.y, x.z);
  
  return;
}
