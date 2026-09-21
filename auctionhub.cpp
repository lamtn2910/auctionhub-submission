#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

struct Bid {
    string bidderId;
    double amount;      
    long long timestamp; 
    int auctionId;
};
void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i) cout << "[" << v[i].bidderId << "] $" << v[i].amount<< " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}
void insertionSort(vector<Bid>& v)
{
    for (int i = 0;i < v.size();i++)
    {
        Bid key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j].amount > key.amount)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}
void selectionSort(vector<Bid>& v)
{
    for (int i = 0;i < v.size()-1;i++)
    {
        int maxidx = i;
        for (int j = i + 1;j < v.size();j++)
        {
            if (v[j].amount > v[maxidx].amount) maxidx = j;
        }
        if (maxidx != i)
        {
            Bid tmp = v[i];
            v[i] = v[maxidx];
            v[maxidx] = tmp;
        }
    }
}
void interchangeSort(vector<Bid>& v, long long& swaps)
{
    swaps = 0;
    for (int i = 0;i < v.size() - 1;i++)
    {
        for (int j = i + 1;j < v.size();j++)
        {
            if (v[i].amount > v[j].amount)
            {
                Bid tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
                swaps++;
            }
        }
    }
    cout << swaps << endl;
}
bool bubbleSortEarlyStop(vector<Bid>& v, bool isSwapped)
{
    isSwapped = false;
    for (int i = 0;i < v.size()-1;i++)
    {
        for (int j = 0;j < v.size() - i - 1;j++)
        {
            if (v[j].amount > v[j+1].amount)
            {
                Bid tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
                isSwapped = true;
            }
        }
    }
    if (isSwapped) return false;
    else return true;
}
int partition(vector<Bid>& v, int lo, int hi) 
{
    int mid = lo + (hi - lo) / 2;
    // Sắp xếp 3 phần tử đầu (lo), giữa (mid), và cuối (hi) theo thứ tự tăng dần
    if (v[mid].amount < v[lo].amount || (v[mid].amount == v[lo].amount && v[mid].timestamp < v[lo].timestamp)) swap(v[lo], v[mid]);
    if (v[hi].amount < v[lo].amount || (v[hi].amount == v[lo].amount && v[hi].timestamp < v[lo].timestamp)) swap(v[lo], v[hi]);
    if (v[hi].amount < v[mid].amount || (v[hi].amount == v[mid].amount && v[hi].timestamp < v[mid].timestamp)) swap(v[mid], v[hi]);
    // Sau khi hoán đổi v[mid] đang là trung vị
    // Đưa trung vị xuống cuối để làm pivot
    swap(v[mid], v[hi]);
    Bid pivot = v[hi];
    int i = lo - 1;
    // Sắp xếp các phần tử nhỏ hơn nằm bên trái pivot,các phần tử lớn hơn nằm bên phải
    for (int j = lo; j < hi; j++) 
    {
        if (v[j].amount < pivot.amount || (v[j].amount == pivot.amount && v[j].timestamp <= pivot.timestamp)) 
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[hi]);
    return i + 1;
}
void quickSort(vector<Bid>& v, int lo, int hi) 
{
    if (lo < hi) {
        int pi = partition(v, lo, hi);
        quickSort(v, lo, pi - 1);
        quickSort(v, pi + 1, hi);
    }
}
void quickSortWrapper(vector<Bid>& v)
{
    if (v.empty()) return;
    auto start = high_resolution_clock::now();
    quickSort(v, 0, v.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << " milliseconds." << endl;
}

int main()
{
    
}
