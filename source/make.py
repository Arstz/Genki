import os

src = ""

filenames = os.listdir(".")
dirnames = list(filter (lambda x : not '.' in x, filenames))
for i in dirnames:
    for j in os.listdir(i):
        filenames.append(i + "/" + j)

for i in filenames:
    i = "./" + i

filenames = list(filter(lambda x : ".h" in x or ".cpp" in x or ".glslv" in x or ".glslf" in x, filenames))
print(filenames)

for i in filenames:
    file = open(i, "r")
    for line in file.readlines():
        src += line
    file.close()

file = open("src.txt", "w")
file.write(src)
file.close()