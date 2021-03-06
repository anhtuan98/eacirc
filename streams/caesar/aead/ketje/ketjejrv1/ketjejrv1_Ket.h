/*
The Ketje authenticated encryption scheme, designed by Guido Bertoni,
Joan Daemen, Michaël Peeters, Gilles Van Assche and Ronny Van Keer.
For more information, feedback or questions, please refer to our website:
http://ketje.noekeon.org/

Implementation by the designers,
hereby denoted as "the implementer".

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#ifndef _Ket_h_
#define _Ket_h_

#include "ketjejrv1_KeccakP-interface.h"

// CHANGE namespace moved due to includes
namespace Ketjejrv1_raw {

#define FRAMEBITSEMPTY	0x01
#define FRAMEBITS0		0x02
#define FRAMEBITS00		0x04
#define FRAMEBITS10		0x05
#define FRAMEBITS01		0x06
#define FRAMEBITS11		0x07

//	Ketje rounds
#define Ket_StartRounds		12
#define Ket_StepRounds		1
#define Ket_StrideRounds	6

#define	Ketje_BlockSize	(2*KeccakF_laneInBytes)

/**
  * Function to extract one byte from the permutation state.
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  offset              Offset in bytes where to extract from state.
  *
  * @return Value of byte at given offset in state
  */
unsigned char Ket_StateExtractByte( void *state, unsigned int offset );

/**
  * Function to overwrite data in the permutation state.
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  offset              Offset in bytes where to start in state.
  * @param  data	            Pointer to data.
  * @param  length 	            Length in bytes.
  */
void Ket_StateOverwrite( void *state, unsigned int offset, const unsigned char *data, unsigned int length );

/**
  * Function to XOR one byte into the permutation state.
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  offset              Offset in bytes where to XOR in state.
  * @param  data	            Data value.
  */
void Ket_StateXORByte( void *state, unsigned int offset, unsigned char data );

/**
  * Function that performs a step, after XORing a framing byte into the state at requested offset. 
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  size                Offset in bytes where to XOR the framing value in the state.
  * @param  frameAndPaddingBits Framing value to pad after data.
  */
void Ket_Step( void *state, unsigned int size, unsigned char frameAndPaddingBits ); 

/**
  * Function that feeds (partial) associated data that consists of a sequence of complete Ketje blocks.
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  data	            Pointer to associated data.
  * @param  nBlocks             Number of associated data blocks.
  */
void Ket_FeedAssociatedDataBlocks( void *state, const unsigned char *data, unsigned int nBlocks );

/**
  * Function that presents a (partial) plaintext body that consists of a
  * sequence of blocks for wrapping. 
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  plaintext           The (partial) plaintext body.
  * @param  ciphertext          The buffer where enciphered data will be stored, can be equal to plaintext buffer.
  * @param  nBlocks             Number of blocks.
  */
void Ket_UnwrapBlocks( void *state, const unsigned char *ciphertext, unsigned char *plaintext, unsigned int nBlocks );

/**
  * Function that presents a (partial) ciphertext body that consists of a
  * sequence of blocks for unwrapping. 
  *
  * @param  state    		    Pointer to the permutation state.
  * @param  ciphertext          The (partial) ciphertext body.
  * @param  plaintext           The buffer where deciphered data will be stored, can be equal to ciphertext buffer.
  * @param  nBlocks             Number of blocks.
  */
void Ket_WrapBlocks( void *state, const unsigned char *plaintext, unsigned char *ciphertext, unsigned int nBlocks );

#endif

} // namespace Ketjejrv1_raw
