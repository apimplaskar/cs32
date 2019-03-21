//
//  Genome.cpp
//  project4
//
//  Created by Aditya Pimplaskar on 3/6/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <stdio.h>

#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include <cctype>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    ~GenomeImpl(){} //data is all in primitive types
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_seq;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_seq = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string temp_line;
    string temp_name;
    string temp_seq; 
    bool lastLineName = false; //was the last line a name?
    bool firstLine = true; // flag if we are looking at the first line
    
    if(!genomeSource){ return false; } //istream fails

    while(getline(genomeSource, temp_line)){
        if(temp_line[0] == '>'){ //first line of a genome
            if(firstLine){ firstLine = false; } 
            if(lastLineName){ return false; } //no sequence following the last name
            //push existing temp_name and temp_seq to a new genome if they are not empty
            if(temp_name.size() != 0 && temp_seq.size() != 0){
                genomes.push_back(Genome(temp_name, temp_seq));
                temp_name = ""; //reset
                temp_seq = "";
            }
            if(temp_line.size() <=1 ){ return false; } //empty name
            temp_name = temp_line.substr(1); //assign a new name to the next one
            lastLineName = true;
        }
        else{
            if(firstLine){ return false; } //if first line is not a name line
            if(temp_line.size() == 0){ return false; } //empty line
            for(int i = 0; i < temp_line.size(); i++){
                if(toupper(temp_line[i]) != 'A' && toupper(temp_line[i]) != 'G' && toupper(temp_line[i]) != 'C' && toupper(temp_line[i]) != 'T' && toupper(temp_line[i]) != 'N'){ return false; } //invalid character
                temp_seq += toupper(temp_line[i]); //need to loop so that we can ensure that we have uppercase chars
            }
            lastLineName = false;
        }
    }
    if(temp_name.size() != 0 && temp_seq.size() != 0){
        genomes.push_back(Genome(temp_name, temp_seq));
        temp_name = ""; //reset
        temp_seq = "";
    }
    return true;
}

int GenomeImpl::length() const
{
    return m_seq.length();  // Return length of sequence string
}

string GenomeImpl::name() const
{
    return m_name;  // Return the name
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if(position + length > this->length()){ return false; } //access out of bounds elements
    if(position < 0 || length < 0){ return false; } //sanity check
    for(int i = position; i < position+length; i++){
        fragment+=m_seq[i];
    }
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
