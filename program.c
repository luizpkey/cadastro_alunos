//...............................................................................//
// Bibliotecas da linguagem C(mingw)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//===============================================================================//
// Estrutura de Aluno
typedef struct{
   int RA;
   char nome[50];
   char endereco[125];
   char curso[80];
} Aluno;

//===============================================================================//
// Estrutura de item do menu
typedef struct{
   char descricao[50];
   int opcao;
} ItemMenu;

/*********************************************************************************
 * Fun��o para pausar
 *********************************************************************************/
void pause(){
   system("pause");
}

/*********************************************************************************
 * Fun��o limpar o buffer // https://pt.stackoverflow.com/questions/9427/limpeza-do-buffer-do-teclado-ap%C3%B3s-scanf
 *********************************************************************************/
void flush_in()
{
   int ch;
   do
   {
      ch = fgetc(stdin);
   } while (ch != EOF && ch != '\n');
}
/*********************************************************************************
 * Fun��o para limpar a tela
 *********************************************************************************/
void clear()
{
   #ifdef _WIN32
         system("cls");
   #else
         system("clear");
   #endif
}
/*********************************************************************************
// Fun��o do menu principal
//    - Retorna a op��o escolhida
 *********************************************************************************/
int Menu()
{
   ItemMenu menu[4] = {
                        {"Cadastrar Aluno", 1}, // Op��o de cadastro e c�digo para identifica��o
                        {"Alterar Aluno"  , 2}, // Op��o de alteracao e c�digo para identifica��o
                        {"Listar Alunos"  , 3}, // op��o de listagem e c�digo para identifica��o
                        {"Sair"           , 4}  // Op��o de sa�da e ... c�digo
                     };
   int n;
   clear();
   printf("Escolha uma op��o: \n");
   for (n = 0; n < 4; n++)
   {
      printf("%d - %s\n", menu[n].opcao, menu[n].descricao);
   }
   scanf("%d", &n);
   flush_in();
   return n;
};

/*********************************************************************************
 * Fun��o cadastro de aluno
 *    - 1 parametro/Argumento: Recebe o (ponteiro) que representa array da struct Aluno.
 *    - 2 parametro/Argumento: Recebe a posi��o atual do aluno atual.
 *********************************************************************************/
int CadastraAluno(Aluno *alunos, int sequencial)
{
   int RA, n, retorno = 0;
   char nome[50], endereco[125], curso[80];
   Aluno *alunoAtual, *aluno;
   clear();
   ItemMenu menu[2] = {{"Confirmar", 1}, {"Cancelar", 0}};

   // Inicializa��o das vari�veis
   RA = 0;
   strcpy(nome, "");
   strcpy(endereco, "");
   strcpy(curso, "");

   // Cadastro
   while ( RA <= 0){
      clear();
      printf("Cadastrando Aluno\n");
      printf("RA: ([-1]->Abandona)");
      scanf("%i", &RA);
      flush_in();

      if (RA==-1){
         printf("Voltando ao menu principal!\n");
         pause();
         return retorno;
      }

      if (RA>0){
         for (n=0;n<=sequencial;n++){
            aluno = &alunos[n];
            if(aluno->RA==RA){
               printf("RA j� informado!\n");
               pause();
               RA=0;
               break;
            }
         }
      }else{
         printf("RA inv�lido!\n");
         pause();         
      }
   }

   printf("Nome: ");
   scanf("%s", &nome);
   flush_in();

   printf("Endere�o: ");
   scanf("%s", &endereco);
   flush_in();

   printf("Curso: ");
   scanf("%s", &curso);
   flush_in();

   // Confirma��o de inclus�o
   printf("Deseja Cadastrar o Aluno?\n");
   for (n = 0; n < 2; n++)
   {
      printf("%d - %s\n", menu[n].opcao, menu[n].descricao);
   }
   scanf("%d", &n);
   flush_in();

   if (n == 1){ // Atribui��o de dados ao alunoAtual
      alunoAtual = &alunos[sequencial];
      alunoAtual->RA = RA;
      strcpy(alunoAtual->nome, nome);
      strcpy(alunoAtual->endereco, endereco);
      strcpy(alunoAtual->curso, curso);
      retorno = 1; // Retorno afirmativo para incrementar o sequencial
   }

   free(RA);
   free(nome);
   free(endereco);
   free(curso);
   free(n);
//   free(aluno); // causa erro pois est� associado ao ponteiro criado com malloc
//   free(alunoAtual); // causa erro pois est� associado ao ponteiro criado com malloc
   return retorno;
}

