#include<stdio.h>
#include<stdlib.h>//for exit(0) function
#include<string.h>//for strcmp
#include<unistd.h>//for pwd_function
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<unistd.h>//for chdir()
void exit_function(){
printf("\nExited\n");
exit(0);
}
void pwd_function(){
char pwd[100];
getcwd(pwd,100);
 printf("%s\n",pwd);
}
void ls_function(){
system("ls");
}
void ls_l_function(){
system("ls -l");
}
void mkdir_function(char dir[100]){
mkdir(dir, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP
| S_IROTH | S_IWOTH | S_IXOTH);
printf("\nDirectory created.");
}
void rmdir_function(char dir[100]){
rmdir(dir);
}
void cd_function(char dir[100]){
chdir(dir);
pwd_function();
}
void split_functions(char *get_command){
int i,k=0;
char *command=(char*)malloc(100);
int n=0;
char *argument=(char*)malloc(100);
int m=0;
int pid;
strcpy(command,"");
strcpy(argument,"");
for (i=0;get_command[i]!='\0';i++){
if (get_command[i]==' '){
i++;
while(get_command[i]!='\0'){
argument[k++]=get_command[i++];
}
argument[k]='\0';
break;
}
command[i]=get_command[i];
}
command[i]='\0';
if (strcmp(command,"mkdir")==0){
mkdir_function(argument);
}
else if(strcmp("rmdir",command)==0){
rmdir_function(argument);
}
else if(strcmp("cd",command)==0){
cd_function(argument);
}
else{//use them as executables
int i=0;
int status;
int cpid;
char *args[200];
args[0]=strtok(get_command," ");
while(args[i]!=NULL){
args[++i]=strtok(NULL," ");
}
if( (cpid=fork()) == 0 ){
execvp(args[0],args);
}
else{
waitpid(cpid,&status,0);
}
}
}
void myshell(){
char get_command[100];
strcpy(get_command,"");
while(1){
printf("\nmyshell>");
scanf("%[^\n]%*c",get_command);
if (strcmp("exit",get_command)==0){
exit_function();
}
else if(strcmp("pwd",get_command)==0){
pwd_function();
}
else if(strcmp("ls",get_command)==0){
ls_function();
}
else if(strcmp("ls -l",get_command)==0){
ls_l_function();
}
else if(strcmp("clear",get_command)==0){
system("clear");
}
else {
split_functions(get_command);
}
strcpy(get_command,"");
}
}
int main(void){
system("clear");
myshell();
return(0);
}
