#pragma once
#include <string.h>
#include<mbstring.h>
//マルチバイト文字のライブラリ
namespace MB_LIB {
	//文字のバイト数を返す
	size_t charSize(const char* c) {
		return _mbclen((unsigned char*)c);
	}
	size_t length(const string s) {
		size_t len = 0;
		const char* bp = s.data();
		while (*bp != '\0'){
			len++;
			bp += charSize(bp);
		}
		return len;
	}
	//区切り文字まで読み飛ばす(trueで成功:offsetに文字インデックスが入る)
	bool read(const char* string, const char* breakChar, size_t& offset) {
		while (string[offset] != '\0') {
			if (strchr(breakChar, string[offset]) && string[offset] != '\0') {
				return true;
			}
			offset += charSize(&string[offset]);
		}
		return false;
	}
	//マルチバイトの一文字の比較
	bool isMbMatch(const char* s1, const char* s2) {
		if (charSize(s1) != charSize(s2)) {
			return false;
		}
		for (size_t i = 0;i < charSize(s1);i++) {
			if (*(s1 + i) != *(s2 + i)) {
				return false;
			}
		}
		return true;
	}

	//文字列の置き換え
	//s:元の文字列
	//target:検索対象文字列
	//r:置き換える文字列
	//return:出力文字列
	string replaceText(const string& s, const string& target, const string& r) {
		string ret;
		const char* bp = s.data();
		while (*bp != '\0') {
			const char* targetBp = target.data();
			bool mbMatch = true;
			for (int i = 0;true;) {
				if (*(targetBp + i) == '\0') {
					break;
				}if (!isMbMatch(bp + i, targetBp + i)) {
					mbMatch = false;
					break;
				}
				i += charSize(targetBp + i);
			}
			if (mbMatch) {
				ret += r;
				bp += target.length();
			}
			else {
				ret += s.substr(bp - s.data(), charSize(bp));
				bp += charSize(bp);
			}
		}
		return ret;
	}
}