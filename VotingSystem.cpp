#include "VotingSystem.h"

VotingSystem::VotingSystem() :
        params(seal::scheme_type::bfv),
        context(SEALContext(params)),
        keygen(context),
        encryptor(context, public_key),
        evaluator(context),
        decryptor(context, secret_key),
        encoder(context)
{
    params.set_poly_modulus_degree(4096);
    params.set_coeff_modulus(CoeffModulus::BFVDefault(4096));
    params.set_plain_modulus(256);
    slot_count = encoder.slot_count();

    keygen.create_public_key(public_key);
    secret_key = keygen.secret_key();
}

vector<uint64_t> VotingSystem::initVotes(vector<uint64_t> votes) const {
    if (votes.size() > slot_count) {
        throw invalid_argument("Too many votes");
    }
    return votes;
}

Ciphertext VotingSystem::encryptVotes(const vector<uint64_t>& votes) {
    Plaintext plain;
    encoder.encode(votes, plain);
    Ciphertext encrypted;
    encryptor.encrypt(plain, encrypted);
    return encrypted;
}

void VotingSystem::addVotes(Ciphertext &total_votes, const Ciphertext& new_votes) {
    evaluator.add_inplace(total_votes, new_votes);
}

int VotingSystem::pickWinner(vector<uint64_t> &votes) {
    return static_cast<int>(distance(votes.begin(), max_element(votes.begin(), votes.end())));
}

vector<uint64_t> VotingSystem::decryptResult(Ciphertext &encrypted_total) {
    Plaintext plain_result;
    decryptor.decrypt(encrypted_total, plain_result);
    vector<uint64_t> result;
    encoder.decode(plain_result, result);
    return result;
}