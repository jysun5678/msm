//#include "bigintegerlibrary.hpp"
//#include"mod_operations.hpp"
//#include"ec_point.hpp"
#include "msm.hpp"
//using namespace std;
//BigInteger q = BigInteger("4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");
int main() {
   /* string a, b;
    cout << "test add, input a, b: ";
    cin >> a >> b;
    //cin >> a;
    //b = "21";
    // 创建 BigInteger 对象
    BigInteger num1(a);
    BigInteger num2(b);
    //BigInteger num2("21");
    // 使用 operator+ 进行加法
    BigInteger sum = num1 + num2;  // 调用 BigInteger::operator+(BigInteger)

    // 输出结果
    if (sum.getSign())cout << "Sum:-" << sum.getNumber() << endl;
    else cout << "Sum: " << sum.getNumber() << endl; // 输出加法结果

 
    BigInteger mul = num1 * num2;
    // 输出结果
    if (mul.getSign())cout << "mul:-" << mul.getNumber() << endl;
    else cout << "mul:" << mul.getNumber() << endl; // 输出乘法结果

    BigInteger div = num1 / num2;
    // 输出结果
    if (div.getSign())cout << "div:-" << div.getNumber() << endl;
    else cout << "div:" << div.getNumber() << endl;

    BigInteger res = num1 % num2;
    // 输出结果
    if (res.getSign())cout << "res:-" << res.getNumber() << endl;
    else cout << "res:" << res.getNumber() << endl;
    BigInteger u,  v;
    BigInteger modinv =  mod_inv(num1, num2, &u, &v);
    // 输出结果
    u = u % num2;
    if (modinv.getNumber() == "1") {
        if (u.getSign())cout << "modinv:-" << u.getNumber() << endl;
        else cout << "modinv:" << u.getNumber() << endl;
    }*/
    //test msm---------------------------
    /*string a, b,c,d;
    cout << "test point add, input a, b,c,d: ";
    cin >> a >> b >> c >> d;

    BigInteger num1(a);
    BigInteger num2(b);
    BigInteger num3(c);
    BigInteger num4(d);
    ecpoint p1 = ecpoint::ecpoint(num1, num2);
    ecpoint p2 = ecpoint::ecpoint(num3, num4);
    ecpoint p3=ecpoint::AddPoints(p1, p2);
    BigInteger x = p3.Get_x();
    BigInteger y = p3.Get_y();
    cout << "pointadd=(" << x.getNumber() << "," << y.getNumber() << ")" << endl;*/

    //test msm-----------------------------
    //Check that y^2 = x^3 + 4
    string a, b;
    cout << "choose base point on y^2=x^3+3: ";
    cin >> a >> b;
    BigInteger num1(a);
    BigInteger num2(b);
    ecpoint p0 = ecpoint::ecpoint(num1, num2);
    while (!ecpoint::is_on_curve(p0)) {
        cout << "wrong point! Input again:";
        cin >> a >> b;
        BigInteger num1(a);
        BigInteger num2(b);
        ecpoint p0 = ecpoint::ecpoint(num1, num2);
    }
    
    cout << "choose the number of sclars:";

    int n;
    cin >> n;
    vector<ecpoint> point = ecpoint::point_gen(p0, n);
    //generate sclars
    vector<BigInteger>scalar;
    for (int i = 1; i <= n; i++) {
        scalar.push_back(BigInteger(i));
    }
    ecpoint result=pippenger(point, scalar);
    BigInteger x = result.Get_x();
    BigInteger y = result.Get_y();
    cout << "msm rsult=(" << x.getNumber() << "," << y.getNumber() << ")" << endl;

    
    return 0;
}
