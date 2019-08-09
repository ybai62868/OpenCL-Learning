
# define MAX 256
kernel __attribute__((reqd_work_group_size(1, 1, )))
void vector_add(global int * c,
				global const int * a,
				global const int * b,
					   const int n_elements)
{
	
}