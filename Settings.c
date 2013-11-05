#include <stdio.h>
#include <stdlib.h>
#include "Settings.h"



Settings* SettingsCreate()
{
	Settings* set = (Settings*) malloc(sizeof(Settings));

	if(set != NULL)
	{
		set->screenW = 800;
		set->screenH = 600;
		set->frameSpeed = 30;
		set->nbrBlocks = 10;
		set->speed = 1.5;
	}

	return set;
}


void SettingsLoad(Settings* set, char* configFileName )
{
	FILE* config = fopen(configFileName,"r");
	if(config != NULL)
	{
		fscanf(config, "largeur_fenetre=%i\n", &set->screenW);
		fscanf(config, "hauteur_fenetre=%i\n", &set->screenH);
		fscanf(config, "framerate_speed=%i\n", &set->frameSpeed);
		fscanf(config, "nombre_blocs_aleatoires=%i\n", &set->nbrBlocks);
		fscanf(config, "snake_speed=%f\n", &set->speed);

		fclose(config);
	}
}


void SettingsFree( Settings* set )
{
	free(set);
}
