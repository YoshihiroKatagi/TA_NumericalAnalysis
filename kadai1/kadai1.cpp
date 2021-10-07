#include<stdio.h>

#define E 100000000000.0
#define alpha 0.00001
#define dT 100.0

struct Variable
{
  double A1;
  double A2;
  double L1;
  double L2;
  double sigma1;
  double sigma2;
  double delta1;
  double delta2;
};

void calc(Variable *Var)
{
  double A1 = Var->A1, A2 = Var->A2, L1 = Var->L1, L2 = Var->L2;

  Var->sigma1 = -1.0 * alpha * dT * E * A2 * (L1 + L2)
        / (A1 * L2 + A2 * L1);
  
  Var->sigma2 = -1.0 * alpha * dT * E * A1 * (L1 + L2)
        / (A1 * L2 + A2 * L1);

  Var->delta1 = (1 - A2 * (L1 + L2) / (A1 * L2 + A2 * L1)) * L1 * alpha * dT;

  Var->delta2 = (1 - A1 * (L1 + L2) / (A1 * L2 + A2 * L1)) * L2 * alpha * dT;
}




void calc_changeA1(void)
{
  double A1_min = 0.00005, A1_max = 0.00015, h = 0.000001;
  int N = (int) ((A1_max - A1_min) / h);
  Variable Var = 
  {
    A1_min, 0.00005, 1.0, 1.0, 0, 0, 0, 0
  };

  char *FileName = "result_changeA1.csv";
  FILE *fp = fopen(FileName, "w");
  fprintf(fp, "A1, sigma1, sigma2, delta1, delta2\n");

  for (int i=0; i < N+1; i++)
  {
    calc(&Var);

    fprintf(fp, "%f, %f, %f, %f, %f\n", Var.A1, Var.sigma1, Var.sigma2,
    Var.delta1, Var.delta2);

    Var.A1 += h;
  }

  fclose(fp);
}

void calc_changeL1(void)
{
  double L1_min = 0.5, L1_max = 1.5, h = 0.01;
  int N = (int) ((L1_max - L1_min) / h);
  Variable Var = 
  {
    0.0001, 0.00005, L1_min, 1.0, 0, 0, 0, 0
  };

  char *FileName = "result_changeL1.csv";
  FILE *fp =fopen(FileName, "w");
  fprintf(fp, "L1, sigma1, sigma2, delta1, delta2\n");

  for(int i=0; i<N+1; i++)
  {
    calc(&Var);

    fprintf(fp, "%f, %f, %f, %f, %f\n", Var.L1, Var.sigma1, Var.sigma2, Var.delta1, Var.delta2);

    Var.L1 += h;
  }

  fclose(fp);

  char labelName[5][7] = {"L1", "sigma1", "sigma2", "delta1", "delta2"};
}

int main(void)
{
  calc_changeA1();
  calc_changeL1();

  return 0;
}