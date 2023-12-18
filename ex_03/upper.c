#include <stdio.h>

int isLowercase(char c) {
    return (c >= 'a' && c <= 'z');
}

int main() {
    // Hier wird der User Input gespeichert, die Zeichenkette darf 50 Zeichen lang sein, deswegen hier 51 um Platz für den Nullterminator "\0" zu reservieren
    char str[51];
    // Um mit whitespace chars umzugehen, wird der scanf() in eine schleife gepackt. Der input wird dann Zeichen für Zeichen (char c) gelesen, solange bis das Ende der Eingabe "\n" erreicht wurde
    char c;
    // i als Position im String
    int i = 0;

    while (1) {
        // Liest ein Zeichen ein
        scanf("%c", &c);
        // break, wenn das Zeichen das Ende der Eingabe ist
        if (c == '\n' || i >= 49) {
            break;
        }
        // Wenn das Zeichen lowercase ist, wird es durch ein uppercase ersetzt
        if (isLowercase(c)) {
            c -= 32;
        }
        // Das Zeichen wird in str gespeichert
        str[i++] = c;
    }
    // Den String terminieren
    str[i] = '\0';
    // Ausgabe an Konsole
    printf("%s\n", str);
    return 0;
}