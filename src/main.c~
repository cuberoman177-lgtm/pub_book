#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "book_utils.h"

// URL - libcurl downloads data - you store it in a buffer - then parse with cJSON

// TODO
// 3. INTEGRATE AI 

// MAIN
// If you might read a variable before assigning it - initialise it
// If you always assign it before use - no need to initialise
int main(int argc, char **argv)
{
    char *api_key = getenv(argv[1]);

    if (NULL == api_key) {
	fprintf(stderr, "No api key found\n");
	return -1;
    }

    FILE *ptr;
    char input[INPUT_LEN] = { '\0' };
    char choice[CHOICE_LEN] = { '\0' };
    char url[URL_SIZE];
    CURL *curl = NULL;
    CURLcode res;
    Memory chunk;
    chunk.data = malloc(1);
    chunk.size = 0;


    search(choice, input);
    int user_choice = atoi(choice);

    switch (user_choice) {

    case 1:
	// builds strings (url)
	snprintf(url, sizeof(url),
		 "https://www.googleapis.com/books/v1/volumes?q=subject:%s&key=%s",
		 input, api_key);
	break;
    case 2:
	snprintf(url, sizeof(url),
		 "https://www.googleapis.com/books/v1/volumes?q=inauthor:%s&key=%s",
		 input, api_key);
	break;
    case 3:
	snprintf(url, sizeof(url),
		 "https://www.googleapis.com/books/v1/volumes?q=intitle:%s&key=%s",
		 input, api_key);
	break;
    };



    // libcurl downloads the data requested from url provided.
    curl = curl_easy_init();

    // This configures settings inside curl.
    if (curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
	res = curl_easy_perform(curl);	// this actually executes the requests using above settings.
	if (res != CURLE_OK) {
	    printf("error occured\n");
	}
	curl_easy_cleanup(curl);	// destroy curl object and close internal state. Does not touch &chunk. 
    }
    cJSON *json = cJSON_Parse(chunk.data);	// get the data from this struct
    cJSON *book_items = cJSON_GetObjectItem(json, "items");


    // NEED TO GET KEYWORDS FROM DESCRIPTION TO HELP WITH RECOMMENDING OTHER BOOKS
    // WILL THEN NEED TO STORE KEYWORDS AND SEARCH USING THEM BEFORE CREATING THE TXT FILE


    int count = cJSON_GetArraySize(book_items);

    ptr = fopen("book_output.txt", "w");
    if (ptr == NULL) {
	printf("Error opening File");
	return 1;
    } else {
	for (int i = 0; i < count && i <= 10; i++) {
	    cJSON *book = cJSON_GetArrayItem(book_items, i);
	    cJSON *volume_info = cJSON_GetObjectItem(book, "volumeInfo");
	    cJSON *book_title = cJSON_GetObjectItem(volume_info, "title");
	    fprintf(ptr, "Title: %s\n", book_title->valuestring);
	    fprintf(ptr, "\n");

	    cJSON *book_description =
		cJSON_GetObjectItem(volume_info, "description");
	    if (cJSON_IsString(book_description)
		&& book_description->valuestring != NULL) {
		fprintf(ptr, "Description: %s\n",
			book_description->valuestring);
		fprintf(ptr, "\n");
	    } else {
		fprintf(ptr, "No description available");
		fprintf(ptr, "\n");
	    }

	    cJSON *author = cJSON_GetObjectItem(volume_info, "authors");
	    cJSON *author_name = cJSON_GetArrayItem(author, 0);
	    if (author_name != NULL) {
		fprintf(ptr, "Author: %s\n", author_name->valuestring);
		fprintf(ptr, "\n");
	    } else {
		fprintf(ptr, "No author information available");
		fprintf(ptr, "\n");
	    }

	    cJSON *catogories =
		cJSON_GetObjectItem(volume_info, "categories");
	    cJSON *catogorie = cJSON_GetArrayItem(catogories, 0);
	    if (catogorie != NULL) {
		fprintf(ptr, "catogorie: %s\n", catogorie->valuestring);
		fprintf(ptr, "\n");
	    } else {
		fprintf(ptr, "No catogorie information available");
		fprintf(ptr, "\n");
	    }

	    cJSON *average_rating =
		cJSON_GetObjectItem(volume_info, "averageRating");
	    cJSON *rating_count =
		cJSON_GetObjectItem(volume_info, "ratingsCount");
	    if (average_rating != NULL) {
		fprintf(ptr, "Average Rating: %.1f\n",
			average_rating->valuedouble);
		if (rating_count != NULL) {
		    fprintf(ptr, "Number of ratings: %.1f\n",
			    rating_count->valuedouble);
		    fprintf(ptr, "\n");
		}
	    } else {
		fprintf(ptr, "No ratings");
		fprintf(ptr, "\n");
	    }

	    fprintf(ptr, "\n");
	}
	fclose(ptr);
    }
    cJSON_Delete(json);



    // Free the memory YOU allocated in your callback. If you dont the memory stays 'reserved'. 
    // Nothing else can use it, even after you stop needing it. That is called a memory leak. 
    // Free tells the Operating System, I'm done with this memory, you can reuse it. 
    free(chunk.data);
    return 0;
}
