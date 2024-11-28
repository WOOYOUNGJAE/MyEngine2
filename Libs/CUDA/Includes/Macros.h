#ifndef CUDACORE_MACROS
#define CUDACORE_MACROS

# define CUDA_SAFE_CALL_ALWAYS(FUNC) \
FUNC; \
cudaDeviceSynchronize(); \
if (cudaPeekAtLastError() != cudaSuccess) \
std::cerr << cudaGetErrorString(cudaGetLastError());

#endif

