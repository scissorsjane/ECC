#include <stdio.h>
#include <gmp.h>
#include<getopt.h>
char* strtoint(char* ori);
static struct option long_options[]={
{"generate",0,NULL,'g'},
{"encrypt",1,NULL,'e'},
{"decrypt1",1,NULL,'d'},
{"decrypt2",1,NULL,'f'},
{"decrypt3",1,NULL,'h'},
{"decrypt4",1,NULL,'i'},
{"key",1,NULL,'k'}
};

struct pt{
mpz_t x;
mpz_t y;
};
mpz_t Kx,Ky,p,a,b,Gx,Gy,q,r,k;
void add(mpz_t xa,mpz_t ya,mpz_t xb,mpz_t yb, mpz_t addx, mpz_t addy);
void mult(mpz_t x,mpz_t y,mpz_t k1, mpz_t mux, mpz_t muy);
void generate();
void generateK(mpz_t k);
void encrypt(mpz_t mx,mpz_t my, mpz_t c1x, mpz_t c1y, mpz_t c2x, mpz_t c2y);
void decrypt(mpz_t c1x, mpz_t c1y, mpz_t c2x, mpz_t c2y, mpz_t k, mpz_t dx, mpz_t dy);

struct pt tempt;

int main(int argc,char* argv[]){
int fen,fde;
int c;
fen=0;
fde=0;
mpz_t mess;
mpz_init(mess);

mpz_t mx,my,c1x,c1y,c2x,c2y;
mpz_init(k);
mpz_init(mx);
mpz_init(my);
mpz_init(c1x);
mpz_init(c1y);
mpz_init(c2x);
mpz_init(c2y);

mpz_init(tempt.x);//add
mpz_init(tempt.y);
mpz_init(Kx);
mpz_init(Ky);
mpz_init(p);
mpz_init(a);
mpz_init(b);
mpz_init(Gx);
mpz_init(Gy);
mpz_init(q);
mpz_init(r);
generate();

while((c=getopt_long(argc,argv,"ge:d:k:",long_options,NULL))!=-1){
switch(c){
case 'g':{
generate();


//gmp_printf("p = %Zd\n",p);
//gmp_printf("G = %Zd, %Zd\n",Gx,Gy);

//gmp_printf("K = %Zd, %Zd\n",Kx, Ky);
//gmp_printf("Generated Ky = %Zd\n",Ky);
break;}
case 'e':{
generate();
gmp_printf("\n");
//gmp_printf("here",mess);
mpz_set_str(mess,strtoint(optarg),10);
mpz_mod_ui(my,mess,1000);

mpz_fdiv_q_ui(mx,mess,1000);
fen=1;
//gmp_printf("m1 = %Zd\n",mess);
//encrypt(mx,my,c1x,c1y,c2x,c2y);
break;
}
case 'k':{
mpz_set_str(k,optarg,10);
generateK(k);
break;}
case 'd':{
fde=1;
mpz_set_str(c1x,optarg,10);
gmp_printf("c1x = %Zd\n",c1x);
break;
}
case 'f':{
fde=1;
mpz_set_str(c1y,optarg,10);
gmp_printf("c1y = %Zd\n",c1y);
break;
}
case 'h':{
fde=1;
mpz_set_str(c2x,optarg,10);
gmp_printf("c2x = %Zd\n",c2x);
break;
}
case 'i':{
fde=1;
mpz_set_str(c2y,optarg,10);
gmp_printf("c2y = %Zd\n",c2y);
break;
}


}


}





mpz_t xa,xb,ya,yb;
/*
mpz_init(xa);
mpz_init(xb);
mpz_init(ya);
mpz_init(yb);
mpz_set_ui(xa,10);
mpz_set_ui(xb,10);
mpz_set_ui(ya,279);
mpz_set_ui(yb,20);
add(xa,ya,xb,yb);
gmp_printf("Generated a+b = %Zd\n",tempt.x);
gmp_printf("Generated a+b = %Zd\n",tempt.y);
*/





if (fen==1)
{
//gmp_printf("m = %Zd\n",mess);
//gmp_printf("m = %Zd, %Zd\n",mx,my);
encrypt(mx,my,c1x,c1y,c2x,c2y);

gmp_printf("Generated c1 = %Zd, %Zd\n",c1x,c1y);
gmp_printf("Generated c2 = %Zd, %Zd\n",c2x,c2y);}

mpz_t dx,dy;
mpz_init(dx);
mpz_init(dy);


if (fde==1)
{
decrypt(c1x,c1y,c2x,c2y,k,dx,dy);
gmp_printf("Decrypted = %Zd%Zd\n",dx,dy);
}
	mpz_clear(Kx);
	mpz_clear(Ky);
	mpz_clear(p);
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(Gx);
	mpz_clear(Gy);
	mpz_clear(q);
	mpz_clear(r);
	mpz_clear(dx);
	mpz_clear(dy);
}//



