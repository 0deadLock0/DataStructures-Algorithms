
#include <iostream>
#include <cassert>

using namespace std;

int64_t modAdd(int64_t a,int64_t b,int64_t m)
{
	return (a%m+b%m)%m;
}
int64_t modMul(int64_t a,int64_t b,int64_t m)
{
	return ((a%m)*(b%m))%m;
}
int64_t modSub(int64_t a,int64_t b,int64_t m)
{
	return (a%m-b%m+m)%m;
}

int64_t myPowMod(int64_t num,int64_t power,int64_t mod)
{
	if(power==0)
		return 1;
	else if(power==1)
		return num%mod;
	else
	{
		int64_t subResult=myPowMod(num,power>>1,mod);
		int64_t result=modMul(subResult,subResult,mod);
		if(power&1)
			result=modMul(result,num,mod);
		return result;
	}
}
int64_t multiplicativeModuloInverse(int64_t a,int64_t m)
{//m needs to be prime
	return myPowMod(a,m-2,m);
}
int64_t extendedGcd(int64_t a,int64_t b,int64_t* x,int64_t* y)
{
	if(b==0)
	{
		*x=1;
		*y=0;
		return a;
	}
	else
	{
		int64_t x1,y1;
		int64_t g=extendedGcd(b,a%b,&x1,&y1);
		*x=y1;
		*y=x1-(a/b)*y1;
		return g;
	}
}
int64_t multiplicativeModuloInverse2(int64_t a,int64_t m)
{
	int64_t inverseA,temp;
	int64_t gcd=extendedGcd(a,m,&inverseA,&temp);
	assert(gcd==1);

	inverseA=(inverseA+m)%m;

	return inverseA;
}

int64_t modDiv(int64_t a,int64_t b,int64_t m)
{
	return ((a%m)*modAdd(multiplicativeModuloInverse2(b,m),m,m))%m;
}

int main()
{
	int64_t a=2123132,b=2;
	int64_t m=1e5+3;

	cout<<modDiv(a,b,m)<<"\n";

	return 0;
}