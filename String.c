#include <stdio.h>
#include <stdlib.h>
#include "String.h"

void realloc_s (void **ptr, size_t taille);

String* StringCreate(char* data)
{
	unsigned int i;
	String* str = (String*) malloc(sizeof(String));
	if(str != NULL)
	{
		for(str->size = 0; data[str->size] != '\0'; str->size++);
		//str->size--;
		str->data = (char*) malloc((str->size+1)*sizeof(char)); //+1 car il y a '\0'
		for(i = 0; i < str->size; i++)
			str->data[i] = data[i];
		str->data[str->size] = '\0';
	}
	
	return str;
}

int StringConcat(String* src, const String* added)
{
	unsigned int i;

	realloc_s(&src->data, (added->size + src->size + 1) * sizeof(char));
	if(src->data == NULL)
		return 1;
		
	src->size += added->size;
	for(i = 0; i < added->size; i++)
		src->data[i + src->size - added->size] = added->data[i];
	
	src->data[src->size] = '\0';
	return 0;
}

int StringConcatChar(String* src, const char* added)
{
	unsigned int size, i;
	for(size = 0; added[size] != '\0'; size++);
	//size--;
	
	realloc_s(&src->data, (size + src->size + 1) * sizeof(char));
	if(src->data == NULL)
		return 1;
		
	src->size += size;
	for(i = 0; i < size; i++)
		src->data[i + src->size - size] = added[i];
	
	src->data[src->size] = '\0';
	return 0;
}

int StringCompareChar(const String* str, const char* data)
{
	unsigned int i, size;
	
	for(size = 0; data[size] != '\0'; size++);
	//size--;
	
	if(str->size != size)
		return 0;
		
	for(i = 0; i < str->size; i++)
		if(str->data[i] == data[i])
			return 0;
			
	return 1;
}

int StringCompare(const String* str1, const String* str2)
{
	unsigned int i;
	
	if(str1->size != str2->size)
		return 0;
		
	for(i = 0; i < str1->size; i++)
		if(str1->data[i] == str2->data[i])
			return 0;
			
	return 1;
}

void StringFree(String* str)
{
	free(str->data);
	free(str);
}

void realloc_s (void **ptr, size_t taille)
{
 void *ptr_realloc = realloc(*ptr, taille);
 
 if (ptr_realloc != NULL)
     *ptr = ptr_realloc;
 else
 {
	 free(*ptr);
	 *ptr = NULL;
 }
}
