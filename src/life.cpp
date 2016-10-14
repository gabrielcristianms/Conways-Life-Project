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

Life::Life( const Life &_obj )
	: m_height { _obj.m_height }
	, m_width { _obj.m_width }
{
	m_cells = new int* [m_height+2];
	for( size_type i = 0; i < m_height+2; ++i )
		m_cells[i] = new int [m_width+2];

	for(size_type i = 0; i < m_height+2; ++i) {
		for( size_type j = 0; j < m_width+2; ++j) {
			m_cells[i][j] = _obj.m_cells[i][j];
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
	std::stringstream ss; //This one is an auxiliary used to convert values to the right type
	std::vector<std::string> line; // We use this container to hold each line of the stream passed as parameter 
	size_type i = 1; // Initialized at val 1 so that we only access the m_height x m_width matrix
	size_type j = 1; // Initialized at val 1 so that we only access the m_height x m_width matrix

	// Loop para pegar cada linha da stringstream e por num vector de strings
	for( std::string temp; getline( _file, temp ); line.push_back( temp ) ){ /* Empty */ };

	// Loop para popular a matriz
	for( auto e : line ){
		// the type of 'e' will be the type which the elements of the vector is, i.e. std::string
		// since the type std::string has begin(), end() methods, we do another ranged for to get the chars of the string
		for( auto c : e ){
			// We'll use a stringstream to convert from char to int
			// Put the char in the stream
			ss << c;
			// Transfer it as an int to the right position in the cell and increment j index, which covers the m_width
			ss >> m_cells[i][j++];
			// Clearing the ss to avoid wrong values
			ss.clear(); 
		}
		// This is necessary so that in the next iteration of the outer for we don't go out of the m_height x m_width matrix range
		j = 1;
		//Increment of the i index, which covers the m_height 
		++i;
	}

}

void
Life::update( void ){
	// Create a Life object which will hold the new configuration
	Life new_config( this->m_height, this->m_width );
	Life old_config( this->m_height, this->m_width );
	old_config = *this;

	// Save this generation in a data structure we'll define
	this->gen.push_back( old_config );
	// Create the vector which will hold the cells that are alive and it's neighbors
	std::vector<std::pair<size_type, size_type>> alive_cells;
	std::vector<std::pair<size_type, size_type>> dead_neighbors;

	// Run through the matrix to get the coordinates of the cells which are alive and it's neighbors
	for(size_type i = 1; i <= this->m_height; ++i){
		for( size_type j = 1; j <= this->m_width; ++j){
			if( this->m_cells[i][j] == 1 ){
				// Constructs a pair and push it to the container
				alive_cells.emplace_back( std::pair<size_type, size_type>( i, j ) );
				// This double for is to get the dead neighbors
				for(size_type a = 0; a < 3; ++a){
					for(size_type b = 0; b < 3; ++b){
						// Setting x and y coordinates of a neighbor
						auto x( i - 1 + a ), y( j - 1 + b );						
						// First we check if the neighbor is dead and check if it doesn't belong in the padding of the matrix
						if( not((x == 0 or x == this->m_height+1) or (y == 0 or y == this->m_width+1) or (this->m_cells[x][y] == 1)) ){
							// Confirmed it's a dead cell, we check if the container is empty so we add without the need of a search
							if( dead_neighbors.size() == 0 )
									dead_neighbors.emplace_back( std::pair<size_type, size_type>( x, y ) );
							else{
								// In this case, we need to search the container to avoid duplicate coordinates
								std::pair<size_type, size_type> aux( x, y );
								// We search the container with the candidate, if it doesn't exist, we push back
								if( std::find( dead_neighbors.begin(), dead_neighbors.end(), aux ) == dead_neighbors.end() )
										dead_neighbors.push_back( aux );
							}
						}
					}
				}
			}
		}
	}
	// Now we'll run through the list of alive cells to test first the neighbors, checking for the death of the cells
	for( const auto &coordinates : alive_cells  ){
		size_type c = 0;
		for(size_type a = 0; a < 3; ++a){
			for(size_type b = 0; b < 3; ++b){
				if( this->m_cells[(coordinates.first - 1) + a][(coordinates.second - 1) + b] == 1 and a != b )
					++c;
			}
		}
		if( not(c <= 1 or c >= 4) )
			new_config.m_cells[coordinates.first][coordinates.second] = 1;
	}
	// Now we'll run through the list of dead cells (which are around alive cells) to test their neighbors and see if it will gain life
	// in the next generation 
	for( const auto &coordinates : dead_neighbors  ){
		size_type c = 0;
		for(size_type a = 0; a < 3; ++a){
			for(size_type b = 0; b < 3; ++b){
				if( this->m_cells[(coordinates.first - 1) + a][(coordinates.second - 1) + b] == 1 )
					++c;
			}
		}
		if( c == 3 )
			new_config.m_cells[coordinates.first][coordinates.second] = 1;
	}
	*this = new_config;

}

bool
Life::isStable( void ){
	size_type sz = gen.size();
	if( sz != 0 ){
		auto result = std::find( gen.begin(), gen.end(), *this );
		if( result != gen.end() ) return true;
	}
	return false;
}

bool
Life::isExtinct( void ){
	for(size_type i = 1; i <= this->m_height; ++i){
		for( size_type j = 1; j <= this->m_width; ++j){
			if( this->m_cells[i][j] != 0 ) return false;
		}
	}
	return true;
}

bool
Life::operator==( const Life &_rhs ){
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
Life::operator!=( const Life &_rhs ){
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