
/*
 * Disciplina: SME0230 - IPC
 *
 * Integrantes: Danilo Viveiros de Assis
 *              Joao Victor Gonzaga
 * IA foi utilizado para a realizacao da arte em ASCII do titulo "SCOUNDREL", juntamente do site asciiart.edu
 * assim como para corrigir o erro na condicao de vitoria, dado que anteriormente o jogo rodava eternamente
 * e erros de indice de contadores que se acumulavam ao longo das salas, o que fazia o jogo acabar antes do fim
 * e continuar depois da vitoria
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* =========================================================================
 * INDICE DE CARTAS NO ARRAY 'ordem[44]':
 *  0 - 12  : Monstros de Paus  (valores 1 a 13, onde 11=J, 12=Q, 13=K)
 * 13 - 25  : Monstros de Espadas (valores 1 a 13)
 * 26 - 34  : Armas de Ouros    (valores 2 a 10)
 * 35 - 43  : Pocoes de Copas   (valores 2 a 10)
 * =========================================================================
 */

/* Permutacao aleatoria (Fisher-Yates) */
void randomiza(int ordem[], int n) {
    int pos_a, pos_b, temp; //posicao a, posicao b, temporario para randomizar
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        pos_a = ordem[i];
        pos_b = ordem[j];
        temp = pos_a;
        pos_a = pos_b;
        pos_b = temp;
        ordem[i]=pos_a;
        ordem[j]=pos_b;
    }
    return;
}

/* Retorna o valor numerico de uma carta dado seu indice no array */
int valor_carta(int indice) {
    if (indice < 26) {
        /* Monstro (Paus ou Espadas): valor = (indice % 13) + 1 */
        return (indice % 13) + 1;
    } else if (indice < 35) {
        /* Arma (Ouros): indice 26 = valor 2, ..., 34 = valor 10 */
        return indice - 24;
    } else {
        /* Pocao (Copas): indice 35 = valor 2, ..., 43 = valor 10 */
        return indice - 33;
    }
}


/* Retorna a string do valor para exibicao (1->A nao existe aqui, 11->J, etc.)*/
void str_valor(int val, char nome_carta[]) {
    if (val == 11) {
        nome_carta[0] = 'J';
        nome_carta[1] = '\0';
    } else if (val == 12) {
        nome_carta[0] = 'Q';
        nome_carta[1] = '\0';
    } else if (val == 13) {
        nome_carta[0] = 'K';
        nome_carta[1] = '\0';
    } else if (val == 14) {
        nome_carta[0] = 'A';
        nome_carta[1] = '\0';
    } else if (val == 10) {
        nome_carta[0] = '1';
        nome_carta[1] = '0';
        nome_carta[2] = '\0';
    } else {
        nome_carta[0] = '0' + val;
        nome_carta[1] = '\0';
    }
    return;
}

/* Imprime a tela de titulo em ASCII Art */
void imprimir_titulo(void) {
    printf("\n");

    printf("  #####    #####   ####   ##  ##  ##  ##  #####   #####   ######  ##   \n");
    printf(" ##      ##       ##  ##  ##  ##  ### ##  ##  ##  ##  ##  ##      ##   \n");
    printf("  ####   ##       ##  ##  ##  ##  ######  ##  ##  #####   ####    ##   \n");
    printf("     ##  ##       ##  ##  ##  ##  ## ###  ##  ##  ## ##   ##      ##   \n");
    printf(" #####     #####   ####    ####   ##  ##  #####   ##  ##  ######  #####\n");
    printf("\n");
    printf("\n");
    return;
}

/* printa menu inicial */
int menu(int player) {

    imprimir_titulo();
    printf("  \t\t======================================== \n");
    printf("  \t\t\tESCOLHA QUEM VAI JOGAR:                \n");
    printf("  \t\t\t(1=HUMANO / 0=COMPUTADOR)              \n");
    printf("  \t\t======================================== \n");
    printf("\n");
    do {
        scanf("%d", &player);
    } while(player!=0&&player!=1);
    system("clear");

    return player;
}

/* Imprime uma linha de uma carta ASCII (12 linhas x 18 chars com bordas).
 * Todas as linhas internas tem EXATAMENTE 16 chars entre os pipes |...|
 * linha: 0 a 11  |  indice: posicao no array (ou -1 para carta invalida) */
