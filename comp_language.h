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
	void read_word(); 
	bool recognize_word(std::string, std::string, int);
	bool find_letter_in_vector(std::string);

protected:
	vector<std::string>  _final_states_comp_language;


};
#endif