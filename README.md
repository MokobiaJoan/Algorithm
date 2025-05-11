To build Task 1.1(Decoder):

BUILD: "make"


RUN PROGRAM: echo -n "input" | ./ascii85 -e

             echo -n '-e result' | ./ascii85 -d



CLEAN BUILD FILES: make clean