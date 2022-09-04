#include <windows.h>

/*
 * Cria uma janela principal para o
 * sistema operacional Windows
 * Não há necessidade de preocupar com o
 * gerenciamento de memória, uma vez que, o sistema
 * é 64bits
 * Este programa conta com duas funções principais,
 * a main e a procjan, que gera a janela
 *
 */

LRESULT CALLBACK ProcJan(HWND, UINT, WPARAM, LPARAM); // prototipo obrigatório
char szNomeAplic[] = "Principal";


int WINAPI WinMain(HINSTANCE hCopia, HINSTANCE hCopiaAnt, LPSTR szLinhaCmd, int iCmdMostrar)
{
    /*
        hCopia -> Número da cópia, ou seja, do processo em execução
        hCopiaAnt -> Parâmetro obsoleto, deve receber nulo
        szLinhaCmd -> Ponteiro que recebe argumentos da linha de comando,já q se pode executar via terminal
        iCmdMostrar -> Como a janela deve ser aberta (1 -> Normal, 7 -> Minimizada)
    */
    HWND hjan;           // identificador da janela
    MSG msg;             // identificador de mensagens
    WNDCLASS classejan;  // identificador do registro da classe que cria janelas(no windows, tudo é derivado)

    // definindo a estrutura WNDCLASS
    classejan.style        = CS_HREDRAW | CS_VREDRAW;  // garante que na horizontal ou vertical a janela será pintada
    classejan.lpfnWndProc  = ProcJan;  // indica que o procedimento é procjan (a funcao principal para criar janela e nela será passado as msg)
    classejan.cbClsExtra   = 0;  //reserva extra de espaço (0, pois não está em uso) [ estrutura da class]
    classejan.cbWndExtra   = 0;   //reserva extra de espaço (0, pois não está em uso)[estrutura da janela]
    classejan.hInstance    = hCopia;  // identificador da instância (processo em execucao)
    classejan.hIcon        = LoadIcon(NULL, IDI_APPLICATION); //icone, pre definido NULL (pode ser um bitmap)
    classejan.hCursor      = LoadCursor(NULL, IDC_ARROW);  // cursor padrao
    classejan.hbrBackground= GetStockObject(WHITE_BRUSH);  // cor branca de fundo
    classejan.lpszMenuName = NULL;  // menu da janela (null = inexistente)
    classejan.lpszClassName= szNomeAplic; // nome da janela

    // registra a janela principal, se ela nao existir, retorna
    if(!RegisterClass(&classejan)) return 0;

    //cria a janela principal
    hjan = CreateWindow(
            szNomeAplic,          // nome a qual a janela é associada
            "Janela Principal",   // nome da que aparecerá na janela
            WS_OVERLAPPEDWINDOW,  // janela padrao
            CW_USEDEFAULT,        // deixa o windows dimencionar a janela responsiva [inicio]
            CW_USEDEFAULT,        // deixa o windows dimencionar a janela responsiva [fim]
            CW_USEDEFAULT,        // deixa o windows dimencionar a janela responsiva [largura]
            CW_USEDEFAULT,        // deixa o windows dimencionar a janela responsiva [altura]
            HWND_DESKTOP,         // Janela mãe, no caso, DESKTOP refere-se ao próprio sistema
            NULL,                 // identificador de menu
            hCopia,               // identificador do processo (copia do programa)
            NULL                  // ponteiro para a janela criada
            );

    //exibe a janela:
    ShowWindow(hjan, iCmdMostrar);  // janela criada e como deve ser exibida

    UpdateWindow(hjan);  // colore a área para a janela passada

    // adapta o programa para receber mensagens do teclado
    while (GetMessage(&msg, NULL, 0, 0))  // iPmsg, é um ponteiro para o windows, que pegara as mensagens de uma fila de execucao, os outros dizem quantas devem ser traduzidas, no caso, todas
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;

}


LRESULT CALLBACK ProcJan(HWND hjan, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /*
     * hjan -> identificador da janela
     * iMsg -> identificador da mensagem na fila de processamento do windows(identifica todas as acoes na janela)
     * wParam -> informacao sobre a msg [posicao do mouse etc]
     * lparam -> informação sobre a msg
     */

    if (iMsg == WM_DESTROY)
    {
         // se o usuario clicar no botao de fechar
            PostQuitMessage(0);
            return 0;
    }

    // para todas as mensagens que nao forem processadas:
    return DefWindowProc(hjan, iMsg, wParam, lParam);  // seu retorno é para dentro do procedimento de janela
}
