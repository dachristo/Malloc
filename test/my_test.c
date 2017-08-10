#include <stdlib.h> 
#include <stdio.h>
#include "../include/malloc.h"

int main() 
{ 
	int i; 
	char *addr; 
	char *addr2; 
	char *addr3; 
	char *addr4; 

	addr = (char *)malloc(42);	
	addr2 = (char *)malloc(42);
	addr3 = (char *)malloc(42);
	addr4 = (char *)malloc(42);
	show_alloc_mem();
	free(addr);
	show_alloc_mem();
	free(addr2);
	show_alloc_mem();	
	free(addr3);
	show_alloc_mem();	
	return (0); 
} 
