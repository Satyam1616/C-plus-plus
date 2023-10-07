#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <openssl/sha.h>

struct Block {
    int index;
    std::string previousHash;
    std::string data;
    std::string hash;
    time_t timestamp;

    Block(int idx, const std::string &prevHash, const std::string &data)
        : index(idx), previousHash(prevHash), data(data) {
        timestamp = std::time(0);
        hash = calculateHash();
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << index << previousHash << data << timestamp;
        return sha256(ss.str());
    }

    static std::string sha256(const std::string &input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input.c_str(), input.length());
        SHA256_Final(hash, &sha256);
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << static_cast<unsigned int>(hash[i]);
        }
        return ss.str();
    }
};

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain() {
        chain.emplace_back(Block(0, "0", "Genesis Block"));
    }

    const Block& getLatestBlock() const {
        return chain.back();
    }

    void addBlock(const std::string &data) {
        const Block &previousBlock = getLatestBlock();
        chain.emplace_back(Block(previousBlock.index + 1, previousBlock.hash, data));
    }
};

int main() {
    Blockchain blockchain;

    blockchain.addBlock("Transaction 1");
    blockchain.addBlock("Transaction 2");
    blockchain.addBlock("Transaction 3");

    for (const Block &block : blockchain.getChain()) {
        std::cout << "Block " << block.index << "\n";
        std::cout << "Previous Hash: " << block.previousHash << "\n";
        std::cout << "Data: " << block.data << "\n";
        std::cout << "Hash: " << block.hash << "\n";
        std::cout << "Timestamp: " << std::ctime(&block.timestamp) << "\n";
    }

    return 0;
}
