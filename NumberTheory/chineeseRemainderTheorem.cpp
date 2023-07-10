
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int64_t getGcd(int64_t a,int64_t b)
{
	while(b!=0)
	{
		int64_t temp=a%b;
		a=b;
		b=temp;
	}
	return a;
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
	int64_t inverseA,temp;
	int64_t gcd=extendedGcd(a,m,&inverseA,&temp);
	assert(gcd==1);

	inverseA=(inverseA+m)%m;

	return inverseA;
}

//Source: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
int64_t on2CoPrimesCRT(int64_t m1,int64_t r1,int64_t m2,int64_t r2)
{
	int64_t n1,n2;
	int64_t gcd=extendedGcd(m1,m2,&n1,&n2);
	assert(gcd==1); // moduli must be coprime

	int64_t lcm=m1*m2;

	auto mod_add=[&lcm](const int64_t a,const int64_t b){return (a%lcm+b%lcm)%lcm;};
	auto mod_mul=[&lcm](const int64_t a,const int64_t b){return (a%lcm*b%lcm)%lcm;};
	auto mod_pos=[&lcm](const int64_t a){return (a+lcm)%lcm;};

	int64_t x=mod_add( mod_mul(mod_mul(r2,n1),m1), mod_mul(mod_mul(r1,n2),m2) );
	x=mod_pos(x);

	return x;
}
int64_t onNCoPrimesCRT(const vector<int64_t>& moduli,vector<int64_t>& remainders)
{
	const int n=moduli.size();
	assert(n==remainders.size());

	// for(int i=0;i<n;++i)
	// 	for(int j=i+1;j<n;++j)
	// 		assert(getGcd(moduli[i],moduli[j])==1); //moduli must be coprimes

	int64_t lcm=1;
	for(const int& mm:moduli)
		lcm*=mm;

	auto mod_add=[&lcm](const int64_t a,const int64_t b){return (a%lcm+b%lcm)%lcm;};
	auto mod_mul=[&lcm](const int64_t a,const int64_t b){return (a%lcm*b%lcm)%lcm;};
	auto mod_pos=[&lcm](const int64_t a){return (a+lcm)%lcm;};

	int64_t num=0;
	for(int i=0;i<n;++i)
	{
		int64_t exceptSelfProduct = lcm/moduli[i];
		int64_t nn = mod_mul( mod_mul(remainders[i],exceptSelfProduct), multiplicativeModuloInverse(exceptSelfProduct,moduli[i]) );
		num = mod_add(num,nn);
	}

	return mod_pos(num);
}

//Source: https://forthright48.com/chinese-remainder-theorem-part-2-non-coprime-moduli/
int64_t on2CRT(int64_t m1,int64_t r1,int64_t m2,int64_t r2)
{//works also when both divisors are not co-primes

//Note: when moduli are of order 10^9 use __int128

	int64_t n1,n2;
	int64_t g=extendedGcd(m1,m2,&n1,&n2);

	int64_t r=r2-r1;
	assert(r%g==0);

	int64_t lcm=m1*(m2/g);

	m1/=g;
	m2/=g;

	auto mod_add=[&lcm](const int64_t a,const int64_t b){return (a%lcm+b%lcm)%lcm;};
	auto mod_mul=[&lcm](const int64_t a,const int64_t b){return (a%lcm*b%lcm)%lcm;};
	auto mod_pos=[&lcm](const int64_t a){return (a+lcm)%lcm;};

	int64_t x=mod_add( mod_mul(mod_mul(r2,n1),m1), mod_mul(mod_mul(r1,n2),m2) );
	x=mod_pos(x);

	return x;
}
int64_t onNCRT(const vector<int64_t>& moduli,const vector<int64_t>& remainders)
{//works also when both divisors are not co-primes

//Note: when moduli are of order 10^9 use __int128

	int64_t m1=moduli[0];
	int64_t r1=remainders[0];

	const int n=moduli.size();
	for(int i=1;i<n;++i)
	{
		int m2=moduli[i];
		int r2=remainders[i];

		int64_t n1,n2;
		int64_t g=extendedGcd(m1,m2,&n1,&n2);

		int64_t r=r2-r1;
		assert(r%g==0);

		int64_t lcm=m1*(m2/g);

		m1/=g;
		m2/=g;

		auto mod_add=[&lcm](const int64_t a,const int64_t b){return (a%lcm+b%lcm)%lcm;};
		auto mod_mul=[&lcm](const int64_t a,const int64_t b){return (a%lcm*b%lcm)%lcm;};
		auto mod_pos=[&lcm](const int64_t a){return (a+lcm)%lcm;};

		int64_t x=mod_add( mod_mul(mod_mul(r2,n1),m1), mod_mul(mod_mul(r1,n2),m2) );
		x=mod_pos(x);

		r1=x;
		m1=lcm;
	}

	return r1;
}

int main()
{
	int64_t m1=7,r1=5;
	int64_t m2=3,r2=2;
	int64_t num=on2CRT(m1,r1,m2,r2);
	cout<<num<<"\n";

	// vector<int64_t> moduli={5,6,7,11};
	// vector<int64_t> remainders={3,3,1,0};
	// int64_t num=onNCRT(moduli,remainders);
	// cout<<num<<"\n";

	return 0;
}