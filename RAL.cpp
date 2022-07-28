#include "funkcie.h"

void func(string& dst, int i, int val) {
    string a = to_string(i);
    string b = to_string(val);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    if (i == 1) dst += "x";
    if (i > 1) dst += a + "^x";
    if (i == 0 || val > 1) dst += b;
    dst += " + ";
}

void transform(string& dst, ZZ_pX src) { //format polynomial to output string
    for (int i = 0; i < (src.rep).length(); i++) {
        int tmp = to_long(rep((src.rep)[i]));
        if (tmp)  func(dst, i, tmp);
    }
    dst.erase(dst.length() - 3, dst.length());
}

void vypis(ZZ_pX A) { 
    string output = "";
    transform(output, A);
    reverse(output.begin(), output.end());
    cout << output << endl;
}

void vypis(Vec<Pair<ZZ_pX, long>> factors) { 
    string tmp = "";
    string final = "";

    for (int i = 0; i < factors.length(); i++) {
        if (factors[i].b > 1)
            tmp += " " + to_string(factors[i].b) + "^";
        tmp += ")";

        transform(tmp, factors[i].a);

        tmp += "(";
        final += tmp;
        tmp = "";
    }
    reverse(final.begin(), final.end());

    cout << "Vysledkom faktorizacie je: " << final << "." << endl;
    cout << "Raw format: " << factors << endl;
}

void inverse_val_A_mod_M() { // zero input is error, f.e. 2 4-> error, 2 doesnt have inverse in group Z4, bcs 2*2=0 mod 4
    ZZ A, M;
    cout << "Input mod M: ";
    cin >> M;
    cout << "Input val A: ";
    cin >> A;

    rem(A, A, M);
    InvMod(A, A, M);
    cout << "invA: " << A << endl;
}

int ord(ZZ A, ZZ M, ZZ result) {
    rem(A, A, M);
    for (long i = 1; i < M; i++) 
        if (PowerMod(A, i, M) == result) 
            return i;
    return 0;
}

void ord_val_A_mod_M() {
    ZZ A, M;
    cout << "Input modulo M: ";
    cin >> M;
    cout << "Input value A: ";
    cin >> A;
    cout << "ord of value: " << A << " modulo: " << M << " is: " << ord(A, M) << endl;
}

void is_irred_poly_A_mod_M() {
    ZZ M;
    cout << "Input mod M: ";
    cin >> M;
    ZZ_p::init(M);

    ZZ_pX A;
    cout << "Input polynom A: ";
    cin >> A;

    if (DetIrredTest(A))
        cout << "your polynom " << A << " is irreducible mod " << M << endl;
    else
        cout << "your polynom " << A << " is not irreducible mod " << M << endl;
}

void factor_poly_A_mod_M() {
    ZZ M;
    cout << "Input mod M: ";
    cin >> M;
    ZZ_p::init(M);

    ZZ_pX A;
    cout << "Input polynom A: ";
    cin >> A;

    Vec<Pair<ZZ_pX, long>> factors;
    CanZass(factors, A);  // calls "Cantor/Zassenhaus" algorithm
    vypis(factors);
}

void inverse_poly_A_mod_poly_MP_mod_M() {
    ZZ M;
    cout << "Input mod M: ";
    cin >> M;
    ZZ_p::init(M);

    ZZ_pX MP, A;
    cout << "Input polynom MP: ";
    cin >> MP;
    cout << "Input polynom A: ";
    cin >> A;

    rem(A, A, MP);
    if (InvModStatus(A, A, MP))
        cout << "GCD: " << A << endl;
    else {
        cout << "invA: "; vypis(A);
        cout << "Raw format: " << A << endl;
    }
}

void CRT_val_A_mod_M_and_val_B_mod_N() {
    ZZ A, M, B, N;
    cout << "Input mod M: ";
    cin >> M;
    cout << "Input val A: ";
    cin >> A;
    cout << "Input mod N: ";
    cin >> N;
    cout << "Input val B: ";
    cin >> B;

    CRT(A, M, B, N);
    if (A < 0) add(A, A, M);
    cout << "result: " << A << " mod: " << M << endl;
}

