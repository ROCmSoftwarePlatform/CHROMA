#ifndef CPP_DSLASH_SCALAR_32BIT_SSE_H
#define CPP_DSLASH_SCALAR_32BIT_SSE_H

#include <xmmintrin.h>

#ifndef ALIGN
#define ALIGN __attribute__ ((aligned(16)))
#endif

#include <cpp_dslash_types.h>

namespace CPlusPlusWilsonDslash {

  namespace DslashScalar64Bit {

    /* Thread dispatch function for D */
    void DPsiPlus(size_t lo, size_t hi, int id, const void *ptr);
    
    /* Thread dispatch function for D^\dagger */
    void DPsiMinus(size_t lo, size_t hi, int id, const void *ptr);

    /* Thread dispatch function for D */
    void DPsiPlus3D(size_t lo, size_t hi, int id, const void *ptr);
    
    /* Thread dispatch function for D^\dagger */
    void DPsiMinus3D(size_t lo, size_t hi, int id, const void *ptr);


    using namespace Dslash64BitTypes;
    
    typedef union { 
      unsigned int c[4];
      __m128d vector;
    } SSESgn;
    
    typedef union { 
      double c[2];
      __m128d vector;
    } SSESgn2;
    

    inline
    void dslash_plus_dir0_forward(FourSpinor  spinor_in,
				  GaugeMatrix  u,
				  FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    _mm_store_pd(&spinor_out[0][0][0], xmm3);
    _mm_store_pd(&spinor_out[0][1][0], xmm4);
    _mm_store_pd(&spinor_out[0][2][0], xmm5);


    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm3);
    _mm_store_pd(&spinor_out[3][1][0], xmm4);
    _mm_store_pd(&spinor_out[3][2][0], xmm5);
    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */

    _mm_store_pd(&spinor_out[1][0][0], xmm3);
    _mm_store_pd(&spinor_out[1][1][0], xmm4);
    _mm_store_pd(&spinor_out[1][2][0], xmm5);
    
    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    _mm_store_pd(&spinor_out[2][0][0], xmm3);
    _mm_store_pd(&spinor_out[2][1][0], xmm4);
    _mm_store_pd(&spinor_out[2][2][0], xmm5);


  }

    inline
      void dslash_plus_dir0_backward_add( FourSpinor  spinor_in,
					  GaugeMatrix  u,
					  FourSpinor spinor_out) 
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    /* Multiply and accumulate */
    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

  }

    inline
      void dslash_plus_dir1_forward_add(FourSpinor  spinor_in,
					GaugeMatrix  u,
					FourSpinor spinor_out)
  {

    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);
    
    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );
    
    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);


    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);


  }
  
    inline
      void dslash_plus_dir1_backward_add(  FourSpinor  spinor_in,
					   GaugeMatrix  u,
					   FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);


  }

    inline
  void dslash_plus_dir2_forward_add(  FourSpinor  spinor_in,
				      GaugeMatrix  u,
				      FourSpinor spinor_out)
  {

    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);


    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);
    
    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );
    
    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);


    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);


  }
  
    inline
  void dslash_plus_dir2_backward_add(  FourSpinor  spinor_in,
				       GaugeMatrix  u,
				       FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);


    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

  }


inline
  void dslash_plus_dir3_forward_add(  FourSpinor  spinor_in,
				      GaugeMatrix  u,
				      FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);
    
    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );
    
    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm0 = _mm_sub_pd( xmm0, xmm3 );
    xmm1 = _mm_sub_pd( xmm1, xmm4 );
    xmm2 = _mm_sub_pd( xmm2, xmm5 );

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);



  }
  

inline
  void dslash_plus_dir3_backward_add_store(  FourSpinor  spinor_in,
					     GaugeMatrix  u,
					     FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);


    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

  }
  
