#include<stdio.h>
#include<math.h>

#define ans sqrt(M_PI)

#define A -1000.0
#define B  1000.0

int div_n = 50;
int div_n_max = 1500;
int div_n_interval = 10;

double f(double x)
{
  return exp(-1 * std::pow(x,2));
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
  char *FileName1 = "result.csv";
  FILE *fp = fopen(FileName1, "w");
  fprintf(fp, "n,trapezoidal,midpoint,simpson\n");
  char *FileName2 = "AbsoluteError.csv";
  FILE *gp = fopen(FileName2, "w");
  fprintf(gp, "n,trapezoidal,midpoint,simpson\n");
  char *FileName3 = "RelativeError.csv";
  FILE *hp = fopen(FileName3, "w");
  fprintf(hp, "n,trapezoidal,midpoint,simpson\n");

  while (div_n <= div_n_max){
    double S1 = trapezoidal_rule(A,B,div_n,f);
    double S2 = midpoint_rule(A,B,div_n,f);
    double S3 = simpson_rule(A,B,div_n,f);

    double AE1 = abs(ans - S1);
    double AE2 = abs(ans - S2);
    double AE3 = abs(ans - S3);

    double RE1 = abs((ans - S1) / ans);
    double RE2 = abs((ans - S2) / ans);
    double RE3 = abs((ans - S3) / ans);

    fprintf(fp, "%d, %f, %f, %f\n", div_n, S1, S2, S3);
    fprintf(gp, "%d, %f, %f, %f\n", div_n, AE1, AE2, AE3);
    fprintf(hp, "%d, %f, %f, %f\n", div_n, RE1, RE2, RE3);

    div_n += div_n_interval;
  }
}

int main(void)
{
  calc_result();
  return 0;
}