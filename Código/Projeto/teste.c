/*===============================
  == Os arquivos de cabeçalho  ==
=================================*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdbool.h>

/*===============================
====== Variáveis Globais ========
=================================*/
// Atributos da tela
const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;

// Taxa de Frames utilizada
int FRAMES_POR_SEGUNDO = 60;

// A nossa variável janela
ALLEGRO_DISPLAY *janela_inicial = NULL;

// As nossas variáveis para imagens que irão aparecer
ALLEGRO_BITMAP *imagem_inicial = NULL;
ALLEGRO_BITMAP *imagem_opcoes = NULL;
ALLEGRO_BITMAP *imagem_on_Melodia = NULL;
ALLEGRO_BITMAP *imagem_off_Melodia = NULL;
ALLEGRO_BITMAP *imagem_on_SFX = NULL;
ALLEGRO_BITMAP *imagem_off_SFX = NULL;
ALLEGRO_BITMAP *imagem_Iniciante = NULL;
ALLEGRO_BITMAP *imagem_Normal = NULL;
ALLEGRO_BITMAP *imagem_Desafiante = NULL;
ALLEGRO_BITMAP *imagem_Plataforma_top_down = NULL;
ALLEGRO_BITMAP *imagem_Plataforma_top_right = NULL;
ALLEGRO_BITMAP *imagem_Plataforma_top_left = NULL;
ALLEGRO_BITMAP *imagem_Plataforma_down_down = NULL;
ALLEGRO_BITMAP *imagem_Plataforma_down_right = NULL;
ALLEGRO_BITMAP *imagem_Plataforma_down_left = NULL;
ALLEGRO_BITMAP *imagem_Iniciar_Jogo_Branco = NULL;
ALLEGRO_BITMAP *imagem_Iniciar_Jogo_Vermelho = NULL;

ALLEGRO_BITMAP *imagem_Fruta_Manga = NULL;

ALLEGRO_BITMAP *imagem_Tela_Fase_1 = NULL;

ALLEGRO_BITMAP *imagem_como_jogar = NULL;


//Fila de eventos, ela vai receber as ações do "usuário/programa".
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

// O nosso arquivo de fonte
ALLEGRO_FONT *fonte28 = NULL;

// Musica de fundo
ALLEGRO_AUDIO_STREAM *musica_journey = NULL;
ALLEGRO_AUDIO_STREAM *musica_megaman = NULL;



// Variáveis auxiliares.
bool sair = false;
bool sound_Melodia = true;
bool sound_SFX = true;
bool iniciante = true;
bool normal = false;
bool desafiante = false;
bool Iniciar_Jogo = false;
bool Iniciar_Jogo_Vermelho = false;
bool limitado = true;

int tecla = 0;
int top = 1;
int down = 2;
int frame = 0;
int i = 0;
int dificuldade = 0;
double velocidade = 0.0;
int fruta = 0;

//Double utilizada para o cálculo do tempo de atualização da tela
double tempoInicial = 0;

//Prototipando as funções
bool inicicializar_comandos();
bool inicicializar_imagens();
void inicializar_registradores_da_fila_de_eventos();
void inicializar_destroy_all();
void iniciarTimer();
double obterTempoTimer();

