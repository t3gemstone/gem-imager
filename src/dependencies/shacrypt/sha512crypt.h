#ifndef SHA512CRYPT_H
#define SHA512CRYPT_H

extern "C" {

char *
sha512_crypt (const char *key, const char *salt);

}

#endif // SHA512CRYPT_H
