#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif
 

 ////////////////////////////////////////////////////////////////////////////////
 
// Use a static data size for simplicity
//
#define DATA_SIZE (1024)

////////////////////////////////////////////////////////////////////////////////

// Simple compute kernel which computes two vector addition
const char * KernelVecAdd = "\n" \
"__kernel void vecadd(                                                  \n" \
"   __global float* input1,                                             \n" \
"   __global float* input2,                                             \n" \
"   __global float* output,                                             \n" \
"   const unsigned int count)                                           \n" \
"{                                                                      \n" \
"   int i = get_global_id(0);                                           \n" \
"   if(i < count)                                                       \n" \
"       output[i] = input1[i] + input2[i];                              \n" \
"}                                                                      \n" \
"\n";

 
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    int err;                            // error code returned from api calls
      
    float data1[DATA_SIZE];             // original data set given to device
    float data2[DATA_SIZE];
    float results[DATA_SIZE];           // results returned from device
    unsigned int correct;               // number of correct results returned
 
    size_t global;                      // global domain size for our calculation
    size_t local;                       // local domain size for our calculation
 
    cl_device_id device_id;             // compute device id 
    cl_context context;                 // compute context
    cl_command_queue commands;          // compute command queue
    cl_program program;                 // compute program
    cl_kernel kernel;                   // compute kernel
    
    cl_mem matrix_A;                    // device memory used for the input array
    cl_mem matrix_B;
    cl_mem matrix_C;                     // device memory used for the output array
    
    // Fill our data set with random float values
    //
    unsigned int count = DATA_SIZE;
    for(int i = 0; i < count; i++) {
        data1[i] = rand() / (float)RAND_MAX;
        data2[i] = rand() / (float)RAND_MAX;
    }

    // Connect to a compute device
    //
    int gpu = 1;
    err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to create a device group!\n");
        return EXIT_FAILURE;
    }
    // TODO:LIST


    // Validate our results
    //
    correct = 0;
    for (int i = 0;i < count;i++) {
        for (int j = 0;j < count; j++) {
            for (int k = 0;k < count;k++ ) {

            }
        }
    }
    
    // Shutdown and cleanup
    //
    clReleaseMemObject(matrix_A);
    clReleaseMemObject(matrix_B);
    clReleaseMemObject(matrix_C);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
 




    return 0;       
}