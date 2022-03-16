#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>


#define MAX_BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/max_brightness\0"
#define BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/brightness\0"


void read_max_brightness(char *buffer, size_t buffer_size) {
	FILE *file = fopen(MAX_BRIGHTNESS_PATH, "r");
	assert(file != NULL);
	fread(buffer, 1, buffer_size, file);
	fclose(file);
}


void read_current_brightness(char *buffer, size_t buffer_size) {
	FILE *file = fopen(BRIGHTNESS_PATH, "r");
	assert(file != NULL);
	fread(buffer, 1, buffer_size, file);
	fclose(file);
}


void write_current_brightness(char *buffer) {
	FILE *file = fopen(BRIGHTNESS_PATH, "w");
	assert(file != NULL);

	size_t write_size = fwrite(buffer, 1, strlen(buffer), file);
	assert(write_size == strlen(buffer));

	fclose(file);
}


void print_help() {
	printf(
		"\nUsage:"
		"\n\tbrightness [<option>|<brightness>|max]"
		"\n"
		"\nCalling without any arguments will print the current brightness"
		"\nCalling with a brightness value of 'max' will set to the max brightness"
		"\n"
		"\nOptions:"
		"\n\t-m | --max\tPrint the max brightness"
		"\n\t-h | --help\tPrint this help"
		"\n"
		"\n"
	);
}


int main(int argc, char *argv[]) {
	// No arguments - print current brightness
	if (argc == 1) {
		char buffer[100] = {0};
		read_current_brightness(buffer, 90);
		printf("%s", buffer);
	}
	// Help
	else if (
		// Only one argument/option is supported
		argc != 2

		// Various ways of requesting the help documentation
		|| 0 == strcmp("-h", argv[1])
		|| 0 == strcmp("--help", argv[1])
	) {
		print_help();
	}
	// Print max brightness
	else if (0 == strcmp("-m", argv[1]) || 0 == strcmp("--max", argv[1])) {
		char buffer[100] = {0};
		read_max_brightness(buffer, 90);
		printf("%s", buffer);
	}
	// Set to max brightness
	else if (0 == strcmp("max", argv[1])) {
		char buffer[100] = {0};
		read_max_brightness(buffer, 90);
		write_current_brightness(buffer);
	}
	// Last chance to catch bad arguments
	else if (*argv[1] == '-') {
		print_help();
	}
	// Set to brightness in argument
	else {
		char buffer[100] = {0};
		strcpy(buffer, argv[1]);
		strcpy(buffer + strlen(argv[1]), "000");
		write_current_brightness(buffer);
	}
}