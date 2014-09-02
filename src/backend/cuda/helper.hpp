#pragma once

#include <backend.hpp>

#define divup(a, b) ((a)+(b)-1)/(b)

static inline unsigned nextpow2(unsigned x)
{
	   x = x - 1;
	   x = x | (x >> 1);
	   x = x | (x >> 2);
	   x = x | (x >> 4);
	   x = x | (x >> 8);
	   x = x | (x >>16);
	   return x + 1;
}

namespace cuda
{

template <typename T>
struct SharedMemory
{
    // return a pointer to the runtime-sized shared memory array.
    __device__ T* getPointer()
    {
        extern __device__ void Error_UnsupportedType(); // Ensure that we won't compile any un-specialized types
        Error_UnsupportedType();
        return (T*)0;
    }
};

#define DECLARE_SPECIALIZATIONS(T)                                          \
template <>                                                                 \
struct SharedMemory <T>                                                     \
{                                                                           \
    __device__ T* getPointer() {                                            \
        extern __shared__ T ptr_##T##_[];                                   \
        return ptr_##T##_;                                                  \
    }                                                                       \
};

DECLARE_SPECIALIZATIONS(float)
DECLARE_SPECIALIZATIONS(cfloat)
DECLARE_SPECIALIZATIONS(double)
DECLARE_SPECIALIZATIONS(cdouble)
DECLARE_SPECIALIZATIONS(char)
DECLARE_SPECIALIZATIONS(int)
DECLARE_SPECIALIZATIONS(uint)
DECLARE_SPECIALIZATIONS(uchar)

template<typename T>
struct kernel_params_t {
    T *             d_dst;
    const T *       d_src;
    dim_type     idims[4];
    dim_type  istrides[4];
    dim_type  ostrides[4];
};

}
