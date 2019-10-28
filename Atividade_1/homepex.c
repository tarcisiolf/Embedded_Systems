#include "homepex.h"
// Atividade 01 - Sistemas Embarcados 2019.2

int smart_house_device_init(device *home_d, char *user, char wifi, unsigned int content)
{
    
    return 0;
}

void house_init(my_house *house)
{
   
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

void smart_house_device_execute(device *home_d, my_house *house, char mode, command *cmd){
    
}

void smart_house_device_print_binary_content(unsigned int cmd){

}

void smart_house_device_monitor(my_house *house){
    /* Elabore aqui um printf que siga a representacao abaixo: */
    // ## MONITOR 
    // # (AMBIENTE): 
    // >> ILUMINÇÃO: (1 ou 0)
    // >> SOM AMBIENTE: (1 ou 0)
    // >> AR CONDICIONADO: (1 ou 0)
    // >> JANELAS: (1 ou 0)
    // >> PORTA: (1 ou 0)
    // >> TV: (1 ou 0)
    // ---------- * ----------
}

int main(int argc, char const *argv[])
{
    // Declare
    device home_d;
    my_house house;
    command cmd = {0};

    // Inicialize
    //smart_house_device_init(&home_d, "<seu_nome>", '1', cmd.content);
    //house_init(&house);

    // Verifique
    //smart_house_device_print(&home_d);
    //smart_house_device_monitor(&house);
    
    // Obs.: Lembre-se sempre verificar se o dispositivo esta conectado ao wi-fi antes de executar alguma acao
    // Obs.: Seu codigo voz eh 101, sempre verifique antes de executar um comando de voz

    /* EXECUTE:
    // Comando de voz
    /// (codigo de voz) : 101
    /// (comando) : 10100 == "ligar luzes da sala e abrir janela da cozinha"
    // smart_house_device_execute();
    // smart_house_device_monitor();
    */
 
    /* EXECUTE:
        // Comando de app
        // (ambiente) sala
        /// ligar luzes + som ambiente + abrir janelas + fechar porta
    // smart_house_device_execute();
    // smart_house_device_monitor();
    */
    
    /* EXECUTE:
    // Comando de voz
    /// (codigo de voz) : 110
    /// (comando) : 01011 == "ligar luz do banheiro e fechar a porta"
    // smart_house_device_execute();
    // smart_house_device_monitor();
    */

    /* EXECUTE:
        // Comando de app
        // (ambiente): quarto
        /// ligar luz +  ar condicionado + fechar janela + abrir porta
    // smart_house_device_execute();
    // smart_house_device_monitor();
    */

    /* EXECUTE:
    // Comando de voz
    /// (codigo de voz) : 101
    /// (comando) : 01011 == "ligar luz do banheiro e fechar a porta"
    // smart_house_device_execute();
    // smart_house_device_monitor();
    */

    return 0;
}
