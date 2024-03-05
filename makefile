lexer:
	gcc -o main driver.c lexer1.c
	./main text.txt parserOutput.txt
parser:
	gcc -o parser driver.c lexer1.c finalParser.c
	./parser text.txt parserOutput.txt