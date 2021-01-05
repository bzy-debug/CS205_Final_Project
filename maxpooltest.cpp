#include<iostream>
using namespace std;

inline int index(int i, int j, int k, int channel, int row, int col)
{
    return k*row*col+i*col+j;
}

float* maxpool (float* input, int in_channels, int in_row, int in_col)
{
    int out_channels = in_channels, out_row = in_row/2, out_col = in_col/2;

    float* output = new float[out_channels * out_row * out_col];

    for (int k=0; k<out_channels; k++)
    {
        int rowi = 0, colj = 0;
        while(rowi < in_row)
        {
            float max = 0;
            for (int i=0; i<2; i++)
                for (int j=0; j<2; j++)
                {
                    float x = input[index(rowi+i,colj+j,k,in_channels, in_row, in_col)];
                    max = max < x ? x : max;
                }
            output[index(rowi/2, colj/2, k, out_channels, out_row, out_col)] = max;
            colj += 2;
            if (colj > in_col)
            {
                colj = 0;
                rowi += 2;
            }
        }
    }
    return output;
}

int main()
{

}