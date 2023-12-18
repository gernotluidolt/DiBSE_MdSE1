#include "my_string.h"
# include <string.h>

int string_cmp(const char* str1, const char* str2){
    // Loop so Lange bis ein string zu Ende ist, und solange die strings gleich sind
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    // Wenn die strings gleich sind, muss das Ergebnis 0 sein
    return *str1 - *str2;
}

unsigned int string_len(const char* str){
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void string_rev(char* str){
    int len  = string_len(str);
    char temp;
    // Buchstaben werden ausgetauscht von vorne nach hinten
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}


char *string_chr(const char* str, const char c){
    while (*str != '\0') { // Durchlaufe die Zeichenkette bis zum Ende
        if (*str == c) {
            return (char *)str; // Gib einen Pointer auf das gefundene Zeichen zurück
        }
        str++; // Gehe zum nächsten Zeichen
    }
    return NULL; // Gib NULL zurück, wenn c nicht gefunden wurde
}