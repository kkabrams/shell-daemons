#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
//I made this because both the geminid and httpd will need this ability.
//and it seemed like something that'd be really slow in shell-script

//the main loop is skipping a check on the last bit, but we don't need to check it for path_info finding.
int main(int argc, char *argv[]) {
  // start at / and stop when we get to a file instead of a directory.
  // the file is the CGI and anything after is going to be the PATH_INFO
  if(argc < 2) {
    fprintf(stderr,"usage: path_info_find /abosulute/path\n");
    fprintf(stderr,"the purpose of this program is to split the PATH_INFO off of SCRIPT_FILENAME.\n");
    fprintf(stderr,"the SCRIPT_FILENAME is the first line of output, PATH_INFO is second.\n");
    fprintf(stderr,"program will not output anything if it can't find a regular file anywhere in the supplied argument.\n");
    return 1;
  }
  struct stat sb;
  char *p=argv[1]+1,*p2;
  while((p=strchr(p,'/'))) {
    *p=0;
    //we nulled the character after the /
    //now let's do a fstat on it or something
    //printf("%s\n",argv[1]);
    if(stat(argv[1],&sb) == -1) {
      //can't stat the file, assume we're now in PATH_INFO and use previous values.
      p2=strrchr(argv[1],'/');
      *p='/';
      *p2='\0';
      printf("%s\n",argv[1]);
      *p2='/';
      printf("%s\n",p2);
      return 0;
    }
    if(S_ISREG(sb.st_mode)) {//if we find a file, exit
      printf("%s\n",argv[1]);
      *p='/';
      printf("%s\n",p);
      //path_info=
      //
      return 0;
    }
    *p='/';
    p++;
  }
  //uh... whatever is after the last / is the PATH_INFO?
  if(stat(argv[1],&sb) == -1) {
    p=strrchr(argv[1],'/');
    *p=0;
    printf("%s\n",argv[1]);
    *p='/';
    printf("%s\n",p);
    return 0;
  }
  return 1;//not found
}
