# LaTeX documentation Makefile

# Compiler settings
LATEX = pdflatex
LATEX_FLAGS = -output-directory=build -interaction=nonstopmode

# Source files
MAIN = main.tex
PROBLEMS = problems/problem1.tex
# Add more problem files as they are created

# Output files
PDF = build/main.pdf
AUX = build/main.aux
LOG = build/main.log
TOC = build/main.toc

.PHONY: all clean

all: $(PDF)

$(PDF): $(MAIN) $(PROBLEMS) | build
	$(LATEX) $(LATEX_FLAGS) $(MAIN)
	$(LATEX) $(LATEX_FLAGS) $(MAIN)  # Second run for TOC

build:
	mkdir -p build

clean:
	rm -f $(PDF) $(AUX) $(LOG) $(TOC)
	rm -f build/*

# Watch for changes and recompile (requires fswatch)
watch:
	fswatch -o $(MAIN) $(PROBLEMS) | xargs -n1 -I{} make all 