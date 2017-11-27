/*==============================
==== Desalocação da Memória ====
================================*/

void inicializar_destroy_all()
{
    // Desalocação da Memória
    al_destroy_font(fonte28);
    al_destroy_font(fonte36);

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
    al_destroy_bitmap(imagem_Iniciar_Jogo_Branco);
    al_destroy_bitmap(imagem_Iniciar_Jogo_Vermelho);
    al_destroy_bitmap(imagem_Tela_Fase_1);
    al_destroy_bitmap(imagem_como_jogar);
    al_destroy_bitmap(imagem_dutos);
    al_destroy_bitmap(arrayFrutas[0]);
    al_destroy_bitmap(arrayFrutas[1]);
    al_destroy_bitmap(arrayFrutas[2]);
    al_destroy_bitmap(arrayFrutas[3]);
    al_destroy_bitmap(arrayFrutas[4]);
    al_destroy_bitmap(arrayFrutas[5]);
    al_destroy_bitmap(arrayFrutas[6]);
    al_destroy_bitmap(arrayFrutas[7]);
    al_destroy_bitmap(arrayFrutas[8]);
    al_destroy_bitmap(arrayFrutas[9]);
    al_destroy_bitmap(imagem_bt_jogar[0]);
    al_destroy_bitmap(imagem_bt_jogar[1]);
    al_destroy_bitmap(imagem_suga_direita);
    al_destroy_bitmap(imagem_suga_esquerda);
    al_destroy_bitmap(imagem_tela_final);

    al_destroy_audio_stream(musica_journey);
    al_destroy_audio_stream(musica_megaman);
}