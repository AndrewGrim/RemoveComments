#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main(int argc, char *argv[]) {
	char inputFile[150];
	char outputFile[150];
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-input") == 0) {
			strcpy(inputFile, argv[i + 1]);
		} else if (strcmp(argv[i],"-output") == 0) {
			strcpy(outputFile, argv[i + 1]);
		}
	}

	FILE *fileObject = fopen(inputFile, "r");

	FILE *modifiedFile = fopen(outputFile, "w+");
	int size = 1;
	while (fgetc(fileObject) != EOF) {
		size++;
	}
	fseek(fileObject, 0, 0);

	char fileContent[size];
	int index = 0;
	char input;
	char lastInput;
	bool isSingleLineComment = false;
	bool isMultiLineComment = false;
	char nextChar;

	while ((input = fgetc(fileObject)) != EOF) {
		nextChar = getc(fileObject);
		if ((input == '/' && nextChar == '/') && (lastInput != '"')) {
			isSingleLineComment = true;
			isMultiLineComment = false;
		} else if ((input == '/' && nextChar == '*') && (lastInput != '"')) {
			isMultiLineComment = true;
			isSingleLineComment = false;
		}
		ungetc(nextChar, fileObject);
		if (!isSingleLineComment && !isMultiLineComment) {
			fileContent[index] = input;
			fputc(fileContent[index], modifiedFile);
		}
		if (input == '\n') {
			if (isSingleLineComment) {
				fputc('\n', modifiedFile);
				isSingleLineComment = false;
			}
		}
		if (input == '*' && nextChar == '/') {
			getc(fileObject);
			isMultiLineComment = false;
		}
		lastInput = input;
		index++;
	}

	fclose(modifiedFile);
	fclose(fileObject);
	free(fileContent);
		
	return 0;
}
