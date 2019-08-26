
 #define CL_HPP_CL_1_2_DEFAULT_BUILD
 #define CL_HPP_TARGET_OPENCL_VERSION 120
 #define CL_HPP_MINIMUM_OPENCL_VERSION 120
 #define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <CL/cl2.hpp>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

#pragma once
#define LENGTH (1024)
#define NUM_WORKGROUPS (1)
#define WORKGROUP_SIZE (16)


int main(int argc, char* argv[1])
{
#if defined(SDX_PLATFORM) && !defined(TARGET_DEVICE)
	#define STR_VALUE(arg) #arg
	#define GET_STARTING(name) STR_VALUE(name)
	#define TARGET_DEVICE GET_STARTING(SDX_PLATFORM)
#endif

	char* xclbinFilename = argv[1];
	size_t vector_size_bytes = sizeof(int) * LENGTH;

	// Source Memory
	float source_a[LENGTH];
	float source_b[LENGTH];
	float result_sim[LENGTH];
	float result_krnl[LENGTH];


	// Create the test data and golden data locally
	for (int i = 0;i < LENGTH;i++) {
		source_a[i] = i;
		source_b[i] = 2 * i;
		result_sim[i] = source_a[i] + source_b[i];
	} 

// OPENCL HOST CODE AREA START

	// Getting  First Platform
	cl_platform_id platform_id;

	err = clGetPlatformIDs(16, platforms, &platform_count);

	// Find Xilinx Platform
	for (unsigned int iplat = 0; iplat < platform_count; iplat++) {
		err = clGetPlatformInfo(platforms[iplat],
			CL_PLATFORM_VENDOR,
			1000,
			(void *)cl_platform_vendor,
			NULL);

		if (strcmp(cl_platform_vendor, "Xilinx") == 0) {
			// Xilinx Platform found
			platform_id = platforms[iplat];
		}
	}
	err = clGetPlatformIDs(16, platforms, &platform_count);
	if (err != CL_SUCCESS) {
		std::cout << "Error: Faild to find an OpenCL platform!" << std::endl;
		std::cout << "Test faild" << std::endl;
		exit(1);
	}


	// Getting ACCELERATOR Devices and selecting 1st such device
	cl_device_id devices[16];
	char cl_device_name[1001];

	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ACCELERATOR,
		1, devices, &num_devices);
	printf("INFO: Found %d devices\n", num_devices);

	// iterate all devices to selecet the target device.
	for (int i = 0; i < num_devices; i++) {
		err = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 1024, cl_device_name, 0);
		std::cout << "CL_DEVICE_NAME" << cl_device_name << std::cout;
	}

	// Creating Context and Command Queue for selected Device
	context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
	if (!context) {
		std::cout << "Error: Faild to create a compute context!" << std::endl;
		exit(1);
	}

	// Create a In-order Command Queue
	commands = clCreateCommandQueue(context, device_id, 0, &err);

	// Create the compute program from the Binary file
	unsigned char *kernelbinary;
	char *xclbin = argv[1];
	std::cout << "INFO: loading xclbin" << xclbin;

	int size = load_file_to_memory(xclbin, (char**) &kernelbinary);
	size_t size_var = size;
	cl_program program = clCreateProgramWithBinary(context, 1, &device_id, 
												&size_var, (const unsigned char **) &kernelbinary,
												&status, &err);
	// Function 
	int load_file_to_memory(const char *filename, char **result)




	// Create Buffers inside Device
	cl_mem buffer_a = clCreateBuffer(context, CL_MEM_WRITE, size, &host_)
	cl_mem buffer_b = 
	cl_mem buffer_c = 




// OPENCL HOST CODE AREA END

	/* Compare the results of the kernel to the simulation*/
	int krnl_match = 0;
	for (int i = 0;i < LENGTH;i++) {
		if (result_sim[i] != result_krnl[i]) {
			std::cout << "Error: Result mismatch" << std::endl;
			std::cout << "i = " << i << "GPU result = " << result_sim[i] << "Krnl Result = " << result_krnl[i] << std::endl;
			krnl_match = 1;
			break;
		}
		else {
			std::cout << "Result Match: i = " << i << "CPU result = " << result_sim[i] << "Krnl Result =" << result_krnl[i] << std::endl;
		}
	}


	//Shutdown and cleanup
	clReleaseMemObject();
	clReleaseCommandQueue();
	clReleaseContext();
	clReleaseKernel();
	clReleaseProgram();


	if (krnl_match) {
		return 1;
	}
	else {
		std::cout << "Success! kenrel results match cpu results." << std::endl;
		return 0;
	}








}