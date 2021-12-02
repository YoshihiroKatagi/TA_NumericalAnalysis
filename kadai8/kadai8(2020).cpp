// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


#define _CRT_SECURE_NO_WARNINGS


#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define delta_t 0.1 // 時間刻み
#define total_step 300 // 計算ステップ数


int main()
{


	int step;
	FILE* fout, * fout2;
	fout = fopen("data.csv", "w");

	if (fout == NULL) { // エラーチェック
		printf("Error: cannot open file\n");
		return -1;
	}

	//初期値入力
	double x0 = 1.0;
	double v0 = 0.0;


	double x[total_step];
	double v[total_step];
	

	srand(1);

	for (step = 0; step < total_step; step++) {

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

			double k1_v = ((1 -  xb * xb) * vb - xb) * delta_t;
			double k2_v = ( (1 - xb * xb) * (vb + k1_v) - xb) * delta_t;

			v[step] = vb + (k1_v + k2_v) / 2.0;


		}

		// printf("%7.2f %10.3f \n", step * delta_t, x[step]);
		fprintf(fout, "%lf, %lf, %lf\n", step * delta_t, x[step], v[step]);



	}

	fclose(fout);


}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