inline
  void dslash_minus_dir0_forward(  FourSpinor  spinor_in,
				   GaugeMatrix  u,
				   FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};
    SSESgn2 conj = {{ 1,-1 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    _mm_store_pd(&spinor_out[0][0][0], xmm3);
    _mm_store_pd(&spinor_out[0][1][0], xmm4);
    _mm_store_pd(&spinor_out[0][2][0], xmm5);


    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_mul_pd(conj.vector, xmm3);
    xmm4 = _mm_mul_pd(conj.vector, xmm4);
    xmm5 = _mm_mul_pd(conj.vector, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm3);
    _mm_store_pd(&spinor_out[3][1][0], xmm4);
    _mm_store_pd(&spinor_out[3][2][0], xmm5);
    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */

    _mm_store_pd(&spinor_out[1][0][0], xmm3);
    _mm_store_pd(&spinor_out[1][1][0], xmm4);
    _mm_store_pd(&spinor_out[1][2][0], xmm5);
    
    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_mul_pd(conj.vector, xmm3);
    xmm4 = _mm_mul_pd(conj.vector, xmm4);
    xmm5 = _mm_mul_pd(conj.vector, xmm5);

    _mm_store_pd(&spinor_out[2][0][0], xmm3);
    _mm_store_pd(&spinor_out[2][1][0], xmm4);
    _mm_store_pd(&spinor_out[2][2][0], xmm5);


  }
  
inline
  void dslash_minus_dir0_backward_add(  FourSpinor  spinor_in,
					GaugeMatrix  u,
					FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    /* Multiply and accumulate */
    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

  }
  
inline
  void dslash_minus_dir1_forward_add(  FourSpinor  spinor_in,
				       GaugeMatrix  u,
				       FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);
    
    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );
    
    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    xmm0 = _mm_sub_pd( xmm0, xmm3 );
    xmm1 = _mm_sub_pd( xmm1, xmm4 );
    xmm2 = _mm_sub_pd( xmm2, xmm5 );

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);


    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);


  }

  
inline
  void dslash_minus_dir1_backward_add(  FourSpinor  spinor_in,
					GaugeMatrix  u,
					FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

  }
  
inline
  void dslash_minus_dir2_forward_add(  FourSpinor  spinor_in,
				       GaugeMatrix  u,
				       FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);


    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);
    
    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );
    
    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd( xmm0, xmm3 );
    xmm1 = _mm_sub_pd( xmm1, xmm4 );
    xmm2 = _mm_sub_pd( xmm2, xmm5 );

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);


    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

  }
  
inline
  void dslash_minus_dir2_backward_add(  FourSpinor  spinor_in,
					GaugeMatrix  u,
					FourSpinor spinor_out)
  {

   __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);


    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);

    xmm3 = _mm_shuffle_pd(xmm3, xmm3, 0x1);
    xmm4 = _mm_shuffle_pd(xmm4, xmm4, 0x1);
    xmm5 = _mm_shuffle_pd(xmm5, xmm5, 0x1);

    xmm3 = _mm_xor_pd(sse_sgn.vector, xmm3);
    xmm4 = _mm_xor_pd(sse_sgn.vector, xmm4);
    xmm5 = _mm_xor_pd(sse_sgn.vector, xmm5);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);

  }
  
