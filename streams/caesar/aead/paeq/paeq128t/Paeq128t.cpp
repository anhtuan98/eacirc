#include "Paeq128t.h"
#include "paeq128t_encrypt.h"
#include "../../common/api.h"
#include "EACglobals.h"

Paeq128t::Paeq128t(int numRounds)
    : CaesarInterface(CAESAR_PAEQ128T, numRounds, CRYPTO_KEYBYTES, CRYPTO_NSECBYTES, CRYPTO_NPUBBYTES, CRYPTO_ABYTES) {
    if (numRounds < -1 || numRounds > maxNumRounds) {
        mainLogger.out(LOGGER_WARNING) << "Weird number of rouds (" << numRounds << ") for " << shortDescription() << endl;
    }
    if (numRounds == -1) {
        Paeq128t_raw::numRounds = maxNumRounds;
        CaesarCommon::numRounds = maxNumRounds;
    } else {
        Paeq128t_raw::numRounds = m_numRounds;
        CaesarCommon::numRounds = m_numRounds;
    }
}

Paeq128t::~Paeq128t() { }

int Paeq128t::encrypt(bits_t *c, length_t *clen, const bits_t *m, length_t mlen,
                       const bits_t *ad, length_t adlen, const bits_t *nsec, const bits_t *npub,
                       const bits_t *k) {
    return Paeq128t_raw::crypto_aead_encrypt(c, clen, m, mlen, ad, adlen, nsec, npub, k);
}

int Paeq128t::decrypt(bits_t *m, length_t *outputmlen, bits_t *nsec,
                       const bits_t *c, length_t clen, const bits_t *ad, length_t adlen,
                       const bits_t *npub, const bits_t *k) {
    return Paeq128t_raw::crypto_aead_decrypt(m, outputmlen, nsec, c, clen, ad, adlen, npub, k);
}

std::string Paeq128t::shortDescription() const {
    return "Paeq128t";
}
