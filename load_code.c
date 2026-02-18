#include <sys/mman.h>
#include <stdint.h>

#define KiB(n) (n * 1024)
#define MiB(n)(KiB(n) * 1024)

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#include <dlfcn.h>

#define USE_DLOPEN 0
int main(){
#if USE_DLOPEN
	void* lib_handle = dlopen("./fib.lib.bin", RTLD_NOW);
	printf("lib_h = %p\n", lib_handle);

	void* fib_ref = dlsym(lib_handle, "fib");
	printf("&fib = %p\n", fib_ref);
	uint64_t (*fib) (uint64_t) = fib_ref; 
	printf("fib(6) = %zu\n", fib(6)); 
#else
	size_t region_size = MiB(1); 
	
	FILE* handle = fopen("fib.lib.bin", "r"); 
	if (!handle) {
		printf("failed to open file\n");
		exit(1);
	}

	int fd = fileno(handle);

	void* region = 
		mmap(NULL, region_size, 
			PROT_READ|PROT_EXEC, MAP_PRIVATE, fd, 0);

	size_t offset = 0x320; // hardcoded for now; you can view ELF symbols with 'nm'

	void* fib_ref = region + offset; 
	uint64_t (*fib) (uint64_t) = fib_ref; 
	
	uint64_t arg = 6;
	printf("fib(%zu) = %zu\n", arg, fib(arg));
#endif
}