void imprimir_linha_carta(int linha, int indice) {
    char val_str[3];
    int val = 0;

    if (indice >= 0) {
        val = valor_carta(indice);
        str_valor(val, val_str);
    }

    /* Monstro: Paus (P) ou Espadas (E) */
    if (indice >= 0 && indice < 26) {
        if (linha == 0)
            printf("+----------------+");
        else if (linha == 1) {
            /* canto superior: valor alinhado a esquerda, 16 chars internos */
            if (val == 10)
                printf("|10              |");
            else if (val > 10)
                printf("|%s               |", val_str);
            else
                printf("|%s               |", val_str);
        } else if (linha == 2)
            printf("|    MONSTRO     |");
        else if (linha == 3)
            printf("|   /\\      /\\   |");
        else if (linha == 4)
            printf("|  /  \\____/  \\  |");
        else if (linha == 5)
            printf("|  |  O    O  |  |");
        else if (linha == 6)
            printf("|  \\_  vvvv  _/  |");
        else if (linha == 7)
            printf("|    \\ ^^^^ /    |");
        else if (linha == 8)
            printf("|     \\____/     |");
        else if (linha == 9)
            printf("|                |");
        else if (linha == 10) {
            /* rodape: valor centrado, sem naipe */
            if (val == 10)
                printf("|    [ 10 ]      |");
            else if (val > 10)
                printf("|     [ %s ]      |", val_str);
            else
                printf("|     [ 0%s ]     |", val_str);
        } else if (linha == 11)
            printf("+----------------+");
    }
    /* Arma: Ouros (O) */
    else if (indice >= 0 && indice < 35) {
        if (linha == 0)
            printf("+----------------+");
        else if (linha == 1) {
            if (val == 10)
                printf("|10              |");
            else
                printf("|%s               |", val_str);
        } else if (linha == 2)
            printf("|      ARMA      |");
        else if (linha == 3)
            printf("|       /\\       |");
        else if (linha == 4)
            printf("|      |  |      |");
        else if (linha == 5)
            printf("|      |  |      |");
        else if (linha == 6)
            printf("|      |  |      |");
        else if (linha == 7)
            printf("|     /_  _\\     |");
        else if (linha == 8)
            printf("|     [____]     |");
        else if (linha == 9)
            printf("|       ||       |");
        else if (linha == 10) {
            if (val == 10)
                printf("|    [ 10 ]      |");
            else
                printf("|     [ 0%s ]     |", val_str);
        } else if (linha == 11)
            printf("+----------------+");
    }
    /* Pocao de Cura: Copas (C) */
    else if (indice >= 0) {
        if (linha == 0)
            printf("+----------------+");
        else if (linha == 1) {
            if (val == 10)
                printf("|10              |");
            else
                printf("|%s               |", val_str);
        } else if (linha == 2)
            printf("|      CURA      |");
        else if (linha == 3)
            printf("|      ^^^       |");
        else if (linha == 4)
            printf("|     [___]      |");
        else if (linha == 5)
            printf("|      | |       |");
        else if (linha == 6)
            printf("|    .-' '-.     |");
        else if (linha == 7)
            printf("|   /  o  . \\    |");
        else if (linha == 8)
            printf("|  |  ~~~~~  |   |");
        else if (linha == 9)
            printf("|   \\_______/    |");
        else if (linha == 10) {
            if (val == 10)
                printf("|    [ 10 ]      |");
            else
                printf("|     [ 0%s ]     |", val_str);
        } else if (linha == 11)
            printf("+----------------+");
    }
    return;
}

/* Imprime a sala de 4 cartas lado a lado com legenda numerada */
void imprimir_sala(int ordem[], int ini, int c_sala) {
    printf("\n  --- SALA %d/15 ---\n\n", c_sala);
    if(c_sala<15) {
        printf("  Carta 1             Carta 2             Carta 3             Carta 4\n");
    } else {
        printf("  Carta 1             Carta 2\n");
    }

    for (int linha = 0; linha < 12; linha++) {
        printf("  ");
        for (int c = 0; c < 4; c++) {
            imprimir_linha_carta(linha, ordem[ini + c]);
            printf("  ");
        }
        printf("\n");
    }
    printf("\n\n");
    return;
}

/* Calcula vida apos usar uma pocao (valor = indice - 33) */
int cura(int vida, int indice_pocao, int jacurou) {
    if(jacurou==0) {
        int recuperacao = indice_pocao - 33;
        vida = vida + recuperacao;
        if (vida > 20) {
            vida = 20;
        }
    }
    return vida;
}

/* Calcula vida apos enfrentar monstro (com ou sem arma).
 * arma == 0 significa desarmado. */
int calcular_dano(int vida, int indice_monstro, int arma) {
    int valor_monstro = (indice_monstro % 13) + 1;
    int dano_sofrido = valor_monstro - arma;
    if (dano_sofrido > 0) {
        vida = vida - dano_sofrido;
    }
    return vida;
}

/* Atualiza o limite da arma apos derrotar um monstro com ela.
 * A arma so pode atacar monstros de valor menor que o ultimo derrotado.
 * Retorna o novo limite (que passa a ser o valor do monstro derrotado). */
int atualizar_limite_arma(int indice_monstro) {
    return (indice_monstro % 13) + 1;
}

