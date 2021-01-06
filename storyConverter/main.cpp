#include<iostream>
#include<fstream>
#include<filesystem>
using namespace std::filesystem;
using namespace std;

#if(1)
#include "V_DATA_FORMAT.h"
void main() {
	//originファイルに入っているストーリーデータを変換する
	for (const directory_entry& e : directory_iterator("origin")) {
		V_DATA_FORMAT data("origin/" + e.path().filename().string(), e.path().filename().string().substr(0, e.path().filename().string().find_last_of(".")));
	}
}
#endif

