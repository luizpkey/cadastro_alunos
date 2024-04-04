//...............................................................................//
// Bibliotecas da linguagem C(mingw)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Bibliotecas do projeto
#include "./include/itemMenu.h"
#include "./include/aluno.h"

#include "./utils.c"

#define _FALHA 0
#define _SUCESSO 1

Aluno *alunos;

/*********************************************************************************
// Funcao do menu principal
//    - Retorna a opcao escolhida
 *********************************************************************************/
int menu()
{
   ItemMenu menu[MENU_PRINCIPAL_TAMANHO_MENU] = {
                        {"Cadastrar Aluno"     , MENU_PRINCIPAL_CADASTRO },
                        {"Alterar Aluno"       , MENU_PRINCIPAL_ALTERAR },
                        {"Excluir Aluno"       , MENU_PRINCIPAL_EXCLUIR },
                        {"Listar Alunos"       , MENU_PRINCIPAL_LISTAR },
                        {"Redimensionar lista" , MENU_PRINCIPAL_REDIMENSIONAR },
                        {"Sair"                , MENU_PRINCIPAL_SAIDA }
                     };
   int n;
   clear();
   printf("Escolha uma opcao: \n");
   for (n = 0; n < MENU_PRINCIPAL_TAMANHO_MENU; n++)
   {
      printf("%d - %s\n", menu[n].opcao, menu[n].descricao);
   }
   scanf("%d", &n);
   fflush(stdin);
   return n;
};

/*********************************************************************************
 * Funcao cadastro de aluno
 *    - 1 parametro/Argumento: Recebe a posicao atual do aluno atual.
 *********************************************************************************/
int CadastraAluno( int sequencial)
{
   int RA, n, retorno = _FALHA;
   char nome[50], endereco[125], curso[80];
   Aluno *alunoAtual, *aluno;
   clear();
   ItemMenu menu[2] = {{"Confirmar", _SUCESSO }, {"Cancelar", _FALHA }};

   // Inicializacao das variaveis
   RA = 0;
   strcpy(nome, "");
   strcpy(endereco, "");
   strcpy(curso, "");

   // Cadastro
   while ( RA <= 0){
      clear();
      printf("Cadastrando Aluno\n");
      printf("RA: ([0]->Abandona)");
      scanf("%i", &RA);
      fflush(stdin);

      if (RA==0){
         printf("Voltando ao menu principal!\n");
         pause();
         return retorno;
      }

      if (RA>0){
         for (n=0;n<=sequencial;n++){
            aluno = &alunos[n];
            if(aluno->RA==RA){
               printf("RA ja informado!\n");
               pause();
               RA=0;
               break;
            }
         }
      }else{
         printf("RA invalido!\n");
         pause();
      }
   }

   printf("Nome: ");
   scanf("%[^\n]", &nome);
   fflush(stdin);

   printf("Endereco: ");
   scanf("%[^\n]", &endereco);
   fflush(stdin);

   printf("Curso: ");
   scanf("%[^\n]", &curso);
   fflush(stdin);

   // Confirmacao de inclusao
   printf("Deseja Cadastrar o Aluno?\n");
   for (n = 0; n < 2; n++)
   {
      printf("%d - %s\n", menu[n].opcao, menu[n].descricao);
   }
   scanf("%d", &n);
   fflush(stdin);

   if (n == _SUCESSO ){ // Atribuicao de dados ao alunoAtual
      alunoAtual = &alunos[sequencial];
      alunoAtual->RA = RA;
      strcpy(alunoAtual->nome, nome);
      strcpy(alunoAtual->endereco, endereco);
      strcpy(alunoAtual->curso, curso);
      retorno = _SUCESSO; // Retorno afirmativo para incrementar o sequencial
   }

   free(RA);
   free(nome);
   free(endereco);
   free(curso);
   free(n);
//   free(aluno); // causa erro pois esta associado ao ponteiro criado com malloc
//   free(alunoAtual); // causa erro pois esta associado ao ponteiro criado com malloc
   return retorno;
}

/*********************************************************************************
 * Funcao para carregar dados dos alunos
 *********************************************************************************/
void inicializaAluno(Aluno *aluno)
{
   aluno->RA = 0;
   strcpy(aluno->nome, "Aluno ");
   strcpy(aluno->endereco, "Endereco ");
   strcpy(aluno->curso, "Curso ");
}

void carregaValores(int quantidadeDeAlunos)
{
   Aluno *aluno;
   for (int n = 0; n < quantidadeDeAlunos; n++)
   {
      aluno = &alunos[n];
      inicializaAluno(aluno);
   }
}

/*********************************************************************************
 * Funcao para listar os alunos
 *    - 1 parametro/Argumento:Recebe a quantidade de alunos
 *********************************************************************************/
int listarAlunos(  int quantidadeDeAlunos)
{
   int n, alunosValidos = 0;
   Aluno *aluno;
   clear();

   printf("Lista de Alunos:\n");
   printf(" RA | Nome | Endereco | Curso\n");
   for (n = 0; n < quantidadeDeAlunos; n++)
   {
      aluno = &alunos[n];
      if (aluno->RA > 0){
         printf(" %d |", aluno->RA);
         printf(" %s |", aluno->nome);
         printf(" %s |", aluno->endereco);
         printf(" %s |\n", aluno->curso);
         alunosValidos++;
      }
   }
   if (alunosValidos==0 ){
      printf("Nenhum aluno cadastrado!\n");
   }
   return alunosValidos;

}

