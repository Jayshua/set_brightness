#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Incorrect arguments.");
	} else {
		FILE *brightness = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
		assert(brightness != NULL);

		size_t write_size = fwrite(argv[1], strlen(argv[1]), 1, brightness);
		assert(write_size > 0);

		char zeros[] = "000";
		size_t write_size_2 = fwrite(zeros, 3, 1, brightness);
		assert(write_size_2 > 0);

		fclose(brightness);
	}
}