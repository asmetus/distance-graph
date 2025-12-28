#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <cmath>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution <long double> uni(0, 1);
exponential_distribution <long double> expon(1);
normal_distribution <long double> norm(0, 1);

void gen_uni(vector <long double> &a){
    for(int j=0;j<a.size();j++){
        a[j] = uni(rng);
    }
    sort(a.begin(), a.end());
}

void gen_exp_log(vector <long double> &a){
    for(int j=0;j<a.size();j++){
        a[j] = -logl(uni(rng));
    }
    sort(a.begin(), a.end());
}

void gen_exp(vector <long double> &a){
    for(int j=0;j<a.size();j++){
        a[j] = expon(rng);
    }
    sort(a.begin(), a.end());
}

void gen_norm(vector <long double> &a){
    for(int j=0;j<a.size();j++){
        a[j] = norm(rng);
    }
    sort(a.begin(), a.end());
}

long double choose(long double n, long double k){
    if(k > n)   return 0;
    long long result = 1;
    for(long long i=n-k+1;i<=n;i++)   result*=i;
    for(long long i=1;i<=k;i++)       result/=i;
    return result;
}

long long reps = 10;
long long N = 1000;
long double delta = 1e-3;
long long distrib = 0;
long long type = 0;
long long param = 3;
ofstream out("result.txt");

int main(int argc, char* argv[]){
    cout.precision(30);
    if(argc > 1){
        N = stod(argv[1]);
        delta = stod(argv[2]);
        reps = stod(argv[3]);

        if(argv[4] == "uni")    distrib = 0;
        if(argv[4] == "exp")    distrib = 1;
        if(argv[4] == "norm")   distrib = 2;

        if(argv[5] == "click")  type = 0;
        if(argv[5] == "concomp")type = 1;
        if(argv[5] == "else")   type = 2;

        param = stod(argv[6]);
    }
    vector <long double> results(reps);
    vector <long double> numbers(N);
    long long step = reps/100;
    for(long long t=0;t<=reps;t++){
        if(t%step == 0) cout << t/step << endl;
        switch (distrib){
            case 2:
                gen_norm(numbers);
                break;
            case 1:
                gen_exp(numbers);
                break;
            case 0:
                gen_uni(numbers);
                break;
        }
        long double res = 0;
        long long j = 0;
        switch (type){
            case 0:
                for(long long i=0;i<numbers.size();i++){
                    while(j < numbers.size() - 1 && numbers[j+1]*1.0 <= numbers[i] + delta)   j++;
                    res += choose(j-i, param - 1);
                }
                break;
            case 1:
                for(long long i=0;i<numbers.size();i++){
                    while(j < numbers.size() - 1 && numbers[j+1]*1.0 <= numbers[i] + delta)   j++;
                    res += 1;
                    i = j;
                }
                break;
            case 2:
                
                break;
        }
        results[t] = res;
    }
    long long x = 0;
    for(int i=0;i<reps;i++){
        if(results[i] > 10000 && results[i] < 1e18){
            x = results[i];
            out << x << ' ';
        }else   out << results[i] << ' ';
    }
}
