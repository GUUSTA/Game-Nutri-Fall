// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>

// Atributos da tela
const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;

int main(void)
{
    // A nossa variável janela
    ALLEGRO_DISPLAY *janela_inicial = NULL;

    // As nossas variáveis para imagens que irão aparecer
    ALLEGRO_BITMAP *imagem_inicial = NULL;
    ALLEGRO_BITMAP *imagem_opcoes = NULL;

    ALLEGRO_BITMAP *imagem_on_Melodia = NULL;
    ALLEGRO_BITMAP *imagem_off_Melodia = NULL;

    ALLEGRO_BITMAP *imagem_on_SFX = NULL;
    ALLEGRO_BITMAP *imagem_off_SFX = NULL;

    //Fila de eventos, ela vai receber as ações do "usuário/programa".
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    // O nosso arquivo de fonte
    ALLEGRO_FONT *fonte28 = NULL;

    // Variáveis auxiliares.
    bool sair = false;
    //bool sound_Melodia = true;
    //bool sound_SFX = true;
    int tecla = 0;
    int selecionar = 0;

    // Inicialização da biblioteca Allegro
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    // Inicialização do add-on para uso de fontes
    al_init_font_addon();
    al_init_ttf_addon();

    // Inicialização do add-on para uso de fontes True Type(Fontes do instaladas no PC).
    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return -1;
    }

    // Cria nosso Display, e verifica se está tudo certo.
    janela_inicial = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela_inicial)
    {
        fprintf(stderr, "Falha ao criar janela_inicial.\n");
        return -1;
    }

    // Inicializa o teclado para uso.
    if (!al_install_keyboard())
    {
        al_destroy_display(janela_inicial);
        fprintf(stderr, "Falha ao inicializar Teclado.\n");
        return -1;
    }

    // Carrega nosso background, e verifica se está tudo certo.
    imagem_inicial = al_load_bitmap("Tela-inicial.png");
    if (!imagem_inicial)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_inicial.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    imagem_opcoes = al_load_bitmap("Tela-Opcoes-2.0.png");
    if (!imagem_opcoes)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_opcoes.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    imagem_on_Melodia = al_load_bitmap("melodia-on.png");
    if (!imagem_on_Melodia)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_on_Melodia.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    imagem_off_Melodia = al_load_bitmap("melodia-off.png");
    if (!imagem_off_Melodia)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_off_Melodia.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    imagem_on_SFX = al_load_bitmap("sfx-on.png");
    if (!imagem_on_SFX)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_on_SFX.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    imagem_off_SFX = al_load_bitmap("sfx-off.png");
    if (!imagem_off_SFX)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_off_SFX.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    // Carregando o arquivo de fonte.
    fonte28 = al_load_font("old_stamper.ttf", 28, 0);
    if (!fonte28)
    {
        al_destroy_display(janela_inicial);
        fprintf(stderr, "Falha ao carregar fonte28.\n");
        return -1;
    }

    // Cria nossa fila de eventos, e verifica se está tudo certo.
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela_inicial);
        return -1;
    }

    // Comandos para dizer a "fila de eventos" registrar ações do Display e Teclado.
    al_register_event_source(fila_eventos, al_get_display_event_source(janela_inicial));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    // Cria nosso background.
    al_draw_bitmap(imagem_inicial, 0, 0, 0);

    // Cria nossos textos "Pressione Enter", e posiciona ambos.
    al_draw_textf(fonte28, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 605, ALLEGRO_ALIGN_CENTRE, "Pressione");
    al_draw_textf(fonte28, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 635, ALLEGRO_ALIGN_CENTRE, "Enter");

    // Cria um Loop, onde ele só irá parar se clicar-mos no X(FECHAR JANELA).
    while (!sair)
    {
        // Verificamos se há eventos na fila
        while(!al_is_event_queue_empty(fila_eventos))
        {
            // Comando de espera de ações da fila de eventos.
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            // Cria nosso background.
            al_draw_bitmap(imagem_inicial, 0, 0, 0);
            // Cria nossos textos "Pressione Enter", e posiciona ambos.
            al_draw_textf(fonte28, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 605, ALLEGRO_ALIGN_CENTRE, "Pressione");
            al_draw_textf(fonte28, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 635, ALLEGRO_ALIGN_CENTRE, "Enter");
            // OBS: Criei ambos novamente para não bugar.

            //Condição para que, se o tipo de evento for pressionar uma tecla, e se essa tecla for ENTER, tecla = 0 recebe 2.
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                case ALLEGRO_KEY_ENTER:
                    tecla = 2;
                    break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true; //Sendo "TRUE" a janela será fechada.
            }
        }

        // Concluíndo que o usuário apertou "ENTER", a criação da tela de opções será realizada.
        if(tecla == 2)
        {
            al_draw_bitmap(imagem_opcoes, 0, 0, 0);

            while (!al_is_event_queue_empty(fila_eventos))
            {
                // Comando de espera de ações da fila de eventos.
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);


                al_draw_bitmap(imagem_on_Melodia, 0, 0, 0);
                al_draw_bitmap(imagem_on_SFX, 0, 0, 0);

                if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    //verifica qual tecla foi pressionada
                    switch(evento.keyboard.keycode)
                    {
                    //seta para cima
                        case ALLEGRO_KEY_UP:
                            selecionar = 1;
                            break;
                    //seta para baixo
                        case ALLEGRO_KEY_DOWN:
                            selecionar = 2;
                            break;
                    //seta para esquerda
                        case ALLEGRO_KEY_LEFT:
                            selecionar = 3;
                            break;
                    //seta para direita.
                        case ALLEGRO_KEY_RIGHT:
                            selecionar = 4;
                            break;
                    }
                }
                else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    sair = true; //Sendo "TRUE" a janela será fechada.
                }
            }
        }


        // Atualiza a tela
        al_flip_display();

    }

    // Desalocação da Memória
    al_destroy_font(fonte28);

    al_destroy_display(janela_inicial);

    al_destroy_event_queue(fila_eventos);

    al_destroy_bitmap(imagem_inicial);
    al_destroy_bitmap(imagem_opcoes);
    al_destroy_bitmap(imagem_on_Melodia);
    al_destroy_bitmap(imagem_off_Melodia);
    al_destroy_bitmap(imagem_on_SFX);
    al_destroy_bitmap(imagem_off_SFX);

    return 0;
}
