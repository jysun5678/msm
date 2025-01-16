#include <iostream>
#include <string>
#include <sstream>
#include <utility>
using namespace std;
class BigInteger
{

private:
    string number;
    bool sign;

public:
    BigInteger();                   // empty constructor initializes zero
    BigInteger(string s);           // "string" constructor
    BigInteger(string s, bool sin); // "string" constructor with given sign
    BigInteger(int n);              // "int" constructor
    void setNumber(string s);
    const string& getNumber(); // retrieves the number
    const string& get_signedNumber();
    void setSign(bool s);
    const bool& getSign();
    BigInteger absolute();        // returns the absolute value
    void operator=(BigInteger b); //operator overloadings
    bool operator==(BigInteger b);
    bool operator!=(BigInteger b);
    bool operator>(BigInteger b);
    bool operator<(BigInteger b);
    bool operator>=(BigInteger b);
    bool operator<=(BigInteger b);
    BigInteger& operator++();   // prefix
    BigInteger operator++(int); // postfix
    BigInteger& operator--();   // prefix
    BigInteger operator--(int); // postfix
    BigInteger operator+(BigInteger b);
    BigInteger operator-(BigInteger b);
    BigInteger operator*(BigInteger b);
    BigInteger operator/(BigInteger b);
    BigInteger operator%(BigInteger b);
    BigInteger operator>>(unsigned b);
    BigInteger& operator+=(BigInteger b);
    BigInteger& operator-=(BigInteger b);
    BigInteger& operator*=(BigInteger b);
    BigInteger& operator/=(BigInteger b);
    BigInteger& operator%=(BigInteger b);
    BigInteger operator-(); // unary minus sign
    operator string();      // for conversion from BigInteger to string

private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
};