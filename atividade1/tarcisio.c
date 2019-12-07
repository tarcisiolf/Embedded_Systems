#include "tarcisio.h"
// Atividade 01 - Sistemas Embarcados 2019.2

int smart_house_device_init(device *home_d, char *user, char wifi, unsigned int content)
{
    strcpy(home_d->user, user);
    home_d->connection_wifi = wifi;
    home_d->mode = content;
    return 0;
}

void house_init(my_house *house)
{
    int i = 0;
    for (i = 0; i < 6; i++)
    {
        house->room[i] = '0';
        house->bedroom[i] = '0';
        house->kitchen[i] = '0';
        house->bwc[i] = '0';
    }
}

void smart_house_device_print(device *home_d)
{
    printf("Username: %s\n", home_d->user);
    switch (home_d->connection_wifi){
    case '0':
        printf("device System is not Connected.\n");
        break;
    case '1':
        printf("device System is Connected!\n");
        break;
    default:
        printf("[ERROR] something is wrong =(.\n");
        break;
    }
}

void smart_house_device_execute(device *home_d, my_house *house, char mode, command *cmd)
{
    if (smart_house_device_isconnected(home_d))             // Verifica se wifi está conectado
    {
        if(mode == '0')                                     // 0 == Comando de Voz
        {
            if(cmd->voice_command.val == 5)                 // Verifica se é o dono, código de voz = 101b = 5
            {
                if(cmd->voice_command.interpret == 20)
                {
                    house->room[0] = '1';
                    house->kitchen[3] = '1'; 
                } 
                else if(cmd->voice_command.interpret == 11)
                {
                    house->bwc[0] = '1';
                    house->bwc[4] = '0'; 
                }      
            } 
            
            else
            {
                printf("* ----------- * NÃO É O DONO * ------------ *\n");
            }           
        }

        else if(mode == '1')                                // 1 == Comando vai app
        {
            switch (cmd->app_command.place_code)
            {
            case 0:                                                         // Sala
                house->room[0] = (cmd->app_command.lighting + 48);
                house->room[1] = (cmd->app_command.sound + 48);
                house->room[2] = (cmd->app_command.air_conditioning + 48);
                house->room[3] = (cmd->app_command.windows + 48);
                house->room[4] = (cmd->app_command.door + 48);
                house->room[5] = (cmd->app_command.tv + 48);
                break;
            
            case 1:                                                         // Cozinha
                house->kitchen[0] = (cmd->app_command.lighting + 48);
                house->kitchen[1] = (cmd->app_command.sound + 48);
                house->kitchen[2] = (cmd->app_command.air_conditioning + 48);
                house->kitchen[3] = (cmd->app_command.windows + 48);
                house->kitchen[4] = (cmd->app_command.door + 48);
                house->kitchen[5] = (cmd->app_command.tv + 48);
                break;

            case 2:                                                         // Quarto
                house->bedroom[0] = (cmd->app_command.lighting + 48);
                house->bedroom[1] = (cmd->app_command.sound + 48);
                house->bedroom[2] = (cmd->app_command.air_conditioning + 48);
                house->bedroom[3] = (cmd->app_command.windows + 48);
                house->bedroom[4] = (cmd->app_command.door + 48);
                house->bedroom[5] = (cmd->app_command.tv + 48);
                break;

            case 3:                                                         // BWC
                house->bwc[0] = (cmd->app_command.lighting + 48);
                house->bwc[1] = (cmd->app_command.sound + 48);
                house->bwc[2] = (cmd->app_command.air_conditioning + 48);
                house->bwc[3] = (cmd->app_command.windows + 48);
                house->bwc[4] = (cmd->app_command.door + 48);
                house->bwc[5] = (cmd->app_command.tv + 48);
                break;
            
            default:
                break;
            }
        }
    }
    
}

void smart_house_device_print_binary_content(unsigned int cmd)
{
    printf("Content of ")
}

