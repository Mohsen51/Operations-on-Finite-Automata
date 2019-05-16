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

using namespace std;
class Automata{
	public:
		Automata(string);

		void display() const;
		void transitions_table() ;
		bool is_an_asynchronous_automaton() const;
		void asynchronous_to_synchronous();
		
		
		void synchronous_transition_table() ;
		bool is_complete() const ;
		


		std::vector<std::string> split_string(std::string );
		std::string concate_vector(std::vector<std::string>);
		std::vector<std::string> remove_duplicate_vector(std::vector<std::string>  );
		std::string remove_duplicate_string(std::string  );

	private:
		void get_data_from_file(string);
		void display_transition_table( ) const;
		void recursive(int ,int ,int ,vector<string> _transitions,vector<string> &) const;
		
		

	protected:
		int _nb_transitions_available;
		int _nb_states;
		std::vector<std::string>   _init_states;
		std::vector<std::string>   _final_states;
		int _nb_transitions;
		std::vector<std::string> _transitions;
		std::map<int,std::vector<std::vector<std::string> > > _transitions_table;
		

		
};



#endif