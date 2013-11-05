#include <stdio.h>

#include "Log.h"
#include "defines.h"

void LogPrint(char* str)
{
	if(LOG_ACTIVE)
		puts(str);
}