void smart_house_device_monitor(my_house *house)
{
    printf("## MONITOR\n");
    printf("# QUARTO\n");
    printf(">> ILUMINAÇÃO:      [%c]\n", house->bedroom[0]);
    printf(">> SOM AMBIENTE:    [%c]\n", house->bedroom[1]);
    printf(">> AR CONDICIONADO: [%c]\n", house->bedroom[2]);
    printf(">> JANELAS:         [%c]\n", house->bedroom[3]);
    printf(">> PORTA:           [%c]\n", house->bedroom[4]);
    printf(">> TV:              [%c]\n", house->bedroom[5]);

    printf("* ------------------ * ------------------ *\n");
    printf("# SALA\n");
    printf(">> ILUMINAÇÃO:      [%c]\n", house->room[0]);
    printf(">> SOM AMBIENTE:    [%c]\n", house->room[1]);
    printf(">> AR CONDICIONADO: [%c]\n", house->room[2]);
    printf(">> JANELAS:         [%c]\n", house->room[3]);
    printf(">> PORTA:           [%c]\n", house->room[4]);
    printf(">> TV:              [%c]\n", house->room[5]);

    printf("* ------------------ * ------------------ *\n");
    printf("# BANHEIRO\n");
    printf(">> ILUMINAÇÃO:      [%c]\n", house->bwc[0]);
    printf(">> SOM AMBIENTE:    [%c]\n", house->bwc[1]);
    printf(">> AR CONDICIONADO: [%c]\n", house->bwc[2]);
    printf(">> JANELAS:         [%c]\n", house->bwc[3]);
    printf(">> PORTA:           [%c]\n", house->bwc[4]);
    printf(">> TV:              [%c]\n", house->bwc[5]);

    printf("* ------------------ * ------------------ *\n");
    printf("# COZINHA\n");
    printf(">> ILUMINAÇÃO:      [%c]\n", house->kitchen[0]);
    printf(">> SOM AMBIENTE:    [%c]\n", house->kitchen[1]);
    printf(">> AR CONDICIONADO: [%c]\n", house->kitchen[2]);
    printf(">> JANELAS:         [%c]\n", house->kitchen[3]);
    printf(">> PORTA:           [%c]\n", house->kitchen[4]);
    printf(">> TV:              [%c]\n", house->kitchen[5]);
    printf("* ------------------ * ------------------ *\n");
}

int smart_house_device_isconnected(device *home_d)
{
    if(home_d->connection_wifi == '0')
    {
        printf("* -------- * Wifi não conectado * -------- *\n");
    }   
    else if(home_d->connection_wifi == '1')
    {
        printf("* ----------- * Wifi conectado * ---------- *\n");
        return 1;
    }
     
    return 0;
}


int main(int argc, char const *argv[])
{
    // Declare
    device home_d;
    my_house house;
    command cmd = {0};

    // Inicialize
    smart_house_device_init(&home_d, "tlf", '1', cmd.content);
    house_init(&house);

    // Verifique
    smart_house_device_print(&home_d);
    smart_house_device_monitor(&house);
    printf("\n\n");
    
    // Obs.: Lembre-se sempre verificar se o dispositivo esta conectado ao wi-fi antes de executar alguma acao
    // Obs.: Seu codigo voz eh 101, sempre verifique antes de executar um comando de voz


    /* EXECUTE:
    // Comando de voz
    /// (codigo de voz) : 101
    /// (comando) : 10100 == "ligar luzes da sala e abrir janela da cozinha"
    */

   cmd.voice_command.val = 5; //        5 = 101, em binário 
   cmd.voice_command.interpret = 20; // 20 = 10100, em binário

   smart_house_device_execute(&home_d, &house, '0', &cmd); // 0 representa comando de voz
   smart_house_device_monitor(&house);
   printf("\n\n");
 
    /* EXECUTE:
        // Comando de app
        // (ambiente) sala
        /// ligar luzes + som ambiente + abrir janelas + fechar porta
    */

    cmd.app_command.place_code = 0;
    cmd.app_command.lighting = 1;
    cmd.app_command.sound = 1;
    cmd.app_command.air_conditioning = 0;
    cmd.app_command.windows = 1;
    cmd.app_command.door = 0;
    cmd.app_command.tv = 0;

    smart_house_device_execute(&home_d, &house, '1', &cmd); // 1 representa comando via app
    smart_house_device_monitor(&house);
    printf("\n\n");

    /* EXECUTE:
    // Comando de voz
    /// (codigo de voz) : 110
    /// (comando) : 01011 == "ligar luz do banheiro e fechar a porta"
    */

    cmd.voice_command.val = 6; //        5 = 101, em binário 
    cmd.voice_command.interpret = 11; // 11 = 01011, em binário

   smart_house_device_execute(&home_d, &house, '0', &cmd); // 0 representa comando de voz
   smart_house_device_monitor(&house);
   printf("\n\n");


    /* EXECUTE:
        // Comando de app
        // (ambiente): quarto
        /// ligar luz +  ar condicionado + fechar janela + abrir porta
    */

    cmd.app_command.place_code = 2;
    cmd.app_command.lighting = 1;
    cmd.app_command.sound = 0;
    cmd.app_command.air_conditioning = 1;
    cmd.app_command.windows = 0;
    cmd.app_command.door = 1;
    cmd.app_command.tv = 0;

    smart_house_device_execute(&home_d, &house, '1', &cmd); // 1 representa comando via app
    smart_house_device_monitor(&house);
    printf("\n\n");

    /* EXECUTE:
    // Comando de voz
    /// (codigo de voz) : 101
    /// (comando) : 01011 == "ligar luz do banheiro e fechar a porta"
    */

    cmd.voice_command.val = 5;        // 5 = 101, em binário 
    cmd.voice_command.interpret = 11; // 11 = 01011, em binário

    smart_house_device_execute(&home_d, &house, '0', &cmd); // 0 representa comando de voz
    smart_house_device_monitor(&house);
    printf("\n\n");

    return 0;
}
