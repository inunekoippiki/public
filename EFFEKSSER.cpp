#include "../Library/GRAPHIC.h"
#include "EFFEKSSER_CONNECT.h"
#include "EFFEKSSER.h"
using namespace EFFEKSSER_CONNECT;
EFFEKSSER::EFFEKSSER() {
	GRAPHIC* g = GRAPHIC::instance();
	Renderer = ::EffekseerRendererDX11::Renderer::Create(g->device(), g->immediateContext(), 4096);
	Manager = ::Effekseer::Manager::Create(1024);
	// 描画方法の指定、独自に拡張しない限り定形文です。
	Manager->SetSpriteRenderer(Renderer->CreateSpriteRenderer());
	Manager->SetRibbonRenderer(Renderer->CreateRibbonRenderer());
	Manager->SetRingRenderer(Renderer->CreateRingRenderer());
	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	Manager->SetTextureLoader(Renderer->CreateTextureLoader());
	// 座標系の指定(RHで右手系、LHで左手系)
	Manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);
	// エフェクトの読込
	Effect["test"] = Effekseer::Effect::Create(Manager, u"Assets/effect/Test2.efk");
	Effect["AttackBuf"] = Effekseer::Effect::Create(Manager, u"Assets/effect/AttackBuf.efk");
	Effect["SpeedBuf"] = Effekseer::Effect::Create(Manager, u"Assets/effect/SpeedBuf.efk");
	Effect["BossDeath"] = Effekseer::Effect::Create(Manager, u"Assets/effect/BossDeath.efk");
}

EFFEKSSER::~EFFEKSSER() {
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	for (auto& i : Effect) {
		ES_SAFE_RELEASE(i.second);
	}
	// エフェクト管理用インスタンスを破棄
	Manager->Destroy();
	// 描画用インスタンスを破棄
	Renderer->Destroy();
}

void EFFEKSSER::updateProj(const MATRIX& pjoj){
	// 投影行列の更新
	Renderer->SetProjectionMatrix(cvtMatrix(pjoj));
}

void EFFEKSSER::updateView(const MATRIX& view){
	// カメラ行列の更新
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
	// 全てのエフェクトの更新
	Manager->Update();
}

void EFFEKSSER::draw(){
	Renderer->BeginRendering();
	Manager->Draw();
	Renderer->EndRendering();
}
