#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include "book_utils.h"

// SEARCH FUNCTION
void search(char choice[], char input[])
{
    if(NULL== choice || NULL == input){
        fprintf(stderr, "you passed a null pointer\n");
        return;
    }

    printf("WELCOME TO BOOK RECOMMENDATIONS!\n");
    while (1) {
	printf
	    ("Pick from the options below to receive book recommendations\n");
	printf
	    ("1. Search by Genre\n2. Search by Author\n3. Search by Title\n");
	printf("\nOption: ");

	if (NULL != fgets(choice, CHOICE_LEN, stdin)) {
	    choice[strcspn(choice, "\n")] = '\0';
	}

	if (strcmp(choice, "1") != 0 &&
	    strcmp(choice, "2") != 0 && strcmp(choice, "3") != 0) {
	    printf("\nInvalid input. Please input 1, 2, 3\n");
	    printf("\n");
	} else {
	    break;
	}
    }


    if (strcmp(choice, "1") == 0) {
	printf("You have asked for books based on Genre\n");
	printf("What genre would you like to find recommensations of: ");
	if (NULL != fgets(input, INPUT_LEN, stdin)) {
	    input[strcspn(input, "\n")] = '\0';
	}
    } else if (strcmp(choice, "2") == 0) {
	printf("You have asked for books based on Author\n");
	printf("What Author would you like to see more books from: ");
	if (NULL != fgets(input, INPUT_LEN, stdin)) {
	    input[strcspn(input, "\n")] = '\0';

	    for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == ' ') {
		    input[i] = '+';
		};
	    }
	}
    } else if (strcmp(choice, "3") == 0) {
	printf("You have asked for books based on a book\n");
	printf
	    ("What book would you like to find recommendations based off: ");
	if (NULL != fgets(input, INPUT_LEN, stdin)) {
	    input[strcspn(input, "\n")] = '\0';

	    for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == ' ') {
		    input[i] = '+';
		};
	    }
	}
    }
    printf("A text file will be generated with recommendations\n");
    printf("\n");
}

    // for (i = 0; input[i] != '\0'; i++) {
    // input[i] = tolower(input[i]);
    // }

// WRITE CALLBACK FUNCTION
size_t write_callback(void *contents, size_t size, size_t nmemb,
		      Memory *mem)
{

    size_t real_size = size * nmemb;
    //struct Memory *mem = (struct Memory *)userdata;

    char *ptr = realloc(mem->data, mem->size + real_size + 1);
    if (NULL == ptr)
	return 0;		// out of memory

    mem->data = ptr;

    memcpy(&(mem->data[mem->size]), contents, real_size);

    mem->size += real_size;
    mem->data[mem->size] = '\0';

    return real_size;
}
