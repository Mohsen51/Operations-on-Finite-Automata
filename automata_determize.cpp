#include "automata_determize.h"

using namespace std;

template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

 Automata_determinize::Automata_determinize(string name):Automata(name){

}

void Automata_determinize::display() const {

	cout <<  endl;
	cout << "1: AUTOMATA DETERMINISTIC "  << endl;	
	cout <<  endl;
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
	const int nameWidth     = 10;
    const int numWidth      = 15;

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

bool Automata_determinize::is_deterministic() {
	int i=0;
	if(_init_states.size()>1){
		i=1;
		cout <<" not deterministic because of mutiple entries"<< endl;
	}
	int j;
	for(map<int,vector<vector<string> > >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
			j = 0;
		 	for(vector<vector<string> >::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		string tmp = "";
		 		for(vector<string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 			tmp += *et+" ";
		 		}
		 		
		 		if( tmp.size()>2)
		 		{
		 			i=1;
		 			cout << " not deterministic because of mutiple transitons possible for state " << at->first<< " transition "<< char(97+j)<< endl;
		 		}
		 	j++;	
		}
		
	}

	if(i==0){
			std::cout << "already determinized" << std:: endl;
			this->adapt_transition_table_if_already_deterministic();
	}
	return i;

}

void Automata_determinize::adapt_transition_table_if_already_deterministic(){

		this->_final_states_deterministic = this->_final_states;
		this->_init_states_deterministic = this->_init_states[0];


		for(map<int,vector<vector<string> > >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {

			vector<string> tmp_vec;
			for(vector<vector<string> >::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
	 		string tmp = "";
	 		string value = "";
	 		for(vector<string>::const_iterator et = it->begin(); et != it->end(); ++et){
	 			tmp += *et+" ";
	 			value = *et;
	 		}
	 		if(tmp =="")
	 		{
	 			string space = "_";
	 			tmp_vec.push_back(space);
	 		}
	 		else{
	 			tmp_vec.push_back(value);
	 		}
		 	
	 			
		 	this->_transitions_table_determiniaze[to_string(at->first)] = tmp_vec;
		 	tmp.clear();
	 			}
	
			
		}
}

void Automata_determinize::determinaze(){
	vector<string>  states;
	map<string,vector<string>  > tmp_map;
	

	rec(this->_init_states,tmp_map);

	this->_transitions_table_determiniaze =  tmp_map;

	this->define_new_init_final_states();
	


}

void Automata_determinize::define_new_init_final_states(){
	//init
	// define new input state

	string init_states_concate = this->concate_vector(this->_init_states);
	this->_init_states_deterministic = init_states_concate;
	//////
	


	//final

	//split final state
	std::vector<std::string> tmp_vector;
	tmp_vector = this->split_string(this->_final_states[0]);

	

	//test matching
	for(map<string,vector<string>  >::const_iterator at = this->_transitions_table_determiniaze.begin(); at != this->_transitions_table_determiniaze.end(); ++at) {
	 	std::vector<std::string> tmp_index_split = this->split_string(at->first);
	 		for(int i=0;i<tmp_vector.size();i++){
	 			for(int j=0;j<tmp_index_split.size();j++){
	 				if(tmp_vector[i]==tmp_index_split[j]){
	 					this->_final_states_deterministic.push_back(at->first);
	 				}
	 			}
	 		}
	 	

	} 	


	this->_final_states_deterministic = this->remove_duplicate_vector(this->_final_states_deterministic);
		
	
			
}

void Automata_determinize::rec(vector<string> states,std::map<string,std::vector<std::string>  > &table ){
	
	string states_concate = this->concate_vector(states);
	states_concate = this->remove_duplicate_string(states_concate);
	

	vector<string> tmp;

	//adiditon of states
	for(int j=0;j<this->_nb_transitions_available;j++){
		string concate ="";
		for(int i=0;i<states.size();i++){
			
			for(int h=0;h<this->_transitions_table[atoi(states[i].c_str())][j].size();h++){
				concate+=this->_transitions_table[atoi(states[i].c_str())][j][h];
				concate = this->remove_duplicate_string(concate);
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

bool Automata_determinize::find_letter_in_vector(string index)
{
	//cout << "ind" << index << endl;
	for(vector<string> ::const_iterator at = this->_final_states_deterministic.begin(); at != this->_final_states_deterministic.end(); ++at) {
		//cout << "at " << *at << endl;
		if (index == *at)
			return 1;
	}
	return 0;
}

void Automata_determinize::read_word()
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

bool Automata_determinize::recognize_word(string word, string state, int index)
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

