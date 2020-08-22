// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2a;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x2b;
        vAlertPubKey = ParseHex("04c244288a8c6ebbf491443ebfa1207275d71cb009f201c118b00cf8e77641c7f1e63e330ba909842c009af375c0f5c1c7368e8d7e2066168c40ce3cb629cf212f");
        nDefaultPort = 20029;
        nRPCPort = 20167;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 18);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 18);

        const char* pszTimestamp = "Ethereum Price Drops Over 20% in 24 hours | JP Buntinx | July 12, 2017"; // Wednesday, July 12, 2017 8:00:00 PM";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = nGenesisBlockReward;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1499889600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = timeGenesisBlock;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 685486;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 6f05b593558f5b7e7218f90806ecb9cd44f1dc2d3ffbccbb273c0ae445c4505d
        block.nTime = 1499889600
        block.nNonce = 685486
        block.GetHash = 00001162af4b590b81270287faf239153aab5195279dd72147e5cc5438cb8b3e
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00001162af4b590b81270287faf239153aab5195279dd72147e5cc5438cb8b3e"));
        assert(genesis.hashMerkleRoot == uint256("0x6f05b593558f5b7e7218f90806ecb9cd44f1dc2d3ffbccbb273c0ae445c4505d"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,68);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,75);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,58);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

       // vSeeds.push_back(CDNSSeedData("someLabel",  "someIP"));
       // vSeeds.push_back(CDNSSeedData("someLabel",  "someIP"));
       // vSeeds.push_back(CDNSSeedData("someLabel",  "someIP"));
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "RmTXZQ9W92y13UkyEoxcEsbjA6oZeQUFZu";
        strDevOpsAddress = "RmG7TTPEJDhNAvK4jy2oShizc8WmeF7pKH";
        nEndPoWBlock = 0x7fffffff;
        nStartPoSBlock = 0;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0x44;
        pchMessageStart[3] = 0xb6;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04ac24ab003c828cdd9cf4db2ebbde8e1cecb3bbfa8b3127fcb9dd9b84d44112080827ed7c49a648af9fe788ff42e316aee665879c553f099e55299d6b54edd7e0");
        nDefaultPort = 20023;
        nRPCPort = 20024;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = timeTestNetGenesis;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 68286;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 6f05b593558f5b7e7218f90806ecb9cd44f1dc2d3ffbccbb273c0ae445c4505d
        block.nTime = 1499889630
        block.nNonce = 68286
        block.GetHash = 00004895f3c16404d555125ae523996d3400a79cb5817f4bc7ed55075a3696f2
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00004895f3c16404d555125ae523996d3400a79cb5817f4bc7ed55075a3696f2"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,129);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,77);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,36);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x98;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = timeRegNetGenesis;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = nNonceReg;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19421;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 6f05b593558f5b7e7218f90806ecb9cd44f1dc2d3ffbccbb273c0ae445c4505d
        block.nTime = 1499889690
        block.nNonce = 8
        block.GetHash = 9044431054951272a03417783f5cfb505d816f1c093d9e0bc934a5a04f2b8487
        */

        assert(hashGenesisBlock == uint256("0x9044431054951272a03417783f5cfb505d816f1c093d9e0bc934a5a04f2b8487"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}