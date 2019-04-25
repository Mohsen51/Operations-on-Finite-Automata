#include "automata.h"
#include<fstream>

template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
}

Automata::Automata() {
		get_data_from_file();
}

void Automata::get_data_from_file() {
	std::string line;
	std::ifstream file;
    file.open("test.txt");

   if(!file.is_open()) {
      std::cout << "error file" << std::endl;
   }
   
   	std::vector<std::string> _tmp_vector;
   	//get line by line 
    getline(file,line);
    this->_nb_transitions_available = atoi(line.c_str());

    getline(file,line);
    this->_nb_states = atoi(line.c_str());

    getline(file,line);
	_tmp_vector.push_back(line.erase(0,2));
    this->_init_states[atoi(&line[0])] = _tmp_vector;
    _tmp_vector.clear();

    getline(file,line);
	_tmp_vector.push_back(line.erase(0,2));
    this->_final_states[atoi(&line[0])] = _tmp_vector;
    _tmp_vector.clear();

	getline(file,line);
    this->_nb_transitions = atoi(line.c_str());
     
    while(getline(file,line)) {
     	this->_transitions.push_back(line);
    }


}

void Automata::display() const{

	std::cout << "initial state(s):" << std::endl;
	
	for(std::map<int,std::vector<std::string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		std::cout << (at->second).front()  << std::endl;
	}

	std::cout << "final state(s):" << std::endl;
	
	
	for(std::map<int,std::vector<std::string> >::const_iterator at = this->_final_states.begin(); at != this->_final_states.end(); ++at) {
		std::cout << (at->second).front()  << std::endl;
	}

	std::cout << "transition table:" << std::endl;
	this->transitions_table();

	 //for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
     //	std::cout << *it << std::endl;
	//}

}


void Automata::transitions_table() const {

	std::map<int,std::vector<std::string> > table;

	// for each state, the algo go trought the _transitions vector to map its transitions  map[state] = [transitions(a),transitions(b)...];
	for(int i=0; i< this->_nb_states; i++) {
		// initialisation of the vector 
		std::vector<std::string> _tmp_transitions;
		for(int i = 0; i < this->_nb_transitions_available; i++) {
			_tmp_transitions.push_back("-");
		}

		for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
		 	//std::cout << "transition" <<*it << std::endl;
		 	 
		 	if(atoi(&(*it)[0])==i and *it != "") {
		 		
		 		if(((_tmp_transitions[int((*it)[1])-97]) != "-")) {
					//std::cout <<"sup" << std::endl;
					_tmp_transitions[int((*it)[1])-97] =  _tmp_transitions[int((*it)[1])-97]+"," + (*it)[2];
					
		 		}
		 		else {
		 			//std::cout <<"=0" << std::endl;
		 			_tmp_transitions[int((*it)[1])-97] = (*it)[2];
		 		}
		 	}

		 	/*for(std::vector<std::string>::const_iterator at = _tmp_transitions.begin(); at != _tmp_transitions.end(); ++at) {
		 	std::cout << *at << std::endl;
		 	}*/
		 	//std::cout << "t0" <<_tmp_transitions[0] << std::endl;
		 	//std::cout << "t1" <<_tmp_transitions[1] << std::endl;

		}

		// map state i to its transition vector 
		table[i] = _tmp_transitions;
		_tmp_transitions.clear();

	}
	display_transition_table(table);

}


void Automata::display_transition_table(std::map< int,std::vector<std::string> > table) const {
	const int nameWidth     = 6;
    const int numWidth      = 8;

    // display banner with available states
	printElement("S", nameWidth);
	for(int i=0; i<this->_nb_transitions_available; i++) {
		printElement(char(97+i), numWidth);
	}
	std::cout << std::endl;

	// printElement is a template (function) to display data with good indentation 
    for(std::map<int,std::vector<std::string> >::const_iterator at = table.begin(); at != table.end(); ++at) {
    		printElement(at->first, nameWidth);
		 	for(std::vector<std::string>::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		printElement(*it, numWidth);
		}
		std::cout << std::endl;
	}

}






