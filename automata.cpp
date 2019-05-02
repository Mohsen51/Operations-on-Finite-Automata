#include "automata.h"


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
     std::cout << "data in memory" << std::endl;

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
	this->display_transition_table();

	 //for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
     //	std::cout << *it << std::endl;
	//}

}


void Automata::transitions_table()  {

	std::vector<std::vector<std::string> > table(this->_nb_transitions_available, std::vector<std::string> (1, "-"));
	 
	// for each state, the algo go trought the _transitions vector to map its transitions  map[state] = [transitions(a),transitions(b)...];
	for(int i=0; i< this->_nb_states; i++) {

		for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
		 //	std::cout << "transition" <<*it << std::endl;
		 	
		 	if((atoi(&(*it)[0])==i) && (*it != "")) {		
		 		if(it->at(1) == '*') {	
		 			for(int j = 0; j < this->_nb_transitions_available; j++) {
		 			std::string save = std::string("(") + (*it)[2] + std::string(")");

		 			table[j].push_back(save);
		 			}
				 }
		 		else{
		 			std::string save = std::string("") + (*it)[2] + std::string("");
		 			table[int((*it)[1])-97].push_back(save);
			 	}

			 		
		 		
		 	}

		}
	
		// map state i to its transition vector 
		
		this->_transitions_table[i] = table;
		for(int x=0;x<this->_nb_transitions_available;x++){
			table[x].clear();
		}
	

	  

	}

}	

void Automata::display_transition_table() const {
	const int nameWidth     = 5;
    const int numWidth      = 20;
	std::cout << "disply"<<std::endl;
    // display banner with available states
	printElement("S", nameWidth);
	for(int i=0; i<this->_nb_transitions_available; i++) {
		printElement(char(97+i), numWidth);
	}
	std::cout << std::endl;

	// printElement is a template (function) to display data with good indentation 
    for(std::map<int,std::vector<std::vector<std::string> > >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
    		printElement(at->first, nameWidth);
		 	for(std::vector<std::vector<std::string> >::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		std::string tmp = "";
		 		for(std::vector<std::string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 			tmp += *et;
		 		}
		 		if(tmp =="")
		 		{
		 			tmp="-";
		 		}
		 		printElement(tmp.erase(0,0), numWidth);
		 		
		}
		std::cout << std::endl;
	}

}

///////////// only for asynchronous automata ///////////////////

void Automata::asynchronous_to_synchronous(){
	// replace epsilon transition by its real value
	int i=0;
	int j=0;
	int h=0;
	std::vector<std::string> tmp_vec;
	std::vector<std::vector<std::string> > tmp(this->_nb_transitions_available, std::vector<std::string> (1, "-"));
	 for(std::map<int,std::vector<std::vector<std::string> > >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
    		
		 	for(std::vector<std::vector<std::string> >::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 			for(std::vector<std::string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 				if(j==1){
							std::cout << i <<":"<<"b"<< std::endl;
		 				}
		 				else {
		 					std::cout << i <<":"<< "a"<< std::endl;
		 				}
		 				std::cout << "DATA in"<< *et<< std::endl;
		 				
		 				this->_transitions_table[i][j][h] = recursive (*et,this->_transitions_table ,tmp_vec,j,h); 
		 				
		 				++h;
		 				}	
		 				h=0;


					//remove duplicate character

				/*	for(int y=0;y<this->_transitions_table[i][j].length();y++) {
						for(int z=0;z<this->_transitions_table[i][j].length();z++){
							if((z != y) && this->_transitions_table[i][j][z] == this->_transitions_table[i][j][y]){
								this->_transitions_table [i][j].erase(z);
							}
						}
					}*/

					//remove unexpected character
				/*	if(std::regex_search(this->_transitions_table[i][j], std::regex(",\\([0-9]\\)"))){
			 			this->_transitions_table[i][j] =  std::regex_replace(this->_transitions_table[i][j] , std::regex(",\\([0-9]\\)"), "");
			 		}
			 		else {
			 			if(std::regex_match(this->_transitions_table [i][j], std::regex("\\([0-9]\\)"))){
			 			this->_transitions_table[i][j] = std::regex_replace(this->_transitions_table[i][j] , std::regex("\\([0-9]\\)"), "-");
				 		}
				 		else	{
				 		this->_transitions_table[i][j] = std::regex_replace(this->_transitions_table[i][j] , std::regex("\\([0-9]\\)"), "");
				 		}
				 	}*/
		 			
					 		for(std::vector<std::string>::const_iterator et = tmp_vec.begin(); et != tmp_vec.end(); ++et){
					 			//if(!(std::regex_search(*et, std::regex("\\([0-9]\\)"))))
					 			this->_transitions_table[i][j].push_back(*et);
					 		}
					 	
					 
		 		
					j++;
					tmp_vec.clear();
				}
			i++;
			j=0;
		}

	}
