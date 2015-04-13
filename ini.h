#include <cstring>
#include <cstdio>

class INI
{
	private:
		FILE* m_f;
		char m_file[64];
		
	public:
		INI(void);
		char open(char* file);
		char get(char* key, char* value);
		char set(char* key, char* value);
		void close(void);
};
