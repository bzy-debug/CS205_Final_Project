#include<iostream>
using namespace std;
inline int index(int i, int j, int k, int channel, int row, int col)
{
    return k*row*col+i*col+j;
}

float* padding(float* input,int in_channels, int in_row, int in_col);

int main()
{
    int in_channels = 3;
    int in_row = 7;
    int in_col = 7;
    float test[in_channels * in_row * in_col];
    for (int i=0; i<in_channels * in_row * in_col; i++)
        test[i] = i%10;
    for (int k=0; k<in_channels; k++)
    {
        for (int i=0; i<in_row; i++)
        {
            for (int j=0; j<in_col; j++)
                cout << test[index(i,j,k,in_channels,in_row,in_col)] << ' ';
            cout << endl;
        }
        cout << endl;
    }
    float* testpad = padding(test, in_channels, in_row, in_col);
    for (int k=0; k<in_channels; k++)
    {
        for (int i=0; i<in_row+2; i++)
        {
            for (int j=0; j<in_col+2; j++)
                cout << testpad[index(i,j,k,in_channels,in_row+2,in_col+2)] << ' ';
            cout << endl;
        }
        cout << endl;
    }
}

float* padding(float* input, int in_channels, int in_row, int in_col)
{
    int row = in_row + 2;
    int col = in_col + 2;
    int channel = in_channels;
    float* output = new float[row*col*channel];
    for (int k=0; k<channel; k++)
        for (int i=0; i<row; i++)
            for (int j=0; j<col; j++)
            {
                if (i==0 || i== row-1 || j==0 || j == col-1)
                    output[index(i,j,k,channel,row,col)] = 0;
                else
                    output[index(i,j,k,channel,row,col)] = input[index(i-1, j-1,k,in_channels, in_row, in_col)];
            }
    return output;
}