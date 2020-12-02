/*
 * Flag names:
	-ltu - lower to upper
	-utl - upper to lower

 * Possible errors:
	- invalid file name
	- too many input arguments
 */

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	if (argv[2] == NULL){
		printf("Error: Flag is missing. Default flag set: -ltu.\n");
	}
	char * inputFileName = argv[1];
	//FILE * inputFile = fopen(inputFileName, "rb");
}