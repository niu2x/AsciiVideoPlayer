#include <stdio.h>
#include <windows.h>

const int buffSize = 1024*1024*1024;
char buff[buffSize];

int main(){
	setvbuf(stdout, buff, _IOFBF, buffSize);

	int n = 10000;
	while( -- n ){
		system("cls");
		for(int i = 0; i < 10; i ++)
			printf("%d", i + n);
		printf("\n");
		fflush(stdout);
		Sleep(300);
	}

	getchar();
	return 0;
}