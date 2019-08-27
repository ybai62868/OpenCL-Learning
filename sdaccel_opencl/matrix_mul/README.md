Vector Addition Example
===============================

This is a simple example of vector addition.
The purpose of this code is to introduce the user to application development
in SDAccel.

Change log
----------
08/02/2016 - Converted to Makefile/xocc flow
1/28/2016 - Initial Release

Files in the Example
---------------------
Application host code
- vadd.cpp
- vadd.h
- xcl.c
- xcl.h

Kernel code
- krnl_vadd.cl

Compilation File
sdaccel.mk : Makefile for compiling SDAccel application
common.mk in ../common directory is also required for compilation

Compilation and Emulation
---------------------------
* Set up environment for SDAccel
* Run "make -f sdaccel.mk help" for further instructions

Executing the Application on FPGA
---------------------------------
* Set up the target FPGA board as described in SDAccel installation guide. 
  Make a note of the board installation directory as it will be used below.
  This step can be skipped if the target board and driver have already been
  set up. 

* For C-shell
  $source <board_installation_dir>/setup.csh 
  For Bash
  $source <board_installation_dir>/setup.sh 

* Run the application
  ./vector_addition.exe bin_vadd_hw.xclbin