/*=====================
==== Início do Jogo ===
=======================*/
int main(void)
{
    float x = 585;
    float y = -100;
    int dir_x = 0;
    int dir_y = 1;
    float raio = 50.0;
    float tam_fruta = 2*raio;

    inicicializar_comandos();
    inicicializar_imagens();
    inicializar_registradores_da_fila_de_eventos();

    /*=====================
    ===== Tela Inicial ====
    =======================*/

    // Cria nosso background.
    al_draw_bitmap(imagem_inicial, 0, 0, 0);

    // Cria nossos textos "Pressione Enter", e posiciona ambos.
    al_draw_textf(fonte28, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 605, ALLEGRO_ALIGN_CENTRE, "Pressione");
    al_draw_textf(fonte28, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 635, ALLEGRO_ALIGN_CENTRE, "Enter");

    // Cria um Loop, onde ele só irá parar se clicar-mos no X(FECHAR JANELA).
    while (!sair)
    {
        iniciarTimer();

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
                    tecla = 1;
                    break;
                }
                if(tecla == 2)
                {
                    switch(evento.keyboard.keycode)
                    {
                        //seta para esquerda
                        case ALLEGRO_KEY_LEFT:
                            top = 1;
                            break;
                        //seta para direita.
                        case ALLEGRO_KEY_RIGHT:
                            top = 2;
                            break;
                        //Tecla A
                        case ALLEGRO_KEY_A:
                            down = 1;
                            break;
                        //Tecla D
                        case ALLEGRO_KEY_D:
                            down = 2;
                            break;
                    }
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true; //Sendo "TRUE" a janela/jogo será fechada.
            }

            /*=====================
            === Tela de Ajustes ===
            =======================*/

            // Concluíndo que o usuário apertou "ENTER", a criação da tela de opções será realizada.
            if(tecla == 1)
            {
                al_draw_bitmap(imagem_opcoes, 0, 0, 0);

                //Verifica oq está acontecendo com os botões Melodia e Efeitos Sonoros.
                if(sound_Melodia == true)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            sound_Melodia = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 655 &&
                            evento.mouse.x <= 916 &&
                            evento.mouse.y >= 277 &&
                            evento.mouse.y <= 319)
                        {
                            sound_Melodia = false;
                        }
                    }
                }

                else if(sound_Melodia == false)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            sound_Melodia = false;
                        }
                    }
                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 655 &&
                            evento.mouse.x <= 960 &&
                            evento.mouse.y >= 277 &&
                            evento.mouse.y <= 319)
                        {
                            sound_Melodia = true;
                        }
                    }
                }

                if(sound_SFX == true)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            sound_SFX = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 655 &&
                            evento.mouse.x <= 916 &&
                            evento.mouse.y >= 338 &&
                            evento.mouse.y <= 380)
                        {
                            sound_SFX = false;
                        }
                    }
                }

                else if(sound_SFX == false)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            sound_SFX = false;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 655 &&
                            evento.mouse.x <= 960 &&
                            evento.mouse.y >= 338 &&
                            evento.mouse.y <= 380)
                        {
                            sound_SFX = true;
                        }
                    }
                }

                //DIFICULDADE DO JOGO
                if(iniciante == true)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES|| ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            iniciante = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 535 &&
                            evento.mouse.x <= 750 &&
                            evento.mouse.y >= 487 &&
                            evento.mouse.y <= 529)
                        {
                            iniciante = false;
                            normal = true;
                        }
                    }
                }

                else if(normal == true)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES|| ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            normal = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 554 &&
                            evento.mouse.x <= 728 &&
                            evento.mouse.y >= 487 &&
                            evento.mouse.y <= 529)
                        {
                            normal = false;
                            desafiante = true;
                        }
                    }
                }

                else if(desafiante == true)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            desafiante = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 510 &&
                            evento.mouse.x <= 767 &&
                            evento.mouse.y >= 487 &&
                            evento.mouse.y <= 529)
                        {
                            iniciante = true;
                            desafiante = false;
                        }
                    }
                }

                if(Iniciar_Jogo == false)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            Iniciar_Jogo = false;
                            Iniciar_Jogo_Vermelho = false;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 599 &&
                            evento.mouse.x <= 680 &&
                            evento.mouse.y >= 558 &&
                            evento.mouse.y <= 604)
                        {
                            Iniciar_Jogo = false;
                            Iniciar_Jogo_Vermelho = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 599 &&
                            evento.mouse.x <= 680 &&
                            evento.mouse.y >= 558 &&
                            evento.mouse.y <= 604)
                        {
                            Iniciar_Jogo = true;
                        }
                    }
                }
                //Aplica oq foi captado pelo  vereficador do mouse acima.

                //Música e Efeitos Sonoros
                if(sound_Melodia == true)
                {
                    al_draw_bitmap(imagem_on_Melodia , 0, 0, 0);
                    al_set_audio_stream_playing(musica_journey, true);
                }
                else
                    if(sound_Melodia == false)
                    {
                        al_draw_bitmap(imagem_off_Melodia , 0, 0, 0);
                        al_set_audio_stream_playing(musica_journey, false);
                    }

                if(sound_SFX == true)
                {
                    al_draw_bitmap(imagem_on_SFX , 0, 0, 0);
                }
                else
                    if(sound_SFX == false)
                    {
                        al_draw_bitmap(imagem_off_SFX , 0, 0, 0);
                    }

                //Deficuldades
                if(iniciante == true)
                {
                    al_draw_bitmap(imagem_Iniciante , 0, 0, 0);
                    dificuldade = 1;
                }
                else if(normal == true)
                {
                    al_draw_bitmap(imagem_Normal , 0, 0, 0);
                    dificuldade = 2;
                }
                else if(desafiante == true)
                {
                    al_draw_bitmap(imagem_Desafiante , 0, 0, 0);
                    dificuldade = 3;
                }

                if(Iniciar_Jogo_Vermelho == true)
                {
                    al_draw_bitmap(imagem_Iniciar_Jogo_Vermelho , 0, 0, 0);
                }
                else if(Iniciar_Jogo_Vermelho == false)
                {
                    al_draw_bitmap(imagem_Iniciar_Jogo_Branco , 0, 0, 0);
                }
                if(Iniciar_Jogo == true)
                {
                    tecla = 2;
                }
            }
        }

        /*=================
        === Tela Fase 1 ===
        ===================*/
        if(tecla == 2)
        {
            if(dificuldade == 1)
            {
                al_draw_bitmap(imagem_Tela_Fase_1 , 0, 0, 0);
                al_set_audio_stream_playing(musica_journey, false);
                al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                al_set_audio_stream_playing(musica_megaman, true);


                switch (fruta)
                {
                    case 0:

                    al_draw_bitmap(imagem_Fruta_Manga, x, y, 0);
                    al_flip_display();


                    velocidade = 2.0;
                    y += velocidade * dir_y;
                    x += velocidade * dir_x;

                    if(y < 230 + tam_fruta)
                    {
                        dir_x = 0;
                        dir_y = 1;
                    }
                    else if(y > 230 + tam_fruta)
                    {
                        dir_y = 0;
                        if(top == 1)
                        {
                            dir_x = -1;
                        }
                        else if(top == 2)
                        {
                            dir_x = 1;
                        }
                        else if(top == 0)
                        {
                            dir_x = 0;
                        }
                    }
                    if(x > 1280 || x < 0)
                    {
                        fruta++;
                        x = 585;
                        y = -100;
                        dir_x = 0;
                        dir_y = 1;
                        velocidade = 0.0;
                    }

                    case 1:

                    al_draw_bitmap(imagem_Fruta_Manga, x, y, 0);
                    al_flip_display();

                    velocidade = 2.0;
                    y += velocidade * dir_y;
                    x += velocidade * dir_x;

                    if(y < 230 + tam_fruta)
                    {
                        dir_x = 0;
                        dir_y = 1;
                    }
                    else if(y > 230 + tam_fruta)
                    {
                        dir_y = 0;
                        if(top == 1)
                        {
                            dir_x = -1;
                        }
                        else if(top == 2)
                        {
                            dir_x = 1;
                        }
                        else if(top == 0)
                        {
                            dir_x = 0;
                        }
                    }
                    if(x > 1280 || x < 0)
                    {
                        fruta++;
                        x = 585;
                        y = -100;
                        dir_x = 0;
                        dir_y = 1;
                        velocidade = 0.0;
                    }

                    case 2:

                    al_draw_bitmap(imagem_Fruta_Manga, x, y, 0);
                    al_flip_display();

                    velocidade = 2.0;
                    y += velocidade * dir_y;
                    x += velocidade * dir_x;

                    if(y < 230 + tam_fruta)
                    {
                        dir_x = 0;
                        dir_y = 1;
                    }
                    else if(y > 230 + tam_fruta)
                    {
                        dir_y = 0;
                        if(top == 1)
                        {
                            dir_x = -1;
                        }
                        else if(top == 2)
                        {
                            dir_x = 1;
                        }
                        else if(top == 0)
                        {
                            dir_x = 0;
                        }
                    }
                    if(x > 1280 || x < 0)
                    {
                        fruta++;
                        x = 585;
                        y = -100;
                        dir_x = 0;
                        dir_y = 1;
                        velocidade = 0.0;
                    }

                    case 3:

                    al_draw_bitmap(imagem_Fruta_Manga, x, y, 0);
                    al_flip_display();

                    velocidade = 2.0;
                    y += velocidade * dir_y;
                    x += velocidade * dir_x;

                    if(y < 230 + tam_fruta)
                    {
                        dir_x = 0;
                        dir_y = 1;
                    }
                    else if(y > 230 + tam_fruta)
                    {
                        dir_y = 0;
                        if(top == 1)
                        {
                            dir_x = -1;
                        }
                        else if(top == 2)
                        {
                            dir_x = 1;
                        }
                        else if(top == 0)
                        {
                            dir_x = 0;
                        }
                    }
                    if(x > 1280 || x < 0)
                    {
                        fruta++;
                        x = 585;
                        y = -100;
                        dir_x = 0;
                        dir_y = 1;
                        velocidade = 0.0;
                    }
                }

            }

            else if(dificuldade == 2)
            {
                al_draw_bitmap(imagem_Tela_Fase_1 , 0, 0, 0);
                al_set_audio_stream_playing(musica_journey, false);
                al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                al_set_audio_stream_playing(musica_megaman, true);
                //al_draw_bitmap(imagem_Plataforma_down_down, 0, 0, 0);
                //al_draw_bitmap(imagem_Plataforma_top_down, 0, 0, 0);
                al_draw_bitmap(imagem_Fruta_Manga, x, y, 0);
                al_flip_display();


                velocidade = 4.0;
                y += velocidade * dir_y;
                x += velocidade * dir_x;

                if(y < 230 + tam_fruta)
                {
                    dir_x = 0;
                    dir_y = 1;
                }
                else if(y > 230 + tam_fruta)
                {
                    dir_y = 0;
                    if(top == 1)
                    {
                        dir_x = -1;
                    }
                    else if(top == 2)
                    {
                        dir_x = 1;
                    }
                    else if(top == 0)
                    {
                        dir_x = 0;
                    }
                }
            }
            else if(dificuldade == 3)
            {
                al_draw_bitmap(imagem_Tela_Fase_1 , 0, 0, 0);
                al_set_audio_stream_playing(musica_journey, false);
                al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                al_set_audio_stream_playing(musica_megaman, true);
                //al_draw_bitmap(imagem_Plataforma_down_down, 0, 0, 0);
                //al_draw_bitmap(imagem_Plataforma_top_down, 0, 0, 0);
                al_draw_bitmap(imagem_Fruta_Manga, x, y, 0);
                al_flip_display();


                velocidade = 6.0;
                y += velocidade * dir_y;
                x += velocidade * dir_x;

                if(y < 230 + tam_fruta)
                {
                    dir_x = 0;
                    dir_y = 1;
                }
                else if(y > 230 + tam_fruta)
                {
                    dir_y = 0;
                    if(top == 1)
                    {
                        dir_x = -1;
                    }
                    else if(top == 2)
                    {
                        dir_x = 1;
                    }
                    else if(top == 0)
                    {
                        dir_x = 0;
                    }
                }
            }
        }
        frame++;

        if (limitado && (obterTempoTimer() < 1.0 / FRAMES_POR_SEGUNDO))
        {
            al_rest((1.0 / FRAMES_POR_SEGUNDO) - obterTempoTimer());
        }

        // Atualiza a tela
        al_flip_display();
    }

    inicializar_destroy_all();

    return 0;
}

