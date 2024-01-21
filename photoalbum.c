/* 
  Alexander Cruz 
  ID: 119092071 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photoalbum.h"

Photo *create_photo(int id, const char *description) {
    Photo *newPhoto = (Photo *)malloc(sizeof(Photo));
    if (newPhoto == NULL) {
        return NULL; /* Memory allocation failed */
    }

    newPhoto->id = id;

    if (description != NULL) {
        newPhoto->description = (char *)malloc(strlen(description) + 1);
        if (newPhoto->description == NULL) {
            free(newPhoto);
            return NULL; /* Memory allocation failed */
        }
        strcpy(newPhoto->description, description);
    } else {
        newPhoto->description = NULL;
    }

    return newPhoto;
}

void print_photo(Photo *photo) {
    if (photo != NULL) {
        printf("Photo Id: %d, ", photo->id);
        if (photo->description != NULL) {
            printf("Description: %s\n", photo->description);
        } else {
            printf("Description: None\n");
        }
    }
}

void destroy_photo(Photo *photo) {
    if (photo != NULL) {
        if (photo->description != NULL) {
            free(photo->description);
        }
        free(photo);
    }
}

void initialize_album(Album *album) {
    int i;

    if (album != NULL) {
        album->size = 0;

        /* Initialize the array of Photo pointers to NULL */
        for (i = 0; i < MAX_ALBUM_SIZE; i++) {
            album->all_photos[i] = NULL;
        }
    }
}

void print_album(const Album *album) {
    int i;

    if (album != NULL) {
        if (album->size == 0) {
            printf("Album has no photos.\n");
        } else {
            for (i = 0; i < album->size; i++) {
                print_photo(album->all_photos[i]);
            }
        }
    }
}

void destroy_album(Album *album) {
    int i;

    if (album != NULL) {
        for (i = 0; i < album->size; i++) {
            destroy_photo(album->all_photos[i]);
        }
        album->size = 0;
    }
}

void add_photo_to_album(Album *album, int id, const char *description) {
    if (album != NULL && album->size < MAX_ALBUM_SIZE) {
        Photo *newPhoto = create_photo(id, description);
        if (newPhoto != NULL) {
            album->all_photos[album->size] = newPhoto;
            album->size++;
        }
    }
}
photoalbum.h

c
Copy code
#if !defined(PHOTOALBUM_H)
#define PHOTOALBUM_H

#define MAX_ALBUM_SIZE 8
#define SUCCESS 0
#define FAILURE -1

typedef struct photo {
    int id;
    char *description; /* dynamically-allocated string */
} Photo;

typedef struct album {
    int size;
    Photo *all_photos[MAX_ALBUM_SIZE];
} Album;

Photo *create_photo(int, const char *);
void print_photo(Photo *);
void destroy_photo(Photo *);
void initialize_album(Album *);
void print_album(const Album *);
void destroy_album(Album *);
void add_photo_to_album(Album *, int, const char *);

#endif
