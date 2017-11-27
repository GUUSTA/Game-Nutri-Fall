
// Funções para regular a taxa de frams por segundos.

void iniciarTimer()
{
    tempoInicial = al_get_time();
}

double obterTempoTimer()
{
    return al_get_time() - tempoInicial;
}