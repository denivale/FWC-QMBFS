#\bin\gnuplot
set terminal epslatex size 4.5,4.5 standalone color colortext 14
set output 'sa15_4.tex'
set size square
set xrange [-1.55:1.55]
set yrange [-1.55:1.55]
unset key; unset tics; unset border
r = 1
s = 0
s2 = 0
set object 1 circle at 0,0 size 1 fs transparent solid 0.25 fillcolor rgb "orange" lw 1
plot "VISUAL/point15_4.dat" u ($1+0):($2+0):3 with labels point pt 7 ps 2 offset char 1,1 notitle, \
"VISUAL/vector15_4.dat" using ($1+0):($2+0):($3+0):($4+0) with vectors filled head lw 2 notitle; \
unset object
