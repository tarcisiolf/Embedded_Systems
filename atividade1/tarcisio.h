#include <stdint.h>
#include <stdio.h>
#include <string.h>

union controller {
    unsigned int content; // Conteudo do comando em 9 bits
    struct {
        unsigned int val : 3; // Voice validation
        unsigned int interpret : 5; // Command interpretation
    }voice_command;
    struct {
        unsigned int place_code : 2; // 00 : Sala, 01 : Cozinha, 10 : Quarto, 11 : Bwc
        unsigned int lighting : 1; // Lighting
        unsigned int sound : 1; // Ambient sound
        unsigned int air_conditioning : 1; // Air conditioning
        unsigned int windows : 1; // Open Windows
        unsigned int door : 1; // Open the door
        unsigned int tv : 1; // Tv
        // 0 : Turn off
        // 1 : Turn on 
    }app_command;
};
typedef union controller command;

struct smart_house_device {
    char user[50];  // Username
    char connection_wifi; // '0' - Not connected, '1' - Connected
    char mode; // '0' - Voice, '1' - App
    command current_command; 
};
typedef struct smart_house_device device;

struct house{
    // '0' : Turn off
    // '1' : Turn on 
    // Cada posicao dos vetores representacao respectivamente iluminacao,
    // som ambiente, ar condicionado, janelas, porta e tv.
    char room[6];
    char bwc[6];
    char bedroom[6];
    char kitchen[6];
};
typedef struct house my_house;

int smart_house_device_init(device *home_d, char *user, char wifi, unsigned content); // Inicializar sistema

int smart_house_device_isconnected(device *home_d); // Verficar se esta conectado

void smart_house_device_execute(device *home_d, my_house *house, char mode, command *cmd); // Executar um comando

void smart_house_device_monitor(my_house *house); // Monitorar o sistema

void smart_house_device_print_binary_content(unsigned int cmd); // Verificar o bits do comando

void smart_house_device_print(device *home_d); // Imprimir status do sistema (nome do usuario e conexão)

// [DICA] é permitido a criação de outras funcoes auxiliares para execucao dessas acima, isso talvez facilite
// e deixe mais organizado o seu codigo.
