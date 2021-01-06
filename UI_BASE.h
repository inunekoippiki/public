#pragma once
class SHADER;
class UI_MANAGER;
class UI_DRAWER;
//UI���N���X
class UI_BASE{
public:
	UI_BASE();
	virtual ~UI_BASE();
	virtual void update() = 0;
	virtual void draw(SHADER* shader) = 0;
	void Delete() { IsDelete = true; }
	//�\���D��x
	unsigned int priority()const { return Priority; }
	//�f���[�g�t���O
	bool isDelete() { return IsDelete; }
	//�\�����Ȃ���
	bool isInvisible() { return IsInvisible; }
	//�`��I�u�W�F�N�g��ݒ肷��
	void setDrawer(UI_DRAWER* drawer) { Drawer = drawer; }
	//true�ŕ\������Ȃ�
	void setInvisible(bool invisible) { IsInvisible = invisible; }
	//�����ŕς��Ă��z��ɓ��꒼���Ȃ��ƕ`�揇�ς��܂���
	void setPriority(unsigned int priority) { Priority = priority; }
	static void setUiManager(UI_MANAGER* uiManager) { UiManager = uiManager; }
protected:
	UI_DRAWER* Drawer = nullptr;
	unsigned int Priority = 0;//�\���D��x
	static UI_MANAGER* UiManager;
private:
	bool IsInvisible = false;
	bool IsDelete = false;
};

