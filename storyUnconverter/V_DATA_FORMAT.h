#pragma once
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<filesystem>
#include <unordered_map>
#include <string>
#include <cassert>
#include <regex>
#include<mbstring.h>
#include "MB_LIB.h"

using MB_LIB::replaceText;
using MB_LIB::isMbMatch;
using MB_LIB::read;
using MB_LIB::charSize;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::tuple;
using std::ofstream;
using std::get;
using std::make_tuple;
using std::filesystem::create_directory;
using std::to_string;

class STRING_TREE{
#if(0)
#define STRING_TREE_THIS_NULL_CHECK() if (this == nullptr) { return nullptr; }
#else
#define STRING_TREE_THIS_NULL_CHECK()
#endif
public:
	STRING_TREE() {};
	STRING_TREE(const string& s, STRING_TREE* parent) {
		size_t offset = 0;
		size_t offsetSt = 0;
		int nest = 0;
		Data = s;
		const char* bp = Data.data();
		while (s.length()>offset) {
			if (read(bp, "[{}]", offset)) {
				switch (bp[offset]) {
				case '[': {
					if (nest == 0) {
						offsetSt = offset + 1;
					}
					nest++;
					break;
				}
				case '{': {
					if (nest == 0) {
						offsetSt = offset + 1;
					}
					nest++;
					break;
				}
				case '}': {
					nest--;
					break;
				}
				case ']': {
					nest--;
					break;
				}
				}
				if (nest == 0) {
					Childs.push_back(new STRING_TREE(Data.substr(offsetSt, offset - offsetSt), this));
				}
			}
			offset += charSize(&(bp[offset]));
		}
	};
	~STRING_TREE() {};
	int maxNest()const {
		size_t offset = 0;
		int nest = 0;
		int maxNest = 0;
		const char* bp = Data.data();
		while (Data.length() > offset) {
			if (read(bp,"[{}]", offset)) {
				switch (bp[offset]) {
				case '[': 
					nest++;
					break;
				case '{': 
					nest++;
					break;
				case '}': 
					nest--;
					break;
				case ']':
					nest--;
					break;
				}
				if (maxNest < nest) { 
					maxNest = nest; 
				}
			}
			offset += charSize(&(bp[offset]));
		}
		return maxNest;
	}
	//Childs�ɕێ����Ă���f�[�^���z��̃f�[�^����Ԃ��܂�
	bool isArray()const {
		return isMbMatch(Data.data(), "{");
	}
	bool isData() const{
		size_t offset = 0;
		size_t offsetSt = 0;
		int nest = 0;
		const char* bp = Data.data();
		while (Data.length() > offset) {
			if (read( bp, "[{", offset)) {
				return false;
			}
			offset += charSize(&(bp[offset]));
		}
		return true;
	}
	//idx�ڂ�Tag����Ԃ�
	string getTag(int idx)const {
		size_t offset = 0;
		size_t offsetSt = 0;
		int nest = 0;
		int i = 0;
		const char* bp = Data.data();
		while (Data.length() > offset) {
			if (read(bp, "[{}]", offset)) {
				switch (bp[offset]) {
				case '[':
					if (nest == 0) {
						if (i == idx) {
							return Data.substr(offsetSt, offset - offsetSt);
						}
						i++;
					}
					nest++;
					break;
				case '{':
					if (nest == 0) {
						if (i == idx) {
							return Data.substr(offsetSt, offset - offsetSt);
						}
						i++;
					}
					nest++;
					break;
				case '}':
					offsetSt = offset+1;
					nest--;
					break;
				case ']':
					offsetSt = offset+1;
					nest--;
					break;
				}
			}
			offset += charSize(&(bp[offset]));
		}
		return string();
	}
	//�^�O������v����C���f�b�N�X��Ԃ��i-1�ŊY���Ȃ��j
	int findData(const string& tag) const{
		size_t offset = 0;
		size_t wordSt = 0;
		int nest = 0;
		int idx = 0;
		const char* bp = Data.data();
		while (Data.length() > offset) {
			if (read( bp, "{[]}", offset)) {
				if (bp[offset] == '{' || bp[offset] == '[') {
					if (nest == 0) {
						if (Data.substr(wordSt, offset - wordSt) == tag) {
							return idx;
						}
						idx++;
					}
					nest++;
				}
				else {
					wordSt = offset + 1;
					nest--;
				}
			}
			offset += charSize(&(bp[offset]));
		}
		return -1;
	}
	int toInt()const {
		return atoi(Data.c_str());
	}
	double toDouble()const {
		return atof(Data.c_str());
	}
	//�f�[�^�̏���񎦂��܂�
	void check() {
		cout << "�G���[���-----------------------------------------------------------------------------------" << endl;
		int errorCnt = 0;
		size_t offset = 0;
		int nest = 0;
		vector<char> nestC;
		nestC.reserve(256);
		int maxNest = 0;
		const char* bp = Data.data();
		while (Data.length() > offset) {
			if (read(bp, "[{}]", offset)) {
				switch (bp[offset]) {
				case '[':
					nestC.emplace_back(']');
					nest++;
					break;
				case '{':
					nestC.emplace_back('}');
					nest++;
					break;
				case '}':
					nest--;
					if (nestC[nest] != '}') {
						cout << offset << "������:���銇�ʂ̎�ނ��s���ł�" << endl;
						errorCnt++;
					}
					nestC.pop_back();
					break;
				case ']':
					nest--;
					if (nestC[nest] != ']') {
						cout << offset << "������:���銇�ʂ̎�ނ��s���ł�" << endl;
						errorCnt++;
					}
					nestC.pop_back();
					break;
				}
				if (maxNest < nest) {
					maxNest = nest;
				}
			}
			offset += charSize(&(bp[offset]));
		}
		if (nest != 0) {
			cout << nest << "���ʂ̐����s���ł�" << endl;
			errorCnt++;
		}
		if (errorCnt != 0) {
			cout << errorCnt << "�̃G���[�����o����܂���" << endl;
		}
		else {
			cout << "�G���[�͌��o����܂���ł���" << endl;
		}
		cout << "�f�[�^���-----------------------------------------------------------------------------------" << endl;
		cout << "�ő�l�X�g:" << maxNest << endl;
		size_t dataCnt_ = 0;dataCnt(dataCnt_);
		cout << "�f�[�^��:" << dataCnt_ << endl;
		size_t dataSize_ = 0;dataSize(dataSize_);
		cout << "�f�[�^��(byte):" << dataSize_ << endl;
	}
	//�f�[�^�̐���Ԃ��܂�
	void dataCnt(size_t& outSize) {
		outSize++;
		for (auto& i : Childs) {
			i->dataCnt(outSize);
		}
	}
	//�f�[�^�̗e�ʂ�Ԃ��܂��i�q�[�v���݁j
	void dataSize(size_t& outSize) {
		outSize += Data.length();
		outSize += sizeof(STRING_TREE);
		for (auto& i : Childs) {
			i->dataSize(outSize);
		}
	}
	void cmd_dispAllData(int& nest) const {
		cout << Data << endl;
		for (auto& i : Childs) {
			i->cmd_dispAllData(++nest);
			--nest;
		}
	}
	void cmd_disp(int& nest)const {
		auto nestSpase = [](int nest) { for (int i = 0;i < nest;i++)cout << " "; };
		int maxNest_ = maxNest();
		for (size_t i = 0;i < Childs.size();i++) {
			nestSpase(nest);
			cout << getTag(i);
			if (Childs[i]->maxNest() == 0) {
				cout << ":" << Childs[i]->Data << endl;
			}
			else {
				cout << endl;
			}
			Childs[i]->cmd_disp(++nest);
			nest--;
		}

	}
	string data()const { return Data; }
	vector<STRING_TREE*> childs()const { return Childs; }
	STRING_TREE* at(const char* s)const {
		STRING_TREE_THIS_NULL_CHECK();
		int idx = findData(s);
		if (idx != -1) {
			return Childs[idx];
		}
		else {
			return nullptr;
		}
	}
	STRING_TREE* at(size_t idx)const {
		STRING_TREE_THIS_NULL_CHECK();
		if (idx >= 0 && idx < Childs.size()) {
			return Childs[idx];
		}
		else {
			return nullptr;
		}
	}

