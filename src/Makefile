IDIR=src

.PHONY: clean, all, doc

all:
	cd $(IDIR) && qmake src.pro
	cd $(IDIR) && make
	if [ ! -d ../bin/linux/ ]; then	mkdir ../bin/linux;	fi
	mv ./src/ProGenealogy ../bin/linux/

doc:
	doxygen Doxyfile

clean:
	cd $(IDIR) && make clean
	cd ../bin && rm -rf linux
	cd ../doc && rm -rf doxygen
	
