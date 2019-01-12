// Copyright (c) 2016-2019 The CryptoCoderz Team / Espers
// Copyright (c) 2019 The CryptoCoderz Team / INSaNe project
// Copyright (c) 2018 The Rubix project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_GENESIS_H
#define BITCOIN_GENESIS_H

#include "bignum.h"

/** Genesis Start Time */
static const unsigned int timeGenesisBlock = 1499889600; // Wednesday, July 12, 2017 8:00:00 PM
/** Genesis TestNet Start Time */
static const unsigned int timeTestNetGenesis = 1499889600+30; // Wednesday, July 12, 2017 8:00:00 PM
/** Genesis RegNet Start Time */
static const unsigned int timeRegNetGenesis = 1499889600+90; // Wednesday, July 12, 2017 8:00:00 PM
/** Genesis Nonce Mainnet*/
static const unsigned int nNonceMain = 685486;
/** Genesis Nonce Testnet */
static const unsigned int nNonceTest = 68286;
/** Genesis Nonce Regnet */
static const unsigned int nNonceReg = 8;
/** Main Net Genesis Block */
static const uint256 nGenesisBlock("0x00001162af4b590b81270287faf239153aab5195279dd72147e5cc5438cb8b3e");
/** Test Net Genesis Block */
static const uint256 hashTestNetGenesisBlock("0x00004895f3c16404d555125ae523996d3400a79cb5817f4bc7ed55075a3696f2");
/** Reg Net Genesis Block */
static const uint256 hashRegNetGenesisBlock("0x9044431054951272a03417783f5cfb505d816f1c093d9e0bc934a5a04f2b8487");
/** Genesis Merkleroot */
static const uint256 nGenesisMerkle("0x6f05b593558f5b7e7218f90806ecb9cd44f1dc2d3ffbccbb273c0ae445c4505d");

#endif // BITCOIN_GENESIS_H
