#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define number_of_equation 2     // 方程式の数
#define variables 2              // 変数の数、ここではxとy
int iteration_count = 0;         // 収束までの反復回数

//パラメータ設定
#define epsiron 0.000001         // 収束条件
double  x = 1.0;                 // xの初期値設定
double  y = 0.0;                 // yの初期値設定

double Jacobian_matrix[number_of_equation][variables];
double f_vector[number_of_equation];
double delta_f_vector[number_of_equation];

// #################################################################
/**
 * @brief f()ベクトルの計算
 */
void calc_f_vector(double f_vector[number_of_equation], double x, double y)
{

  f_vector[0] = cos(x + y) + 2.0 * (x - y) - 1.5;
  f_vector[1] = cos(x + y) - 2.0 * (x - y) + 2.5;

}

// #################################################################
/**
 * @brief ヤコビアン計算
 */
void calc_Jacobian(double Jacobian_matrix[number_of_equation][variables], double x, double y)
{

  Jacobian_matrix[0][0] = -1.0 * sin(x + y) + 2.0;
  Jacobian_matrix[0][1] = -1.0 * sin(x + y) - 2.0;
  Jacobian_matrix[1][0] = -1.0 * sin(x + y) - 2.0;
  Jacobian_matrix[1][1] = -1.0 * sin(x + y) + 2.0;

}
// #################################################################
/**
 * @brief ガウスの消去法による連立方程式の求解
 */
void solve(double Jacobian_matrix[number_of_equation][variables], double f_vector[number_of_equation], double delta_f_vector[number_of_equation])
{

  int r, c;       //マトリックスの行と列のカウンター
  int rr, cc;     //マトリックスの行と列のカウンター
  double pivot;   //マトリックスの対角成分
  double p;       //計算に使用するマトリックスの成分

  for(r = 0; r < number_of_equation; r++){    //前進消去

    pivot = Jacobian_matrix[r][r];            //対角成分をpivotに代入

    for(c = r; c < variables; c++){           //r行目の処理

      Jacobian_matrix[r][c] = Jacobian_matrix[r][c] / pivot;
    }

    f_vector[r] = f_vector[r] / pivot;

    for(rr = r + 1; rr < number_of_equation; rr ++){   //r+1行目以下の処理

      p = Jacobian_matrix[rr][r];

      for(cc = r ; cc < variables; cc++){

        Jacobian_matrix[rr][cc] = Jacobian_matrix[rr][cc] - p * Jacobian_matrix[r][cc]; 
      }

      f_vector[rr] = f_vector[rr] - p * f_vector[r];
    }

  }

  for(r = number_of_equation - 1; r >= 0; r--){   //後退代入

    delta_f_vector[r] = f_vector[r];

    for(c = r + 1; c < number_of_equation; c++){

      delta_f_vector[r] = delta_f_vector[r] - Jacobian_matrix[r][c] * delta_f_vector[c];
    }
  }
}

// #################################################################
/**
 * @brief Newton-Raphson法
 */
void newton_raphson_method()
{
  int i;
  
  //連立方程式の解となる配列の初期化
  delta_f_vector[0] = 0.0;
  delta_f_vector[1] = 0.0;

  for(;;){                                //収束条件を満たすまでループ

  printf("iteration = %d, x = %f, y = %f\n",iteration_count, x, y);

  //f()とヤコビアンの計算
  calc_f_vector(f_vector,x, y);
  calc_Jacobian(Jacobian_matrix, x, y);

  //ガウスの消去法によるΔxの求解
  solve(Jacobian_matrix, f_vector, delta_f_vector);

  //Δxベクトルの符号の反転
  for(i = 0; i < number_of_equation; i++){

    delta_f_vector[i] = - delta_f_vector[i];
  }

  //Δxベクトルによるx,yの更新
  x += delta_f_vector[0];
  y += delta_f_vector[1];
  iteration_count ++;

  //verification用出力
  // printf("verification_f1 = %f ,verification_f2 = %f \n", 4 * x - 4.2 * pow(x,3.0) + pow(x, 5.0) + y, x + 2.0 * y);
  // printf("verification_f = %f \n \n", 2 * pow(x, 2.0) - 1.05 * pow(x,4.0) + pow(x, 6.0)/ 6.0 + x * y + pow(y, 2.0));

  //収束条件
  if(abs(sqrt(delta_f_vector[0] * delta_f_vector[0] + delta_f_vector[1] * delta_f_vector[1])) < epsiron ) break;

  }

}

int main()
{

  printf("Caliculation procedure \n\n");
  printf("epsiron=%f, x=%f, y=%f \n\n", epsiron, x, y);

  newton_raphson_method();      //Newton-Raphson法による計算実行

  printf("\n");
  printf("Caliculation is succeeded! \n");

  return 0;
}