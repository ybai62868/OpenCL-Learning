__kernel void __attribute__ ((reqd_work_group_size(1, 1, 1)))
krnl_vadd(
     __global int* a,
     __global int* b,
     __global int* c,
     const int length) {


  for(int i = 0; i < length; i++){
    c[i] = a[i] + b[i];
  }

  return;
}