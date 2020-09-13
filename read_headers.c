#include <stdio.h>
#include <ctype.h> //toupper
#include <string.h> //strcpy, cat, etc
#include <stdlib.h> //getenv
#include <unistd.h> //execv

// this program is to read in headers like the type in:
// urn:ietf:rfc:3864
// from stdin and then store them into environment variables
// so that the program specified by argv[1] can do something with them

char convert(char in) {
  if(in >= 'a' && in <= 'z') return in-' ';
  if(in == '-') return '_';
  return in;
}

int main(int argc,char *argv[]) {
  int i;
  char line[8192];//lol. how long should this be?
  char scheme[512];
  char name[8192 + 512 + 1];
  char *value;
  strcpy(scheme,getenv("SERVER_PROTOCOL"));
  if(strchr(scheme,'/')) *strchr(scheme,'/')=0;
  while(fgets(line,sizeof(line)-1,stdin)) {
    if(strchr(line,'\n')) *strchr(line,'\n')=0;
    if(strchr(line,'\r')) *strchr(line,'\r')=0;
    if(!strlen(line)) break;//got a blank line. abort.
    if((value=strchr(line,':'))) {
      *value=0;
      for(value++;*value==' ';value++);
    } else {
      continue;
    }
    strcpy(name,scheme);
    strcat(name,"_");
    strcat(name,line);
    for(i=0;name[i];name[i]=convert(name[i]),i++);
    //add support for multi-line headers eventually.
    //printf("%s=%s\n",name,value);
    setenv(name,value,1);
  }
  if(argc > 1) {
    execv(argv[1],argv+1);//run argv
    perror("execv");
  }
  printf("usage: read_headers /external/program arg1 arg2\n");
  return 1;//if we got here it was an error of some kind.
}
