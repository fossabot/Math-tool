#include "config.h"

//sifrovania
string to_lower(string input) {
    string result;
    for (int i = 0; i<input.length(); i++) {
        char tmp = input[i]; 
        if (tmp > 64 && tmp < 91) tmp += 32;
        result+=tmp;
    }
    return result;
}

int val(char c) {
    return c - 97;
}

int ival(char c) {
    return c + 97;
}

int func(int x, int a, int b, int c) {
    return (x * a + b) % c;
}

int ifunc(int x, int a, int b, int c) {
    int tmp = x - b;
    while(tmp % a != 0)
        tmp += c;
    return tmp / a;
}

#define ot val(OT[i])
#define zt val(ZT[i])
#define in a, b, c

#define asd string OT, string& ZT, int &IV, int a, int b, int c, int i
void _ecb(asd) { ZT += ival(func(ot, in)); }
void _cbc(asd) { ZT += ival(func(ot + zt, in)); }
void _cfb(asd) { ZT += ival(func(func(zt, in), 1, ot, c)); }
void _ofb(asd) { IV = func(IV, in); ZT += ival(func(ot, 1, IV, c)); }
void _ctr(asd) { IV = func(IV + i + 1, in); ZT += ival(func(ot, 1, IV, c)); }
void(*sifrovat[5])(asd) = {_ecb, _cbc, _cfb, _ofb, _ctr};

#define fgh string& OT, string ZT, int& IV, int a, int b, int c, int i
void _ecb(fgh) { OT += ival(ifunc(zt, in)); }
void _cbc(fgh) { OT += ival(func(ifunc(zt, in) - val(ZT[i + 1]), 1, c, c)); }
void _cfb(fgh) { OT += ival(func(zt - func(val(ZT[i + 1]), in), 1, c, c)); }
void _ofb(fgh) { IV = func(IV, in); OT += ival(func(zt - IV, 1, c, c)); }
void _ctr(fgh) { IV = func(IV + i + 1, in); OT += ival(func(zt - IV, 1, c, c)); }
void(*desifrovat[5])(fgh) = { _ecb, _cbc, _cfb, _ofb, _ctr };

enum mode { ecb, cbc, cfb, ofb, ctr };

mode input0() {
    int tmp;
    cout << "Aky mod chces pouzit?: 1-ecb, 2-cbc, 3-cfb, 4-ofb, 5-ctr: ";
    cin >> tmp;
    return mode(tmp - 1);
}

string input1(string input) {
    string text;
    cout << "Zadaj " << input << ": ";
    cin >> text;

    text = to_lower(text);
    for (int i = 0; i < text.length(); i++)
        cout << val(text[i]) << " ";
    return text;
}

void input2(int& a, int& b, int& c) {
    cout << "Zadaj parametre (a b c) funkcie f pre Ax+b mod c:";
    cin >> a >> b >> c;
    cout << a << "x + " << b << " mod " << c << endl;
}

#define params OT, ZT, IV, in, i

void sifruj() {
    mode m = input0();
    string OT = input1("OT");

    int IV=0, in;
    if (m != ecb) {
        cout << "Zadaj hodnotu IV: ";
        cin >> IV;
    }
    input2(in);

    string ZT;
    if(m == cbc || m == cfb) ZT += ival(func(IV, in));

    for (int i = 0; i < OT.length(); i++)
        sifrovat[m](params);
    cout << ZT << endl;
}

void desifruj() {
    mode m = input0();
    string ZT = input1("ZT");
    if (m == cbc || m == cfb) reverse(ZT.begin(), ZT.end());

    int IV=0, in;
    if (m == ofb || m == ctr) {
        cout << "Zadaj hodnotu IV: ";
        cin >> IV;
    }
    input2(in);

    string OT;

    if (m == cbc || m == cfb) {
        for (int i = 0; i < ZT.length()-1; i++)
            desifrovat[m](params);
        IV = ifunc(val(ZT[ZT.length() - 1]), in);
        reverse(OT.begin(), OT.end());
        cout << endl << "OT: " << OT << endl << "IV: " << IV << endl;
    }
    else {
        for (int i = 0; i < ZT.length(); i++)
            desifrovat[m](params);
        cout << OT << endl;
    }
}

