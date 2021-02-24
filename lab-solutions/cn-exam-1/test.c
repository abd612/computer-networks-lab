#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main (void)
{
	char m[512];
	int i = 0, j = 0, k = 0, cnt = 0;

	printf("Enter a string: ");
	memset(m,0,sizeof(m));
	scanf ("%s", &m);

	printf("Char: %c = %d\n", m[5], (int)m[5]);
	
	int s = sizeof(m);
	int l = strlen(m);
	while(m[k] != '\0')
		k++;

	printf("Size: %i\n", s);
	printf("Length: %i\n", l);
	printf("Actual Length: %i\n", k);

	k = 0;
	
	// char c = m[l-1];
	// char t[l-2];

	// printf("Char: %c\n", c);

	// for(i = 0; i < l-3; i++)
	// 	t[i] = m[i];

	// while(t[j] != '\0')
	// 	if(t[j++] == 'c')
	// 		cnt++;

	// printf("Count: %i", cnt);
	return 0;
}