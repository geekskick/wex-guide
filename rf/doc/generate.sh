#!/bin/bash

bfname=$(dirname "$1")/"`basename "$1" .tex`"

makeindex -s "$bfname".ist -t "$bfname".alg -o "$bfname".acr "$bfname".acn
makeindex -s "$bfname".ist -t "$bfname".glg -o "$bfname".gls "$bfname".glo


mkdir -p pdf
pdflatex main.tex
mv *.pdf pdf/guide.pdf
rm *.log *.aux *.lof *.toc
