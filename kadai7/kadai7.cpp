#include <stdio.h>
#include <math.h>

double answer(double t) {
  // 解析解
  // return (1.0/2.0 * (exp(sqrt(-3) * t) + exp(-1 * sqrt(-3) * t)));
  return cos(sqrt(3.0)*t);
}

double euler(double x1, double dx, double dt) {
  // オイラー法
  return (x1 + dx*dt);
}

double heun(double x1, double dx1, double dx2, double dt) {
  // ホイン法
  return (x1 + 1.0/2.0 * (dx1 + dx2) * dt);
}

int main(void) {
  FILE *fp1, *fp2;
  fp1 = fopen("Euler_result.csv", "w");
  fp2 = fopen("Heun_result.csv", "w");
  fprintf(fp1, "t,x,dx,x_true\n");
  fprintf(fp2, "t,x,dx,x_true\n");

  const int N = 100;
  const double dt = 0.1;
  const double t_0 = 0.0;
  const double x_0 = 1.0;
  const double dx_0 = 0.0;
  const double ddx_0 = -3.0;

  double x_true;
  double t = t_0;
  double x_e = x_0;
  double x_h = x_0;
  double dx_e = dx_0;
  double dx_h = dx_0;
  double ddx_e = ddx_0;
  double ddx_h = ddx_0;
  double x_next_e, dx_next_e;
  double x_next_h, dx_next_h;

  x_true = answer(t);
  fprintf(fp1, "%f, %f, %f, %f\n", t, x_e, dx_e, x_true);
  fprintf(fp2, "%f, %f, %f, %f\n", t, x_h, dx_h, x_true);

  for (int i  = 0; i < N; i++) {
    t = t + dt;
    ddx_e = -3.0 * x_e;
    ddx_h = -3.0 * x_h;

    x_next_e = euler(x_e, dx_e, dt);
    dx_next_e = euler(dx_e, ddx_e, dt);

    dx_next_h = euler(dx_h, ddx_h, dt);
    x_next_h = heun(x_h, dx_h, dx_next_h, dt);

    x_true = answer(t);

    fprintf(fp1, "%f, %f, %f, %f\n", t, x_next_e, dx_next_e, x_true);
    fprintf(fp2, "%f, %f, %f, %f\n", t, x_next_h, dx_next_h, x_true);

    x_e = x_next_e;
    dx_e = dx_next_e;
    x_h = x_next_h;
    dx_h = dx_next_h;
  }
  fclose(fp1);
  fclose(fp2);

  return 0;
}