#undef in

void RSA_sifruj() {
    int n, e, x;
    cout << "Zadaj VK(n,e) a spravu x:";
    cin >> n >> e >> x;

    ZZ_p::init(to_ZZ(n));
    ZZ_p res = to_ZZ_p(power(to_ZZ(x), e));
    cout << "E(x)= x^e mod n\nE(x)= "<< x << "^" << e <<" mod "<< n << " = " << res << endl;
}

void RSA_desifruj() {
    int n, d, y;
    cout << "Zadaj PK(n,d) a spravu y:";
    cin >> n >> d >> y;

    ZZ_p::init(to_ZZ(n));
    ZZ_p res = to_ZZ_p(power(to_ZZ(y), d));
    cout << "D(y)= y^d mod n\nD(y)= " << y << "^" << d << " mod " << n << " = " << res << endl;
}

void RSA_2020() {
    int n, e, x;
    cout << "pre VK(n,e) a msg x, zadaj n,e,x:";
    cin >> n >> e >> x;

    vec_ZZ list = factorize_number(to_ZZ(n));
    cout << " hodnota n( " << n << " ) rozlozena na prvociselne delitele : " << list << endl;
    if (list.length() > 2) return;
    int max_power = cancer(list);
    cout << " lambda( " << n << " ) = lcm( ";

    for (int i = 0; i < list.length(); i++) {
        cout << " lam( " << list[i] << " )";
        if (i != list.length() - 1) cout << ", ";
    }

    int p, q; //89,97
    p = to_long(list[0]);
    q = to_long(list[1]);
    vec_to_lambda(list);

    cout << " ) = lcm( ";
    for (int i = 0; i < list.length(); i++) {
        cout << list[i];
        if (i != list.length() - 1) cout << ", ";
    }

    //toto funguje iba ak n je naozaj cislo ktore ma prave dva prvociselne delitele
    int tmp, d, d1, d2, y1, y2, x1, x2, u, v,res;
    tmp = lcm(list);
    d = InvMod(e, tmp);
    d1 = d % (p-1);
    d2 = d % (q-1); 
    y1 = x % p; 
    y2 = x % q; 
    x1 = PowerMod(y1, d1, p);
    x2 = PowerMod(y2, d2, q);
    u = InvMod(q, p);
    v = InvMod(p, q);
    res = AddMod(x1 * u * q, x2 * v * p, n);

    cout << " ) = " << tmp << endl
         << " " << e << " x d = " << "1 (mod " << tmp << ") -> d = " << e << "^-1(inverzny prvok) -> d = " << d << endl
         <<"Algorytmus rychleho desifrovania:"<<endl
         << "d1= " << d  << "(mod " << p-1 << ") = " << d1 << endl
         << "d2= " << d  << "(mod " << q-1 << ") = " << d2 << endl
         << "y1= " << x  << "(mod " << p << ") = " << y1 << endl
         << "y2= " << x  << "(mod " << q << ") = " << y2 << endl
         << "x1= " << y1 << "^" << d1 << "(mod " << p << ") = " << x1 << endl
         << "x2= " << y2 << "^" << d2 << "(mod " << q << ") = " << x2 << endl
         << "u= " << q << "^-1" << "(mod " << p << ") = " << u << endl
         << "v= " << p << "^-1" << "(mod " << q << ") = " << v << endl
         << "result-> (x1 * u * q + x2 * v * p) mod n"<<endl
         << "( " << x1 << " * " << u << " * " << q << " + " << x2 << " * " << v << " * " << p << " ) mod " << n << " = " << res % n << endl;
}

int char_to_int(char c , string table, int offset) {
    for (int i = 0; i < table.length(); i++) 
        if (c == table[i]) return i+offset;
}

