NAME=doc

$(NAME).pdf: $(NAME).tex title.tex
	pdflatex $(NAME)
	bibtex $(NAME)
	pdflatex $(NAME)
	pdflatex $(NAME)


clean:
	-rm -f *.dvi *.aux *.toc *.log *.out *.blg *.pdf *.bbl img/logo-eps-converted-to.pdf
