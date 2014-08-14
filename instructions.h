#include "virtue.h"
#include "vector.h"

/*

	128bit

*/
static inline double mul128( vector16* restrict p, vector16* restrict q )
{
	if ( p->size() != q->size() )
		std::cerr << "Error: mul128: the vector sizes must be equal.";

	__m128d P, Q, W;

	W = _mm_set_pd(0.0,0.0);

	for (size_t i = 0; i < p->size(); i+=2)
	{
		P = _mm_load_pd(p->elems+i);
		Q = _mm_load_pd(q->elems+i);
		W = _mm_hadd_pd(W, _mm_mul_pd(P,Q));
	}

	return (double)W[0] + (double)W[1];
}

/*

	optimize multiplication with 256bit SSE/AVX instrutions 

*/
static inline double mul256( vector32* restrict p, vector32* restrict q )
{
	size_t size = p->size(), n = (size%4?size:p->realsize()-3);

	if ( !size )
		return 0.0;

	if ( size != q->size() )
		std::cerr << "Error: mul256: the vector sizes must be equal.";

	__m256d P, Q, W;
	W = _mm256_set_pd(0.0,0.0,0.0,0.0);

	for (size_t i = 0; i < n; i+=4)
	{
		P = _mm256_load_pd(p->elems+i);
		Q = _mm256_load_pd(q->elems+i);
		W = _mm256_hadd_pd(W, _mm256_mul_pd(P,Q));
	}

	__m128d upper = _mm256_extractf128_pd(W, 1); // add upper 128 bits of W to its lower 128 bits
	__m128d sum = _mm_add_pd(upper, _mm256_castpd256_pd128(W));
	double ret = (double)sum[0] + (double)sum[1];

	size_t dif = p->realsize() - size;
	if ( dif )
	{
		size_t nextra = (4-dif);
		for (size_t i = 0; i < nextra; ++i, n+=i)
		{
			ret += *(p->elems+n) * *(q->elems+n);
		}
		return ret;
	}
	else { return ret; }
}