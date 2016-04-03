#include "cc_misc.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*======================================================================*/
/**
 * Variaveis Globais
 */
//Tabela de simbolos
SymbolTable* symbol_table = NULL;

//Uma entrada da tabela de simbolos
SymbolTableEntry* symbol_table_entry = NULL;

//Controle de linha de arquivo
int line_number = 1;

/*======================================================================*/
/**
 * Funções Miscelaneas
 */
int comp_get_line_number (void)
{
  //implemente esta função => OK
  assert (line_number > 0);
  return line_number;
}

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s. Linha: %d\n", mensagem, line_number); //altere para que apareça a linha => OK
}

void main_init (int argc, char **argv)
{
  //implemente esta função com rotinas de inicialização, se necessário => OK
  symbol_table = SymbolTable_construct();
}

void main_finalize (void)
{
  //implemente esta função com rotinas de inicialização, se necessário => OK
  SymbolTable_destruct(symbol_table);
  symbol_table = NULL;
}

void comp_print_table (void)
{
  //para cada entrada na tabela de símbolos
  //Etapa 1: chame a função cc_dict_etapa_1_print_entrada
  //implemente esta função => OK

  assert(symbol_table != NULL);
  
  if ( symbol_table->first != NULL){  
    SymbolTableEntry* currentEntry = symbol_table->first;
    do{
      cc_dict_etapa_1_print_entrada(currentEntry->key, currentEntry->value);
      currentEntry = currentEntry->next;
    }while (currentEntry != NULL);
  }
}

/*======================================================================*/
/**
 * Definição dos métodos de SymbolTableEntry
 */
SymbolTableEntry* SymbolTableEntry_construct(const char* key, const int value){
  SymbolTableEntry* _this;
  _this = malloc(sizeof(SymbolTableEntry));
  
  _this->key = malloc(strlen(key)+1);
  strcpy(_this->key, key);
  _this->value = value;
  _this->next = NULL;

  return _this;
}

void SymbolTableEntry_destruct(struct s_SymbolTableEntry* _this){
  assert (_this != NULL);

  free(_this->key);
  _this->key = NULL;
  _this->next = NULL;
  free(_this);
}

/*======================================================================*/
/**
 * Definição dos métodos de SymbolTable
 */
SymbolTable* SymbolTable_construct(){
  SymbolTable* _this;
  _this = malloc(sizeof(SymbolTable));
  _this->add = &SymbolTable_add;
  
  _this->first = NULL;

  return _this;
}

void SymbolTable_destruct(struct s_SymbolTable* _this){
  assert (_this != NULL);

  SymbolTableEntry* current = _this->first;
  SymbolTableEntry* next;
  while (current != NULL){
    next = current->next;
    SymbolTableEntry_destruct(current);
    current = next;
  }
  free(_this);
}

void SymbolTable_add(struct s_SymbolTable* _this, SymbolTableEntry* _new){
  assert (_this != NULL);
  assert (_new != NULL);

  if (_this->first == NULL){
    _this->first = _new;
    _this->first->next = NULL;
  }else{

    SymbolTableEntry* current = _this->first;
    SymbolTableEntry *old, *prev = NULL;
    //Procura chave na tabela
    do{
      //se encontrou
      if (!strcmp(current->key, _new->key)){
        old = current;

        //Atualiza entrada
        current = _new; 
        current->next = old->next;

        //Atualiza ponteiro da anterior
        if (prev != NULL)
          prev->next = current;

        //Atualiza ponteiro da primeira
        if (old == _this->first)
          _this->first = current;

        //Destroi entrada antiga
        SymbolTableEntry_destruct(old);
        old = NULL;
        break;
      }else{
        prev = current;
      }
    }while((current = current->next) != NULL); //Segue procurando pela proxima entrada
    
    //Se não havia esta chave na tabela ainda
    if (current == NULL){
      //Então adiciona-la
      assert (prev != NULL); //Há ao menos uma entrada
      assert (prev->next == NULL); //Ao final    
      prev->next = _new;
      _new->next = NULL;
    }
  }
}

