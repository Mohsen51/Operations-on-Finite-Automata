void Automata::transitions_table()  {

	std::map<int,std::vector<std::string> > table;

	// for each state, the algo go trought the _transitions vector to map its transitions  map[state] = [transitions(a),transitions(b)...];
	for(int i=0; i< this->_nb_states; i++) {
		// initialisation of the vector 
		std::vector<std::string> _tmp_transitions;
		for(int j = 0; j < this->_nb_transitions_available; j++) {
			_tmp_transitions.push_back("-");
		}

		for(std::vector<std::string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
		 	//std::cout << "transition" <<*it << std::endl;
		 	
		 	if((atoi(&(*it)[0])==i) && (*it != "")) {		
		 		if(it->at(1) == '*') {	
		 			for(int j = 0; j < this->_nb_transitions_available; j++) {
				 		if(((_tmp_transitions[j]) != "-")) {
							_tmp_transitions[j] =  _tmp_transitions[j]+ std::string(",(") +
												   (*it)[2] + std::string(")");
							
				 		}
				 		else {
				 			//std::cout <<"=0" << std::endl;
				 			_tmp_transitions[j] = std::string("(") + (*it)[2] + std::string(")");
				 		}
				 	}
				  }
		 		else{
		 			if(((_tmp_transitions[int((*it)[1])-97]) != "-")) {
					//std::cout <<"sup" << std::endl;
					_tmp_transitions[int((*it)[1])-97] =  _tmp_transitions[int((*it)[1])-97]+ "," + (*it)[2];
					
			 		}
			 		else {
			 			//std::cout <<"=0" << std::endl;
			 			_tmp_transitions[int((*it)[1])-97] = (*it)[2];
			 		}
			 	}

			 		
		 		
		 	}

		 	/*for(std::vector<std::string>::const_iterator at = _tmp_transitions.begin(); at != _tmp_transitions.end(); ++at) {
		 	std::cout << *at << std::endl;
		 	}*/
		 	//std::cout << "t0" <<_tmp_transitions[0] << std::endl;
		 	//std::cout << "t1" <<_tmp_transitions[1] << std::endl;

		}

		// map state i to its transition vector 

		this->_transitions_table[i] = _tmp_transitions;
		_tmp_transitions.clear();

	}

	///////////// only for asynchronous automata ///////////////////
	// replace epsilon transition by its real value
	int i=0;
	int j=0;
	 for(std::map<int,std::vector<std::string> >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
    		
		 	for(std::vector<std::string>::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 			 std::cout << "before" << i << "space"<<*it << std::endl;
		 			this->_transitions_table[i][j] = recursive (*it,this->_transitions_table ,j); 
		 			 std::cout << "after : " << this->_transitions_table[i][j] << std::endl;
					

					//remove duplicate character

					for(int y=0;y<this->_transitions_table[i][j].length();y++) {
						for(int z=0;z<this->_transitions_table[i][j].length();z++){
							if((z != y) && this->_transitions_table[i][j][z] == this->_transitions_table[i][j][y]){
								this->_transitions_table [i][j].erase(z);
							}
						}
					}

					//remove unexpected character
					if(std::regex_search(this->_transitions_table[i][j], std::regex(",\\([0-9]\\)"))){
			 			this->_transitions_table[i][j] =  std::regex_replace(this->_transitions_table[i][j] , std::regex(",\\([0-9]\\)"), "");
			 		}
			 		else {
			 			if(std::regex_match(this->_transitions_table [i][j], std::regex("\\([0-9]\\)"))){
			 			this->_transitions_table[i][j] = std::regex_replace(this->_transitions_table[i][j] , std::regex("\\([0-9]\\)"), "-");
				 		}
				 		else	{
				 		this->_transitions_table[i][j] = std::regex_replace(this->_transitions_table[i][j] , std::regex("\\([0-9]\\)"), "");
				 		}
				 	}
					j++;
				}
			i++;
			j=0;
		}
		
	/////////////////////////////////////////////////////
	


}


void Automata::display_transition_table() const {
	const int nameWidth     = 15;
    const int numWidth      = 17;

    // display banner with available states
	printElement("S", nameWidth);
	for(int i=0; i<this->_nb_transitions_available; i++) {
		printElement(char(97+i), numWidth);
	}
	std::cout << std::endl;

	// printElement is a template (function) to display data with good indentation 
    for(std::map<int,std::vector<std::string> >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
    		printElement(at->first, nameWidth);
		 	for(std::vector<std::string>::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		printElement(*it, numWidth);
		}
		std::cout << std::endl;
	}

}

std::string Automata::recursive(std::string line, std::map<int, std::vector<std::string> > table,int j) const {
	std::smatch m;
	int tmp = 0;
	int &x = tmp;
	if( std::regex_search(line,m, std::regex("\\([0-9]\\)"))) {
		
		std::string value_to_replace;
		for (unsigned i=0; i<m.size(); ++i) {
	   		value_to_replace+= m.str(i);
	 	}
 		
	 	x = value_to_replace[1]-'0';
	 	std::cout << x << ":" <<table[tmp][j] << std::endl;

	 	//std::cout <<"/"<<table[tmp][j]<<"/" << std::endl;
	 	if( !(std::regex_match(table[tmp][j],m, std::regex("-")))) {
	 		table[tmp][j] = std::regex_replace(line , std::regex("\\([0-9]\\)"), recursive(table[tmp][j],table,j));
	 		return table[tmp][j];
	 	}
	 
	 	else {
		 	return line;
	 		
	 	
	 	
		}
	}
	else {
	
		

		return line;
	}
	



}

//////////////

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


	//////
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






