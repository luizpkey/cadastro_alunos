//===============================================================================//
// Estrutura de Aluno
#ifndef ALUNO_H
   #define ALUNO_H
   typedef struct
   {
      int RA;
      char nome[50];
      char endereco[125];
      char curso[80];
   } Aluno;
#endif