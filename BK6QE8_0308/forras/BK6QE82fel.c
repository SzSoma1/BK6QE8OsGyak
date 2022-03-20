#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Adjon meg egy UNIX parancsot! \n");
	char par[6];
	scanf("%s", &par);
	system(par);
	return 0;
}
