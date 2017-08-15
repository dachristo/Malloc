#include <stdlib.h> 
#include <stdio.h>
#include "../include/malloc.h"

void	show_alloc_mem();

int main() 
{ 
	int i; 
	char *addr; 

	i = 0;
	while (i < 1024) 
	{
		addr = (char*)malloc(i);	
		addr[0] = 42;
		free(addr);
		i++;
	}
	show_alloc_mem();
	return (0); 
}
