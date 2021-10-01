/*
PROG: shopping
LANG: C++
*/

#include "bits/stdc++.h"
#include <math.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<string> vs;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef set<int> si;
typedef map<string, int> msi;
typedef map<int, int> mii;
#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a))

struct Offer {
    mii product_offer_details;
    int price;
};

int valid_offer(vi &numbers, mii& product_index, vi &new_numbers, Offer &offer) {
    new_numbers = numbers;
    for (auto prod: offer.product_offer_details) {
        if (product_index.find(prod.first) != product_index.end() && prod.second <= numbers[product_index[prod.first]])
            new_numbers[product_index[prod.first]] = numbers[product_index[prod.first]] - prod.second;
        else
            return 0;
    }

    return offer.price;
}

int recursive(vi numbers, mii& product_index, vi &costs, vector<Offer> &offers, int *memo) {
    if (all_of(numbers.begin(), numbers.end(), [](int elem){ return elem == 0;}))
        return 0;

    ll mykey = 0;
    for(auto num: numbers) {
        mykey *= 6;
        mykey += num;
    }

    if (memo[mykey])
        return memo[mykey];

    int result = INT_MAX;
    bool offer_applied = false;
    FOR(i, 0, offers.size()) {
        vi new_numbers;
        int cost = valid_offer(numbers, product_index, new_numbers, offers[i]);
        if (cost != 0) {
            result = min(result, cost + recursive(new_numbers, product_index, costs, offers, memo));
            offer_applied = true;
        }
    }
    if (!offer_applied) {
        if (result == INT_MAX)
            result = 0;
        for (int i = 0; i < numbers.size(); i++) {
            if (numbers[i])
                result += costs[i] * numbers[i];
        }
    }

    memo[mykey] = result;

    return result;
}

int main() {
    ofstream fout("shopping.out");
    ifstream fin("shopping.in");
    int s;
    fin >> s;
    vector<Offer> offers(s);
    FOR(i, 0, s)
    {
        int n;
        fin >> n;
        FOR(j, 0, n)
        {
            int c, k;
            fin >> c >> k;
            offers[i].product_offer_details[c] = k;
        }
        fin >> offers[i].price;
    }
    int b;
    fin >> b;
    mii product_index;
    int ind = 0;
    vi product_counts(b);
    vi product_costs(b);
    FOR(i, 0, b)
    {
        int c, k, p;
        fin >> c >> k >> p;
        product_index[c] = ind;
        product_counts[ind] = k;
        product_costs[ind] = p;
        ind++;
    }

    int memo[6*6*6*6*6];
    memset(memo, 0, sizeof(memo));

    fout << recursive(product_counts, product_index, product_costs, offers, memo) << endl;
    return 0;
}