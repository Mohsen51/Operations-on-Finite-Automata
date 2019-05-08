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




void Automata::display_transition_table() const {
	const int nameWidth     = 5;
    const int numWidth      = 20;
	std::cout << "display"<<std::endl;
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
		 			tmp += *et+" ";
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

void Automata::is_an_asynchronous_automaton() const{
	std::vector<std::string>  tmp;
	for(std::vector<std::string>::const_iterator line = this->_transitions.begin(); line != this->_transitions.end(); ++line) {
		if(42==(int((*line)[1]))){
			std::string l;
			l = *line;
			tmp.push_back(l);
		}
	}


	if(tmp.size()>1){
		std::cout << "the automata is asynchronous" << std::endl;
		std::cout << "the following transitions are astnchronous:" << std::endl;
		for(std::vector<std::string>::const_iterator line = tmp.begin(); line != tmp.end(); ++line) {
			std::cout << *line << std::endl;

		}
	}
}


void Automata::display_asynchronous_to_synchronous(){
	
	std::vector<std::string>  states;
	std::map<int,std::vector<std::vector<std::string> > > map1;
	std::vector<std::vector<std::string> >  table(this->_nb_transitions_available, std::vector<std::string> (1, "-"));


	/*for(std::map<int,std::vector<std::string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		states = at->second;
		for(std::vector<std::string>::const_iterator it = states.begin(); it != states.end(); ++it) {
				std::cout << *it << std::endl;
		}
	}*/
	
	
	
		for(int i=0;i<this->_nb_states;i++){
			std::vector<std::string> list;
			for(int t=0;t<this->_nb_transitions_available;t++){
				//states[0].size()-1
				//std::cout <<"i:"<<states[0][i]<< std::endl;
				this->recursive(t,i,0,this->_transitions,list);
				
				std::sort(list.begin(), list.end()); 
				list.erase(std::unique(list.begin(), list.end()), list.end());
				
				/*for(std::vector<std::string>::const_iterator line = list.begin(); line != list.end(); ++line) {
				std::cout << *line << std::endl;
				}*/
				table[t]=list;
				
				list.clear();
		}
		this->_transitions_table[i] = table;
		for(int x=0;x<this->_nb_transitions_available;x++){
			table[x].clear();
		}
   		

		

	}

}

void Automata::asynchronous_to_synchronous(){
	std::vector<std::string>  states;
	std::map<int,std::vector<std::vector<std::string> > > map1;
	std::vector<std::vector<std::string> >  table(this->_nb_transitions_available, std::vector<std::string> (1, "-"));


	for(std::map<int,std::vector<std::string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		states = at->second;
		for(std::vector<std::string>::const_iterator it = states.begin(); it != states.end(); ++it) {
				std::cout << *it << std::endl;
		}
	}
	
	while(states){
		for(int t=0;t<this->_nb_transitions_available;t++){
			std::vector<std::string> list;
			for(int i=0;i<this->states[0].size()-1;i++){
				this->recursive(t,i,0,this->_transitions,list);	
				
				/*for(std::vector<std::string>::const_iterator line = list.begin(); line != list.end(); ++line) {
						std::cout << *line << std::endl;
				}*/
				
				
						
			}   		

		}
		std::sort(list.begin(), list.end()); 
		list.erase(std::unique(list.begin(), list.end()), list.end());
		table[t] = list;
		list.clear();
		map[]
		for(int x=0;x<this->_nb_transitions_available;x++){
				table[x].clear();
		}
	}

}







void Automata::recursive(int t,int i,int lamba,std::vector<std::string> _transitions,std::vector<std::string> &list) const {

	for(std::vector<std::string>::const_iterator line = _transitions.begin(); line != _transitions.end(); ++line) {
		//std::cout <<*line <<" t"<<t << " i"<<i<< "lambda" << lamba <<std::endl;
		
	if((*line)!=" "){
		if(( ((*line)[0]==(*line)[2] && (int((*line)[1])-97)==t && !lamba && (atoi(&(*line)[0])==i)) || ((atoi(&(*line)[0])==i) && (t==(int((*line)[1])-97)) && !lamba))){
			//std::cout <<"1"<< std::endl;
			std::string tmp;
			tmp = line[0][2];
			list.push_back(tmp);
			
			recursive(t,atoi(&(*line)[2]),1,_transitions,list);

		}

		else{
			if( (atoi(&(*line)[0])==i) && (42==(int((*line)[1]))) && lamba){
				//std::cout <<"2"<< std::endl;
				std::string tmp;
				tmp = line[0][2];
				list.push_back(tmp);
				recursive(t,atoi(&(*line)[2]),1,_transitions,list);
			}
			else{
				if((atoi(&(*line)[0])==i) && (42==(int((*line)[1]))) && !lamba){
					//std::cout <<"3"<< std::endl;
					recursive(t,atoi(&(*line)[2]),0,_transitions,list);
				}
			}


		}
	}
	}
	

}






