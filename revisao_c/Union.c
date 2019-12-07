#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SET_BIT(byte, bit) byte = byte | (1 << bit)     // set the x.content[2] = 0;
#define CLEAR_BIT(byte, bit) byte = byte & ~(1 << bit)  // set the x.content[2] = 0;
#define GET_BIT(byte, bit) (byte << (7 - bit)) >> 7     // get the x.content[2]
#define TOGGLE_BIT(byte, bit) byte = byte ^ (1 << bit)  // set the x.content[2] = 0;

#define CHECK_CONDITION(x) \
    do {                   \
        if (x)             \
            return -1;     \
    } while (0)

struct packet_s {
    uint8_t ab;
    uint8_t c;
    uint16_t d;
};

struct packet_simple_s {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint16_t d;
};

union int_array4 {
    int a;
    uint8_t data[4];
};

union int_array4 x = {0};

// Pode acessar a union byte_s através de content ou nibble ou por bit - obs: dentro da union
// Guarda na memória um espaço de 8 bytes 
union byte_s {
    uint8_t content;
    struct {
        unsigned int low : 4;
        unsigned int high : 4;
    } nibble;
    struct {
        unsigned int bit0 : 1;
        unsigned int bit1 : 1;
        unsigned int bit2 : 1;
        unsigned int bit3 : 1;
        unsigned int bit4 : 1;
        unsigned int bit5 : 1;
        unsigned int bit6 : 1;
        unsigned int bit7 : 1;
    };
};

typedef union byte_s byte_t;

// a:3 - reserva na memória um espaço para 3 bits
struct packet_ninja_s {
    unsigned int a : 3;
    unsigned int b : 5;
    union {
        struct {
            unsigned int reserved : 8;
            unsigned int c : 8;
            unsigned int d : 16;
        };
        uint8_t data[4];
    };
};

typedef struct packet_s packet_t;
typedef struct packet_ninja_s packet_ninja_t;

// packet_t: 8bytes->ab , 8bytes-> c, 16bytes->d
// Função do tipo packet_t. Assim, devemos acessar a struct com '.' 
packet_t packet_create(uint8_t a, uint8_t b, uint8_t c, uint16_t d)
{
    packet_t pkt = {.ab = a | b << 3, .c = c, .d = d};
    return pkt;
}

// packet_ninja_t: 3bits->a, 5 bits->b; 8bytes->reserved, 8bytes->c, 16bytes->d; data[4]
// packet passado como ponteiro. Assim, acessamos a struct usando '->'
int packet_ninja_init(packet_ninja_t *pkt, uint8_t a, uint8_t b, uint8_t c, uint16_t d)
{
    pkt->a = a;
    pkt->b = b;
    pkt->c = c;
    pkt->d = d;
    return 0;
}

// Copia o conteúdo de data para pkt->data. Memcpy(destination, source, size)
// Data + 1 pois o primeiro byte de data é reservado
int packet_ninja_set(packet_ninja_t *pkt, uint8_t *data, size_t size)
{
    CHECK_CONDITION(size > 3);
    // if (size > 3) {
    //     return -1;
    // }
    memcpy(pkt->data + 1, data, size);
    // pkt->c = data[0];
    // pkt->d = data[1] | data[2] << 8;
    return 0;
}


//pkt->d 16 bytes
int packet_ninja_set_bytes(packet_ninja_t *pkt, uint8_t *data, size_t size)
{
    if (size > 3) {
        return -1;
    }

    pkt->c = data[0];
    pkt->d = data[1] | data[2] << 8;
    return 0;
}

void packet_ninja_print(packet_ninja_t *pkt)
{
    if (!pkt) {
        return;
    }
    printf("Packet ninja: a %d/%02Xh, b %d/0x%02X, c %d/0x%02X, d %d/0x%02X\n", pkt->a,
           pkt->a, pkt->b, pkt->b, pkt->c, pkt->c, pkt->d, pkt->d);
}

int main(int argc, char const *argv[])
{
    packet_ninja_t my_pkt = {0};
    packet_ninja_init(&my_pkt, 6, 2, 0x0f, 0x10e4);
    packet_ninja_print(&my_pkt);
    uint8_t data[] = {0x01, 0x02, 0x03};
    packet_ninja_set(&my_pkt, data, 3);
    packet_ninja_print(&my_pkt);
    uint8_t data2[] = {0x04, 0x05, 0x06};
    packet_ninja_set_bytes(&my_pkt, data2, 3);
    packet_ninja_print(&my_pkt);
    printf("Size of normal %ld, simple %ld ,ninja %ld\n", sizeof(struct packet_s),
           sizeof(struct packet_simple_s), sizeof(struct packet_ninja_s));

    byte_t x = {0xfe};
    printf("Content %02Xh, nibble low: %Xh, high: %Xh\n", x.content, x.nibble.low, x.nibble.high);
    if (x.content & (1 << 2)) {
        x.content = x.content & ~(1 << 2);  // set the x.content[2] = 0;
        x.content = x.content | (1 << 2);   // set the x.content[2] = 1;
        x.content = x.content ^ (1 << 2);   // toggle x.content[2]
        CLEAR_BIT(x.content, 2);
        SET_BIT(x.content, 2);
        TOGGLE_BIT(x.content, 2);
        GET_BIT(x.content, 2);
        x.bit2 = 0;
        x.bit2 = 1;
        x.bit2 = ~x.bit2;
    }
    return 0;
}