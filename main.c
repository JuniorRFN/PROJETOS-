#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// PROTOTIPO DAS FUNÇÕES
void bubblesort ();
void abrir();
void fechar();
void ler();
void escrever();
int contador();
void busca();
void escrever_nomes();
void escrever_nomes_nota();
int editar();
void nova_media();
float mediageral();

// STRUCT PARA A ALOCAÇÃO DE DADOS DE CADA ALUNO
typedef struct registro
{
  int matricula;
  char nome[100];
  float notas[3];
  float media;
} registro;

//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  // ABERTURA DO ARQUIVO
  FILE *texto;
  abrir(&texto);

  // CONTADOR DE LINHAS
  int linhas;
  linhas = contador(&texto, linhas);
  fechar(&texto);
  abrir(&texto);

  // ALOCAÇÃO DINAMICA DO VETOR DO STRUCT
  registro *dados = (registro *) malloc (linhas*sizeof(registro));

  // LEITURA DO DOCUMENTO
  int maior,menor;
  ler(&texto, dados, linhas, &maior, &menor);

  // VARIAVEIS NECESSARIAS
  int aprovado, nao_aprovado;
  float media_geral;
  FILE *novo_texto;

  while(1)
  {
    // MENU
    int destino;

    printf("----------MENU----------\n(BY JUNIOR FERNANDES)\n\n");
    printf("1. Imprimir todos os elementos do arranjo;\n");
    printf("2. Imprimir apenas os nomes dos alunos;\n");
    printf("3. Imprimir o nome dos alunos e sua respectiva nota final;\n");
    printf("4. Buscar os dados de um aluno usando a busca sequencial;\n");
    printf("5. Imprimir os alunos ordenados de acordo com sua matricula;\n");
    printf("6. Editar os dados de um aluno;\n");
    printf("7. Imprimir a matricula, nome e nota final do aluno que obteve a maior nota de todas;\n");
    printf("8. Imprimir a matricula, nome e nota final do aluno que obteve a menor nota de todas;\n");
    printf("9. Imprimir quantos alunos foram aprovados e quantos alunos foram reprovados, imprima ainda a media geral;\n");
    printf("10. Gerar novo arquivo alterado;\n");
    printf("0. Sair do programa;\n");


    scanf("%i", &destino);

    // CHAMADA DAS FUNÇÕES
    switch (destino)
    {
      case 0:
        free(dados);
        fechar(&texto);
        exit(0);
        break;

      case 1:
        nova_media(dados, linhas, &maior, &menor); escrever(dados,linhas); system("pause"); system("cls");
        break;

      case 2:
        escrever_nomes(dados,linhas); system("pause"); system("cls");
        break;

      case 3:
        nova_media(dados, linhas, &maior, &menor); escrever_nomes_nota(dados,linhas); system("pause"); system("cls");
        break;

      case 4:
        nova_media(dados, linhas, &maior, &menor); bubblesort(dados, linhas); busca(dados, linhas); system("pause"); system("cls");
        break;

      case 5:
        nova_media(dados, linhas, &maior, &menor); bubblesort(dados, linhas); escrever(dados, linhas); system("pause"); system("cls");
        break;

      case 6:
        editar(dados, linhas); nova_media(dados, linhas, &maior, &menor); system("pause"); system("cls");
        break;

      case 7:
        nova_media(dados, linhas, &maior, &menor);
        printf("%i ",dados[maior].matricula);
        printf("%s ",dados[maior].nome);
        printf("MEDIA: %.2f\n",dados[maior].media);
        system("pause"); system("cls");
        break;

      case 8:
        nova_media(dados, linhas, &maior, &menor);
        printf("%i ",dados[menor].matricula);
        printf("%s ",dados[menor].nome);
        printf("MEDIA: %.2f\n",dados[menor].media);
        system("pause"); system("cls");
        break;

      case 9:
        nova_media(dados, linhas, &maior, &menor);

        aprovado=0; nao_aprovado=0;

        for(int i=0; i <linhas; i++)
        {
          if (dados[i].media>=6.0)
          {
            aprovado++;
          }

          else if (dados[i].media<6.0)
          {
            nao_aprovado++;
          }
        }

        media_geral=mediageral(dados, linhas);
        printf("FORAM APROVADOS: %i ",aprovado);
        printf("NAO FORAM APROVADOS: %i ",nao_aprovado);
        printf("MEDIA GERAL: %.2f\n",media_geral);
        system("pause"); system("cls");
        break;

        case 10:
          novo_texto=fopen("novo_alunos.txt", "w");
          bubblesort(dados, linhas);

          for (int i = 0; i <linhas; i++)
          {
            fprintf(novo_texto,"%i ",dados[i].matricula);
            fprintf(novo_texto,"%s ",dados[i].nome);
            fprintf(novo_texto,"%.2f ",dados[i].notas[0]);
            fprintf(novo_texto,"%.2f ",dados[i].notas[1]);
            fprintf(novo_texto,"%.2f ",dados[i].notas[2]);
            fprintf(novo_texto,"MEDIA: %.2f\n",dados[i].media);
          }

            free(dados);
            fechar(&texto);
            exit(0);
            break;


        default:
          printf("INDICE INVALIDO\n"); system("pause"); system("cls");
          break;
      }
  }



  free(dados);
  fechar(&texto);
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////

