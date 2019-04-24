#include "automata.h"
#include<fstream>



Automata::Automata(){
		get_data_from_file();
}

void Automata::get_data_from_file()
{
	std::string line;
	std::ifstream file;
    file.open("test.txt");

   if(!file.is_open()) {
      std::cout << "erro file" << std::endl;
   }
   
   	std::vector<std::string> _tmp_vector;
    getline(file,line);
    this->_nb_transitions_possible = atoi(line.c_str());
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
	
	std::string tmp ="";
	for(std::map<int,std::vector<std::string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		std::cout << (at->second).front()  << std::endl;
	}

	std::cout << "final state(s):" << std::endl;
	
	
	for(std::map<int,std::vector<std::string> >::const_iterator at = this->_final_states.begin(); at != this->_final_states.end(); ++at) {
		std::cout << (at->second).front()  << std::endl;
	}



	std::cout << "transitions tables:" << std::endl;
	this->transitions_table();

	 //for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
     //	std::cout << *it << std::endl;
	//}

}


void Automata::transitions_table() const {

	std::map<int,std::vector<std::string> > table;

	


	for(int i=0; i< this->_nb_states; i++)
	{
		//std::cout <<"i"<< i << std::endl;
		std::string  array[] = {"-","-"};
		std::vector<std::string> _tmp_transitions(std::begin(array),std::end(array));

		for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
		 	//std::cout << "transition" <<*it << std::endl;
		 	
		 	 
		 	if(atoi(&(*it)[0])==i and *it != "")
		 	{
		 		
		 		if(((_tmp_transitions[int((*it)[1])-97]) != "-"))
				{
					//std::cout <<"sup" << std::endl;
					_tmp_transitions[int((*it)[1])-97] =  _tmp_transitions[int((*it)[1])-97]+"," + (*it)[2];
					
		 		}
		 		else
		 		{
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

		table[i] = _tmp_transitions;
		_tmp_transitions.clear();
	}

	display_transition_table(table);

}


void Automata::display_transition_table(std::map<int,std::vector<std::string> > table) const{
	std::string banner ="S";
	for(int i=0; i< this->_nb_transitions_possible; i++)
	{
		banner = banner + "   " + char(97+i);
	}
	std::cout << banner  << std::endl;

	for(std::map<int,std::vector<std::string> >::const_iterator at = table.begin(); at != table.end(); ++at) {
		 	
		 	std::string tmp = std::to_string(at->first);
		 	std::string value;
		 	for(std::vector<std::string>::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 	tmp = tmp + "   " + *it ;

		}

		std::cout << tmp  << std::endl;
	}

}






