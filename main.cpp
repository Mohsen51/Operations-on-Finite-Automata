#include "automata.h"



int main(){

	Automata a;
	//a.transitions_table();

	if(a.is_an_asynchronous_automaton()){
		a.asynchronous_to_synchronous();
		a.determinaze();
		if(a.is_complete()){
			a.complete();
		}
	}
	else{
		a.synchronous_transition_table();
		if((a.is_deterministic())){
			if((a.is_complete())){
				a.determinaze();
				a.complete();
				//it should be completed before determinazing in real senario 
			}
			else{
				
				a.determinaze();
			}
		}
		else{
			a.determinaze();
		}
	}

	a.display_complete_dererministic_automaton();
	
	
	
	
	return 0;
}