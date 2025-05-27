const char *WORDS[] = {"CHESS", "BATTLE", "TIME", "PERSON", "YEAR", "THING", "WORLD", "WOMAN", "WORK", "GROUP"};
int WORDS_LEN = 10;
int r = 0;

void rand_bump(void) {
	r = ++r % WORDS_LEN;
}

char* rand_get_word(void) {
	return WORDS[r];
}
