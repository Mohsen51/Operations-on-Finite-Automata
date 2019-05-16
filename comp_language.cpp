#include "comp_language.h"


using namespace std;

template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}


Comp_language::Comp_language(string name):Automata_determinize(name){

}

void Comp_language::display() const{
	cout <<  endl;
	cout << "2: AUTOMATA COMPLEMANTARY LANGUAGE "  << endl;	
	cout <<  endl;
	cout << "initial state(s):" << endl;
	
	cout << this->_init_states_deterministic << endl;

	cout << "final state(s):" << endl;
	
	
	for(vector<string> ::const_iterator at = this-> _final_states_comp_language.begin(); at != this-> _final_states_comp_language.end(); ++at) {
		cout << *at+" ";  
	}
	cout << endl;

	cout << "transition table:" << endl;
	this->display_complete_dererministic_automaton();

	 //for(vector<string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
     //	cout << *it << endl;
	//}

}

void Comp_language::get_comp_automata(){


	 for(std::map<std::string,std::vector<std::string> >::const_iterator at = this->_transitions_table_determiniaze.begin(); at != this->_transitions_table_determiniaze.end(); ++at) {
	 	
	 	for(std::vector<std::string> ::const_iterator it = this->_final_states_deterministic.begin(); it != this->_final_states_deterministic.end(); ++it) {
	 	if(at->first !=  *it){
	 		this-> _final_states_comp_language.push_back(at->first);	
	 	}

	 }
	}

	this->_final_states_comp_language = this->remove_duplicate_vector(this-> _final_states_comp_language);

}

bool Comp_language::find_letter_in_vector(string index)
{
	//cout << "ind" << index << endl;
	for(vector<string> ::const_iterator at = this->_final_states_comp_language.begin(); at != this->_final_states_comp_language.end(); ++at) {
		//cout << "at " << *at << endl;
		if (index == *at)
			return 1;
	}
	return 0;
}

void Comp_language::read_word()
{
	string word;
	do
	{
		cout << "Please enter a word (type 'end' to quit)" << endl;
		cin >> word;
		if (word!="end")
			cout << recognize_word(word,this->_init_states_deterministic,0) << endl;
	} while (word!="end");
	
}

bool Comp_language::recognize_word(string word, string state, int index)
{
	if (index<=word.size()-1)
	{
		int nbr= (int)word[index]-97; 
		string value=this->_transitions_table_determiniaze[state][nbr];
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