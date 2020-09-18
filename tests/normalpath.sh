#!/bin/sh
np="$1"
if [ ! -x "$np" ];then
  echo first argument needs to be the name of the normalpath program you want to test.
  exit 1
fi

HOMEPARENT="$(cd $HOME; cd ..; pwd)"
ROOTHOMEPARENT="$(cd ~root; cd ..; pwd)"
ROOTHOME="$(cd ~root;pwd)"

printf "pass/fail%40s %40s %40s %40s\n" "input" "actual output" "expected output" "description of test"
cat <<EOF \
  | tr -s '\t' \
  | tr '\t' ' ' \
  | while read -r input output name;do actualout="$("$np" "$input")" ; if [ "$actualout" = "$output" ]; then printf "\033[32mpassed:\033[0m "; else printf "\033[31mfailed:\033[0m "; fi;printf "for input: '%40s' : '%40s' == '%40s' ??? (%s)\n" "$input" "$actualout" "$output" "$name";done
.		$PWD		current working directory
/		/		root dir
/..		/		root dir up one
~		$HOME		current user home dir
~/derp		$HOME/derp	current user subdir of home
~/..		$HOMEPARENT	current user parent of home dir
~root		$ROOTHOME	root user home dir
~root/derp	$ROOTHOME/derp  root user subdir of home
~root/..	$ROOTHOMEPARENT root user parent of home
/../../../../	/		up many times from root dir
~in^va#lid	~in^va#lid	invalid user home
~in^va#lid/derp	~in^va#lid/derp subdir of invalid user home
EOF
