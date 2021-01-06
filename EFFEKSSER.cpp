#include "../Library/GRAPHIC.h"
#include "EFFEKSSER_CONNECT.h"
#include "EFFEKSSER.h"
using namespace EFFEKSSER_CONNECT;
EFFEKSSER::EFFEKSSER() {
	GRAPHIC* g = GRAPHIC::instance();
	Renderer = ::EffekseerRendererDX11::Renderer::Create(g->device(), g->immediateContext(), 4096);
	Manager = ::Effekseer::Manager::Create(1024);
	// �`����@�̎w��A�Ǝ��Ɋg�����Ȃ������`���ł��B
	Manager->SetSpriteRenderer(Renderer->CreateSpriteRenderer());
	Manager->SetRibbonRenderer(Renderer->CreateRibbonRenderer());
	Manager->SetRingRenderer(Renderer->CreateRingRenderer());
	// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
	Manager->SetTextureLoader(Renderer->CreateTextureLoader());
	// ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
	Manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);
	// �G�t�F�N�g�̓Ǎ�
	Effect["test"] = Effekseer::Effect::Create(Manager, u"Assets/effect/Test2.efk");
	Effect["AttackBuf"] = Effekseer::Effect::Create(Manager, u"Assets/effect/AttackBuf.efk");
	Effect["SpeedBuf"] = Effekseer::Effect::Create(Manager, u"Assets/effect/SpeedBuf.efk");
	Effect["BossDeath"] = Effekseer::Effect::Create(Manager, u"Assets/effect/BossDeath.efk");
}

EFFEKSSER::~EFFEKSSER() {
	// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
	for (auto& i : Effect) {
		ES_SAFE_RELEASE(i.second);
	}
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	Manager->Destroy();
	// �`��p�C���X�^���X��j��
	Renderer->Destroy();
}

void EFFEKSSER::updateProj(const MATRIX& pjoj){
	// ���e�s��̍X�V
	Renderer->SetProjectionMatrix(cvtMatrix(pjoj));
}

void EFFEKSSER::updateView(const MATRIX& view){
	// �J�����s��̍X�V
	Renderer->SetCameraMatrix(cvtMatrix(view));
}

Effekseer::Handle EFFEKSSER::play(const char* name, const VECTOR3& pos){
	return Manager->Play(Effect[name], cvtVector3D(pos));
}

Effekseer::Handle EFFEKSSER::play(const char* name, const VECTOR3& pos,float scale){
	Effekseer::Handle handle = Manager->Play(Effect[name], Effekseer::Vector3D());
	Effekseer::Matrix43 m;
	m.Translation(pos.x, pos.y, pos.z);
	m.Scaling(scale, scale, scale);
	Manager->SetBaseMatrix(handle, m);
	return handle;
}

Effekseer::Handle EFFEKSSER::play(const char* name, const VECTOR3& pos, const VECTOR3 scale){
	Effekseer::Handle handle = Manager->Play(Effect[name],Effekseer::Vector3D());
	Effekseer::Matrix43 m;
	m.Translation(pos.x, pos.y, pos.z);
	m.Scaling(scale.x, scale.y, scale.z);
	Manager->SetBaseMatrix(handle, m);
	return handle;
}

Effekseer::Handle EFFEKSSER::play(const char* name, const VECTOR3& pos, const VECTOR3& rad,const VECTOR3 scale){
	Effekseer::Handle handle = Manager->Play(Effect[name], Effekseer::Vector3D());
	Effekseer::Matrix43 mR;
	Effekseer::Matrix43 mL;
	mL.Scaling(scale.x, scale.y, scale.z);
	mR.RotationY(rad.y);
	Effekseer::Matrix43::Multiple(mL, mL, mR);
	mR.Translation(pos.x, pos.y, pos.z);
	Effekseer::Matrix43::Multiple(mL, mL, mR);
	Manager->SetBaseMatrix(handle, mL);
	return handle;
}

void EFFEKSSER::setPos(Effekseer::Handle handle, const VECTOR3& pos){
	Manager->SetLocation(handle, pos.x, pos.y, pos.z);
}

void EFFEKSSER::setRotation(Effekseer::Handle handle, const VECTOR3& rad){
	Manager->SetRotation(handle, rad.x, rad.y, rad.z);
}

void EFFEKSSER::setScale(Effekseer::Handle handle, const VECTOR3& scale){
	Manager->SetScale(handle, scale.x, scale.y, scale.z);
}

void EFFEKSSER::setPaused(Effekseer::Handle handle, bool paused){
	Manager->SetPaused(handle, paused);
}

void EFFEKSSER::stopRoot(Effekseer::Handle handle){
	Manager->StopRoot(handle);
}

void EFFEKSSER::update(){
	// �S�ẴG�t�F�N�g�̍X�V
	Manager->Update();
}

void EFFEKSSER::draw(){
	Renderer->BeginRendering();
	Manager->Draw();
	Renderer->EndRendering();
}
