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
        
        int cont1 = 0, cont2 = 0;
        Life::size_type altura, largura;
        ifstream input (arquivo);
        stringstream ss1, ss2;
        string dim, carvivo, temp, matriz; 
        
        if (input.is_open())
            
        {
            getline(input,dim);
            ss1 << dim;
            ss1 >> altura;
            ss1 >> largura;
                
            getline(input,carvivo);
            
            while (getline(input,matriz))
            {
                cont1++;
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
            cont2 = matriz.size();
            if(cont2 != largura )
            {
                cout << "Matriz de tamanho diferente das dimensões!" << endl;
                return EXIT_FAILURE;
                
            }
            
            ss2 << matriz;
            ss2 << '\n';
                
            }
            if(cont1 != altura)
            {
             cout << "Matriz de tamanho diferente das dimensões!" << endl;
             return EXIT_FAILURE;
            }
              cout << altura << endl;
              cout << largura << endl;
              cout << carvivo << endl; 
              cout << ss2.str() << endl;  
              
              
            input.close();
            
        }
        
        else cout << "Unable to open file." << endl;
        
        string create;
        create = argv[2];
        
        ofstream output (create);
        if (output.is_open())
        {
            output << "This is a line.\n";
            output << "This is another line.\n";
            output.close();
        }
        else cout << "Unable to open file";
        
        
        
        
        
        
        
	std::cout << ">>> Normal Exiting...\n";
	return EXIT_SUCCESS;
}