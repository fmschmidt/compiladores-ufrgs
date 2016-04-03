/*
  Grupo01
  Felipe de Medeiros Schmidt
  William Bombardelli da Silva
*/
%{
#include "parser.h" //arquivo automaticamente gerado pelo bison
#include "cc_misc.h"

#define ACAO_ADD_TABELA_SIMBOLOS symbol_table->add(symbol_table, SymbolTableEntry_construct(yytext, line_number) );

extern int line_number; //Numero da linha
extern SymbolTable* symbol_table; //Tabela de simbolos
extern SymbolTableEntry* symbol_table_entry; //Uma entrada da tabela de simbolos
%}

ER_IDENTIFICADOR  ([a-z]|[A-Z]|_)([a-z]|[A-Z]|_|[0-9])*
ER_ERRO           .
%%

  /* Fim de linha -> nova linha */
\n                    { line_number++; }    

  /* Expressões regulares dos tokens */
{ER_IDENTIFICADOR}    { ACAO_ADD_TABELA_SIMBOLOS return TK_IDENTIFICADOR; }
{ER_ERRO}             { return TOKEN_ERRO; }


%%
