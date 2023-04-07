comp: bstree.o hashtab.o bstree_main.o
	gcc -Wall bstree.o hashtab.o bstree_main.o -o main
bstree.o: bstree.c
	gcc -c bstree.c
hashtab.o: hashtab.c
	gcc -c hashtab.c
bstree_main.o: bstree_main.c
	gcc -c bstree_main.c
clean: 
	rm bstree.o bstree_main.o hashtab.o main