#include <stdlib.h> 
#include "../malloc.h"

void	show_alloc_mem();

int main() 
{ 
	int i; 
	char *addr; 

	int value = 1024;
	while (value > 0) 
	{
		addr = (char*)malloc(value);	
		addr[0] = 42;
		free(addr);
		value--;
	}
	show_alloc_mem();
	return (0); 
}
