#include <windows.h>
#include <iomanip> 
#include <string>
#include "Utilities.h"
 

void prompt(std::string str, unsigned int type)
{
	std::string keychain;

	switch (type)
	{
	case 0:
		keychain = "[Other] ";
			break;
	case 1:
		keychain = "[Texture] ";
			break;
	case 2:
		keychain = "[Music] ";
			break;
	case 3:
		keychain = "[Sound] ";
			break;
	case 4:
		keychain = "[Info]";
			break;
	case 5: 
		keychain = "[Alert]";
			break;
	default:
		keychain = "";
	}
	keychain += str;
	std::cout << keychain << std::endl;
}

void initLog()
{
	prompt("=========================================");
	prompt("====   Popolino's LogSplat  (v1.0)   ====");
	prompt("=========================================");
	prompt("");
	prompt("       ** [LOADING COMPONENTS] **\n");
 
}


void testRessource(bool state, std::string name)
{
	if (!state)
	{
		prompt("Failed to load ressource : " + name, 1);
		std::getchar();
		exit(-1);
	}
	else
		prompt(name + " Loaded 100 %", 1);
}
 