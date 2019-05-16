#ifndef AUTOMATA_STANDARDIZE_H
#define AUTOMATA_STANDARDIZE_H

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
#include "comp_language.h"


using namespace std;

class Automata_standardize: public Comp_language{
public:
	Automata_standardize(string);
	vector<string> list_transition_init_state();
	void create_state_i();
	void define_state_i_as_init_state();
	bool is_standardize();
	void standardize();

	void display();
	void display_standardize_automaton() ;



protected:
	std::map<std::string,std::vector<std::string> > _transitions_table_standardize;
	std::string   _init_states_standardize;
};


#endif