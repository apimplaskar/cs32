//
//  GenomeMatcher.cpp
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
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
    static bool compare(const GenomeMatch& a, const GenomeMatch& b); //needs to be used when sorting the relatedGenomes' result array
private:
    int m_searchLength;
    Trie<DNAMatch> m_Trie;
    // vector<Genome> m_genomes;
    //unordered_map<string, const Genome*> m_genomes;
    unordered_map<string, const Genome> m_genomes;
    int scan(const DNAMatch& genome, int startIndex, const string& fragment, bool exactMatchOnly, int mimimumLength) const;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_searchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    //cout << "called addGenome" << endl;
    string to_add;
    m_genomes.insert(make_pair(genome.name(), genome));
    //add to our container of genomes
    for(int i = 0; i < genome.length(); i++){
        //the DNAMatch that will be the value in trie
        DNAMatch temp;
        temp.genomeName = genome.name();
        temp.position = i;
        temp.length = m_searchLength;
        
        if(genome.extract(i, m_searchLength, to_add)){ //if valid substring
           m_Trie.insert(to_add, temp); //add extracted substring to the hash table
        }

        to_add = ""; //reset
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_searchLength;
}


int GenomeMatcherImpl::scan(const DNAMatch& gen, int startIndex, const string& fragment, bool exactMatchOnly, int minimumLength) const{
    //cout << "Vector of genomes holds: " << m_genomes.size() << " items." << endl;
    /*
     GenomeMatcher Scanner
     for each genome sequence location
     extract genome sequence from pos to pos+fragment length
     compare:
     if num diff > 1 || differ in the first element: false
     if not,
     if it is longer than the old longest scan, store this in a temp variable
     if not, do nothing
     
     return the maximally long scan (in the temp variable)
     */
    
    bool allowError = !exactMatchOnly; //keeps track of error (if exactMatchOnly is false: then we will allow an error, if not it we won't allow an error)
    string g_seq;
    const Genome genome = m_genomes.at(gen.genomeName); //read genome in
    //need to extract the relevant sequence for the same genome!!!
    bool did_extract_work = genome.extract(startIndex, genome.length()-startIndex, g_seq);
    if(!did_extract_work){
        return -1; } //flag that it failed
    int len_match = 0;
    for(int i = 0; i < g_seq.size(); i++){
        if(g_seq[i] != fragment[i] && !allowError){ break; } //no more errors allowed
        else if(g_seq[i] != fragment[i]){
            allowError = false; //if we have one error, we can't allow any more
            len_match++;
        }
        else{
            len_match++; //number of matches increments
        }
    }
    if(len_match < minimumLength){
        //cout << "Failed because matches were not long enough" << endl;
        return -1; } //flag that it failed
    return len_match;
}


bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    //cout << "called findGenomesWithThisDNA" << endl;
    /*
     if fragment's length < minimumLength, return false
        TENTATIVELY if minimumLength < m_searchLength, return false
     
     frag_sub = substring of fragment that is length m_searchLength
      some vector =  m_Trie.find(frag_sub, exactMatchOnly); //finds all instances of frag_sub
     We now have a vector full of which genomes match and at which location
     For each genome found:
        Scan each found location in to find which one has the longest overlap
            This will use a helper fn.
            Push the one with the longest overlap into the vector
     if matches' size == 0, return false
     return true
     */
    
    if(fragment.length() < minimumLength){
        //cout << "returning false: fragment.length() < minimumLength" << endl;
        return false; }
    if(minimumLength < minimumSearchLength()){
        //cout << "returning false: minimumLength < minimumSearchLength()" << endl;
        return false; }
    
    string frag_sub = fragment.substr(0, m_searchLength);
    //cout << "Fragment substring that we are searching for: " << frag_sub << endl;
    vector<DNAMatch> init_matches = m_Trie.find(frag_sub, exactMatchOnly);
    
    //cout << "init matches size: " << init_matches.size() << endl;
    // for each DNA match:
        // figure out how long it goes
    
    bool updatedExisting;
    //for(DNAMatch i_match: init_matches){
    for(int i = 0; i < init_matches.size(); i++){
        //cout << "loop has run " << i << " times." << endl;
        DNAMatch i_match = init_matches[i];
        updatedExisting = false;
        //cout << "Called scan function " << endl;
        int ran_scan = scan(i_match, i_match.position, fragment, exactMatchOnly, minimumLength);
        //cout << "Scan worked? " << ran_scan << endl;
        if(ran_scan == -1){ continue; }
        else{
            for(DNAMatch match: matches){
                if(match.genomeName == i_match.genomeName) {
                    if (ran_scan > match.length){
                        match.length = ran_scan;
                        match.position = i_match.position;
                    }
                    updatedExisting = true;
                    break;
                }
            }
            if(!updatedExisting){
                DNAMatch addMe;
                addMe.genomeName = i_match.genomeName;
                addMe.position = i_match.position;
                addMe.length = ran_scan;
                matches.push_back(addMe);
            }
        }
    }
    return(matches.size() != 0);
}

