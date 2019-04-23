#include "automata.h"
#include<fstream>


Automata::Automata(){
		std::string line;
	    std::ifstream file;
	    file.open("test.txt");

	   if(!file.is_open()) {
	      std::cout << "erro file" << std::endl;
	   }
	   
	    int i=0;
	    while(getline(file,line)) {
	     std::cout << line << std::endl;
	     if(i==0)
	     {
	     	this->_nb_transitions_possible = atoi(line.c_str());
	     }
	     else if(i==1)
	     {
	     	this->_nb_states = atoi(line.c_str());
	     }
	     else if(i==2)
	     {
	     	this->_init_states = new int[line[0]];
	     	this->_init_states[0] = (int)line[0]-48;
	     	for(int i=1; i<line[0];i++)
	     	{
	     		this->_init_states[i] = (int) line[i]-48;
	     	}
	     }
	     else if(i==3)
	     {
	     	this->_final_states = new int[line[0]];
	     	this->_final_states[0] = (int)line[0]-48;
	     	for(int i=1; i<line[0];i++)
	     	{
	     		this->_final_states[i] = (int) line[i]-48;
	     	}
	     }
	     else if(i==4)
	     {
	     	this->_nb_transitions = atoi(line.c_str());
	     }
	     else
	     {
	     	if(i==5){
				this->_transitions = new std::string[this->_nb_states*2];
	     	}
	     	this->_transitions[i-5] = line;
	     	 std::cout << i << std::endl;
	     }
	     i++;
	    }
}

void Automata::display() const{

	 std::cout << this->_nb_transitions_possible << std::endl;
	 std::cout << this->_nb_states << std::endl;
	 std::cout << this->_init_states[0] << std::endl;
	 std::cout << this->_final_states[0] << std::endl;
	 std::cout << this->_nb_transitions << std::endl;
	 std::cout << this->_transitions[0] << std::endl;

}





