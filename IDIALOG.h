#pragma once
class SHADER;
//�_�C�����O�̃C���^�[�t�F�[�X
class IDIALOG{
public:
	virtual ~IDIALOG() {};
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw(SHADER* shader) = 0;
private:

};