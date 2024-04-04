//===============================================================================//
// Estrutura de item do menu
#ifndef ITEM_MENU_H
   #define ITEM_MENU_H
   typedef struct
   {
      char descricao[50];
      int opcao;
   } ItemMenu;

   #define MENU_PRINCIPAL_CADASTRO      1
   #define MENU_PRINCIPAL_ALTERAR       2
   #define MENU_PRINCIPAL_EXCLUIR       3
   #define MENU_PRINCIPAL_LISTAR        4
   #define MENU_PRINCIPAL_REDIMENSIONAR 5
   #define MENU_PRINCIPAL_SAIDA         6
   #define MENU_PRINCIPAL_TAMANHO_MENU  6
#endif
