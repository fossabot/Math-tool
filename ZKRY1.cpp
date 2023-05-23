#include "config.h"
#define prime_mod 10007 //prime used in cancer function, if needed use 1000003 instead

int primes[] = {
    2  ,3  ,5  ,7  ,11 ,13 ,17 ,19 ,23 ,29 ,31 ,37 ,
    41 ,43 ,47 ,53 ,59 ,61 ,67 ,71 ,73 ,79 ,83 ,89 ,
    97 ,101,103,107,109,113,127,131,137,139,149,151,
    157,163,167,173,179,181,191,193,197,199,211,223,
    227,229,233,239,241,251,257,263,269,271,277,281,
    283,293,307,311,313,317,331,337,347,349,353,359,
    367,373,379,383,389,397,401,409,419,421,431,433,
    439,443,449,457,461,463,467,479,487,491,499,503,
    509,521,523,541,547,557,563,569,571,577,587,593,
    599,601,607,613,617,619,631,641,643,647,653,659,
    661,673,677,683,691,701,709,719,727,733,739,743,
    751,757,761,769,773,787,797,809,811,821,823,827,
    829,839,853,857,859,863,877,881,883,887,907,911,
    919,929,937,941,947,953,967,971,977,983,991,997
}; //list of prime numbers (n < 1000)
int Velkost = sizeof(primes) / sizeof(int);

void kvadraticke_zvysky() {
    ZZ p;
    cout << "zadaj modulo p: ";
    cin >> p;
    ZZ_p::init(p);

    vec_ZZ_p list;
    list.SetMaxLength(1);

    for (int i = 1; i < (p + 1) / 2; i++) {
        ZZ_p tmp = to_ZZ_p(i * i);
        bool is = false;
        for (int j = 0; j < list.length(); j++)
            if (list[j] == tmp) is = true;
        if (!is) list.append(tmp);
    }
    cout << list << endl;
}

void Jakobi_symbol() {
    ZZ p, a;
    cout << "zadaj modulo p: ";
    cin >> p;
    cout << "zadaj value a: ";
    cin >> a;

    rem(a, a, p);
    cout << "pre value: " << a << " modulo: " << p << " je jakobiho symbol: " << Jacobi(a, p) << endl;
}

void kvadraticke_korene() {
    ZZ p, a, b;
    cout << "zadaj modulo p: ";
    cin >> p;
    ZZ_p::init(p);

    cout << "zadaj value a: ";
    cin >> a;

    vec_ZZ_p list;
    list.SetMaxLength(1);

    for (int i = 1; i < p; i++) {
        ZZ_p tmp = to_ZZ_p(i);
        ZZ_p res = tmp * tmp;
        bool is = false;
        if (rep(res) != a) continue;
        for (int j = 0; j < list.length(); j++)
            if (list[j] == tmp) is = true;
        if (!is) list.append(tmp);
    }
    cout << "Result bruteforce korenov: " << list << endl;

    if (Jacobi(a, p) == 1 && ProbPrime(p)) {
        SqrRootMod(b, a, p);
        cout << "Korene z NTL funkcie SqrRoot() z hodnoty: " << a << " modulo: " << p << " su: " << b << " a " << p - b << endl;
    }
}

// rules for Jacobi 
int flip(ZZ& p, ZZ& q) {
    int res = -1;
    int x = rem(p, 4);
    cout << "\np: " << p << " % 4 = " << x;

    if (x != 3) res = 1;
    x = rem(q, 4);
    cout << "\nq: " << q << " % 4 = " << x;

    if (x != 3) res = 1;
    ZZ tmp = p;
    rem(p, q, p);
    q = tmp;

    return res;
}

int two(ZZ p) {
    int tmp = rem(p, 8);
    cout << "\np: " << p << " % 8 = " << tmp;
    if (tmp == 1 || tmp == 7) return 1;
    if (tmp == 3 || tmp == 5) return -1;
    return 0;
}

