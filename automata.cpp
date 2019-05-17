#include "automata.h"

using namespace std;

template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

Automata::Automata(string name) {
		get_data_from_file(name);
}

void Automata::get_data_from_file(string name) {
	string line;
	ifstream file;
    file.open(name);

   if(!file.is_open()) {
      cout << "error file" << endl;
   }
   
   	vector<string> _tmp_vector;
   	//get line by line 
    getline(file,line);
    this->_nb_transitions_available = atoi(line.c_str());

    getline(file,line);
    this->_nb_states = atoi(line.c_str());

    getline(file,line);
    string z = line.substr(0,1);
    int size = atoi(z.c_str());
   
    for(int i=0;i<(size*2)-1;i++){
    	 char tmp = line[i+2];
    	string s(1, tmp);	 
    	_tmp_vector.push_back(s);
    }
	
	this->_init_states = _tmp_vector;
    _tmp_vector.clear();

    getline(file,line);
	 string x = line.substr(0,1);
    size = atoi(x.c_str());
   
    for(int i=0;i<(size*2)-1;i++){
    	 char tmp = line[i+2];
    	string s(1, tmp);	 
    	_tmp_vector.push_back(s);
    }

    this->_final_states = _tmp_vector;
    _tmp_vector.clear();

	getline(file,line);
    this->_nb_transitions = atoi(line.c_str());
     
    while(getline(file,line)) {
     	this->_transitions.push_back(line);
    }
   

}

void Automata::display() const{

	cout <<  endl;
	cout << "AUTOMATA "  << endl;	
	cout <<  endl;

	cout << "initial state(s):" << endl;
	
	for(vector<string> ::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		cout << *at ;
	}
	cout <<  endl;

	cout << "final state(s):" << endl;
	
	
	for(vector<string> ::const_iterator at = this->_final_states.begin(); at != this->_final_states.end(); ++at) {
		cout << *at;
	}
	cout <<  endl;

	cout << "transition table:" << endl;
	this->display_transition_table();

	 //for(vector<string>::const_iterator it = this->_transitions.begin(); it != this->_transitions.end(); ++it) {
     //	cout << *it << endl;
	//}

}




void Automata::display_transition_table() const {
	const int nameWidth     = 5;
    const int numWidth      = 20;
	cout << "display"<<endl;
    // display banner with available states
	printElement("S", nameWidth);
	for(int i=0; i<this->_nb_transitions_available; i++) {
		printElement(char(97+i), numWidth);
	}
	cout << endl;

	// printElement is a template (function) to display data with good indentation 
    for(map<int,vector<vector<string> > >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
    		printElement(at->first, nameWidth);
		 	for(vector<vector<string> >::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		string tmp = "";
		 		for(vector<string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 			tmp += *et+" ";
		 		}
		 		if(tmp =="")
		 		{
		 			tmp="-";
		 		}
		 		printElement(tmp.erase(0,0), numWidth);
		 		
		}
		cout << endl;
	}

}



///////////// only for asynchronous automata ///////////////////

bool Automata::is_an_asynchronous_automaton() const{
	vector<string>  tmp;
	int i=0;
	for(vector<string>::const_iterator line = this->_transitions.begin(); line != this->_transitions.end(); ++line) {
		if(42==(int((*line)[1]))){
			string l;
			l = *line;
			tmp.push_back(l);
		}
	}


	if(tmp.size()>1){
		i=1;
		cout << "the automata is asynchronous" << endl;
		cout << "the following transitions are asynchronous:" << endl;
		for(vector<string>::const_iterator line = tmp.begin(); line != tmp.end(); ++line) {
			cout << *line << endl;

		}
	}
	else {
		cout << "the automata is synchronous" << endl;
	}
	return i;
}

