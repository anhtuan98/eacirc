#ifndef AES128MARBLE4RV1_H
#define AES128MARBLE4RV1_H

#include "../../../CaesarInterface.h"

class Aes128marble4rv1 : public CaesarInterface {
    static const int maxNumRounds = -1;
public:
    Aes128marble4rv1(int numRounds);
    ~Aes128marble4rv1();
    int encrypt(bits_t *c, length_t *clen, const bits_t *m, length_t mlen,
                        const bits_t *ad, length_t adlen, const bits_t *nsec, const bits_t *npub,
                        const bits_t *k);
    int decrypt(bits_t *m, length_t *outputmlen, bits_t *nsec,
                        const bits_t *c, length_t clen, const bits_t *ad, length_t adlen,
                        const bits_t *npub, const bits_t *k);
    std::string shortDescription() const;
};

#endif // AES128MARBLE4RV1_H
