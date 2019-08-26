
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

	if (krnl_match) {
		return 1;
	}
	else {
		std::cout << "Success! kenrel results match cpu results." << std::endl;
		return 0;
	}








}