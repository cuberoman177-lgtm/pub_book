#ifndef book_utils_h
#define book_utils_h

#define BOOKGENRE_LEN 20
#define INPUT_LEN 20
#define CHOICE_LEN 10
#define CAT_LEN 50
#define URL_SIZE 256

// STRUCTS
struct _Memory {
    char *data;
    size_t size;
};
typedef struct _Memory Memory;

void search(char choice[], char input[]);
size_t write_callback(void *contents, size_t size, size_t nmemb,
		      Memory * mem);

#endif				// book_utils_h
