#\bin\gnuplot
set terminal epslatex size 4.5,4.5 standalone color colortext 14
set output 'sa12_0.tex'
set size square
set xrange [-1.55:1.55]
set yrange [-1.55:1.55]
unset key; unset tics; unset border
r = 1
s = 0
s2 = 0
set object 1 circle at 0,0 size 1 fs transparent solid 0.25 fillcolor rgb "orange" lw 1
plot "VISUAL/point12_0.dat" u ($1+0):($2+0):3 with labels point pt 7 ps 2 offset char 1,1 notitle, \
"VISUAL/vector12_0.dat" using ($1+0):($2+0):($3+0):($4+0) with vectors filled head lw 2 notitle, \
"VISUAL/inter12_0.dat" u ($1+0):($2+0) with point pt 7 ps 2 pc 1;
unset object
