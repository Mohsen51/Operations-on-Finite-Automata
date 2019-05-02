#include "automata.h"



int main(){

	Automata a;
	a.transitions_table();
	a.display();
	/*std::map<int,std::vector<std::vector<std::string> > > table;
	
	for(int i=0;i<4;i++){
		std::vector<std::vector<std::string> > vector(2, std::vector<std::string> (1, std::to_string(i)));
		table[i] = vector;

	}

	std::map<int,std::vector<std::vector<std::string> > >::iterator iter = std::next(table.begin(), 3);
	std::map<int,std::vector<std::vector<std::string> > >::iterator iterend = std::next(table.begin(), 3);
	


	for(std::map<int,std::vector<std::vector<std::string> > >::const_iterator at = table.begin(); at != table.end(); ++at) {
			std::vector<std::vector<std::string> > ::const_iterator iter2 = std::next((at->second).begin(), 1);
			std::vector<std::vector<std::string> > ::const_iterator iterend2 = std::next((at->second).begin(), 2);
		 	for(std::vector<std::vector<std::string> >::const_iterator it = iter2; it != iterend2; ++it) {
		 		std::string tmp_str = "";
		 		for(std::vector<std::string>::const_iterator et = it->begin(); et != it->end(); ++et){
		 			tmp_str += *et;
		 		}
		 		std::cout << tmp_str << std::endl;
		 	}
		 }		
*/
	
	return 0;
}