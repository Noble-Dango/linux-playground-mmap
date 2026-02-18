#include <sys/mman.h>
#include <stdint.h>

#define KiB(n) (n * 1024)
#define MiB(n)(KiB(n) * 1024)

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int main(){
	size_t region_size = KiB(8); 
	
	uint8_t* region = (uint8_t*) 
		mmap(NULL, region_size, 
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, (-1), 0);

	for (int i = 0 ; i<region_size -1; ++i) {
		region[i] = 'A' + (i%26); 
	}
	region[region_size -1 ] = '\0';
	printf("%s[len=%zu]\n", region, strlen((char const*) region));
}
