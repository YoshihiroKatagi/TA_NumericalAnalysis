#include<stdio.h>
#include<math.h>

#define a1 0.0
#define b1 1.0
#define a2 0.0
#define b2 1.0

double f1(double x)
{
  return 1.0/(1.0 + x*x);
}
double f2(double x)
{
  return std::exp(-1.0 * x*x);
}

double trapezoidal_rule(double a, double b, int n, double (* pfunc)(double))
{
  double S = 0.0;
  double h = (b-a)/ n;
  double x1 = a;
  double x2 = a + h;
  double y1, y2;

  for (int i=0;i<n;i++) {
    y1 = pfunc(x1);
    y2 = pfunc(x2);

    S += h * (y1 + y2) / 2.0;

    x1 = x2;
    x2 = x2 + h;
  }
  return S;
}
double midpoint_rule(double a, double b, int n, double (* pfunc)(double))
{
  double S = 0.0;
  double h = (b-a)/n;
  double x;
  double y;

  for (int i=0;i<n;i++) {
    x = a + h * (2*i + 1) / 2.0;
    y = pfunc(x);

    S += h * y;
  }
  return S;
}
double simpson_rule(double a, double b, int n, double (* pfunc)(double))
{
  double S = 0.0;
  double h = (b-a)/n;
  double x1 = a;
  double x2 = a + h/2.0;
  double x3 = a + h;
  double y1, y2, y3;

  for (int i=0;i<n;i++) {
    y1 = pfunc(x1);
    y2 = pfunc(x2);
    y3 = pfunc(x3);

    S += h * (y1 + 4*y2 + y3) / 6.0;

    x1 += h;
    x2 += h;
    x3 += h;
  }
  return S;
}

void calc_result(void)
{
  int n = 1, n_max = 20;

  char *FileName = "result1.csv";
  FILE *fp = fopen(FileName, "w");
  fprintf(fp, "n, trapezoidal, midpoint, simpson\n");

  char *Filename = "result2.csv";
  FILE *gp = fopen(Filename, "w");
  fprintf(gp, "n, trapezoidal, midpoint, simpson\n");

  while (n<=n_max){
    double S1 = trapezoidal_rule(a1,b1,n,f1);
    double S2 = midpoint_rule(a1,b1,n,f1);
    double S3 = simpson_rule(a1,b1,n,f1);
    
    double T1 = trapezoidal_rule(a2,b2,n,f2);
    double T2 = midpoint_rule(a2,b2,n,f2);
    double T3 = simpson_rule(a2,b2,n,f2);

    fprintf(fp, "%d, %f, %f, %f\n", n, S1, S2, S3);
    fprintf(gp, "%d, %f, %f, %f\n", n, T1, T2, T3);

    n += 1;
  }
}

int main(void)
{
  calc_result();
  return 0;
}