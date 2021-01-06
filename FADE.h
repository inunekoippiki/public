#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/COLOR.h"
#include "../Library/TEXTURE.h"
class SHADER;
//�t�F�[�h�C���t�F�[�h�A�E�g�Ǘ��N���X
class FADE {
public:
	FADE();
	~FADE();
	//�t�F�[�h�C�����J�n����
	void fadeInTrigger();
	//�t�F�[�h�A�E�g���J�n����
	void fadeOutTrigger();
	//�t�F�[�h�p�̉摜��`�悷��
	void draw(SHADER* shader);
	//true�Ńt�F�[�h�C�����I�����Ă���
	int fadeInEndFlag();
	//true�Ńt�F�[�h�A�E�g���I�����Ă���
	int fadeOutEndFlag();
	//�t�F�[�h�̃X�s�[�h��ݒ肷��
	void setSpeed(float speed);
private:
	enum FADE_STATE {
		FADE_IN_TRIGGER, FADE_IN, FADE_IN_END,
		FADE_OUT_TRIGGER, FADE_OUT, FADE_OUT_END
	};
	FADE_STATE FadeState;
	TEXTURE Texture;
	VECTOR2 Pos;
	COLOR Color;
	//�t�F�[�h�X�s�[�h
	float Speed = 0.0f;
};