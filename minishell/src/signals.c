#include "../minishellft.h"

volatile sig_atomic_t g_in_readline = 0;

// Manejador de la señal SIGINT (Ctrl+C)
void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    if (g_in_readline)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

// Manejador de la señal SIGTSTP (Ctrl+Z)
void sigtstp_handler(int sig)
{
    (void)sig;
    // Puedes suspender el proceso o tomar alguna acción personalizada
    write(1, "\nProcess suspended. Type 'fg' to resume.\n", 42); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

// Manejador de la señal SIGQUIT (Ctrl+\)
void sigquit_handler(int sig)
{
    (void)sig;
    write(1, "Quit (core dumped)\n", 19);  // Mensaje estándar de Ctrl+ /(invertida)
}

// Manejador de la señal SIGTERM (para la terminación del proceso)
void sigterm_handler(int sig)
{
    (void)sig;
    write(1, "Terminating shell...\n", 21);  // Mensaje de terminación
    exit(0);  // Terminar el shell
}

// Manejador de la señal SIGCHLD (cuando un proceso hijo termina)
void sigchld_handler(int sig)
{
    (void)sig;
    // Puedes usar waitpid() para recoger el proceso hijo terminado
    // Aquí no es necesario hacer nada si no se espera el proceso
    // Para capturar todos los hijos terminados:
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

// Manejador de la señal SIGWINCH (cuando la terminal cambia de tamaño)
void sigwinch_handler(int sig)
{
    (void)sig;
    // Actualiza el tamaño de la terminal si es necesario
    // Por ejemplo, puedes usar `ioctl` para obtener el tamaño de la terminal
    // En algunos shells se actualiza el prompt al cambiar el tamaño de la ventana
}

// Función para inicializar el manejo de señales
void setup_signals()
{
    signal(SIGINT, sigint_handler);    // Manejar SIGINT (Ctrl+C)
    signal(SIGTSTP, sigtstp_handler);  // Manejar SIGTSTP (Ctrl+Z)
    signal(SIGQUIT, sigquit_handler);  // Manejar SIGQUIT (Ctrl+\)
    signal(SIGTERM, sigterm_handler);  // Manejar SIGTERM
    signal(SIGCHLD, sigchld_handler);  // Manejar SIGCHLD (cuando un proceso hijo termina)
    signal(SIGWINCH, sigwinch_handler);  // Manejar SIGWINCH (cambio de tamaño de la terminal)
}
