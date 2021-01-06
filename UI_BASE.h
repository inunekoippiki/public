#pragma once
class SHADER;
class UI_MANAGER;
class UI_DRAWER;
//UI基底クラス
class UI_BASE{
public:
	UI_BASE();
	virtual ~UI_BASE();
	virtual void update() = 0;
	virtual void draw(SHADER* shader) = 0;
	void Delete() { IsDelete = true; }
	//表示優先度
	unsigned int priority()const { return Priority; }
	//デリートフラグ
	bool isDelete() { return IsDelete; }
	//表示しないか
	bool isInvisible() { return IsInvisible; }
	//描画オブジェクトを設定する
	void setDrawer(UI_DRAWER* drawer) { Drawer = drawer; }
	//trueで表示されない
	void setInvisible(bool invisible) { IsInvisible = invisible; }
	//ここで変えても配列に入れ直さないと描画順変わりません
	void setPriority(unsigned int priority) { Priority = priority; }
	static void setUiManager(UI_MANAGER* uiManager) { UiManager = uiManager; }
protected:
	UI_DRAWER* Drawer = nullptr;
	unsigned int Priority = 0;//表示優先度
	static UI_MANAGER* UiManager;
private:
	bool IsInvisible = false;
	bool IsDelete = false;
};

