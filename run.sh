# GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/global_b1
# GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/global_b2

# LocalBlockAlignment/bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_b1
# LocalBlockAlignment/bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_b2

# LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_conc_b1
# LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/local_conc_b2

# Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b1 -o in/b1o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/semi_b1
# Semi-GlobalBlockAlignment/bin/BlockAlignment -b in/b2 -o in/b2o -t in/t1 in/t2 in/t3 in/t4 in/t5 > out/semi_b2





# GlobalBlockAlignment/bin/BlockAlignment \
# 	-t in/text/t1.txt t2.txt t3.txt t4.txt t5.txt t6.txt t7.txt t8.txt t9.txt t10.txt \
# 	-o in/fragment/t1-f1.txt \
# 	-b in/detFragment/t1-f1.txt

# LocalBlockAlignment/bin/BlockAlignment \
# 	-t in/text/t1.txt t2.txt t3.txt t4.txt t5.txt t6.txt t7.txt t8.txt t9.txt t10.txt \
# 	-o in/fragment/t1-f1.txt \
# 	-b in/detFragment/t1-f1.txt

# LocalBlockAlignment\ \(concatenation\)//bin/BlockAlignment \
# 	-t in/text/t1.txt t2.txt t3.txt t4.txt t5.txt t6.txt t7.txt t8.txt t9.txt t10.txt \
# 	-o in/fragment/t1-f1.txt \
# 	-b in/detFragment/t1-f1.txt

# Semi-GlobalBlockAlignment/bin/BlockAlignment \
# 	-t in/text/t1.txt t2.txt t3.txt t4.txt t5.txt t6.txt t7.txt t8.txt t9.txt t10.txt \
# 	-o in/fragment/t1-f1.txt \
# 	-b in/detFragment/t1-f1.txt




echo "Running Global Alignment\n"
./global.sh

echo "Running Local Alignment\n"
./local.sh

echo "Running Local (Concat) Alignment\n"
./local_concat.sh

echo "Running Semi Global Alignment\n"
./semi_global.sh
echo ""