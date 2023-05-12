# FWC-QMBFS
Fast calculation of full Wick's contractions in quantum many-body fermion systems

Authors: Deni Vale, Nils Paar

Email: denivalesq@gmail.com (dvale@iv.hr), npaar@phy.hr

Platform: Linux

Version: v1.0

Maintainer of the current version: Deni Vale

Build: 2019 - 2023  All rights reserved (C)

This work is protected under the Croatian law "Zakon o autorskom pravu i srodnim pravima" NN 111/21 from October 22 2021.

This work is published under the Creative Commons Zero v1.0 Universal.

The statements above do not include any external program or latex package called by this program.

# Requirements for LaTex output and visualization

External programs: 
1) gnuplot 
2) latex 
3) pdflatex
4) dvips
5) pdf viewer (evince by default) 

Additional LaTex packages: 
1) simpler-wick 
2) graphicx
3) inconsolata
4) mathrsfs
5) fontenc
6) amssymb  

Package simpler-wick may be downloaded from https://github.com/JP-Ellis/simpler-wick/ or visit www.jpellis.me/projects/simpler-wick.

If you are doing this manually please paste refmathstyle.sty, simpler-wick.tex, simpler-wick.sty, simpler-wick.code.tex in the source code folder. The same holds for each example.

# Compiling code

Open terminal in source folder location and write the following command:

$ make

# Running program

Make sure you have installed all necessary external programs and additional packages.

Store arrangement of operators in textual file:

Name of the example in.dat. Operators in the case of the two-body interaction:

a_a^\dagger a_b^\dagger a_d a_c

We are looking the expectation value of this arrangement of Q.M. operators.

Content of in.dat should look like:

a*(a)a*(b)a(d)a(c)

The above case includes the general operator type. You may also have particle or hole operators, and combination of it. For example in extended Hartree-Fock version you may have:

a*(a)a*(b)a(d)a(c)c*(m)c*(n)h*(j)h*(i)

In general you may name the input textual file as you wish, but in that case run it as 

$./run -f <name of input file>.

Before runnig the program you should adjust parameters related to predefined indices of particle and hole states, but also to output. Here is the example of the choice saved in paramet.par:

#automatic

1

#hole indices

i j k l q

#particle indices

m n o p

#draw visual representation (prepair, draw, show) put n for no

p d n

#latex document (prepair, write/append, show) put n for no

p w n

#program used to open ps or pdf output

evince

We used the first letter of actions to enable choices to prepair, draw and show the graphical representation, and similarly to to prepair, write/append and show for latex document of the output of the calculation. In the above example program prepairs the graphical output (vertices, directed lines, intersection points), draws the output (create gnuplot and latex files with ps, dvi, eps output) but does not show it in document viewer. Similarly, the result is prepaired as LaTex objects, which are then written to file. The pdf file of corresponding LaTex is also created in the last step of the process. The pdf version is not shown in document viewer here. You may also change the document viewer, which should correspod to the installed program on your platform.
  
  
Write the following command in terminal:

$./ run -f in.dat
  
The result is written on the standard output in the latex form for each nonvanishing transformation with the calculation procedure. The LaTex result, if one enables options prepair and write, is then written in the latout.tex file and corresponding pdf file is created. In the folder named VISUAL the whole graphical output is saved.

