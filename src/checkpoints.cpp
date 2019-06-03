// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0,      Params().HashGenesisBlock())
        (2,      uint256("0x00000b51534c5d3f153c9fde7e3610a59f8d9bcef92a7c4ca0f298e8a8ba7616"))
        (11,	 uint256("0x000033a166c7a660425b244d9b79fd7f3eb1a7829071a5c244408d2cf4f29196"))
        (90,	 uint256("0x00003bef52846d9e8e5a7da540d7bc2fa42eacb2d283cc5fa71353d23ed5070a"))
        (119,	 uint256("0x000008b7ea6c57e3310fbc86a199e9c2f67736d2084f126a3d0ce663180772d4"))
        (470,    uint256("0xe9a58103149f76624bfd36804e795092edbc68d3c863baae29cd5eca5258eb37"))
        (500,    uint256("0x0000000077a93c8d1ecc315b65ddc6abad9cee653ea857fe7048ab7cbb7d4035"))
        (700,    uint256("0x929b9e5143afa18bc26ce0c4a9f1b24846930f635aaf259498624d65afa2ccb4"))
        (1100,   uint256("0x00000000003c3be21fb6a875a08a2c1d86ca5def9c167c86d62e260beefcf5be"))
        (1500,   uint256("0x089f5f8c970f805c1e057bc0fc2cb4b0778d82c962d50ba65dc81721f0951043"))
        (5000,   uint256("0x95100ec38b68551610740b66f866fbffb7a7bff6343b2560b89bdccfd2b3e9ca"))
        (7000,   uint256("0xda8a960625b85c343dbf3186252e301e6de1a7606722e3f447575ae5f9edebe5"))
        (9000,   uint256("0x000000000038c06d0e026d9dfb5f8f82115d0aa6b110838cfd9bf3968929ae11"))
        (10000,  uint256("0x0000000000431ff319bdb5df30811575ceae93ff920e10c5bcdf4f7e99b3364c"))
        (20000,  uint256("0x58cf54da0b328fac63bd54bdc079da09c6bf46b2c2395e5aeecabc7ca0b714e9"))
        (25000,  uint256("0xe9b208f654e89ba6b5ece2adf5b15a517aa36ab26d61fb724b1a54319599c2a9"))
        (50000,  uint256("0x3dcbc03d65479fb43c690a85b11f14d6dfdb481a98f396c80e70230a64292bee"))
        (70000,  uint256("0xc65d21c57164bc6ceea5267c7a728ffb4c5266bcc8e5efb74b999d42fdfe9106"))
        (73900,  uint256("0x66de18e9a9c622c814910c9ab94328cc8ebc0ea9bcd448ab4c5657eb05aa75ee"))
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
