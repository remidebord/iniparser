#include <iostream>
#include "ini.h"

INI ini;

int main(int argc, char** argv)
{
	char buffer[256] = {0};

	if(ini.open("test.txt"))
	{
		// read
		ini.get("AUDIO", buffer);
		
		printf("%s\n", buffer);
		
		// write
		ini.set("VIDEO", "H264");
		
		ini.close();
	}
	else
	{
		printf("failed to open text file !");
	}
	
	return 0;
}
