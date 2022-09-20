#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//CORES TOTAL
#define RESET "\e[0m"
#define RED "\e[41;31m"
#define GREEN "\e[42;32m"
#define YELLOW "\e[43;33m"
#define BLUE "\e[44;34m"
#define WHITE "\e[47;37m"
#define BLACK "\e[40;30m"
#define PURPLE "\e[45;35m"

//CORES TEXTO
#define RED_T "\e[0;31m"
#define GREEN_T "\e[0;32m"
#define YELLOW_T "\e[0;33m"
#define BLUE_T "\e[0;34m"

//CORES FUNDO
#define RED_F "\e[41m"
#define GREEN_F "\e[42m"
#define YELLOW_F "\e[43m"
#define BLUE_F "\e[44m"

//STRUCT DOS PEÕES
typedef struct peao
{
  int peao[5];
  int loop_t[5];
  int trava_win[5];
  int trava_peao[5];
  int trava_inicio;
  int vitoria;
  int trava_player;
}peao;

//FUNÇÕES
int inicio_menu();
int quantidade();
void tabuleiro();
void define();
void location();
void mini_menu();
void comer();

///////////////////////////////////////////////////////////////////////////////
int main()
{
  peao cor[5];
  int jogadores=2, escolha, loop=1,win[5]={0,0,0,0,0};
  define(cor);

  //TABULEIRO
  int tab[15][15]={83,83,83,83,83,83,46,47,48,93,93,93,93,93,93,
                   83,83,83,83,83,83,45,94,49,93,93,93,93,93,93,
                   83,83,-33,-30,83,83,44,95,50,93,93,-43,-40,93,93,
                   83,83,-31,-32,83,83,43,96,51,93,93,-41,-42,93,93,
                   83,83,83,83,83,83,42,97,52,93,93,93,93,93,93,
                   83,83,83,83,83,83,41,98,53,93,93,93,93,93,93,
                   35,36,37,38,39,40,62,99,62,54,55,56,57,58,59,
                   34,84,85,86,87,88,89,62,69,68,67,66,65,64,60,
                   33,32,31,30,29,28,62,79,62,14,13,12,11,10,61,
                   73,73,73,73,73,73,27,78,15,63,63,63,63,63,63,
                   73,73,73,73,73,73,26,77,16,63,63,63,63,63,63,
                   73,73,-23,-20,73,73,25,76,17,63,63,-13,-10,63,63,
                   73,73,-21,-22,73,73,24,75,18,63,63,-11,-12,63,63,
                   73,73,73,73,73,73,23,74,19,63,63,63,63,63,63,
                   73,73,73,73,73,73,22,21,20,63,63,63,63,63,63};


  //TELA INICIAL
  while(loop==1)
  {
    escolha=inicio_menu(jogadores);
    switch(escolha)
    {
      case 0: exit(1); break;
      case 1: loop=0; system("cls"); break;
      case 2: system("cls"); jogadores=quantidade(); break;
      default: system("cls"); printf(RED_T "VALOR INVALIDO\n" RESET); system("pause"); system("cls"); break;
    }
  }

//JOGO

int player=1,confirm,i=1,block_selc[4]={1,1,1,1},seis_repeat[4]={1,1,1,1},trava_azul=0,selc,jogo=1;

while(jogo==1)
{
  cor[player].trava_player=0;
  tabuleiro(tab,cor);

  //MENU DE JOGADORES
  int dado;

  i=1;
  while(i==1)
  {
    mini_menu (block_selc,win,player);

    printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
    scanf("%i",&confirm);

    switch(confirm)
    {
      case 1: srand(time(NULL)); dado=(rand()%6)+1; i=0; printf(BLUE_T "\nDADO: %i\n" RESET,dado); break;
      default: printf(RED_T "VALOR INVALIDO\n" RESET); system("pause"); system("cls"); tabuleiro(tab,cor); break;
    }
  }

  location(cor,player,tab,dado,block_selc,seis_repeat,win,trava_azul,confirm,selc);

  if(win[player]==4)
  {
    jogo=0;
  }

  //TROCA DE PLAYER
  if (win[player]!=4)
  {
    if(cor[player].trava_player==0)
    { cor[player].trava_player=1;
      player++;

      if(player>jogadores)
      {
        player=1;
      }
    }
  }

  system("pause");
  system("cls");
}

  system("cls");
  printf("PLAYER %i VENCEU!!!!\n",player);
  system("pause");

  return 0;
}
///////////////////////////////////////////////////////////////////////////////

