#include <iostream>
#include <string>
#include <cmath>			//need for pow() function
#include <ctime>			//need for date manipulation

class Bond {
private:
	std::string issuer;		//Company or governemnt issuing the bond
	double faceValue;		//Face value or principal issued
	double coupon;			//Coupon rate in %
	std::string issueDate;		//Date of Issue "YYYY-MM-DD"
	std::string maturityDate;	//Date of maturity "YYYY-MM-DD"
	double frequency;		//Payment frequency (0.5: every 2y, 1: annually, 2: semi-annually, ...)
	
	double maturity(const std::string& startDate, const std::string& endDate) {
		struct std::tm start ={}, end ={};
		strptime(startDate.c_str(), "%Y-%m-%d", &start);
		strptime(endDate.c_str(), "%Y-%m-%d", &end);

		std::time_t start_time = std::mktime(&start);
		std::time_t end_time = std::mktime(&end);

		double seconds = std::difftime(end_time, start_time);
		return seconds/(3600*24*365.25);
	}

public:
	Bond(std::string name, double fV, double c, std::string date1, std::string date2, double f):
		issuer(name), faceValue(fV), coupon(c), issueDate(date1), maturityDate(date2), frequency(f) {}

	double price(double discountRate) {
		double couponPayment = (coupon*faceValue)/frequency;
		double years = maturity(maturityDate, issueDate);
		int nbrPayments = static_cast<int>(years*frequency);

		double price = 0.0;
		for (int i=1; i<= nbrPayments; ++i) {
			price+=couponPayment/pow(1+discountRate/frequency, i);
		}

		price += faceValue / pow(1+ discountRate / frequency, nbrPayments);
		return price;
	}
};