void generate()
{

mpz_set_str(p,"A9FB57DBA1EEA9BC3E660A909D838D726E3BF623D52620282013481D1F6E5377",16);
mpz_set_str(a,"7D5A0975FC2C3057EEF67530417AFFE7FB8055C126DC5C6CE94A4B44F330B5D9",16);
mpz_set_str(b,"26DC5C6CE94A4B44F330B5D9BBD77CBF958416295CF7E1CE6BCCDC18FF8C07B6",16);
mpz_set_str(Gx,"8BD2AEB9CB7E57CB2C4B482FFC81B7AFB9DE27E1E3BD23C23A4453BD9ACE3262",16);
mpz_set_str(Gy,"547EF835C3DAC4FD97F8461A14611DC9C27745132DED8E545C1D54C72F046997",16);
mpz_set_str(q,"A9FB57DBA1EEA9BC3E660A909D838D718C397AA3B561A6F7901E0E82974856A7",16);
mpz_mod(Gx,Gx,p);
mpz_mod(Gy,Gy,p);
gmp_randstate_t s1;
gmp_randinit_mt(s1);
gmp_randseed_ui(s1,time(NULL));
mpz_rrandomb(r,s1,10);
//gmp_printf("Generating r: %Zd\n",r);

gmp_randclear(s1);


}


void add(mpz_t xa,mpz_t ya,mpz_t xb,mpz_t yb, mpz_t addx, mpz_t addy){
mpz_t lam,lam2,x3,y3,temp;
mpz_init(lam);
mpz_init(lam2);
mpz_init(x3);
mpz_init(y3);
mpz_init(temp);
mpz_t yan,ybn;
mpz_init(yan);
mpz_init(ybn);
mpz_sub(yan,p,ya);
//mpz_mod(yan,yan,p);
mpz_sub(ybn,p,yb);
//mpz_mod(ybn,ybn,p);


if(mpz_cmp_ui(xa,0)==0 && mpz_cmp_ui(ya,0)==0)
	{mpz_set(addx,xb);mpz_set(addy,yb);}
if (mpz_cmp_ui(xb,0)==0 && mpz_cmp_ui(yb,0)==0 )
	{mpz_set(addx,xa);mpz_set(addy,ya);}
if(mpz_cmp(xa,xb)==0 && (mpz_cmp(ya,ybn)==0||mpz_cmp(yan,yb)==0) )
	{mpz_set_ui(addx,0);mpz_set_ui(addy,0);}
if(mpz_cmp(xa,xb)==0 && mpz_cmp(ya,yb)==0){

//mpz_pow_ui(lam,xa,2);
mpz_mul(lam,xa,xa);mpz_mod(lam,lam,p);

mpz_mul_ui(lam,lam,3);

mpz_add(lam,lam,a);
mpz_mul_ui(lam2,ya,2);
mpz_invert(lam2,lam2,p);mpz_mod(lam2,lam2,p);
mpz_mul(lam,lam,lam2);mpz_mod(lam,lam,p);


mpz_powm_ui(x3,lam,2,p);
mpz_mul_ui(temp,xa,2);
mpz_sub(x3,x3,temp);

mpz_sub(y3,xa,x3);
mpz_mul(y3,y3,lam);
mpz_sub(y3,y3,ya);

mpz_mod(x3,x3,p);
mpz_mod(y3,y3,p);
mpz_set(addx,x3);
mpz_set(addy,y3);

//return 
}
else{
mpz_sub(lam,ya,yb);mpz_mod(lam,lam,p);
mpz_sub(lam2,xa,xb);mpz_mod(lam2,lam2,p);
mpz_invert(lam2,lam2,p);
mpz_mul(lam,lam,lam2);mpz_mod(lam,lam,p);

mpz_powm_ui(x3,lam,2,p);
mpz_sub(x3,x3,xb);
mpz_sub(x3,x3,xa);

mpz_sub(y3,xa,x3);
mpz_mul(y3,y3,lam);
mpz_sub(y3,y3,ya);

mpz_mod(x3,x3,p);
mpz_mod(y3,y3,p);
mpz_set(addx,x3);
mpz_set(addy,y3);
}
	mpz_clear(lam);
	mpz_clear(lam2);
	mpz_clear(x3);
	mpz_clear(y3);
	mpz_clear(temp);
	mpz_clear(ybn);

}

