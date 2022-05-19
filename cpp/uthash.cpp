#include <iostream>
#include <bits/stdc++.h> // queue
#include <algorithm> // max

#include <quadmath.h>

#include <uthash.h>

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

typedef struct triplet {
  unsigned long int key;
  unsigned long int next;
  unsigned int sqrts;
  UT_hash_handle hh;
}striplet;

striplet *paths = NULL;

void add_triplet(striplet **dict, unsigned long int id, unsigned long int n, unsigned int sr) {
  
  striplet *s;
  HASH_FIND_ULINT(*dict, &id, s);
  if (s == NULL) {
    s = (striplet*)malloc(sizeof *s);
    s->key = id;
    s->next = n;
    s->sqrts = sr;
    HASH_ADD_ULINT(*dict, key, s);
  }
  
}

unsigned int i,p;
unsigned long int m,n;

unsigned long int bound = 1000000000;
__float128 lb,x;

int main() {

  lb = logq(bound);

  striplet *s;
  s = (striplet*)malloc(sizeof *s);

  add_triplet(&paths, 3, 3, 0);

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

    HASH_FIND_ULINT(paths, &n, s);
      
    while (s == NULL) {
      queue.push(n);

      add_triplet(&paths, n, m, i);

      n = isqrt(n);
      i += 1;
      HASH_FIND_ULINT(paths, &n, s);
    }
  }

  unsigned long int max_i = 1;
  HASH_FIND_ULINT(paths, &max_i, s);
  while (s != NULL) {
    max_i += 1;
    HASH_FIND_ULINT(paths, &max_i, s);
  }

  unsigned long int v;
  
  v = 1;
  while (v<max_i) {
    HASH_FIND_ULINT(paths, &v, s);
    cout << v << "," << s->next << "," << s->sqrts << endl;
    v += 1;
  }

  return 0;

}