/*===============================
==== Inicizalização/Instalação ==
====== de alguns comandos =======
=================================*/
bool inicicializar_comandos()
{
    // Inicialização da biblioteca Allegro
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        inicializar_destroy_all();
        return false;
    }

    // Inicialização do add-on para uso de fontes
    al_init_font_addon();
    al_init_ttf_addon();

    // Inicialização do add-on para uso de fontes True Type(Fontes do instaladas no PC).
    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        inicializar_destroy_all();
        return false;
    }

    // Cria nosso Display, e verifica se está tudo certo.
    janela_inicial = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela_inicial)
    {
        fprintf(stderr, "Falha ao criar janela_inicial.\n");
        inicializar_destroy_all();
        return false;
    }

    // Configura o título da janela
    al_set_window_title(janela_inicial, "Nutri Fall");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        inicializar_destroy_all();
        return false;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela_inicial, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        inicializar_destroy_all();
        return false;
    }

    // Inicializa o teclado para uso.
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar Teclado.\n");
        inicializar_destroy_all();
        return false;
    }

    // Carregando o arquivo de fonte.
    fonte28 = al_load_font("old_stamper.ttf", 28, 0);
    if (!fonte28)
    {
        fprintf(stderr, "Falha ao carregar fonte28.\n");
        inicializar_destroy_all();
        return false;
    }

    if (!al_install_audio())
    {
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        inicializar_destroy_all();
        return false;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        inicializar_destroy_all();
        return false;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        inicializar_destroy_all();
        return false;
    }

    musica_journey = al_load_audio_stream("musica Journey.ogg", 4, 1024);
    if (!musica_journey)
    {
        fprintf(stderr, "Falha ao carregar audio -  musica Journey.ogg.\n");
        inicializar_destroy_all();
        return false;
    }

    musica_megaman = al_load_audio_stream("musica Megaman.ogg", 4, 1024);
    if (!musica_megaman)
    {
        fprintf(stderr, "Falha ao carregar audio -  musica Megaman.ogg.ogg.\n");
        inicializar_destroy_all();
        return false;
    }

    // Cria nossa fila de eventos, e verifica se está tudo certo.
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        inicializar_destroy_all();
        return false;
    }
}

