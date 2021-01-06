#pragma once
#include "../Library/VECTOR2.h"
#include "../Library/COLOR.h"
#include "../Library/TEXTURE.h"
class SHADER;
//フェードインフェードアウト管理クラス
class FADE {
public:
	FADE();
	~FADE();
	//フェードインを開始する
	void fadeInTrigger();
	//フェードアウトを開始する
	void fadeOutTrigger();
	//フェード用の画像を描画する
	void draw(SHADER* shader);
	//trueでフェードインが終了している
	int fadeInEndFlag();
	//trueでフェードアウトが終了している
	int fadeOutEndFlag();
	//フェードのスピードを設定する
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
	//フェードスピード
	float Speed = 0.0f;
};