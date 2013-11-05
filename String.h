#ifndef DEF_STRING
#define DEF_STRING

struct String
{
	char* data;
	unsigned int size;
};
typedef struct String String;

String* StringCreate(char* data);
int StringConcat(String* src, const String* added);
int StringConcatChar(String* src, const char* added);
int StringCompareChar(const String* str, const char* data);
int StringCompare(const String* str1, const String* str2);
void StringFree(String* str);

#endif