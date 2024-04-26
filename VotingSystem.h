#ifndef VOTING_SYSTEM_H
#define VOTING_SYSTEM_H

#include "seal/seal.h"
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;
using namespace seal;

class VotingSystem {
private:
    EncryptionParameters params;
    SEALContext context;
    KeyGenerator keygen;
    PublicKey public_key;
    SecretKey secret_key;
    Encryptor encryptor;
    Evaluator evaluator;
    Decryptor decryptor;
    BatchEncoder encoder;
    size_t slot_count;

public:
    VotingSystem();

    vector<uint64_t> initVotes(vector<uint64_t> votes) const;

    Ciphertext encryptVotes(const vector<uint64_t>& votes);

    void addVotes(Ciphertext &total_votes, const Ciphertext& new_votes);

    static static int pickWinner(vector<uint64_t> &votes);

    vector<uint64_t> decryptResult(Ciphertext &encrypted_total);
};

#endif // VOTING_SYSTEM_H