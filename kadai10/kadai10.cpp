#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsiron 0.001       // 収束条件
double x = 5.0;             // xの初期値設定

// ##############################################
/**
 * @brief fxの計算
 * @param [double] x
 */
double calc_fx(double x)
{
  // double fx = pow(x, 3.0) - 13.0;                     //問1
  double fx = tanh(x) + 0.1 * x + 0.2;             //問2

  return fx;
}

// ##############################################
/**
 * @brief fx'の計算
 * @param [double] x
 */
double calc_fx_dot(double x)
{
  // double fxdot = 3.0 * x * x;                         //問1
  double fxdot = 1 / cosh(x) * cosh(x) + 0.1;         //問2

  return fxdot;
}

// ##############################################
/**
 * @brief Newton-Rapson法
 */
void newton_rapson_method()
{
  FILE *fp;
  fp = fopen("kadai10_2.csv", "w");

  printf("初期値：%f \n", x);             //xの初期値の出力

  double delta_x;
  int iteration_count;
  iteration_count = 0;
  for(;;){                        //収束条件を満たすまでループ
    //fx,fx'の計算
    double fx = calc_fx(x);
    double fxdot = calc_fx_dot(x);

    delta_x = - fx / fxdot;         //Δxの計算

    if(abs(delta_x) < epsiron) break;     //収束条件

    x += delta_x;           //xの更新
    iteration_count = iteration_count + 1;        //反復回数のカウント
    fprintf(fp, "%d %f \n", iteration_count, x);
  }

  //xの収束会の出力
  printf("数値解：%f\n反復回数：%d \n", x, iteration_count);
}

int main()
{
  newton_rapson_method();

  return 0;
}

