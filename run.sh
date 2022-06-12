cd build
cmake --build .
./main | tee ../log.txt
cd ..
pdflatex Math.tex
diff log.txt log_old.txt
