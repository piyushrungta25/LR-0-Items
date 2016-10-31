all:
	gcc items.c states.c sets.c gotos.c -fopenmp -o bin/items
