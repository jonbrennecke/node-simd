#include "instructions.h"

#include <time.h>

int main()
{	
	const size_t n = 102400003;

	// ~~~~~~~~~~~~~~~~~~~~ test 128bit ~~~~~~~~~~~~~~~~~~~~
	std::clock_t start;
    double duration;
    start = std::clock();
	auto p = vector16(n);
	auto q = vector16(n);

	for (size_t i = 0; i < p.size(); ++i)
	{
		p[i] = 2.0;
		q[i] = 1.3;
	}

	printf("%f\n",mul128(&p,&q));
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"duration: "<< duration <<'\n';

	// ~~~~~~~~~~~~~~~~~~~~ test 256bit ~~~~~~~~~~~~~~~~~~~~
    start = std::clock();
	auto x = vector32(n);
	auto y = vector32(n);

	for (size_t i = 0; i < x.size(); ++i)
	{
		x[i] = 2.0;
		y[i] = 1.3;
	}

	printf("%f\n",mul256(&x,&y));
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"duration: "<< duration <<'\n';

    // ~~~~~~~~~~~~~~~~~~~~ test non SSE version ~~~~~~~~~~~~~~~~~~~~

	start = std::clock();
	auto s = vector16(n);
	auto t = vector16(n);

	for (size_t i = 0; i < x.size(); ++i)
	{
		s[i] = 2.0;
		t[i] = 1.3;
	}

	double count = 0.0;
	for (size_t i = 0; i < s.size(); ++i)
	{
		count += s[i]*t[i];
	}

	printf("%f\n",count);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"duration: "<< duration <<'\n';


	return 0;
}