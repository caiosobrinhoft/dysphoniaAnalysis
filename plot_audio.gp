set terminal png size 2560, 1080
set output 'grafico_audio.png'
set xlabel 'Amostras normalizadas'
set ylabel 'Amplitude'
plot 'saida.txt' with lines