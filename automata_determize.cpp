#include "automata_determize.h"

using namespace std;

template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

 Automata_determinize::Automata_determinize(string name):Automata(name){

}

void Automata_determinize::display() const {
	cout << "initial state(s):" << endl;
	
	cout << this->_init_states_deterministic << endl;

	cout << "final state(s):" << endl;
	

	for(vector<string> ::const_iterator at = this->_final_states_deterministic.begin(); at != this->_final_states_deterministic.end(); ++at) {
		cout << *at + " ";
	}
		cout << endl;

	cout << "transition table:" << endl;
	this->display_complete_dererministic_automaton();
}

void Automata_determinize::display_complete_dererministic_automaton() const {
	const int nameWidth     = 6;
    const int numWidth      = 15;
	cout << "display_complete_dererministic_automaton"<<endl;
    // display banner with available states
	printElement("S", nameWidth);
	for(int i=0; i<this->_nb_transitions_available; i++) {
		printElement(char(97+i), numWidth);
	}
	cout << endl;

	// printElement is a template (function) to display data with good indentation 
    for(map<string,vector<string>  >::const_iterator at = this->_transitions_table_determiniaze.begin(); at != this->_transitions_table_determiniaze.end(); ++at) {
    		
    		
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



void Automata_determinize::complete() {
	int i = 0;
	 for(map<string,vector<string>  >::iterator at = this->_transitions_table_determiniaze.begin(); at != this->_transitions_table_determiniaze.end(); ++at) {
		 	for(vector<string> ::iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		string tmp;
		 		tmp = *it;
		 		if(tmp =="")
		 		{
		 			i = 1;
		 			*it = "P";
		 		}
		 
		}
	}

	if(i == 1){
		for(int j=0;j<this->_nb_transitions_available;j++){
			this->_transitions_table_determiniaze["P"].push_back("P");
		}
		
	}
}


void Automata_determinize::determinaze(){
	vector<string>  states;
	map<string,vector<string>  > tmp_map;
	cout <<"a"<<this->_init_states[_init_states.begin()->first][0]<<"a"<< endl;

	rec(this->_init_states[_init_states.begin()->first],tmp_map);

	this->_transitions_table_determiniaze =  tmp_map;

	this->define_new_init_final_states();


}

void Automata_determinize::define_new_init_final_states(){
	//init
	// define new input state
	
	string init_states_concate = this->_init_states[_init_states.begin()->first][0];
	this->_init_states_deterministic = init_states_concate;
	//////
	


	//final

	//split final state

	std::vector<std::string> tmp_vector;
	tmp_vector = this->split_string(this->_final_states[_final_states.begin()->first][0]);
	

	//test matching
	for(map<string,vector<string>  >::const_iterator at = this->_transitions_table_determiniaze.begin(); at != this->_transitions_table_determiniaze.end(); ++at) {
	 	std::vector<std::string> tmp_index_split = this->split_string(at->first);
	 		for(int i=0;i<tmp_vector.size();i++){
	 			for(int j=0;j<tmp_index_split.size();j++){
	 				if(tmp_vector[i]==tmp_index_split[j]){
	 					this->_final_states_deterministic.push_back(tmp_vector[i]);
	 				}
	 			}
	 		}
	 	

	} 	

	this->_final_states_deterministic = this->remove_duplicate(this->_final_states_deterministic);
		

			
}

void Automata_determinize::rec(vector<string> states,std::map<string,std::vector<std::string>  > &table ){
	
	string states_concate = this->concate_vector(states);
	cout << "a" << states_concate << "a"<< endl;
	

	vector<string> tmp;

	//adiditon of states
	for(int j=0;j<this->_nb_transitions_available;j++){
		string concate ="";
		for(int i=0;i<states.size();i++){
			
			for(int h=0;h<this->_transitions_table[atoi(states[i].c_str())][j].size();h++){
				concate+=this->_transitions_table[atoi(states[i].c_str())][j][h];
			}
			//cout << concate << endl;
			

		}
		//remove duplicate
		/*std::sort(concate.begin(), concate.end());
		concate.erase(std::unique(concate.begin(), concate.end()), concate.end());	*/
		
		tmp.push_back(concate);
	}
	
	
	
	
	table[states_concate] = tmp;

	
	for(int j=0;j<this->_nb_transitions_available;j++){
		vector<string> tmp2;
		for(int i=0;i<states.size();i++){
			for(int h=0;h<this->_transitions_table[atoi(states[i].c_str())][j].size();h++){
				tmp2.push_back(this->_transitions_table[atoi(states[i].c_str())][j][h]);
			}

			
		}
		
		if(table[states_concate][j]!="" && !(table.count(table[states_concate][j]) > 0)){
			rec(tmp2,table);
		}

	
	}

		
		
		
	

	


}



