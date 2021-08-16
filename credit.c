#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)

{
    long credit;
    credit = get_long("Credit card number: ");

    long a = credit % 10;

    long b = (credit - a) % 100;

    long bb = b / 10 * 2;

    long bbb = bb % 10 + (bb / 10);

    long c = (credit - a - b) % 1000;

    long cc = c / 100;

    long d = (credit - a - b -c) % 10000;

    long dd = d / 1000 * 2;

    long ddd = dd % 10 + (dd / 10);

    long e = (credit - a - b - c - d) % 100000;

    long ee = e / 10000 ;

    long f = (credit - a - b - c - d - e) % 1000000;

    long ff = f / 100000 * 2;

    long fff = ff % 10 + (ff / 10);

    long g = (credit - a - b - c - d - e - f) % 10000000;

    long gg = g / 1000000;

    long h = (credit - a - b - c - d - e - f - g) % 100000000;

    long hh = h / 10000000 * 2;

    long hhh = hh % 10 + (hh / 10);

    long i = (credit - a - b - c - d - e - f - g - h) % 1000000000;

    long ii = i / 100000000;

    long j = (credit - a - b - c - d - e - f - g - h - i) % 10000000000;

    long jj = j / 1000000000 * 2;

    long jjj = jj % 10 + (jj / 10);

    long k = (credit - a - b - c - d - e - f - g - h - i - j) % 100000000000;

    long kk = k / 10000000000;

    long l = (credit - a - b - c - d - e - f - g - h - i - j - k) % 1000000000000;

    long ll = l / 100000000000 * 2;

    long lll = ll % 10 + (ll / 10);

    long m = (credit - a - b - c - d - e - f - g - h - i - j - k - l) % 10000000000000;

    long mm = m / 1000000000000;

    long n = (credit - a - b - c - d - e - f - g - h - i - j - k - l - m) % 100000000000000;

    long nn = n / 10000000000000 * 2;

    long nnn = nn % 10 + (nn / 10);

    long o = (credit - a - b - c - d - e - f - g - h - i - j - k - l - m - n) % 1000000000000000;

    long oo = o / 100000000000000;

    long p = (credit - a - b - c - d - e - f - g - h - i - j - k - l - m - n - o) % 10000000000000000;

    long pp = p / 1000000000000000 * 2;

    long ppp = pp % 10 + (pp / 10);

    long sec = bbb + ddd + fff + hhh + jjj + lll + nnn + ppp;

    long fir = a + cc + ee + gg + ii + kk + mm + oo;

    long total = (fir + sec) % 10;

    long ae = credit / 10000000000000;

    long mc = credit / 100000000000000;

    long visa1 = (credit / 1000000000000000) % 10;

    long visa2 = (credit / 1000000000000) % 10;

    if (total == 0)
    {
        if (ae == 34 || ae == 37)
        {
            printf("AMEX\n");
        }
        else if (mc > 50 && mc < 56)
        {
            printf("MASTERCARD\n");
        }
        else if (visa1 == 4 || visa2 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}