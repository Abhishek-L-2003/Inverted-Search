result.exe: main.o create.o deleteduplicates.o display.o save.o search.o update.o validate_file.o validate.o
	gcc -o result.exe main.c create.c deleteduplicates.c display.c save.c search.c update.c validate_file.c validate.c
main.o: main.c
	gcc -c main.c
validate.o: validate.c
	gcc -c validate.c
create.o: create.c
	gcc -c create.c
deleteduplicates.o: deleteduplicates.c
	gcc -c deleteduplicates.c
display.o: display.c
	gcc -c display.c
save.o: save.c
	gcc -c save.c
search.o: search.c
	gcc -c search.c
update.o: update.c
	gcc -c update.c
validate_file.o: validate_file.c
	gcc -c validate_file.c
clean:
	rm *.exe *.o