parser:
	rm -f parser
	gcc -o parser driver.c parser.c lexer.c
	./parser "./TestCases/t4.txt" parserOutput.txt