#include "life.h"

int main(int argc, char const *argv[]){
	Life petri( 4, 4);
	Life petri2( 5, 4);
	if( petri != petri2 )
		std::cout << "Sao diferentes.\n";
	std::cout << ">>> Normal Exiting...\n";
	return EXIT_SUCCESS;
}