int minus_one(ZZ p) {
    int tmp = rem(p, 4);
    cout << "\np: " << p << " % 4 = " << tmp;
    if (tmp == 1) return 1;
    if (tmp == 3) return -1;
    return 0;
}

void vypis_pravidlo(int& c, ZZ p, ZZ q, string s) {
    cout << endl << c++ << "...pre J(" << p << "/" << q << ") plati pravidlo " << s;
}

void vypis_medzivysledok(int tmp) {
    cout << "\nmedzivysledok je -> " << tmp << endl;
}

void vypis_vysledok_operacie(ZZ p, ZZ q) {
    cout << "vysledok operacie = J(" << p << "/" << q << ")" << endl;
}

//expected return is -1/0/1
int Jakobi_postup(ZZ p, ZZ q) {
    int res = 1, tmp = 1, c = 1;
    if (p > q) rem(p, p, q);

    while (1) {
        while (!rem(p, 2)) { // while number is even spin this

            if (p == q - 1) {
                vypis_pravidlo(c, p, q, "J(p-1/q)");
                tmp = minus_one(q);

                vypis_medzivysledok(tmp);
                if (tmp == 0)  return 0;

                res *= tmp;
                p = 1;

                vypis_vysledok_operacie(p, q);
                break;
            }

            vypis_pravidlo(c, p, q, "J(p/q) = (2/q) * ((p/2)/q)");
            tmp = two(q);

            vypis_medzivysledok(tmp);
            if (tmp == 0) return 0;

            res *= tmp;
            div(p, p, 2);

            vypis_vysledok_operacie(p, q);
        }

        if (p == 1) {
            vypis_pravidlo(c, p, q, "J(1/q)");
            tmp = 1;

            vypis_medzivysledok(tmp);
            return res;
        }

        vypis_pravidlo(c, p, q, "J(p/q) = J(q/p)");
        tmp = flip(p, q);

        vypis_medzivysledok(tmp);
        vypis_vysledok_operacie(p, q);

        if (p == 0) {
            vypis_pravidlo(c, p, q, "GCD(p,q) != 1");
            tmp = 0;

            vypis_medzivysledok(tmp);
            return 0;
        }

        res *= tmp;
    }
}

void Jakobi_postup() {
    cout << "Priklad na ratanie Jacobiho symbolu s postupom pre J(p/q):\n";
    ZZ p, q;
    cout << "zadaj p: ";
    cin >> p;
    cout << "zadaj q: ";
    cin >> q;

    cout << "\nVysledok pre J(" << p << "/" << q << ") = " << Jakobi_postup(p, q) << endl << endl;
}

void CRT() {
    ZZ A, M, B, N;
    napln_hodnoty(M, A, N, B);

    ZZ tmp, tmp2, mulmod;
    mulmod = M * N;

    ZZ invM, invN;
    tmp = M % N;
    InvMod(invN, tmp, N);

    tmp = N % M;
    InvMod(invM, tmp, M);

    tmp = A * invM * N;
    tmp2 = B * invN * M;

    cout << "mod1 * mod2: " << mulmod << endl
        << "inv prvok prva rovnica: " << invM << endl
        << "inv prvok druha rovnica: " << invN << endl
        << " prvok A( " << A << " ) * invMP( " << invM << " ) * "
        << " modulo NP( " << N << ") = " << tmp << endl
        << " prvok B( " << B << " ) * invNP( " << invN << " ) * "
        << " modulo MP( " << M << ") = " << tmp2 << endl;

    tmp += tmp2;
    tmp2 = tmp % mulmod;

    cout << "tieto vysledky teraz scitam a zmodulujem-> ( "
        << tmp << " ) % (" << mulmod << ") = "
        << tmp2 << " mod " << mulmod << endl;
}

vec_ZZ factorize_number(ZZ n) {
    vec_ZZ res;
    while (n != 1)
        for (int i = 0; i < Velkost; i++) {
            int prime = primes[i]; // could be replaced by actually calculating primes
            if (rem(n, prime) == 0) {
                div(n, n, prime);
                res.append(to_ZZ(prime));
                break;
            }
        }
    return res;
}

