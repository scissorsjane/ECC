#include <stdio.h>
#include <gmp.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
int main(){
printf("input the number you need to map back\n");
long long int a;
scanf("%lld",&a);
char ch[100]="";
char t[1];
int tempt;
while(a!=0){
tempt=a%100;
a=a/100;
if (tempt<=19){
	tempt=tempt+38;
}
if(tempt>=19){
tempt=tempt+45;
}
sprintf(t,"%c",tempt);
strcat(ch,t);
//printf("%s",t);


}
int i;
for (i=strlen(ch)-1;i>=0;i--){
printf("%c",ch[i]);

}



}