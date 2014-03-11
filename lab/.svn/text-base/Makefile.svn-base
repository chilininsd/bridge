
all: 
	cd files-processes; make
	cd threads; make
	cd C-examples/; make 
	cd plugins; make


zipfile:
	cd plugins; make clean
	cd C-examples; make clean
	cd files-processes/; make  clean
	cd threads; make  clean
	zip -x "*/.svn*" -x "*/.project" -x "*/.classpath" -r lab.zip processes-files/ threads/ plugins/ C-examples/ 
	zip -x "*/.svn*" -r mswin.zip ms-windows/

	
clean:
	cd files-processes; make  clean
	cd threads; make  clean
	cd plugins; make clean
	cd C-examples; make clean
