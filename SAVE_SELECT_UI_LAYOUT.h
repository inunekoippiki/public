#pragma once
#include <array>
class UI_2D_LEFT;
class CONTAINER;
class UI_MANAGER;
class SAVE_SELECT_UI_SAVE_DATA;
struct SAVE_DATA;
//�o�g����ʂ�UI�̔z�u�ƍX�V������N���X
class SAVE_SELECT_UI_LAYOUT {
public:
	SAVE_SELECT_UI_LAYOUT();
	~SAVE_SELECT_UI_LAYOUT();
	void create(CONTAINER* c, STATIC_FONT* font, UI_MANAGER* uiManager, const std::array< SAVE_DATA, 3> saveData);
	//�Z�[�u�f�[�^���f���[�g������̍X�V
	void SaveDataDeleteUpdate(const std::array< SAVE_DATA, 3> saveData);
	void draw(SHADER* shader);
	//�I�𒆂̃Z�[�u�f�[�^�C���f�b�N�X
	void choiceIdx(int idx);
private:
	UI_2D_LEFT* SaveSelectBack = nullptr;
	std::array<UI_2D_LEFT*, 3> NewGameIcon = {};
	UI_2D_LEFT* ChoiceIcon = nullptr;
	std::array<VECTOR2, 3> ChoiceIconPos = {};
	SAVE_SELECT_UI_SAVE_DATA* SaveSelectSaveData[3] = {};
};

