#ifndef AUTOMATA_DETERMINIZE_H
#define AUTOMATA_DETERMINIZE_H


#include<fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <regex>
#include <string>
#include <algorithm>
#include "automata.h"


class Automata_determinize: public Automata{
public:
	Automata_determinize(string );
	void display() const;
	void display_complete_dererministic_automaton() const;
	void complete();
	void determinaze();	
	bool is_deterministic();
	void rec(std::vector<std::string> ,std::map<std::string,std::vector<std::string>  > & );
	void define_new_init_final_states();
	void adapt_transition_table_if_already_deterministic();
	void read_word(); 
	bool recognize_word(std::string, std::string, int);
	bool find_letter_in_vector(std::string);

protected:
	std::string   _init_states_deterministic;
	vector<std::string>  _final_states_deterministic;
	std::map<std::string,std::vector<std::string> > _transitions_table_determiniaze;
	
};

#endif