void El_gamal_2020() {
    ZZ p, a, c;
    cout << "Zadaj VK(p,a,c): ";
    cin >> p >> a >> c;

    string ZT;
    cout << "Zadaj ZT: ";
    cin >> ZT;

    string table;
    cout << "Zadaj prekladovu tabulku: ";
    cin >> table;
    
    int offset;
    cout << "Zadaj offset zaciatku indexovania: ";
    cin >> offset;

    int y1, y2, b, A, B, OT;
    b = ord(a, p, c);
    cout << "Ak pozname b tak mozeme desifrovat podla vzorca x = y2 * (y1^b)^-1 mod p, kde y1,y2 je ZT a x je OT\n";
    cout << "b je :" << b << endl;

    cout << "_________________________________________\n"
        << "|            |   A  |   B  |             |\n"
        << "| ZT=(y1,y2) | y1^b | A^-1 | y2 * B | OT |\n";

    for (int i = 0; i < ZT.length(); i+=2) {
        char tmp = ZT[i];
        char tmp2 = ZT[i + 1];
        y1 = char_to_int(tmp, table, offset);
        y2 = char_to_int(tmp2, table, offset);
        A = PowerMod(y1, b, to_long(p));
        B = InvMod(A, to_long(p));
        OT = MulMod(B, y2, to_long(p));
        cout << "|(" << tmp << "," << tmp2 << ")=(" << y1 << "," << y2 << ")|  " << A << "  |  " << B << "  |   " << OT << "   | " << table[OT - offset] << "  |\n";
    }
}

int inverse(ZZ A, ZZ M) {
    A = ((A % M)+M)%M;
    for (long i = 1; i < M; i++) 
        if ((A*i)%M == 1) return i;
    return 0;
}

void vypocet(ZZ a, ZZ p) {
    ZZ x1, x2, y1, y2, lam, tmp;
    cout << "zadaj P(x1,y1): ";
    cin >> x1 >> y1;
    cout << "zadaj Q(x2,y2): ";
    cin >> x2 >> y2;
    tmp = y1 + y2;

    if (x1 == x2 && tmp == p || tmp == 0) {
        cout << "P + Q = 0";
        return;
    }

    if (x1 == x2 && y1 == y2) {
        lam = rep(to_ZZ_p((3 * x1 * x1 + a) * inverse(2 * y1, p)));
        cout << "lam= (3 * x1^2 + a) * (2 * y1)^-1 mod p\n";
    }
    else {
        lam = rep(to_ZZ_p((y2 - y1) * inverse(x2 - x1, p)));
        cout << "lam= (y2 - y1) * (x2 - x1)^-1 mod p\n";
    }

    ZZ x3 = rep(to_ZZ_p(lam * lam - x1 - x2));
    ZZ y3 = rep(to_ZZ_p(lam * (x1 - x3) - y1));
    cout << "lam = " << lam << endl 
         << "x3= lam^2 - x1 - x2"<<endl
         << "x3= "<<x3<<endl
         << "y3= lam * (x1 - x3) - y1"<<endl
         << "y3= "<<y3<<endl
         << "P(" << x1 << "," << y1 << ") + Q(" << x2 << "," << y2 << ") = (" << x3 << "," << y3 << ")"<<endl;
}

string addd(ZZ num) {
    string s="";
    if(num==0)  s = (char)to_long((num % 10) + 48) + s;
    else
    while (num > 0) {
        s = (char)to_long((num % 10) + 48) + s;
        num /= 10;
    }
    return s;
}

void addd(string &out,ZZ x, ZZ y) {
    out = out + "| (" + addd(x) + "," + addd(y) + ")";
}

#define xi x[i]
#define xj x[j]
#define yi y[i]
#define yj y[j]