bool GenomeMatcherImpl::compare(const GenomeMatch& a, const GenomeMatch& b){
    if(a.percentMatch == b.percentMatch){ //if the percent matches are the same, compare them based on their names
        return a.genomeName > b.genomeName;
    }
    return(a.percentMatch > b.percentMatch);
}


bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    /*
     The method MUST use the following algorithm to get full credit:
     We will consider sequences of length fragmentMatchLength from the query
     genome starting at positions 0, 1* fragmentMatchLength,2* fragmentMatchLength,
     etc. (e.g., if fragmentMatchLength were 12, the start positions would be 0, 12, 24,
     36). If the length of the query genome is not a multiple of fragmentMatchLength,
     we ignore the final sequence that is shorter than fragmentMatchLength. Let S be
     the number of sequences we will consider. For example, if the query genome
     were 800 bases long and fragmentMatchLength were 12, then since 800/12 is
     66.6667, S will be 66 (since we ignore the final 8 base long sequence).
     For each such sequence:
     1. Extract that sequence from the queried genome.
     2. Search for the extracted sequence across all genomes in the library (using
     findGenomesWithThisDNA()), allowing SNiP matches if exactMatchOnly
     is false).
     3. If a match is found in one or more genomes in the library, then for each
     such genome, increase the count of matches found thus far for it.
     For each genome g in the library that contained at least one matching sequence
     from the query genome:
     1. Compute the percentage p of sequences from the query genome that were
     found in genome g by dividing the number of matching sequences found
     in genome g by S (e.g., if S is 66, and 15 of the 66 sequences were found
     28
     in the genome, then 15/66 or 22.73% of the sequences from the query
     genome were found in that genome, so p will be 22.73).
     2. If p is greater than or equal to the matchPercentThreshold parameter (a
     percentage in the range 0 though 100), then g is a matching genome.
     Return from the function with the results vector containing all matching genomes,
     ordered in descending order by the match proportion p, and breaking ties by the
     genome name in ascending alphabetical order. The results vector contains
     GenomeMatch objects, where the GenomeMatch structure looks like this:
     struct GenomeMatch
     {
     std::string genomeName;
     double percentMatch;                //    0    to    100
     }
     */
    
    if(fragmentMatchLength < minimumSearchLength()){ return false; }
    
    unordered_map<string, int> countOfGenome;
    double numFragmentsToScan = query.length()/fragmentMatchLength;
    //cout << "num Fragments: " << numFragmentsToScan << endl;
    //initialize countOfGenome's int to 0
    for(int i = 0; i < numFragmentsToScan; i++){
        string sequence_fragment;
        bool didExtract = query.extract(i*fragmentMatchLength, fragmentMatchLength, sequence_fragment);
        if(!didExtract) { cerr << "Extraction failure." << endl; }
        vector <DNAMatch> genomesWFragments;
        bool foundGenomes = findGenomesWithThisDNA(sequence_fragment, fragmentMatchLength, exactMatchOnly, genomesWFragments);
        if(!foundGenomes) { cerr << "Genome finding failure" << endl; }
        
        //cout << "size of genomes with fragments vector: " << genomesWFragments.size() << endl;
        
        //Logs number of matches by genome
        for(int j = 0; j < genomesWFragments.size(); j++){
            unordered_map<string, int>::iterator loggingMatches;
            loggingMatches = countOfGenome.find(genomesWFragments[j].genomeName);
            if(loggingMatches == countOfGenome.end()){
                countOfGenome.insert(make_pair(genomesWFragments[j].genomeName, 1));
            }
            else{
                (*loggingMatches).second++;
            }
        }
    }
    //cout << "countOfGenome size: " << countOfGenome.size() << endl;
    unordered_map<string, int>::iterator it = countOfGenome.begin();
    while(it != countOfGenome.end()){
        //cout << "it second: " << it->second << endl;
        double percentMatch = ((it->second)/numFragmentsToScan) * 100;
        //cout << "% match: " << percentMatch << endl;
        if(percentMatch >= matchPercentThreshold){
            //we push that genome into the genome matches vector
            //cout << "enters !!! " << endl;
            GenomeMatch temp;
            temp.genomeName = it->first;
            temp.percentMatch = percentMatch;
            results.push_back(temp);
        }
        it++;
    }
    
    //cout << "size of results: " << results.size() << endl;
    
    sort(results.begin(), results.end(), compare);
    return (results.size() != 0);
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
