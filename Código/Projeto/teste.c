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
#include <time.h>
#include <conio.h>
#include "variaveisEFuncoes.h"
#include "inicializarImagens.h"
#include "inicializarDestroyAll.h"
#include "inicializarTimer.h"


/*=====================
==== Início do Jogo ===
=======================*/
int main(void)
{
    float x = 585;
    float y = -100;
    float raio = 50.0;
    float tam_fruta = 2*raio;
    int dir_x = 0;
    int dir_y = 1;

    inicicializar_comandos();
    if(!inicicializar_comandos)
    {
        fprintf(stderr, "Falha ao inicializar comandos\n");
        return false;
    }
    inicicializar_imagens();
    if(!inicicializar_imagens)
    {
        fprintf(stderr, "Falha ao inicializar comandos\n");
        return false;
    }
    inicializar_registradores_da_fila_de_eventos();
    numeros_aleatorios();

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
                if(tecla == 3)
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
                    velocidade = 2.0;
                }
                else if(normal == true)
                {
                    al_draw_bitmap(imagem_Normal , 0, 0, 0);
                    dificuldade = 2;
                    velocidade = 4.0;
                }
                else if(desafiante == true)
                {
                    al_draw_bitmap(imagem_Desafiante , 0, 0, 0);
                    dificuldade = 3;
                    velocidade = 8.0;
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

            if(tecla == 2 && Iniciar_Jogo_Vermelho == true)
            {
                al_draw_bitmap(imagem_como_jogar , 0, 0, 0);

                if(jogar == false)
                {
                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES ||ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 0 &&
                            evento.mouse.x <= 1280 &&
                            evento.mouse.y >= 0 &&
                            evento.mouse.y <= 720)
                        {
                            jogar = false;
                            bt_jogar_vermelho = false;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || ALLEGRO_EVENT_MOUSE_WARPED)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 888 &&
                            evento.mouse.x <= 1043 &&
                            evento.mouse.y >= 583 &&
                            evento.mouse.y <= 628)
                        {
                            jogar = false;
                            bt_jogar_vermelho = true;
                        }
                    }

                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        // Verificamos se ele está sobre a região da imagem habilitado
                        if (evento.mouse.x >= 888 &&
                            evento.mouse.x <= 1043 &&
                            evento.mouse.y >= 583 &&
                            evento.mouse.y <= 628)
                        {
                            jogar = true;
                        }
                    }
                }

                if(bt_jogar_vermelho == true)
                {
                    al_draw_bitmap(imagem_bt_jogar[1] , 0, 0, 0);
                }
                else if(bt_jogar_vermelho == false)
                {
                    al_draw_bitmap(imagem_bt_jogar[0] , 0, 0, 0);
                }
                if(jogar == true)
                {
                    tecla = 3;
                }
            }
        }
        /*=================
        === Tela Fase 1 ===
        ===================*/
        if(tecla == 3 && bt_jogar_vermelho == true)
        {
            if(dificuldade == 1 && velocidade == 2.0)
            {
                al_draw_bitmap(imagem_Tela_Fase_1 , 0, 0, 0);
                al_draw_bitmap(imagem_dutos , 0, 0, 0);

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===============================================================       ==================================================================================
                // =================================================================     ==================================================================================
                // =================================================================     ==================================================================================
                // =================================================================     ==================================================================================
                // =================================================================     ==================================================================================
                // =================================================================     ==================================================================================
                // ============================================================              ============================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================


                if (sound_Melodia == true)
                {
                    al_set_audio_stream_playing(musica_journey, false);
                    al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                    al_set_audio_stream_playing(musica_megaman, true);
                }
                else if(sound_Melodia)
                {
                    al_set_audio_stream_playing(musica_journey, false);
                    al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                    al_set_audio_stream_playing(musica_megaman, false);
                }

                if(top == 1)
                {
                    if(anima_esquerda == 0)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, -10, 0, 0);
                        anima_esquerda++;
                    }
                    else if (anima_esquerda == 1)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, 0, 0, 0);
                        anima_esquerda++;
                    }
                    else if (anima_esquerda == 2)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, 10, 0, 0);
                        anima_esquerda = 0;
                    }
                }
                if(top == 2)
                {
                    if(anima_direita == 0)
                    {
                        al_draw_bitmap(imagem_suga_direita, -10, 0, 0);
                        anima_direita++;
                    }
                    else if (anima_direita == 1)
                    {
                        al_draw_bitmap(imagem_suga_direita, 0, 0, 0);
                        anima_direita++;
                    }
                    else if (anima_direita == 2)
                    {
                        al_draw_bitmap(imagem_suga_direita, 10, 0, 0);
                        anima_direita = 0;
                    }
                }

                if(fruta == 0)
                {
                    if(j[0] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

                else if(fruta == 1)
                {
                    if(j[1] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

               // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 2)
                {
                    if(j[2] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 3)
                {
                    if(j[3] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 4)
                {
                    if(j[4] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 5)
                {
                    if(j[5] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 6)
                {
                    if(j[6] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

                else if(fruta == 7)
                {
                    if(j[7] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 8)
                {
                    if(j[8] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 9)
                {
                    if(j[9] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                }
            }


                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ====================================================                            =============================================================================================
                // ============================================================================    =======================================================================
                // ============================================================================    =======================================================================
                // =====================================================                           ==============================================================================================
                // =====================================================    =============================================================================================
                // =====================================================    ==============================================================================================
                // =====================================================                           ==================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

            else if(dificuldade == 2 && velocidade == 4.0)
            {
                al_draw_bitmap(imagem_Tela_Fase_1 , 0, 0, 0);
                al_draw_bitmap(imagem_dutos , 0, 0, 0);

                if (sound_Melodia == true)
                {
                    al_set_audio_stream_playing(musica_journey, false);
                    al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                    al_set_audio_stream_playing(musica_megaman, true);
                }
                else if(sound_Melodia)
                {
                    al_set_audio_stream_playing(musica_journey, false);
                    al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                    al_set_audio_stream_playing(musica_megaman, false);
                }

                if(top == 1)
                {
                    if(anima_esquerda == 0)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, -10, 0, 0);
                        anima_esquerda++;
                    }
                    else if (anima_esquerda == 1)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, 0, 0, 0);
                        anima_esquerda++;
                    }
                    else if (anima_esquerda == 2)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, 10, 0, 0);
                        anima_esquerda = 0;
                    }
                }
                if(top == 2)
                {
                    if(anima_direita == 0)
                    {
                        al_draw_bitmap(imagem_suga_direita, -10, 0, 0);
                        anima_direita++;
                    }
                    else if (anima_direita == 1)
                    {
                        al_draw_bitmap(imagem_suga_direita, 0, 0, 0);
                        anima_direita++;
                    }
                    else if (anima_direita == 2)
                    {
                        al_draw_bitmap(imagem_suga_direita, 10, 0, 0);
                        anima_direita = 0;
                    }
                }

                if(fruta == 0)
                {
                    if(j[0] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

                else if(fruta == 1)
                {
                    if(j[1] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

               // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 2)
                {
                    if(j[2] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 3)
                {
                    if(j[3] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 4)
                {
                    if(j[4] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 5)
                {
                    if(j[5] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 6)
                {
                    if(j[6] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

                else if(fruta == 7)
                {
                    if(j[7] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 8)
                {
                    if(j[8] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 9)
                {
                    if(j[9] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                }
            }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // =====================================================                           =============================================================================================
                // ============================================================================    =======================================================================
                // ============================================================================    =======================================================================
                // =====================================================                           ==============================================================================================
                // ============================================================================    =========================================================================
                // ============================================================================    ===========================================================================
                // =====================================================                           ==================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

            else if(dificuldade == 3 && velocidade == 8.0)
            {
                al_draw_bitmap(imagem_Tela_Fase_1 , 0, 0, 0);
                al_draw_bitmap(imagem_dutos , 0, 0, 0);

                if (sound_Melodia == true)
                {
                    al_set_audio_stream_playing(musica_journey, false);
                    al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                    al_set_audio_stream_playing(musica_megaman, true);
                }
                else if(sound_Melodia)
                {
                    al_set_audio_stream_playing(musica_journey, false);
                    al_attach_audio_stream_to_mixer(musica_megaman, al_get_default_mixer());
                    al_set_audio_stream_playing(musica_megaman, false);
                }

                if(top == 1)
                {
                    if(anima_esquerda == 0)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, -10, 0, 0);
                        anima_esquerda++;
                    }
                    else if (anima_esquerda == 1)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, 0, 0, 0);
                        anima_esquerda++;
                    }
                    else if (anima_esquerda == 2)
                    {
                        al_draw_bitmap(imagem_suga_esquerda, 10, 0, 0);
                        anima_esquerda = 0;
                    }
                }
                if(top == 2)
                {
                    if(anima_direita == 0)
                    {
                        al_draw_bitmap(imagem_suga_direita, -10, 0, 0);
                        anima_direita++;
                    }
                    else if (anima_direita == 1)
                    {
                        al_draw_bitmap(imagem_suga_direita, 0, 0, 0);
                        anima_direita++;
                    }
                    else if (anima_direita == 2)
                    {
                        al_draw_bitmap(imagem_suga_direita, 10, 0, 0);
                        anima_direita = 0;
                    }
                }

                if(fruta == 0)
                {
                    if(j[0] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[0] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[0] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[0]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

                else if(fruta == 1)
                {
                    if(j[1] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[1] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[1] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[1]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

               // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 2)
                {
                    if(j[2] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[2] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[2] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[2]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 3)
                {
                    if(j[3] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[3] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[3] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[3]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 4)
                {
                    if(j[4] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[4] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[4] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[4]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 5)
                {
                    if(j[5] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[5] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[5] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[5]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 6)
                {
                    if(j[6] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[6] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[6] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[6]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================

                else if(fruta == 7)
                {
                    if(j[7] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[7] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[7] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[7]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 8)
                {
                    if(j[8] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                    }
                    else if (j[8] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                    else if (j[8] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[8]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                        }
                    }
                }

                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                // ===================================================================================================================================================
                else if(fruta == 9)
                {
                    if(j[9] == 0)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 1)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 2)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 3)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 4)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 5)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 6)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 7)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 8)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                    else if (j[9] == 9)
                    {
                        al_draw_bitmap(arrayFrutas[j[9]], x, y, 0);
                        al_flip_display();

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

                        if(x > 1070)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            pontos += 1;
                            tecla = 4;
                        }
                        else if(x < 110)
                        {
                            x = 585;
                            y = -100;
                            dir_x = 0;
                            dir_y = 1;
                            fruta += 1;
                            tecla = 4;
                        }
                    }
                }
            }
        }

        if(tecla == 4)
        {
            al_draw_bitmap(imagem_tela_final, 0, 0, 0);
            al_draw_textf(fonte36, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 168, ALLEGRO_ALIGN_CENTRE, "Voce acertou  %d/10 e obteve %d Pontos!",  pontos, 100*pontos);
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
