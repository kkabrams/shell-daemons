PREFIX:=/usr/local
CFLAGS=-pedantic -Wall

.PHONEY: all install test clean

all: read_headers normalpath query_param

install: all
	install -t $(PREFIX)/libexec read_headers
	install -t $(PREFIX)/libexec geminid
	install -t $(PREFIX)/libexec httpd
	install -t $(PREFIX)/bin mime-type
	install -t $(PREFIX)/bin normalpath

clean:
	rm normalpath
	rm read_headers
	rm query_param

test: tests/normalpath.output

tests/normalpath.output: normalpath tests/normalpath.sh
	./tests/normalpath.sh ./normalpath | tee tests/normalpath.output
