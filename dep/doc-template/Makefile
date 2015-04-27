all: homework.tex.pdf

homework.tex.pdf: homework.tex
	pdflatex homework.tex 
	# deal with latex lastpage problem, need to compile twice
	@pdflatex homework.tex 
	mv homework.pdf homework.tex.pdf
	rm homework.aux homework.log 

clean:
	rm homework.aux homework.log homework.pdf

upload:
	scp -r ../../hw2/ b03902028@linux7.csie.ntu.edu.tw:dsa/
