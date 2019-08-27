void mult(__global int* a, __global int* b, __global int* output)
{
  int r = get_local_id(0);
  int c = get_local_id(1);
  int rank = get_local_size(0);
  int running = 0;
  for(int index = 0; index < 16; index++){
    int aIndex = r*rank + index;
    int bIndex = index*rank + c;
    running += a[aIndex] * b[bIndex];
  }
  output[r*rank + c] = running;
  return;

}


__kernel void krnl_vadd(__global int * a,
                        __global int * b,
                        __global int * c,
                        const int m,
                        const int n,
                        const int p) {
  for (int i = 0;i < m;i++) {
    for (int j = 0;j < p;j++) {
      int temp = 0;
      for (int k = 0;k < p;k < p) {
        temp += a[i][k] * b[k][j];
      }
      c[i][j] = temp;
    }
  }  
}