//MENU DA TELA INICIAL
int inicio_menu(int jogadores)
{
  system("cls");
  int escolha;
  printf("-----LUDO-----\n");
  printf("AVISSO!! - USE APENAS NUMEROS PARA JOGAR\n\n");
  printf(BLUE_T "JOGADORES ATUAIS - %i\n\n" RESET,jogadores);
  printf(RED_T "(0) SAIR\n" RESET);
  printf(GREEN_T "(1) INICIAR\n" RESET);
  printf(YELLOW_T  "(2) QUANTIDADE DE JOGADORES\n" RESET);
  scanf("%i",&escolha);

  return escolha;
}

//QUANTIDADE DE JOGADORES
int quantidade()
{
  int jogadores;

  while(1)
  {
    printf(YELLOW_T "QUANTAS PESSOAS IRAO JOGAR:\n" RESET);
    scanf("%i",&jogadores);

    if(jogadores==2 || jogadores==3 || jogadores==4)
    {
      system("cls");
      return jogadores;
    }

    else
    {
      printf(RED_T "VALOR DE JOGADORES INVALIDO\n" RESET); system("pause"); system("cls");
    }
  }
}

//CRIAÇÃO DO TABULEIRO
void tabuleiro(int tab[][15],peao cor[])
{
  int count=0;

  for(int i=0; i<15; i++)
  {
    for(int j=0; j<15; j++)
    {
      //AZUL
      if(tab[i][j]==10 || tab[i][j]==63 || tab[i][j]>63 && tab[i][j]<70)
      {
        if(tab[i][j]==cor[1].peao[1])
        {
          printf(BLUE_F "P1" RESET);
        }

        else if(tab[i][j]==cor[1].peao[2])
        {
          printf(BLUE_F "P2" RESET);
        }

        else if(tab[i][j]==cor[1].peao[3])
        {
          printf(BLUE_F "P3" RESET);
        }

        else if(tab[i][j]==cor[1].peao[4])
        {
          printf(BLUE_F "P4" RESET);
        }

        else if(tab[i][j]==cor[2].peao[1])
        {
          printf(RED_F "P1" RESET);
        }

        else if(tab[i][j]==cor[2].peao[2])
        {
          printf(RED_F "P2" RESET);
        }

        else if(tab[i][j]==cor[2].peao[3])
        {
          printf(RED_F "P3" RESET);
        }

        else if(tab[i][j]==cor[2].peao[4])
        {
          printf(RED_F "P4" RESET);
        }

        else if(tab[i][j]==cor[3].peao[1])
        {
          printf(GREEN_F "P1" RESET);
        }

        else if(tab[i][j]==cor[3].peao[2])
        {
          printf(GREEN_F "P2" RESET);
        }

        else if(tab[i][j]==cor[3].peao[3])
        {
          printf(GREEN_F "P3" RESET);
        }

        else if(tab[i][j]==cor[3].peao[4])
        {
          printf(GREEN_F "P4" RESET);
        }

        else if(tab[i][j]==cor[4].peao[1])
        {
          printf(YELLOW_F "P1" RESET);
        }

        else if(tab[i][j]==cor[4].peao[2])
        {
          printf(YELLOW_F "P2" RESET);
        }

        else if(tab[i][j]==cor[4].peao[3])
        {
          printf(YELLOW_F "P3" RESET);
        }

        else if(tab[i][j]==cor[4].peao[4])
        {
          printf(YELLOW_F "P4" RESET);
        }

        else
        {
          printf(BLUE "%i" RESET, tab[i][j]);
        }

        count++;
      }

      //VERMELHO
      else if(tab[i][j]==23 || tab[i][j]==73 || tab[i][j]>73 && tab[i][j]<80)
      {
        if(tab[i][j]==cor[1].peao[1])
        {
          printf(BLUE_F "P1" RESET);
        }

        else if(tab[i][j]==cor[1].peao[2])
        {
          printf(BLUE_F "P2" RESET);
        }

        else if(tab[i][j]==cor[1].peao[3])
        {
          printf(BLUE_F "P3" RESET);
        }

        else if(tab[i][j]==cor[1].peao[4])
        {
          printf(BLUE_F "P4" RESET);
        }

        else if(tab[i][j]==cor[2].peao[1])
        {
          printf(RED_F "P1" RESET);
        }

        else if(tab[i][j]==cor[2].peao[2])
        {
          printf(RED_F "P2" RESET);
        }

        else if(tab[i][j]==cor[2].peao[3])
        {
          printf(RED_F "P3" RESET);
        }

        else if(tab[i][j]==cor[2].peao[4])
        {
          printf(RED_F "P4" RESET);
        }

        else if(tab[i][j]==cor[3].peao[1])
        {
          printf(GREEN_F "P1" RESET);
        }

        else if(tab[i][j]==cor[3].peao[2])
        {
          printf(GREEN_F "P2" RESET);
        }

        else if(tab[i][j]==cor[3].peao[3])
        {
          printf(GREEN_F "P3" RESET);
        }

        else if(tab[i][j]==cor[3].peao[4])
        {
          printf(GREEN_F "P4" RESET);
        }

        else if(tab[i][j]==cor[4].peao[1])
        {
          printf(YELLOW_F "P1" RESET);
        }

        else if(tab[i][j]==cor[4].peao[2])
        {
          printf(YELLOW_F "P2" RESET);
        }

        else if(tab[i][j]==cor[4].peao[3])
        {
          printf(YELLOW_F "P3" RESET);
        }

        else if(tab[i][j]==cor[4].peao[4])
        {
          printf(YELLOW_F "P4" RESET);
        }

        else
        {
          printf(RED "%i" RESET, tab[i][j]);
        }

        count++;
      }

      //VERDE
      else if(tab[i][j]==36 || tab[i][j]==83 || tab[i][j]>83 && tab[i][j]<90)
      {
        if(tab[i][j]==cor[1].peao[1])
        {
          printf(BLUE_F "P1" RESET);
        }

        else if(tab[i][j]==cor[1].peao[2])
        {
          printf(BLUE_F "P2" RESET);
        }

        else if(tab[i][j]==cor[1].peao[3])
        {
          printf(BLUE_F "P3" RESET);
        }

        else if(tab[i][j]==cor[1].peao[4])
        {
          printf(BLUE_F "P4" RESET);
        }

        else if(tab[i][j]==cor[2].peao[1])
        {
          printf(RED_F "P1" RESET);
        }

        else if(tab[i][j]==cor[2].peao[2])
        {
          printf(RED_F "P2" RESET);
        }

        else if(tab[i][j]==cor[2].peao[3])
        {
          printf(RED_F "P3" RESET);
        }

        else if(tab[i][j]==cor[2].peao[4])
        {
          printf(RED_F "P4" RESET);
        }

        else if(tab[i][j]==cor[3].peao[1])
        {
          printf(GREEN_F "P1" RESET);
        }

        else if(tab[i][j]==cor[3].peao[2])
        {
          printf(GREEN_F "P2" RESET);
        }

        else if(tab[i][j]==cor[3].peao[3])
        {
          printf(GREEN_F "P3" RESET);
        }

        else if(tab[i][j]==cor[3].peao[4])
        {
          printf(GREEN_F "P4" RESET);
        }

        else if(tab[i][j]==cor[4].peao[1])
        {
          printf(YELLOW_F "P1" RESET);
        }

        else if(tab[i][j]==cor[4].peao[2])
        {
          printf(YELLOW_F "P2" RESET);
        }

        else if(tab[i][j]==cor[4].peao[3])
        {
          printf(YELLOW_F "P3" RESET);
        }

        else if(tab[i][j]==cor[4].peao[4])
        {
          printf(YELLOW_F "P4" RESET);
        }

        else
        {
          printf(GREEN "%i" RESET, tab[i][j]);
        }

        count++;
      }

      //AMARELO
      else if(tab[i][j]==49 || tab[i][j]==93 || tab[i][j]>93 && tab[i][j]<100)
      {
        if(tab[i][j]==cor[1].peao[1])
        {
          printf(BLUE_F "P1" RESET);
        }

        else if(tab[i][j]==cor[1].peao[2])
        {
          printf(BLUE_F "P2" RESET);
        }

        else if(tab[i][j]==cor[1].peao[3])
        {
          printf(BLUE_F "P3" RESET);
        }

        else if(tab[i][j]==cor[1].peao[4])
        {
          printf(BLUE_F "P4" RESET);
        }

        else if(tab[i][j]==cor[2].peao[1])
        {
          printf(RED_F "P1" RESET);
        }

        else if(tab[i][j]==cor[2].peao[2])
        {
          printf(RED_F "P2" RESET);
        }

        else if(tab[i][j]==cor[2].peao[3])
        {
          printf(RED_F "P3" RESET);
        }

        else if(tab[i][j]==cor[2].peao[4])
        {
          printf(RED_F "P4" RESET);
        }

        else if(tab[i][j]==cor[3].peao[1])
        {
          printf(GREEN_F "P1" RESET);
        }

        else if(tab[i][j]==cor[3].peao[2])
        {
          printf(GREEN_F "P2" RESET);
        }

        else if(tab[i][j]==cor[3].peao[3])
        {
          printf(GREEN_F "P3" RESET);
        }

        else if(tab[i][j]==cor[3].peao[4])
        {
          printf(GREEN_F "P4" RESET);
        }

        else if(tab[i][j]==cor[4].peao[1])
        {
          printf(YELLOW_F "P1" RESET);
        }

        else if(tab[i][j]==cor[4].peao[2])
        {
          printf(YELLOW_F "P2" RESET);
        }

        else if(tab[i][j]==cor[4].peao[3])
        {
          printf(YELLOW_F "P3" RESET);
        }

        else if(tab[i][j]==cor[4].peao[4])
        {
          printf(YELLOW_F "P4" RESET);
        }

        else
        {
          printf(YELLOW "%i" RESET, tab[i][j]);
        }

        count++;
      }

      //GERAL
      else
      {
        if(tab[i][j]==cor[1].peao[1])
        {
          printf(BLUE_F "P1" RESET);
        }

        else if(tab[i][j]==cor[1].peao[2])
        {
          printf(BLUE_F "P2" RESET);
        }

        else if(tab[i][j]==cor[1].peao[3])
        {
          printf(BLUE_F "P3" RESET);
        }

        else if(tab[i][j]==cor[1].peao[4])
        {
          printf(BLUE_F "P4" RESET);
        }

        else if(tab[i][j]==cor[2].peao[1])
        {
          printf(RED_F "P1" RESET);
        }

        else if(tab[i][j]==cor[2].peao[2])
        {
          printf(RED_F "P2" RESET);
        }

        else if(tab[i][j]==cor[2].peao[3])
        {
          printf(RED_F "P3" RESET);
        }

        else if(tab[i][j]==cor[2].peao[4])
        {
          printf(RED_F "P4" RESET);
        }

        else if(tab[i][j]==cor[3].peao[1])
        {
          printf(GREEN_F "P1" RESET);
        }

        else if(tab[i][j]==cor[3].peao[2])
        {
          printf(GREEN_F "P2" RESET);
        }

        else if(tab[i][j]==cor[3].peao[3])
        {
          printf(GREEN_F "P3" RESET);
        }

        else if(tab[i][j]==cor[3].peao[4])
        {
          printf(GREEN_F "P4" RESET);
        }

        else if(tab[i][j]==cor[4].peao[1])
        {
          printf(YELLOW_F "P1" RESET);
        }

        else if(tab[i][j]==cor[4].peao[2])
        {
          printf(YELLOW_F "P2" RESET);
        }

        else if(tab[i][j]==cor[4].peao[3])
        {
          printf(YELLOW_F "P3" RESET);
        }

        else if(tab[i][j]==cor[4].peao[4])
        {
          printf(YELLOW_F "P4" RESET);
        }

        else if(tab[i][j]==62)
        {
          printf(BLACK "%i" RESET, tab[i][j]);
        }

        else if(tab[i][j]==57 || tab[i][j]==18 || tab[i][j]==31 || tab[i][j]==44)
        {
          printf(PURPLE "%i" RESET, tab[i][j]);
        }

        else if(tab[i][j]<0)
        {
          printf(WHITE "P0" RESET, tab[i][j]);
        }

        else
        {
          printf(WHITE "%i" RESET, tab[i][j]);
        }

        count++;
      }

      //LINHAS
      if (count==15)
      {
        printf("\n");
        count=0;
      }
    }
  }
}

