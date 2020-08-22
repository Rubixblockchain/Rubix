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
        (0,     Params().HashGenesisBlock() )
        (1,      uint256("0x0003071185b88b3b7ac32ce3a04c9e4bc5b485aee7f9d4be0cd906b8158ee2b4"))
        (10,      uint256("0x0001d465f5ba77a70cda9f5149619567edd0afe9ca40415709354ae534b66e89"))
        (100,    uint256("0x542a8101388444870dde573f2c126dcf9666bfe1664efa3dae647892e22cf916"))
        (150,    uint256("0xe18d2f78673c4503fc078eb9aeded8fe33d6db9f46a5d49ffd648d666607499a"))
        (175,    uint256("0x1bc95bf898bf5ad5868f079717158bd3a1314a534bbaea965fb36c9a26843f2d"))
        (500,      uint256("0xee09e49dc639a43f10f06ccbb54e53e77b05933f0923e9e4e8d499358a0f6d0a"))
        (1000,      uint256("0xfd7b4850ebe601810c03f46b8d11c38de7c5ed59253b373187b263ee5e0a32eb"))
        (2500,    uint256("0x00022741d81f82864f64b13489736a64f68898fe6662d7e24e85744fecf82e10"))
        (5000,    uint256("000001a9cae6e86f313e38481025b5f304bdf905dc1b963186edd0c2bd60ecebb"))
        (8000,    uint256("0x0003d6e039c2797cba50ff372c44c806fc99bedabaa11bd98f3d617ec6d94cb0"))
        (10000,      uint256("0x00030c5a94d8427ac83ce22b9534a161b2529fa44bf61a610041d8a3792f7d77"))
        (14000,    uint256("0xd33516463f528898ef6dcfcb5beb73e80625a3d5d7b6a3e6d2b6426b9af285e5"))
        (18000,    uint256("0x0000000000023a7e0116efa99b518f0ce2cb9689ba31f13e35aeccc6aa359f09"))
        (19000,    uint256("0x0000000000019619935fdce0d4468e31443ed4fd6b969419fc9e14b2f1c25894"))
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
