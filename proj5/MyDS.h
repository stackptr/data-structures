/* MyDS.h
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Provides the interface for a data structure that stores STL strings.
 */

#ifndef MYDS_H
#define MYDS_H

#include <string>
#include <algorithm>
#include <vector>
#include <list>

class MyDS {
public:
  // Required functions:
  explicit MyDS(int size = 101) : currentSize(0) { hashTable.resize(101);}
  bool push(const std::string& x){
    std::list<std::string> & whichList = hashTable[ myhash( x ) ];
    if( std::find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
        return false;
    whichList.push_back( x );

    // Rehash; see Section 5.5
    if( ++currentSize > hashTable.size( ) )
        rehash( );
    return true;
  }
  bool search(const std::string& x) const{
    const std::list<std::string> & whichList = hashTable[ myhash( x ) ];
    return std::find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
  }

  // Helper functions:
  void makeEmpty(){
    for(unsigned int i = 0; i < hashTable.size(); i++)
      hashTable[i].clear();
  }

  bool remove(const std::string& x){
    std::list<std::string> & whichList = hashTable[ myhash(x) ];
    std::list<std::string>::iterator itr = std::find( whichList.begin( ), whichList.end( ), x );
    if (itr == whichList.end() )
      return false;
    
    whichList.erase(itr);
    --currentSize;
    return true;
  }

private:
  std::vector<std::list<std::string> > hashTable;
  unsigned int currentSize;

  void rehash( ){
    std::vector<std::list<std::string> > oldLists = hashTable;

    // Create new double-sized, empty table
    hashTable.resize( nextPrime( 2 * hashTable.size( ) ) );
    for( unsigned int j = 0; j < hashTable.size( ); j++ )
        hashTable[ j ].clear( );

    // Copy table over
    currentSize = 0;
    for( unsigned int i = 0; i < oldLists.size( ); i++ ){
        std::list<std::string>::iterator itr = oldLists[ i ].begin( );
        while( itr != oldLists[ i ].end( ) )
            push( *itr++ );
    }
  }
  int myhash(const std::string& x) const {
    int hashVal = hash( x );
    hashVal %= hashTable.size( );
    if( hashVal < 0 )
        hashVal += hashTable.size( );
    return hashVal;
  }
  
  int hash(const std::string & key) const {
    int hashVal = 0;

    for (unsigned int i = 0; i < key.length(); i++)
      hashVal = 37 * hashVal + key[i];
    return hashVal;
  }

  bool isPrime( int n ){
    if( n == 2 || n == 3 )
        return true;
    if( n == 1 || n % 2 == 0 )
        return false;
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

int nextPrime( int n ){
    if( n % 2 == 0 )
        n++;
    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
}
};

#endif