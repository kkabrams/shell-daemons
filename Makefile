PREFIX:=/usr/local
CFLAGS=-pedantic -Wall

.PHONEY: all install test clean

all: read_headers normalpath query_param test path_info_find

install: all
	install -t $(PREFIX)/libexec coind
	install -t $(PREFIX)/libexec read_headers
	install -t $(PREFIX)/libexec query_param
	install -t $(PREFIX)/libexec geminid
	install -t $(PREFIX)/libexec httpd
	install -t $(PREFIX)/libexec gopherd
	install -t $(PREFIX)/bin mime-type
	install -t $(PREFIX)/bin normalpath
	install -t $(PREFIX)/bin http2gemini
	install -t $(PREFIX)/bin path_info_find

clean:
	rm normalpath
	rm read_headers
	rm query_param
	rm tests/*.output

test: tests/normalpath.output

tests/normalpath.output: normalpath tests/normalpath.sh
	./tests/normalpath.sh ./normalpath | tee tests/normalpath.output