inline
  void dslash_minus_dir3_forward_add(  FourSpinor  spinor_in,
				       GaugeMatrix  u,
				       FourSpinor spinor_out)
  {
 __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );
    
    /* End multiply */

    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);
    
    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );
    
    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);

    xmm0 = _mm_add_pd( xmm0, xmm3 );
    xmm1 = _mm_add_pd( xmm1, xmm4 );
    xmm2 = _mm_add_pd( xmm2, xmm5 );

    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    /* SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0] );
    xmm6 = _mm_load_sd(&u[1][0][0] );
    xmm4 = _mm_load_sd(&u[0][1][0] );
    xmm7 = _mm_load_sd(&u[2][1][0] );
    xmm5 = _mm_load_sd(&u[0][2][0] );
    
    xmm3 = _mm_unpacklo_pd( xmm3, xmm3 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm4 = _mm_unpacklo_pd( xmm4, xmm4 );
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd( xmm5, xmm5 );
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][2][0] );
    xmm7 = _mm_load_sd(&u[2][0][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0] );
    xmm7 = _mm_load_sd(&u[2][2][0] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1] );
    xmm7 = _mm_load_sd(&u[1][1][1] );
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][2][1] );
    xmm7 = _mm_load_sd(&u[0][1][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd( xmm2, xmm6);
    xmm7 = _mm_mul_pd( xmm0, xmm7);
    xmm5 = _mm_add_pd( xmm6, xmm5);
    xmm4 = _mm_add_pd( xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[1][0][1] );
    xmm7 = _mm_load_sd(&u[0][2][1] );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd(&u[2][0][1] );
    xmm6 = _mm_load_sd(&u[1][2][1] );
    xmm7 = _mm_load_sd(&u[2][1][1] );
    
    xmm0 = _mm_unpacklo_pd( xmm0, xmm0 );
    xmm6 = _mm_unpacklo_pd( xmm6, xmm6 );
    xmm7 = _mm_unpacklo_pd( xmm7, xmm7 );
    
    xmm0 = _mm_mul_pd( xmm2, xmm0 );
    xmm6 = _mm_mul_pd( xmm1, xmm6 );
    xmm7 = _mm_mul_pd( xmm2, xmm7 );
    xmm3 = _mm_add_pd( xmm0, xmm3 );
    xmm5 = _mm_add_pd( xmm6, xmm5 );
    xmm4 = _mm_add_pd( xmm7, xmm4 );

    /* End Multiply */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);

    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);


    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);


  }
  
