/*
  Big Integer library in C++, single file implementation.
 */

#include"bigintegerlibrary.hpp"
#include <cmath>
#define MAX 10000 // for strings
 // MAX length of a string, So number can be as high as 10^(10000)

//using namespace std;




/*------------------------------------------------------------------------------*/

BigInteger::BigInteger()
{ // empty constructor initializes to zero
    number = "0";
    sign = false; // false means positive (+ve)
}

BigInteger::BigInteger(string s)
{ // "string" constructor
    if (isdigit(s[0]))
    {   // if not signed , isdigit is inbuilt C++ function to check
        //if character is digit or not
        setNumber(s);
        sign = false; // +ve
    }
    else
    {
        setNumber(s.substr(1));
        sign = (s[0] == '-');
    }
}

BigInteger::BigInteger(string s, bool sin)
{ // "string" constructor
    setNumber(s);
    setSign(sin);
}

BigInteger::BigInteger(int n)
{ // "int" constructor
    stringstream ss;
    string s;
    ss << n;
    ss >> s; //converting int to string using stringstream

    if (isdigit(s[0]))
    { // if not signed
        setNumber(s);
        setSign(false); // +ve
    }
    else
    {
        setNumber(s.substr(1));
        setSign(s[0] == '-');
    }
}

void BigInteger::setNumber(string s)
{
    number = s; //assigns this string to number(private variable)
}

const string& BigInteger::getNumber()
{ // retrieves the number for user reference
    return number;
}
const string& BigInteger::get_signedNumber()
{ 
    if(!getSign())return number;
    else {
        string signum = "-"+number;
    }
}

void BigInteger::setSign(bool s)
{
    sign = s; // if s==1 then -ve else +ve
}

const bool& BigInteger::getSign()
{ // retrieves the sign for user reference
    return sign;
}

BigInteger BigInteger::absolute()
{                                   //return type is BigInteger
    return BigInteger(getNumber()); // +ve by default
}
//now operator overloading
void BigInteger::operator=(BigInteger b)
{
    setNumber(b.getNumber());
    setSign(b.getSign());
}

bool BigInteger::operator==(BigInteger b)
{
    return equals((*this), b);
}

bool BigInteger::operator!=(BigInteger b)
{
    return !equals((*this), b);
}

bool BigInteger::operator>(BigInteger b)
{
    return greater((*this), b);
}

bool BigInteger::operator<(BigInteger b)
{
    return less((*this), b);
}

bool BigInteger::operator>=(BigInteger b)
{
    return equals((*this), b) || greater((*this), b);
}

bool BigInteger::operator<=(BigInteger b)
{
    return equals((*this), b) || less((*this), b);
}

BigInteger& BigInteger::operator++()
{ // prefix
    (*this) = (*this) + 1;
    return (*this);
}

BigInteger BigInteger::operator++(int)
{ // postfix
    BigInteger before = (*this);

    (*this) = (*this) + 1;

    return before;
}

BigInteger& BigInteger::operator--()
{ // prefix
    (*this) = (*this) - 1;
    return (*this);
}

BigInteger BigInteger::operator--(int)
{ // postfix
    BigInteger before = (*this);

    (*this) = (*this) - 1;

    return before;
}

BigInteger BigInteger::operator+(BigInteger b)
{
    BigInteger addition;
    if (getSign() == b.getSign())
    { // both +ve or -ve
        addition.setNumber(add(getNumber(), b.getNumber()));
        addition.setSign(getSign());
    }
    else
    { // sign different
        if (absolute() > b.absolute())
        {
            addition.setNumber(subtract(getNumber(), b.getNumber()));
            addition.setSign(getSign());
        }
        else
        {
            addition.setNumber(subtract(b.getNumber(), getNumber()));
            addition.setSign(b.getSign());
        }
    }
    if (addition.getNumber() == "0") // avoid (-0) problem
        addition.setSign(false);

    return addition;
}

BigInteger BigInteger::operator-(BigInteger b)
{
    b.setSign(!b.getSign()); // x - y = x + (-y)
    return (*this) + b;
}