int cancer(vec_ZZ& list) {
    vec_ZZ res, count;
    ZZ max_power(1);
    int max_prime = primes[Velkost - 1];
    count.SetLength(max_prime + 1);

    for (int i = 0; i < list.length(); i++)
        count[to_long(list[i])]++;

    for (int i = 0; i <= max_prime; i++) {
        ZZ tmp = count[i];
        if (tmp > 0) res.append(PowerMod(to_ZZ(i), tmp, to_ZZ(prime_mod))); 
        if (tmp > max_power) max_power = tmp;
    }

    list = res;
    return to_long(max_power);
}

ZZ lambda(ZZ p) {
    ZZ res(1);

    for (ZZ i(1); i < p; i++) {
        int tmp = ord(i, p);
        if (tmp > res) res = tmp;
    }

    return res;
}

void vec_to_lambda(vec_ZZ& list) {
    vec_ZZ res;

    for (int i = 0; i < list.length(); i++)
        res.append(lambda(list[i]));

    list = res;
}

int phi(int p) {
    int res = 1;

    for (int i = 2; i < p; i++)
        if (GCD(i, p) == 1) res++;

    return res;
}

ZZ phi(ZZ p) {
    return to_ZZ(phi(to_long(p)));
}

bool is_done(vec_ZZ list) {
    for (int i = 0; i < list.length(); i++)
        if (list[i] != 1) return 0;

    return 1;
}

int lcm(vec_ZZ& list) {
    int res = 1;
    bool was_divided = false;
    while (!is_done(list))
        for (int i = 0; i < Velkost; i++) {
            int prime = primes[i]; // could be replaced by actually calculating primes
            for (int j = 0; j < list.length(); j++) {
                ZZ tmp = list[j];
                if (tmp == 1) continue;
                if (rem(tmp, prime) == 0) {
                    was_divided = true;
                    div(list[j], tmp, prime);
                }
            }
            if (was_divided) {
                was_divided = false;
                res *= prime;
                break;
            }
        }
    return res;
}

void simplify_formula() {
    ZZ p, n;
    cout << " zadaj modulo p: ";
    cin >> p;
    cout << " pre X^n zadaj n: ";
    cin >> n;

    vec_ZZ list = factorize_number(p);
    cout << " hodnota p( " << p << " ) rozlozena na prvociselne delitele : " << list << endl;

    int max_power = cancer(list);
    cout << " prvocisla zgrupene podla rovnakych do skupin: " << list << endl
        << " lambda( " << p << " ) = lcm( ";

    for (int i = 0; i < list.length(); i++) {
        cout << " lam( " << list[i] << " )";
        if (i != list.length() - 1) cout << ", ";
    }

    vec_to_lambda(list);

    cout << " ) = lcm( ";
    for (int i = 0; i < list.length(); i++) {
        cout << list[i];
        if (i != list.length() - 1) cout << ", ";
    }

    int tmp = lcm(list);
    cout << " ) = " << tmp << endl
        << " Vzorec na upravu teda vyzera takto: x^( " << max_power
        << " + " << tmp << " ) = x^( " << max_power << " ) mod " << p << endl
        << " takze originalny vyraz: x^ ( " << n << " ) modulo " << p;

    while (n > max_power)
        n -= tmp;
    n += tmp;
    cout << " je zjednoduseny na : x^ ( " << n << " ) mod " << p << endl;
}

void ideponent_list_mod_p() {
    int p;
    cout << "zadaj modulo p: ";
    cin >> p;

    vec_ZZ res;
    for (ZZ i(0); i < p; i++)
        if (rem(i * i, p) == i)
            res.append(i);
    cout << res << endl;
}

void Ax_plus_B_equals_C_mod_M() {
    //TODO
}

void (*ZKRY1[8])() = {kvadraticke_zvysky,
                      Jakobi_symbol,
                      kvadraticke_korene,
                      Jakobi_postup,
                      ideponent_list_mod_p,
                      CRT,
                      simplify_formula,
                      Ax_plus_B_equals_C_mod_M
};