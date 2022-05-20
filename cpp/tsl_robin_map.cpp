#include <iostream>
#include <tsl/robin_map.h>
#include <bits/stdc++.h> // queue
#include <algorithm> // max

#include <quadmath.h>

using namespace std;

// From Rosetta Code

unsigned long int isqrt(unsigned long int x) {
  unsigned long int q = 1, r = 0;
  while (q <= x) {
    q <<= 2;
  }
  while (q > 1) {
    long int t;
    q >>= 2;
    t = x - r - q;
    r >>= 1;
    if (t >= 0) {
      x = t;
      r += q;
    }
  }
  return r;
}

unsigned int i,p;
unsigned long int m,n;

unsigned long int bound = 1000000000;
__float128 lb,x;

int main() {

  lb = logq(bound);

  tsl::robin_map<unsigned long int, unsigned long int> paths;
  paths[3] = 3;

  tsl::robin_map<unsigned long int, unsigned int> sqrts;
  sqrts[3] = 0;
  
  queue<unsigned long int> queue;
  queue.push(3);

  while (!queue.empty()) {

    m = queue.front();
    queue.pop();
    x = lgammaq(m+1.0Q);

    if (x <= lb ) {
      p = 0;
    } else {
      p = ceilq(log2q(x/lb));
    }
    
    i = p;

    if (p==0) {
      n = roundq(expq(x/powq(2,p)));
    } else {
      n = floorq(expq(x/powq(2,p)));
    }

    while (paths.find(n) == paths.end()) {
      queue.push(n);
      paths[n] = m;
      sqrts[n] = i;
      n = isqrt(n);
      i += 1;
    }
  }

  unsigned long int max_i = 1;

  while (paths.find(max_i) != paths.end()) {
    max_i += 1;
  }

  unsigned long int v;
  
  v = 1;
  while (v<max_i) {
    cout << v << "," << paths[v] << "," << sqrts[v] << endl;
    v += 1;
  }

  return 0;

}
