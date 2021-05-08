#include <stdio.h>
#include <string.h> //strchr

//this is to replace all of the:
//   printf "%s\n" "$QUERY_STRING" | tr '&' '\n' | grep "^$1=" | cut -d= -f2-
//that I do a lot.

#include <stdlib.h> //getenv

int main(int argc,char *argv[]) {
  char *p;
  if(argc != 2) return fprintf(stderr,"usage: query_param param_name\n"),1;
  for(p=getenv("QUERY_STRING");p;p=strchr(p,'&')) {
    p++;
    if(!strncmp(p,argv[1],strlen(argv[1]))) {
      if(strchr(p,'=')-p == strlen(argv[1])) {
        if(strchr(p,'&')) *strchr(p,'&')=0;
        printf("%s\n",p+strlen(argv[1])+1);
        return 0;
      }
    }
  }
  return 1;
}
