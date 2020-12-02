/*
 * Possible errors:
	- invalid file name
	- too many input arguments
 */

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	char * inputFileName = argv[1];
	//FILE * inputFile = fopen(inputFileName, "rb");
}