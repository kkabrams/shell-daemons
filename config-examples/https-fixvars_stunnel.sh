#!/bin/sh

export PATH=/bin:/usr/bin:/usr/local/bin
#stunnel already sets REMOTE_PORT
export REMOTE_PORT
### this is to canonicalize IP addresses. ipconvert is in my... iptools repo?
export REMOTE_ADDR="$(printf "%s\n" "$REMOTE_ADDR" | tr -d '[]' | xargs ipconvert | tail -n1 | cut '-d ' -f2)"
export HTTPS=on
exec /service/httpd/httpd
