#include <sys/mman.h>
#include <stdint.h>

#define KiB(n) (n * 1024)
#define MiB(n)(KiB(n) * 1024)

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int main(){
	size_t region_size = MiB(1); 
	
	FILE* handle = fopen("test.txt", "r"); 
	if (!handle) {
		printf("failed to open file\n");
		exit(1);
	}

	int fd = fileno(handle);

	uint8_t* region = (uint8_t*) 
		mmap(NULL, region_size, 
			PROT_READ, MAP_SHARED, fd, 0);

	printf("%s[len=%zu]\n", region, strlen((char const*) region));
}
