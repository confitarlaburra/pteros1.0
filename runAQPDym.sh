./AQPmsd -f ../test_MD/AQP4/hAQP4.pdb ../test_MD/AQP4.1000.dcd -dim z -rad 0.3 -win 100 -minZmaxZ -1 +1 -sel "name OH2" -selFit "chain A" "chain B" "chain C" "chain D" -ref ../test_MD/AQP4/A.pdb 
./AQPpf -f  ../test_MD/AQP4/hAQP4.pdb ../test_MD/AQP4.1000.dcd -dim z -rad 0.3 -win 100 -minZmaxZ -1 +1 -sel "name OH2" -selFit "chain A" "chain B" "chain C" "chain D" -ref ../test_MD/AQP4/A.pdb
