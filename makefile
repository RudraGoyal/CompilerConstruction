lexer:
	gcc -o main driver.c lexer1.c
	./main text.txt parserOutput.txt
parser:
	# rm "./parser.exe"
	gcc -o parser driver.c parser.c lexer.c
	./parser text.txt parserOutput.txt
run:
	./parser text.txt parserOutput.txt
