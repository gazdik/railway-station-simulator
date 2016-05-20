cd plot

python gantt.py -o realtimes.gpl -c colors.cfg realtimes.txt

gnuplot <<- EOF
  load "main.gpl"
  exit
EOF
