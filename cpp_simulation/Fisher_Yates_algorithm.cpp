#include<bits/stdc++.h>

using namespace std;
int main() {
   int n;
   srand(2020);
   cout << "Enter the array size: "<<endl;
   cin >> n;

   int arr[n], arr1[n], index_arr[n];  //index_arr :記錄哪個元素使用 arr[i]舊的陣列  arr1[i]新的陣列
   int index;
   cout << "Enter the array elements: "<<endl;
   for (int i = 0; i < n; i++)
    arr[i]=i+2;

    for(int x=0;x<10;x++)
    {
        for (int i = 0; i < n; i++)
        index_arr[i] = 0;

        for (int i = 0; i < n; i++)
        {
            do {
                index = rand() % n;

            }
            while (index_arr[index] != 0);

            index_arr[index] = 1;
            arr1[i] = arr[index];
            /*for (int i = 0; i < n; i++) cout << index_arr[i] << " ";
            cout <<endl;*/
        }
        cout<<"The shuffled array is: ";
        for (int i = 0; i < n; i++)
        {
                cout << arr1[i] << " ";
        }
        cout<< endl;
    }

   system("pause");
   return 0;
}