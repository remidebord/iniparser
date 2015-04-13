#include <iostream>
#include "ini.h"

INI :: INI(void)
{

}

char INI :: open(char* file)
{
	strcpy(m_file, file);
	
	m_f = fopen(m_file, "r+b");
	
	if(m_f == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

char INI :: get(char* key, char* value)
{
	char buffer[256] = {0};
	char tmp[256] = {0};
	
	// Reopen ini file
	m_f = freopen(m_file, "r+b", m_f);
	
	if(m_f)
	{
		// Back to the beginning of the file
		rewind(m_f);
		
		// Search
		while(fgets(buffer, 255, m_f) != NULL)
		{			
			// Key found ?
			if(strncmp(key, buffer, strlen(key)) == 0)
			{
				sprintf(tmp, "%s=%%s", key);
				
				sscanf(buffer, tmp, value);
					
				return 1;
			}
		}
	}
	
	return 0;
}

char INI :: set(char* key, char* value)
{
	char buffer[256] = {0};
	char tmp[256] = {0};
	int length = 0;
	char found = 0;
	char result = 0;
	
	FILE * f;
  	f = tmpfile();
	
	// Reopen ini file
	m_f = freopen(m_file, "r+b", m_f);
	
	if(m_f)
	{
		// Back to the beginning of the file
		rewind(m_f);
		
		// Search
		while(fgets(buffer, 255, m_f) != NULL)
		{
			// Key found ?
			if(strncmp(key, buffer, strlen(key)) == 0)
			{
				// Insert new key and value into temporary file
				sprintf(tmp, "%s=%s\n", key, value);
				
				fputs(tmp, f);
				
				found = 1;
			}
			else
			{
				// Insert key and value into temporary file
				length = strlen(buffer);
				
				if(buffer[length-1] == '\n')
				{
					buffer[length-1] = '\0';
					buffer[length-2] = '\n';
				}
				
				fputs(buffer, f);
			}
			
			memset(buffer, 0x00, 256);
			memset(tmp, 0x00, 256);
		}
		
		// Key found ?
		if(found)
		{
			// Reopen ini file (clear file)
			m_f = freopen(m_file, "w", m_f);
			
			if(m_f)
			{				
				// Back to the beginning of the files
				rewind(f);
				rewind(m_f);
				
				// Copy temporary file into ini file
				while(fgets(buffer, 255, f) != NULL)
				{					
					fputs(buffer, m_f);
				}
				
				result = 1;
			}
		}
	}
	
	// Close temporary file
	fclose(f);
	
	return result;
}

void INI :: close(void)
{
	if(m_f != NULL)
	{
		fclose(m_f);
	}
}
