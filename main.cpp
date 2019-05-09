#include "automata.h"



int main(){

	Automata a;
	//a.transitions_table();
	a.is_an_asynchronous_automaton();
	//a.asynchronous_to_synchronous();
	a.synchronous_transition_table();
	a.display();
	//a.determinaze();
	//a.display_transition_table2();
	
	return 0;
}