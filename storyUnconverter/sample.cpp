#include <stdio.h>
#include <cmath>
#include "fpErrorStop.h"

void main(){
	//ここにプログラムをタイプする
	FPErrorStop(); //これで止まるといいなぁ、、、

#if 0
	//EM_INEXACT で引っかかる
	float f1 = 10.0f;
	printf("端数が出る\n");
	float f2 = f1 / 3.0f;
#endif

#if 0
	//EM_ZERODIVIDE で引っかかる
	float f1 = 10.0f;
	float f2 = 1.0f;
	float f3 = 0.0f;
	float f4 = 2.0f;
	printf("1で割る\n");
	printf("%f\n", f1 / f2);
	printf("0で割る\n");
	printf("%f\n", f1 / f3);
	printf("2で割る\n");
	printf("%f\n", f1 / f4);
#endif

#if 0
	//EM_INVALID でひっかかる
	float f1 = 2.0f;
	printf("範囲外のパラメータを渡す\n");
	float f2 = acosf(f1);
	printf("%f\n", f2);
#endif

#if 0
	//EM_OVERFLOW でひっかかる
	float f1 = FLT_MAX;
	printf("オーバーフローさせる\n");
	float f2 = f1 * 2.0f;
#endif

	//
	float f1 = 19999999.0f;
	float f2 = f1 + 1.0f;
	printf("%f %f\n", f1, f2);
}

