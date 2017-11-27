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
ALLEGRO_BITMAP *imagem_Iniciar_Jogo_Branco = NULL;
ALLEGRO_BITMAP *imagem_Iniciar_Jogo_Vermelho = NULL;
ALLEGRO_BITMAP *imagem_Tela_Fase_1 = NULL;
ALLEGRO_BITMAP *imagem_como_jogar = NULL;
ALLEGRO_BITMAP *imagem_dutos = NULL;
ALLEGRO_BITMAP *arrayFrutas[10];
ALLEGRO_BITMAP *imagem_bt_jogar[2];
ALLEGRO_BITMAP *imagem_suga_direita = NULL;
ALLEGRO_BITMAP *imagem_suga_esquerda = NULL;
ALLEGRO_BITMAP *imagem_tela_final = NULL;


//Fila de eventos, ela vai receber as ações do "usuário/programa".
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

// O nosso arquivo de fonte
ALLEGRO_FONT *fonte28 = NULL;
ALLEGRO_FONT *fonte36 = NULL;

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
bool jogar = false;
bool bt_jogar_vermelho = false;

int tecla = 0;
int top = 1;
int down = 2;
int frame = 0;
int i = 0;
int j[10];
int dificuldade = 0;
int fruta = 0;
int anima_direita = 0;
int anima_esquerda = 0;
int pontos = 0;

double velocidade = 0.0;

//Double utilizada para o cálculo do tempo de atualização da tela
double tempoInicial = 0;

//Prototipando as funções
bool inicicializar_comandos();
bool inicicializar_imagens();
void inicializar_registradores_da_fila_de_eventos();
void inicializar_destroy_all();
void iniciarTimer();
void numeros_aleatorios();
double obterTempoTimer();


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
    fonte28 = al_load_font("fontes/old_stamper.ttf", 28, 0);
    if (!fonte28)
    {
        fprintf(stderr, "Falha ao carregar fonte28.\n");
        inicializar_destroy_all();
        return false;
    }

    // Carregando o arquivo de fonte.
    fonte36 = al_load_font("fontes/comic.ttf", 36, 0);
    if (!fonte36)
    {
        fprintf(stderr, "Falha ao carregar fonte36.\n");
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

    musica_journey = al_load_audio_stream("musicas/musica Journey.ogg", 4, 1024);
    if (!musica_journey)
    {
        fprintf(stderr, "Falha ao carregar audio -  musica Journey.ogg.\n");
        inicializar_destroy_all();
        return false;
    }

    musica_megaman = al_load_audio_stream("musicas/musica Megaman.ogg", 4, 1024);
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

// Função para gerar números aleatórios que serão
// usados para determinar qual será a sequencia de
// queda das frutas.
// Isso serve para: toda vez que for iniciado o jogo,
// sempre será uma sequencia diferente de frutas!

void numeros_aleatorios()
{
    srand((unsigned)time(NULL));
    for (i = 0; i < 10; i++)
     {
           /* gerando valores aleatórios entre zero e 9 */
           j[i] = rand() % 10;
     }
}