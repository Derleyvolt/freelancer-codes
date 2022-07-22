#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXN 10
#define NAVIOS 5

int mat[MAXN][MAXN];
int render_mat[MAXN][MAXN];

typedef struct Ponto {
  int x, y;
} Ponto;

typedef struct navio {
  int direction; // 1 = horizontal, 0 = vertical
  Ponto posicao;
  int tamanho;
  Ponto celulas[5];
} Navio;

Navio navios_usuario[NAVIOS];
Navio navios_maquina[NAVIOS];

int navios_tamanhos[5] = {5, 4, 3, 2};

void inicializar() {
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      render_mat[i][j] = mat[i][j] == 'B' ? '.' : mat[i][j];
    }
  }
}

int gna(int min, int max) {
  static int i = 0;
  if (i == 0) {
    srand(time(NULL));
    i++;
  }

  return min + (rand() % (max - min + 1));
}

Ponto criar_ponto(int x, int y) {
  Ponto p;
  p.x = x;
  p.y = y;
  return p;
}

Ponto generate_random_point() {
  Ponto p;
  p.x = gna(0, 9);
  p.y = gna(0, 9);
  return p;
}

void generate_cells(Navio *arg) {
  arg->celulas[0] = arg->posicao;

  for (int i = 1; i < arg->tamanho; i++) {
    if (arg->direction == 1) {
      // arg->posicao.y++;
      arg->celulas[i] = criar_ponto(arg->posicao.x, arg->celulas[i - 1].y + 1);
    } else {
      // arg->posicao.x++;
      // arg->celulas[i] = arg->posicao;
      arg->celulas[i] = criar_ponto(arg->celulas[i - 1].x + 1, arg->posicao.y);
    }
  }
}

void print_point(Ponto p) { printf("x: %d, y: %d\n", p.x, p.y); }

Navio gerar_navio(int tamanho) {
  Navio nav;

  nav.direction = gna(0, 1);
  nav.posicao = generate_random_point();
  nav.tamanho = tamanho;
  generate_cells(&nav);
  return nav;
}

int check_vality(Navio a) {
  for (int i = 0; i < a.tamanho; i++) {
    Ponto p = a.celulas[i];
    if (p.x > 9 || p.y > 9 || mat[p.x][p.y] != '.') {
      return 0;
    }
  }

  return 1;
}

void draw_navio(Navio a, char symbol) {
  for (int i = 0; i < a.tamanho; i++) {
    Ponto p = a.celulas[i];
    mat[p.x][p.y] = symbol;
  }
}

void gerar_navios_aleatorios() {
  for (int i = 0; i < 2; i++) {
    int navios_gerados = 0;
    Navio navio;
    while (navios_gerados != 4) {
      do {
        navio = gerar_navio(navios_tamanhos[navios_gerados]);
      } while (check_vality(navio) == 0);

      if (i % 2 == 0) {
        navios_usuario[navios_gerados] = navio;
      } else {
        navios_maquina[navios_gerados] = navio;
      }

      draw_navio(navio, 'A' + i);
      navios_gerados++;
    }

    printf("\n");
  }
}

void show_grade() {
  system("clear");
  printf("    ");
  for (int i = 'A'; i <= 'J'; i++) {
    printf("%c ", i);
  }

  printf("\n\n");

  for (int i = 0; i < MAXN; i++) {
    if (i + 1 < 10)
      printf("%d   ", i + 1);
    else
      printf("%d  ", i + 1);
    for (int j = 0; j < MAXN; j++) {
      printf("%c ", render_mat[i][j]);
    }
    printf("\n\n");
  }

  printf("\n\n");
}

void reset_matriz() {
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      mat[i][j] = '.';
    }
  }
}

Ponto get_position() {
  printf("Digite a posicao de tiro (Ex: A2) ");
  char input[10];
  scanf("%s", input);

  if (strlen(input) >= 2) {
    char l = input[0];

    if (l >= 'a' && l <= 'z') {
      l = l - 32;
      printf("%c\n", l);
    }

    if (l < 'A' || l > 'Z') {
      return criar_ponto(-1, -1);
    }

    char num[5];
    strcpy(num, input + 1);

    int n = atoi(num);

    if (n < 1 || n > 10) {
      return criar_ponto(-1, -1);
    }

    return criar_ponto(n - 1, l - 'A');
  } else {
    return criar_ponto(-1, -1);
  }
}

