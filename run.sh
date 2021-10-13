cd build
cmake --build .
./Math_Proof | tee ../log.txt
cd ..
pdflatex Math.tex
pdflatex Math.tex
diff log.txt log_old.txt
