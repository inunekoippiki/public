#if(1)
#include <string>
#include<fstream>
#include<filesystem>
#include <iostream>
#include "MB_LIB.h"
using namespace std::filesystem;
using std::tuple;
using std::get;
using std::cin;
using std::cout;
using std::endl;

#endif 

#if(1)
std::string textUncvt(const std::string& storyTextName) {

	FILE* fp = fopen((storyTextName + ".txt").c_str(), "r");
	fseek(fp, 0L, SEEK_END);//ファイルポインタをファイルの最後まで進める
	int size = ftell(fp);//ファイルサイズを取得
	rewind(fp);//ファイルポインタを最初に戻す
	//バッファを確保して一気に読み込む
	char* buffer = new char[size + 1];
	fread(buffer, 1, size, fp);
	fclose(fp);
	buffer[size] = 0;
	//colorIdx begin,end
	std::vector<tuple<int,int, int>> colorData;
	FILE* cfp = fopen((storyTextName + "C" + ".txt").c_str(), "r");
	if (cfp != nullptr) {
		std::vector<tuple<float, float, float, float>> colorList;
		int colorListNum = 0;
		fscanf(cfp, "%d", &colorListNum);
		colorList.push_back({ 1.0f,1.0f,1.0f,1.0f });
		for (int i = 0;i < colorListNum;i++) {
			decltype(colorList)::value_type data;
			fscanf(cfp, "%f %f %f %f", &get<0>(data), &get<1>(data), &get<2>(data), &get<3>(data));
			colorList.push_back(data);
		}
		int colorNum = 0;
		fscanf(cfp, "%d", &colorNum);
		int beforeColorIdx = -1;
		int beforeIdx = -1;
		int EndIdx = -1;
		int beginIdx = -1;

		for (int i = 0;i < colorNum;i++) {
			int cidx = 0;
			int sidx = 0;
			fscanf(cfp, "%d %d", &cidx, &sidx);
			if (beginIdx == -1) {
				beginIdx = sidx;
			}
			if (beforeColorIdx == -1) {
				beforeColorIdx = cidx;
			}
			if (beforeIdx == -1) {
				beforeIdx = sidx-1;
			}

			if (cidx != beforeColorIdx || beforeIdx + 1 != sidx|| colorNum==i+1) {
				colorData.push_back({ beforeColorIdx,beginIdx,beforeIdx-1 });
				beginIdx = sidx;
				beforeColorIdx = cidx;
			}
			else {
				beforeIdx = sidx;
			}
		}
		fclose(cfp);
	}


	std::string outData;
	outData += "\t\ttext[\n"; {
		std::string text = MB_LIB::replaceText(buffer, "\n", "\\n");
		text = MB_LIB::replaceText(text, "\s", "\\s");
		outData += "\t\t\t{text{" + text + "}}\n";

	}outData += "\t\t]\n"; 
	return outData;
}

void uncvt (const std::string& inFineName,const std::string outFileName){
	//テクスチャ名,x座標,Y座標,表示ページ数,フィードインフレーム,非表示ページ（-1は消えない）,フィードアウトフレーム 
	std::vector<std::tuple<char[256], float, float, int, int, int, int>> texturesData;
	std::vector<std::tuple<char[256], char[256]>> textsData;
	std::vector<std::tuple<char[256], int, int>> soundsData;
	FILE* storyTextFile = fopen((inFineName+".txt").c_str(), "r");
	if (storyTextFile == nullptr) { cout << "ストーリーファイルが読み込まれませんでした"<<endl; }
	//テクスチャ読み込み
	int texturesNum = 0;
	fscanf(storyTextFile, "%d", &texturesNum);
	texturesData.reserve(texturesNum);
	for (int i = 0;i < texturesNum;i++) {
		decltype(texturesData)::value_type data;
		fscanf(storyTextFile, "%s %f %f %d %d %d %d", get<0>(data), &get<1>(data), &get<2>(data), &get<3>(data), &get<4>(data), &get<5>(data), &get<6>(data));
		texturesData.push_back(data);
	}
	//テキスト読み込み
	int textsNum = 0;
	fscanf(storyTextFile, "%d", &textsNum);
	textsData.reserve(textsNum);
	for (int i = 0;i < textsNum;i++) {
		decltype(textsData)::value_type data;
		fscanf(storyTextFile, "%s %s", get<0>(data), get<1>(data));
		textsData.push_back(data);
	}
	//サウンド読み込み
	int soundsNum = 0;
	fscanf(storyTextFile, "%d", &soundsNum);
	soundsData.reserve(soundsNum);
	for (int i = 0;i < soundsNum;i++) {
		decltype(soundsData)::value_type data;
		fscanf(storyTextFile, "%s %d %d", get<0>(data), &get<1>(data), &get<2>(data));
		soundsData.push_back(data);
	}

	std::string outData;
	outData += "page[\n";
	{
		for (int i = 0;i < textsData.size();i++) {
			outData += "\t{\n";
			{
				outData += textUncvt(inFineName +"/"+ get<1>(textsData[i]));
				outData += "\t\tname{" + std::string(get<0>(textsData[i])) + "}\n";
				{
					std::string texturesText;
					bool empty = true;
					texturesText += "\t\timage[\n";
					{
						for (auto i2 : texturesData) {
							if (get<3>(i2) == i) {
								texturesText += "\t\t\t{image{" + std::string(get<0>(i2)) + "}px{" + std::to_string(get<1>(i2)) + "}py{" + std::to_string(get<2>(i2)) + " }fadeIn{" + std::to_string(get<4>(i2)) + "}fadeOut{" + std::to_string(get<6>(i2)) + "}stFadeOutPage{-1}}\n";
								empty = false;
							}
						}
					}texturesText += "\t\t]\n";
					if (!empty) {
						outData += texturesText;
					}
				}
				{
					std::string soundsText;
					bool empty = true;
					soundsText += "\t\tsound[\n";
					{
						for (auto i2 : soundsData) {
							if (get<1>(i2) == i) {
								soundsText += "\t\t\t{sound{" + std::string(get<0>(i2)) + "}loop{ " + std::to_string(get<2>(i2)) + " }}\n";
								empty = false;
							}
						}
					}soundsText += "\t\t]\n";
					if (!empty) {
						outData += soundsText;
					}
				}

			}outData += "\t}\n";

		}
	}outData += "]\n";
	std::ofstream ofs("textOutput/" + outFileName + ".txt");
	ofs << outData << endl;
	ofs.close();

}

void main() {
	std::string fileName;
	std::cin >> fileName;
	uncvt("textInput/"+fileName,"fileName");
}
#endif

