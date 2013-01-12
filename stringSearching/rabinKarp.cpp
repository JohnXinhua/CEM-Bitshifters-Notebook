
int int_mod(int a, int b) { // correctly calculates a mod b even if a < 0
	return (a % b + b) % b;
}

void Rabin_Karp(text[], pattern[]) {
	// let n be the size of the text, m the size of the pattern, B - the base of the numeral system,
	// and M - a big enough prime number

	if (n < m) return; // no match is possible

	// calculate the hash value of the pattern
	hp = 0;
	for (i = 0; i < m; i++)
		hp = int_mod(hp * B + pattern[i], M);

	// calculate the hash value of the first segment of the text of length m
	ht = 0;
	for(i = 0; i < m; i++)
		ht = int_mod(ht * B + text[i], M);

	if(ht == hp) check character by character if the first
							 segment of the text matches the pattern;

	// start the "rolling hash" - for every next character in the text calculate the hash value
	// of the new segment of length m; E = (Bm-1) modulo M
	for(i = m; i < n; i++) {
		ht = int_mod(ht - int_mod(text[i - m] * E, M), M);
		ht = int_mod(ht * B, M);
		ht = int_mod(ht + text[i], M);

		if(ht == hp) check character by character if the
								 current segment of the text matches
								 the pattern;
	}
}
