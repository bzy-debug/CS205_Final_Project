#include<iostream>
using namespace std;

inline int index(int i, int j, int k, int channel, int row, int col)
{
    return k*row*col+i*col+j;
}

float* conv(int in_channels, int out_channels, float* p_weight, float* p_bias, float* input, int in_row, int in_col);
int main()
{
    float* input = new float[10*10*3];
    for (int i=0; i<10*10*3; i++)
        input[i] = i%8;
    float kernel[27] = {-1, -1, 1, 0, 1, -1, 0, 1, 1, 1, 0, 0, 1, -1, -1, 1, 0, -1, 0, 1, 1, 0, 1, 0, 1, -1, 1};
    float bias = 1;
    for (int k=0; k<3; k++)
    {
        for (int i=0; i<10; i++)
        {
            for (int j=0; j<10; j++)
                cout << input[index(i,j,k,3,10,10)]<<' ';
            cout << endl;
        }
        cout << endl;
    }
    float* output = conv(3,1,kernel,&bias,input,10,10);
    for (int k=0; k<1; k++)
    {
        for (int i=0; i<8; i++)
        {
            for (int j=0; j<8; j++)
                cout << input[index(i,j,k,1,8,8)]<<' ';
            cout << endl;
        }
        cout << endl;
    }

}

float* conv(int in_channels, int out_channels, float* p_weight, float* p_bias, float* input, int in_row, int in_col)
{
    float* output;
    int out_row, out_col;
    out_row = in_row - 2;
    out_col = in_col - 2;
    output = new float[out_channels*out_row*out_col];

    for (int l=0; l<out_channels; l++)
    {
        float* kernel = p_weight + l*in_channels*3*3;
        float bias = p_bias [l];
        int rowi = 0, colj = 0;
        while (rowi <= in_row - 3)
        {
            float sum = 0;
            for (int k=0; k<in_channels; k++)
                for (int i=0; i<3; i++)
                    for (int j=0; j<3; j++)
                    { 
                        sum += input[index(rowi+i,colj+j,k,in_channels,in_row,in_col)] * kernel[index(i,j,k,in_channels,3,3)];
                    }
            printf("rowi = %d, colj = %d\n", rowi, colj);



            sum += bias;
            if (sum < 0)
                sum = 0;
            output[index(rowi, colj, l, out_channels, out_row, out_col)] = sum;
            colj ++;
            if (colj > in_col - 3)
            {
                colj = 0;
                rowi ++;
            }
        }
    }
    return output;
}