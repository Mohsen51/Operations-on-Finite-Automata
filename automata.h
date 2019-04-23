#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>

class Automata
{
public:
	Automata();

	void display() const;

	friend std::ostream& operator<<(std::ostream&, const Automata&);

private:
	int _nb_transitions_possible;
	int _nb_states;
	int *_init_states;
	int *_final_states;
	int _nb_transitions;
	std::string *_transitions;
};

#endif