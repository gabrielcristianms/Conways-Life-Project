#include "life.h"

using namespace std;

int main(int argc, char const *argv[]){
        if(argc < 2 or argc > 3)
        {
            cout << "Wrong Syntaxe!" << endl;
            cout << "Use: life <input_cfg_file> [<output_cfg_evolution_file>]" << endl;
            return EXIT_FAILURE;
        }
        
        
        string arquivo;
        arquivo = argv[1];
        
        Life::size_type altura, largura;
        ifstream input (arquivo);
        stringstream ss1, ss2, ss3;
        string dim, carvivo, temp, matriz1, matriz2; 
        
        if (input.is_open())
        {
            getline(input,dim);
            ss1 << dim;
            ss1 >> altura;
            ss1 >> largura;
                
            getline(input,carvivo);
            
            while (getline(input,matriz1))
            {
            for( auto it = matriz1.begin(); it < matriz1.end(); ++it) 
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
            ss3 << matriz1;
            ss3 << '\n';
                
            }
              cout << altura << endl;
              cout << largura << endl;
              cout << carvivo << endl; 
              cout << ss3.str() << endl;  
            
            input.close();
        }
        
        else cout << "Unable to open file." << endl;
        
        
	std::cout << ">>> Normal Exiting...\n";
	return EXIT_SUCCESS;
}