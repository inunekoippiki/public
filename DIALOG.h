#pragma once
#include <functional>
#include "../Library/common.h"
#include "../Library/SOUND.h"
#include "../Library/VECTOR2.h"
#include "../Library/TEXTURE.h"
class SHADER;
//Y/N�_�C�����O�̊�{�@�\���������N���X
class DIALOG{
public:
	DIALOG();
	~DIALOG();
	void create(
		CONTAINER* c,
		TEXTURE* selectIconTexture,
		const VECTOR2& selectIconYes,
		const VECTOR2& selectIconNo,
		TEXTURE* windowTexture,
		const VECTOR2& windowTexturePos);
	//yes�������ꂽ�ۂ̃R�[���o�b�N�֐���ݒ肷��
	template<class T>
	void setYesFunc(const T& yesFunc) { YesFunc = yesFunc; };
	//no�������ꂽ�ۂ̃R�[���o�b�N�֐���ݒ肷��
	template<class T>
	void setNoFunc(const T& noFunc) { NoFunc = noFunc; };
	//cancel�������ꂽ�ۂ̃R�[���o�b�N�֐���ݒ肷��
	template<class T>
	void setCancelFunc(const T& cancelFunc) { CancelFunc = cancelFunc; };
	void init();
	void update();
	void draw(SHADER* shader);
	void windowDraw(SHADER* shader);
	void selectIconDraw(SHADER* shader);
private:
	enum class STATE {
		YES, NO
	};
	STATE State= STATE::YES;

	TEXTURE* SelectIconTexture = nullptr;
	VECTOR2 SelectIconYes;
	VECTOR2 SelectIconNo;

	TEXTURE* WindowTexture = nullptr;
	VECTOR2 WindowTexturePos;

	SOUND* SoundChoice = nullptr;
	SOUND* SoundCancel = nullptr;
	SOUND* SoundEnter = nullptr;

	std::function<void()> YesFunc = nullptr;
	std::function<void()> NoFunc = nullptr;
	std::function<void()> CancelFunc = nullptr;
};
