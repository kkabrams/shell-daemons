#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>

#define DEBUG 0

int main(int argc,char *argv[]) {
 int i,j,k,l;
 char *s=argv[1];
 char *out=malloc(MAXPATHLEN+1);
 switch(s[0]) {
  case '/':
   strcpy(out,"/");
   break;
  case '~':
   strcpy(out,(char *)getenv("HOME"));
   break;
  default:
//old code, but might be what I decide I /really/ want.
//   getcwd(out,MAXPATHLEN);
   if(getenv("PWD")) strcpy(out,getenv("PWD"));
   strcat(out,"/");
 }
 strcat(out,s);
#if DEBUG
 printf("%s\n",out);
#endif
 l=strlen(out)-1;
 if(out[l] == '.' && out[l-1] == '/') strcat(out,"/");
 if(out[l] == '.' && out[l-1] == '.' && out[l-2] == '/') strcat(out,"/");
 for(i=0;out[i];) {
#if DEBUG
  printf("%s @ %s\n",out,out+i);
#endif
  if(strlen(out+i) >= 4) {
   if(out[i] == '/' && out[i+1] == '.' && out[i+2] == '.' && out[i+3] == '/') {
    for(j=i-1;j>0 && out[j] != '/';j--) {
    }
    if(j<0) j=0;
    for(k=j;out[k];k++) {
     out[k]=out[k+(i-j)+3];
     if(!out[k]) break;
    }
    i=0;
    continue;
   }
  }
  if(strlen(out+i) >= 3) {
   if(out[i] == '/' && out[i+1] == '.' && out[i+2] == '/') {
    for(j=i;out[j];j++) {
     out[j]=out[j+2];
     if(!out[j]) break;
    }
    i=0;
    continue;
   }
  }
  if(strlen(out+i) >= 2) {
   if(out[i] == '/' && out[i+1] == '/') {
    //leftshift over it.
    for(j=i;out[j];j++) {
     out[j]=out[j+1];
     if(!out[j]) break;
    }
    i=0;
    continue;
   }
  }
  i++;
 }
 printf("%s\n",out);
 return 0;
}
