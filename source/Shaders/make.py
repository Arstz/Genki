import os

filenames = list(filter(lambda value: ".glslv" in value or ".glslf" in value, (os.listdir("."))))

cppfile = open("shaders.h", "w")
cppfile.write("#include <string>\n\n\n")

for filename in filenames:
    varname = filename[:]
    cppfile.write("extern std::string " + varname.replace(".", "_") + ' = ""\n')
    buffer = ""
    file = open(filename, "r")
    for line in file.readlines():
        buffer += '"' + line[:-1] + '\\n"' + '\n'
    file.close()
    if len(buffer) > 0:
        cppfile.write(buffer[:-2] + "\\0\";" + "\n\n\n")

cppfile.close()