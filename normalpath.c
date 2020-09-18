#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>

#include <pwd.h> //getpwnam()

#define DEBUG 0

int main(int argc,char *argv[]) {
 int i,j,k,l;
 struct passwd *pwd;
 if(argc < 2) {
   fprintf(stderr,"usage: normalpath a/path/to/normalize/to/not/include/../../../or///t//h//e//s//e/\n");
   exit(1);
 }
 char *s=argv[1];
 char *t;
 char *out;
 switch(s[0]) {
  case '/':
   out=malloc(strlen(argv[1])+1);
   strcpy(out,"/");
   break;
  case '~':
   s++;//skip this character.
   if((t=strchr(s,'/'))) {//if there's a /...
     *strchr(s,'/')=0;
   }
   if(strlen(s)) {
     pwd=getpwnam(s);
     s+=strlen(s);//set it to null byte at the end, if there was a /, t will override this later
   }
   else {
     pwd=getpwuid(getuid());//there was a / after the ~
   }
   if(pwd) {
     out=malloc(strlen(pwd->pw_dir)+strlen(argv[1])+1);//
     strcpy(out,pwd->pw_dir);
     strcat(out,"/");
     if(t) s=t+1;
   } else {
     s=argv[1];//let's pretend like we're ignoring ~ now...
     if(t) *t='/';//need to undo this /before/ the malloc to get proper length of argv[1]
     out=malloc(strlen(argv[1])+1);
     strcpy(out,"");
   }
   break;
  default:
//old code, but might be what I decide I /really/ want.
//   getcwd(out,MAXPATHLEN);
   if(getenv("PWD")) {
     out=malloc(strlen(getenv("PWD"))+strlen(argv[1])+1);
     strcpy(out,getenv("PWD"));
   } else {
     out=malloc(strlen(argv[1])+1);
     strcpy(out,"");
   }
   strcat(out,"/");//???
 }
// the only place the string /might/ get longer is in the previous two cases of and ~
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
 if(out[0] == '/' && out[1] == 0) {
   //the only case we want the last character to be /
 }
 else {//strip the trailing /
   if(out[strlen(out)-1] == '/') {
     out[strlen(out)-1]=0;//null it out
   }
 }
 printf("%s\n",out);
 return 0;
}
