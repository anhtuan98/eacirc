#include "Pi64cipher256v1tworounds.h"
#include "pi64cipher256v1tworounds_encrypt.h"
#include "../../common/api.h"
#include "EACglobals.h"

Pi64cipher256v1tworounds::Pi64cipher256v1tworounds(int numRounds)
    : CaesarInterface(CAESAR_PI64CIPHER256V1TWOROUNDS, numRounds, CRYPTO_KEYBYTES, CRYPTO_NSECBYTES, CRYPTO_NPUBBYTES, CRYPTO_ABYTES) {
    if (numRounds < -1 || numRounds > maxNumRounds) {
        mainLogger.out(LOGGER_WARNING) << "Weird number of rouds (" << numRounds << ") for " << shortDescription() << endl;
    }
    if (numRounds == -1) {
        Pi64cipher256v1tworounds_raw::numRounds = maxNumRounds;
        CaesarCommon::numRounds = maxNumRounds;
    } else {
        Pi64cipher256v1tworounds_raw::numRounds = m_numRounds;
        CaesarCommon::numRounds = m_numRounds;
    }
}

Pi64cipher256v1tworounds::~Pi64cipher256v1tworounds() { }

int Pi64cipher256v1tworounds::encrypt(bits_t *c, length_t *clen, const bits_t *m, length_t mlen,
                       const bits_t *ad, length_t adlen, const bits_t *nsec, const bits_t *npub,
                       const bits_t *k) {
    return Pi64cipher256v1tworounds_raw::crypto_aead_encrypt(c, clen, m, mlen, ad, adlen, nsec, npub, k);
}

int Pi64cipher256v1tworounds::decrypt(bits_t *m, length_t *outputmlen, bits_t *nsec,
                       const bits_t *c, length_t clen, const bits_t *ad, length_t adlen,
                       const bits_t *npub, const bits_t *k) {
    return Pi64cipher256v1tworounds_raw::crypto_aead_decrypt(m, outputmlen, nsec, c, clen, ad, adlen, npub, k);
}

std::string Pi64cipher256v1tworounds::shortDescription() const {
    return "Pi64cipher256v1tworounds";
}
