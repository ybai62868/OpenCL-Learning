
__kernel void vector_add(__global float * input1,
                         __global float * input2,
                         __global float * output,
                         const unsigned int count)
{
    int i = get_global_id(0);
    if (i < count) {
        output[i] = input1[i] + input2[i];
    }
}

