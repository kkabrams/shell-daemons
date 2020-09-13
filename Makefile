PREFIX:=/usr/local

all: read_headers normalpath

install: all
	install -t $(PREFIX)/libexec read_headers
	install -t $(PREFIX)/libexec geminid
	install -t $(PREFIX)/libexec httpd
	install -t $(PREFIX)/bin mime-type
	install -t $(PREFIX)/bin normalpath
