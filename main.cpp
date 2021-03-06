#include "automata.h"
#include "automata_determize.h"
#include "comp_language.h"
#include "automata_standardize.h"
#include <sstream>


int main(){
	int test = 1;
	while(test){
		string i;
		int nbr = 0;
		while (true)
		{
			std::cout << "which FA do you want to use?" << std::endl;
			getline(cin, i);
			stringstream myStream(i);
			if (myStream >> nbr)
			{
				if (nbr>0 && nbr<45 && nbr!=43)
					break;
			}
		}
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
		int choice;
		bool choice2 = 1;
		do
		{
			string input = "";
			while (true)
			{
				cout << "In which table do you want to check your word ? (1:Deterministic, 2:Complementary language, 3:Standardized or any other number if you don't want to check any word)" << endl;
				getline(cin, input);
				stringstream myStream(input);
				if (myStream >> choice)
					break;
			}
			switch (choice)
			{
			case 1:
				c.Automata_determinize::read_word();
				break;
			case 2:
				c.Comp_language::read_word();
				break;
			case 3:
				c.Automata_standardize::read_word();
				break;
			default:
				choice2=0; 
				break;
			}
			if (choice2)
			{
				while (true)
				{
					cout << "Do you want to check a word from another table ? (enter 1 or 0)" << endl;
					getline(cin, input);
					stringstream myStream(input);
					if (myStream >> choice2)
						break;
				}
			}
		} while (choice2);
		cout << "Do you want to test another Automata ? (enter 1 if yes)" << endl;
		cin >> test;		
	}
		
	return 0;
}