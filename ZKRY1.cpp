#include "funkcie.h"
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
    cout << "\ncislo p: " << p << " % 4 = " << x;
    if (x != 3) res = 1;

    x = rem(q, 4);
    cout << "\ncislo q: " << q << " % 4 = " << x;
    if (x != 3) res = 1;

    ZZ tmp = p;
    rem(p, q, p);
    q = tmp;

    return res;
}

int two(ZZ p) {
    int tmp = rem(p, 8);
    cout << "\nhodnota pre cislo p: " << p << " % 8 = " << tmp;
    if (tmp == 1 || tmp == 7) return 1;
    if (tmp == 3 || tmp == 5) return -1;
    return 0;
}

int minus_one(ZZ p) {
    int tmp = rem(p, 4);
    cout << "\nhodnota pre cislo p: " << p << " % 4 = " << tmp;
    if (tmp == 1) return 1;
    if (tmp == 3) return -1;
    return 0;
}

_Check_return_ int _cdecl Jakobi_postup(ZZ a, ZZ p) {
    int res = 1, tmp = 1, counter = 1;
    if (a > p) rem(a, a, p);

    while (1) {
        while (!rem(a, 2)) { // if number is even do this
            if (a == p - 1) {
                cout << endl << counter++ << "...pre J(" << a << "/" << p << ") plati a = p - 1, takze sa da pouzit pravidlo J(p - 1/p)\n";
                tmp = minus_one(p); // rule J(p-1/p)
                cout << " je -> " << tmp << endl;
                if (tmp == 0) { cout << "hodnota je 0, zly vstup\n"; return 0; } 

                res *= tmp;
                a = 1;
                break;
            }
            cout << endl << counter++ << "...pre J(" << a << "/" << p << ") plati ze a = 2*k " << " takze J(" << a << "/" << p << ") rozdelim na (2/" << p << " * " << a / 2 << "/" << p << ").\n na (2/" << p << ") pouzijem pravidlo J(2/p)\n";
            tmp = two(p); //rule J(2/p)
            cout << " je -> " << tmp << endl;
            if (tmp == 0) { cout << "hodnota je 0, zly vstup\n"; return 0; } 

            res *= tmp;
            div(a, a, 2);
        }
        if (a == 1) { cout << endl << counter++ << "...pre J(" << a << "/" << p << ") plati a = 1,\n takze sa da pouzit pravidlo J(1/p)\nhodnota je -> 1\n"; break; } //rule J(1/p)

        cout << endl << counter++ << "...pre J(" << a << "/" << p << ") plati ze oboje su neparne cisla, takze sa da pouzit pravidlo J(p/q) = J(q/p)\n";
        tmp = flip(a, p); //rule J(p/q)= J(q/p), inside of flip another rule gets enforced: if a=b mod p, then J(a/p) = J(b/p) 
        cout << "\n hodnota pre otocenie teda je -> " << tmp << endl << endl << counter++ << "...po vymene hodnot mozme uplatnit hned pravidlo, ak a=b mod p, tak J(a/p) = J(b/p)\n Dalej teda pokracujeme s J(" << a << "/" << p << ")\n";
        if (a == 0) { cout << "GCD(a,p)!=1, takze hodnota je -> 0\n"; return 0; }

        res *= tmp;
    }
    return res;//expected return is 1/-1, error return is 0
}

void Jakobi_postup() {
    ZZ p, a;
    cout << "zadaj modulo p: ";
    cin >> p;
    cout << "zadaj value a: ";
    cin >> a;

    cout << " po vynasobeni vsetkych medzivysledkov (cisel 1/-1/0), konecny vysledok je " << Jakobi_postup(a, p) << endl; //in case of bad input returns 0
}

void my_CRT(ZZ A, ZZ MP, ZZ B, ZZ NP) {
    ZZ tmp, tmp2, mulmod, invMP, invNP;

    mul(mulmod, MP, NP);

    rem(tmp, MP, NP);
    InvMod(invNP, tmp, NP);

    rem(tmp, NP, MP);
    InvMod(invMP, tmp, MP);

    mul(tmp, A, invMP);
    mul(tmp, tmp, NP);
    mul(tmp2, B, invNP);
    mul(tmp2, tmp2, MP);

    cout << "mod1 * mod2: " << mulmod << endl
        << "inv prvok prva rovnica: " << invMP << endl
        << "inv prvok druha rovnica: " << invNP << endl
        << " prvok A( " << A << " ) * invMP( " << invMP << " ) * "
        << " modulo NP( " << NP << ") = " << tmp << endl
        << " prvok B( " << B << " ) * invNP( " << invNP << " ) * "
        << " modulo MP( " << MP << ") = " << tmp2 << endl;

    add(tmp, tmp, tmp2);
    rem(tmp2, tmp, mulmod);

    cout << "tieto vysledky teraz scitam a zmodulujem-> ( "
        << tmp << " ) % (" << mulmod << ") = "
        << tmp2 << " mod " << mulmod << endl;
}

void CRT() {
    ZZ A, P, a, p;
    cout << "Input modulo p: ";
    cin >> p;
    cout << "Input value a: ";
    cin >> a;
    cout << "Input modulo P: ";
    cin >> P;
    cout << "Input value A: ";
    cin >> A;

    my_CRT(a, p, A, P);
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