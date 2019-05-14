#include "automata.h"
#include "automata_determize.h"


int main(){

	string i;
	std::cout << "which FA do you want to use?" << std::endl;
	cin >> i;

	string name = "automata/FA_"+i+".txt";

	Automata_determinize b(name);
	
	

	if(b.is_an_asynchronous_automaton()){
		b.asynchronous_to_synchronous();
		b.determinaze();
		if(b.is_complete()){
			//a.complete();
		}
	}
	else{
		b.synchronous_transition_table();
		if((b.is_deterministic())){
			if((b.is_complete())){

				b.determinaze();
				b.complete();
				//it should be completed before determinazing in real senario 
			}
			else{
				
				b.determinaze();
			}
			b.display();
		}
		
		else{
			std::cout << "already determize" << std:: endl;
			b.Automata::display();
			
		}
	}



	
	
	
	
	
	return 0;
}