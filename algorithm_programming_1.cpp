#include<cstdio>
#include<algorithm>
#include<iostream>
#include<ctime>

int myrandom (int i) { return std::rand()%i;}

// FindIndexMin return an index of the smallest integer of a given interval [a,b]
int FindIndexMin(int *f, int from, int to){
    int min_idx = from;
    for(int i=from;i<=to;i++){
        if (f[i] < f[min_idx]){
            min_idx = i;
        }
    }
    return min_idx;
}

void Swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// b_sort receive array of integers of size n and sort the given array in
// an increasing order
void b_sort(int *f, int n){
    for(int i=0;i<n-1;i++){
        int min_idx = FindIndexMin(f, i, n-1);
        Swap(f+i, f+min_idx);
    }
}

// a_sort receive array of inegers of size n and sort the given array in
// an increasing order
void a_sort(int *f, int n){
    int *f_tmp = new int [n];
    for(int i=0;i<n;i++){
        f_tmp[i] = f[i];
    }
    int *idx = new int [n];
    bool pass;
    for(;;){
        pass = true;
        for(int i=0;i<n;i++){
            idx[i] = i;
        }
        std::random_shuffle(idx, idx+n, myrandom);
        for(int i=1;i<n;i++){
            if(f[idx[i]] < f[idx[i-1]]){
                pass = false;
                break;
            }
        }
        if (pass) {
            for(int i=0;i<n;i++){
                f[i] = f_tmp[idx[i]];
            }
            break;
        }
    }
    delete[] f_tmp;
    delete[] idx;
}

// show print the first n items of a given array f.
void show(int *f, int n){
    for(int i=0;i<n;i++){
        printf("%d ",f[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("input the number of the list: ");
    scanf("%d", &n);

    int *f1, *f2;
    f1 = new int[n];
    f2 = new int[n];
    printf("input numbers in the list: ");
    for(int i=0;i<n;i++){
        scanf("%d", &f1[i]);
        f2[i] = f1[i];
    }

    std::clock_t start;
    double duration;

    printf("--------------------------\n");
    printf("Using A's algorithm\n");
    // show(f1,n);

    start = std::clock();
    a_sort(f1, n);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    printf("the result is: ");
    show(f1,n);
    std::cout<<"Done: "<< duration <<" second\n";

    printf("--------------------------\n");
    printf("Using B's algorithm\n");
    // show(f2,n);

    start = std::clock();
    b_sort(f2, n);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    printf("the result is: ");
    show(f2,n);
    std::cout<<"Done: "<< duration <<" second\n";

    delete[] f1;
    delete[] f2;
}