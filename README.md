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

# Compiling code

Open terminal in source folder location and write the following command:

$ make

# Run code

Make sure you have installed all necessary external programs and additional packages.

Store arrangement of operators in textual file:

Name of the example in.dat. Operators in the case of the two-body interaction:

a_a^\dagger a_b^\dagger a_d a_c

We are looking the expectation value of this arrangement of Q.M. operators.

Content of in.dat should look like:

a*(a)a*(b)a(d)a(c)

The above case includes the general operator type. You may also have particle or hole operators, and combination of it. For example in extended Hartree-Fock version you may have:

a*(a)a*(b)a(d)a(c)c*(m)c*(n)h*(j)h*(i)

Write the following command in terminal:

$./ run -f in.dat

