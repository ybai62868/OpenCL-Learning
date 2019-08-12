
kernel void __attribute__((reqd_work_group_size(1, 1, 1)))
vector_add(
		  __global int * a,
		  __global int * b,
		  __global int * c,
		  const int length)
{
	// for (int i = 0; i < length; i++) {
	// 	c[i] = a[i] + b[i];
	// }
	int i = get_global_id(0);
	c[i] = a[i] + b[i];
}