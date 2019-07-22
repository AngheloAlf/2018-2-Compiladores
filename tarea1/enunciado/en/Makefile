URL = https://www.gutenberg.org/files/2701/2701-h/2701-h.htm

all: tarea-1.pdf MobyDick.txt.gz README.pdf

tarea-1.pdf: tarea-1.tex condiciones.tex
	latexmk -pdf -shell-escape $<

MobyDick.txt.gz: MobyDick.txt
	gzip -9f $<

MobyDick.txt:
	links -dump 1 $(URL) > $@

README.pdf: README.md
	pandoc $^ -o $@

clean:
	rm tarea-1.pdf MobyDick.txt MobyDick.txt README.pdf

.PHONY: all clean