	//�I�y�[���[�^�[
	const STRING_TREE* operator[](const char* s)const {
		STRING_TREE_THIS_NULL_CHECK();
		int idx = findData(s);
		if (idx!=-1) {
			 return Childs[idx];
		}
		else{
			return nullptr;
		}
	}
	const STRING_TREE* operator[](size_t idx)const {
		STRING_TREE_THIS_NULL_CHECK();
		if (idx>=0&&idx<Childs.size()) {
			return Childs[idx];
		}
		else {
			return nullptr;
		}
	}
	operator string() { return Data; }
	operator int() { return toInt(); }
	operator float() { return(float)toDouble(); }
	operator double() { return toDouble(); }
private:
	string Data;
	vector<STRING_TREE*> Childs;
#undef STRING_TREE_THIS_NULL_CHECK
};

void cvtStory(STRING_TREE* tree,const string fileName) {
	//�e�L�X�g�Ƃ��̐F
	struct STORY_TEXT {
		STORY_TEXT() {};
		STORY_TEXT(const string& text, const string& color) :
			Text(text), Color(color) {

		}
		string Text;
		string Color;
	};
	//1�y�[�W�̃e�L�X�g
	struct STORY_PAGE_TEXT {
		vector<STORY_TEXT> Page;
	};
	//�ꖇ�̉摜
	struct STORY_IMG {
		string Img;
		double Px = 0.0;
		double Py = 0.0;
		int FadeIn = 0;
		int FadeOut = 0;
		int StFadeOutPage = -1;
	};
	//�P�y�[�W�̉摜
	struct STORY_PAGE_IMG {
		vector<STORY_IMG> Img;
	};
	//��̃T�E���h
	struct STORY_SOUND {
		string Sound;
		bool loop = false;
	};
	//1�y�[�W�̃T�E���h
	struct STORY_PAGE_SOUND {
		vector<STORY_SOUND> Sounds;
	};
	//1�y�[�W
	struct STORY_PAGE {
		string CharaName;
		STORY_PAGE_TEXT Text;
		STORY_PAGE_IMG Img;
		STORY_PAGE_SOUND Sounds;
	};
	//�S�ẴX�g�[���[�̃f�[�^
	vector<STORY_PAGE> RootStory;
	//�X�g�[���ϊ��J�n--------------------------------------------------------------
	for (auto& i : tree->childs()[0]->childs()) {
		static int debugCnt = 0;
		cout << debugCnt++ << endl;
		STORY_PAGE StoryPage;
		//1�y�[�W�̃e�L�X�g�ݒ�
		STORY_PAGE_TEXT& storyPageText = StoryPage.Text;
		int StoryTextIdx = i->findData("text");
		if (StoryTextIdx != -1) {
			for (auto& StoryText : i->childs()[StoryTextIdx]->childs()) {
				//�e�L�X�g�Ƃ��̐F�̐ݒ�
				STORY_TEXT pageText;
				int textIdx = StoryText->findData("text");
				if (textIdx != -1) {
					pageText.Text = StoryText->childs()[textIdx]->data();
					pageText.Text = replaceText(pageText.Text, "\\n", "\n");
					pageText.Text = replaceText(pageText.Text, "\\s", " ");
				}
				textIdx = StoryText->findData("color");
				if (textIdx != -1) {
					pageText.Color = StoryText->childs()[textIdx]->data();
				}
				storyPageText.Page.push_back(pageText);
			}
			StoryPage.Text = storyPageText;
		}
		//�����Ă�L�����̖��O�ݒ�
		StoryTextIdx = i->findData("name");
		if (StoryTextIdx != -1) {
			StoryPage.CharaName = i->childs()[StoryTextIdx]->data();
		}
		//�e�N�X�`���̐ݒ�
		STORY_PAGE_IMG& StoryPageImg = StoryPage.Img;
		StoryTextIdx = i->findData("image");
		if (StoryTextIdx != -1) {
			for (auto& i2 : i->childs()[StoryTextIdx]->childs()) {
				STORY_IMG StoryImg;
				int idx = i2->findData("image");
				if (idx != -1) {
					StoryImg.Img = i2->childs()[idx]->data();
				}
				idx = i2->findData("px");
				if (idx != -1) {
					StoryImg.Px = i2->childs()[idx]->toDouble();
				}
				idx = i2->findData("py");
				if (idx != -1) {
					StoryImg.Py = i2->childs()[idx]->toDouble();
				}
				idx = i2->findData("fadeIn");
				if (idx != -1) {
					StoryImg.FadeIn = i2->childs()[idx]->toInt();
				}
				idx = i2->findData("fadeOut");
				if (idx != -1) {
					StoryImg.FadeOut = i2->childs()[idx]->toInt();
				}
				idx = i2->findData("stFadeOutPage");
				if (idx != -1) {
					StoryImg.StFadeOutPage = i2->childs()[idx]->toInt();
				}
				StoryPageImg.Img.push_back(StoryImg);
			}
		}
		StoryPage.Img = StoryPageImg;
		//�P�y�[�W�̃T�E���h�̐ݒ�
		STORY_PAGE_SOUND& StoryPageSound = StoryPage.Sounds;
		//�T�E���h�̐ݒ�
		int StoryPageSoundIdx = i->findData("sound");
		if (StoryPageSoundIdx != -1) {
			for (auto& i2 : i->childs()[StoryPageSoundIdx]->childs()) {
				STORY_SOUND StorySound;
				int idx = i2->findData("sound");
				if (idx != -1) {
					StorySound.Sound = i2->childs()[idx]->data();
				}
				idx = i2->findData("loop");
				if (idx != -1) {
					StorySound.loop = i2->childs()[idx]->toInt();
				}
				StoryPageSound.Sounds.push_back(StorySound);
			}
		}
		RootStory.push_back(StoryPage);
	}
	cout << "�ꎟ�ϊ�--------------------------------------------------------------------------------" << endl;
	for (size_t i = 0;i < RootStory.size();i++) {
		cout << i << "----------------------------------------------------------------" << endl;
		cout << "charaName:" << RootStory[i].CharaName << endl;
		for_each(RootStory[i].Text.Page.begin(), RootStory[i].Text.Page.end(), [](STORY_TEXT& i) {cout << i.Text;});
		cout << endl;
		cout << "useColor:" << endl;
		for_each(RootStory[i].Text.Page.begin(), RootStory[i].Text.Page.end(), [](STORY_TEXT& i) {cout << " " << i.Color << endl;});
		cout << "images:" << endl;
		for_each(RootStory[i].Img.Img.begin(), RootStory[i].Img.Img.end(), [](STORY_IMG& i) {
			cout << " " << i.Img << "," << i.Px << "," << i.Py << "," << i.FadeIn << "," << i.FadeOut << endl;});
		cout << "sounds:" << endl;
		for_each(RootStory[i].Sounds.Sounds.begin(), RootStory[i].Sounds.Sounds.end(), [](STORY_SOUND& i) {
			cout << " " << i.Sound << "," << i.loop << endl;});
	}
	class OUT_COLOR {
	public:
		OUT_COLOR(const STORY_PAGE_TEXT& pageText) {
			size_t offset = 0;
			for (auto& i : pageText.Page) {
				if (i.Color.empty()) {
					const char* bp = i.Text.data();
					while (*bp != '\0') {
						if (!isMbMatch(bp , "\n")) {
							offset++;
						}
						bp += charSize(bp);
					}
				}
				else{
					ColorList.push_back(i.Color);
					const char* bp = i.Text.data();
					while (*bp != '\0') {
						if (!isMbMatch(bp, "\n")) {
							TextColor.push_back(make_tuple(ColorList.size(), offset++));
						}
						bp += charSize(bp);
					}
				}
			}
		};
		void outColorData(const string& fileName) {
			if (ColorList.empty())return;
			ofstream file(fileName + "C.txt");
			file << ColorList.size() << endl;
			for (auto i : ColorList) {
				fileCvtColor(file, i);
			}
			file << TextColor.size() << endl;
			for (auto i : TextColor) {
				file << get<0>(i) << " " << get<1>(i) << endl;
			}
			file.close();
		}
	private:
		void fileCvtColor(ofstream& stream, const string& color) {
			unsigned int value = 0;
			sscanf(color.c_str(), "%x", &value);
			unsigned r = ((value& 0xFF0000)>>16);
			unsigned g = ((value & 0x00FF00)>>8);
			unsigned b = (value & 0x0000FF);

			stream << (r/255.0) << " "
				<< (g / 255.0) << " "
				<< (b / 255.0) << " " << "1.00"<<endl;
		}
		vector<string> ColorList;
		vector<tuple<int,int>> TextColor;
	};
	class OUT_TEXT {
	public:
		OUT_TEXT(const STORY_PAGE_TEXT& pageText) {
			for (auto& i : pageText.Page) {
				Text += i.Text;
			}
		}
		void outTextData(const string& fileName) {
			ofstream file(fileName + ".txt");
			file << Text << endl;
			file.close();
		}
	private:
		string Text;
	};
	class OUT_STORY {
	public:
		OUT_STORY(const vector<STORY_PAGE>& story) {
			for (size_t i = 0;i < story.size();i++) {
				TextDatas.push_back(make_tuple(OUT_TEXT(story[i].Text), OUT_COLOR(story[i].Text)));
				Texts.push_back(make_tuple(story[i].CharaName, i));
				for (auto& i2 : story[i].Img.Img) {
					Imgages.push_back(make_tuple(i2.Img, i2.Px, i2.Py, i, i2.FadeIn, i2.StFadeOutPage<0?-1: (i2.StFadeOutPage + i), i2.FadeOut));
				}
				for (auto& i2 : story[i].Sounds.Sounds) {
					Sounds.push_back(make_tuple(i2.Sound, i, i2.loop));
				}
			}
		}
		void outStoryData(const string& fileName) {
			ofstream file(fileName+".txt");
			file << Imgages.size() << endl;
			for (auto& i : Imgages) {
				file << get<0>(i) << " "
					<< get<1>(i) << " "
					<< get<2>(i) << " "
					<< get<3>(i) << " "
					<< get<4>(i) << " "
					<< get<5>(i) << " "
					<< get<6>(i) << endl;
			}
			file << Texts.size() << endl;
			for (auto& i : Texts) {
				file << get<0>(i) << " "
					<< get<1>(i) << endl;
			}
			file << Sounds.size() << endl;
			for (auto& i : Sounds) {
				file << get<0>(i) << " "
					<< get<1>(i) << " "
					<< get<2>(i) << endl;
			}
			file.close();
			for (size_t i = 0; i < TextDatas.size();i++) {
				create_directory(fileName);
				auto &t = TextDatas[i];
				get<0>(t).outTextData(fileName+"/" + to_string(i));
				get<1>(t).outColorData(fileName +"/" + to_string(i));
			}
		}
	private:
		vector<tuple<string, double, double, int, int, int, int>> Imgages;
		vector<tuple<string, int>> Texts;
		vector<tuple<string, int, int>> Sounds;
		vector<tuple<OUT_TEXT, OUT_COLOR>> TextDatas;
	};
	OUT_STORY v2StoryTest(RootStory);
	v2StoryTest.outStoryData(fileName);
}

class V_DATA_FORMAT{
public:
	V_DATA_FORMAT(const string& fileName, const string& outFileName) {
		OutFileName = outFileName;
		std::ifstream file(fileName);
		load(file);
	};
	~V_DATA_FORMAT() {};
	void load(const string& fileName) {

	};
	void load(std::ifstream& file) {
		string s;
		string a;
		int len = 0;
		while (true){
			file >> a;
			if (file.fail()) {
				break;
			}
			s += a;
			len++;
		}
		dataCreate(s,0);
	}
	void dataCreate(const string s,size_t offset) {
		STRING_TREE* stringTree = new STRING_TREE(s,nullptr);
		int nest = 0;
		stringTree->check();
		cvtStory(stringTree, OutFileName);
		return;
	}
private:
	string OutFileName;
};