void CRT(ZZ_pX& A, ZZ_pX& MP, ZZ_pX& B, ZZ_pX& NP) {
    ZZ_pX temp, temp2, mulmod;
    GCD(temp, MP, NP);

    if (temp != 1) {
        cout << "GCD: " << temp << endl;
        return;
    }

    mul(mulmod, MP, NP);
    cout << "mulmod: "; vypis(mulmod);
    cout << "Raw format: " << mulmod << endl << endl;

    ZZ_pX invMP, invNP;
    rem(temp, MP, NP);

    if (InvModStatus(invNP, temp, NP)) {
        cout << "GCD: " << A << endl;
        return;
    }

    rem(temp, NP, MP);
    if (InvModStatus(invMP, temp, MP)) {
        cout << "GCD: " << A << endl;
        return;
    }

    cout << "invMP: "; vypis(invMP);
    cout << "Raw format: " << invMP << endl << endl;

    cout << "invNP: "; vypis(invNP);
    cout << "Raw format: " << invNP << endl << endl;

    mul(temp, A, invMP);
    mul(temp, temp, NP);

    mul(temp2, B, invNP);
    mul(temp2, temp2, MP);

    add(temp, temp, temp2);
    rem(temp, temp, mulmod);

    cout << "result: "; vypis(temp);
    cout << "Raw format: " << temp << endl;
}

void CRT_poly_A_mod_poly_MP_and_poly_B_mod_poly_NP_mod_M() {
    ZZ M;
    cout << "Input mod M: ";
    cin >> M;
    ZZ_p::init(M);

    ZZ_pX A, MP, B, NP;
    cout << "Input poly mod MP: ";
    cin >> MP;
    cout << "Input poly A: ";
    cin >> A;
    cout << "Input poly mod NP: ";
    cin >> NP;
    cout << "Input poly B: ";
    cin >> B;

    cout << "\nzadane pole: " << M;
    cout << "\nzadany polynom: "; vypis(A); cout << " modulo: "; vypis(MP);
    cout << "\nzadany polynom: "; vypis(B); cout << " modulo: "; vypis(NP);
    cout << endl;

    CRT(A, MP, B, NP);
}

void list_of_cyklo_poly() {
    fstream file("cyklotomic_100.txt", ios::out);

    vec_ZZX phi(INIT_SIZE, 100);
    for (long i = 1; i <= 100; i++) {
        ZZX t;
        t = 1;
        for (long j = 1; j <= i - 1; j++)
            if (i % j == 0)
                t *= phi(j);
        phi(i) = (ZZX(i, 1) - 1) / t; // ZZX(i, a) == X^i * a
        file << i << ": " << phi(i) << "\n";
    }
}

