#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef enum {
    OVAL,
    RECTANGLE,
} Shape;

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW
} Color;

typedef struct {
    unsigned int size;
    Shape shape;
    const char* color;
} Graphic;

const char* get_color(Color color) {
    switch(color) {
        case COLOR_RED: return RED;
        case COLOR_GREEN: return GRN;
        case COLOR_YELLOW: return YEL;
        default: return RESET;
    }
}

void paint(Graphic graphic) {
    double radius = graphic.size / 2.0;
    int i, j;

    for (i = 0; i <= 2 * radius; i++) {
        for (j = 0; j <= 2 * radius; j++) {
            switch(graphic.shape) {
                case RECTANGLE:
                    (void) printf("%s*" RESET, graphic.color);
                    break;
                case OVAL: {
                    double distance = sqrt((i - radius) * (i - radius) + (j - radius) * (j - radius));
                    if (distance > radius - 0.5 && distance < radius + 0.5) {
                        (void) printf("%s*" RESET, graphic.color);
                    } else {
                        (void) printf(" ");
                    }
                } break;
            }
        }
        (void) printf("\n");
    }
}

int main() {
    int input;
    Graphic graphic;

    do {
        (void) printf("Geben Sie die gewünschte Form an [OVAL=0 | RECTANGLE=1]: ");
        (void) scanf("%d", &input);
        graphic.shape = (Shape)input;

        (void) printf("Geben Sie die gewünschte Grösse an: ");
        (void) scanf("%u", &graphic.size);

        (void) printf("Geben Sie die gewünschte Farbe an [RED=0 | GREEN=1 | YELLOW=2]: ");
        (void) scanf("%d", &input);
        graphic.color = get_color((Color)input);

        paint(graphic);

        while(getchar() != '\n'); // empty buffer
        (void) printf("\nMöchten Sie weiter machen oder abbrechen? [(n)ext|(q)uit] ");
    } while(getchar() == 'n');

    (void) printf("Byebye..\n");
    return EXIT_SUCCESS;
}