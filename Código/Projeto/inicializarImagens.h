/*===============================
==== Inicialização de Imagens ===
=================================*/
bool inicicializar_imagens()
{
    // Carrega nosso background, e verifica se está tudo certo.
    imagem_inicial = al_load_bitmap("imagens/Tela-inicial.png");
    if (!imagem_inicial)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_inicial.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_opcoes = al_load_bitmap("imagens/Tela_Opcoes3.0.png");
    if (!imagem_opcoes)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_opcoes.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_on_Melodia = al_load_bitmap("imagens/melodia-on.png");
    if (!imagem_on_Melodia)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_on_Melodia.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_off_Melodia = al_load_bitmap("imagens/melodia-off.png");
    if (!imagem_off_Melodia)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_off_Melodia.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_on_SFX = al_load_bitmap("imagens/sfx-on.png");
    if (!imagem_on_SFX)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_on_SFX.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_off_SFX = al_load_bitmap("imagens/sfx-off.png");
    if (!imagem_off_SFX)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_off_SFX.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Iniciante = al_load_bitmap("imagens/Dificuldade_Iniciante.png");
    if (!imagem_Iniciante)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Iniciante.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Normal = al_load_bitmap("imagens/Dificuldade_Normal.png");
    if (!imagem_Normal)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Normal.\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Desafiante = al_load_bitmap("imagens/Dificuldade_Desafiante.png");
    if (!imagem_Desafiante)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Desafiante\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Iniciar_Jogo_Branco = al_load_bitmap("imagens/Iniciar_Jogo_Branco.png");
    if (!imagem_Iniciar_Jogo_Branco)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Iniciar_Jogo_Branco\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Iniciar_Jogo_Vermelho = al_load_bitmap("imagens/Iniciar_Jogo_Vermelho.png");
    if (!imagem_Iniciar_Jogo_Vermelho)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Iniciar_Jogo_Vermelho\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[0] = al_load_bitmap("imagens/ACenoura.1.png");
    if (!arrayFrutas[0])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de ACenoura.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[1] = al_load_bitmap("imagens/Amanga.1.png");
    if (!arrayFrutas[1])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de Amanga.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[2] = al_load_bitmap("imagens/ATomateA.1.png");
    if (!arrayFrutas[2])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de ATomateA.1a\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[3] = al_load_bitmap("imagens/BAbacate.1.png");
    if (!arrayFrutas[3])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de BAbacate.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[4] = al_load_bitmap("imagens/BBanana.1.png");
    if (!arrayFrutas[4])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de BBanana.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[5] = al_load_bitmap("imagens/BOvo.1.png");
    if (!arrayFrutas[5])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de BOvo.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[6] = al_load_bitmap("imagens/CBocolis.1.png");
    if (!arrayFrutas[6])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de CBocolis.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[7] = al_load_bitmap("imagens/CLaranja.1.png");
    if (!arrayFrutas[7])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de CLaranja.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[8] = al_load_bitmap("imagens/CMorango.1.png");
    if (!arrayFrutas[8])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de CMorango.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[8] = al_load_bitmap("imagens/CMorango.1.png");
    if (!arrayFrutas[8])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de CMorango.1\n");
        inicializar_destroy_all();
        return false;
    }

    arrayFrutas[9] = al_load_bitmap("imagens/EAvela.1.png");
    if (!arrayFrutas[9])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de EAvela.1\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_Tela_Fase_1 = al_load_bitmap("imagens/Tela_Fase_1.png");
    if (!imagem_Tela_Fase_1)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_Tela_Fase_1\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_como_jogar = al_load_bitmap("imagens/como_jogar.png");
    if (!imagem_como_jogar)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_como_jogar\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_bt_jogar[0] = al_load_bitmap("imagens/bt_jogar_branco.png");
    if (!imagem_bt_jogar[0])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_bt_jogar[0]\n");
        inicializar_destroy_all();
        return false;
    }
    imagem_bt_jogar[1] = al_load_bitmap("imagens/bt_jogar_vermelho.png");
    if (!imagem_bt_jogar[1])
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_bt_jogar[0]\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_dutos = al_load_bitmap("imagens/dutos.png");
    if (!imagem_dutos)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_dutos\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_suga_esquerda = al_load_bitmap("imagens/friozinhoesquerdo.png");
    if (!imagem_suga_esquerda)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de friozinhodireito\n");
        inicializar_destroy_all();
        return false;
    }

    imagem_suga_direita = al_load_bitmap("imagens/friozinhodireito.png");
    if (!imagem_suga_direita)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de imagem_suga_direita \n");
        inicializar_destroy_all();
        return false;
    }

    imagem_tela_final = al_load_bitmap("imagens/tela_final.png");
    if (!imagem_tela_final)
    {
        fprintf(stderr, "Falha ao carregar o arquivo de tela_final.png \n");
        inicializar_destroy_all();
        return false;
    }
}