void DFT() {
    int n;
    cout << "zadaj n, pre DFT n-teho radu: ";
    cin >> n;

    char odpoved;
    cout << "Chces zadat vlasne pole? (Y/N)";
    cin >> odpoved;

    ZZ pole(0);
    if (odpoved == 'N') {
        for (int i = 1; i < 5; i++)
            if (ProbPrime((n * i) + 1)) {
                pole = n * i + 1;
                cout << "pole ktore sa pouzije " << " je: " << pole << endl;
                break;
            }
    }
    else {
        cout << "\n Zadaj pole ";
        cin >> pole;
    }

    if (pole == 0) {
        cout << "pole sa nenaslo";
        return;
    }

    ZZ_p::init(pole);
    ZZ_p prvok;
    mat_ZZ_p H, H2;

    H.SetDims(n, n);
    H2.SetDims(n, n);

    cout << "Chces zadat vlasny prvok z tohoto pola? (Y/N)";
    cin >> odpoved;
    if (odpoved == 'N') {
        for (int i = 0; i < pole; i++)
            if (ord(to_ZZ(i), pole) == n) {
                cout << "prvok " << i << " je radu " << n << " v poli " << pole << endl;
                prvok = i;
                break;
            }
    }
    else {
        cout << "\n Zadaj prvok radu " << n << " z pola " << pole;
        cin >> prvok;
        if (ord(rep(prvok), pole) != n) {
            cout << "zadany prvok nie je radu " << n << " v poli " << pole;
            return;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == 0 || j == 0) {
                H[i][j] = 1;
                H2[i][j] = 1;
            }
            else {
                ZZ_p tmp = prvok;
                for (int k = 1; k < i; k++)
                    tmp *= prvok;

                H[i][j] = H[i][j - 1] * tmp;
                H2[i][j] = conv<ZZ_p>(InvMod(rep(H[i][j]), pole));
            }

    cout << "obsah matice H je: \n" << H << endl;
    cout << "obsah matice H2 je: \n" << H2 << endl;

    vec_ZZ_p vektor;
    cout << "zadaj vektor V na zobrazenie: ";
    cin >> vektor;

    vektor *= H;
    cout << "vektor V' je: " << vektor << endl;

    vektor = InvMod(n, to_long(pole)) * vektor * H2;
    cout << "overenie V = 1/n * V' * H' = " << vektor << endl << endl;
}

void kvadraticke_sito() {
    ZZ N, m;
    cout << "zadaj N: ";
    cin >> N;

    m = SqrRoot(N);
    cout << "Spodny stvorec ku " << N << " je " << m << endl;
    cout << " i |Q(i)=(m+i)^2 -N | rozklad\n";

    for (int i = -3; i <= 3; i++)
        cout << " " << i << " |   " << ((m + i) * (m + i) - N) << " | " << endl;
}

void berlekamp() {
    ZZ p;
    cout << "zadaj modulo p: ";
    cin >> p;
    ZZ_p::init(p);

    ZZ_pX mod, poly_v_matici;
    mat_ZZ_p matica, jednotkova_matica;

    cout << endl << "zadaj polynom: ";
    cin >> mod;
    cout << " zadany polynom: "; vypis(mod); cout << endl;

    int dlzka = deg(mod);
    matica.SetDims(dlzka, dlzka);
    jednotkova_matica.SetDims(dlzka, dlzka);
    poly_v_matici.SetMaxLength(dlzka);

    for (int i = 0; i < dlzka; i++) {
        SetCoeff(poly_v_matici, to_long(p) * i);
        cout << "polynom na " << i << " riadku je pred redukciou: "; vypis(poly_v_matici);
        rem(poly_v_matici, poly_v_matici, mod);
        for (int j = 0; j < dlzka; j++)
            matica[i][j] = poly_v_matici[j];
        cout << " po redukcii: "; vypis(poly_v_matici); cout << endl;
        clear(poly_v_matici);
    }
    cout << "matica ma teda tvar Q: " << endl << matica << endl;

    ident(jednotkova_matica, dlzka);
    cout << "jednotkova matica I: " << endl << jednotkova_matica << endl;

    matica -= jednotkova_matica;
    cout << "Q-I " << endl << matica << endl;

    matica = transpose(matica);
    cout << "Q-I transponovana: " << endl << matica << endl;

    gauss(matica);
    cout << "vysledok gaussovej eliminacie: " << endl << matica << endl;
}

void sqrt() {
    ZZ p, b, a;
    cout << "zadaj modulo p: ";
    cin >> p;
    cout << "zadaj value a: ";
    cin >> a;

    if (!ProbPrime(p)) cout << "p nieje prvocislo\n";

    int res = Jacobi(a, p);
    cout << "Jakobi pre " << a << " modulo: " << p << " je: " << res << endl;
    if (res == 1) {
        SqrRootMod(b, a, p);
        cout << "Korene z: " << a << " modulo: " << p << " su: " << b << " a " << p - b << endl;
    }
}

void (*RAL[11])() = { ord_val_A_mod_M,
                      inverse_val_A_mod_M,
                      is_irred_poly_A_mod_M,
                      factor_poly_A_mod_M,
                      inverse_poly_A_mod_poly_MP_mod_M,
                      CRT_val_A_mod_M_and_val_B_mod_N,
                      CRT_poly_A_mod_poly_MP_and_poly_B_mod_poly_NP_mod_M,
                      DFT,
                      kvadraticke_sito,
                      berlekamp,
                      sqrt
};