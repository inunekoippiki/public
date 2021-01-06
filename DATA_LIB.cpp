#include <stdio.h>
#include "../Library/VECTOR2.h"
#include "../Library/CONTAINER.h"
#include "../Library/DATA.h"
#include "DATA_LIB.h"
namespace DATA_LIB {
	VECTOR2 vector2(CONTAINER* c, const char* name) {
		char s[256];
		strcpy(s, name);
		int len = (int)strlen(s);
		s[len + 2] = '\0';
		s[len] = '.';
		s[len+1] = 'x';
		float x = c->data(s);
		s[len+1] = 'y';
		float y = c->data(s);
		return VECTOR2(x, y);
	}

	VECTOR3 vector3(CONTAINER* c, const char* name) {
		char s[256];
		strcpy(s, name);
		int len = (int)strlen(s);
		s[len + 2] = '\0';
		s[len] = '.';
		s[len + 1] = 'x';
		float x = c->data(s);
		s[len + 1] = 'y';
		float y = c->data(s);
		s[len + 1] = 'z';
		float z = c->data(s);
		return VECTOR3(x, y, z);
	}
	COLOR color(CONTAINER* c, const char* name){
		char s[256];
		strcpy(s, name);
		int len = (int)strlen(s);
		s[len + 2] = '\0';
		s[len] = '.';
		s[len + 1] = 'r';
		float r = c->data(s);
		s[len + 1] = 'g';
		float g = c->data(s);
		s[len + 1] = 'b';
		float b = c->data(s);
		s[len + 1] = 'a';
		float a = c->data(s);
		return COLOR(r, g, b, a);
	}
}