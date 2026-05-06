#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// trocar a ordem dos inteiros numa matriz de 0 a 43
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// imprimir o deck ===debug===
//ta so no seco no seco, so com os valores
void printArray (int ordem[], int n)
{
    for (int i = 0; i < 4; i++){
        //printf("%d ", ordem[i]);
        if(ordem[i]<13){
            printf("%d", ordem[i]+1);
            printf("P ");
        } else {
            if(ordem[i]<26){
                printf("%d", (ordem[i]%13)+1);
                printf("E ");
            } else {
                if(ordem[i]<35){
                    printf("%d", ordem[i]-24);
                    printf("O ");

                } else {
                    if(ordem[i]<44){
                        printf("%d", ordem[i]-33);
                        printf("C ");
                    }
                }
            }
        }
    }
    printf("\n\n");
}

int cura(int vtemp, int ctemp) //vida e cura "temporaria" (da funcao)
{
    vtemp = vtemp + ctemp - 34;
    if(vtemp > 20){
        vtemp = 20;
    }
    return vtemp;
}

int dano(int vtemp, int dtemp) //vida e dano "temporario" (da funcao)
{
    vtemp = vtemp - (dtemp%13+1);
    return vtemp;
}

// permutacao aleatoria
void randomize ( int ordem[], int n )
{
    // semementes diferentes para diferentes configuracoes
    srand (time(NULL) );

    // comeca pelo ultimo elemento a aleatorizacao, sem necessidade do primeiro (pcp)
    //n eh o modulo do conjunto dos elementos do array
    for (int i = n-1; i > 0; i--)
    {
        // indice alatorio
        int j = rand() % (i+1);

        // trocar com um de outro indice
        swap(&ordem[i], &ordem[j]);
    }
}

// ========================================= teste e parte principal ===========================
int main()
{
    int ordem[44], vida, arma, escolha;
    vida = 20;
    arma = 0;
    for(int i = 0; i < 44; i++){
        ordem[i] = i;
    }
    int n = sizeof(ordem)/ sizeof(ordem[0]);
    randomize (ordem, n);

    //cartas (0-25 sao inimigos), (26-34 armas) e (35-44 pocoes de cura)
    ordem[0]=15;
    printArray(ordem, n);
    printf("Vida: %d", vida);
    printf("\nArma: %d", arma);

    do{
    printf("\nEscolha uma carta\n");
    scanf("%d", &escolha); //le as cartas escolhidas
    }while (escolha<0 || escolha>3);


    //ve o tipo da carta
    if(ordem[escolha]<=25){
        //monstro
        vida = dano(vida, ordem[escolha]);
    } else{
        if(ordem[escolha]>35){
            //pocao de cura
            vida = cura(vida, ordem[escolha]);
        } else{
        //arma
        }
    }
    /* ===debug===
    printf("\n\n vida: %d \n\n", vida);
    */
    return 0;
} // =====================================================================================