void Automata::synchronous_transition_table() {
	
	vector<string>  states;
	
	vector<vector<string> >  table(this->_nb_transitions_available, vector<string> (1, "-"));
	
	
	for(int i=0;i<this->_nb_states;i++){
		vector<string> list;
		for(int t=0;t<this->_nb_transitions_available;t++){
			for(vector<string>::const_iterator line = _transitions.begin(); line != _transitions.end(); ++line) {
				int index_left;
				int transition;
				
				//check the position of the transition letter
	
				if(int((*line)[1])-97 >= 0){
					//covnersion from str to int 
					index_left = atoi(&(*line)[0]);
					transition = int((*line)[1])-97;

					if(index_left==i && (t==transition)){
						string tmp;
						tmp = line[0][2];
						list.push_back(tmp);
					}
				}
				else{
					//covnersion from str to int 
					index_left = (atoi(&(*line)[0])+atoi(&(*line)[1]));
					transition = (int((*line)[2])-97);
					if(index_left==i && (t==(transition))){		

						string tmp;
						tmp = line[0][3];
						list.push_back(tmp);
					}
				}

			}
			
			sort(list.begin(), list.end()); 
			list.erase(unique(list.begin(), list.end()), list.end());
			
			/*for(vector<string>::const_iterator line = list.begin(); line != list.end(); ++line) {
			cout << *line << endl;
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






bool Automata::is_complete() const {
	int i = 0;
	int j = 0;
	for(map<int,vector<vector<string> > >::const_iterator at = this->_transitions_table.begin(); at != this->_transitions_table.end(); ++at) {
			j = 0;
		 	for(vector<vector<string> >::const_iterator it = (at->second).begin(); it != (at->second).end(); ++it) {
		 		string tmp = "";
		 		for(vector<string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 			tmp += *et+" ";
		 		}
		 		if(tmp =="")
		 		{
		 			i=1;
		 			cout << "state " << at->first<< " transition "<< char(97+j)<<" not complete"<< endl;
		 		}
		 	j++;	
		}
		
	}

	return i;
}


void Automata::asynchronous_to_synchronous(){
	
	vector<string>  states;
	map<int,vector<vector<string> > > map1;
	vector<vector<string> >  table(this->_nb_transitions_available, vector<string> (1, "-"));


	/*for(map<int,vector<string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		states = at->second;
		for(vector<string>::const_iterator it = states.begin(); it != states.end(); ++it) {
				cout << *it << endl;
		}
	}*/
	
	
	
		for(int i=0;i<this->_nb_states;i++){
			vector<string> list;
			for(int t=0;t<this->_nb_transitions_available;t++){
				//states[0].size()-1
				//cout <<"i:"<<states[0][i]<< endl;
				this->recursive(t,i,0,this->_transitions,list);
				
				sort(list.begin(), list.end()); 
				list.erase(unique(list.begin(), list.end()), list.end());
				
				/*for(vector<string>::const_iterator line = list.begin(); line != list.end(); ++line) {
				cout << *line << endl;
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









void Automata::recursive(int t,int i,int lamba,vector<string> _transitions,vector<string> &list) const {

	for(vector<string>::const_iterator line = _transitions.begin(); line != _transitions.end(); ++line) {
		//cout <<*line <<" t"<<t << " i"<<i<< "lambda" << lamba <<endl;
		
	if((*line)!=" "){
		int index_left  = atoi(&(*line)[0]);
		int transition = int((*line)[1])-97;
		if(( ((*line)[0]==(*line)[2] && transition==t && !lamba && index_left==i)) || (((index_left==i) && (t==transition) && !lamba))){
			//cout <<"1"<< endl;
			string tmp;
			tmp = line[0][2];
			list.push_back(tmp);
			
			recursive(t,atoi(&(*line)[2]),1,_transitions,list);

		}

		else{
			if( (index_left==i) && (42==(int((*line)[1]))) && lamba){
				//cout <<"2"<< endl;
				string tmp;
				tmp = line[0][2];
				list.push_back(tmp);
				recursive(t,atoi(&(*line)[2]),1,_transitions,list);
			}
			else{
				if((index_left==i) && (42==(int((*line)[1]))) && !lamba){
					//cout <<"3"<< endl;
					recursive(t,atoi(&(*line)[2]),0,_transitions,list);
				}
			}


		}
	}
	}
	

}


void Automata::return_formated_index(string line,string &index_left,int &transition){
	
		
	if(this->conver_transiiton_letter_to_int(line,1) >=0 ){
		index_left = this->conver_string_to_int(line,0);
		transition = this->conver_transiiton_letter_to_int(line,1);
	}
	else{
		index_left = this->conver_string_to_int(line,0)+ this->conver_string_to_int(line,1);
		transition = this->conver_transiiton_letter_to_int(line,2);
	}
	



}

int Automata::conver_string_to_int(string str, int index){
	return atoi(&(str)[index]);
}

int Automata::conver_transiiton_letter_to_int(string str, int index){
	return int((str)[index]);
}

std::vector<std::string> Automata::split_string(std::string str) {
	std::vector<std::string> tmp;
	std::string tmp_str = str;
	for(int i=0;i<str.size();i++){
		tmp_str = str[i];
		tmp.push_back(tmp_str);
	}

	return tmp;
}

std::string Automata::concate_vector(std::vector<std::string> str){
	string tmp ="";
	for(int h=0;h<str.size();h++){
		if(str[h]!=" ")
			tmp+=str[h];
	}

	return tmp;
}

//work for bith string and vector
std::vector<std::string> Automata::remove_duplicate_vector(std::vector<std::string> vec ){
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());	

	return vec;
}

std::string Automata::remove_duplicate_string(std::string str ){
	std::sort(str.begin(), str.end());
	str.erase(std::unique(str.begin(), str.end()), str.end());	

	return str;
}

