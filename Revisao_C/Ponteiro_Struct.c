#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum { RED, GREEN, BLUE, YELLOW, COLOR_COMPONENT_COUNT } color_component_t;
// uint8_t led1_color[COLOR_COMPONENT_COUNT] = {0};
// uint8_t led2_color[COLOR_COMPONENT_COUNT] = {0};

struct led_color {
    uint64_t vai;
    uint8_t red;
    uint8_t green;
    uint32_t reserved;
    uint8_t blue;
};

typedef struct led_color led_color_t;

int led_color_set(led_color_t *led_color, color_component_t color, uint8_t value)
{
    if (!led_color) {
        return -1;
    }
    switch (color) {
    case RED:
        led_color->red = value;
        break;
    case GREEN:
        led_color->green = value;
        break;
    case BLUE:
        led_color->blue = value;
        break;
    default:
        break;
    }
    return 0;
}

void led_color_print(led_color_t *led_color)
{
    if (!led_color) 
    {
        return;
    }
    printf("RED: %d | GREEN: %d | BLUE: %d\n", led_color->red, led_color->green, led_color->blue);
}

int led_color_set_all(led_color_t *led_color, uint8_t r, uint8_t g, uint8_t b)
{
    if (!led_color) 
    {
        return -1;
    }
    led_color->red   = r;
    led_color->green = g;
    led_color->blue  = b;
    led_color_print(led_color);
    return 0;
}

int main(int argc, char const *argv[])
{
    led_color_t led1_color = {0};
    led_color_t led2_color = {0};

    led_color_set_all(&led1_color, 50, 100, 150);
    led_color_set_all(NULL, 150, 100, 50);
    led_color_set_all(&led2_color, 1500, 1000, 5000);
    led_color_set_all(&led2_color, 150, 100, 50);

    printf("Size of the struct: %ld\n", sizeof(led_color_t));

    return 0;
}