/*********************************************************************************
 * Funcao para alterar os alunos
 *    - 1 parametro/Argumento:Recebe a quantidade de alunos
 *********************************************************************************/
void AlteraAluno( int quantidadeDeAlunos)
{
   int RA, n, alunosValidos;
   Aluno *aluno;
   char nome[50], endereco[125], curso[80];

   clear();
   alunosValidos=listarAlunos( quantidadeDeAlunos);

   if (alunosValidos>0){
      printf("Qual RA deseja alterar? ");
      scanf("%d", &RA);
      fflush(stdin);

      for (n = 0; n < quantidadeDeAlunos; n++){
         aluno = &alunos[n];
         if (aluno->RA == RA)
         {
            printf("\nNome: %s: Digit o novo nome[branco nao altera]: ", aluno->nome);
            scanf("%[^\n]", &nome);
            fflush(stdin);

            if (strlen(nome) > 0)
            {
               strcpy( aluno->nome, nome);
            }
            printf("\nEndereco: %s: Digite o novo endereco[branco nao altera]: ", aluno->endereco);
            scanf("%[^\n]", &endereco);
            fflush(stdin);

            if (strlen(endereco) > 0)
            {
               strcpy(aluno->endereco, endereco);
            }
            printf("\nCurso: %s: Digite o novo curso[branco nao altera]: ", aluno->curso);
            scanf("%[^\n]", &curso);
            fflush(stdin);

            if (strlen(curso) > 0)
            {
               strcpy(aluno->curso, curso);
            }
            break;
         }
      }
   }
   pause();
}

/*********************************************************************************
 * Funcao para excluir os alunos
 *    - 1 parametro/Argumento:Recebe a quantidade de alunos
 *********************************************************************************/
int excluirAluno(int quantidadeDeAlunos)
{
   int RA, n, alunosValidos, retorno = _FALHA;
   Aluno *aluno;
   char nome[50], endereco[125], curso[80];

   clear();
   alunosValidos = listarAlunos(quantidadeDeAlunos);

   if (alunosValidos > 0)
   {
      printf("Qual RA deseja alterar? ");
      scanf("%d", &RA);
      fflush(stdin);

      for (n = 0; n < quantidadeDeAlunos; n++)
      {
         aluno = &alunos[n];
         if (aluno->RA == RA)
         {
            while (n<quantidadeDeAlunos-1){
               printf("RA: %d %d\n", alunos[n].RA, alunos[n + 1].RA);
               alunos[n] = alunos[n+1];
               n++;
            }
            aluno = &alunos[quantidadeDeAlunos-1];
            inicializaAluno(aluno);
            retorno  = _SUCESSO;
            break;
         }
      }
   }
   pause();
   return retorno;
}

/*********************************************************************************
 * Funcao principal do programa / Entrada do programa
 *********************************************************************************/
int alterarDimensao( int sequencial){
   int quantidadeDeAlunos;

   clear();
   printf("Quantidade de alunos deseja cadastrar? ");
   scanf("%d", &quantidadeDeAlunos);
   fflush(stdin);

   if (quantidadeDeAlunos < 0) {
      quantidadeDeAlunos = 0;
   }

   if (quantidadeDeAlunos < sequencial)
   {
      quantidadeDeAlunos = sequencial;
      printf("Quantidade de alunos nao pode ser menor\n que a quantidade de alunos cadastrados, \n alterando para %d!\n", sequencial);
      pause();
   }

   if (sequencial==0){
      alunos = (Aluno *)malloc(sizeof(Aluno) * quantidadeDeAlunos);
   }else{
      alunos = (Aluno *)realloc(alunos, sizeof(Aluno) * quantidadeDeAlunos);
   }

   return quantidadeDeAlunos;
}
/*********************************************************************************
 * Funcao principal do programa / Entrada do programa
 *********************************************************************************/
int main( int argc, char *argv[] )
{
   Aluno *aluno;
   int quantidadeDeAlunos, sequencial = 0;
   int opcao = 0;

   quantidadeDeAlunos = alterarDimensao( sequencial);
   carregaValores( quantidadeDeAlunos);

   while ((opcao =  menu()) != MENU_PRINCIPAL_SAIDA)
   {
      if ( opcao != MENU_PRINCIPAL_SAIDA
        && opcao != MENU_PRINCIPAL_LISTAR
        && opcao != MENU_PRINCIPAL_REDIMENSIONAR
        && quantidadeDeAlunos == sequencial){
         printf("Necessario redimensionar a lista!\n");
         pause();
         quantidadeDeAlunos = alterarDimensao( sequencial);
         if (quantidadeDeAlunos == sequencial){
            continue;
         }
      }
      if (opcao ==  MENU_PRINCIPAL_CADASTRO){
         if (CadastraAluno( sequencial) == _SUCESSO)
         {
            sequencial++;
         };
      }
      else if (opcao == MENU_PRINCIPAL_ALTERAR)
      {
         AlteraAluno( quantidadeDeAlunos);
      }
      else if (opcao == MENU_PRINCIPAL_EXCLUIR)
      {
         if (excluirAluno( quantidadeDeAlunos)== _SUCESSO){
            sequencial--;
         };
      }
      else if (opcao == MENU_PRINCIPAL_LISTAR)
      {
         listarAlunos( quantidadeDeAlunos);
         pause();
      }
      else if (opcao == MENU_PRINCIPAL_REDIMENSIONAR)
      {
         quantidadeDeAlunos = alterarDimensao( sequencial);
      }
      else
      {
         printf("Opcao Invalida!");
      }

   }

   return 0;
}
