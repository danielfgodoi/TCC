GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/global_b1
GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/global_b2

LocalBlockAlignment/bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_b1
LocalBlockAlignment/bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_b2

LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_conc_b1
LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_conc_b2

Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/semi_b1
Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/semi_b2