Navio *get_navio_by_point(Ponto p) {
  for (int i = 0; i < 10; i++) {
    if (i < 5) {
      Navio nav = navios_usuario[i];

      for (int j = 0; j < nav.tamanho; j++) {
        if (nav.celulas[j].x == p.x && nav.celulas[j].y == p.y) {
          return &navios_usuario[i];
        }
      }

    } else {
      Navio nav = navios_maquina[i - 5];

      for (int j = 0; j < nav.tamanho; j++) {
        if (nav.celulas[j].x == p.x && nav.celulas[j].y == p.y) {
          return &navios_maquina[i - 5];
        }
      }
    }
  }

  return NULL;
}

// garante que a maquina não destrua seus proprios navios
Ponto maquina_jogada() {
  Ponto posicoes_validas[MAXN * MAXN];

  int tam = 0;

  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if ((render_mat[i][j] == '.' || render_mat[i][j] == 'A') &&
          (mat[i][j] != 'B')) {
        posicoes_validas[tam] = criar_ponto(i, j);
        tam++;
      }
    }
  }

  return posicoes_validas[gna(0, tam - 1)];
}

int destruiu_navio(Navio *nav) {
  for (int i = 0; i < nav->tamanho; i++) {
    Ponto p = nav->celulas[i];
    if (render_mat[p.x][p.y] == '.' || render_mat[p.x][p.y] == 'A') {
      return 0;
    }
  }

  return 1;
}

void desenhar_navio_destruido(Navio *nav) {
  for (int i = 0; i < nav->tamanho; i++) {
    Ponto p = nav->celulas[i];
    render_mat[p.x][p.y] = '#';
  }
}

int pontos_jogador = 0;
int pontos_maquina = 0;

int calcular_vencedor() {
  if (pontos_jogador == 4) {
    system("clear");
    printf("O jogador eh o vencedor!\n");
    return 1;
  } else if (pontos_maquina == 4) {
    system("clear");
    printf("A maquina eh a vencedora!\n");
    return 1;
  }

  return 0;
}

void ponto_pra_sistema_letra_numero(Ponto p, char coord[10]) {
  coord[0] = 'A' + p.y;
  if (p.x > 8) {
    coord[1] = '1';
    coord[2] = '0';
    coord[3] = 0;
  } else {
    coord[1] = '1' + p.x;
    coord[2] = 0;
  }
}

int draw_screen() {
  show_grade();

  if (calcular_vencedor()) {
    return 1;
  }

  printf("PONTOS MAQUINA: %d\n", pontos_maquina);
  printf("PONTOS JOGADOR: %d\n\n", pontos_jogador);

  return 0;
}

int main() {
  reset_matriz();
  gerar_navios_aleatorios();
  inicializar();

  int vez = 0;
  Ponto p;

  for (;;) {
    if (vez % 2 == 0) {
      for (int j = 0; j < 3; j++) {
        if (draw_screen()) {
          return 0;
        }
        for (;;) {
          printf("VEZ DO HUMANO\n\n");
          p = get_position();
          getchar();
          if (p.x == -1) {
            printf("Voce digitou uma posicao invalida, tente novamente\n");
            getchar();
            show_grade();
          } else {
            break;
          }
        }

        Navio *nav = get_navio_by_point(p);

        if (nav == NULL) {
          printf("AGUA\n");
          render_mat[p.x][p.y] = 'o';
        } else {
          render_mat[p.x][p.y] = 'X';
          if (destruiu_navio(nav) == 1) {
            printf("AFUNDOU\n");
            desenhar_navio_destruido(nav);
            pontos_jogador++;
          } else {
            printf("FOGO");
          }
        }

        getchar();
      }
      vez++;
    } else {
	   char cd[3][10];
      for (int j = 0; j < 3; j++) {
        if (draw_screen()) {
          return 0;
        }
        printf("VEZ DA MAQUINA JOGAR\n\n");
        p = maquina_jogada();

        char coord[10];

        ponto_pra_sistema_letra_numero(p, cd[j]);

        //printf("JOGADA: %s\n\n", coord);

        Navio *nav = get_navio_by_point(p);

        if (nav == NULL) {
          printf("\nAGUA\n");
          render_mat[p.x][p.y] = 'o';
        } else {
          render_mat[p.x][p.y] = 'X';
          if (destruiu_navio(nav) == 1) {
            printf("\nAFUNDOU\n");
            desenhar_navio_destruido(nav);
            pontos_maquina++;
          } else {
            printf("\nFOGO");
          }
        }
      }

	  printf("JOGADAS DA MAQUINA\n");
	  for(int k = 0; k < 3; k++) {
		  printf("%s\n", cd[k]);
	  }
	  getchar();
      vez++;
    }
  }

  return 0;
}
