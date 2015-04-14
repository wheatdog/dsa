TARGET=hw1_ans

all: $(TARGET).pdf

## Generalized rule: how to build a .pdf from each .tex
%.pdf: %.tex 
	pdflatex -interaction nonstopmode $<

touch:
	touch *.tex

again: touch all

clean:
	rm -f *.aux *.log *.nav *.out *.snm *.toc *.vrb || true

veryclean: clean
	rm -f $(TARGET).pdf

view: $(TARGET).pdf
	if [ "Darwin" = "$(shell uname)" ]; then open $(TARGET).pdf ; else evince $(TARGET).pdf ; fi

submit: $(TARGET).pdf
	cp $(TARGET).pdf ../

print: $(TARGET).pdf
	lpr $(TARGET).pdf

hw1: hw1_ans.pdf
	cygstart hw1_ans.pdf

.PHONY: all again touch clean veryclean view print