// ORDENAÇÃO DAS MATRICULAS
void bubblesort (registro *dados, int linhas)
{
  int aux_matricula;
  char aux_nome[100];
  float aux_nota1, aux_nota2, aux_nota3, aux_media;

  for(int i=1; i<linhas; i++)
  {
    for(int j=0; j<linhas-1; j++)
    {
      if(dados[j].matricula>dados[j+1].matricula)
      {
        // MATRICULAS
        aux_matricula=dados[j].matricula;
        dados[j].matricula=dados[j+1].matricula;
        dados[j+1].matricula=aux_matricula;

        // NOMES
        strcpy(aux_nome,dados[j].nome);
        strcpy(dados[j].nome,dados[j+1].nome);
        strcpy(dados[j+1].nome,aux_nome);

        // NOTAS
        aux_nota1=dados[j].notas[0];
        dados[j].notas[0]=dados[j+1].notas[0];
        dados[j+1].notas[0]=aux_nota1;

        aux_nota2=dados[j].notas[1];
        dados[j].notas[1]=dados[j+1].notas[1];
        dados[j+1].notas[1]=aux_nota2;

        aux_nota3=dados[j].notas[2];
        dados[j].notas[2]=dados[j+1].notas[2];
        dados[j+1].notas[2]=aux_nota3;

        //MEDIAS
        aux_media=dados[j].media;
        dados[j].media=dados[j+1].media;
        dados[j+1].media=aux_media;
      }
    }
  }
}

// ABRE O ARQUIVO
void abrir(FILE **f)
{
  *f=fopen("alunos.txt", "a+");

  // TESTANDO SE O ARQUIVO REALMENTE ABRIU
  if (*f == NULL)
  {
    printf("Error: alunos.txt");
    exit(1);
  }

}

// FECHA O ARQUIVO
void fechar(FILE **f)
{
  fclose(*f);
}

// FUNÇÃO PARA LER OS DADOS DO ARQUIVO E ALOCAR NA STRUCT
void ler(FILE **texto,registro *dados,int linhas)
{
  for (int i=0; i<linhas; i++)
  {
    fscanf(*texto,"%i",&dados[i].matricula);
    fscanf(*texto,"%s",&dados[i].nome);
    fscanf(*texto,"%f",&dados[i].notas[0]);
    fscanf(*texto,"%f",&dados[i].notas[1]);
    fscanf(*texto,"%f",&dados[i].notas[2]);

    // GERAR A MEDIA
    dados[i].media=(dados[i].notas[0]+dados[i].notas[1]+dados[i].notas[2])/3.0;
  }
}

// ESCREVE TODA A STRUCT
void escrever(registro *dados, int linhas)
{
  for (int i = 0; i <linhas; i++)
  {
    printf("%i ",dados[i].matricula);
    printf("%s ",dados[i].nome);
    printf("%.2f ",dados[i].notas[0]);
    printf("%.2f ",dados[i].notas[1]);
    printf("%.2f ",dados[i].notas[2]);
    printf("MEDIA: %.2f\n",dados[i].media);
  }
}

// CONTADOR DE LINHAS
int contador(FILE **texto, int linhas)
{
  linhas=0;
  char count;

  while((count=fgetc(*texto))!=EOF)
  {
    if(count=='\n')
    {
      linhas++;
    }
  }

  return linhas;
}

