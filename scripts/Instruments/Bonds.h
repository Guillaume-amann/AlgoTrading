#include <iostream>
#include <cmath>			//need for pow() function
#include <ctime>			//need for date manipulation
using namespace std;

class Bond {
private:
	string issuer;			//Company or governemnt issuing the bond
	double faceValue;		//Face value or principal issued
	double coupon;			//Coupon rate in %
	string issueDate;		//Date of Issue "YYYY-MM-DD"
	string maturityDate;		//Date of maturity "YYYY-MM-DD"
	double frequency;		//Payment frequency (0.5: every 2y, 1: annually, 2: semi-annually, ...)
	double bondYield;       	//Yield to maturity
	double bondDuration;    	//Duration of the bond
	double bondConvexity;   	//Convexity of the bond

	double maturity(const string& startDate, const string& endDate) {
		struct tm start ={}, end ={};
		strptime(startDate.c_str(), "%Y-%m-%d", &start);
		strptime(endDate.c_str(), "%Y-%m-%d", &end);

		time_t start_time = mktime(&start);
		time_t end_time = mktime(&end);

		double seconds = difftime(end_time, start_time);
		return seconds/(3600*24*365.25);
	}

	void calculateValues(double marketPrice, double discountRate=0.0325) {
        bondYield = yield(marketPrice);
        bondDuration = duration(discountRate);
        bondConvexity = convexity(discountRate);
    }

public:
	Bond(const string& name, double fV, double c, const string& date1, const string& date2, double f = 1, double marketPrice = 0) : issuer(name), faceValue(fV), coupon(c), issueDate(date1), maturityDate(date2), frequency(f) {
		if (marketPrice > 0) {
			calculateValues(marketPrice);
        	} else {
			bondYield = 0;
			bondDuration = 0;
			bondConvexity = 0;
        	}
	}

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

	double yield(double marketPrice) {
        	double couponPayment = (coupon * faceValue) / frequency;
        	double years = maturity(maturityDate, issueDate);
        	return (couponPayment + (faceValue - marketPrice) / years) / ((faceValue + marketPrice) / 2);
    	}

	double duration(double discountRate) {
		double couponPayment = (coupon * faceValue) / frequency;
		double years = maturity(maturityDate, issueDate);
		int nbrPayments = static_cast<int>(years * frequency);

		double duration = 0.0;
		for (int i = 1; i <= nbrPayments; ++i) {
				double presentValue = couponPayment / pow(1 + discountRate / frequency, i);
				duration += (i / frequency) * presentValue;
		}
		duration += (faceValue / pow(1 + discountRate / frequency, nbrPayments)) * (nbrPayments / frequency);
		return duration / (price(discountRate)); // Macaulay Duration
	}

    	double convexity(double discountRate) {
        	double couponPayment = (coupon * faceValue) / frequency;
        	double years = maturity(maturityDate, issueDate);
        	int nbrPayments = static_cast<int>(years * frequency);

        	double convexity = 0.0;
        	for (int i = 1; i <= nbrPayments; ++i) {
            		convexity += (couponPayment / pow(1 + discountRate / frequency, i)) * (i * (i + 1));
        	}
        	convexity += (faceValue / pow(1 + discountRate / frequency, nbrPayments)) * (nbrPayments * (nbrPayments + 1));
        	return convexity / (price(discountRate) * pow((1 + discountRate / frequency), 2));
    	}

    	string getIssuer() { return issuer; }
    	double getFaceValue() { return faceValue; }
   	double getCoupon() { return coupon; }
    	string getIssueDate() { return issueDate; }
    	string getMaturityDate() { return maturityDate; }
    	double getFrequency() { return frequency; }
    	double getBondYield() { return bondYield; }
    	double getBondDuration() { return bondDuration; }
    	double getBondConvexity() { return bondConvexity; }
};
