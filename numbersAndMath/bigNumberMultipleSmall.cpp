bool multiple(char *num, int div) {
	int len = strlen(num);
	int calc = 0;
	int power = 1;
	for (int i = len-1; i >= 0; i--) {
		int curr = ((num[i] - '0') * power) % div;
		calc = (calc + curr) % div;
		power = (power * 10) % div;
	}
	return calc == 0;
}
