#ifndef gotos_h
#define gotos_h
#include "structures.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


gotos *get_empty_goto();
mappings *get_empty_mappings();
void push_goto_in_mapping(gotos *, mappings *);
void print_mappings(mappings *);
bool goto_in_mapping(gotos *,mappings *);
void delete_gotos(gotos *);
void delete_goto(gotos *);
void delete_mapping(mappings *);

#endif
