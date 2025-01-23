

//#include"bigintegerlibrary.hpp"
#include"mod_operations.hpp"
#include<vector>
static BigInteger q = BigInteger("4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");
//static BigInteger q = BigInteger("3329");
//static BigInteger q = BigInteger("57896044618658097711785492504343953926634992332820282019728792003956564819949");
//static BigInteger q = BigInteger("18446744073709551557");
using namespace std;
class ecpoint {
private:
	BigInteger x;
	BigInteger y;
	bool is_infinity;

    //static string q1 = "4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787";
	//static BigInteger q = BigInteger(q1, 0);

	// r("52435875175126190479447740508185965837690552500527637822603658699938581184513");
	//string r1 = "52435875175126190479447740508185965837690552500527637822603658699938581184513";
	//BigInteger r = BigInteger(r1, 0);
public:
	ecpoint() {
		x = 0;
		y = 0;
		is_infinity=true;
	}
	ecpoint(BigInteger X, BigInteger Y) {
		x = X%q;
		y = Y%q;
		if (X == 0 && Y == 0)
		{
			is_infinity = true;
		}
		else is_infinity = false;
	}
	void Set_x(BigInteger X)
	{
		x = X;
	}

	void Set_y(BigInteger Y)
	{
		y = Y;
	}

	BigInteger Get_x(void) { return x; }
	BigInteger Get_y(void) { return y; }

	static bool is_on_curve(ecpoint& P)
	{
		//Check that y^2 = x^3 + ax + b
		if (P.is_infinity)
			return true;

		BigInteger x_coordinate = P.Get_x();
		BigInteger y_coordinate = P.Get_y();
		//BigInteger y2 = mod_mul(y_coordinate, y_coordinate, q);
		BigInteger y2 = barret(y_coordinate, y_coordinate, q);
		BigInteger left = y2;
		
		//unsigned right = P.x * P.x * P.x + P.ec.a * P.x + P.ec.b;
		//BigInteger right = x_coordinate * x_coordinate * x_coordinate + 4;
		//BigInteger x2 = mod_mul(x_coordinate, x_coordinate, q);
		//BigInteger x3 = mod_mul(x2, x_coordinate, q);
		BigInteger x2 = barret(x_coordinate, x_coordinate, q);
		BigInteger x3 = barret(x2, x_coordinate, q);
		BigInteger right = x3 + 3;
		left = left % q;
		right = right % q;
		cout << "left=" << left.getNumber() << ",right=" << right.getNumber() << "\n";
		return left == right;
	}

	//static ecpoint AddPoints(ecpoint& P1, ecpoint& P2)
	static ecpoint AddPoints(ecpoint& P1, ecpoint& P2)
	{
		if (P1.is_infinity)
			return P2;

		if (P2.is_infinity)
			return P1;

		BigInteger x1 = P1.Get_x();
		BigInteger y1 = P1.Get_y();
		BigInteger x2 = P2.Get_x();
		BigInteger y2 = P2.Get_y();
		cout << "P1(" << x1.getSign() << "+" << x1.getNumber() << "," << y1.getSign() << "+" << y1.getNumber() << ")+";
		cout << "P2(" << x2.getSign() << "+" << x2.getNumber() << "," << y2.getSign() <<"+" << y2.getNumber() << ")=";
		if (x1 == x2 && y1 == y2)
			return ecpoint::DoublePoint(P1);

		if (x1 == x2)
			return ecpoint();

		//BigInteger s = (y2 - y1) / (x2 - x1);
		BigInteger s;
		BigInteger y21, x21;
		/*y21 = y2 - y1;
		x21 = x2 - x1;
		s.setSign(y21.getSign() != x21.getSign());
		y21 = BigInteger(y21.getNumber(), 0);
		x21 = BigInteger(x21.getNumber(), 0);
		BigInteger u, v;
		BigInteger modinv = mod_inv(x2-x1, q, &u, &v);*/
		y21 = mod_sub(y2, y1, q);
		x21 = mod_sub(x2, x1, q);
		BigInteger u, v;
		BigInteger modinv = mod_inv(x21, q, &u, &v);
		u = u % q;
		//cout << "u=" <<u.getSign()<<"+" << u.getNumber() << "\n";
		//s = mod_mul(y2 - y1,u , q);
		s = barret(y21,u , q);
		//s = s % q;
		//cout << "s=" << s.getNumber() << "\n";
		//BigInteger new_x = s * s - x1 - x2;
		//BigInteger new_y = s * (x1 - new_x) - y1;
		//BigInteger s2 = mod_mul(s, s, q);
		BigInteger s2 = barret(s, s, q);
		BigInteger new_x = s2 - x1 - x2;
		BigInteger x_2 = mod_sub(x1, new_x, q);
		//BigInteger sx = mod_mul(x_2, s, q);
		BigInteger sx = barret(x_2, s, q);
		BigInteger new_y = mod_sub(sx, y1, q);
		new_x = new_x % q;
		new_y = new_y % q;
		cout << "(" << new_x.getNumber() << "," << new_y.getNumber() << ")\n";
		return ecpoint(new_x, new_y);
	}

