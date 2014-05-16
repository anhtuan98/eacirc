#ifndef _EACIRC_TERM_H
#define _EACIRC_TERM_H

#include "poly.h"
#include <assert.h> 
#include <vector>
#include <cmath>
#include <stdexcept>

// Basic element of the term array/vector.
typedef POLY_GENOME_ITEM_TYPE term_elem_t; 

// Number of the variables in a term type.
typedef unsigned long term_size_t;

// Typedef for the vector inside term
typedef std::vector<term_elem_t> term_t;

/**
 * GF2[x1, ..., xn]
 * 
 * One term in a polynomial.
 * Consists of an array of term_elem_t.
 * 
 * Note: Null term (all term_elem_t are zero) will
 * be evaluated to 1.
 *
 * It is not possible to express a zero term (not needed in
 * the polynomial representation of a function).
 * 
 * Term is stored in the internal vector in this way:
 * x_0  .. x_63  goes to the vector[0]
 * x_64 .. x_128 goes to the vector[1] ...
 * 
 */
class Term {
  protected:
    /**
     * Number of input variables.
     * i.e., bit input size.
     */
    term_size_t size;
    
    /**
     * Size of the vector derived from the size.
     * ceil(size / 8*sizeof(term_elem_t))
     */
    term_size_t vectorSize;
    
    /**
     * Internal term representation using a vector.
     */
    term_t * term;
    
    /**
     * Helper attribute - whether to ignore this term or not.
     * Used in transforming to ANF.
     * If true, this term should not appear in the ANF.
     * 
     * @param cT
     */
    bool ignore;
    
  public:  	
    /**
     * Default constructor.
     */
    Term () : size(0), vectorSize(0), term(NULL),  ignore(false) { }
    
    /**
     * Copy constructor.
     */
    Term (const Term &cT);
    
    /**
     * Instantiate using size.
     */
    Term (term_size_t size);
    
    /**
     * Instantiate using genome.
     */
    Term (term_size_t size, GA2DArrayGenome<POLY_GENOME_ITEM_TYPE>* pGenome, const int polyIdx, const int offset);
    
    /**
     * Getter for the size.
     */
    term_size_t getSize (void) const {return (size);}
    
    /**
     * Returns number of term building blocks if term has provided bit size.
     * @param bitSize
     * @return 
     */
    static inline unsigned int getTermSize(unsigned int bitSize) { return OWN_CEIL((double) bitSize / (8.0*(double)sizeof(term_elem_t))); };
    
    /**
     * Returns number of term building blocks if term has provided bit size, provided storage type.
     * @param bitSize
     * @param typeSize
     * @return 
     */
    static inline unsigned int getTermSize(unsigned int bitSize, unsigned int typeSize) { return OWN_CEIL((double) bitSize / (8.0*(double)typeSize)); };
    
    /**
     * Setter only for the size. Performs no initialization.
     */
    Term * setSize(term_size_t size) {
        this->size = size; 
        this->vectorSize = (term_size_t) OWN_CEIL((double) size / (8.0*(double)sizeof(term_elem_t)));
        return this;
    }
    
    /**
     * Term initializer, set size has to be called before.
     */
    Term * initialize();
    
    /**
     * Term initializer, able to set new size.
     * @param 
     * @return 
     */
    Term * initialize(term_size_t);
    
    /**
     * Initialize term from the genome.
     * 
     * @param pGenome
     * @param polyIdx           1. D index (which polynomial to use.
     * @param offset            2. D offset where to start reading.
     * @return 
     */
    Term * initialize(term_size_t size, GA2DArrayGenome<POLY_GENOME_ITEM_TYPE>* pGenome, const int polyIdx, const int offset);
    
    /**
     * Dumps term to the genome.
     * Writes vector[0] .. vector[n] to the genome (thus ordering is x_0 ... x_size).
     * 
     * @param pGenome
     * @param polyIdx
     * @param offset
     */
    void dumpToGenome(GA2DArrayGenome<POLY_GENOME_ITEM_TYPE>* pGenome, const int polyIdx, const int offset) const;
    
    /**
     * Sets particular bit in the term,
     * @param bit
     * @param value
     */
    void setBit(unsigned int bit, bool value);
    bool getBit(unsigned int bit) const;
    void flipBit(unsigned int bit);
    
    bool getIgnore() const { return this->ignore; }
    Term * setIgnore(bool ign) { this->ignore = ign; return this; }
    
    // Comparator for sorting
    int compareTo(const Term& other) const;
    int compareTo(const Term * other) const;
    
    // Assignment operator
    Term& operator=(const Term& other);
    bool operator<(const Term& other)   const { return this->compareTo(other)==-1;    }
    bool operator<=(const Term& other)  const { return this->compareTo(other)!=1;     }
    bool operator>(const Term& other)   const { return this->compareTo(other)==1;     }
    bool operator>=(const Term& other)  const { return this->compareTo(other)!=-1;    }
    
    // Operations required by the library.
    //friend bool operator= (Term &cT);
    friend bool operator== (const Term &cT1, const Term &cT2);
    friend bool operator!= (const Term &cT1, const Term &cT2);
    
    // Evaluation
    bool evaluate(const unsigned char * input, term_size_t inputLen) const;
    
    /**
     * Returns position of a particular bit w.r.t. term elements (POLY_GENOME_ITEM_TYPE).
     * Returns index of POLY_GENOME_ITEM_TYPE
     * @return 
     */
    static inline unsigned int getBitPos(int bitIdx, int termIdx, unsigned int termSize) { return 1 + termIdx*termSize + (bitIdx/(8*sizeof(POLY_GENOME_ITEM_TYPE))); }
    
    /**
     * Returns position of a particular bit inside term element.
     * Returns bit position inside POLY_GENOME_ITEM_TYPE.
     * @return 
     */
    static inline unsigned int getBitLoc(int bitIdx) { return bitIdx % (8*sizeof(POLY_GENOME_ITEM_TYPE)); }
};

// Pointer to the term.
typedef Term * PTerm;

inline bool operator== (const Term &cT1, const Term &cT2){ return cT1.compareTo(cT2) == 0; }
 
inline bool operator!= (const Term &cT1, const Term &cT2){ return !(cT1 == cT2); }

// Term comparator
struct TermComparator {
  bool operator() (const Term& lhs, const Term& rhs) const { return lhs.compareTo(rhs) == -1; }
};

// PTerm comparator
struct PTermComparator {
  bool operator() (const PTerm& lhs, const PTerm& rhs) const { return lhs->compareTo(rhs) == -1; }
};



#endif  // end of file