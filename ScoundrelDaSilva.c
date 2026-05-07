
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// trocar a ordem dos inteiros numa matriz de 0 a 43
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
  return;
}

// imprimir o deck ===debug===
// ta so no seco no seco, so com os valores
void printArray(int ordem[], int n) {
  for (int i = 0; i < 4; i++) {
    // printf("%d ", ordem[i]);
    if (ordem[i] < 13) {
      printf("%d", ordem[i] + 1);
      printf("P- ");
    } else {
      if (ordem[i] < 26) {
        printf("%d", (ordem[i] % 13) + 1);
        printf("E- ");
      } else {
        if (ordem[i] < 35) {
          printf("%d", ordem[i] - 24);
          printf("O* ");

        } else {
          if (ordem[i] < 44) {
            printf("%d", ordem[i] - 33);
            printf("C+ ");
          }
        }
      }
    }
  }
  printf("\n\n");
  return;
}

// pocao de cura
int cura(int vtemp, int ctemp)  // vida e cura "temporarias" (da funcao)
{
  vtemp = vtemp + ctemp - 33;
  if (vtemp > 20) {
    vtemp = 20;
  }
  return vtemp;
}

// monstros e dano
int dano(int vtemp, int dtemp,
         int atemp)  // vida, dano e arma "temporarios" (da funcao)
{
  if ((dtemp % 13 + 1 - atemp) >= 0) {
    vtemp = vtemp - (dtemp % 13 + 1 - atemp);
  }
  return vtemp;
}

int armaf(int dtemp, int atemp) {  // dano e arma "temmporarios" (da funcao)
  if ((dtemp % 13 + 1) < atemp) {
    atemp = (dtemp % 13 + 1);
  }
  return atemp;
}

// permutacao aleatoria
void randomize(int ordem[], int n) {
  // semementes diferentes para diferentes configuracoes
  srand(time(NULL));

  // comeca pelo ultimo elemento a aleatorizacao, sem necessidade do primeiro
  // (pcp) n eh o modulo do conjunto dos elementos do array
  for (int i = n - 1; i > 0; i--) {
    // indice alatorio
    int j = rand() % (i + 1);

    // trocar com um de outro indice
    swap(&ordem[i], &ordem[j]);
  }
  return;
}

// ========================================= teste e parte principal
// ===========================
int main() {
  int ordem[44], vida, arma, escolha1, escolha2, escolha3, mao, rodada, japulou;
  vida = 20;
  arma = 0;
  escolha1 = 0;  // inicializa as escolhas
  escolha2 = 0;
  escolha3 = 0;
  rodada = 0;   // contador de rodadas
  japulou = 0;  // inicializa japulou, que eh usado para verificar se a pessoa
                // pulou a ultima rodada

  for (int i = 0; i < 44; i++) {
    ordem[i] = i;
  }
  int n = sizeof(ordem) / sizeof(ordem[0]);
  randomize(ordem, n);

  /*
  GAMEPLAY COMECA AQUI
  */

  while (1) {  // por enquanto roda pra sempre, eh apenas temporario
    // cartas (0-25 sao inimigos), (26-34 armas) e (35-44 pocoes de cura)
    printArray(ordem, n);
    printf("Vida: %d", vida);
    printf("\nArma: %d", arma);

    if (japulou == 0) {
      printf(
          "\nDeseja pular? Caso sim digite 1, caso nao digite 0 e escolha tres "
          "cartas\n");
      do {
        scanf("%d", &escolha1);  // le se pula
      } while ((escolha1 < 0 || escolha1 > 1));

      if (escolha1 ==
          1) {  // se pulou cai no caso 4 para pular na proxima verificacao
        japulou = 1;
      }
    } else {
      japulou = 0;
      printf("\nEscolha tres cartas\n");
    }

    // se nao pulou
    if (japulou != 1) {
      do {
        scanf("%d", &escolha1);  // le as cartas escolhidas
        scanf("%d", &escolha2);
        scanf("%d", &escolha3);
        escolha1 = escolha1 - 1;
        escolha2 = escolha2 - 1;
        escolha3 = escolha3 - 1;
        if (((escolha1 < 0 || escolha1 > 4) || (escolha2 < 0 || escolha2 > 4) ||
             (escolha3 < 0 || escolha3 > 4)) ||
            (escolha1 == escolha2 || escolha1 == escolha3 ||
             escolha2 == escolha3)) {
          printf("Alguma das escolhas foi invalida, tente novamente\n");
        }
      } while (((escolha1 < 0 || escolha1 > 4) ||
                (escolha2 < 0 || escolha2 > 4) ||
                (escolha3 < 0 || escolha3 > 4)) ||
               (escolha1 == escolha2 || escolha1 == escolha3 ||
                escolha2 == escolha3));

      // ve o tipo da carta
      if (ordem[escolha1] <= 25) {
        // monstro
        vida = dano(vida, ordem[escolha1], arma);
        arma = armaf(ordem[escolha1], arma);
      } else {
        if (ordem[escolha1] > 35) {
          // pocao de cura
          vida = cura(vida, ordem[escolha1]);
        } else {
          // arma
          arma = ordem[escolha1] - 24;
        }
      }

      if (ordem[escolha2] <= 25) {
        // monstro
        vida = dano(vida, ordem[escolha2], arma);
        arma = armaf(ordem[escolha2], arma);
      } else {
        if (ordem[escolha2] > 35) {
          // pocao de cura
          vida = cura(vida, ordem[escolha2]);
        } else {
          // arma
          arma = ordem[escolha1] - 24;
        }
      }

      if (ordem[escolha3] <= 25) {
        // monstro
        vida = dano(vida, ordem[escolha3], arma);
        arma = armaf(ordem[escolha3], arma);
      } else {
        if (ordem[escolha3] > 35) {
          // pocao de cura
          vida = cura(vida, ordem[escolha3]);
        } else {
          // arma
          arma = ordem[escolha1] - 24;
        }
      }
    } else {
      randomize(ordem, n);
      mao = 3;
    }
    mao = 0;  // recomeca a escolha das cartas
    rodada++;
    printf("\n\n");  // da espaco pra proxima tela
  }

  /*
  GAMEPLAY ACABA AQUI
  */

  /* ===debug===
  printf("\n\n vida: %d \n\n", vida);
  //printArray(ordem, n);
  */

  return 0;
}  // =====================================================================================
