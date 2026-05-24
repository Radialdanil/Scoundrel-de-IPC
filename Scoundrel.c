
/*
 * Integrantes do Grupo: Danilo Viveiros de Assis       NUSP:
 *                       Joao Victor Gonzaga de Sousa   NUSP:
 * Disciplina: SME0230 - IPC
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================================
 * INDICE DE CARTAS NO ARRAY 'ordem[44]':
 *  0 - 12  : Monstros de Paus  (valores 1 a 13, onde 11=J, 12=Q, 13=K)
 * 13 - 25  : Monstros de Espadas (valores 1 a 13)
 * 26 - 34  : Armas de Ouros    (valores 2 a 10)
 * 35 - 43  : Pocoes de Copas   (valores 2 a 10)
 * =========================================================================
 */

/* Permutacao aleatoria (Fisher-Yates) */
void randomize(int ordem[], int n) {
    int a, b, temp;
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        //swap(&ordem[i], &ordem[j]);
        a = ordem[i];
        b = ordem[j];
        temp = a;
        a = b;
        b = temp;
        ordem[i]=a;
        ordem[j]=b;
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

/* Retorna o simbolo ASCII do naipe */
char simbolo_naipe(int indice) {
    if (indice < 13)
        return 'P';
    if (indice < 26)
        return 'E';
    if (indice < 35)
        return 'O';
    return 'C';
}

/* Retorna a string do valor para exibicao (1->A nao existe aqui, 11->J, etc.)
 */
void str_valor(int val, char buf[]) {
    if (val == 11) {
        buf[0] = 'J';
        buf[1] = '\0';
    } else if (val == 12) {
        buf[0] = 'Q';
        buf[1] = '\0';
    } else if (val == 13) {
        buf[0] = 'K';
        buf[1] = '\0';
    } else if (val == 14) {
        buf[0] = 'A';
        buf[1] = '\0';
    } else if (val == 10) {
        buf[0] = '1';
        buf[1] = '0';
        buf[2] = '\0';
    } else {
        buf[0] = '0' + val;
        buf[1] = '\0';
    }
    return;
}

/* Imprime a tela de titulo em ASCII Art */
void imprimir_titulo(void) {
    printf("\n");

    printf("  #####    #####   ####   ##  ##  ##  ##  #####   #####   ######  ##  "
           "  \n");
    printf(" ##      ##       ##  ##  ##  ##  ### ##  ##  ##  ##  ##  ##      ##    "
           "\n");
    printf("  ####   ##       ##  ##  ##  ##  ######  ##  ##  #####   ####    ##    "
           "\n");
    printf("     ##  ##       ##  ##  ##  ##  ## ###  ##  ##  ## ##   ##      ##    "
           "\n");
    printf(" #####     #####   ####    ####   ##  ##  #####   ##  ##  ######  "
           "######\n");
    printf("\n");
    printf("\n");
    return;
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
    /* Carta invalida */
    else {
        if (linha == 0)
            printf("+----------------+");
        else if (linha == 11)
            printf("+----------------+");
        else
            printf("|   [  ???  ]    |");
    }
    return;
}

/* Imprime a sala de 4 cartas lado a lado com legenda numerada */
void imprimir_sala(int ordem[], int ini, int c_sala) {
    printf("\n  --- SALA %d/14 ---\n\n", c_sala);
    printf(
        "  Carta 1             Carta 2             Carta 3             Carta 4\n");

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
int cura(int vida, int indice_pocao) {
    int recuperacao = indice_pocao - 33;
    vida = vida + recuperacao;
    if (vida > 20) {
        vida = 20;
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
    printf(
        " ================================================================== \n");
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
        printf(
            "  Aviso         : Voce pulou a ultima sala. NAO pode pular esta.\n");
    } else {
        printf("  Aviso         : Voce PODE pular esta sala.\n");
    }
    printf(
        " ================================================================== \n");
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

int main(void) {
    int ordem[44];
    int vida = 20;
    int arma = 0;        /* valor da arma equipada (0 = nenhuma) */
    int limite_arma = 0; /* valor do ultimo monstro derrotado pela arma */
    int japulou = 0;     /* 1 se pulou a sala anterior */
    int japocao = 0;     /* 1 se ja usou pocao neste turno */
    int total = 44;      /* total de cartas ainda no deck */
    int val;
    int contador_sala = 1;

    /* Inicializa deck de 0 a 43 */
    for (int i = 0; i < 44; i++) {
        ordem[i] = i;
    }
    randomize(ordem, total);

    /* Loop principal: roda enquanto ha cartas e o jogador esta vivo */
    while (vida > 0 && total >= 1) {

        /* Garante que ha pelo menos 4 cartas para formar a sala */
        if (total < 4) {
            printf("\n  Masmorra esgotada! Voce venceu!\n");
            vida = -2; /* sinaliza saida do loop sem morte */
        }

        if (vida > 0 && total >= 4) {
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
                    scanf("%d", &opcao);
                    if (opcao < 0 || opcao > 1) {
                        printf("  Entrada invalida. Digite 1 ou 0: ");
                    }
                } while (opcao < 0 || opcao > 1);

                if (opcao == 1) {
                    pular_sala(ordem, total);
                    japulou = 1;
                    pulou = 1;
                    printf("  Sala evitada! As 4 cartas foram para o fundo da "
                           "masmorra.\n\n");
                }
            } else {
                printf("  Voce nao pode pular duas salas seguidas.\n");
            }

            /* Se nao pulou, resolve 3 cartas */
            if (pulou == 0) {
                japulou = 0;
                japocao = 0;

                int e1, e2, e3;
                int valido = 0;

                while (valido == 0) {
                    printf("\n  =====================================================================\n");
                    printf("  Escolha 3 cartas para resolver (numeros 1 a 4, separados por espaco): \n");
                    printf("  =====================================================================\n  ");
                    scanf("%d %d %d", &e1, &e2, &e3);
                    e1--;
                    e2--;
                    e3--; /* converte para indice 0-3 */

                    if ((e1 < 0 || e1 > 3) || (e2 < 0 || e2 > 3) || (e3 < 0 || e3 > 3) ||
                            (e1 == e2 || e1 == e3 || e2 == e3)) {
                        printf("  Escolha invalida! Use numeros de 1 a 4 sem repeticao.\n");
                    } else {
                        valido = 1;
                    }
                }

                /* Resolve cada carta na ordem escolhida */
                val = valor_carta(ordem[e1]);

                if (ordem[e1] < 26) {
                    /* Monstro */
                    if (arma > 0 && arma_pode_atacar(limite_arma, ordem[e1])) {
                        /* Pergunta ao jogador se quer usar a arma */
                        int usar_arma;
                        printf("  Monstro %d! Voce tem arma %d equipada. Usar arma? (1=sim / "
                               "0=nao): ",
                               val, arma);
                        do {
                            scanf("%d", &usar_arma);
                            if (usar_arma < 0 || usar_arma > 1) {
                                printf("  Entrada invalida. Digite 1 para sim ou 0 para nao: ");
                            }
                        } while (usar_arma < 0 || usar_arma > 1);

                        if (usar_arma == 1) {
                            vida = calcular_dano(vida, ordem[e1], arma);
                            limite_arma = atualizar_limite_arma(ordem[e1]);
                            printf("  Voce usou a arma! Dano sofrido: %d\n",
                                   val - arma > 0 ? val - arma : 0);
                        } else {
                            vida = calcular_dano(vida, ordem[e1], 0);
                            printf("  Voce lutou desarmado! Dano sofrido: %d\n", val);
                        }
                    } else {
                        /* Sem arma ou arma nao pode atacar este monstro */
                        if (arma > 0) {
                            printf(
                                "  Monstro %d! Sua arma nao pode atacar este monstro (limite: %d). "
                                "Lutando desarmado!\n",
                                val, limite_arma);
                        } else {
                            printf("  Monstro %d! Sem arma equipada. Lutando desarmado!\n", val);
                        }
                        vida = calcular_dano(vida, ordem[e1], 0);
                        printf("  Dano sofrido: %d\n", val);
                    }

                    if (vida <= 0) {
                        vida = 0;
                        break;
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
                        vida = cura(vida, ordem[e1]);
                        printf("  Pocao usada! Vida restaurada de %d para %d.\n", vida_antes,
                               vida);
                        japocao = 1;
                    } else {
                        printf("  Segunda pocao no mesmo turno descartada.\n");
                    }
                }

                val = valor_carta(ordem[e2]);

                if (ordem[e2] < 26) {
                    /* Monstro */
                    if (arma > 0 && arma_pode_atacar(limite_arma, ordem[e2])) {
                        /* Pergunta ao jogador se quer usar a arma */
                        int usar_arma;
                        printf("  Monstro %d! Voce tem arma %d equipada. Usar arma? (1=sim / "
                               "0=nao): ",
                               val, arma);
                        do {
                            scanf("%d", &usar_arma);
                            if (usar_arma < 0 || usar_arma > 1) {
                                printf("  Entrada invalida. Digite 1 para sim ou 0 para nao: ");
                            }
                        } while (usar_arma < 0 || usar_arma > 1);

                        if (usar_arma == 1) {
                            vida = calcular_dano(vida, ordem[e2], arma);
                            limite_arma = atualizar_limite_arma(ordem[e2]);
                            printf("  Voce usou a arma! Dano sofrido: %d\n",
                                   val - arma > 0 ? val - arma : 0);
                        } else {
                            vida = calcular_dano(vida, ordem[e2], 0);
                            printf("  Voce lutou desarmado! Dano sofrido: %d\n", val);
                        }
                    } else {
                        /* Sem arma ou arma nao pode atacar este monstro */
                        if (arma > 0) {
                            printf(
                                "  Monstro %d! Sua arma nao pode atacar este monstro (limite: %d). "
                                "Lutando desarmado!\n",
                                val, limite_arma);
                        } else {
                            printf("  Monstro %d! Sem arma equipada. Lutando desarmado!\n", val);
                        }
                        vida = calcular_dano(vida, ordem[e2], 0);
                        printf("  Dano sofrido: %d\n", val);
                    }

                    if (vida <= 0) {
                        vida = 0;
                        break;
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
                        vida = cura(vida, ordem[e2]);
                        printf("  Pocao usada! Vida restaurada de %d para %d.\n", vida_antes,
                               vida);
                        japocao = 1;
                    } else {
                        printf("  Segunda pocao no mesmo turno descartada.\n");
                    }
                }

                val = valor_carta(ordem[e3]);

                if (ordem[e3] < 26) {
                    /* Monstro */
                    if (arma > 0 && arma_pode_atacar(limite_arma, ordem[e3])) {
                        /* Pergunta ao jogador se quer usar a arma */
                        int usar_arma;
                        printf("  Monstro %d! Voce tem arma %d equipada. Usar arma? (1=sim / "
                               "0=nao): ",
                               val, arma);
                        do {
                            scanf("%d", &usar_arma);
                            if (usar_arma < 0 || usar_arma > 1) {
                                printf("  Entrada invalida. Digite 1 para sim ou 0 para nao: ");
                            }
                        } while (usar_arma < 0 || usar_arma > 1);

                        if (usar_arma == 1) {
                            vida = calcular_dano(vida, ordem[e3], arma);
                            limite_arma = atualizar_limite_arma(ordem[e3]);
                            printf("  Voce usou a arma! Dano sofrido: %d\n",
                                   val - arma > 0 ? val - arma : 0);
                        } else {
                            vida = calcular_dano(vida, ordem[e3], 0);
                            printf("  Voce lutou desarmado! Dano sofrido: %d\n", val);
                        }
                    } else {
                        /* Sem arma ou arma nao pode atacar este monstro */
                        if (arma > 0) {
                            printf(
                                "  Monstro %d! Sua arma nao pode atacar este monstro (limite: %d). "
                                "Lutando desarmado!\n",
                                val, limite_arma);
                        } else {
                            printf("  Monstro %d! Sem arma equipada. Lutando desarmado!\n", val);
                        }
                        vida = calcular_dano(vida, ordem[e3], 0);
                        printf("  Dano sofrido: %d\n", val);
                    }

                    if (vida <= 0) {
                        vida = 0;
                        break;
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
                        vida = cura(vida, ordem[e3]);
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
        system("cls");
        printf("\n");
    }

    /* Mensagem de fim de jogo */
    if (vida <= 0) {
        printf(
            "\n ================================================================== "
            "\n");
        printf("  GAME OVER! Seus pontos de vida chegaram a zero.\n");
        printf("  Voce foi derrotado pela Masmorra...\n");
        printf(" =================================================================="
               " \n\n");
    }
    if(vida==-2||total<1) {
        printf(
            "\n ================================================================== "
            "\n");
        printf("  VITORIA! Voce atravessou toda a Masmorra!\n");
        printf("  Pontos de vida restantes: %d\n", vida);
        printf(" =================================================================="
               " \n\n");
    }

    return 0;
}
