#pragma once
#pragma warning (disable:4996)
#include <type_traits>
#include <array>
#include <functional>
#include <stdio.h>
#include <string.h>
#include "../Library/VECTOR2.h"
#include "../Library/VECTOR3.h"
#include "../Library/COLOR.h"
class CONTAINER;
#pragma warning(push)
#pragma warning(disable:4996)
namespace DATA_LIB {
	//DATA‚©‚çVECTOR2‚ğæ‚èo‚·ì‹Æ‚ğ©“®‚Å‚µ‚Ä‚­‚ê‚é(ÅŒã”ö‚É.x,.y‚ğ‚Â‚¯‚Ä‚é‚¾‚¯)
	VECTOR2 vector2(CONTAINER* c, const char* name);
	VECTOR3 vector3(CONTAINER* c, const char* name);
	COLOR color(CONTAINER* c, const char* name);
	//DATA‚©‚ç”z—ñ‚Ìæ‚èo‚µ‚ğ©“®‚Å‚â‚Á‚Ä‚­‚ê‚é
	template<class T, int U>
	void data(CONTAINER* c, const char* name, std::array <T,U>& dataArray) {
		char s[256];
		int idx = 0;	
		for (auto& i : dataArray) {
			sprintf(s, "%s%d", name, idx);
			i = c->data(s);
			idx++;
		}
	}
	template<int U> 
	void data(CONTAINER* c, const char* name, std::array<VECTOR2, U>& dataArray) {
		char s[256];
		int idx = 1;
		for (auto& i : dataArray) {
			sprintf(s, "%s%d", name, idx);
			i = vector2(c, s);
			idx++;
		}
	}

	template<int U>
	void data(CONTAINER* c, const char* name, std::array<VECTOR3, U>& dataArray) {
		char s[256];
		int idx = 1;
		for (auto& i : dataArray) {
			sprintf(s, "%s%d", name, idx);
			i = vector3(c, s);
			idx++;
		}
	}

	template<int U>
	void data(CONTAINER* c, const char* name, std::array<COLOR, U>& dataArray) {
		char s[256];
		int idx = 1;
		for (auto& i : dataArray) {
			sprintf(s, "%s%d", name, idx);
			i = color(c, s);
			idx++;
		}
	}
	//–ß‚Á‚Ä‚­‚é”Å
	template<class T, int U>
	auto data(CONTAINER* c, const char* name) {
		std::array<T, U> dataArray;
		data(c, name, dataArray);
		return dataArray;
	}

	template<class T>
	auto data(CONTAINER* c, const char* name) {
		T dataArray;
		data(c, name, dataArray);
		return dataArray;
	}
}
#pragma warning(pop)
