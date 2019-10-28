#include <stdint.h>
#include <stdio.h>
#include <string.h>

// #define RED 0
// #define GREEN 1
// #define BLUE 7

typedef enum { RED, GREEN, BLUE, YELLOW, COLOR_COMPONENT_COUNT } color_component_t; // Defined enum 
uint8_t led1_color[COLOR_COMPONENT_COUNT] = {0};
uint8_t led2_color[COLOR_COMPONENT_COUNT] = {0};


int led_color_set(uint8_t *led_color, color_component_t color, uint8_t value)
{
    if (!led_color) 
    {
        return -1;
    }

    led_color[color] = value;
    return 0;
}

void led_color_print(uint8_t *led_color)
{
    if (!led_color)
    {
        return;
    }
    printf("RED: %d | GREEN: %d | BLUE: %d\n", led_color[RED], led_color[GREEN], led_color[BLUE]);
}

int led_color_set_all(uint8_t *led_color, uint8_t r, uint8_t g, uint8_t b)
{
    // if (!led_color) {
    //     return -1;
    // }
    int rc = 0;
    rc += led_color_set(led_color, RED, r);     
    rc += led_color_set(led_color, GREEN, g);
    rc += led_color_set(led_color, BLUE, b);
    led_color_print(led_color);
    return rc;                                  // Return code. If this code as different then 0 an error happened
}

int main(int argc, char const *argv[])
{
    int a = 10;
    // {
    char b = 5;
    // }
    b = a;
    printf("Value a:0x%02X b:0x%02X\n", a, b);
    a = 0x101;  // a = 257;
    b = a;
    printf("Value a:0x%02X b:0x%02X\n", a, b);
    long int c      = 0;
    long long int d = 0;
    printf("Value sizeof c:%lu d:%lu\n", sizeof(c), sizeof(d));

    uint8_t e[6];
    char f = 100;
    // = {0};  // 0 '\0' NULL

    memset(e, 0, sizeof(e)); //sizeof(e) = 6
    for (int i = 0; i < sizeof(e); ++i) 
    {
        printf("Value sizeof e[%d]:0x%02X\n", i, e[i]);  //-> *(e + i*sizeof(type e aponta))
    }
    // e[6] = 5; *** stack smashing detected ***
    printf("Value f:0x%02X\n", f);

    char *g = NULL;         // Cria um ponteiro NULL
    g       = (char *) &a;  // Cast - Transforma o ponteiro para um ponteiro de char
    *g      = 10;           // Conteúdo de g = 10

    printf("Value of content of G: %d\n", *g);

    // Enum

    led_color_set_all(led1_color, 50, 100, 150);
    if (led1_color[RED] != 50 || led1_color[GREEN] != 100 || led1_color[BLUE] != 150) {
        printf("Failed!\n");
    }
    led_color_set_all(NULL, 150, 100, 50);
    led_color_set_all(led2_color, 1500, 1000, 5000);    // Valores truncados, são muito grandes para serem representados por uint8
    led_color_set_all(led2_color, 150, 100, 50);
    // led_color_set(led1_color, RED, 50);
    // led_color_set(led1_color, GREEN, 100);
    // led_color_set(led1_color, BLUE, 150);
    // led_color_print(led1_color);

    // led_color_set(led2_color, RED, 150);
    // led_color_set(led2_color, GREEN, 100);
    // led_color_set(led2_color, BLUE, 50);
    // led_color_print(led2_color);
    return 0;
}