
#include <iostream>
#include <cassert>

using namespace std;

int64_t modMul(int64_t a,int64_t b,int64_t m)
{
	return ((a%m)*(b%m))%m;
}
int64_t modAdd(int64_t a,int64_t b,int64_t m)
{
	return (a%m+b%m)%m;
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

int64_t multiplicativeModuloInverse(int64_t a,int64_t m)
{
	//[a*inverse(a)]%m = 1
	
	//Fermat Little Theorem: a^phi(m) = 1(mod m) ==> a^(phi(m)-1) = a^(-1)(mod m)
	//						 when m is prime phi(m)=m-1, so when m=prime, a^(m-1) = 1(mod m) ==> a^(m-2) = a^(-1)(mod m)
	
	//Extended Euclidin Theorem: a*inverse(a) = 1(mod m) ==> a*inverse(a) - 1 = m*y (some intezer y) ==> inverse(a)*a + (-y)*m = 1
	//Bezout Theorem says there always exists integeral solution for equation of form xa + yb = 1 when a and b are co-prime
	//So, a^(-1) is just first coeficient of the above equation: inverse(a)*a + (-y)*m = 1

	int64_t inverseA;

	// inverseA = myPowMod(a,m-2,m); //based on fermat little theorem for prime m

	int64_t temp;
	int64_t gcd=extendedGcd(a,m,&inverseA,&temp); //based on extended euclidin theorem + bezout theorem, a and m must be coprime
	assert(gcd==1);

	inverseA=(inverseA+m)%m;

	return inverseA;
}

int main()
{
	int64_t a=3,m=1e9+7;

	cout<<multiplicativeModuloInverse(a,m)<<"\n";

	return 0;
}