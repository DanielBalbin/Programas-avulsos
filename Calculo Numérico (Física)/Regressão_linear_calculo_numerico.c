/*-------------------Regre��o linear-----------------------*/
/*                                                         */
/* Nome: Daniel Rodrigues Balbin                           */
/*---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*Fun��o para realizar somatorias*/
double SOMATORIA( double *dados, int ini,int fim)
{
    int i;
    double soma=0;
    for( i=ini; i<fim;i++)
    {
        soma += dados[i];
    }
    return soma;
}

/*Fun��o de soma e multiplica��o simultanea*/
double SOMATORIAX( double *xi, double *fi, int ini,int fim)
{
    int i;
    double soma=0;
    for( i=ini; i<fim;i++)
    {
        soma += (xi[i])*(fi[i]);
    }
    return soma;
}

/*Fun��o para escaneamento de vetores, recebe o vetor e seu tamanho*/
double *SCANVET( double *vetor, int tamanho)
{
       double transf;
       int i;
       for( i=0; i<tamanho; i++)
       {
             scanf("%lf",&transf);
             vetor[i] = transf;
       }
       return vetor;
}

/*Fun��o para zerar todos os valores de uma matriz, recebe a matriz e suas dimen��es*/
void ZERAMAT( double **mat,int linhas,int colunas)
{
    int i,j;
    for( i=0; i<linhas; i++)
    {
        for( j=0; j<colunas; j++)
        {
            mat[i][j] = 0;
        }
    }
}

/*Fun��o para impress�o de matrizes. Criada para auxiliar o debug*/
void PRINTMAT( double **mat,int linhas,int colunas)
{
    int i,j;
    for( i=0; i<linhas; i++)
    {
        for( j=0; j<colunas; j++)
        {
            printf( "%g ", mat[i][j]);
        }
        printf( "\n");
    }
}

/*Fun��o para criar matrizes, recebe de argumentos um ponteiro de matriz e as dimens�es da matriz*/
double **CRIAMAT( double **mat, int linhas, int colunas)
{
    int i;
    mat = (double**)malloc(sizeof(double*)*linhas);
    for( i=0; i<linhas; i++)
    {
         mat[i] = (double*)malloc(sizeof(double)*colunas);
    }
    return mat;
}

/*Fun��o para transformar uma matriz numa matriz triangular superior*/
void MATTRISUP(double **mat,int linhas,int colunas)
{
     int i,j,k;
     double quo;/*quo � o cociente aji/aii que � multiplicado por cada elemento da linha antes da subtra��o*/
     for( i=0; i<(linhas-1); i++)
     {
          for( j=i+1; j<linhas; j++)
          {
               quo = (mat[j][i])/(mat[i][i]);
               for( k=0; k<colunas; k++)
               {
                    mat[j][k]= mat[j][k] - mat[i][k]*quo;
               }
          }
     }
}

/*Fun��o para zerar os valores de um vetor, recebe o vetor e seu tamanho*/
void ZERAVET(double *vetor, int tamanho)
{
     int i;
     for( i=0; i<tamanho; i++)
     {
          vetor[i]=0;
     }
}

/*Fun��o para resolver sistemas lineares no formato de matrizes atrav�s do metodo de Gauss*/
double *RESOLVE( double **mat, int linhas)
{
       int i,j;
       double *sol,soma = 0;
       sol = (double*)malloc(sizeof(double)*linhas);
       ZERAVET(sol,linhas);
       sol[linhas-1] = ( mat[linhas-1][linhas])/( mat[linhas-1][linhas-1]);
       for( i=(linhas-2); i>=0; i--)
       {

            for( j=linhas-1; j>i; j--)
            {
                   soma += mat[i][j]*sol[j];
            }
       sol[i] = ( mat[i][linhas] - soma)/( mat[i][i]);
       soma = 0;
       }
       return sol;
}

/*Fun��o para prenchimento de matrizes, dados um ponteiro para matrizes, as dimen��es da matriz e os valores para prechela esta criara uma matriz*/
double **SCANMAT( double **mat, int linhas, int colunas)
{
       int i,j;
       double tran;
       for( i=0; i<linhas; i++)
       {
            for( j=0; j<colunas; j++)
            {
                 scanf("%lf",&tran);
                 mat[i][j] = tran;
            }
       }
       return mat;
}

/*Fun��o para organizar a matriz do sistema linear*/
double ** MATSETUP( double **mat, double *xi, double *fi, int inicio, int fim)
{
    mat[0][0] = ( fim-inicio);
    mat[0][1] = SOMATORIA( xi, inicio, fim);
    mat[1][0] = mat[0][1];
    mat[1][1] = SOMATORIAX( xi, xi, inicio, fim);
    mat[0][2] = SOMATORIA( fi, inicio, fim);
    mat[1][2] = SOMATORIAX( xi, fi, inicio, fim);
    return mat;
}

int main()
{
    double *xi,*fi,**matriz, *sol;
    int n=0;
    /*-----------------------------------------------------------------*/
    /*  xi � o vetor que contem os valores de x                        */
    /*  fi � o vetor que contem os valores de f                        */
    /*  matriz � a matriz onde ser�o armazenados os valores do sitema  */
    /*  sol � o vetor que armazenara as solu��es do sistema            */
    /*  n � a quantidade de dados a serem armazenados                  */
    /*-----------------------------------------------------------------*/
    scanf( "%d", &n);
    xi = (double*)malloc( sizeof( double)*n);
    fi = (double*)malloc( sizeof( double)*n);
    xi = SCANVET( xi, n);
    fi = SCANVET( fi, n);
    matriz = CRIAMAT( matriz, 2, 3);
    matriz = MATSETUP( matriz, xi, fi, 0, 10);
/* Aqui geramos a matriz do primeiro conjunto de pontos 0.8 a 9.8*/
    MATTRISUP( matriz, 2, 3);
    sol = RESOLVE( matriz, 2);
    printf("\nx(0) = %lf\nx(1) = %lf\n", sol[0], sol[1]);
    matriz = MATSETUP( matriz, xi, fi, 17, 20);
/* Aqui geramos a matriz do segundo conjunto de pontos 11.4 a 11.8*/
    MATTRISUP( matriz, 2, 3);
    sol = RESOLVE( matriz, 2);
    printf("\nx(0) = %lf\nx(1) = %lf\n", sol[0], sol[1]);
    return 0;
}
