#include "life.h"

Life::Life( size_type _h = 0, size_type _w = 0)
	: m_height { _h }
	, m_width { _w }
{
	m_cells = new int* [m_height+2];
	for(size_type i = 0; i < m_height+2; ++i)
		m_cells[i] = new int [m_width+2];

	for(size_type i = 0; i < m_height+2; ++i) {
		for( size_type j = 0; j < m_width+2; ++j) {
			m_cells[i][j] = 0;
		}
	}
}

Life::~Life(){
	for(size_type i = 0; i < m_width+2; ++i)
		delete [] m_cells[i];
	delete [] m_cells;
}

void
Life::setAlive( std::stringstream &_file ){
	std::stringstream temp; //This one is an auxiliary we'll use to convert values to the right type
	std::vector<std::string> line; // We'll use this container to hold each line of the stream passed as parameter 
	size_type i = 1; // Initialized at val 1 so that we'll only access the m_height x m_width matrix
	size_type j = 1; // Initialized at val 1 so that we'll only access the m_height x m_width matrix

	// Loop para pegar cada linha da stringstream e por num vector de strings
	for( std::string temp; getline( _file, temp ); line.push_back( temp ) ){ /* Empty */ };

	// Loop para popular a matriz
	for( auto e : line ){
		// the type of 'e' will be the type which the elements of the vector is, i.e. std::string
		// since the type std::string has begin(), end() methods, we do another ranged for to get the chars of the string
		for( auto c : e ){
			// We'll use a stringstream to convert from char to int
			// Put the char in the stream
			temp << c;
			// Transfer it as an int to the right position in the cell and increment j index, which covers the m_width
			temp >> m_cells[i][j++];
			// Clearing the temp to avoid wrong values
			temp.clear(); 
		}
		// This is necessary so that in the next iteration of the outer for we don't go out of the m_height x m_width matrix range
		j = 1;
		//Increment of the i index, which covers the m_height 
		++i;
	}

}

bool
Life::operator==( Life &_rhs ){
	if( this->m_height != _rhs.m_height ) return false;
	if( this->m_width != _rhs.m_width ) return false;

	for(size_type i = 1; i <= this->m_height; ++i) {
		for( size_type j = 1; j <= this->m_width; ++j) {
			if( this->m_cells[i][j] != _rhs.m_cells[i][j]) return false;
		}
	}
	return true;
}

bool
Life::operator!=( Life &_rhs ){
	return !( *this == _rhs );
}

Life&
Life::operator=( const Life &_rhs ){
	// Deletes the memory allocated previously
	for(size_type i = 0; i < this->m_width+2; ++i)
		delete [] this->m_cells[i];
	delete [] this->m_cells;

	// Allocates the new space we'll use
	this->m_cells = new int* [m_height+2];
	for(size_type i = 0; i < m_height+2; ++i)
		m_cells[i] = new int [m_width+2];

	// Copying the measures of our cells matrix
	this->m_height = _rhs.m_height;
	this->m_width  = _rhs.m_width;

	// Copying the values of _rhs.m_cells to the object this->m_cells who called =() 
	for(size_type i = 0; i < this->m_height+2; ++i) {
		for( size_type j = 0; j < this->m_width+2; ++j) {
			this->m_cells[i][j] = _rhs.m_cells[i][j];
		}
	}	
	return *this;
}