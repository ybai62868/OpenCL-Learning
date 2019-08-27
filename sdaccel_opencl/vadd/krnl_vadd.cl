__kernel void __attribute__ ((reqd_work_group_size(1, 1, 1)))
krnl_vadd(
     __global int* a,
     __global int* b,
     __global int* c,
     const int length) {


  for(int i = 0; i < length; i++){
  	for (int j = 0;j < length; j++){
  		__local int temp;
  		temp = 0;
  		for (int k = 0;k < length;k++){
  			temp += a[k + (i*length)] * b[j + (k*length)];
  		}
  		c[j + (i*length)] = temp;
  	}
  }

  return;
}