void mult(mpz_t x,mpz_t y,mpz_t k1, mpz_t mux, mpz_t muy)
{
	mpz_t nx,ny,rx,ry,t2,k2;
	mpz_init(nx);
	mpz_init(ny);
	mpz_init(rx);
	mpz_init(ry);
	mpz_init(t2);
	mpz_init(k2);
	mpz_set(nx,x);
	mpz_set(ny,y);
	mpz_set(k2,k1);
	
	while (mpz_cmp_ui(k2,0)!=0)
	{	
		if (mpz_mod_ui(t2,k2,2)==1)
		{add(rx,ry,nx,ny,rx,ry);}
		add(nx,ny,nx,ny,nx,ny);
		mpz_fdiv_q_ui(k2,k2,2);
		
		
	}

	mpz_mod(rx,rx,p);
	mpz_mod(ry,ry,p);
	mpz_set(mux,rx);
	mpz_set(muy,ry);


	mpz_clear(nx);
	mpz_clear(ny);
	mpz_clear(rx);
	mpz_clear(ry);
	mpz_clear(t2);
	mpz_clear(k2);

}

void generateK(mpz_t k)
{
mult(Gx,Gy,k, Kx, Ky);
}

void encrypt(mpz_t mx,mpz_t my, mpz_t c1x, mpz_t c1y, mpz_t c2x, mpz_t c2y)
{
mpz_t t1x,t1y;
mpz_init(t1x);
mpz_init(t1y);
//mpz_init(t2x);
//mpz_init(t2y);
mult(Kx,Ky,r,t1x,t1y);

add(mx,my,t1x,t1y,c1x,c1y);


mult(Gx,Gy,r,c2x,c2y);




}

void decrypt(mpz_t c1x, mpz_t c1y, mpz_t c2x, mpz_t c2y, mpz_t k, mpz_t dx, mpz_t dy)
{
mpz_t t2x,t2y;
mpz_init(t2x);
mpz_init(t2y);
mult(c2x,c2y,k,t2x,t2y);

mpz_t t3x,t3y;
mpz_init(t3x);
mpz_init(t3y);

mpz_set(t3x,t2x);
mpz_sub(t3y,p,t2y);
//mpz_mod(t3x,t3x,p);
//mpz_mod(t3y,t3y,p);

add(c1x,c1y,t3x,t3y,dx,dy);

	mpz_clear(t2x);
	mpz_clear(t2y);
	mpz_clear(t3x);
	mpz_clear(t3y);

}


char* strtoint(char* ori){
char* res=(char*)malloc(strlen(ori)*2*sizeof(char));
int i=0;
char temp[2]="";
int t;
for (i=0;i<strlen(ori);i++){
if (ori[i]<=57&&ori[i]>=48){
t=(int)ori[i]-38;
}
if (ori[i]<=122&&ori[i]>=65){
t=(int)ori[i]-45;
}

if (ori[i]==44){
t=78;
}
if (ori[i]==46){
t=79;
}
if (ori[i]==33){
t=80;
}
if (ori[i]==40){
t=81;
}
if (ori[i]==41){
t=82;
}

sprintf(temp,"%d",t);

strcat(res,temp);
//printf ("%s\n",res);
}
return res;
}

