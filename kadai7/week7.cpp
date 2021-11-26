#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

void divide(double &x,double &ddx);
void Euler_method(double &x_n0,double &x_n1,double &dx,double dt);
void Heun_method(double &x_n0,double &x_n1,double &dx,double &ddx,double dt);

int main(){
    FILE *fp1,*fp2;
	fp1=fopen("kadai7t_x.dat","w");
  fp2=fopen("kadai7x_dx.dat","w");

  int divide = 1000;

  double x_n0,dx_n0;
  double x;
  double x_n1,dx_n1;
  double dx;
  double ddx_n0;
  double C,a;
  double t,dt;

  dt = 0.01e0;

  t=0;
  x_n0 = 1;
  dx_n0 = 0;
  ddx_n0 =-1;

  fprintf(fp1,"%e %e\n",t,x_n0);
  fprintf(fp2,"%e %e\n",x_n0,dx_n0);

  for(int i=0;i<divide;i++){

    // divide(x_n0,ddx_n0);
    ddx_n0=-1*x_n0;

    Euler_method(dx_n0,dx_n1,ddx_n0,dt);
    // Euler_method(x_n0,x_n1,dx_n0,dt);

    // Heun_method(x_n0,x_n1,dx_n0,ddx_n0,dt);

    fprintf(fp1,"%e %e\n",dt * i,x_n1);
    fprintf(fp2,"%e %e\n",x_n1,dx_n1);

    x_n0 =x_n1;
    dx_n0 =dx_n1;

  }

  fclose(fp1);
  fclose(fp2);

	return 0;
}

void divide(double &x,double &ddx){
  ddx = -x;
}

void Euler_method(double &x_n0,double &x_n1,double &dx,double dt){

  x_n1=x_n0+dt*dx;

}

void Heun_method(double &x_n0,double &x_n1,double &dx,double &ddx,double dt){

  x_n1=x_n0+dx*dt+1e0/2e0*ddx*dt*dt;
}


