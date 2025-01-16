#include "mod_operations.hpp"

#include <cmath>  // 包含 std::floor
// Modular addition
BigInteger mod_add(BigInteger a, BigInteger b, BigInteger modulus) {
    BigInteger c = a+b;
    if (c >= modulus)return c- modulus;
    else return c;
}

// Modular subtraction
BigInteger mod_sub(BigInteger a, BigInteger b, BigInteger modulus) {
    if (a>= b) return a-b;
    else {
        BigInteger c = a+ modulus;
        return c- b;
    }
    //return (a >= b) ? (a - b) % modulus : ((a % modulus) + modulus - (b % modulus)) % modulus;
}

// Modular multiplication
BigInteger mod_mul(BigInteger a, BigInteger b, BigInteger modulus) {
    BigInteger result;
    BigInteger c = a*b;
    result=c%modulus;
    return result;
}

// Modular inverse using extended Euclidean algorithm
/*vector<int> mod_inv(vector<int> a, vector<int> modulus) {
    if (modulus.empty()) {
        // 返回错误，modulus不能为零
        cout << "modulus equals 0!" << "\n";
        return {};
    }

    vector<int>  m0 = modulus, t, q={0}, r;
    vector<int>b = { 1,1 };
    vector<int>x0={1,0}, x1 = { 1,1 };

    while (cmp(modulus, a)) {
        // 计算商
        //q = floor(a / modulus);
        q = div( modulus,a,r);
        t = a;

        // 计算模
        //modulus = a % modulus;
        //modulus = a - q * modulus;
        modulus = r;
        a = t;

        // 更新系数
        t = x0;
        //x0 = x1 - q * x0
        x0 = mod_mul(q, x0, modulus);
        x0 = sub(x1, x0);
        x1 = t;
    }
    x0 = { 0 };
    // 如果 x1 < 0, 需要加上 m0
    if (!cmp(x1,x0)) {
        //x1 += m0;
        x1 = add(x1, m0);
    }

    return x1;
}*/
BigInteger mod_inv(BigInteger a, BigInteger P, BigInteger* u, BigInteger* v)
{
   // cout <<"a="<<a.getNumber()<<",b="<<P.getNumber() << "!\n";
    BigInteger x = BigInteger(), modulus = P;
    string l = "1";
    if (a == x)
    {
        *u = BigInteger();
        *v = BigInteger(l, 0);
        return P;
    }

    BigInteger _u, _v, t, r;

    t = P / a;
    r = P % a;
   // cout << "t=" << t.getNumber() << ",r=" << r.getNumber() << "!\n";
    BigInteger pgcd = mod_inv(r, a, &_u, &_v);
    t = t* _u;
    //*u = sub(_v, t);
    /*if (_v >= t)* u = _v- t;
    else {
        _v = _v+ modulus;
        *u = _v- t;
    }*/
    *u = _v - t;
    *v = _u;

   /* cout << "a*u+p*v=";
    if (a.getSign())cout << "-" << a.getNumber() ;
    else cout <<  a.getNumber() ;
    cout << "*";
    if ((*u).getSign())cout << "-" << (*u).getNumber() ;
    else cout << (*u).getNumber();
    cout << "+";
    if (P.getSign())cout << "-" << P.getNumber() ;
    else cout << P.getNumber() ;
    cout << "*";
    if ((*v).getSign())cout << "-" << (*v).getNumber() ;
    else cout << (*v).getNumber() ;
    cout << "\n";*/

    return pgcd;
}