/*===============================
==== Inicialização de Imagens ===
=================================*/
bool inicicializar_imagens()
{
    // Carrega nosso background, e verifica se está tudo certo.
    imagem_inicial = al_load_bitmap("Tela-inicial.png");
    if (!imagem_inicial)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_inicial.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_opcoes = al_load_bitmap("Tela_Opcoes3.0.png");
    if (!imagem_opcoes)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_opcoes.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_on_Melodia = al_load_bitmap("melodia-on.png");
    if (!imagem_on_Melodia)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_on_Melodia.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_off_Melodia = al_load_bitmap("melodia-off.png");
    if (!imagem_off_Melodia)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_off_Melodia.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_on_SFX = al_load_bitmap("sfx-on.png");
    if (!imagem_on_SFX)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_on_SFX.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_off_SFX = al_load_bitmap("sfx-off.png");
    if (!imagem_off_SFX)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_off_SFX.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Iniciante = al_load_bitmap("Dificuldade_Iniciante.png");
    if (!imagem_Iniciante)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Iniciante.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Normal = al_load_bitmap("Dificuldade_Normal.png");
    if (!imagem_Normal)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Normal.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Desafiante = al_load_bitmap("Dificuldade_Desafiante.png");
    if (!imagem_Desafiante)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Desafiante\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Plataforma_down_down = al_load_bitmap("Plataforma_down_down.png");
    if (!imagem_Plataforma_down_down)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Plataforma_down_down\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Plataforma_down_left = al_load_bitmap("Plataforma_down_left.png");
    if (!imagem_Plataforma_down_left)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Plataforma_down_left\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Plataforma_down_right = al_load_bitmap("Plataforma_down_right.png");
    if (!imagem_Plataforma_down_right)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Plataforma_down_right\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Plataforma_top_down = al_load_bitmap("Plataforma_top_down.png");
    if (!imagem_Plataforma_top_down)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Plataforma_top_down\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Plataforma_top_left = al_load_bitmap("Plataforma_top_left.png");
    if (!imagem_Plataforma_top_left)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Plataforma_top_left\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Plataforma_top_right = al_load_bitmap("Plataforma_top_right.png");
    if (!imagem_Plataforma_top_right)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Plataforma_top_right\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Iniciar_Jogo_Branco = al_load_bitmap("Iniciar_Jogo_Branco.png");
    if (!imagem_Iniciar_Jogo_Branco)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Iniciar_Jogo_Branco\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Iniciar_Jogo_Vermelho = al_load_bitmap("Iniciar_Jogo_Vermelho.png");
    if (!imagem_Iniciar_Jogo_Vermelho)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Iniciar_Jogo_Vermelho\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Fruta_Manga = al_load_bitmap("Manga2.png");
    if (!imagem_Fruta_Manga)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Fruta_Manga\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Tela_Fase_1 = al_load_bitmap("Tela_Fase_1.png");
    if (!imagem_Tela_Fase_1)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Tela_Fase_1\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_como_jogar = al_load_bitmap("como_jogar.png");
    if (!imagem_como_jogar)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_como_jogar\n");
        inicializar_destroy_all();
        return false;
    }
}

