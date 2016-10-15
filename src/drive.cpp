#include "life.h"
using namespace std;

int main(int argc, char const *argv[]){
	// Checks if we have the correct number of arguments
    if(argc < 2 or argc > 3)
    {
        cout << "Wrong Syntax!" << endl;
        cout << "Use: life <input_cfg_file> [<output_cfg_evolution_file>]" << endl;
        return EXIT_FAILURE;
    }
    
    // Setting up the variables we'll use  
    string arquivo;
    arquivo = argv[1];
        
    Life::size_type altura, largura;
    ifstream input (arquivo);
    stringstream ss1, ss2; 
    string dim, carvivo, temp, matriz; 
        
    // If we have no troubles opening the file, we starting reading lines from it
    if (input.is_open())
    {
    	getline(input,dim);
    	//Checking if there are spaces between the two numbers in the first line, if there is, it's a format error in the file
    	if( dim.size() == 3 ){
    		// Getting the values and converting using a stringstream
        	ss1 << dim;
        	ss1 >> altura;
        	ss1 >> largura;
            
            // Getting the char used to represent live cells
        	getline(input,carvivo);
        	// Checking in the same maner as in line one
        	if( carvivo.size() == 1 ){
        		// Reading the actual matrix that will be used in the setAlive() method.            
        		while (getline(input,matriz))
        		{
        			// This changes de string characters that are meant to be alive into 1 and 0 otherwise
        			for( auto it = matriz.begin(); it < matriz.end(); ++it) 
            		{
            			temp = *it;
                		if(temp == carvivo)
                		{
                 		*it = '1';   
                		}
                		else 
                		{
                 		*it = '0';   
            			}
        			}
        			// Writes in the stringstream which will be used
        			ss2 << matriz;
        			ss2 << '\n';
       			}
       		}
       		else{
       			cout << "File is in the wrong format at the second line." << endl;
       		}
       	}
    	else{
       		cout << "File is in the wrong format at the first line." << endl;
       		return EXIT_FAILURE;
       	}                        
            input.close();
    }    
    else{
    	cout << "Unable to open file." << endl;
    	return EXIT_FAILURE;
    }

    // Setting up the variables for the simulation
    std::string word;
    bool flag_stable = false;
    bool flag_extinct = false;
    // will be used to count generations
    Life::size_type g = 0;
    // Using Default Constructor
    Life simulation( altura, largura );
    simulation.setAlive( ss2 );
    cout << "Welcome to Conway's Game of Life\nThe Height and Width were read from the file "
    	 << arquivo << "\nwith Height: " << altura << " and Width: " << largura
    	 << "\nThe actual configuration, with 1 for alive and 0 for dead, is:\n\n"
    	 << simulation 
    	 << "\nThe simulation will stop if either it goes stable or goes extinct. Let's begin!!!\n\n";
   	// Reads user input until he types "n" or the simulation goes extinct or stable
    do{
    	cout << "Generation #" << (g++)+1 << ":\n" << simulation << "\n\n";
    	simulation.update();
    	if( simulation.isExtinct() ){
    		flag_extinct = true;
    		break;
    	} 
    	if( simulation.isStable() ){
    		flag_stable = true;
    		break;
    	}
    	cout << "Continue?\n(y?n) \n";
    	cin >> word;
    }while(  word != "n" );

    // Prints expecific to the cases where the simulation ended not because of the user
    if( flag_extinct ) cout << "The simulation ended with extinction at generation #" << g+1 << endl;
    if( flag_stable )  cout << "The simulation ended with stability at generation #"  << g+1 << " with frequency "<< g-1 << endl;

    // Variables used in the writing of the generation log file
    string create;
    create = argv[2];
        
    ofstream output (create);
    // Opening of the file
    if (output.is_open())
    {
    	cout << "File opened at " << create << " with success!\n";
    	// Generation counter for the writing of the file
    	Life::size_type i = 1;
    	// Ranged for to write the configurations simulated
	    for( auto &gen : simulation.gen ){
	    	output << "Generation #" << i++ << "\n\n"
	    		   << gen
	    		   << "\n\n";
	    }
	    if( flag_stable )
	    	output << "Generation #" << i << "\n\n" << simulation << "\n\nEnd of log.";
        output.close();
    }
    else cout << "Unable to open file";        
        
	std::cout << ">>> Normal Exiting...\n";
	return EXIT_SUCCESS;
}