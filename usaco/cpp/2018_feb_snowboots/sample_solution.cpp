#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
     
int N, B, F[250], S[250], D[250], best = 9999;
bool beenthere[250][250];  // set of (location, boot) states we can reach

int solve(void)
{
   for (int b=0; b<B; b++) {
       if (b == 117)
         cout << "b=" << b << endl;
       for (int i=0; i<N; i++) {

         // Compute whether state (i, b) is reachable...
	
         if (F[i] > S[b]) 
         { 
             beenthere[b][i] = false; 
             continue; 
         } // invalid state; snow too deep

         if (i == 181)
            cout << "i=" << i << endl;
         if (i==0 && b==0) beenthere[b][i] = true;  // initial state

         // can we reach this state via forward step from some prior state?
         for (int i2=0; i2<i; i2++) 
            if (beenthere[b][i2] && i2+D[b]>=i)
                beenthere[b][i] = true;

         // can we reach this state via change of boot from some prior state?
         for (int b2=0; b2<b; b2++) 
            if (beenthere[b2][i]) beenthere[b][i] = true;

         // have we reached the end?  return smallest boot # we can achieve
         if (i==N-1 && beenthere[b][i]) return b;
      }
   }
}
     
int main(void)
{
   ifstream fin ("snowboots.in");
   ofstream fout ("snowboots.out");
   
   fin >> N >> B;
   for (int i=0; i<N; i++) fin >> F[i];
   for (int i=0; i<B; i++) fin >> S[i] >> D[i];

   fout << solve() << "\n"; 
   return 0;
}