
namespace Cuda {


#ifdef __INTELLISENSE__
#define CUDA_KERNEL(...)
#else
#define CUDA_KERNEL(...) <<< __VA_ARGS__ >>>
#endif


	void kernel(double* A, double* B, double* C, int arraySize);
	void RunTest();

}
