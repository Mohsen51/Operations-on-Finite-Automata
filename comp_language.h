#ifndef COMP_LANGUAGE_H
#define COMP_LANGUAGE_H


#include<fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <regex>
#include <string>
#include <algorithm>
#include "automata.h"
#include "automata_determize.h"

class Comp_language : public Automata_determinize{
public:
	Comp_language(string );
	void display() const;
	void get_comp_automata();

private:
	vector<std::string>  _final_states_comp_language;
	std::map<std::string,std::vector<std::string> > _transitions_table_comp_language;
};



#endif