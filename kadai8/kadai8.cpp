

#include <stdio.h>
#include <math.h>

#define delta_t 0.1 // 時間刻み
#define total_step 300 // 計算ステップ数

void Heun (double x0, double v0, int i)
{

}

int main()
{
  FILE *fout;
  fout = fopen("data.csv", "w");

  if (fout==NULL) {
    printf("Error: cannot open file\n");
  }

  fprintf(fout, "t,x,v\n");

  //初期値入力
  double x0 = 1.0;
  double v0 = 0.0;

  double x[total_step];
  double v[total_step];

  for (int step=0; step<total_step; step++) {
    if (step == 0) {
      x[step] = x0;
      v[step] = v0;
    }
    else {
      double vb = v[step - 1];
      double xb = x[step - 1];

      double k1_x = (vb)*delta_t;
      double k2_x = (vb)*delta_t;

      x[step] = xb + (k1_x + k2_x) / 2.0;

      double k1_v = (2 * (1 - xb * xb) * vb - 2 * xb) * delta_t;
      double k2_v = (2 * (1 - xb * xb) * (vb + k1_v) - 2 * xb) * delta_t;

      v[step] = vb + (k1_v + k2_v) / 2.0;
    }
    fprintf(fout, "%f, %f, %f\n", step*delta_t, x[step], v[step]);
  }
  fclose(fout);


}