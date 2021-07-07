CC =		cc

OBJ1 =		byte.o symbol.o cldict.o interp.o drive.o lex.o lexcmd.o
OBJ2 =		primitive.o line.o courier.o object.o number.o 
OBJ3 =		syms.o main.o process.o array.o file.o block.o
OBJ4 =		string.o class.o
OBJ =		$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)

# In following line, we must use a command file since there are too many
# arguments for AmigaDos to deal with.

st :		$(OBJ)
		ln -F st.ln

byte.o :	byte.c
		$(CC) -c $(CFLAGS) byte.c

symbol.o :	symbol.c
		$(CC) -c $(CFLAGS) symbol.c

cldict.o :	cldict.c
		$(CC) -c $(CFLAGS) cldict.c

interp.o :	interp.c
		$(CC) -c $(CFLAGS) interp.c

drive.o :	drive.c
		$(CC) -c $(CFLAGS) drive.c

lex.o :	lex.c
		$(CC) -c $(CFLAGS) lex.c

lexcmd.o :	lexcmd.c
		$(CC) -c $(CFLAGS) lexcmd.c

primitive.o :	primitive.c
		$(CC) -c $(CFLAGS) primitive.c

line.o :	line.c
		$(CC) -c $(CFLAGS) line.c

courier.o :	courier.c
		$(CC) -c $(CFLAGS) courier.c

object.o :	object.c
		$(CC) -c $(CFLAGS) object.c

number.o  :	number.c
		$(CC) -c $(CFLAGS) number.c

syms.o :	syms.c
		$(CC) -c $(CFLAGS) syms.c

main.o :	main.c
		$(CC) -c $(CFLAGS) main.c

process.o :	process.c
		$(CC) -c $(CFLAGS) process.c

array.o :	array.c
		$(CC) -c $(CFLAGS) array.c

file.o :	file.c
		$(CC) -c $(CFLAGS) file.c

block.o :	block.c
		$(CC) -c $(CFLAGS) block.c

string.o :	string.c
		$(CC) -c $(CFLAGS) string.c

class.o :	class.c
		$(CC) -c $(CFLAGS) class.c