BigInteger BigInteger::operator*(BigInteger b)
{
    BigInteger mul;

    mul.setNumber(multiply(getNumber(), b.getNumber()));
    mul.setSign(getSign() != b.getSign());

    if (mul.getNumber() == "0") // avoid (-0) problem
        mul.setSign(false);

    return mul;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"
/*BigInteger BigInteger::operator/(BigInteger b)
{
    long long den = toInt(b.getNumber());
    BigInteger div;

    div.setNumber(divide(getNumber(), den).first);
    div.setSign(getSign() != b.getSign());

    if (div.getNumber() == "0") // avoid (-0) problem
        div.setSign(false);

    return div;
}*/
/*BigInteger BigInteger::operator/(BigInteger b)
{
    //long long den = toInt(b.getNumber());
    BigInteger div= BigInteger();
    div.setSign(getSign() != b.getSign());
    if (b == BigInteger()) {
        cout << "cannot div by 0!\n";
        return BigInteger();
    }
    //else if (toInt(b.getNumber()) < 2147483648) {//within "int" size
    else if (b < BigInteger("2147483648")) {
        //cout << "x/y:  x=" << getNumber() << ",y=" << b.getNumber() << "!\n";
        div.setNumber(divide(getNumber(), toInt(b.getNumber())).first);
        div.setSign(getSign() != b.getSign());

        if (div.getNumber() == "0") // avoid (-0) problem
            div.setSign(false);
        //cout << "x/y=" << div.getNumber() << "\n";
        return div;
    }
    else {
        BigInteger x = BigInteger(getNumber(), 0);
        BigInteger y = BigInteger(b.getNumber(), 0);
        cout << "x/y:  x=" << x.getNumber() << ",y=" << y.getNumber() << "!\n";
        //compute x/y
        while (x >= y) {
            x = x - y;
            if(!div.getSign())div++;
            else div--;
            cout << "div=" << div.getNumber() << "\n";
        }
        if (div.getNumber() == "0") {
            div.setSign(false);
        }
        cout << "x/y=" << div.getNumber()  << "\n";
        return div;
    }
}*/
BigInteger BigInteger::operator/(BigInteger b) {//Binary Search Method
    int m = len();
    int n = b.len();
    int high = m - n + 1;
    int low = m - n - 1;
    int medium=m-n;
    //cout << "x/y:  x=" << getNumber() << ",y=" << b.getNumber() << "x_len="<<m<<",y_len="<<n << "\n";
    //initial range of the result is (2^low,2^high)
    BigInteger div = BigInteger();
    BigInteger max= BigInteger(1), min= BigInteger(1);
    div.setSign(getSign() != b.getSign());
    if (b == BigInteger()) {
        cout << "cannot div by 0!\n";
        return BigInteger();
    }
    else if (m<n) {
        return BigInteger();
    }
    else if (m == n) {
        if((*this)<b)return BigInteger();
        else return BigInteger(1);
    }
    else {
        //cout << "m=" << m << ",n=" << n << "\n";
        for (int i = 0; i < high; i++) {
            //max = max * BigInteger(2);
            max = max + max;
        }
        for (int i = 0; i < low; i++) {
            //min = min * BigInteger(2);
            min = min + min;
        }
        //cout << "max=" << max.getNumber() << ",min=" << min.getNumber() << "\n";
        while ((max - min)>= BigInteger(2)) {
            
            BigInteger temp = average(min,max);
            //cout << "temp=" << temp.getNumber()<<",min="<<min.getNumber()<<",max="<<max.getNumber()<<"\n";
            if (temp*b <= (*this))min = temp;
            else max = temp;
        }
        return min;
    }
}


// Warning: Denomerator must be within "long long" size not "BigInteger"
/*BigInteger BigInteger::operator%(BigInteger b)
{
    long long den = toInt(b.getNumber());

    BigInteger rem;
    long long rem_int = divide(number, den).second;
    rem.setNumber(toString(rem_int));
    rem.setSign(getSign() != b.getSign());

    if (rem.getNumber() == "0") // avoid (-0) problem
        rem.setSign(false);
    if (rem.getSign())return rem + b;
    else return rem;
}*/
/*BigInteger BigInteger::operator%(BigInteger b)
{
    //long long den = toInt(b.getNumber());

    BigInteger rem= BigInteger();
    BigInteger x = BigInteger(getNumber(), getSign());
    BigInteger y = BigInteger(b.getNumber(), 0);
    //if (b.getSign()) {
        //cout << "modulus cannot be negative!\n";
       // return BigInteger();
    //}
    cout << "x%y:  x="<<x.getSign() << x.getNumber() << ",y=" << y.getSign() << y.getNumber() << "!\n";
    //if (toInt(b.getNumber()) < 2147483648) {//within "int" size
    if (y < BigInteger("2147483648")) {//within "int" size
        cout << "0000\n";
        long long den = toInt(b.getNumber());

        //BigInteger rem;
        long long rem_int = divide(number, den).second;
        rem.setNumber(toString(rem_int));
        rem.setSign(getSign() != b.getSign());
        //cout << "x%y=" << rem.getNumber() << "\n";
        if (rem.getNumber() == "0") // avoid (-0) problem
            rem.setSign(false);
        if (rem.getSign())return rem + b;
        else return rem;
    }
    else {
        if (getSign() == 0&&b.getSign()==0) {
            cout << "1111\n";
            while (x >= y) {
                x = x - y;
            }
            rem = x;
        }
        else if (getSign() == 0 && b.getSign()==1) {
            cout << "2222\n";
            while (x > BigInteger()) {
                x = x - y;
            }
            rem = x;
        }
        else if (getSign() == 1 && b.getSign() == 1) {
            cout << "3333\n";
            while (x < BigInteger()) {
                x = x + y;
            }
            rem = x-y;
        }
        else {
            while (x.getSign()) {
                cout << "4444\n";
                x = x + y;
                cout << "  x=" << x.getSign() << x.getNumber() << "\n";
            }
            rem = x;
        }
        //cout << "x%y=" << rem.getNumber() << "\n";
        return rem;
    }
}*/
BigInteger BigInteger::operator%(BigInteger b) {

    if (b > (*this)) {
        if (getSign()) {
            BigInteger div = (*this) / b;
            BigInteger result =  div * b-(*this) ;
            return result;
        }
        else return (*this);
    }
    else {
        BigInteger div = (*this) / b;
        BigInteger result = (*this) - div * b;
        return result;
    }
}


BigInteger BigInteger::operator>>(unsigned b)
{
    BigInteger b1 = (*this);
    if(b==0)return (*this);
    else if (b >= 1)
    {
        //(*this) = (*this) / (2 ^ b);
        while (b > 0) {
            //(*this) = (*this) / b1;
            string s = b1.getNumber();
            s = divide(s,2).first;
            b1 = BigInteger(s);
            b=b-1;
        }
        return b1;
    }
    else {
        BigInteger c = BigInteger();
        return c;
    }
}

BigInteger& BigInteger::operator+=(BigInteger b)
{
    (*this) = (*this) + b;
    return (*this);
}

BigInteger& BigInteger::operator-=(BigInteger b)
{
    (*this) = (*this) - b;
    return (*this);
}

BigInteger& BigInteger::operator*=(BigInteger b)
{
    (*this) = (*this) * b;
    return (*this);
}

BigInteger& BigInteger::operator/=(BigInteger b)
{
    (*this) = (*this) / b;
    return (*this);
}

BigInteger& BigInteger::operator%=(BigInteger b)
{
    (*this) = (*this) % b;
    return (*this);
}

BigInteger BigInteger::operator-()
{ // unary minus sign
    return (*this) * -1;
}

BigInteger::operator string()
{                                                 // for conversion from BigInteger to string
    string signedString = (getSign()) ? "-" : ""; // if +ve, don't print + sign
    signedString += number;
    return signedString;
}

int BigInteger::len()
{ 
    int len=0;
    string s = getNumber();
    int s_len = s.length();
    BigInteger t = (*this);
    while (s_len != 0) {
        //t = t >> 1;
        //cout << "s=" << s << "\n";
        s = divide(s, 2).first;
        len++;
        if (s != "0")s_len = s.length();
        else s_len = 0;
        //cout <<"s_len="<< s_len << ",len=" << len << "\n";
    }
    return len;
}

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
    return n1.getNumber() == n2.getNumber() && n1.getSign() == n2.getSign();
}

