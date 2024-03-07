#include <stdio.h>

size_t _strlen(char *str) { // _strlen(string) returns length of string
	int count = 0;
	while(str[count] != '\0') // \0 NULL terminator, refers to nothing
		count++;
	return count;
}
int _strcmp(char *_source,char *_target) { // if(_strcmp(string,string)) If the same, the 'if' block returns true(1) if not, returns false(0)
	if(_strlen(_source) != _strlen(_target))
		return 0;
	else {
		int i = 0;
		while(i < _strlen(_source))
			if(_source[i] == _target[i])
				i++;
		if(i == _strlen(_source))
			return 1;
		else
			return 0;
	}
}
void* _memset(void *dst,int c, size_t len) {
	unsigned char* char_dst = dst;
	while (len--)
		*char_dst++ = c;
	return dst;
}
/*	void _memset(char *dst,int c,int len) {
 		while(len--)
   			*dst++ = c;
	}
*/

void * _memcpy(void *dest,void *src,int n) { // copys src to dest
	if(dest==NULL) return NULL;
	char *char_dest = (char*) dest;
	char *char_src = (char*) src;
	// for(int i=0;i<n;i++) {
	// 	char_dest[i] = char_src[i];
	// }
	while (n--) {
		*char_dest = *char_src;
		*char_dest++;
		*char_src++;
	}
	return dest;
}

void readInt(int *val) {
	scanf("%d",val);
}
void readChar(char *c) {
	scanf("%c",c);
}
void readStr(char * str) {
	fgets(str,sizeof(str),stdin);
	// If you declare the string as 'char *' it probably won't work (cause:size of string)
}