/////////////////////////////////////////////////////




std::string Automata::recursive(std::string line, std::map<int,std::vector<std::vector<std::string> > > table,std::vector<std::string> &tmp_vec,int j,int h) const {
	std::smatch m;
	int tmp = 0;
	int &x = tmp;

	if( std::regex_search(line,m, std::regex("\\([0-9]\\)"))) {
		
		/*std::string value_to_replace;
		for (unsigned i=0; i<m.size(); ++i) {
	   		value_to_replace+= m.str(i);
	 	}
 		
	 	x = value_to_replace[1]-'0';
	 	std::cout << x << ":" <<table[tmp][j] << std::endl;
	*/	tmp = line[1]-'0';
		std::cout << "value: " <<  line << std::endl;
	 	std::cout << tmp <<":"<<j << ":" <<h << std::endl;

	 	
	 	std::map<int,std::vector<std::vector<std::string> > >::iterator iter = std::next(table.begin(), x);
		std::map<int,std::vector<std::vector<std::string> > >::iterator iterend = std::next(table.begin(), x+1);

	 	for(std::map<int,std::vector<std::vector<std::string> > >::const_iterator at = iter; at != iterend; ++at) {
	 		std::vector<std::vector<std::string> > ::const_iterator iter2 = std::next((at->second).begin(), j);
			std::vector<std::vector<std::string> > ::const_iterator iterend2 = std::next((at->second).begin(), j+1);
		 	for(std::vector<std::vector<std::string> >::const_iterator it = iter2; it != iterend2; ++it) {
		 		for(std::vector<std::string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 			
		 				std::cout <<"in"<<*et <<std::endl;
		 			
		 			if( std::regex_search(line,m, std::regex("\\([0-9]\\)")) ) {
				 			tmp_vec.push_back(recursive(*et,table,tmp_vec,j,h));
				 		
					 		
				 			
				 	}
				 	if(	std::regex_search(line,m, std::regex("[0-9]"))){
				 			tmp_vec.push_back(line);
				 			
				 	}
				 	
		 		std::cout <<"et" << *et << "end" <<std::endl;
		 		}

		 		
		 }		
	 	
	 	
		}
	return "";
	}
	if(std::regex_search(line, std::regex("[0-9]"))) {
		
		std::map<int,std::vector<std::vector<std::string> > >::iterator iter = std::next(table.begin(), atoi(line.c_str()));
		std::map<int,std::vector<std::vector<std::string> > >::iterator iterend = std::next(table.begin(), atoi(line.c_str())+1);
		
	 	for(std::map<int,std::vector<std::vector<std::string> > >::const_iterator at = iter; at != iterend; ++at) {
	 		std::vector<std::vector<std::string> > ::const_iterator iter2 = std::next((at->second).begin(), j);
			std::vector<std::vector<std::string> > ::const_iterator iterend2 = std::next((at->second).begin(), j+1);
		 	for(std::vector<std::vector<std::string> >::const_iterator it = iter2; it != iterend2; ++it) {
		 			for(std::vector<std::string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 				std::cout <<*et<<std::endl;
		 				/*if( !(std::regex_search(*et, std::regex("\\([0-9]\\)")))) {
		 				std::cout <<"test"<<std::endl;
		 				tmp_vec.push_back(*et);

		 			}*/
		 		}
		 	}
		 }
		return line;
	}
	else{
	return "";
	}

}






