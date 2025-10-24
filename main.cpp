#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Step {
    int step = -1;
    vector<int> numberUnderStep;
};

int main()
{
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        const auto arr = new int[n];
        for(int i=0;i<n;i++)
            cin>>arr[i];
        int min = INT_MAX;
        int max = INT_MIN;
        sort(arr, arr+n);
        vector<int> step;
        for(int i=0;i<n;i++) {
            if (arr[i] < min) min = arr[i];
            if (arr[i] > max) max = arr[i];

            if (step.back() != arr[i]) step.push_back(arr[i]);
        }
        delete arr;
    }

    return 0;
}