//SETA OS VALORES DOS PEOES
void define(peao cor[])
{
  int count=1;

  cor[1].peao[1]=-13;
  cor[1].peao[2]=-10;
  cor[1].peao[3]=-11;
  cor[1].peao[4]=-12;

  cor[2].peao[1]=-23;
  cor[2].peao[2]=-20;
  cor[2].peao[3]=-21;
  cor[2].peao[4]=-22;

  cor[3].peao[1]=-33;
  cor[3].peao[2]=-30;
  cor[3].peao[3]=-31;
  cor[3].peao[4]=-32;

  cor[4].peao[1]=-43;
  cor[4].peao[2]=-40;
  cor[4].peao[3]=-41;
  cor[4].peao[4]=-42;

  //RESET DE LOOP
  for(int i=1; i<5; i++)
  {
    for(int j=1; j<5; j++)
    {
      cor[i].loop_t[j]=0;
      cor[i].trava_win[j]=0;
      cor[i].trava_peao[j]=1;
      cor[i].trava_inicio=0;
    }
  }
}

//GERA OS PEOES NOVOS
void location(peao cor[],int player,int tab[][15],int dado,int block_selc[],int seis_repeat[],int win[],int trava_azul,int confirm,int selc)
{
  int i;

  //SELECAO DO JOGADOR
  i=1;

  //AZUL
  if(player==1)
  {
    if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
    {
      cor[player].trava_inicio=0;
    }

    int duas=0,seis_c=0;
    //LIBERAR PEAO NOVO
    while(i==1)
    {
      if(dado==6 && seis_repeat[0]<5 && seis_c<3)
      {
        for(int j=1; j<5; j++)
        {
          if (cor[1].peao[j]<0)
          {
            cor[1].peao[j]=10; cor[player].trava_peao[j]=0; break;
          }
        }

        block_selc[0]++;
        seis_repeat[0]++;
        seis_c++;

        if(duas==0)
        {
          printf(GREEN_T "PEAO LIBERADO\n" RESET);
          cor[player].trava_inicio=1;
          system("pause"); system("cls");
        }

        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        srand(time(NULL)); dado=(rand()%6)+1;
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);

        if(dado==6)
        {
          i=1; duas++;
          printf(GREEN_T "PEAO LIBERADO\n" RESET); system("pause"); system("cls");
        }
      }

      else if(dado==6 && duas>0)
      {
        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);

        i=0;
        duas=0;
        seis_c++;
      }

      else
      {
        i=0;
        duas=0;
      }
    }

    //DADO
    int loop2=0;

    if(cor[player].trava_inicio==1 && seis_c<3)
    {
      while(loop2==0)
      {
        printf(RED_T "SELECIONE O PEAO:\n" RESET);
        scanf("%i",&selc);

        loop2=0;

        if(cor[player].trava_peao[selc]==0)
        {
          cor[player].peao[selc]+=dado; loop2=1;
          comer(player,cor,selc,block_selc,seis_repeat);

          if(cor[1].peao[selc]>=70)
          {
            loop2=0;
            cor[1].peao[selc]-=dado;
            printf(RED_T "PEAO INVALIDO\n" RESET);
            cor[player].trava_peao[selc]=1;

            if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
            {
              loop2=1;
            }
            else
            {
              system("pause"); system("cls");
              tabuleiro(tab,cor);
              mini_menu(block_selc,win,player);
              printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
              printf("%i\n",confirm);
              printf(BLUE_T "\nDADO: %i\n" RESET,dado);
            }
            cor[player].trava_peao[selc]=0;
          }
        }
        else
        {
          printf(RED_T "PEAO INVALIDO\n" RESET);
          system("pause"); system("cls");
          tabuleiro(tab,cor);
          mini_menu(block_selc,win,player);
          printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
          printf("%i\n",confirm);
          printf(BLUE_T "\nDADO: %i\n" RESET,dado);
        }
      }

      //LINHA MEIO
      int n_dado;
      if(cor[1].peao[selc]>60 && cor[1].peao[selc]<67 && trava_azul==0)
      {
        n_dado=cor[1].peao[selc]-60;
        cor[1].peao[selc]=63+n_dado;
        trava_azul=1;
      }

      if(cor[1].peao[selc]==69 && cor[1].trava_win[selc]==0)
      {
        win[1]++;
        cor[1].trava_peao[selc]++;
        cor[1].trava_win[selc]++;
        cor[player].trava_player=1;
      }
    }

    else
    {
      printf(RED_T "PROXIMO TURNO\n" RESET);
    }

  }
  //VERMELHO
  if(player==2)
  {
    if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
    {
      cor[player].trava_inicio=0;
    }

    int duas=0,seis_c=0;
    //LIBERAR PEAO NOVO
    while(i==1)
    {
      if(dado==6 && seis_repeat[1]<5 && seis_c<3)
      {
        for(int j=1; j<5; j++)
        {
          if (cor[2].peao[j]<0)
          {
            cor[2].peao[j]=23; cor[player].trava_peao[j]=0; break;
          }
        }

        block_selc[1]++;
        seis_repeat[1]++;
        seis_c++;

        if(duas==0)
        {
          printf(GREEN_T "PEAO LIBERADO\n" RESET);
          cor[player].trava_inicio=1;
          system("pause"); system("cls");
        }

        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        srand(time(NULL)); dado=(rand()%6)+1;
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);


        if(dado==6)
        {
          i=1; duas++;
          printf(GREEN_T "PEAO LIBERADO\n" RESET); system("pause"); system("cls");
        }
      }

      else if(dado==6 && duas>0)
      {
        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);

        i=0;
        duas=0;
        seis_c++;
      }

      else
      {
        i=0;
        duas=0;
      }
    }

    //DADO
    int loop2=0;

    if(cor[player].trava_inicio==1 && seis_c<3)
    {
      while(loop2==0)
      {
        printf(RED_T "SELECIONE O PEAO:\n" RESET);
        scanf("%i",&selc);

        loop2=0;

        if(cor[player].trava_peao[selc]==0)
        {
          cor[player].peao[selc]+=dado; loop2=1;
          comer(player,cor,selc,block_selc,seis_repeat);

          if(cor[2].peao[selc]>=80)
          {
            loop2=0;
            cor[2].peao[selc]-=dado;
            printf(RED_T "PEAO INVALIDO\n" RESET);
            cor[player].trava_peao[selc]=1;

            if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
            {
              loop2=1;
            }
            else
            {
              system("pause"); system("cls");
              tabuleiro(tab,cor);
              mini_menu(block_selc,win,player);
              printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
              printf("%i\n",confirm);
              printf(BLUE_T "\nDADO: %i\n" RESET,dado);
            }
            cor[player].trava_peao[selc]=0;
          }
        }
        else
        {
          printf(RED_T "PEAO INVALIDO\n" RESET);
          system("pause"); system("cls");
          tabuleiro(tab,cor);
          mini_menu(block_selc,win,player);
          printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
          printf("%i\n",confirm);
          printf(BLUE_T "\nDADO: %i\n" RESET,dado);
        }
      }

      //LINHA MEIO
      int n_dado,n_dado_loop;

      //LOOP DO TABULEIRO RESET
      if(cor[2].peao[selc]>61 && cor[2].peao[selc]<70)
      {
        n_dado_loop=cor[2].peao[selc]-61;
        cor[2].peao[selc]=9+n_dado_loop;
        cor[2].loop_t[selc]++;
      }

      if(cor[2].peao[selc]>21 && cor[2].peao[selc]<28 && cor[2].loop_t[selc]>0)
      {
        n_dado=cor[2].peao[selc]-21;
        cor[2].peao[selc]=73+n_dado;
      }

      if(cor[2].peao[selc]==79 && cor[2].trava_win[selc]==0)
      {
        win[2]++;
        cor[2].trava_peao[selc]++;
        cor[2].trava_win[selc]++;
        cor[player].trava_player=1;
      }
    }

    else
    {
      printf(RED_T "PROXIMO TURNO\n" RESET);
    }
  }

  //VERDE
  if(player==3)
  {
    if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
    {
      cor[player].trava_inicio=0;
    }

    int duas=0,seis_c=0;
    //LIBERAR PEAO NOVO
    while(i==1)
    {
      if(dado==6 && seis_repeat[2]<5 && seis_c<3)
      {
        for(int j=1; j<5; j++)
        {
          if (cor[3].peao[j]<0)
          {
            cor[3].peao[j]=36; cor[player].trava_peao[j]=0; break;
          }
        }

        block_selc[2]++;
        seis_repeat[2]++;
        seis_c++;

        if(duas==0)
        {
          printf(GREEN_T "PEAO LIBERADO\n" RESET);
          cor[player].trava_inicio=1;
          system("pause"); system("cls");
        }

        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        srand(time(NULL)); dado=(rand()%6)+1;
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);


        if(dado==6)
        {
          i=1; duas++;
          printf(GREEN_T "PEAO LIBERADO\n" RESET); system("pause"); system("cls");
        }
      }

      else if(dado==6 && duas>0)
      {
        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);

        i=0;
        duas=0;
        seis_c++;
      }

      else
      {
        i=0;
        duas=0;
      }
    }

    //DADO
    int loop2=0;

    if(cor[player].trava_inicio==1 && seis_c<3)
    {
      while(loop2==0)
      {
        printf(RED_T "SELECIONE O PEAO:\n" RESET);
        scanf("%i",&selc);

        loop2=0;

        if(cor[player].trava_peao[selc]==0)
        {
          cor[player].peao[selc]+=dado; loop2=1;
          comer(player,cor,selc,block_selc,seis_repeat);

          if(cor[3].peao[selc]>=90)
          {
            loop2=0;
            cor[3].peao[selc]-=dado;
            printf(RED_T "PEAO INVALIDO\n" RESET);
            cor[player].trava_peao[selc]=1;

            if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
            {
              loop2=1;
            }
            else
            {
              system("pause"); system("cls");
              tabuleiro(tab,cor);
              mini_menu(block_selc,win,player);
              printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
              printf("%i\n",confirm);
              printf(BLUE_T "\nDADO: %i\n" RESET,dado);
            }
            cor[player].trava_peao[selc]=0;
          }
        }

        else
        {
          printf(RED_T "PEAO INVALIDO\n" RESET);
          system("pause"); system("cls");
          tabuleiro(tab,cor);
          mini_menu(block_selc,win,player);
          printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
          printf("%i\n",confirm);
          printf(BLUE_T "\nDADO: %i\n" RESET,dado);
        }
      }

      //LINHA MEIO
      int n_dado,n_dado_loop;

      //LOOP DO TABULEIRO RESET
      if(cor[3].peao[selc]>61 && cor[3].peao[selc]<70)
      {
        n_dado_loop=cor[3].peao[selc]-61;
        cor[3].peao[selc]=9+n_dado_loop;
        cor[3].loop_t[selc]++;
      }

      if(cor[3].peao[selc]>34 && cor[3].peao[selc]<41 && cor[3].loop_t[selc]>0)
      {
        n_dado=cor[3].peao[selc]-34;
        cor[3].peao[selc]=83+n_dado;
      }

      if(cor[3].peao[selc]==89 && cor[3].trava_win[selc]==0)
      {
        win[3]++;
        cor[3].trava_peao[selc]++;
        cor[3].trava_win[selc]++;
        cor[player].trava_player=1;
      }
    }

    else
    {
      printf(RED_T "PROXIMO TURNO\n" RESET);
    }
  }

  //AMARELO
  if(player==4)
  {
    if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
    {
      cor[player].trava_inicio=0;
    }

    int duas=0,seis_c=0;
    //LIBERAR PEAO NOVO
    while(i==1)
    {
      if(dado==6 && seis_repeat[3]<5 && seis_c<3)
      {
        for(int j=1; j<5; j++)
        {
          if (cor[4].peao[j]<0)
          {
            cor[4].peao[j]=49; cor[player].trava_peao[j]=0; break;
          }
        }

        block_selc[3]++;
        seis_repeat[3]++;
        seis_c++;

        if(duas==0)
        {
          printf(GREEN_T "PEAO LIBERADO\n" RESET);
          cor[player].trava_inicio=1;
          system("pause"); system("cls");
        }

        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        srand(time(NULL)); dado=(rand()%6)+1;
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);


        if(dado==6)
        {
          i=1; duas++;
          printf(GREEN_T "PEAO LIBERADO\n" RESET); system("pause"); system("cls");
        }
      }

      else if(dado==6 && duas>0)
      {
        tabuleiro(tab,cor);
        mini_menu(block_selc,win,player);
        printf(YELLOW_T "\nNOVO DADO: %i\n" RESET,dado);

        i=0;
        duas=0;
        seis_c++;
      }

      else
      {
        i=0;
        duas=0;
      }
    }

    //DADO
    int loop2=0;

    if(cor[player].trava_inicio==1 && seis_c<3)
    {
      while(loop2==0)
      {
        printf(RED_T "SELECIONE O PEAO:\n" RESET);
        scanf("%i",&selc);

        loop2=0;

        if(cor[player].trava_peao[selc]==0)
        {
          cor[player].peao[selc]+=dado; loop2=1;
          comer(player,cor,selc,block_selc,seis_repeat);

          if(cor[4].peao[selc]>=100)
          {
            loop2=0;
            cor[4].peao[selc]-=dado;
            printf(RED_T "PEAO INVALIDO\n" RESET);
            cor[player].trava_peao[selc]=1;

            if(cor[player].trava_peao[1]==1 && cor[player].trava_peao[2]==1 && cor[player].trava_peao[3]==1 && cor[player].trava_peao[4]==1)
            {
              loop2=1;
            }
            else
            {
              system("pause"); system("cls");
              tabuleiro(tab,cor);
              mini_menu(block_selc,win,player);
              printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
              printf("%i\n",confirm);
              printf(BLUE_T "\nDADO: %i\n" RESET,dado);
            }
            cor[player].trava_peao[selc]=0;
          }
        }
        else
        {
          printf(RED_T "PEAO INVALIDO\n" RESET);
          system("pause"); system("cls");
          tabuleiro(tab,cor);
          mini_menu(block_selc,win,player);
          printf(YELLOW_T "\n(1) ROLL THE DICE\n" RESET);
          printf("%i\n",confirm);
          printf(BLUE_T "\nDADO: %i\n" RESET,dado);
        }
      }

      //LINHA MEIO
      int n_dado,n_dado_loop;

      //LOOP DO TABULEIRO RESET
      if(cor[4].peao[selc]>61 && cor[4].peao[selc]<70)
      {
        n_dado_loop=cor[4].peao[selc]-61;
        cor[4].peao[selc]=9+n_dado_loop;
        cor[4].loop_t[selc]++;
      }

      if(cor[4].peao[selc]>47 && cor[4].peao[selc]<54 && cor[4].loop_t[selc]>0)
      {
        n_dado=cor[4].peao[selc]-47;
        cor[4].peao[selc]=93+n_dado;
      }

      if(cor[4].peao[selc]==99 && cor[4].trava_win[selc]==0)
      {
        win[4]++;
        cor[4].trava_peao[selc]++;
        cor[4].trava_win[selc]++;
        cor[player].trava_player=1;
      }
    }

    else
    {
      printf(RED_T "PROXIMO TURNO\n" RESET);
    }
  }
}

