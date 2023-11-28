

#include <iostream>
#include <fstream>
using namespace std;

struct data
{
    string date;
    float exchange;
};

void readfile(struct data arr[])
{
    string line;
    int n=6668;
    int c=0;
    ifstream in;
    in.open("/Users/mohamedazouz/CLionProjects/untitled/exchange.txt");
    if(in.is_open())
    {
        while(c<n&&in>>arr[c].date>>arr[c].exchange)
            c++;
    }else
        cout<<"File wasn't opened"<<endl;
    in.close();
}

void swap(struct data &x, struct data &y)
{
    struct data z = x; x = y; y = z;
}
void Max_Heapify(struct data arr[], int n, int i)
{
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < n && arr[left].exchange>arr[largest].exchange)
        largest = left;
    if(right < n && arr[right].exchange > arr[largest].exchange)
        largest = right;
    if(largest != i)
    {
        swap(arr[i],arr[largest]);
        Max_Heapify(arr,n,largest);
    }
}

void Min_Heapify(struct data arr[], int n, int i)
{
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < n && arr[left].exchange<arr[smallest].exchange)
        smallest = left;
    if(right < n && arr[right].exchange < arr[smallest].exchange)
        smallest = right;
    if(smallest != i)
    {
        swap(arr[i],arr[smallest]);
        Min_Heapify(arr,n,smallest);
    }
}

void Build_Max(struct data arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Max_Heapify(arr, n, i);

}

void Build_Min(struct data arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Min_Heapify(arr, n, i);

}

float max_subsequence(struct data arr[], int n, float mean, int &im, int &jm)
{
    for(int x = 0; x < n; x++){
        arr[x].exchange = arr[x].exchange - mean;
    }
    int i = 1;
    double Sij = 0;
    double Smax = 0;
    im = 0;
    jm = 0;
    for(int j = 1; j < n; j++){
        Sij = Sij + arr[j].exchange;
        if(Sij > Smax){
            Smax = Sij;
            im = i;
            jm = j;
        }
        else if (Sij < 0){
            i = j+1;
            Sij = 0;
        }
    }
    return Smax;
}

float getmean(struct data arr[],int n){
    float sum = 0;
    for(int i=0;i<n;i++){
        sum = sum + arr[i].exchange;
    }
    return sum/n;
}

void positiveval (struct data arr[], int n,float mean, struct data valarr[], int arrsi)
{
    Build_Max(arr,arrsi);
    int count = 0;
    for(int i=0;i<n;i++){
        if(arr[i].exchange-mean>0)
            valarr[count++] = arr[i];
    }
    Build_Max(valarr,count);
}

void negativeval(struct data arr[], int n, float mean, struct data valarr[], int arrsi)
{
    Build_Min(arr, arrsi);
    int count=0;
    for (int i = 0; i < n; i++) {
        if (arr[i].exchange - mean < 0)
            valarr[count++] = arr[i];
    }
    Build_Min(valarr,count);
}

int main() {
    int n = 6668, p;
    float mean;

    cout << "Please enter the amount of highest/ lowest exchange rates you want: " << endl;
    cin >> p;
    struct data arr[n];
    struct data arr2[n];
    struct data *pval;
    pval = new struct data[p];
    struct data *nval;
    nval = new struct data[p];
    readfile(arr);
    mean = getmean(arr,n);

    for(int i=0;i<n;i++)
    {
        arr2[i] = arr[i];
    }

    positiveval(arr, p, mean, pval,n);
    cout<<"The "<<p<<" positive exchange rates are: "<<endl;
    for(int i=0;i<p;i++)
    {
        cout<<"Date: "<<pval[i].date <<" Exchange rate (-mean): "<<pval[i].exchange-mean<<endl;
    }

    negativeval(arr, p, mean, nval,n);
    cout<<"The "<<p<<" negative exchange rates are: "<<endl;
    for(int i=0;i<p;i++)
    {
        cout<<"Date: "<<nval[i].date <<" Exchange rate (-mean): "<<nval[i].exchange-mean<<endl;
    }

    int im,jm;
    cout<<"The maximum subsequence is: "<<max_subsequence(arr2,n,mean,im,jm)<<" which occured from: "<<arr2[im].date<<" to "<<arr2[jm].date<<endl;

    delete[] nval;
    delete[]  pval;
}