/*=====================================
==== Inicialização de Registradores ===
========= da fila de eventos ==========
=======================================*/
void inicializar_registradores_da_fila_de_eventos()
{
    al_attach_audio_stream_to_mixer(musica_journey, al_get_default_mixer());
    al_set_audio_stream_playing(musica_journey, true);

    // Comandos para dizer a "fila de eventos" registrar ações do Display e Teclado.
    al_register_event_source(fila_eventos, al_get_display_event_source(janela_inicial));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
}

/*==============================
==== Desalocação da Memória ====
================================*/

void inicializar_destroy_all()
{
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
    al_destroy_bitmap(imagem_Iniciante);
    al_destroy_bitmap(imagem_Normal);
    al_destroy_bitmap(imagem_Desafiante);
    al_destroy_bitmap(imagem_Plataforma_down_down);
    al_destroy_bitmap(imagem_Plataforma_down_left);
    al_destroy_bitmap(imagem_Plataforma_down_right);
    al_destroy_bitmap(imagem_Plataforma_top_down);
    al_destroy_bitmap(imagem_Plataforma_top_left);
    al_destroy_bitmap(imagem_Plataforma_top_right);
    al_destroy_bitmap(imagem_Iniciar_Jogo_Branco);
    al_destroy_bitmap(imagem_Iniciar_Jogo_Vermelho);
    al_destroy_bitmap(imagem_Fruta_Manga);
    al_destroy_bitmap(imagem_Tela_Fase_1);
    al_destroy_bitmap(imagem_como_jogar);


    al_destroy_audio_stream(musica_journey);
    al_destroy_audio_stream(musica_megaman);
}


void iniciarTimer()
{
    tempoInicial = al_get_time();
}

double obterTempoTimer()
{
    return al_get_time() - tempoInicial;
}