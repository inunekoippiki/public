#pragma once
#include <string.h>
#include<mbstring.h>
//�}���`�o�C�g�����̃��C�u����
namespace MB_LIB {
	//�����̃o�C�g����Ԃ�
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
	//��؂蕶���܂œǂݔ�΂�(true�Ő���:offset�ɕ����C���f�b�N�X������)
	bool read(const char* string, const char* breakChar, size_t& offset) {
		while (string[offset] != '\0') {
			if (strchr(breakChar, string[offset]) && string[offset] != '\0') {
				return true;
			}
			offset += charSize(&string[offset]);
		}
		return false;
	}
	//�}���`�o�C�g�̈ꕶ���̔�r
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

	//������̒u������
	//s:���̕�����
	//target:�����Ώە�����
	//r:�u�������镶����
	//return:�o�͕�����
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