	//static ecpoint DoublePoint(ecpoint& P)
	static ecpoint DoublePoint(ecpoint& P)
	{

		BigInteger x_coordinate = P.Get_x();
		BigInteger y_coordinate = P.Get_y();
		cout << "double P(" << x_coordinate.getNumber() << "," << y_coordinate.getNumber() << ")=";
		//unsigned left = Fq(ec.q, 3) * x * x;//Fq class
		//BigInteger left = 3 * x_coordinate * x_coordinate;
		//BigInteger left = x_coordinate * x_coordinate + x_coordinate * x_coordinate + x_coordinate * x_coordinate;
		//BigInteger xpow = mod_mul(x_coordinate, x_coordinate, q);
		BigInteger xpow = barret(x_coordinate, x_coordinate, q);
		BigInteger left = xpow + xpow + xpow;
		left = left % q;
		//BigInteger s = left / (y_coordinate+y_coordinate);
		BigInteger u, v;
		BigInteger y_2 = mod_add(y_coordinate, y_coordinate, q);
		//BigInteger modinv = mod_inv(y_coordinate + y_coordinate, q, &u, &v);
		BigInteger modinv = mod_inv(y_2, q, &u, &v);
		//cout << "U sign=" << u.getSign() << "u=" << u.getNumber() << "\n";
		u = u % q;
		//BigInteger s = mod_mul(left, u, q);
		BigInteger s = barret(left, u, q);
		s = s % q;
		//cout <<"s sign="<<s.getSign() << "s=" << s.getNumber() << "\n";
		//BigInteger new_x = s * s - x_coordinate - x_coordinate;
		//BigInteger s2= mod_mul(s, s, q);
		BigInteger s2 = barret(s, s, q);
		BigInteger new_x = s2 - x_coordinate - x_coordinate;
        new_x = new_x % q;
		//BigInteger new_y = s * (x_coordinate - new_x) - y_coordinate;
		BigInteger x_2 = mod_sub(x_coordinate, new_x, q);
		//BigInteger sx = mod_mul(x_2, s, q);
		BigInteger sx = barret(x_2, s, q);
		BigInteger new_y = mod_sub(sx , y_coordinate,q);
		new_y = new_y % q;
        cout << "(" << new_x.getNumber() << "," << new_y.getNumber() << ")\n";
		return ecpoint(new_x, new_y);

	}

	static ecpoint ScalarMult(BigInteger k, ecpoint& P)
	{
		ecpoint Result = ecpoint();
		
		//ecpoint Result=P;
		//unsigned i;
		if (P.Get_x() == BigInteger() && P.Get_y() == BigInteger())return P;
		else {
			/*while (k > 0)
			{

				if (k % 2 == 0) Result = DoublePoint(Result);
				else Result = ecpoint::AddPoints(Result, P);
				k = k / 2;
			}
			return Result;
			*/
			ecpoint temp = P;
			if (k == BigInteger())return ecpoint();
			else if(k == BigInteger("1"))return P;
			else if (k == BigInteger("2"))return ecpoint::DoublePoint(P);
			else {
				while (k > BigInteger()) {
					if (k % BigInteger("2") == BigInteger("1")) {
						Result = ecpoint::AddPoints(Result, temp);
					}
					temp = ecpoint::DoublePoint(temp);
					
					k = k / BigInteger("2");
					//cout << "k=" << k.getNumber() << "\n";
				}
				return Result;
			}

		}
	}

	//static vector<ecpoint> point_gen(ecpoint& p0, BigInteger n)
	static vector<ecpoint> point_gen(ecpoint& p0, int n)
	{
		//p0 is base point, n is the number of out points 
		vector<ecpoint>p;
		cout << "start gen\n";
		//BigInteger num = BigInteger();
		int num = 0;
		BigInteger scalar = BigInteger();
		ecpoint mul;
		while (num != n) {
			scalar++;
			cout << "scalar=" << scalar.getNumber() << "\n";
			mul=ecpoint::ScalarMult(scalar, p0);
			BigInteger x = mul.Get_x();
			BigInteger y = mul.Get_y();
			cout << "generate point=(" << x.getNumber() << "," << y.getNumber() << ")  ";
			if (ecpoint::is_on_curve(mul)) {
				num++;
				p.push_back(mul);
				cout << "is on curve\n";
			}
			else {
				cout << "not on curve\n";
			}
			//cout << "1\n";
		}
		cout << "gen sucess\n";
		return p;
	}
};

