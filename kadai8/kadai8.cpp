#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;


#define delta_t 0.1 // 時間刻み
#define total_step 300 // 計算ステップ数

void Heun (double x0, double v0, int i)
{
  string filename = "data" + to_string(i+1) + ".csv";
  FILE *fout;
  fout = fopen(filename.c_str(), "w");

  if (fout==NULL) {
    printf("Error: cannot open file\n");
  }

  fprintf(fout, "t,x,v\n");

  double x[total_step];
  double v[total_step];

  for (int step=0; step<=total_step; step++) {
    if (step == 0) {
      x[step] = x0;
      v[step] = v0;
    }
    else {
      double vb = v[step - 1];
      double xb = x[step - 1];

      double k1_x = (vb)*delta_t;

      x[step] = xb + k1_x;

      double k1_v = (2 * (1 - xb * xb) * vb - 2 * xb) * delta_t;
      double k2_v = (2 * (1 - xb * xb) * (vb + k1_v) - 2 * xb) * delta_t;

      v[step] = vb + (k1_v + k2_v) / 2.0;
    }
    fprintf(fout, "%f, %f, %f\n", step*delta_t, x[step], v[step]);
  }
  fclose(fout);
}

int main()
{
  double ini_v[4][2] = {{1.0, 0.0}, {-1.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};

  for (int i=0; i<4; i++){
    double x0_i = ini_v[i][0];
    double v0_i = ini_v[i][1];
    Heun(x0_i, v0_i, i);
  }
}