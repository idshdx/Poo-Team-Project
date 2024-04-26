#include "VotingSystem.h"
#include "seal/seal.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace seal;

int main() {
    VotingSystem votingSystem;

    // Voter 1 votes for the first option
    vector<uint64_t> votes1(5, 0);
    votes1[0] = 1; // Vote for option 1
    Ciphertext encrypted1 = votingSystem.encryptVotes(votes1);

    // Voter 2 votes for the second option
    vector<uint64_t> votes2(5, 0);
    votes2[1] = 1; // Vote for option 2
    Ciphertext encrypted2 = votingSystem.encryptVotes(votes2);

    // Voter 3 votes for the fifth option
    vector<uint64_t> votes3(5, 0);
    votes3[4] = 1; // Vote for option 5
    Ciphertext encrypted3 = votingSystem.encryptVotes(votes3);

    // Add all votes together
    Ciphertext total_votes = encrypted1;
    votingSystem.addVotes(total_votes, encrypted2);
    votingSystem.addVotes(total_votes, encrypted3);

    // Decrypt and display results
    vector<uint64_t> results = votingSystem.decryptResult(total_votes);
    cout << "Voting results:" << endl;
    for (size_t i = 0; i < results.size(); i++) {
        cout << "Option " << (i + 1) << ": " << results[i] << " votes" << endl;
    }

    return 0;
}
