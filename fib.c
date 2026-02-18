#include <stdint.h> 

uint64_t fib(uint64_t n){
	uint64_t a = 0;
	uint64_t b = 1; 
	uint64_t fib = 0;
	for (uint64_t i = 2; i<=n; ++i){
		fib = a + b;
		a = b;
		b = fib;
	}
	return fib;
}
