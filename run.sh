# GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/global_b1
# GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/global_b2
# LocalBlockAlignment/bin/BlockAlignment -b in/b1 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_b1
# LocalBlockAlignment/bin/BlockAlignment -b in/b2 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_b2
# LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b1 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_conc_b1
# LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b2 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_conc_b2
# Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/semi_b1
# Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/semi_b2

printf "\n\n\n\n====================\nGlobal B1\n\n"
GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -t in/t1
printf "\n\n\n\n====================\nGlobal B2\n\n"
GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -t in/t1
printf "\n\n\n\n====================\nLocal B1\n\n"
LocalBlockAlignment/bin/BlockAlignment -b in/b1 -t in/t1
printf "\n\n\n\n====================\nLocal B2\n\n"
LocalBlockAlignment/bin/BlockAlignment -b in/b2 -t in/t1
printf "\n\n\n\n====================\nLocalConc B1\n\n"
LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b1 -t in/t1
printf "\n\n\n\n====================\nLocalConc B2\n\n"
LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b2 -t in/t1
printf "\n\n\n\n====================\nSemi B1\n\n"
Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -t in/t1
printf "\n\n\n\n====================\nSemi B2\n\n"
Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -t in/t1