/*********************************************************************************
 * Fun��o para listar os alunos
 *    - 1 parametro/Argumento: Recebe o array de alunos
 *    - 2 parametro/Argumento:Recebe a quantidade de alunos
 *********************************************************************************/
void listarAlunos( Aluno *alunos, int quantidadeDeAlunos)
{
   int n;
   Aluno *aluno;
   clear();

   printf("Lista de Alunos:\n");
   for (n = 0; n < quantidadeDeAlunos; n++)
   {
      aluno = &alunos[n];
      printf("RA: %d\n", aluno->RA);
      printf("Nome: %s\n", aluno->nome);
      printf("Endere�o: %s\n", aluno->endereco);
      printf("Curso: %s\n\n", aluno->curso);
   }
   pause();
}

/*********************************************************************************
 * Fun��o para alterar os alunos
 *    - 1 parametro/Argumento: Recebe o array de alunos
 *    - 2 parametro/Argumento:Recebe a quantidade de alunos
 *********************************************************************************/
void AlteraAluno(Aluno *alunos, int quantidadeDeAlunos)
{
   int RA, n, alunosValidos;
   Aluno *aluno;
   char nome[50], endereco[125], curso[80];

   clear();
   alunosValidos=0;
   for (n = 0; n < quantidadeDeAlunos; n++){
      aluno = &alunos[n];
      if( aluno->RA != 0 ){
         alunosValidos++;
         printf("%d - %s\n", aluno->RA, aluno->nome);
      }
   }

   if (alunosValidos>0){
      printf("Qual RA deseja alterar? ");
      scanf("%d", &RA);
      flush_in();
      for (n = 0; n < quantidadeDeAlunos; n++){
         aluno = &alunos[n];
         if (aluno->RA == RA)
         {
            printf("\nNome: %s: Digit o novo nome[branco n�o altera]: ", aluno->nome);
            scanf("%s", &nome);
            flush_in();
   
            if (strlen(nome) > 0)
            {
               strcpy( &aluno->nome, nome);
            }
            printf("\nEndere�o: %s: Digite o novo endere�o[branco n�o altera]: ", aluno->endereco);
            scanf("%s", &endereco);
            flush_in();
   
            if (strlen(endereco) > 0)
            {
               strcpy(aluno->endereco, endereco);
            }
            printf("\nCurso: %s: Digite o novo curso[branco n�o altera]: ", aluno->curso);
            scanf("%s", &curso);
            flush_in();
   
            if (strlen(curso) > 0)
            {
               strcpy(aluno->curso, curso);
            }
            break;
         }
      }
   }else{
      printf("Sem alunos a alterar!\n");
   }
   pause();
}

/*********************************************************************************
 * Fun��o principal do programa / Entrada do programa
 *********************************************************************************/
int main( int argc, char *argv[] )
{
   Aluno *alunos;
   Aluno *aluno;
   int quantidadeDeAlunos, sequencial = 0;
   int opcao = 0;

   setlocale(LC_ALL, NULL);
   setlocale(LC_ALL, "");
   clear();
   printf("Quantidade de alunos deseja cadastrar? ");
   scanf("%d", &quantidadeDeAlunos);
   flush_in();

   alunos = (Aluno *)malloc(sizeof(Aluno) * quantidadeDeAlunos);

   for (int n = 0; n < quantidadeDeAlunos; n++){
      aluno = &alunos[n];
      aluno->RA = 0;
      strcpy(aluno->nome, "Aluno ");
      strcpy(aluno->endereco, "Endere�o ");
      strcpy(aluno->curso, "Curso ");
   }

   while ((opcao = Menu()) != 4)
   {
      if (opcao == 1){
         if (CadastraAluno(alunos, sequencial) == 1)
         {
            sequencial++;
         };
      }else if (opcao == 2){
         AlteraAluno(alunos, quantidadeDeAlunos);
      }else if (opcao == 3){
         listarAlunos(alunos, quantidadeDeAlunos);
      }else
      {
         printf("Op��o Inv�lida!");
      }

   }

   return 0;
}
