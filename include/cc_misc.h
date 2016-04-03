#ifndef __MISC_H
#define __MISC_H
#include <stdio.h>

/**
 * Tipo: Entrada da tabela de simbolos
 */
typedef struct s_SymbolTableEntry{
  char* key;
  int value;
  struct s_SymbolTableEntry* next;
} SymbolTableEntry;

SymbolTableEntry* SymbolTableEntry_construct(const char* key, const int value);
void SymbolTableEntry_destruct(struct s_SymbolTableEntry* _this);

/**
 * Tipo: Tabela de simbolos
 */
typedef struct s_SymbolTable{
  SymbolTableEntry* first;
  
  void (*add)(struct s_SymbolTable*, SymbolTableEntry*);
} SymbolTable;

SymbolTable* SymbolTable_construct();
void SymbolTable_destruct(struct s_SymbolTable* _this);
void SymbolTable_add(struct s_SymbolTable* _this, SymbolTableEntry* _new);

int getLineNumber (void);
void yyerror (char const *mensagem);
void main_init (int argc, char **argv);
void main_finalize (void);

#endif
