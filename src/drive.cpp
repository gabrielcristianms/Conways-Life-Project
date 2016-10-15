#include "life.h"
using namespace std;

int main(int argc, char const *argv[]){
    if(argc < 2 or argc > 3)
    {
        cout << "Wrong Syntax!" << endl;
        cout << "Use: life <input_cfg_file> [<output_cfg_evolution_file>]" << endl;
        return EXIT_FAILURE;
    }
      
    string arquivo;
    arquivo = argv[1];
        
    Life::size_type altura, largura;
    ifstream input (arquivo);
    stringstream ss1, ss2; 
    string dim, carvivo, temp, matriz; 
        
    if (input.is_open())
    {
    	getline(input,dim);
    	if( dim.size() == 3 ){
        	ss1 << dim;
        	ss1 >> altura;
        	ss1 >> largura;
                
        	getline(input,carvivo);
        	if( carvivo.size() == 1 ){            
        		while (getline(input,matriz))
        		{
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
                
        	cout << altura << endl;
            cout << largura << endl;
            cout << carvivo << endl; 
            cout << ss2.str() << endl; 
            
            input.close();
    }    
    else{
    	cout << "Unable to open file." << endl;
    	return EXIT_FAILURE;
    }

    std::string word;
    bool flag_stable = false;
    bool flag_extinct = false;
    Life::size_type g = 0;
    Life simulation( altura, largura );
    simulation.setAlive( ss2 );
    cout << "Welcome to Conway's Game of Life\nThe Height and Width were read from the file "
    	 << arquivo << "\nwith Height: " << altura << " and Width: " << largura
    	 << "\nThe actual configuration, with 1 for alive and 0 for dead, is:\n\n"
    	 << simulation 
    	 << "\nThe simulation will stop if either it goes stable or goes extinct. Let's begin!!!\n\n";
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

    if( flag_extinct ) cout << "The simulation ended with extinction at generation #" << g+1 << endl;
    if( flag_stable )  cout << "The simulation ended with stability at generation #"  << g+1 << " with frequency "<< g-1 << endl;

    string create;
    create = argv[2];
        
    ofstream output (create);
    if (output.is_open())
    {
    	cout << "File opened at " << create << " with success!\n";
    	Life::size_type i = 1;
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