// BUSCA SEQUENCIAL
void busca (registro *dados, int linhas)
{
  int matricula;
  printf("DIGITE O NUMERO DA MATRICULA:\n\n");
  scanf("%i",&matricula);

  int teste=0;

  for (int i = 0; i <linhas; i++)
  {
    if (matricula==dados[i].matricula)
    {
      printf("%i ",dados[i].matricula);
      printf("%s ",dados[i].nome);
      printf("%.2f ",dados[i].notas[0]);
      printf("%.2f ",dados[i].notas[1]);
      printf("%.2f ",dados[i].notas[2]);
      printf("MEDIA: %.2f\n\n\n",dados[i].media);

      teste=1;
    }
  }

  if(teste==0)
  {
    printf("MATRICULA NAO ENCONTRADA\n\n");
  }
}

// ESCREVE APENAS OS NOMES
void escrever_nomes(registro *dados, int linhas)
{
  for (int i = 0; i <linhas; i++)
  {
    printf("%s\n",dados[i].nome);
  }
}

// ESCREVE NOMES E NOTA FINAL (MEDIA)
void escrever_nomes_nota(registro *dados, int linhas)
{
  for (int i = 0; i <linhas; i++)
  {
    printf("%s // ",dados[i].nome);
    printf("NOTA FINAL: %.2f\n",dados[i].media);
  }
}

// EDITAR DADOS DE UM ALUNO
int editar (registro *dados, int linhas)
{
  int matricula, edit, i, certo;
  char nome[100];

  // BUSCA SEQUENCIAL
  printf("DIGITE O NUMERO DA MATRICULA:\n\n");
  scanf("%i",&matricula);

  int teste=0;

  for (i = 0; i <linhas; i++)
  {
    if (matricula==dados[i].matricula)
    {
      printf("%i ",dados[i].matricula);
      printf("%s ",dados[i].nome);
      printf("%.2f ",dados[i].notas[0]);
      printf("%.2f ",dados[i].notas[1]);
      printf("%.2f ",dados[i].notas[2]);
      printf("MEDIA: %.2f\n\n\n",dados[i].media);

      certo=i;
      teste=1;
    }
  }

  if (teste==1)
  {
      // ALTERAÇÃO
      printf("O QUE QUER ALTERAR:\n");
      printf("1. MATRICULA;\n");
      printf("2. NOME;\n");
      printf("3. NOTA 1;\n");
      printf("4. NOTA 2;\n");
      printf("5. NOTA 3;\n");
      printf("0. VOLTAR AO MENU;\n");

      scanf("%i",&edit);

      switch(edit)
      {
        case 1:
          printf("NOVA MATRICULA:\n");
          scanf("%i",&dados[certo].matricula);
          break;

        case 2:
          printf("NOVO NOME:\n");
          setbuf(stdin, NULL);
          gets(nome);
          strcpy(dados[certo].nome,nome);
          break;

        case 3:
          printf("NOVA NOTA 1:\n");
          scanf("%f",&dados[certo].notas[0]);
          break;

        case 4:
          printf("NOVA NOTA 2:\n");
          scanf("%f",&dados[certo].notas[1]);
          break;

        case 5:
          printf("NOVA NOTA 3:\n");
          scanf("%f",&dados[certo].notas[2]);
          break;

        case 0:
          break;

        default:
          printf("VALOR INVALIDO");
          break;
    }
  }

  if(teste==0)
  {
    printf("MATRICULA NAO ENCONTRADA\n\n");
  }
}

// ALTERA A MEDIA E SETA O MAIOR E O MENOR
void nova_media(registro *dados,int linhas, int *maior, int *menor)
{
  int ma=0,me=11;

  for(int i=0; i <linhas; i++)
  {
    // GERAR A MEDIA
    dados[i].media=(dados[i].notas[0]+dados[i].notas[1]+dados[i].notas[2])/3.0;

    if (dados[i].media>ma)
    {
      *maior=i;
      ma=dados[i].media;
    }

    if (dados[i].media<me)
    {
      *menor=i;
      me=dados[i].media;
    }
  }
}

// MEDIA GERAL
float mediageral (registro *dados,int linhas)
{
  float soma = 0, media;

  for(int i=0; i < linhas; i++)
  {
    soma+=dados[i].media;
  }

  media=soma/linhas;

  return media;
}
