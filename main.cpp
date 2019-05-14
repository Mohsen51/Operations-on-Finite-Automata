#include "automata.h"
#include "automata_determize.h"
#include "comp_language.h"


int main(){

	string i;
	std::cout << "which FA do you want to use?" << std::endl;
	cin >> i;

	string name = "automata/FA_"+i+".txt";

	Comp_language c(name);
	
	

	if(c.is_an_asynchronous_automaton()){
		c.asynchronous_to_synchronous();
		c.determinaze();
		if(c.is_complete()){
			//a.complete();
		}
	}
	else{
		c.synchronous_transition_table();
		if((c.is_deterministic())){
			if((c.is_complete())){

				c.determinaze();
				c.complete();
			}
			else{
				
				c.determinaze();
			}
			c.Automata_determinize::display();
			c.get_comp_automata();
			c.display();
		}
		
		else{
			std::cout << "already determize" << std:: endl;
			c.Automata::display();
			
		}
	}

	



	
	
	
	
	
	return 0;
}