/* Verifica se a arma pode ser usada contra este monstro.
 * limite_arma == 0 significa arma recen-equipada (sem restricao ainda).
 * Retorna 1 se pode usar, 0 se nao pode. */
int arma_pode_atacar(int limite_arma, int indice_monstro) {
    int valor_monstro = (indice_monstro % 13) + 1;
    if (limite_arma == 0) {
        return 1; /* sem restricao ainda */
    }
    return (valor_monstro < limite_arma);
}

/* Imprime o estado atual da mesa (vida, arma equipada, limite) */
void imprimir_mesa(int vida, int arma, int limite_arma, int japulou) {
    imprimir_titulo();
    printf(" ================================================================== \n");
    printf("  Pontos de Vida: %d / 20\n", vida);

    if (arma == 0) {
        printf("  Arma equipada : Nenhuma\n");
    } else {
        printf("  Arma equipada : %d (Ouros)", arma);
        if (limite_arma > 0) {
            printf("  [so ataca monstros < %d]", limite_arma);
        }
        printf("\n");
    }

    if (japulou == 1) {
        printf("  Aviso         : Voce pulou a ultima sala. NAO pode pular esta.\n");
    } else {
        printf("  Aviso         : Voce PODE pular esta sala.\n");
    }
    printf(" ================================================================== \n");
    return;
}


/* Move as 4 cartas do inicio do array para o final (pular sala).
 * As cartas sao inseridas no final do deck ainda nao processado. */
void pular_sala(int ordem[], int total_restante) {
    /* Guarda as 4 cartas da sala */
    int c0 = ordem[0];
    int c1 = ordem[1];
    int c2 = ordem[2];
    int c3 = ordem[3];

    /* Desloca todas as outras cartas validas para a esquerda */
    int validas = 0;
    for (int i = 0; i < total_restante; i++) {
        if (ordem[i] >= 0) {
            validas++;
        }
    }

    /* Conta quantas cartas validas existem alem das 4 da sala */
    int destino = 0;
    for (int i = 4; i < total_restante; i++) {
        if (ordem[i] >= 0) {
            ordem[destino] = ordem[i];
            destino++;
        }
    }
    /* Coloca as 4 cartas puladas no final */
    ordem[destino] = c0;
    ordem[destino + 1] = c1;
    ordem[destino + 2] = c2;
    ordem[destino + 3] = c3;

    /* Marca posicoes sobrando como invalidas */
    for (int i = destino + 4; i < total_restante; i++) {
        ordem[i] = -1;
    }
    return;
}
/* Funcoes do robo */
/* escolhe se o robo vai pular */
/* c3 e c4 podem nao existir */
int robo_pula (int c1, int c2, int c3, int c4, int vida) {
    int contador_monstro = 0;
    int dano_monstro = 0;
    float treshold;
    int roboescolha = 0;
    treshold = (float)vida*0.7;
    //conta quantos monstros tem
    if(c1<26 && c1 >= 0) {
        contador_monstro++;
        dano_monstro += c1%13+1;
    }
    if(c2<26 && c2 >= 0) {
        contador_monstro++;
        dano_monstro += c2%13+1;
    }
    if(c3<26 && c3 >= 0) {
        contador_monstro++;
        dano_monstro += c3%13+1;
    }
    if(c4<26 && c4 >= 0) {
        contador_monstro++;
        dano_monstro += c4%13+1;
    }
    if((contador_monstro > 3 && ((float)dano_monstro*1.5) >= treshold)||(contador_monstro==0)) {
        roboescolha = 1;
    }

    printf("%d", roboescolha);
    usleep(700000);

    return roboescolha;
}

/* escolhe se o robo usa arma */
int robo_arma (int monstro, int vida) {
    if(((monstro%13)+1 >=4) || ((monstro%13)+1 > vida)) {
        printf("1\n");
        return 1;
    }
    printf("0\n");
    usleep(700000);
    return 0;
}

