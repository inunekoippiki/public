#pragma once
#include <list>
#include "../Library/MATRIX.h"
#include "UI_BASE.h"
class UI_BASE;
class SHADER;
//UIを表示するクラス。
//priorityを設定することで描画順を設定できる
class UI_MANAGER {
public:
	UI_MANAGER();
	~UI_MANAGER();
	//UIを追加する
	void add(UI_BASE* ui, unsigned int priority);
	void draw(SHADER* shader);
	//3D上に表示されるUIのための行列
	MATRIX projView() { return ProjView; }
	//3D上に表示されるUIのための行列を設定する
	void setProjView(const MATRIX& projView) { ProjView = projView; }
private:
	std::list < UI_BASE*> UiList;
	MATRIX ProjView;
};

