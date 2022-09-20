#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//CORES TEXTO
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define RESET "\e[0m"

typedef struct ponto
{
    int x,y;
} ponto;

void pdef();
float dist();
int quadrante();
void write_quadrante();
void cord();
void define();

//////////////////////////////////////////////////////////////////////////////////////
int main()
{
    ponto p[2];
    float distancia;
    int escolha, quadra;

    for(int i=1; i<3; i++)
    {
        printf("PONTO %i EIXO X:\n",i);
        scanf("%i",&p[i-1].x);

        printf("PONTO %i EIXO Y:\n",i);
        scanf("%i",&p[i-1].y);

        printf("\n");
    }

    system("pause"); system("cls");

    while(1)
    {
        printf(BLUE"P1(%i,%i)     -     P2(%i,%i)\n",p[0].x,p[0].y,p[1].x,p[1].y);
        printf(YELLOW"\n-----MENU-----\n");
        printf(RED"(0) Sair;\n");
        printf(GREEN"(1) Inicializacao passando parametros;\n");
        printf(GREEN"(2) Inicializacao fazendo a leitura dentro da funcao;\n");
        printf(GREEN"(3) Analisar qual o quadrante um ponto se encontra;\n");
        printf(GREEN"(4) Verificar ponto e quadrante;\n");
        printf(GREEN"(5) Alterar os valores de um determinado ponto;\n");
        printf(GREEN"(6) Retornar qual a distancia entre dois pontos;\n");
        printf(GREEN"(7) Retornar o maior valor de coordenada de um ponto;\n"RESET);
        scanf("%i",&escolha);

        switch(escolha)
        {
            case 0: system("cls");  exit(1); break;
            case 1: system("cls");

            for(int j=1; j<3; j++)
            {
                printf("PONTO %i EIXO X:\n",j);
                scanf("%i",&p[j-1].x);

                printf("PONTO %i EIXO Y:\n",j);
                scanf("%i",&p[j-1].y);

                printf("\n");
            }

            system("pause"); system("cls"); break;
            case 2: system("cls");  define(p); system("pause"); system("cls"); break;
            case 3: system("cls");  quadra=quadrante(p,escolha,quadra); write_quadrante(quadra); system("pause"); system("cls"); break;
            case 4: system("cls");  quadra=quadrante(p,escolha,quadra); system("pause"); system("cls"); break;
            case 5: system("cls");  pdef(p); system("pause"); system("cls"); break;
            case 6: system("cls"); distancia=dist(p);  printf("A DISTANCIA ENTRE OS PONTOS E: %.2f\n",distancia); system("pause"); system("cls"); break;
            case 7: system("cls"); cord(p); system("pause"); system("cls"); break;
            default: system("cls"); printf("Valor invalido"); system("pause"); system("cls"); break;
        }
    }


    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////

void define(ponto p[])
{
  for(int i=1; i<3; i++)
  {
      printf("PONTO %i EIXO X:\n",i);
      scanf("%i",&p[i-1].x);

      printf("PONTO %i EIXO Y:\n",i);
      scanf("%i",&p[i-1].y);

      printf("\n");
  }
}

void pdef(ponto p[])
{
  int d;

  printf("ESCOLHA O PONTO:\n");
  scanf("%i",&d);

  system("cls");

  switch(d)
  {
    case 1:
      printf("PONTO %i EIXO X:\n",d);
      scanf("%i",&p[d-1].x);

      printf("PONTO %i EIXO Y:\n",d);
      scanf("%i",&p[d-1].y);

    case 2:
      printf("PONTO %i EIXO X:\n",d);
      scanf("%i",&p[d-1].x);

      printf("PONTO %i EIXO Y:\n",d);
      scanf("%i",&p[d-1].y);

    default: printf("PONTO INVALIDO\n");
  }
}

float dist(ponto p[])
{
    float d2,xt,yt,d;

    xt=p[1].x-p[0].x; yt=p[1].y-p[0].y;

    d2=(pow(xt,2)+pow(yt,2));

    d=sqrt(d2);

    return d;
}

int quadrante(ponto p[],int escolha, int quadra)
{
  int d,c,loop1=1;
  int quad,trava_4=0;

  printf("DEFINA O PONTO:\n");
  scanf("%i",&d);

  switch(d)
  {
    case 1:
    if(p[0].x>0 && p[0].y>0)
    {
      quad=1;
    }

    else if(p[0].x<0 && p[0].y>0)
    {
      quad=2;
    }

    else if(p[0].x<0 && p[0].y<0)
    {
      quad=3;
    }

    else if(p[0].x>0 && p[0].y<0)
    {
      quad=4;
    }

    else if(p[0].x==0 && p[0].y==0)
    {
      quad=5;
    }

    else if(p[0].x!=0 && p[0].y==0)
    {
      quad=6;
    }

    else if(p[0].x!=0 && p[0].y==0)
    {
      quad=7;
    }

    break;

    case 2:
    if(p[1].x>0 && p[1].y>0)
    {
      quad=1;
    }

    else if(p[1].x<0 && p[1].y>0)
    {
      quad=2;
    }

    else if(p[1].x<0 && p[1].y<0)
    {
      quad=3;
    }

    else if(p[1].x>0 && p[1].y<0)
    {
      quad=4;
    }

    else if(p[1].x==0 && p[1].y==0)
    {
      quad=5;
    }

    else if(p[1].x!=0 && p[1].y==0)
    {
      quad=6;
    }

    else if(p[1].x!=0 && p[1].y==0)
    {
      quad=7;
    }

    break;

    default: quad=0; printf("PONTO INVALIDO\n");
  }

  if(escolha==4 && quad!=0)
  {
    while(loop1==1)
    {
      printf("DEFINA O QUADRANTE:\n");
      scanf("%i",&c);

      if(c>0 && c<5)
      {
        loop1=0;
        trava_4=1;
      }

      else
      {
        printf("QUADRANTE INVALIDO\n");
      }
    }
  }

  if(quad==c && trava_4==1)
  {
    printf("QUADRANTE CORRETO\n");
  }

  else if(trava_4==1)
  {
    printf("QUADRANTE INCORRETO\n");

  }

  return quad;
}

void write_quadrante(int quadra)
{
  if(quadra==1)
  {
    printf("O PONTO ESTA NO 1 QUADRANTE\n");
  }

  else if(quadra==2)
  {
    printf("O PONTO ESTA NO 2 QUADRANTE\n");
  }

  else if(quadra==3)
  {
    printf("O PONTO ESTA NO 3 QUADRANTE\n");
  }

  else if(quadra==4)
  {
    printf("O PONTO ESTA NO 4 QUADRANTE\n");
  }

  else if(quadra==5)
  {
    printf("O PONTO ESTA NO CENTRO\n");
  }

  else if(quadra==6)
  {
    printf("O PONTO ESTA NO EIXO X\n");
  }

  else if(quadra==7)
  {
    printf("O PONTO ESTA NO EIXO Y\n");
  }

  else
  {

  }
}

void cord(ponto p[])
{
  int d;

  printf("ESCOLHA O PONTO:\n");
  scanf("%i",&d);

  switch(d)
  {
    case 1:
      if(p[0].x>p[0].y)
      {
        printf("X = %i\n",p[0].x);
      }

      else if(p[0].x<p[0].y)
      {
        printf("Y = %i\n",p[0].y);
      }

      else
      {
        printf("AMBOS = %i\n",p[0].y);
      }

      break;

    case 2:
    if(p[1].x>p[1].y)
    {
      printf("X = %i\n",p[1].x);
    }

    else if(p[1].x<p[1].y)
    {
      printf("Y = %i\n",p[1].y);
    }

    else
    {
      printf("AMBOS = %i\n",p[1].y);
    }

    break;

    default: printf("PONTO INVALIDO\n");
  }
}
