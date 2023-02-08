#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

//CORES GERAIS
#define GREEN_F "\e[42;32m"
#define LIFE "\e[42;31m"
#define SELECT "\e[42;33m"
#define PLAYER "\e[47;30m"
#define BLUE_T "\e[34m"
#define PLAYER2 "\e[47;37m"

//CORES CARTA
#define RESET "\e[0m"
#define RED_CARD "\e[47;31m"
#define BLACK_CARD "\e[47;30m"
#define RED_F "\e[41;31m"
#define WHITE_F "e[47;37m"

typedef struct elemento
{
    int id;
    int power;
    int valor;
    int naipe;
    int trava;
    struct elemento *anterior;
}elemento;

typedef struct players
{
  elemento *carta[6];
  int vidas;
  int vitorias;
  int real_v;
}players;

typedef struct pilha
{
    elemento *topo;
}pilha;

pilha* criapilha();
void liberapilha();
int empilha();
players* cria_players();
int estavazia();
int quantidadejogador();
elemento* vector();
void bubblesort();
void tabuleiro();
int troca_jogador();
void rodadas();
void desempilha();
void txt();

////////////////////////////////////////////////////////////////////////////////
int main()
{

    int select=0,escolha,confere,jogadores=2,rodada=5,inversor_rodada=0,teste=1,vencedor,conta_foras,player=1,aux_id,imprimir;
    pilha *ponto;
    elemento *vetor;
    players *mao;
    FILE *f;
    int cataMesaSeleccion[9]={0,0,0,0,0,0,0,0,0};

    f=fopen("acontecimentos.txt","w+");

    if(f==NULL)
    {
      printf("ERROR TXT\n"); system("pause");
      exit(1);
    }

    int tab[27][27]= {100,100,100,100,100,100,100,100,100,601,100,100,100,100,100,100,100,501,100,100,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,602,603,604,605,606,100,100,100,502,503,504,505,506,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,631,632,633,634,635,100,100,100,531,532,533,534,535,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,621,622,623,624,625,100,100,100,521,522,523,524,525,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,611,612,613,614,615,100,100,100,511,512,513,514,515,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
                      100,702,100,731,721,711,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,411,421,431,100,402,100,
                      100,703,100,732,722,712,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,412,422,432,100,403,100,
                      701,704,100,733,723,713,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,413,423,433,100,404,401,
                      100,705,100,734,724,714,100,100,100,100,100,100,608,100,508,100,100,100,100,100,100,414,424,434,100,405,100,
                      100,706,100,735,725,715,100,100,100,100,100,100,607,100,507,100,100,100,100,100,100,415,425,435,100,406,100,
                      100,100,100,100,100,100,100,100,100,100,708,707,100,100,100,407,408,100,100,100,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,100,100,100,808,807,100,100,100,307,308,100,100,100,100,100,100,100,100,100,100,
                      100,802,100,831,821,811,100,100,100,100,100,100,107,100,207,100,100,100,100,100,100,311,321,331,100,302,100,
                      100,803,100,832,822,812,100,100,100,100,100,100,108,100,208,100,100,100,100,100,100,312,322,332,100,303,100,
                      801,804,100,833,823,813,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,313,323,333,100,304,301,
                      100,805,100,834,824,814,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,314,324,334,100,305,100,
                      100,806,100,835,825,815,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,315,325,335,100,306,100,
                      100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,111,112,113,114,115,100,100,100,211,212,213,214,215,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,121,122,123,124,125,100,100,100,221,222,223,224,225,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,131,132,133,134,135,100,100,100,231,232,233,234,235,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,102,103,104,105,106,100,100,100,202,203,204,205,206,100,100,100,100,100,100,100,
                      100,100,100,100,100,100,100,100,100,101,100,100,100,100,100,100,100,201,100,100,100,100,100,100,100,100,100};


    while(1)
    {
        //VERIFICAR VITORIAS
        if(teste==0)
        {
          conta_foras=0;

          for (int i=0; i<=jogadores; i++)
          {

            if (mao[i].vidas==0)
            {
              conta_foras++;
            }

            else
            {
              vencedor=i;
            }
          }

          if (conta_foras==jogadores-1)
          {
            select=3;
          }

          else if (conta_foras==jogadores)
          {
            select=2;
          }

        }



        //MENU INICIAL
        if(select==0)
        {
            printf("(0) SAIR\n");
            printf("(1) INICIAR JOGO\n");
            printf("(2) QUANTIDADE DE JOGADORES\n");
            printf("\nJOGADORES: %i\n",jogadores);
            scanf("%i",&escolha);

            switch(escolha)
            {
                default: printf("VALOR INVALIDO\n"); system("pause"); system("cls"); break;
                case 0: liberapilha(ponto,vetor,mao,jogadores); exit(1); break;
                case 1:
                {
                  mao=cria_players(jogadores); system("pause"); system("cls"); select=1;

                  int travaPlayer[jogadores+1];

                  for(int j=0; j<=jogadores; j++)
                  {
                    travaPlayer[j]=0;
                  }

                  break;
                }
                case 2: jogadores=quantidadejogador(); system("pause"); system("cls"); break;
            }
        }

        //JOGO COMEÃ‡A
        else if(select==1)
        {

          ponto=criapilha(); vetor=vector(); bubblesort(vetor,aux_id);
          confere=empilha(ponto,vetor); desempilha(ponto,jogadores,rodada,mao);

          for(int i=1; i<=jogadores; i++)
          {
            for(int j=1; j<=rodada; j++)
            {
              mao[i].carta[j]->trava=0;
            }
          }

          if(confere==0)
          {
            printf("error\n"); liberapilha(ponto,vetor,mao,jogadores); system("pause"); system("cls");
            select=0;
          }

          int conta_jogador=0,fase_jogo=0,escolhe_carta,conta_rodada=0,maior=1,maior_player;


            //QUANTO FAZ?


            int somaAcho=0;

            while (fase_jogo==0)
            {
              if(mao[player].vidas<1)
              {
                conta_jogador++;
                player=troca_jogador(jogadores, player);
              }

              tabuleiro(tab, player, jogadores,mao,fase_jogo,rodada,cataMesaSeleccion);

              printf(BLUE_T "P%i QUANTAS RODADAS VOCE FAZ?\n" RESET,player);
              scanf("%i",&mao[player].vitorias);

              somaAcho+=mao[player].vitorias;

              if(conta_jogador==jogadores-1)
              {
                if(somaAcho==rodada)
                {
                  somaAcho-=mao[player].vitorias;
                  mao[player].vitorias=-1;
                }
              }

              if(mao[player].vitorias>-1 && mao[player].vitorias<=rodada)
              {
                txt(1,f, player, jogadores,mao,rodada,cataMesaSeleccion);
                player=troca_jogador(jogadores, player);
                conta_jogador++;

                if(conta_jogador==jogadores)
                {
                  somaAcho=0;
                  conta_jogador=0;
                  fase_jogo=1;
                }
              }

              else
              {
                printf("VALOR INVALIDO\n");
              }

              system("pause"); system("cls");
            }

            while (fase_jogo==1)
            {

              if(mao[player].vidas<1)
              {
                conta_jogador++;
                player=troca_jogador(jogadores, player);
              }

              tabuleiro(tab, player, jogadores,mao,fase_jogo,rodada,cataMesaSeleccion);

              if(conta_jogador==jogadores)
              {
                for(int i=1;i<9;i++)
                {
                  cataMesaSeleccion[i]=0;
                }

                conta_jogador=0;
              }

              printf("P%i SELECIONE A CARTA\n",player);
              scanf("%i",&escolhe_carta);

              if(escolhe_carta>0 && escolhe_carta<=rodada && mao[player].carta[escolhe_carta]->trava==0)
              {
                mao[player].carta[escolhe_carta]->trava=1;
                cataMesaSeleccion[player]=escolhe_carta;
                txt(2,f, player, jogadores,mao,rodada,cataMesaSeleccion);
                if(mao[player].carta[escolhe_carta]->power>maior)
                {
                  maior=mao[player].carta[escolhe_carta]->power;
                  maior_player=player;
                }

                player=troca_jogador(jogadores, player);
                conta_jogador++;

                if(conta_jogador==jogadores)
                {

                  mao[maior_player].real_v++;
                  maior=0;
                  conta_rodada++;
                  player=maior_player;
                  txt(3,f, player, jogadores,mao,rodada,cataMesaSeleccion);

                  if(conta_rodada==rodada)
                  {

                    for(int i=1; i<=jogadores; i++)
                    {
                      if(mao[i].real_v!=mao[i].vitorias)
                      {
                        mao[i].vidas--;
                        txt(6,f, i, jogadores,mao,rodada,cataMesaSeleccion);
                        mao[i].real_v=0;
                        mao[i].vitorias=0;
                      }
                    }

                    conta_rodada=0;
                    player=troca_jogador(jogadores, player);
                    rodadas(&rodada, &inversor_rodada);
                    fase_jogo=0;
                    teste=0;
                  }
                }
              }

              else
              {
                printf("VALOR INVALIDO\n");
              }

              system("pause"); system("cls");
            }

        }

        else if (select==2)
        {
          printf("PARABENS TODOS PERDERAM\n"); fclose(f); system("pause"); system("cls"); liberapilha(ponto,vetor,mao,jogadores); exit(1);
        }

        else if (select==3)
        {
          printf("PARABENS JOGADOR %i. VOCE VENCEU\n",vencedor); system("pause"); system("cls");
          txt(4,f, vencedor, jogadores,mao,rodada,cataMesaSeleccion);
          fclose(f); liberapilha(ponto,vetor,mao,jogadores); exit(1);
        }
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////

//CRIA AS CARTAS
elemento* vector()
{
  elemento *vetorfisico = (elemento*) malloc (41*sizeof(elemento));
  srand(time(NULL));

  int count = 0;
  for(int i=1; i<=10; i++)
  {
    for(int j=1; j<=4; j++)
    {
        vetorfisico[count].valor=i;
        vetorfisico[count].naipe=j;
        vetorfisico[count].trava=0;
        vetorfisico[count].id=rand()+1;
        vetorfisico[count].id=pow(vetorfisico[count].id,2);

        //POWER
        //////////////////////////////////
        if (i==4 && vetorfisico[count].naipe==4)
        {
          vetorfisico[count].power=(66+vetorfisico[count].naipe);
        }

        else if (i==7 && vetorfisico[count].naipe==3)
        {
          vetorfisico[count].power=(61+vetorfisico[count].naipe);
        }

        else if (i==1 && vetorfisico[count].naipe==2)
        {
          vetorfisico[count].power=(56+vetorfisico[count].naipe);
        }

        else if (i==7 && vetorfisico[count].naipe==1)
        {
          vetorfisico[count].power=(51+vetorfisico[count].naipe);
        }

        else if (i==3)
        {
          vetorfisico[count].power=(46+vetorfisico[count].naipe);
        }

        else if (i==2)
        {
          vetorfisico[count].power=(41+vetorfisico[count].naipe);
        }

        else if (i==1)
        {
          vetorfisico[count].power=(36+vetorfisico[count].naipe);
        }

        else if (i==10)
        {
          vetorfisico[count].power=(31+vetorfisico[count].naipe);
        }

        else if (i==9)
        {
          vetorfisico[count].power=(26+vetorfisico[count].naipe);
        }

        else if (i==8)
        {
          vetorfisico[count].power=(21+vetorfisico[count].naipe);
        }

        else if (i==7)
        {
          vetorfisico[count].power=(16+vetorfisico[count].naipe);
        }

        else if (i==6)
        {
          vetorfisico[count].power=(11+vetorfisico[count].naipe);
        }

        else if (i==5)
        {
          vetorfisico[count].power=(6+vetorfisico[count].naipe);
        }

        else if (i==4)
        {
          vetorfisico[count].power=(1+vetorfisico[count].naipe);
        }
        //////////////////////////////////
        count++;
      }
    }
    return vetorfisico;
};

//CRIA O BARALHO
pilha* criapilha()
{
    pilha *ponto = (pilha*) malloc (sizeof(pilha));
    ponto->topo=NULL;

    return ponto;
};

//LIBERA O BARALHO
void liberapilha(pilha* ponto, elemento *vetorfisico, players* mao,int jogadores)
{
    elemento *aux;

    while(ponto->topo!=NULL)
    {
        aux=ponto->topo;
        ponto->topo=ponto->topo->anterior;

        free(aux);
    }

    for (int i=0; i<=jogadores; i++)
    {
    	for (int j=0; j<=5; j++)
    	{
    		free(mao[i].carta[j]);
		}
	}


    free(vetorfisico);
    free(ponto);
};

//EMPILHA AS CARTAS
int empilha(pilha* ponto, elemento *vetorfisico)
{
  for(int i=1;i<=40; i++)
  {
    elemento *novo = (elemento*) malloc (sizeof(elemento));

      novo->valor=vetorfisico[i].valor;
      novo->naipe=vetorfisico[i].naipe;
      novo->power=vetorfisico[i].power;
      novo->id=vetorfisico[i].id;

      novo->anterior=ponto->topo;
      ponto->topo=novo;
  }
    return 1;
};

//GERA JOGADORES E DESTRIBUI CARTAS
players* cria_players(int jogadores)
{
    players *jogador = (players*) malloc ((jogadores+1)*sizeof(players));

    for(int i=1; i<=jogadores; i++)
    {
      jogador[i].vidas=5;
      jogador[i].real_v=0;
    }

    return jogador;
};

//QUANTIDADE DE JOGADORES
int quantidadejogador()
{
  system("cls");
  int quantidade;

  while(1)
  {
    printf("QUANTOS IRAO JOGAR:\n");
    scanf("%i",&quantidade);

    if(quantidade>=2 && quantidade<=6)
    {
      return quantidade;
    }

    else
    {
      printf("VALOR INVALIDO\n");
      system("pause"); system("cls");
    }
  }
};

// ORDENAÃ‡ÃƒO DOS IDS
void bubblesort (elemento* vetor,int aux_id)
{

  for(int j=1; j<41; j++)
  {
    for(int i=1; i<41; i++)
    {
      if(vetor[i].id>vetor[i-1].id)
      {
        aux_id = vetor[i].valor;
        vetor[i].valor=vetor[i-1].valor;
        vetor[i-1].valor=aux_id;

        aux_id = vetor[i].naipe;
        vetor[i].naipe=vetor[i-1].naipe;
        vetor[i-1].naipe=aux_id;

        aux_id = vetor[i].power;
        vetor[i].power=vetor[i-1].power;
        vetor[i-1].power=aux_id;

        aux_id = vetor[i].id;
        vetor[i].id=vetor[i-1].id;
        vetor[i-1].id=aux_id;
      }
    }
  }
};

//GERAÃ‡ÃƒO DO TABULEIRO
void tabuleiro(int tab[][27], int player,int jogadores,players *mao, int fase_jogo, int rodada, int cataMesaSeleccion[])
{
  int playerAtual=player*100,contadorLinhas=0;

  for(int i=0;i<27;i++)
  {
    for(int j=0;j<27;j++)
    {

      //////////////////////////////////////////////////////////////////////////

      //valor mesa
      if(tab[i][j]%100==7 && tab[i][j]/100<=jogadores && cataMesaSeleccion[tab[i][j]/100]!=0)
      {

        //PRETAS
        if(mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->naipe==2 || mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->naipe==4)
        {

          switch(mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->valor)
          {
            default:printf(BLACK_CARD "|%i|" RESET ,mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->valor); break;
            case 8: printf(BLACK_CARD "|Q|" RESET); break;
            case 9: printf(BLACK_CARD "|J|" RESET); break;
            case 10:  printf(BLACK_CARD "|K|" RESET); break;
          }

        }

        //VERMELHAS
        else if(mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->naipe==1 || mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->naipe==3)
        {

          switch(mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->valor)
          {
            default:printf(RED_CARD "|%i|" RESET ,mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->valor); break;
            case 8: printf(RED_CARD "|Q|" RESET); break;
            case 9: printf(RED_CARD "|J|" RESET); break;
            case 10:  printf(RED_CARD "|K|" RESET); break;
          }

        }

        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //naipe mesa
      else if(tab[i][j]%100==8 && tab[i][j]/100<=jogadores && cataMesaSeleccion[tab[i][j]/100]!=0)
      {
        switch(mao[tab[i][j]/100].carta[cataMesaSeleccion[tab[i][j]/100]]->naipe)
        {
          case 1: printf(RED_CARD "|O|" RESET); break;
          case 2: printf(BLACK_CARD "|E|" RESET); break;
          case 3: printf(RED_CARD "|C|" RESET); break;
          case 4: printf(BLACK_CARD "|P|" RESET); break;
        }

        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //casa dos players
      else if(tab[i][j]%100==1 && tab[i][j]/100<=jogadores)
      {
        printf(PLAYER "P%i|" RESET,tab[i][j]/100);
        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //vidas
      if(tab[i][j]%100>1 && tab[i][j]%100<7 && tab[i][j]/100<=jogadores && mao[tab[i][j]/100].vidas>=(tab[i][j]%100)-1)
      {

        printf(LIFE "|X|" RESET);
        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //seletores
      if(tab[i][j]%100>30 && tab[i][j]%100<36 && tab[i][j]/100==player && tab[i][j]%10<=rodada)
      {

        switch (tab[i][j]%10)
        {
          case 1: printf(SELECT "(1)" RESET); break;
          case 2: printf(SELECT "(2)" RESET); break;
          case 3: printf(SELECT "(3)" RESET); break;
          case 4: printf(SELECT "(4)" RESET); break;
          case 5: printf(SELECT "(5)" RESET); break;
        }

        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //valor mao
      if(tab[i][j]%100>10 && tab[i][j]%100<16 && tab[i][j]/100==player && mao[player].carta[tab[i][j]%10]->trava==0 && tab[i][j]%10<=rodada)
      {

        //PRETAS
        if(mao[player].carta[tab[i][j]%10]->naipe==2 || mao[player].carta[tab[i][j]%10]->naipe==4)
        {

          switch(mao[player].carta[tab[i][j]%10]->valor)
          {
            default:printf(BLACK_CARD "|%i|" RESET ,mao[player].carta[tab[i][j]%10]->valor); break;
            case 8: printf(BLACK_CARD "|Q|" RESET); break;
            case 9: printf(BLACK_CARD "|J|" RESET); break;
            case 10:  printf(BLACK_CARD "|K|" RESET); break;
          }

        }

        //VERMELHAS
        else if(mao[player].carta[tab[i][j]%10]->naipe==1 || mao[player].carta[tab[i][j]%10]->naipe==3)
        {

          switch(mao[player].carta[tab[i][j]%10]->valor)
          {
            default:printf(RED_CARD "|%i|" RESET ,mao[player].carta[tab[i][j]%10]->valor); break;
            case 8: printf(RED_CARD "|Q|" RESET); break;
            case 9: printf(RED_CARD "|J|" RESET); break;
            case 10:  printf(RED_CARD "|K|" RESET); break;
          }

        }

        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //naipe mao
      else if(tab[i][j]%100>20 && tab[i][j]%100<26 && tab[i][j]/100==player && mao[player].carta[tab[i][j]%10]->trava==0 && tab[i][j]%10<=rodada)
      {
        switch(mao[player].carta[tab[i][j]%10]->naipe)
        {
          case 1: printf(RED_CARD "|O|" RESET); break;
          case 2: printf(BLACK_CARD "|E|" RESET); break;
          case 3: printf(RED_CARD "|C|" RESET); break;
          case 4: printf(BLACK_CARD "|P|" RESET); break;
        }

        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

      //////////////////////////////////////////////////////////////////////////

      //verde
      else
      {
        printf(GREEN_F "100" RESET);

        contadorLinhas++;

        if(contadorLinhas==27)
        {
          contadorLinhas=0;
          printf("\n");
        }

        continue;
      }

    }
  }
};

//ALTERA O JOGADOR
int troca_jogador(int jogadores, int player)
{
  player++;
  if(player>jogadores)
  {
    player=1;
  }

  return player;
};

//RODADAS
void rodadas(int *rodada, int *inversor_rodada)
{
  if (*inversor_rodada==0)
  {
    (*rodada)--;
    if(*rodada==0)
    {
      (*inversor_rodada)=-1;
      (*rodada)=2;
    }
  }

  else if (*inversor_rodada==-1)
  {
    (*rodada)++;
    if(*rodada==6)
    {
      (*inversor_rodada)=0;
      (*rodada)=4;
    }
  }
};

//DA AS CARTAS
void desempilha(pilha* ponto, int jogadores,int rodada,players *mao)
{
  for(int i=1; i<=jogadores; i++)
  {
    for(int j=0; j<=rodada; j++)
    {
        mao[i].carta[j]=ponto->topo;
        ponto->topo=ponto->topo->anterior;
    }
  }
};

//IMPRIME
void txt(int imprimir, FILE *f, int player,int jogadores,players *mao, int rodada, int cataMesaSeleccion[])
{

  switch(imprimir)
  {
    case 1: fprintf(f,"P%i DISSE QUE FAZ %i RODADAS\n",player,mao[player].vitorias); break;
    case 3: fprintf(f,"P%i É O VENCEDOR DA RODADAS\n",player); break;
    case 4: fprintf(f,"P%i É O VENCEDOR\n",player); break;
    case 5: fprintf(f,"TODOS PERDERAM\n",player); break;
    case 6: fprintf(f,"P%i PERDEU VIDA\n",player); break;
    case 2:
    {
      switch (mao[player].carta[cataMesaSeleccion[player]]->naipe)
      {
        case 1:
        {
          switch(mao[player].carta[cataMesaSeleccion[player]]->valor)
          {
            default: fprintf(f,"P%i JOGOU A CARTA %i DE OURO\n",player,mao[player].carta[cataMesaSeleccion[player]]->valor); break;
            case 8: fprintf(f,"P%i JOGOU A CARTA Q DE OURO\n",player); break;
            case 9: fprintf(f,"P%i JOGOU A CARTA J DE OURO\n",player); break;
            case 10: fprintf(f,"P%i JOGOU A CARTA K DE OURO\n",player); break;
          } break;
        }

        case 2:
        {
          switch(mao[player].carta[cataMesaSeleccion[player]]->valor)
          {
            default: fprintf(f,"P%i JOGOU A CARTA %i DE ESPADAS\n",player,mao[player].carta[cataMesaSeleccion[player]]->valor); break;
            case 8: fprintf(f,"P%i JOGOU A CARTA Q DE ESPADAS\n",player); break;
            case 9: fprintf(f,"P%i JOGOU A CARTA J DE ESPADAS\n",player); break;
            case 10: fprintf(f,"P%i JOGOU A CARTA K DE ESPADAS\n",player); break;
          } break;
        }

        case 3:
        {
          switch(mao[player].carta[cataMesaSeleccion[player]]->valor)
          {
            default: fprintf(f,"P%i JOGOU A CARTA %i DE COPAS\n",player,mao[player].carta[cataMesaSeleccion[player]]->valor); break;
            case 8: fprintf(f,"P%i JOGOU A CARTA Q DE COPAS\n",player); break;
            case 9: fprintf(f,"P%i JOGOU A CARTA J DE COPAS\n",player); break;
            case 10: fprintf(f,"P%i JOGOU A CARTA K DE COPAS\n",player); break;
          } break;
        }

        case 4:
        {
          switch(mao[player].carta[cataMesaSeleccion[player]]->valor)
          {
            default: fprintf(f,"P%i JOGOU A CARTA %i DE PAUS\n",player,mao[player].carta[cataMesaSeleccion[player]]->valor); break;
            case 8: fprintf(f,"P%i JOGOU A CARTA Q DE PAUS\n",player); break;
            case 9: fprintf(f,"P%i JOGOU A CARTA J DE PAUS\n",player); break;
            case 10: fprintf(f,"P%i JOGOU A CARTA K DE PAUS\n",player); break;
          } break;
        }
      }
     break;}
  }
}
