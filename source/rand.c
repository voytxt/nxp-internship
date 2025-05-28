#include <stdint.h>

const char *WORDS[] = { "CHESS", "BATTLE", "TIME", "PERSON", "YEAR", "THING", "WORLD", "WOMAN",
		"WORK", "GROUP" };
const int WORDS_LEN = 10;

uint32_t r = 0;

void rand_bump(void) {
	r = ++r % 100000;
}

const char* rand_get_word(void) {
	// https://en.wikipedia.org/wiki/Linear_congruential_generator
	uint64_t t = (uint64_t) 1103515245u * r + 12345u;
	r = (uint32_t) (t % 2147483648u);

	return WORDS[r % WORDS_LEN];
}