/* escolhe cartas do robo */
int robo_cartas (int c1, int c2, int c3, int c4, int vida, int arma, int armat, int rando, int e1, int e2, int ve1, int ve2, int *lance_random) {
    int escolha = -2;

    /* Aqui se encontram os monstros */
    /* maior monstro que nao te mata */
    if(c1<26||c2<26||c3<26||c4<26) { /* ve se tem algum monstro */
        /* ve se algum nao te mata */
        /* ve qual e um monstro */
        int m1, m2, m3, m4, maiorm; /* inicializa sem monstros */
        m1 = -1;
        m2 = -1;
        m3 = -1;
        m4 = -1;
        maiorm = -2;
        if(c1<26 && c1 >= 0) {
            m1=c1; /* se c1 e monstro, guarda seu indice */
        }
        if(c2<26 && c2 >= 0) {
            m2=c2; /* se c2 e monstro, guarda seu indice */
        }
        if(c3<26 && c3 >= 0) {
            m3=c3; /* se c3 e monstro, guarda seu indice */
        }
        if(c4<26 && c4 >= 0) {
            m4=c4; /* se c4 e monstro, guarda seu indice */
        }
        /* visto quais sao monstros, ve se tem um maior que nao te mata */
        if((m1 != -1)&&(vida+arma-((c1%13)+1)>0)) { /* se c1 e monstro e nao te mata */
            /* se e1 e e2 nao sao monstros que te matam */
            if(e1>-1 && ve1 < 26) { /* se e1 monstro */
                if(vida+arma-(((c1%13)+1)+ve1)>0) { /* se a conta com e1 nao te mata */
                    if((c1%13)+1>maiorm) {
                        maiorm = 1;
                    }
                }
            }
            if(e2>-1 && ve2 < 26) { /* se e2 monstro */
                if(vida+arma-(((c1%13)+1)+ve2)>0) { /* se a conta com e2 nao te mata */
                    if(c1>maiorm) {
                        maiorm = 1;
                    }
                }
            }
            if((e1>-1 && ve1 < 26)&&(e2>-1 && ve2 < 26)) { /* se e1 e e2 sao monstros */
                if(vida+arma-(((c1%13)+1)+ve1+ve2)>0) { /* se a conta com e1 e e2 nao te mata */
                    if(c1>maiorm) {
                        maiorm = 1;
                    }
                }
            }
        }
        if((m2 != -1)&&(vida+arma-((c2%13)+1)>0)) { /* se c2 e monstro e nao te mata */
            /* se e1 e e2 nao sao monstros que te matam */
            if(e1>-1 && ve1 < 26) { /* se e1 monstro */
                if(vida+arma-(((c2%13)+1)+ve1%13)>0) { /* se a conta com e1 nao te mata */
                    if(c2>maiorm) {
                        maiorm = 2;
                    }
                }
            }
            if(e2>-1 && ve2 < 26) { /* se e2 monstro */
                if(vida+arma-(((c2%13)+1)+ve2)>0) { /* se a conta com e2 nao te mata */
                    if(c2>maiorm) {
                        maiorm = 2;
                    }
                }
            }
            if((e1>-1 && ve1 < 26)&&(e2>-1 && ve2 < 26)) { /* se e1 e e2 sao monstros */
                if(vida+arma-(((c2%13)+1)+ve1+ve2)>0) { /* se a conta com e1 e e2 nao te mata */
                    if(c2>maiorm) {
                        maiorm = 2;
                    }
                }
            }
        }
        if((m3 != -1)&&(vida+arma-((c3%13)+1)>0)) { /* se c3 e monstro e nao te mata */
            /* se e1 e e2 nao sao monstros que te matam */
            if(e1>-1 && ve1 < 26) { /* se e1 monstro */
                if(vida+arma-(((c3%13)+1)+ve1)>0) { /* se a conta com e1 nao te mata */
                    if(c3>maiorm) {
                        maiorm = 3;
                    }
                }
            }
            if(e2>-1 && ve2 < 26) { /* se e2 monstro */
                if(vida+arma-(((c3%13)+1)+ve2)>0) { /* se a conta com e2 nao te mata */
                    if(c3>maiorm) {
                        maiorm = 3;
                    }
                }
            }
            if((e1>-1 && ve1 < 26)&&(e2>-1 && ve2 < 26)) { /* se e1 e e2 sao monstros */
                if(vida+arma-(((c3%13)+1)+ve1+ve2)>0) { /* se a conta com e1 e e2 nao te mata */
                    if(c3>maiorm) {
                        maiorm = 3;
                    }
                }
            }
        }
        if((m4 != -1)&&(vida+arma-((c4%13)+1)>0)) { /* se c1 e monstro e nao te mata */
            /* se e1 e e2 nao sao monstros que te matam */
            if(e1>-1 && e1 < 26) { /* se e1 monstro */
                if(vida+arma-(((c4%13)+1)+ve1)>0) { /* se a conta com e1 nao te mata */
                    if(c4>maiorm) {
                        maiorm = 4;
                    }
                }
            }
            if(e2>-1 && ve2 < 26) { /* se e2 monstro */
                if(vida+arma-(((c4%13)+1)+ve2)>0) { /* se a conta com e2 nao te mata */
                    if(c4>maiorm) {
                        maiorm = 4;
                    }
                }
            }
            if((e1>-1 && ve1 < 26)&&(e2>-1 && ve2 < 26)) { /* se e1 e e2 sao monstros */
                if(vida+arma-(((c4%13)+1)+ve1+ve2)>0) { /* se a conta com e1 e e2 nao te mata */
                    if(c4>maiorm) {
                        maiorm = 4;
                    }
                }
            }
        }
        escolha = maiorm;
    }

    /* aqui se encontram as curas, se a vida for menos da metade escolhe a maior cura, senao escolhe a menor */
    /* escolher a maior cura */
    if(((ve1 < 35) && (ve2 < 35)) && (vida < 12)) { /* se ja escolheu pocao, ou vida alta nao entra aqui */
        int p1, p2, p3, p4, mp;
        p1 = -1;
        p2 = -1;
        p3 = -1;
        p4 = -1;
        /* ve as curas disponiveis */
        if(c1 <= 43 && c1 >=35) {
            p1 = c1;
        }
        if(c2 <= 43&& c2 >=35) {
            p2 = c2;
        }
        if(c3 <= 43&& c3 >=35) {
            p3 = c3;
        }
        if(c4 <= 43&& c4 >=35) {
            p4 = c4;
        }
        if(vida < 13) {
            mp = -2;
            /* ve a maior cura */
            if(p1 != -1 && mp < c1) {
                mp = c1;
            }
            if(p2 != -1 && mp <c2) {
                mp = c2;
            }
            if(p3 != -1 && mp < c3) {
                mp = c3;
            }
            if(p4 != -1 && mp <c4) {
                mp = c4;
            }
        } else {
            mp = 100;
            /* escolhe a menor */
            /* ve a menor cura */
            if(p1 != -1 && c1 <= mp) {
                mp = c1;
            }
            if(p2 != -1 && c2 <= mp) {
                mp = c2;
            }
            if(p3 != -1 && c3 <= mp) {
                mp = c3;
            }
            if(p4 != -1 && c4 <= mp) {
                mp = c4;
            }
            if(mp == 100) {
                mp = -2;
            }
        }
        /* sabendo o valor da maior escolhe ela */
        if(mp == c1) {
            mp = 1;
        }
        if(mp == c2) {
            mp = 2;
        }
        if(mp == c3) {
            mp = 3;
        }
        if(mp == c4) {
            mp = 4;
        }
        escolha = mp;
    }

    /* Aqui se encontram as armas*/
    if(((ve1 > 25) && (ve1 <35)) || ((ve2 > 25) && (ve2 < 35))) { /* se ja escolheu arma nao entra aqui */
        if((c1<35&&c1>25)||(c2<35&&c2>25)||(c3<35&&c3>25)||(c4<34&&c4>25)) { /* ve se tem alguma arma */
            int a1,a2,a3,a4,ma; /* ve quais sao armas e melhor arma */
            a1 = -1;
            a2 = -1;
            a3 = -1;
            a4 = -1;
            ma = -2;
            /* armat e arma atual */
            if(c1 >= 26 && c1 < 35) {
                a1 = c1;
            }
            if(c2 >= 26 && c2 < 35) {
                a2 = c2;
            }
            if(c3 >= 26 && c3 < 35) {
                a3 = c3;
            }
            if(c4 >= 26 && c4 < 35) {
                a4 = c4;
            }
            /* sabendo quais sao armas, decide uma boa o suficiente */
            if(a1 != -1 && (c1%13)+1 > armat) { /* se c1 e arma e acima do treshold */
                ma = 1;
            }
            if(a2 != -1 && (c2%13)+1 > armat) { /* se c2 e arma e acima do treshold */
                ma = 2;
            }
            if(a3 != -1 && (c3%13)+1 > armat) { /* se c3 e arma e acima do treshold */
                ma = 3;
            }
            if(a4 != -1 && (c4%13)+1 > armat) { /* se c4 e arma e acima do treshold */
                ma = 4;
            }
            /* se nenhuma passando do treshold escolhe qualquer */
            if(ma == -2) {
                if(a1 != -1) {
                    ma = 1; /* escolhe a 1 se ela for arma */
                }
                if(a2 != -1) {
                    ma = 2; /* escolhe a 2 se ela for arma */
                }
                if(a3 != -1) {
                    ma = 3; /* escolhe a 1 se ela for arma */
                }
                if(a4 != -1) {
                    ma = 4; /* escolhe a 1 se ela for arma */
                }
            }
            escolha = ma;
        }
    }

    if(escolha == -2 || escolha == e1 || escolha == e2) { /* se nao escolheu a melhor jogada, vai qualquer uma */
        escolha = rando;
    }
    printf(" %d", escolha);
    usleep(1000000);
    return escolha; //volta uma escolha por vez, a main possui uma memoria das escolhas anteriores
}

