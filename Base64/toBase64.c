int main(int argc, char** argv){
	FILE * inputFile = fopen(argv[1], "r");
	if (inputFile == NULL){
		printf("File reading error.");
		return -1;
	}

	fclose(inputFile);
}