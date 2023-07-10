
#include <iostream>

using namespace std;

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

int main()
{
	int64_t a=5,b=6;
	int64_t x,y;
	int64_t g=extendedGcd(a,b,&x,&y);

	cout<<"GCD: "<<g<<" | Coefficients[x,y] in "<<a<<"x+"<<b<<"y="<<g<<": "<<x<<" "<<y<<endl;

	return 0;
}