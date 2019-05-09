#include "automata.h"

using namespace std;

template<typename T> void printElement(T t, const int& width) {
	const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

Automata::Automata() {
		get_data_from_file();
}

void Automata::get_data_from_file() {
	string line;
	ifstream file;
    file.open("test.txt");

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
     cout << "data in memory" << endl;

}

void Automata::display() const{

	cout << "initial state(s):" << endl;
	
	for(map<int,vector<string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		cout << (at->second).front()  << endl;
	}

	cout << "final state(s):" << endl;
	
	
	for(map<int,vector<string> >::const_iterator at = this->_final_states.begin(); at != this->_final_states.end(); ++at) {
		cout << (at->second).front()  << endl;
	}

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

void Automata::is_an_asynchronous_automaton() const{
	vector<string>  tmp;
	for(vector<string>::const_iterator line = this->_transitions.begin(); line != this->_transitions.end(); ++line) {
		if(42==(int((*line)[1]))){
			string l;
			l = *line;
			tmp.push_back(l);
		}
	}


	if(tmp.size()>1){
		cout << "the automata is asynchronous" << endl;
		cout << "the following transitions are astnchronous:" << endl;
		for(vector<string>::const_iterator line = tmp.begin(); line != tmp.end(); ++line) {
			cout << *line << endl;

		}
	}
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

/*void Automata::asynchronous_to_synchronous(){
	vector<string>  states;
	map<int,vector<vector<string> > > map1;
	vector<vector<string> >  table(this->_nb_transitions_available, vector<string> (1, "-"));


	for(map<int,vector<string> >::const_iterator at = this->_init_states.begin(); at != this->_init_states.end(); ++at) {
		states = at->second;
		for(vector<string>::const_iterator it = states.begin(); it != states.end(); ++it) {
				cout << *it << endl;
		}
	}
	
	while(states){
		for(int t=0;t<this->_nb_transitions_available;t++){
			vector<string> list;
			for(int i=0;i<this->states[0].size()-1;i++){
				this->recursive(t,i,0,this->_transitions,list);	
				
				for(vector<string>::const_iterator line = list.begin(); line != list.end(); ++line) {
						cout << *line << endl;
				}
				
				
						
			}   		

		}
		sort(list.begin(), list.end()); 
		list.erase(unique(list.begin(), list.end()), list.end());
		table[t] = list;
		list.clear();
		map[]
		for(int x=0;x<this->_nb_transitions_available;x++){
				table[x].clear();
		}
	}

}*/







void Automata::recursive(int t,int i,int lamba,vector<string> _transitions,vector<string> &list) const {

	for(vector<string>::const_iterator line = _transitions.begin(); line != _transitions.end(); ++line) {
		//cout <<*line <<" t"<<t << " i"<<i<< "lambda" << lamba <<endl;
		
	if((*line)!=" "){
		if(( ((*line)[0]==(*line)[2] && (int((*line)[1])-97)==t && !lamba && (atoi(&(*line)[0])==i)) || ((atoi(&(*line)[0])==i) && (t==(int((*line)[1])-97)) && !lamba))){
			//cout <<"1"<< endl;
			string tmp;
			tmp = line[0][2];
			list.push_back(tmp);
			
			recursive(t,atoi(&(*line)[2]),1,_transitions,list);

		}

		else{
			if( (atoi(&(*line)[0])==i) && (42==(int((*line)[1]))) && lamba){
				//cout <<"2"<< endl;
				string tmp;
				tmp = line[0][2];
				list.push_back(tmp);
				recursive(t,atoi(&(*line)[2]),1,_transitions,list);
			}
			else{
				if((atoi(&(*line)[0])==i) && (42==(int((*line)[1]))) && !lamba){
					//cout <<"3"<< endl;
					recursive(t,atoi(&(*line)[2]),0,_transitions,list);
				}
			}


		}
	}
	}
	

}






