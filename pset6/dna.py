import csv
import sys
import random
import re
# if len(sys.argv) < 3:
#     print("Usage: python dna.py data.csv sequence.txt")
# else:

#     with open(sys.argv[2], 'r')as txtfile:
#         for text in txtfile:
#             # print(text[12:22:1])
#             agagtc = text.count("AGATC")
#             aatc = text.count("AATG")
#             tatc = text.count("TATC")
#             top = (agagtc, aatc, tatc)
#             print(type(top))
#     # print(database)
#     name = []

#     csvFile = sys.argv[1]
#     with open(csvFile, 'r')as dnaDatabase:
#         dna_database = csv.DictReader(dnaDatabase)

#         for row in dna_database:
#             # row["name"] = row
#             # row["AGATC"] = int(row["AGATC"])
#             # row["AATG"] = int(row["AATG"])
#             # row["TATC"] = int(row["TATC"])
            
#             name.append(row)
#     print(())
            
if len(sys.argv)!= 3:
    print("Error !")
    sys.exit(1)
 
with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    sequences = next(reader)
    
with open (sys.argv[2]) as dnafile:
    dna = csv.reader(dnafile)
    for row in dnafile:
        dnalist = row
    
DNA = dnalist[0]
dict_seq = {}
 
 
search_re = re.compile('(?:' + DNA + ')+')
print(max((len(seq) for seq in search_re.findall(dna)), default=0) // len(DNA))
 
 
with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        match = 0
        for DNA in dict_seq:
            if dict_seq[DNA] == int(row[DNA]):
                match += 1
        if match == len(dict_seq):
            print(row['name'])
            exit()
    #otherwise, no match
    print("No match")