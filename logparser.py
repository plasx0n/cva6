import re

# last insn not an issue anymore 
regex = r"\s+[0-9]+ 0x\w+ [a-zA-Z] \(0x\S+\) (?P<insn>[0-9a-zA-Z.]+)(\s+.+|\n)"
subst = "\\g<insn>\n"

f = open('log.txt','r')
data = f.read()
f.close()

# You can manually specify the number of replacements by changing the 4th argument
result = re.sub(regex, subst, data)

if result:
    print (result)

