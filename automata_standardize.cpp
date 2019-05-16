#include "automata_standardize.h"
#include "automata.h"
#include "automata_determize.h"
#include "comp_language.h"

using namespace std;


template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}


Automata_standardize::Automata_standardize(string name ):Comp_language(name){
	

}

vector<string> Automata_standardize::list_transition_init_state(){
	this->_transitions_table_standardize = this->_transitions_table_determiniaze;
	return this->_transitions_table_standardize[this->_init_states_deterministic];
}


void Automata_standardize::create_state_i(){
	string name = "i";
	
	this->_transitions_table_standardize[name] = this->list_transition_init_state();
}


void Automata_standardize::define_state_i_as_init_state(){
	this->_init_states_standardize = "i";
}

bool Automata_standardize::is_standardize(){
	int tmp = 0;
	// don't need to check mutiple entries because we use CDFA
	  for(map<string,vector<string>  >::const_iterator at = this->_transitions_table_determiniaze.begin(); at != this->_transitions_table_determiniaze.end(); ++at) {
		 	for(vector<string> ::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {

		 		if(*it == this->_init_states_deterministic){
					cout <<"not standardized"<<endl; 
					tmp = 1;
		 		}
		}
		
		
	}
	if( tmp==0){
		this->_init_states_standardize = this->_init_states_deterministic;
		this->_transitions_table_standardize = this->_transitions_table_determiniaze;
		std::cout << "already standardized" << std:: endl;
	}
	return tmp;

}
void Automata_standardize::standardize(){

	this->create_state_i();
	this->define_state_i_as_init_state();
}

void Automata_standardize::display()  {
	cout << "STANDARDIZE AUTOMATA" << endl;

	cout << "initial state(s):" << endl;
	
	cout << this->_init_states_standardize << endl;

	cout << "final state(s):" << endl;
	
	
	for(vector<string> ::const_iterator at = this-> _final_states_comp_language.begin(); at != this-> _final_states_comp_language.end(); ++at) {
		cout << *at+" ";  
	}
	cout << endl;

	cout << "transition table:" << endl;
	this->display_standardize_automaton() ;
}


void Automata_standardize::display_standardize_automaton() {

	const int nameWidth     = 10;
    const int numWidth      = 15;
	cout << "display_standardize_automaton"<<endl;
    // display banner with available states
	printElement("S", nameWidth);
	for(int i=0; i<this->_nb_transitions_available; i++) {
		printElement(char(97+i), numWidth);
	}
	cout << endl;

	// printElement is a template (function) to display data with good indentation 
    for(map<string,vector<string>  >::const_iterator at = this->_transitions_table_standardize.begin(); at != this->_transitions_table_standardize.end(); ++at) {
    		
    		
    		printElement(at->first, nameWidth);
		 	for(vector<string> ::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		string tmp;
		 		tmp = *it;
		 		if(tmp =="")
		 		{
		 			tmp="-";
		 		}
		 		printElement(tmp.erase(0,0), numWidth);
		 		
		}
		cout << endl;
		
	}

}

bool Automata_standardize::find_letter_in_vector(string index)
{
	//cout << "ind" << index << endl;
	for(vector<string> ::const_iterator at = this->_final_states_comp_language.begin(); at != this->_final_states_comp_language.end(); ++at) {
		//cout << "at " << *at << endl;
		if (index == *at)
			return 1;
	}
	return 0;
}

void Automata_standardize::read_word()
{
	string word;
	do
	{
		cout << "Please enter a word (type 'end' to quit)" << endl;
		cin >> word;
		cout << recognize_word(word,this->_init_states_standardize,0) << endl;
	} while (word!="end");
	
}

bool Automata_standardize::recognize_word(string word, string state, int index)
{
	if (index<=word.size()-1)
	{
		int nbr= (int)word[index]-97; 
		string value=this->_transitions_table_standardize[state][nbr];
		if (value == "" && !find_letter_in_vector(value))
		{ 
			return 0;
		}
		else if (find_letter_in_vector(value) && index==word.size()-1)
		{
			return 1;
		}
		else
		{
			return recognize_word(word,value,index+1);
		}
		
	}
	else
	{
		return 0;
	}
	
}