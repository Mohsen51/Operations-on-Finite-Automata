#ifndef AUTOMATA_H
#define AUTOMATA_H

#include<fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <regex>
#include <string>

class Automata{
	public:
		Automata();

		void display() const;
		void transitions_table() ;
		
		

	private:
		int _nb_transitions_available;
		int _nb_states;
		std::map<int, std::vector<std::string> >  _init_states;
		std::map<int, std::vector<std::string> >  _final_states;
		int _nb_transitions;
		std::vector<std::string> _transitions;
		std::map<int,std::vector<std::vector<std::string> > > _transitions_table;


		void get_data_from_file();
		void display_transition_table( ) const;
		void asynchronous_to_synchronous();
		std::string recursive(std::string, std::map<int,std::vector<std::vector<std::string> > > ,	std::vector<std::string>&,int,int ) const;

		
};

#endif