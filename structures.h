#ifndef structures_h
#define structures_h

char START_SYMBOL;

typedef struct production{
  char head;
  char *body;
  int pos;
  struct production *next_prod;
}production;

typedef struct states{
  int no_of_prod;
  production *productions;
  struct states *next_state;
}states;

typedef struct set{
  states *states;
}set;

#endif
