#include "automata.h"
#include "automata_determize.h"
#include "comp_language.h"
#include "automata_standardize.h"


int main(){
	int test = 1;
	while(test){
		string i;
		std::cout << "which FA do you want to use?" << std::endl;
		cin >> i;

		string name = "automata/FA_"+i+".txt";

		Automata_standardize c(name);
		
		std::cout << "######INFO ABOUT THE AUTOMATA#####" << std::endl;
		// define the transition table
		if(c.is_an_asynchronous_automaton()){
			c.asynchronous_to_synchronous();
		}
		else{
			c.synchronous_transition_table();
		}
		
		//determinize and complete
		if((c.is_deterministic())){

			if((c.is_complete())){
				c.determinaze();
				c.complete();
			}
			else{
				c.determinaze();
			}
		}
		
		// Automata complementary language
		c.get_comp_automata();

		// Standardize
		if(c.is_standardize()){
			c.standardize();
			
		}

		c.Automata::display();
		c.Automata_determinize::display();
		c.Comp_language::display();
		c.display();

		
		std::cout << "Do you want to test an another Automata: enter 1 or 0" << std::endl;
		cin >> test;		
	}
	
	


	



	
	
	
	
	
	return 0;
}