#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handleSignals(int signum);

int main() {
    void(*sigHandlerInterrupt)(int);
    void(*sigHandlerQuit)(int);
    void(*sigHandlerReturn)(int);
    sigHandlerInterrupt = sigHandlerQuit = handleSignals;
    sigHandlerReturn = signal(SIGINT, sigHandlerInterrupt);

    if (sigHandlerReturn == SIG_ERR) {
        perror("Signal error");
        return 1;
    }

    sigHandlerReturn = signal(SIGQUIT, sigHandlerQuit);

    if (sigHandlerReturn == SIG_ERR) {
        perror("Signal error");
        return 1;
    }
    for(;;) {
        printf("\nA programbol valo kilepeshez az alabbiakat kell elvegezni: \n");
        printf("1. masik terminal nyitasa.\n");
        printf("2. Adja ki a parancsot: kill: %d \n", getpid());
        sleep(10);
    }
    return 0;
}

void handleSignals(int signum) {

    if(signum == SIGINT)
        {
            printf("\n CTRL+C-t eszlelt\n");
            signal(SIGINT, SIG_DFL);
        }else if(signum == SIGQUIT)
            {
                printf("SIQUIT aktivalodott\n");
            }else
            {

                printf("\nFogadott jel szama: %d\n", signum);
            }
    
    return ;
}
