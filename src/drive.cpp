#include "life.h"

int main(int argc, char const *argv[]){
	Life petri( 4, 4);
	Life petri2( 5, 4);
	petri2 = petri;
	if( petri == petri2 )
		std::cout << "Sao iguais.\n";

	std::cout << petri << "\n" << petri2 << "\n";

	Life colonia( 5, 5 );
	std::stringstream ss;
	ss << "00000\n00100\n01110\n00000\n00000";
	colonia.setAlive( ss );
	std::cout << colonia << std::endl;

	if( colonia.isExtinct() ) std::cout << "A colonia morreu!\n";
	else std::cout << "A colonia esta viva!!!\n";

	if( petri.isExtinct() ) std::cout << "Petri morreu!\n";
	else std::cout << "Petri esta viva!!!\n";

	std::string user = "user";
	while( user != "n" ){
		colonia.update();
		std::cout << colonia << "\n";
		if( colonia.isExtinct() )
		{
			std::cout << "morreu morreu\n";
			break;
		}
		if( colonia.isStable() )
			break;
		std::cin >> user;		
	}
	std::cout << ">>> Normal Exiting...\n";
	return EXIT_SUCCESS;
}