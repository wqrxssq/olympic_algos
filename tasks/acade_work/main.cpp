#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
void trim(vector<ll>& poly){
    while(poly.size()>1 && poly.back()==0) poly.pop_back();
}
vector<ll> conv(const vector<ll>& a, const vector<ll>& b){
    vector<ll> res(a.size()+b.size()-1,0);
    for(size_t i=0;i<a.size();i++)
        for(size_t j=0;j<b.size();j++)
            res[i+j]+=a[i]*b[j];
    return res;
}
vector<ll> poly_add(const vector<ll>& a, const vector<ll>& b){
    size_t n=max(a.size(),b.size());
    vector<ll> res(n,0);
    for(size_t i=0;i<n;i++){
        ll A=i<a.size()?a[i]:0;
        ll B=i<b.size()?b[i]:0;
        res[i]=A+B;
    }
    trim(res);
    return res;
}
vector<ll> poly_sub(const vector<ll>& a, const vector<ll>& b){
    size_t n=max(a.size(),b.size());
    vector<ll> res(n,0);
    for(size_t i=0;i<n;i++){
        ll A=i<a.size()?a[i]:0;
        ll B=i<b.size()?b[i]:0;
        res[i]=A-B;
    }
    trim(res);
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<ll> s;
    if(getline(cin,line)){
        istringstream iss(line);
        ll num;
        while(iss >> num) s.push_back(num);
    }
    int k = s.size();
    ll C;
    vector<ll> lam;
    if(getline(cin,line)){
        istringstream iss(line);
        iss >> C;
        for (int i = 0; i < k; i++){
            ll t;
            iss >> t;
            lam.push_back(t);
        }
    }
    if(k==0){
        vector<ll> P = {C};
        vector<ll> Q = {1, -1};
        trim(P);
        trim(Q);
        for(auto x : P) cout << x << " ";
        cout << "\n";
        for(auto x : Q) cout << x << " ";
        cout << "\n";
        return 0;
    }
    vector<ll> A(k,0);
    for (int i=0;i<k;i++){
        A[i]= s[i];
    }
    vector<ll> U(k,0);
    for (int i=0;i<k;i++){
        for (int j=0;j<i;j++){
            int idx=(k-i)+j;
            if(idx>=U.size()) U.resize(idx+1,0);
            U[idx]+=lam[i]*s[j];
        }
    }
    while(A.size()<U.size()) A.push_back(0);
    vector<ll> Aprime=poly_sub(A,U);
    vector<ll> one_minus_x = {1, -1};
    vector<ll> P_full = conv(one_minus_x, Aprime);
    if(P_full.size()<= (size_t)k) P_full.resize(k+1,0);
    P_full[k]+= C;
    vector<ll> T(k+1,0);
    T[0]=0;
    for (int d=1; d<=k; d++){
        T[d]= lam[k-d];
    }
    vector<ll> L(T.size(),0);
    L[0]=1;
    for(size_t i=1;i<T.size();i++){
        L[i] = -T[i];
    }
    vector<ll> Q_full = conv(one_minus_x, L);
    vector<ll> P_final = P_full, Q_final = Q_full;
    if(Q_final[0]>0){
        for(auto &x:P_final) x=-x;
        for(auto &x:Q_final) x=-x;
    }
    trim(P_final);
    trim(Q_final);
    for(auto x:P_final) cout<<x<<" ";
    cout<<"\n";
    for(auto x:Q_final) cout<<x<<" ";
    cout<<"\n";
    return 0;
}