bool BigInteger::less(BigInteger n1, BigInteger n2)
{
    bool sign1 = n1.getSign();
    bool sign2 = n2.getSign();

    if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
        return true;

    else if (!sign1 && sign2)
        return false;

    else if (!sign1)
    { // both +ve
        if (n1.getNumber().length() < n2.getNumber().length())
            return true;
        if (n1.getNumber().length() > n2.getNumber().length())
            return false;
        return n1.getNumber() < n2.getNumber();
    }
    else
    { // both -ve
        if (n1.getNumber().length() > n2.getNumber().length())
            return true;
        if (n1.getNumber().length() < n2.getNumber().length())
            return false;
        return n1.getNumber().compare(n2.getNumber()) > 0;
        // greater with -ve sign is LESS
    }
}

bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
    return !equals(n1, n2) && !less(n1, n2);
}

string BigInteger::add(string number1, string number2)
{
    string add = (number1.length() > number2.length()) ? number1 : number2;
    char carry = '0';
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else // if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.size() - 1; i >= 0; --i)
    {
        add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

        if (i != 0)
        {
            if (add[i] > '9')
            {
                add[i] -= 10;
                carry = '1';
            }
            else
                carry = '0';
        }
    }
    if (add[0] > '9')
    {
        add[0] -= 10;
        add.insert(0, 1, '1');
    }
    return add;
}

