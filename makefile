files = testTree.c BiThrNode.c

testtree: $(files)
	gcc -o $@ $^

testdebugger: $(files)
	gcc -o $@ $^
