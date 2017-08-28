# ECC
it is implemented using ecc, have fun.
This is the information of this algorithm https://en.wikipedia.org/wiki/Elliptic_curve_cryptography

use --generate our generate function in this case just do initailzation, no output.  e.g. ./c1 --generate
use --encrypt to encrypt the message, the key should also be added to do encryption, the cyphertext will be splited into 4 parts.   e.g. ./c1 --generate --encrypt ProfManuelandhistasareawsome --key yourkey
use --decrypt to decrypt the cyphertext, remenber to add your key. The encrypted message has four parts, thus when decrypting it, using -decrypt1 *decryptmessage1* -decrypt2 *decryptmessage2* -decrypt3 *decryptmessage3* -decrypt4 *decryptmessage4* --key yourkey

you need to guess the key in order to break this cypher.
after you get the result of decypher, which is a number, run ./mapback and follow the instruction so that the numbers could be mapped back to characters.