int main(void) {
    int lance_random = 0;
    int ordem[44];
    int vida = 20;
    int arma = 0;        /* valor da arma equipada (0 = nenhuma) */
    int limite_arma = 0; /* valor do ultimo monstro derrotado pela arma */
    int japulou = 0;     /* 1 se pulou a sala anterior */
    int japocao = 0;     /* 1 se ja usou pocao neste turno */
    int total = 44;      /* total de cartas ainda no deck */
    int val_resolvido;
    int contador_sala = 1;
    int player;          /* guarda quem joga */
    int random, random_passado;
    random_passado = 5;
    srand(time(NULL));
    random = (rand())%4+1;

    /* ve quem joga */
    player = menu(player);

    /* Inicializa deck de 0 a 43 */
    for (int i = 0; i < 44; i++) {
        ordem[i] = i;
    }
    randomiza(ordem, total);

    /* Loop principal: roda enquanto ha cartas e o jogador esta vivo */
    while (vida > 0 && total >= 1) {

        /* Garante que ha pelo menos 4 cartas para formar a sala */
        if (total < 2) {
            printf("\n  Masmorra esgotada! Voce venceu!\n");
            vida = -2; /* sinaliza saida do loop sem morte */
        }

        if (vida > 0 && total >= 2) { //continua o jogo
            int e1, e2, e3, ve1, ve2;
            e1 = 0;
            e2 = 0;
            e3 = 0;
            ve1 = -1;
            ve2 = -1;
            imprimir_mesa(vida, arma, limite_arma, japulou);
            imprimir_sala(ordem, 0, contador_sala);

            /* Verifica se pode pular */
            int pulou = 0;
            if (japulou == 0) {
                int opcao;
                printf("  ======================================== \n");
                printf("  DESEJA PULAR ESTA SALA? (1=SIM / 0=NAO):  \n");
                printf("  ======================================== \n   ");
                do {
                    /* robot/human */
                    if(player == 1) {
                        scanf("%d", &opcao);
                    } else {
                        /* retorna pular */
                        opcao = robo_pula(ordem[0], ordem[1], ordem[2], ordem[3], vida);
                        int teste1, teste2, teste3;
                        teste1 = robo_cartas(ordem[0], ordem[1], ordem[2], ordem[3], vida, arma, limite_arma, random, e1, e2, ve1, ve2, &lance_random);
                        teste2 = robo_cartas(ordem[0], ordem[1], ordem[2], ordem[3], vida, arma, limite_arma, random, e1, e2, ve1, ve2, &lance_random);
                        teste3 = robo_cartas(ordem[0], ordem[1], ordem[2], ordem[3], vida, arma, limite_arma, random, e1, e2, ve1, ve2, &lance_random);
                        if (lance_random == 1) {
                            opcao = 1;
                            lance_random = 0;
                            //printf("SALVEI\n");
                        }
                    }

                    if (opcao < 0 || opcao > 1) {
                        printf("  Entrada invalida. Digite 1 ou 0: ");
                    }
                } while (opcao < 0 || opcao > 1);

                if (opcao == 1) {
                    pular_sala(ordem, total);
                    japulou = 1;
                    pulou = 1;
                    printf("  Sala evitada! As 4 cartas foram para o fundo da \nmasmorra.\n\n");
                }
            } else {
                printf("  Voce nao pode pular duas salas seguidas.\n");
            }

            /* Se nao pulou, resolve 3 cartas */
            if (pulou == 0) {
                japulou = 0;
                japocao = 0;
                int valido = 0;

                while (valido == 0) {
                    printf("\n  =====================================================================\n");
                    printf("  Escolha 3 cartas para resolver (numeros 1 a 4, separados por espaco): \n");
                    printf("  =====================================================================\n  ");
                    /* robot/human */
                    if(player == 1) {
                        scanf("%d %d %d", &e1, &e2, &e3);
                    } else {
                        e1 = robo_cartas(ordem[0], ordem[1], ordem[2], ordem[3], vida, arma, limite_arma, random, e1, e2, ve1, ve2, &lance_random);
                        ve1 = ordem[e1-1];

                        /* randomiza */
                        do {
                            random = rand()%4+1;
                        } while(random==e1||random==e2);
                        e2 = robo_cartas(ordem[0], ordem[1], ordem[2], ordem[3], vida, arma, limite_arma, random, e1, e2, ve1, ve2, &lance_random);
                        ve2 = ordem[e2-1];

                        /* randomiza */
                        do {
                            random = rand()%4+1;
                        } while(random==e1||random==e2);
                        e3 = robo_cartas(ordem[0], ordem[1], ordem[2], ordem[3], vida, arma, limite_arma, random, e1, e2, ve1, ve2, &lance_random);
                    }
                    e1--;
                    e2--;
                    e3--; /* converte para indice 0-3 */

                    if ((e1 < 0 || e1 > 3) || (e2 < 0 || e2 > 3) || (e3 < 0 || e3 > 3) || (e1 == e2 || e1 == e3 || e2 == e3)) {
                        printf("  Escolha invalida! Use numeros de 1 a 4 sem repeticao.\n");
                    } else {
                        valido = 1;
                    }
                }

                /* Resolve cada carta na ordem escolhida */
                val_resolvido = valor_carta(ordem[e1]);

                if (ordem[e1] < 26) {
                    /* Monstro */
                    if (arma > 0 && arma_pode_atacar(limite_arma, ordem[e1])) {
                        /* Pergunta ao jogador se quer usar a arma */
                        int usar_arma;
                        printf("  Monstro %d! Voce tem arma %d equipada. Usar arma? (1=sim / 0=nao): ", val_resolvido, arma);
                        do {
                            /* robot/human */
                            if(player == 1) {
                                scanf("%d", &usar_arma);
                            } else {
                                /* retorna usar arma */
                                usar_arma = robo_arma(ordem[e1], vida);
                            }
                            if (usar_arma < 0 || usar_arma > 1) {
                                printf("  Entrada invalida. Digite 1 para sim ou 0 para nao: ");
                            }
                        } while (usar_arma < 0 || usar_arma > 1);

                        if (usar_arma == 1) {
                            vida = calcular_dano(vida, ordem[e1], arma);
                            limite_arma = atualizar_limite_arma(ordem[e1]);
                            printf("  Voce usou a arma! Dano sofrido: %d\n",
                                   val_resolvido - arma > 0 ? val_resolvido - arma : 0);
                        } else {
                            vida = calcular_dano(vida, ordem[e1], 0);
                            printf("  Voce lutou desarmado! Dano sofrido: %d\n", val_resolvido);
                        }
                    } else {
                        /* Sem arma ou arma nao pode atacar este monstro */
                        if (arma > 0) {
                            printf("  Monstro %d! Sua arma nao pode atacar este monstro (limite: %d). Lutando desarmado!\n",val_resolvido, limite_arma);
                        } else {
                            printf("  Monstro %d! Sem arma equipada. Lutando desarmado!\n", val_resolvido);
                        }
                        vida = calcular_dano(vida, ordem[e1], 0);
                        printf("  Dano sofrido: %d\n", val_resolvido);
                    }
                    /* Se morreu, morre :( */
                    if (vida <= 0) {
                        vida = 0;
                    }

                } else if (ordem[e1] < 35) {
                    /* Arma */
                    arma = valor_carta(ordem[e1]);
                    limite_arma = 0; /* nova arma, sem restricao ainda */
                    printf("  Voce equipou uma arma de valor %d!\n", arma);

                } else {
                    /* Pocao */
                    if (japocao == 0) {
                        int vida_antes = vida;
                        vida = cura(vida, ordem[e1], japocao);
                        printf("  Pocao usada! Vida restaurada de %d para %d.\n", vida_antes,
                               vida);
                        japocao = 1;
                    } else {
                        printf("  Segunda pocao no mesmo turno descartada.\n");
                    }
                }

                val_resolvido = valor_carta(ordem[e2]);

                if (ordem[e2] < 26) {
                    /* Monstro */
                    if (arma > 0 && arma_pode_atacar(limite_arma, ordem[e2])) {
                        /* Pergunta ao jogador se quer usar a arma */
                        int usar_arma;
                        printf("  Monstro %d! Voce tem arma %d equipada. Usar arma? (1=sim / 0=nao): ",val_resolvido, arma);
                        do {
                            /* robot/human */
                            if(player == 1) {
                                scanf("%d", &usar_arma);
                            } else {
                                /* retorna usar arma */
                                usar_arma = robo_arma(ordem[e2], vida);
                            }

                            if (usar_arma < 0 || usar_arma > 1) {
                                printf("  Entrada invalida. Digite 1 para sim ou 0 para nao: ");
                            }
                        } while (usar_arma < 0 || usar_arma > 1);

                        if (usar_arma == 1) {
                            vida = calcular_dano(vida, ordem[e2], arma);
                            limite_arma = atualizar_limite_arma(ordem[e2]);
                            printf("  Voce usou a arma! Dano sofrido: %d\n",
                                   val_resolvido - arma > 0 ? val_resolvido - arma : 0);
                        } else {
                            vida = calcular_dano(vida, ordem[e2], 0);
                            printf("  Voce lutou desarmado! Dano sofrido: %d\n", val_resolvido);
                        }
                    } else {
                        /* Sem arma ou arma nao pode atacar este monstro */
                        if (arma > 0) {
                            printf("  Monstro %d! Sua arma nao pode atacar este monstro (limite: %d). Lutando desarmado!\n",
                                   val_resolvido, limite_arma);
                        } else {
                            printf("  Monstro %d! Sem arma equipada. Lutando desarmado!\n", val_resolvido);
                        }
                        vida = calcular_dano(vida, ordem[e2], 0);
                        printf("  Dano sofrido: %d\n", val_resolvido);
                    }
                    /* Se morreu, morre :( */
                    if (vida <= 0) {
                        vida = 0;
                    }

                } else if (ordem[e2] < 35) {
                    /* Arma */
                    arma = valor_carta(ordem[e2]);
                    limite_arma = 0; /* nova arma, sem restricao ainda */
                    printf("  Voce equipou uma arma de valor %d!\n", arma);

                } else {
                    /* Pocao */
                    if (japocao == 0) {
                        int vida_antes = vida;
                        vida = cura(vida, ordem[e2], japocao);
                        printf("  Pocao usada! Vida restaurada de %d para %d.\n", vida_antes,
                               vida);
                        japocao = 1;
                    } else {
                        printf("  Segunda pocao no mesmo turno descartada.\n");
                    }
                }

                val_resolvido = valor_carta(ordem[e3]);

                if (ordem[e3] < 26) {
                    /* Monstro */
                    if (arma > 0 && arma_pode_atacar(limite_arma, ordem[e3])) {
                        /* Pergunta ao jogador se quer usar a arma */
                        int usar_arma;
                        printf("  Monstro %d! Voce tem arma %d equipada. Usar arma? (1=sim / 0=nao): ",val_resolvido, arma);
                        do {
                            /* robot/human */
                            if(player == 1) {
                                scanf("%d", &usar_arma);
                            } else {
                                /* retorna usar arma */
                                usar_arma = robo_arma(ordem[e3], vida);
                            }

                            if (usar_arma < 0 || usar_arma > 1) {
                                printf("  Entrada invalida. Digite 1 para sim ou 0 para nao: ");
                            }
                        } while (usar_arma < 0 || usar_arma > 1);

                        if (usar_arma == 1) {
                            vida = calcular_dano(vida, ordem[e3], arma);
                            limite_arma = atualizar_limite_arma(ordem[e3]);
                            printf("  Voce usou a arma! Dano sofrido: %d\n",
                                   val_resolvido - arma > 0 ? val_resolvido - arma : 0);
                        } else {
                            vida = calcular_dano(vida, ordem[e3], 0);
                            printf("  Voce lutou desarmado! Dano sofrido: %d\n", val_resolvido);
                        }
                    } else {
                        /* Sem arma ou arma nao pode atacar este monstro */
                        if (arma > 0) {
                            printf("  Monstro %d! Sua arma nao pode atacar este monstro (limite: %d). Lutando desarmado!\n",
                                   val_resolvido, limite_arma);
                        } else {
                            printf("  Monstro %d! Sem arma equipada. Lutando desarmado!\n", val_resolvido);
                        }
                        vida = calcular_dano(vida, ordem[e3], 0);
                        printf("  Dano sofrido: %d\n", val_resolvido);
                    }
                    /* Se morreu, morre :( */
                    if (vida <= 0) {
                        vida = 0;
                    }

                } else if (ordem[e3] < 35) {
                    /* Arma */
                    arma = valor_carta(ordem[e3]);
                    limite_arma = 0; /* nova arma, sem restricao ainda */
                    printf("  Voce equipou uma arma de valor %d!\n", arma);

                } else {
                    /* Pocao */
                    if (japocao == 0) {
                        int vida_antes = vida;
                        vida = cura(vida, ordem[e3], japocao);
                        printf("  Pocao usada! Vida restaurada de %d para %d.\n", vida_antes,
                               vida);
                        japocao = 1;
                    } else {
                        printf("  Segunda pocao no mesmo turno descartada.\n");
                    }
                }

                /* Atualiza o deck: remove as 3 cartas usadas */
                //atualizar_deck(ordem, total, e1, e2, e3);
                /* Marca as 3 escolhas como usadas (-1) */
                ordem[e1] = -1;
                ordem[e2] = -1;
                ordem[e3] = -1;

                /* Compacta o array: move validos para o inicio */
                int write = 0;
                for (int read = 0; read < total; read++) {
                    if (ordem[read] >= 0) {
                        ordem[write] = ordem[read];
                        write++;
                    }
                }
                /* Preenche o resto com -1 */
                for (int i = write; i < total; i++) {
                    ordem[i] = -1;
                }
                total = write;
            }
        }
        if(japulou==0) {
            contador_sala++;
        }
        system("clear");
        printf("\n");
    }

    /* Mensagem de fim de jogo */
    if (vida <= 0&& vida != -2) {
        printf("\n ================================================================== \n");
        printf("  GAME OVER! Seus pontos de vida chegaram a zero.\n");
        printf("  Voce foi derrotado pela Masmorra...\n");
        printf(" ================================================================== \n\n");
    }
    if(vida==-2||total<1) {
        printf("\n ================================================================== \n");
        printf("  VITORIA! Voce atravessou toda a Masmorra!\n");
        printf(" ================================================================== \n\n");
    }

    return 0;
}
