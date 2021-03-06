#include<bits/stdc++.h>
using namespace std;


long long int mergeq(long long a[],long long tmp[],int l,int mid,int r){
    long long count=0;
    int i=l;
    int k=l;
    int j=mid;
    while(i<=mid-1 && j<=r){
        if(a[i]<=a[j]){
            tmp[k]=a[i];
            k++;
            i++;
        }
        else{
            tmp[k]=a[j];
            k++;
            j++;
            count +=mid-i;
        }
    }
    while(i<=mid-1){
        tmp[k++]=a[i++];
    }
    while(j<=r){
        tmp[k++]=a[j++];
    }
    for(int i=l;i<=r;i++){
        a[i]=tmp[i];
    }
    return count;
}

long long int merges(long long a[],long long tmp[],int l,int r){
    long long mid,count=0;
    if(l<r){
        mid=(l+r)/2;
        count+= merges(a,tmp,l,mid);
        count+= merges(a,tmp,mid+1,r);
        count+= mergeq(a,tmp,l,mid+1,r);
    }
    return count;
}

long long int inversionCount(long long arr[], long long n)//count the number swap needed in order to make array sorted
{//implemented using merge sort
    long long tmp[n];
    return merges(arr,tmp,0,n-1);
}



 void merge(int arr[], int l, int mid, int r)
    {
        int n= r-l+1;
         int tmp[n];
         int i=l;
         int j=0;
         int k=mid;
         while(i<=mid-1 && k<=r){
             if(arr[i]<=arr[k]){
                 tmp[j++]=arr[i++];
             }
             else{
                 tmp[j++]=arr[k++];
             }
         }
         while(i<=mid-1){
             tmp[j++]=arr[i++];
         }
         while(k<=r){
             tmp[j++]=arr[k++];
         }
         for(int i=l;i<=r;i++){
             arr[i]=tmp[i-l];
         }
    }
    void mergeSort(int arr[], int l, int r)//merge sort implementation
    {
        if(l<r){
            int mid=(l+r)/2;
            mergeSort(arr,l,mid);
            mergeSort(arr,mid+1,r);
            
            merge(arr,l,mid+1,r);
        }
        
    }

int main(){
return 0;
}
