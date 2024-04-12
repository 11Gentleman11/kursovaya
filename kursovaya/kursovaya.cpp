#include<iostream>
#include <fstream>
using namespace std;
class Tzadacha 
{
    int data[50][50]; 
    int nado[50];
    int volume[50];
    int rps[50][50];
    int no_of_rows, no_of_col, no_of_rps;
public:
    Tzadacha() 
    {
        for (int i = 0; i < 50; i++) 
        {
            volume[i] = 0;
            nado[i] = 0;
            for (int j = 0; j < 50; j++) {
                data[i][j] = 0;
                rps[i][j] = 0;
            }
        }
        no_of_rows = no_of_col = no_of_rps = 0;
    }
    
    void setCol(int no) { no_of_col = no; };
    void setRow(int no) { no_of_rows = no; }
    void getData();
    void getvolume();
    void getValue();
    void makerps();
    bool checkValue(int[], int);
    void vivod();
};
bool Tzadacha::checkValue(int arr[], int no) 
{
    for (int i = 0; i < no; i++)
        if (arr[i] != 0)
            return false;
    return true;
}
void arrayCopy(int start, int end, int array1[], int start1, int array2[]) 
{
    for (int i = start, j = start1; i < end; i++, j++) {
        array2[j] = array1[i];
    }
}
int getTotal(int array[], int no) {
    int sum = 0;
    for (int i = 0; i < no; i++)
        sum += array[i];
    return sum;
}
void Tzadacha::makerps() 
{
    int i = 0, j = 0;
    int vr_nado[50] = { 0 };
    int vr_volume[50] = { 0 };
    int sum_of_cap, sum_of_req;
    sum_of_cap = getTotal(volume, no_of_rows);
    sum_of_req = getTotal(nado, no_of_col);
    if (sum_of_cap != sum_of_req) {
        if (sum_of_cap > sum_of_req) {
            for (j = 0; j < no_of_rows; j++)
                data[j][no_of_col] = 0;
            nado[no_of_col] = sum_of_cap - sum_of_req;
            no_of_col++;
        }
        else {
            for (j = 0; j < no_of_col; j++)
                data[no_of_rows][j] = 0;
            volume[no_of_rows] = sum_of_req - sum_of_cap;
            no_of_rows++;
        }
    }
    i = j = 0;
    arrayCopy(0, no_of_rows, volume, 0, vr_volume);
    arrayCopy(0, no_of_col, nado, 0, vr_nado);
    while (!checkValue(vr_volume, no_of_rows) || !checkValue(vr_nado, no_of_col)) 
    {
        if (vr_volume[i] > vr_nado[j]) 
        {
            rps[i][j] = vr_nado[j];
            vr_volume[i] -= vr_nado[j];
            vr_nado[j] = 0;
            j++;
        }

       
        else if (vr_volume[i] < vr_nado[j]) 
        {
            rps[i][j] = vr_volume[i];
            vr_nado[j] -= vr_volume[i];
            vr_volume[i] = 0;
            i++;
        }
        else 
        {
            rps[i][j] = vr_volume[i];
            vr_volume[i] = vr_nado[j] = 0;
            i++;
            j++;
        }
        no_of_rps++;
    }
}
void Tzadacha::getvolume()
{
    volume[0] = 220;
    volume[1] = 160;
    volume[2] = 80;
    
}
void Tzadacha::getValue() 
{
    nado[0]=  120;
    nado[1] = 80;
    nado[2] = 60;
    nado[3] = 100;
    nado[4] = 100;
}
void Tzadacha::vivod() 
{
    int i;
   
   
    int k = 0, sum = 0;
    for (i = 0; i < no_of_rows; i++) 
    {
        for (int j = 0; j < no_of_col; j++) 
        {
            if (rps[i][j] != 0) {
                cout << "(" << data[i][j] << "*" << rps[i][j] << ")";
                if (k < no_of_rps - 1) {
                    cout << "+";
                    k++;
                }
                sum += data[i][j] * rps[i][j];
              
            }
        }
    }
    cout << "\nОпорное решение = " << sum ;
}
void Tzadacha::getData() 
{
    fstream fin("paths.txt");
    int a;
    for (int i = 0; i < no_of_rows; i++) 
    {
        
        for (int j = 0; j < no_of_col; j++) 
        {
            fin >> a;
            data[i][j]=a;
        }
    }
}


void main() 
{
    setlocale(LC_ALL, "Rus");
    Tzadacha m1;
    int r=3, c=5;
   

    m1.setCol(c);
    m1.setRow(r);

    m1.getData();
    m1.getvolume();
    m1.getValue();
    m1.makerps();
    m1.vivod();

   
}