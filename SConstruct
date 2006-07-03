from glob import glob

flags = '-Wall -ansi -pedantic -g'

test = Environment(CCFLAGS = flags)
test.Program('qfbottest', [glob('./*.cpp')] )
