#ifndef DEF_SETTINGS
#define DEF_SETTINGS

typedef struct
{
	unsigned int screenW, screenH, frameSpeed, nbrBlocks;
	float speed;
} Settings;

Settings* SettingsCreate();
void SettingsLoad(Settings* set, char* configFileName);
void SettingsFree(Settings* set);

#endif