string BigInteger::subtract(string number1, string number2)
{
    string sub = (number1.length() > number2.length()) ? number1 : number2;
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.length() - 1; i >= 0; --i)
    {
        if (number1[i] < number2[i])
        {
            number1[i] += 10;
            number1[i - 1]--;
        }
        sub[i] = ((number1[i] - '0') - (number2[i] - '0')) + '0';
    }

    while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
        sub.erase(0, 1);

    return sub;
}

string BigInteger::multiply(string n1, string n2)
{
    if (n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for (int i = n1.length() - 1; i >= 0; --i)
    {
        string temp = n2;
        int currentDigit = n1[i] - '0';
        int carry = 0;

        for (int j = temp.length() - 1; j >= 0; --j)
        {
            temp[j] = ((temp[j] - '0') * currentDigit) + carry;

            if (temp[j] > 9)
            {
                carry = (temp[j] / 10);
                temp[j] -= (carry * 10);
            }
            else
                carry = 0;

            temp[j] += '0'; // back to string mood
        }

        if (carry > 0)
            temp.insert(0, 1, (carry + '0'));

        temp.append((n1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

        res = add(res, temp); // O(n)
    }

    while (res[0] == '0' && res.length() != 1) // erase leading zeros
        res.erase(0, 1);

    return res;
}

pair<string, long long> BigInteger::divide(string n, long long den)
{
    if (den == 0)
    {
        return make_pair("Error: Division by zero", 0);
    }

    long long rem = 0;
    string result;
    result.resize(MAX);

    for (int indx = 0, len = n.length(); indx < len; ++indx)
    {
        rem = (rem * 10) + (n[indx] - '0');
        result[indx] = rem / den + '0';
        rem %= den;
    }
    result.resize(n.length());

    while (result[0] == '0' && result.length() != 1)
        result.erase(0, 1);

    if (result.length() == 0)
        result = "0";

    return make_pair(result, rem);
}

string BigInteger::toString(long long n)
{
    stringstream ss;
    string temp;

    ss << n;
    ss >> temp;

    return temp;
}

long long BigInteger::toInt(string s)
{
    long long sum = 0;

    for (int i = 0; i < s.length(); i++)
        sum = (sum * 10) + (s[i] - '0');

    return sum;
}

BigInteger BigInteger::average(BigInteger a, BigInteger b)
{
    //cout << "start average\n";
    BigInteger sum = a + b;
    /*BigInteger min;
    if (a <= b)min = a;
    else min = b;
    while (min * BigInteger(2) < sum) {
         min++;
         cout
    }*/
    string s = sum.getNumber();
    s = divide(s, 2).first;
    BigInteger result = BigInteger(s, sum.getSign());
    //cout << "a=" << a.getNumber() << ",b=" << b.getNumber() << "    result=" << result.getNumber() << "\n";
    return result;
}