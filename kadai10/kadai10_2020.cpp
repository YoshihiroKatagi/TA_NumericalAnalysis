#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsiron 0.001            // 収束条件
double  x = 5.0;                 //xの初期値設定


// #################################################################
/**
 * @brief fxの計算
 * @param [double] x
 */
double calc_fx(double x)
{

  double fx = pow(5e0,1e0/3e0) - x;                 //問1()
  // double fx = pow(x,3e0) - 3 * pow(x,2e0) + x + 3; //問2()

  return fx;

}

// #################################################################
/**
 * @brief fx'の計算
 * @param [double] x
 */
double calc_fx_dot(double x)
{

  double fxdot = -1.0;                      //問1()
  // double fxdot = 3 * pow(x,2e0) - 6e0 * x; //問2()

  return fxdot;

}

// #################################################################
/**
 * @brief Newton-Raphson法
 */
void newton_raphson_method()
{
  FILE *fp1;
	fp1=fopen("kadai10a.dat","w");


  printf("first_x = %f \n",x);            //xの初期値の出力

  double delta_x;
  int iteration_count;
  iteration_count = 0;
  for(;;){                                //収束条件を満たすまでループ

  //fx,fx'の計算
  double fx = calc_fx(x);
  double fxdot = calc_fx_dot(x);

  delta_x = - fx / fxdot;                 //Δxの計算

  if(abs(delta_x) < epsiron) break;       //収束条件

  x += delta_x;                           //xの更新
  iteration_count = iteration_count + 1;                      //反復回数のカウント
  fprintf(fp1,"%d %f \n",iteration_count,x);

  }

  //xの収束解の出力
  printf("x = %f, iteration_count = %d \n", x, iteration_count);

  //検算用出力
  // printf("verification = %f \n", pow(x,3.0) - 3 * pow(x,2.0) + x + 3);
  // printf("verification = %f \n", pow(5.0,3.0 / 2.0) - x);

}

int main()
{

  newton_raphson_method();

  return 0;
}