void mini_menu (int block_selc[],int win[],int player)
{
  switch(player)
  {
    case 1: printf(BLUE_T "\nPLAYER %i TURN\n" RESET,player); printf("\nPEOES LIBERADOS: %i" GREEN_T "\nPEOES VITORIOSOS: %i\n" RESET,block_selc[player-1]-1,win[player]); break;
    case 2: printf(RED_T "\nPLAYER %i TURN\n" RESET,player); printf("\nPEOES LIBERADOS: %i" GREEN_T "\nPEOES VITORIOSOS: %i\n" RESET,block_selc[player-1]-1,win[player]); break;
    case 3: printf(GREEN_T "\nPLAYER %i TURN\n" RESET,player); printf("\nPEOES LIBERADOS: %i" GREEN_T "\nPEOES VITORIOSOS: %i\n" RESET,block_selc[player-1]-1,win[player]); break;
    case 4: printf(YELLOW_T "\nPLAYER %i TURN\n" RESET,player); printf("\nPEOES LIBERADOS: %i" GREEN_T "\nPEOES VITORIOSOS: %i\n" RESET,block_selc[player-1]-1,win[player]); break;
  }
}

void comer(int player,peao cor[],int selc,int block_selc[],int seis_repeat[])
{
  if (cor[player].peao[selc]!=10 && cor[player].peao[selc]!=23 && cor[player].peao[selc]!=36 && cor[player].peao[selc]!=49 && cor[player].peao[selc]!=18 && cor[player].peao[selc]!=57 && cor[player].peao[selc]!=31 && cor[player].peao[selc]!=44)
  {
    for(int i=1; i<5; i++)
    {
      for(int j=1; j<5; j++)
      {
        if(cor[player].peao[selc]==cor[i].peao[j])
        {
          //AZUL
          if(player==1)
          {
            if(i==2)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -23; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -20; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -21; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -22; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==3)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -33; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -30; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -31; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -32; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==4)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -43; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -40; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -41; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -42; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }
          }

          //VERMELHO
          else if(player==2)
          {
            if(i==1)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -13; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -10; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -11; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -12; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==3)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -33; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -30; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -31; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -32; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==4)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -43; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -40; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -41; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -42; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }
          }

          //VERDE
          else if(player==3)
          {
            if(i==1)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -13; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -10; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -11; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -12; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==2)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -23; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -20; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -21; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -22; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==4)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -43; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -40; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -41; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -42; block_selc[3]--; seis_repeat[3]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }
          }

          //AMARELO
          else if(player==4)
          {
            if(i==1)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -13; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -10; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -11; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -12; block_selc[0]--; seis_repeat[0]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==2)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -23; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -20; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -21; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -22; block_selc[1]--; seis_repeat[1]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }

            else if(i==3)
            {
              switch(j)
              {
                case 1: cor[i].peao[j]= -33; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 2: cor[i].peao[j]= -30; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 3: cor[i].peao[j]= -31; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
                case 4: cor[i].peao[j]= -32; block_selc[2]--; seis_repeat[2]--; cor[i].trava_peao[j]=1; cor[player].trava_player=1; break;
              }
            }
          }
        }
      }
    }
  }
}
