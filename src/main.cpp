#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

const float FPS = 100;

const int SCREEN_W = 960;
const int SCREEN_H = 540;

int main()
{
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;

    // Inicializar o Allegro
    if (!al_init())
    {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return -1;
    }
    // cria a tela (dimensoes de SCREEN_W, SCREEN_H pixels)
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    // cria fila de eventos
    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        fprintf(stderr, "falha ao criar a fila de eventos!\n");
        al_destroy_display(display);
        return -1;
    }
    //instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

    // registra na fila os eventos de tela
    al_register_event_source(event_queue, al_get_display_event_source(display));
    //registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source()); 


    bool playing = true;
    while (playing)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0)); // limpa a tela com a cor preta
        // atualiza a tela quando tem algo pra mostrar
        al_flip_display();

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

        //se o tipo de evento for o fechamento da tela (clique no x da janela)
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			playing = 0;
		}
        //se o tipo de evento for um clique de mouse
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			std::cout << "\nmouse clicado em: " << ev.mouse.x << ", " << ev.mouse.y;
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			//imprime qual tecla foi
			std::cout << "\ncodigo tecla: " << ev.keyboard.keycode;
		}


    }

    // limpa a tela
    al_clear_to_color(al_map_rgb(0, 0, 0)); // limpa a tela com a cor preta
    // atualiza a tela quando tem algo pra mostrar
    al_flip_display();
    al_rest(5);

    //procedimento de fim de jogo (limpar tela, liberar memória, etc)
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


    return 0;
}
