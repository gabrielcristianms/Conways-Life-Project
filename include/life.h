#ifndef __LIFE_H__
#define __LIFE_H__
#include <iostream>
#include <fstream>
#include <sstream> // std::stringstream
#include <cassert> // std::assert
#include <vector>	// std::vector
#include <utility>	// std::pair
#include <unordered_map> //hash
#include <string>
#include <algorithm> // std::copy
#include <cstdlib> //EXIT_SUCCESS

class Life{
	public:
		//Defining an alias for the size parameters of the matrix
		using size_type = unsigned long;
		//Public historic of the generations
		std::vector<Life> gen;
		//Default Constructor
		explicit Life( size_type, size_type );
		Life( const Life& );	
		//Destructor
		~Life();
		//Initializes a configuration of the game
		void setAlive( std::stringstream& );
		//This function aplies the rules of Conway's Game of Life, killing or creating cells.
		void update( void );
		//Checks if the configuration is stable
		bool isStable( void );
		//Checks if the configuration is defunct
		bool isExtinct( void );
		//Overloading the == operator to compare different Life instances.
		bool operator==( const Life& );
		//Overloading the != operator to compare different Life instances.
		bool operator!=( const Life& );
		//Copy assignment.
		Life& operator=( const Life& );
		//Overloading the << operator to print Life objects using cout and similar functions.
		friend std::ostream & operator<<( std::ostream& _os, const Life &_obj ){
			for(size_type i = 1; i <= _obj.m_height; ++i) {
				for( size_type j = 1; j <= _obj.m_width; ++j) {
					_os << _obj.m_cells[i][j];
				}
			_os << "\n";
			}
			return _os;
		};
	private:
		int **m_cells;
		size_type m_height;
		size_type m_width;
};
#endif