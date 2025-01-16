#include"msm.hpp"
//#include"ec_point.hpp"
//#include<vector>
ecpoint pippenger(vector<ecpoint>point, vector<BigInteger>scalar) {
	cout << "start pippenger\n";
	const unsigned n = scalar.size();
	cout << "n=" << n<<","<<point.size()<<"\n";
	const unsigned b = 32, c = 4, k = b / c;
	const unsigned mask = (1 << c) - 1;
	vector<unsigned>scalar_matrix;
	vector<vector<ecpoint>> Bucketpoints(mask);
	Bucketpoints.reserve(mask);
	int a_ij,a;
	BigInteger t;
	ecpoint bucketagg,temp;
	vector<ecpoint> agg_result;
	ecpoint final_result=ecpoint();
	ecpoint temp_result = ecpoint();
	vector<BigInteger>div_scalar(k);
	BigInteger k1 = BigInteger("16");
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {		
			BigInteger x = point[j].Get_x();
			BigInteger y = point[j].Get_y();
			//cout << "point=(" << x.getNumber() << "," << y.getNumber() << "),scalar="<< scalar[j].getNumber()<<"\n";
		
			t = (scalar[j] >> (c * i));
			//a = stoi(t.getNumber());
			t = t % k1;
			//t = scalar[0];
			a = stoi(t.getNumber());
			//cout << "a=" << a;
			//a_ij = (scalar[i] >> c * i) & mask;
			a_ij =a & mask;
			scalar_matrix.push_back(a_ij);
			if (a_ij != 0) Bucketpoints[a_ij-1].push_back(point[j]);
		}
        //bucket aggregation
	    for (size_t m = 0; m < mask; m++) {
		     //size_t bucket_size = Bucketpoints[m].size();
			size_t bucket_size;
			if (!Bucketpoints[m].empty())bucket_size = Bucketpoints[m].size();
			else bucket_size = 0;
		     /*for (size_t k = 1; k < bucket_size; k++) {
			     Bucketpoints[m][0] = ecpoint::AddPoints(Bucketpoints[m][0], Bucketpoints[m][k]);
		     }*/
			 if (bucket_size>1) {
				 for (size_t k = 1; k < bucket_size; k++) {
					// cout << "cs>1!\n";
					 Bucketpoints[m][0] = ecpoint::AddPoints(Bucketpoints[m][0], Bucketpoints[m][k]);
				 }
			 }
			 
	     }
		//Triangle sum
		//bucketagg = Bucketpoints[mask - 1][0];
		//temp = Bucketpoints[mask - 1][0];
		if (!Bucketpoints[mask - 1].empty()) {
			bucketagg = Bucketpoints[mask - 1][0];
			temp = Bucketpoints[mask - 1][0];
		}
		else {
			bucketagg = ecpoint();
			temp = ecpoint();
		}
		for (int s = mask - 2; s >= 0; s--) {
			if (!Bucketpoints[s].empty()) {
				BigInteger x_temp = temp.Get_x();
				BigInteger y_temp = temp.Get_y();
				//cout <<"s="<<s << "temp=(" << x_temp.getNumber() << "," << y_temp.getNumber() << ")\n";
				BigInteger sx_temp = Bucketpoints[s][0].Get_x();
				BigInteger sy_temp = Bucketpoints[s][0].Get_y();
				temp = ecpoint::AddPoints(Bucketpoints[s][0],temp);
				//cout << "after add=" << "s=(" << sx_temp.getNumber() << "," << sy_temp.getNumber() << ")\n";
				bucketagg= ecpoint::AddPoints(bucketagg, temp);
			}
		}
		
		agg_result.push_back(bucketagg);
		//Bucketpoints.clear();
		for (auto& bucket : Bucketpoints) {
			bucket.clear();
		}
	}
	//bucket*4^i
	//cout << "agg_size=" << agg_result.size() << "\n";
	//for (int i = 0; i < k; i++) {
	for (int i = 0; i < agg_result.size(); i++) {
		div_scalar[i] = BigInteger(int(pow(4, i)));
		BigInteger x = agg_result[i].Get_x();
		BigInteger y = agg_result[i].Get_y();
		//cout << "agg=(" << x.getNumber() << "," << y.getNumber() << ")" ;
		BigInteger k2 = div_scalar[i];
		//cout << "div=" << k2.getNumber() ;
		temp_result = ecpoint::ScalarMult(div_scalar[i], agg_result[i]);
		final_result = ecpoint::AddPoints(temp_result, final_result);
	}
	cout << "finish pippenger\n";
	return final_result;
}