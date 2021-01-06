#include <stdio.h>
#include <cmath>
#include "fpErrorStop.h"

void main(){
	//�����Ƀv���O�������^�C�v����
	FPErrorStop(); //����Ŏ~�܂�Ƃ����Ȃ��A�A�A

#if 0
	//EM_INEXACT �ň���������
	float f1 = 10.0f;
	printf("�[�����o��\n");
	float f2 = f1 / 3.0f;
#endif

#if 0
	//EM_ZERODIVIDE �ň���������
	float f1 = 10.0f;
	float f2 = 1.0f;
	float f3 = 0.0f;
	float f4 = 2.0f;
	printf("1�Ŋ���\n");
	printf("%f\n", f1 / f2);
	printf("0�Ŋ���\n");
	printf("%f\n", f1 / f3);
	printf("2�Ŋ���\n");
	printf("%f\n", f1 / f4);
#endif

#if 0
	//EM_INVALID �łЂ�������
	float f1 = 2.0f;
	printf("�͈͊O�̃p�����[�^��n��\n");
	float f2 = acosf(f1);
	printf("%f\n", f2);
#endif

#if 0
	//EM_OVERFLOW �łЂ�������
	float f1 = FLT_MAX;
	printf("�I�[�o�[�t���[������\n");
	float f2 = f1 * 2.0f;
#endif

	//
	float f1 = 19999999.0f;
	float f2 = f1 + 1.0f;
	printf("%f %f\n", f1, f2);
}

