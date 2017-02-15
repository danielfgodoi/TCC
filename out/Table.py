# -*- encoding: utf-8 -*-
# Author: Daniel de Faria Godoi
# Email: danielfgodoi@gmail.com

import sys

if __name__ == "__main__":

	if len(sys.argv) == 2:
		arg = sys.argv[1]

	else:
		arg = 0

	if arg == "global":
		path = "global"
		files = [
		"global_t1-f1.txt",
		"global_t1-f2.txt",
		"global_t1-f3.txt",
		"global_t1-f4.txt",
		"global_t1-f5.txt",
		"global_t2-f1.txt",
		"global_t2-f2.txt",
		"global_t2-f3.txt",
		"global_t2-f4.txt",
		"global_t2-f5.txt",
		"global_t3-f1.txt",
		"global_t3-f2.txt",
		"global_t3-f3.txt",
		"global_t3-f4.txt",
		"global_t3-f5.txt",
		"global_t4-f1.txt",
		"global_t4-f2.txt",
		"global_t4-f3.txt",
		"global_t4-f4.txt",
		"global_t4-f5.txt",
		"global_t5-f1.txt",
		"global_t5-f2.txt",
		"global_t5-f3.txt",
		"global_t5-f4.txt",
		"global_t5-f5.txt",
		"global_t6-f1.txt",
		"global_t6-f2.txt",
		"global_t6-f3.txt",
		"global_t6-f4.txt",
		"global_t6-f5.txt",
		"global_t7-f1.txt",
		"global_t7-f2.txt",
		"global_t7-f3.txt",
		"global_t7-f4.txt",
		"global_t7-f5.txt",
		"global_t8-f1.txt",
		"global_t8-f2.txt",
		"global_t8-f3.txt",
		"global_t8-f4.txt",
		"global_t8-f5.txt",
		"global_t9-f1.txt",
		"global_t9-f2.txt",
		"global_t9-f3.txt",
		"global_t9-f4.txt",
		"global_t9-f5.txt",
		"global_t10-f1.txt",
		"global_t10-f2.txt",
		"global_t10-f3.txt",
		"global_t10-f4.txt",
		"global_t10-f5.txt"]

		for file in files:
			with open(path+"/"+file) as fileObject:
				content = fileObject.readlines()
			content = [x.strip() for x in content]

			i = 0
			for c in content:
				if c and c != "S	N	M" and c != "-----------------" and ">" not in c and "percentage" not in c:
					if "Number of chars ?: " in c:
						c = c.replace("Number of chars ?: ", "")
					elif "Numer of hits: " in c:
						c = c.replace("Numer of hits: ", "")
					print c,"\t",
					i += 1

					if i % 3 == 0:
						print

	elif arg == "local":
		path = "local"
		files = [
		"local_t1-f1.txt",
		"local_t1-f2.txt",
		"local_t1-f3.txt",
		"local_t1-f4.txt",
		"local_t1-f5.txt",
		"local_t2-f1.txt",
		"local_t2-f2.txt",
		"local_t2-f3.txt",
		"local_t2-f4.txt",
		"local_t2-f5.txt",
		"local_t3-f1.txt",
		"local_t3-f2.txt",
		"local_t3-f3.txt",
		"local_t3-f4.txt",
		"local_t3-f5.txt",
		"local_t4-f1.txt",
		"local_t4-f2.txt",
		"local_t4-f3.txt",
		"local_t4-f4.txt",
		"local_t4-f5.txt",
		"local_t5-f1.txt",
		"local_t5-f2.txt",
		"local_t5-f3.txt",
		"local_t5-f4.txt",
		"local_t5-f5.txt",
		"local_t6-f1.txt",
		"local_t6-f2.txt",
		"local_t6-f3.txt",
		"local_t6-f4.txt",
		"local_t6-f5.txt",
		"local_t7-f1.txt",
		"local_t7-f2.txt",
		"local_t7-f3.txt",
		"local_t7-f4.txt",
		"local_t7-f5.txt",
		"local_t8-f1.txt",
		"local_t8-f2.txt",
		"local_t8-f3.txt",
		"local_t8-f4.txt",
		"local_t8-f5.txt",
		"local_t9-f1.txt",
		"local_t9-f2.txt",
		"local_t9-f3.txt",
		"local_t9-f4.txt",
		"local_t9-f5.txt",
		"local_t10-f1.txt",
		"local_t10-f2.txt",
		"local_t10-f3.txt",
		"local_t10-f4.txt",
		"local_t10-f5.txt"]

		for file in files:
			with open(path+"/"+file) as fileObject:
				content = fileObject.readlines()
			content = [x.strip() for x in content]

			i = 0
			for c in content:
				if c and c != "S	TL	BL" and c != "-----------------" and "percentage" not in c:
					if ">" in c:
						c = c.replace("> Best result and text-block best line in/text/", "")
						c = c.replace(" and in/detFragment/", "\t")
						c = c.replace(".txt", "")
					if "Number of chars ?: " in c:
						c = c.replace("Number of chars ?: ", "")
					elif "Numer of hits: " in c:
						c = c.replace("Numer of hits: ", "")
					print c,"\t",
					i += 1

					if i % 4 == 0:
						print

	elif arg == "local_concat":
		path = "local_concat"
		files = [
		"local_concat_t1-f1.txt",
		"local_concat_t1-f2.txt",
		"local_concat_t1-f3.txt",
		"local_concat_t1-f4.txt",
		"local_concat_t1-f5.txt",
		"local_concat_t2-f1.txt",
		"local_concat_t2-f2.txt",
		"local_concat_t2-f3.txt",
		"local_concat_t2-f4.txt",
		"local_concat_t2-f5.txt",
		"local_concat_t3-f1.txt",
		"local_concat_t3-f2.txt",
		"local_concat_t3-f3.txt",
		"local_concat_t3-f4.txt",
		"local_concat_t3-f5.txt",
		"local_concat_t4-f1.txt",
		"local_concat_t4-f2.txt",
		"local_concat_t4-f3.txt",
		"local_concat_t4-f4.txt",
		"local_concat_t4-f5.txt",
		"local_concat_t5-f1.txt",
		"local_concat_t5-f2.txt",
		"local_concat_t5-f3.txt",
		"local_concat_t5-f4.txt",
		"local_concat_t5-f5.txt",
		"local_concat_t6-f1.txt",
		"local_concat_t6-f2.txt",
		"local_concat_t6-f3.txt",
		"local_concat_t6-f4.txt",
		"local_concat_t6-f5.txt",
		"local_concat_t7-f1.txt",
		"local_concat_t7-f2.txt",
		"local_concat_t7-f3.txt",
		"local_concat_t7-f4.txt",
		"local_concat_t7-f5.txt",
		"local_concat_t8-f1.txt",
		"local_concat_t8-f2.txt",
		"local_concat_t8-f3.txt",
		"local_concat_t8-f4.txt",
		"local_concat_t8-f5.txt",
		"local_concat_t9-f1.txt",
		"local_concat_t9-f2.txt",
		"local_concat_t9-f3.txt",
		"local_concat_t9-f4.txt",
		"local_concat_t9-f5.txt",
		"local_concat_t10-f1.txt",
		"local_concat_t10-f2.txt",
		"local_concat_t10-f3.txt",
		"local_concat_t10-f4.txt",
		"local_concat_t10-f5.txt"]

		for file in files:
			with open(path+"/"+file) as fileObject:
				content = fileObject.readlines()
			content = [x.strip() for x in content]

			i = 0
			for c in content:
				if c and c != "Similarity" and c != "-----------------" and ">" not in c and "percentage" not in c:
					if "Number of chars ?: " in c:
						c = c.replace("Number of chars ?: ", "")
					elif "Numer of hits: " in c:
						c = c.replace("Numer of hits: ", "")
					print c,"\t",
					i += 1

					if i % 3 == 0:
						print

	elif arg == "semi_global":
		path = "semi_global"
		files = [
		"semi_global_t1-f1.txt",
		"semi_global_t1-f2.txt",
		"semi_global_t1-f3.txt",
		"semi_global_t1-f4.txt",
		"semi_global_t1-f5.txt",
		"semi_global_t2-f1.txt",
		"semi_global_t2-f2.txt",
		"semi_global_t2-f3.txt",
		"semi_global_t2-f4.txt",
		"semi_global_t2-f5.txt",
		"semi_global_t3-f1.txt",
		"semi_global_t3-f2.txt",
		"semi_global_t3-f3.txt",
		"semi_global_t3-f4.txt",
		"semi_global_t3-f5.txt",
		"semi_global_t4-f1.txt",
		"semi_global_t4-f2.txt",
		"semi_global_t4-f3.txt",
		"semi_global_t4-f4.txt",
		"semi_global_t4-f5.txt",
		"semi_global_t5-f1.txt",
		"semi_global_t5-f2.txt",
		"semi_global_t5-f3.txt",
		"semi_global_t5-f4.txt",
		"semi_global_t5-f5.txt",
		"semi_global_t6-f1.txt",
		"semi_global_t6-f2.txt",
		"semi_global_t6-f3.txt",
		"semi_global_t6-f4.txt",
		"semi_global_t6-f5.txt",
		"semi_global_t7-f1.txt",
		"semi_global_t7-f2.txt",
		"semi_global_t7-f3.txt",
		"semi_global_t7-f4.txt",
		"semi_global_t7-f5.txt",
		"semi_global_t8-f1.txt",
		"semi_global_t8-f2.txt",
		"semi_global_t8-f3.txt",
		"semi_global_t8-f4.txt",
		"semi_global_t8-f5.txt",
		"semi_global_t9-f1.txt",
		"semi_global_t9-f2.txt",
		"semi_global_t9-f3.txt",
		"semi_global_t9-f4.txt",
		"semi_global_t9-f5.txt",
		"semi_global_t10-f1.txt",
		"semi_global_t10-f2.txt",
		"semi_global_t10-f3.txt",
		"semi_global_t10-f4.txt",
		"semi_global_t10-f5.txt"]

		for file in files:
			with open(path+"/"+file) as fileObject:
				content = fileObject.readlines()
			content = [x.strip() for x in content]

			i = 0
			for c in content:
				if c and c != "S	TL	BL" and c != "-----------------" and "percentage" not in c:
					if ">" in c:
						c = c.replace("> Best result and text-block best line in/text/", "")
						c = c.replace(" and in/detFragment/", "\t")
						c = c.replace(".txt", "")
					if "Number of chars ?: " in c:
						c = c.replace("Number of chars ?: ", "")
					elif "Numer of hits: " in c:
						c = c.replace("Numer of hits: ", "")
					print c,"\t",
					i += 1

					if i % 4 == 0:
						print

	else:
		print "Invalid option!\nPlease choose between 'global', 'local', 'local_concat' or 'semi_global'"
