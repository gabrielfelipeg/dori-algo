#include <bits/stdc++.h>

using namespace std;

typedef struct letra{
    long long id;
    char letraq;
}letra;

bool cmp(letra a, letra b){
    return a.id < b.id;
}

long long multi(long long a, long long b, long long m){
    return ((a%m) * (b%m))%m;
}

pair<long long, long long> extended_gcd(long long a, long long b) {
    if (!b) return {1, 0};
    pair<long long, long long> t = extended_gcd(b, a % b);
    return {t.second, t.first - t.second * (a / b)};
}

long long modinverse(long long a, long long m) {
    return (extended_gcd(a, m).first % m + m) % m;
}

int main(){
    string s, query[3];
    cin >> s;
    long long coprimes[3] = {26, 25, 23};
    long long modulo = coprimes[0] * coprimes[1] * coprimes[2];
    for(long long i = 0; i < 3; i++){
        string temp = "";
        for(long long j = 0; j < s.size(); j++){
            temp += 'a' + (j % coprimes[i]);
        }
        cout << "? " << temp << endl;
        cin >> query[i];
    }
    long long demask[s.size()];
    for(long long i = 0; i < s.size(); i++){
        demask[i] = 0;
        for(long long j = 0; j < 3; j++){
            demask[i] += (query[j][i] - 'a') * (modulo / coprimes[j]) * modinverse(modulo / coprimes[j], coprimes[j]);
            // SUM j = 0..N [value[i] * M/FACTOR(J) * (M/FACTOR(J))^-1] inverso modular em modulo do coprimo
        }
        demask[i] %= modulo;
    }
    letra letras[s.size()];
    for(long long i = 0; i < s.size(); i++){
        letras[i].id = demask[i];
        letras[i].letraq = s[i];
    }
    sort(letras, letras + s.size(), cmp);
    cout <<  "! " ;
    for(long long i = 0; i < s.size(); i++){
        cout << letras[i].letraq;
    }
    cout << endl;
    return 0;
}