set terminal pngcairo size 1700,600
set output 'img.png'
set yrange[0:0.11]
set grid
plot "hist.dat" with lines
