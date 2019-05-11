#ifndef AUTOMATA_H
#define AUTOMATA_H

#include<fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <regex>
#include <string>
#include <algorithm>

class Automata{
	public:
		Automata();

		void display() const;
		void transitions_table() ;
		bool is_an_asynchronous_automaton() const;
		void asynchronous_to_synchronous();
		void determinaze();	
		void display_complete_dererministic_automaton() const;
		void synchronous_transition_table() ;
		bool is_complete() const ;
		bool is_deterministic() const;
		void complete();

	private:
		int _nb_transitions_available;
		int _nb_states;
		std::map<int, std::vector<std::string> >  _init_states;
		std::map<int, std::vector<std::string> >  _final_states;
		int _nb_transitions;
		std::vector<std::string> _transitions;
		std::map<int,std::vector<std::vector<std::string> > > _transitions_table;
		std::map<std::string,std::vector<std::string> > deter;



		void get_data_from_file();
		void display_transition_table( ) const;
		void rec(std::vector<std::string> ,int ,std::map<int,std::vector<std::vector<std::string>  > > ,std::map<std::string,std::vector<std::string>  > & ); 
		
		void recursive(int ,int,int ,std::vector<std::string>,std::vector<std::string>&) const;

		
};

#endif