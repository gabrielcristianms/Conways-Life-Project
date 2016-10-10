#ifndef __LIFE_H__
#define __LIFE_H__
#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cstdlib>

class Life{
	public:
		//Defining an alias for the size parameters of the matrix
		using size_type = unsigned long;

		//Default Constructor
		Life( size_type, size_type );	
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
		bool operator==( Life& );
		//Overloading the != operator to compare different Life instances.
		bool operator!=( Life& );
		//Copy assignment.
		Life& operator=( const Life& );
		//Overloading the << operator to print Life objects using cout and similar functions.
		friend std::ostream& operator<<( std::ostream&, Life& );
	private:
		int **m_cells;
		size_type m_height;
		size_type m_width;
};
#endif