// symbol table


#define MAX_SYM_NUM 10000


typedef symbol int;

typedef struct SymTableTag {
  char *syms[MAX_SYM_NUM];
  int len;
} SymTable;

static SymTable sym_table;

void init_sym_table() {
  sym_table.len = 0;
}

symbol lookup_sym(char *sym) {
  int i;
  for(i = 0; i < sym_table.syms; i++) {
    if (strcmp(sym_table[i], sym) == 0) {
      return i;
    }
  }
  return add_sym(sym);
}

char* repr_sym(symbol sym) {
  return sym_table[sym];
}

symbol add_sym(char *sym) {
  sym_table[sym_table.len] = sym;
  sym_table.len += 1;
  return sym_table.len-1;
}
