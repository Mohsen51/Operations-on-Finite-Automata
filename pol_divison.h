#ifndef POL_DIVISION_H
#define POL_DIVISION_H

#include <vector>
#include <string>

using namespace std;


class Polynom {

public:
	void transform_binary_message_to_polynom();

private:
	char message;

	vector<int> init_dividand_index;
	vector<int> dividand_index;
	vector<int> diviseur_index;
	vector<int> quotient;
	vector<int> rest;


	

};

#endif