void table(ZZ a, ZZ p, vec_ZZ x, vec_ZZ y) {
    string out = "";
    for (int i = -1; i < 5; i++, out += "\n")
        for (int j = -1; j < 5; j++)
            if (i == -1 && j == -1) out += " +     ";
            else if (i == -1) addd(out, xj, yj);
            else if (j == -1) addd(out, xi, yi);
            else if (xi == xj && (yi + yj) == p || (yi + yj) == 0) out += "   0   ";
            else {
                ZZ lam = (yj - yi) * inverse(xj - xi, p);
                if (xi == xj && yi == yj)
                    lam = (3 * xi * xi + a) * inverse(2 * yi, p);
                 
                ZZ x3 = rep(to_ZZ_p(lam * lam - xi - xj));
                ZZ y3 = rep(to_ZZ_p(lam * (xi - x3) - yi));
                addd(out, x3, y3);
            }
    cout << out;
}

void epilepticke_krivky_2020() {
    ZZ a, b, p;
    cout << "Zadaj parametre (a,b,p) pre krivku y^2 = x^3 + ax + b mod p: ";
    cin >> a >> b >> p;

    if (AddMod(PowerMod((4 * a) % p, 3, p),PowerMod((27 * b) % p, 2, p),p) == 0) {
        cout << "Zadane parametre netvoria elipticku krivku.\n";
        return;
    }
    cout << "Zadane parametre tvoria elipticku krivku.\n";

    vec_ZZ x, y;
    ZZ_p::init(p);
    for (ZZ i(0); i < p; i++) 
        for (ZZ j(0); j < p; j++) 
            if (to_ZZ_p(j*j) == to_ZZ_p(i*i*i) + to_ZZ_p(a * i) + to_ZZ_p(b)) {
                x.append(i);
                y.append(j);
            }
    int dlzka = x.length();
    if (dlzka > 20) dlzka = 20;

    for (int i = 0; i < dlzka; i++) 
        cout << "Bod "<<i+1<<" x, y = [" << xi << ", " << yi << "]" << endl;

    table(a, p, x, y);
    while (1) {
        cout << "Stlac 0 pre ukoncenie prikladu\nStlac 1 pre vypocet konkretneho suctu:";
        bool tmp;
        cin >> tmp;
        if (tmp == 0) return;
        else if (tmp == 1) vypocet(a, p);
    }
}  

bool is_prime(ZZ num) {
    ZZ sqrt = SqrRoot(num);
    cout << "testing if " << num << " is prime\n"
         << "sqrt: " << sqrt << endl;

    if (rem(num, 2) == 0) return 0;

    for (int i = 3; i < sqrt; i+=2)
        if (rem(num, i) == 0) return 0;

    return 1;
}

void Gordon_Helman_Bach_2020() {
    ZZ s, t, b;
    cout << "Zadaj parametre s,t a pocet bitov b: ";
    cin >> s >> t >> b;

    ZZ tmp(b/2), q, p;
    for (int i = 1; i < tmp; i++) {
        q = 2 * i * t + 1;
        cout << "i: "<< i << ",q: " << q << endl;
        if (is_prime(q)) break;
    }

    ZZ p0 = 2 * PowerMod(s, q - 2, q) * s - 1;
    cout << "p0= 2 * (s^(q-2) mod q) * s -1" << endl
        << "p0= 2 * (" << s << "^(" << q - 2 << ") mod " << q << ")* " << s << " - 1" << endl
        << "p0=" << p0 << endl;

    for (int i = 0; i < tmp; i++) {
        p = p0 + 2 * i * q * s;
        cout << "i: " << i << ",p: " << p << endl;
        if (is_prime(p)) break;
    }
    cout << "Cislo p(" << p << ") je silne prvocislo s " << b << " alebo viac bitmi." << endl;
}

void (*ZKRY2[8])() = { sifruj,
                       desifruj,
                       RSA_2020,
                       El_gamal_2020,
                       epilepticke_krivky_2020,
                       Gordon_Helman_Bach_2020,
                       RSA_sifruj,
                       RSA_desifruj
};