inline
  void dslash_minus_dir3_backward_add_store(  FourSpinor  spinor_in,
					      GaugeMatrix  u,
					      FourSpinor spinor_out)
  {
    __m128d xmm0 ALIGN;
    __m128d xmm1 ALIGN;
    __m128d xmm2 ALIGN;
    __m128d xmm3 ALIGN;
    __m128d xmm4 ALIGN;
    __m128d xmm5 ALIGN;
    __m128d xmm6 ALIGN;
    __m128d xmm7 ALIGN;

    SSESgn sse_sgn = {{ 0x0, 0x80000000, 0x0, 0x0 }};

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[0][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[2][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[2][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[2][2][0]);

    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);


    /* Adj Su3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);

    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[0][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[0][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[0][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[0][0][0], xmm0);
    _mm_store_pd(&spinor_out[0][1][0], xmm1);
    _mm_store_pd(&spinor_out[0][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[2][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[2][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[2][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Store */
    _mm_store_pd(&spinor_out[2][0][0], xmm0);
    _mm_store_pd(&spinor_out[2][1][0], xmm1);
    _mm_store_pd(&spinor_out[2][2][0], xmm2);

    /* Component 0 of the input spinor */
    xmm0 = _mm_load_pd(&spinor_in[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_in[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_in[1][2][0]);
    
    /* Component 3 of the input spinor */
    xmm3 = _mm_load_pd(&spinor_in[3][0][0]);
    xmm4 = _mm_load_pd(&spinor_in[3][1][0]);
    xmm5 = _mm_load_pd(&spinor_in[3][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    /* Adj SU3 Multiply */
    xmm3 = _mm_load_sd(&u[0][0][0]);  /* _c11_re */
    xmm6 = _mm_load_sd(&u[0][1][0]);  /* _c21_re */
    xmm4 = _mm_load_sd(&u[1][0][0]);  /* _c12_re */
    xmm7 = _mm_load_sd(&u[1][2][0]);  /* _c32_re */
    xmm5 = _mm_load_sd(&u[2][0][0]);  /* _c13_re */
    
    xmm3 = _mm_unpacklo_pd(xmm3, xmm3); 
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm4 = _mm_unpacklo_pd(xmm4, xmm4);
    
    xmm3 = _mm_mul_pd(xmm0, xmm3);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm5 = _mm_unpacklo_pd(xmm5, xmm5);
    
    xmm4 = _mm_mul_pd(xmm0, xmm4);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_mul_pd(xmm0, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd(&u[2][1][0]); /* _c23_re */
    xmm7 = _mm_load_sd(&u[0][2][0]); /* _c31_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm3 = _mm_add_pd(xmm7, xmm3);
    
    xmm6 = _mm_load_sd(&u[1][1][0]); /* _c22_re */
    xmm7 = _mm_load_sd(&u[2][2][0]); /* _c33_re */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    xmm4 = _mm_add_pd(xmm6, xmm4);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm6 = _mm_load_sd(&u[0][0][1]); /* _c11_im */
    xmm7 = _mm_load_sd(&u[1][1][1]); /* _c22_im */
    
    xmm0 = _mm_xor_pd(sse_sgn.vector, xmm0);
    xmm1 = _mm_xor_pd(sse_sgn.vector, xmm1);
    xmm2 = _mm_xor_pd(sse_sgn.vector, xmm2);
    
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_shuffle_pd(xmm0, xmm0, 0x1);
    xmm1 = _mm_shuffle_pd(xmm1, xmm1, 0x1);
    xmm2 = _mm_shuffle_pd(xmm2, xmm2, 0x1);
    
    xmm6 = _mm_mul_pd(xmm0, xmm6);
    xmm7 = _mm_mul_pd(xmm1, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[2][2][1] ); /* c33im */
    xmm7 = _mm_load_sd( &u[1][0][1] ); /* c12im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm2, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    xmm6 = _mm_load_sd( &u[0][1][1] ); /* c21im */
    xmm7 = _mm_load_sd( &u[2][0][1] ); /* c13im */
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm0, xmm7);
    xmm3 = _mm_add_pd(xmm6, xmm3);
    xmm5 = _mm_add_pd(xmm7, xmm5);
    
    xmm0 = _mm_load_sd( &u[0][2][1] ); /* c31im */
    xmm6 = _mm_load_sd( &u[2][1][1] ); /* c23im */
    xmm7 = _mm_load_sd( &u[1][2][1] ); /* c32im */
    
    xmm0 = _mm_unpacklo_pd(xmm0, xmm0);  
    xmm6 = _mm_unpacklo_pd(xmm6, xmm6);
    xmm7 = _mm_unpacklo_pd(xmm7, xmm7);
    
    xmm0 = _mm_mul_pd(xmm2, xmm0);
    xmm6 = _mm_mul_pd(xmm1, xmm6);
    xmm7 = _mm_mul_pd(xmm2, xmm7);
    
    xmm3 = _mm_add_pd(xmm0, xmm3);
    xmm5 = _mm_add_pd(xmm6, xmm5);
    xmm4 = _mm_add_pd(xmm7, xmm4);
    
    /* End multiply */

    /* Load sum */
    xmm0 = _mm_load_pd(&spinor_out[1][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[1][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[1][2][0]);

    /* Accumulate */
    xmm0 = _mm_add_pd(xmm0, xmm3);
    xmm1 = _mm_add_pd(xmm1, xmm4);
    xmm2 = _mm_add_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[1][0][0], xmm0);
    _mm_store_pd(&spinor_out[1][1][0], xmm1);
    _mm_store_pd(&spinor_out[1][2][0], xmm2);


    /* Load Sum */
    xmm0 = _mm_load_pd(&spinor_out[3][0][0]);
    xmm1 = _mm_load_pd(&spinor_out[3][1][0]);
    xmm2 = _mm_load_pd(&spinor_out[3][2][0]);


    xmm0 = _mm_sub_pd(xmm0, xmm3);
    xmm1 = _mm_sub_pd(xmm1, xmm4);
    xmm2 = _mm_sub_pd(xmm2, xmm5);

    _mm_store_pd(&spinor_out[3][0][0], xmm0);
    _mm_store_pd(&spinor_out[3][1][0], xmm1);
    _mm_store_pd(&spinor_out[3][2][0], xmm2);


  }
  }
}
#endif

    



