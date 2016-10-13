#include "life.h"

int main(int argc, char const *argv[]){
	Life petri( 4, 4);
	Life petri2( 5, 4);
	petri2 = petri;
	if( petri == petri2 )
		std::cout << "Sao iguais.\n";

	std::cout << petri << "\n" << petri2 << "\n";

	Life colonia( 2, 2 );
	std::stringstream ss;
	ss << "11\n10";
	colonia.setAlive( ss );
	std::cout << colonia << std::endl;
	std::cout << ">>> Normal Exiting...\n";
	return EXIT_SUCCESS;
}