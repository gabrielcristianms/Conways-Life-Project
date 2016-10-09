#ifndef __LIFE_H__
#define __LIFE_H__
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdlib>

class Life{
	public:
		//Defining a type for the size of the matrix
		using size_type = unsigned long;

		//Default Constructor
		Life( size_type, size_type, std::ostream& );
		//Copy Constructor
		Life( const Life& );
		//Destructor
		~Life();
		//This function aplies the rules of Conway's Game of Life, killing or creating cells.
		void update( void );
		//This function prints the actual configuration in the screen.
		void print( void ) const;
		//Overloading the == operator to compare different Life instances.
		bool operator==( Life& ) const;
		//Overloading the != operator to compare different Life instances.
		bool operator!=( Life& ) const;
		//Copy assignment.
		Life& operator=( const Life& );
		//Overloading the << operator to print Life objects using cout and similar functions.
		friend std::ostream& operator<<( std::ostream&, Life& );
	private:
		bool **m_cells;
		size_type m_height;
		size_type m_width;
};
#endif