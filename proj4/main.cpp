/* main.cpp
 * Corey Johns
 * COP4530 Fall 2012
 *
 * Modified interface from assignment 1.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "wordlist.h"

#define DEBUG 0

// Create the document map
std::map<std::string, WordList> docs;

// Function prototypes
void analyze(std::string);
void read_file(std::string&, std::ifstream&);
void query(std::string);
void print(std::string);

int main(int argc, char** argv){
  if ( argc < 2 ){
    std::cout << "Usage: Retrieve [FILE]...\n";
    return 1;
  }

  // Analyze files given as argument
  for(int i = 1; i < argc; i++){
    analyze(argv[i]);
  }

  // Enter user prompt
  std::string input;
  do {
    getline(std::cin, input);
    switch(input[0]){
      case 'a':
        if ( input.length() < 2 ){
          std::cout << "Error: No files specified!\n";
          break;
        }
        analyze(input.substr(2, input.length() - 2));
        break;
      case 'q':
        if ( input.length() < 2 ){
          std::cout << "Error: Number of documents, word list not specified!\n";
          break;
        }
        query(input.substr(2, input.length() - 2));
        break;
      case 'p':
        if (input.length() < 2){
          std::cout << "Error: Supply a number and filename!\n";
          break;
        }
        print(input.substr(2, input.length() - 2));
        break;
      case 'x':
        break;
      default:
        std::cout << "Error: Invalid command.\n";
        break;
    }
  } while (input[0] != 'x');
  return 0;
}

void analyze(std::string s){
  // First split up the parameters
  std::string delimiters = " ";
  std::size_t current;
  std::size_t next = -1;
  std::string filename;
  do {
    current = next + 1;
    next = s.find_first_of(delimiters, current);
    filename = s.substr(current, next-current);

    // Check if the file exists
    std::ifstream infile(filename.c_str());
    if (!infile){
      std::cout << "File " << filename << " does not exist\n";
    }
    else {
      // File exists, map the filename to a WordList obj and read in file
      docs[filename] = WordList(); // Will replace the results if filename exists
      read_file(filename, infile);
      infile.close();
    }
  } while (next != std::string::npos);
}

/* read_file
 *
 * Given a filename and ifstream handle, read in file to a WordList object
 */
void read_file(std::string &filename, std::ifstream &infile){
  std::string s, word;
  std::string delimiters = "\n\t!()-:;\",.?/ ";
  while (infile.good()){
    getline(infile, s);
    std::size_t current;
    std::size_t next = -1;
    do {
      current = next + 1;
      next = s.find_first_of(delimiters, current);
      word = s.substr(current, next-current);
      docs[filename].Add(word);

    } while (next != std::string::npos);
  }
  if (DEBUG)
    docs[filename].Print(100);
}

void query(std::string s){
  // Vector to hold parameters
  std::vector<std::string> word_list;

  // Split up the words
  std::string delimiters = " ";
  std::size_t current;
  std::size_t next = -1;
  int num_docs;
  int count = 0;
  do {
    current = next + 1;
    next = s.find_first_of(delimiters, current);
    if (count == 0){ // First parameter is the number of documents to return
      num_docs = std::atoi(s.substr(current, next-current).c_str() );
      count++;
    }
    else
      word_list.push_back( s.substr(current, next-current) );
  } while (next != std::string::npos);
  
  // Results map; document => sum of frequencies
  std::map<std::string, double> results;
  std::map<std::string, WordList>::iterator it;
  for ( it=docs.begin(); it != docs.end(); it++){
    // For each document
    std::vector<std::string>::iterator w_it;
    for ( w_it=word_list.begin(); w_it != word_list.end(); w_it++){
      double curr_word_freq = it->second.WordFreq(*w_it);
      if(curr_word_freq == 0){ // If any word is not in document, set freq to 0
        results[it->first] = 0;
        break;
      }
      results[it->first] += curr_word_freq;

      // ... YIKES!
    }

  }

  // Sort results by another map... There is probably a better way
  // but maps by definition can't sort by value
  std::map<double, std::string> sorted_results;
  std::map<std::string, double>::const_iterator r_it;
  int num_results = 0;
  for ( r_it=results.begin(); r_it != results.end(); r_it++){
    // Only put it in sorted_results if non-zero!
    if(r_it->second != 0){
      sorted_results[r_it->second] = r_it->first;
      num_results++;
    }
  }
  if(num_results == 0){
    std::cout << "No matching document\n";
    return;
  }
  count = 0;
  std::map<double, std::string>::const_reverse_iterator sr_it;
  for ( sr_it=sorted_results.rbegin(); sr_it != sorted_results.rend(); sr_it++){
    std::cout << sr_it->second << " " << sr_it->first << std::endl;
    count++;
    if(count == num_docs)
      break;
  }
}

void print(std::string s){
  // Split up the parameters
  std::string delimiters = " ";
  std::size_t current;
  std::size_t next = -1;
  int num_words;
  std::string filename;

  int count = 0;
  do {
    current = next + 1;
    next = s.find_first_of(delimiters, current);
    if (count == 0){ // First parameter is the number of words to return
      num_words = std::atoi(s.substr(current, next-current).c_str() );
      count++;
    }
    else if (count == 1){ // Second parameter is the filename
      filename = s.substr(current, next-current);
    }
  } while (next != std::string::npos);

  std::map<std::string, WordList>::iterator it = docs.find(filename);
  if ( it == docs.end() )
    std::cerr << "File " << filename << " has not been analyzed\n";
  else
    it->second.Print(num_words);
}
