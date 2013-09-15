/* compare.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Provides an executable to compare the performance of different
 * containers on a set of files.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include "MyDS.h"
#include "cputime.h"
#include "MyHash.h"

int main(int argc, char** argv){
  // Exit if no files are specified
  if ( argc < 2 ){
    std::cout << "Usage: compare-containers [FILE]...\n";
    return 1;
  }
  
  // Create maps to associate each file name with the container of words
  std::map<std::string, std::set<std::string> > files_set;
  std::map<std::string, std::unordered_set<std::string> > files_hash;
  std::map<std::string, std::unordered_set<std::string, MyHash> > files_myhash;
  std::map<std::string, MyDS > files_myds;

  /* Create simple arrays to store the statistics of each container, indexed as:
   *   0: Time taken to store the words of all the files
   *   1: Minimum search time for a word
   *   2: Maximum time taken to search for a word
   *   3: Total time taken to search for each word (used internally)*
   *   4: Total words searched for (used internally)*
   * * Used to calculate the average search time for the word
   */
  double stats_set[5] = {};
  double stats_hash[5];
  double stats_myhash[5];
  double stats_myds[5];
  
  unsigned long long t1, t2;
  unsigned long time_sec;

  for(int i = 1; i < argc; i++){
    // Open each file
    std::ifstream infile(argv[i]);
    if (infile){
      // Variables to read each word
      std::string s;
      std::string delimiters = "\n\t!()-:;\",.?/ ";


      // Create the set container
      files_set[argv[i]] = std::set<std::string>();

      // Read in the files
      t1 = cputime();
      while (infile.good()){
        getline(infile, s);
        std::size_t current;
        std::size_t next = -1;
        do {
          current = next + 1;
          next = s.find_first_of(delimiters, current);
          files_set[argv[i]].insert(s.substr(current, next-current));
        } while (next != std::string::npos);
      }
      t2 = cputime();
      stats_set[0] += (t2-t1)*iCPS;
      
      // Reset file
      infile.clear();
      infile.seekg(0);

      // Hash container
      files_hash[argv[i]] = std::unordered_set<std::string>();
      // Read in the files
      t1 = cputime();
      while (infile.good()){
        getline(infile, s);
        std::size_t current;
        std::size_t next = -1;
        do {
          current = next + 1;
          next = s.find_first_of(delimiters, current);
          files_hash[argv[i]].insert(s.substr(current, next-current));
        } while (next != std::string::npos);
      }
      t2 = cputime();
      stats_hash[0] += (t2-t1)*iCPS;
      
      // Reset file
      infile.clear();
      infile.seekg(0);

      // MyHash container
      files_myhash[argv[i]] = std::unordered_set<std::string, MyHash>();
      // Read in the files
      t1 = cputime();
      while (infile.good()){
        getline(infile, s);
        std::size_t current;
        std::size_t next = -1;
        do {
          current = next + 1;
          next = s.find_first_of(delimiters, current);
          files_myhash[argv[i]].insert(s.substr(current, next-current));
        } while (next != std::string::npos);
      }
      t2 = cputime();
      stats_myhash[0] += (t2-t1)*iCPS;
      
      // Reset file
      infile.clear();
      infile.seekg(0);

      // MyDS container
      files_myds[argv[i]] = MyDS();
      // Read in the files
      t1 = cputime();
      while (infile.good()){
        getline(infile, s);
        std::size_t current;
        std::size_t next = -1;
        do {
          current = next + 1;
          next = s.find_first_of(delimiters, current);
          files_myds[argv[i]].push(s.substr(current, next-current));
        } while (next != std::string::npos);
      }
      t2 = cputime();
      stats_myds[0] += (t2-t1)*iCPS;


      // Close file
      infile.close();
    } // Nothing to do if file isn't open, since it does not exist
  }
  
  // User prompt
  std::vector<std::string> user_input; // Vector to hold all user input
  std::string cur_input; // Holds current input
  std::cin >> cur_input;
  while(cur_input != "x"){
    // Store word in vector
    user_input.push_back(cur_input);
    // Get next input
    std::cin >> cur_input;
  }

  std::vector<std::string>::const_iterator itr;
  for (itr = user_input.begin(); itr != user_input.end(); itr++){
    // Search each set container for the file
    std::cout << *itr << " set";
    for(int i = 1; i < argc; i++){
      if(files_set.find(argv[i]) != files_set.end()){
        std::set<std::string>::const_iterator result_itr;
        t1 = cputime();
        result_itr = files_set[argv[i]].find(*itr);
        t2 = cputime();
        // If found, output result
        if (result_itr != files_set[argv[i]].end())
          std::cout << " " << argv[i];

        // Update stats
        time_sec = (t2-t1)*iCPS;
        if(time_sec < stats_set[1] || stats_set[1] == 0)
          stats_set[1] = time_sec;

        if(time_sec > stats_set[2] || stats_set[2] == 0)
          stats_set[2] = time_sec;

        stats_set[3] += time_sec;
        ++stats_set[4];
      }
    }
    std::cout << std::endl;

    // Search each hash container for the file
    std::cout << *itr << " hash";
    for(int i = 1; i < argc; i++){
      if(files_hash.find(argv[i]) != files_hash.end()){
        std::unordered_set<std::string>::const_iterator result_itr;
        t1 = cputime();
        result_itr = files_hash[argv[i]].find(*itr);
        t2 = cputime();
        // If found, output result
        if (result_itr != files_hash[argv[i]].end())
          std::cout << " " << argv[i];

        // Update stats
        time_sec = (t2-t1)*iCPS;
        if(time_sec < stats_hash[1] || stats_hash[1] == 0)
          stats_hash[1] = time_sec;

        if(time_sec > stats_hash[2] || stats_hash[2] == 0)
          stats_hash[2] = time_sec;

        stats_hash[3] += time_sec;
        ++stats_hash[4];
      }
    }
    std::cout << std::endl;
    
    // Search each myhash container for the file
    std::cout << *itr << " myhash";
    for(int i = 1; i < argc; i++){
      if(files_myhash.find(argv[i]) != files_myhash.end()){
        std::unordered_set<std::string, MyHash>::const_iterator result_itr;
        t1 = cputime();
        result_itr = files_myhash[argv[i]].find(*itr);
        t2 = cputime();
        // If found, output result
        if (result_itr != files_myhash[argv[i]].end())
          std::cout << " " << argv[i];

        // Update stats
        time_sec = (t2-t1)*iCPS;
        if(time_sec < stats_myhash[1] || stats_myhash[1] == 0)
          stats_myhash[1] = time_sec;

        if(time_sec > stats_myhash[2] || stats_myhash[2] == 0)
          stats_myhash[2] = time_sec;

        stats_myhash[3] += time_sec;
        ++stats_myhash[4];
      }
    }
    std::cout << std::endl;
    
    // Search each myds container for the file
    std::cout << *itr << " myds";
    for(int i = 1; i < argc; i++){
      if(files_myds.find(argv[i]) != files_myds.end()){
        t1 = cputime();
        if (files_myds[argv[i]].search(*itr))
          std::cout << " " << argv[i];
        t2 = cputime();

        // Update stats
        time_sec = (t2-t1)*iCPS;
        if(time_sec < stats_myds[1] || stats_myds[1] == 0)
          stats_myds[1] = time_sec;

        if(time_sec > stats_myds[2] || stats_myds[2] == 0)
          stats_myds[2] = time_sec;

        stats_myds[3] += time_sec;
        ++stats_myds[4];
      }
    }
    std::cout << std::endl;


  }

  // After exiting, output stats for each container
  std::cout << std::setprecision(3) << std::fixed;
  std::cout << "set: store " << stats_set[0] << " s, search: min "
    << stats_set[1] << " s, max " << stats_set[2] << " s, mean "
    << stats_set[3] / stats_set[4] << " s" << std::endl;
  std::cout << "hash: store " << stats_hash[0] << " s, search: min "
    << stats_hash[1] << " s, max " << stats_hash[2] << " s, mean "
    << stats_hash[3] / stats_hash[4] << " s" << std::endl;
  std::cout << "myhash: store " << stats_myhash[0] << " s, search: min "
    << stats_myhash[1] << " s, max " << stats_myhash[2] << " s, mean "
    << stats_myhash[3] / stats_myhash[4] << " s" << std::endl;
  std::cout << "myds: store " << stats_myds[0] << " s, search: min "
    << stats_myds[1] << " s, max " << stats_myds[2] << " s, mean "
    << stats_myds[3] / stats_myds[4] << " s" << std::endl;
}