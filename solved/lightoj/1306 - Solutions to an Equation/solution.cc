#include <algorithm>
#include <cstdio>

using namespace std;

long long gcd(long long a, long long b, long long &x, long long &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  long long x1, y1;
  long long d = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

bool find_any_solution(long long a, long long b, long long c, long long &x0,
                       long long &y0, long long &g) {
  g = gcd(abs(a), abs(b), x0, y0);
  if (c % g) {
    return false;
  }

  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}

void shift_solution(long long &x, long long &y, long long a, long long b,
                    long long cnt) {
  x += cnt * b;
  y -= cnt * a;
}

long long find_all_solutions(long long a, long long b, long long c,
                             long long minx, long long maxx, long long miny,
                             long long maxy) {
  long long x, y, g;
  if (!find_any_solution(a, b, c, x, y, g)) return 0;
  a /= g;
  b /= g;

  long long sign_a = a > 0 ? +1 : -1;
  long long sign_b = b > 0 ? +1 : -1;

  shift_solution(x, y, a, b, (minx - x) / b);
  if (x < minx) shift_solution(x, y, a, b, sign_b);
  if (x > maxx) return 0;
  long long lx1 = x;

  shift_solution(x, y, a, b, (maxx - x) / b);
  if (x > maxx) shift_solution(x, y, a, b, -sign_b);
  long long rx1 = x;

  shift_solution(x, y, a, b, -(miny - y) / a);
  if (y < miny) shift_solution(x, y, a, b, -sign_a);
  if (y > maxy) return 0;
  long long lx2 = x;

  shift_solution(x, y, a, b, -(maxy - y) / a);
  if (y > maxy) shift_solution(x, y, a, b, sign_a);
  long long rx2 = x;

  if (lx2 > rx2) swap(lx2, rx2);
  long long lx = max(lx1, lx2);
  long long rx = min(rx1, rx2);

  if (lx > rx) return 0;
  return (rx - lx) / abs(b) + 1;
}

long long solve() {
  long long a, b, c, x1, x2, y1, y2;
  scanf("%lld%lld%lld%lld%lld%lld%lld", &a, &b, &c, &x1, &x2, &y1, &y2);
  c *= -1;  // ax + by = c

  if (a == 0 && b == 0) {
    if (c == 0) return (x2 - x1 + 1) * (y2 - y1 + 1);
    return 0;
  }

  if (a == 0 || b == 0) {
    if (b == 0) {
      swap(a, b);
      swap(x1, y1);
      swap(x2, y2);
    }

    if (c % b) return 0;

    long long y = c / b;
    if (y >= y1 && y <= y2) return (x2 - x1 + 1);
    return 0;
  }

  return find_all_solutions(a, b, c, x1, x2, y1, y2);
}

int main() {
  int tc;
  scanf("%d", &tc);
  for (int i = 0; i < tc; i++) {
    printf("Case %d: %lld\n", i + 1, solve());
  }

  return 0;
}