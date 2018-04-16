// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2017-2018 The LitecoinZ and ConbiniCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "crypto/equihash.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "base58.h"

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 0;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime     = nTime;
    genesis.nBits     = nBits;
    genesis.nNonce    = nNonce;
    genesis.nSolution = nSolution;
    genesis.nVersion  = nVersion;

    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();

    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database (and is in any case of zero value).
 *
 * >>> from pyblake2 import blake2s
 * >>> 'ConbiniCoin' + blake2s(b'NY Times 05/Oct/2011 Steve Jobs, Apple’s Visionary, Dies at 56LTC#433272 27659f4c97de825afe9f1d4ab6c2ba4e83751a11f0144905b0fec849c36fb1ce LTC#741825 27659c79fbb898e9c35f55d49126afcc3a63d1501d399651f21980c538cbaa8f DJIA close on 29 Nov 2017: 23,940.68').hexdigest()
 */
static CBlock CreateGenesisBlock(uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion)
{
    const char* pszTimestamp = "ConbiniC0519e6b00b75f8e572fe01a8c277250f683c736d4c6f3e9df6b102eed7d4e4dd";
    const CScript genesisOutputScript = CScript() << ParseHex("04da16b9af2c85fa8ec666046ccc0b2d5a5fa992867257a701cf7758c3e7464ba3c4cc9e22f1fb30c8944ab2bdb35c21dd21b563b7a51dbc0e78be46e809e4b8ff") << OP_CHECKSIG;

    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nSolution, nBits, nVersion);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "CONBINI";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;

        pchMessageStart[0] = 0xd8;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0xcd;
        pchMessageStart[3] = 0x93;
        vAlertPubKey = ParseHex("04aef689da1e268663f53c4157fac611af2a7211e0694873d66327aed938a77f483d9bacade8da7cff1d402820899970b764c5f3508e3dc52fdcecf82679911ae9");

        nDefaultPort = 29333;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;
        const size_t N = 200, K = 9;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        genesis = CreateGenesisBlock(
            1512832667,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000001610"),
            ParseHex("008abde46ca8e31bbcbdb0c02713b4f8d7d85ccee24a0b33aef216ab6b5948258f2b7ddc7a34851c336b158fc5a08b07c861079899506267b3ab7849fcc5ce529c2ebd05b05f97fcb19882775966dad45337290701ab2b2938e3ee7175ed0164111f1b8916ba92c78e100c945919899b09e6f5d4563765dfe926c9f47cc601fd1a4cb88b0f211b6ca3b0477d5845a61c14cd430cdf3c59359e378d70901277aeb57ca5f7ed1f2ce609ccdfc9bbe91961d69fd2b0489e194a1024dfed0e0e5eb1a591c83f499c0103925fe81e9db1dff9106d154e3b41c9e3ab113805a43ed0e296ea179cb99d91445854f6a8d185f59c54d9d5ed7b9cee8b061aa8f90b82c788e8a14cd1425a01acc6125948aa2ecf39e5104fd12c545cd9c5715a31570af29f9d67373fc70115a84ab06367d43bff89582f384c8f464e4b98992319f7fcb675cb83d75fe89a729577bd5336331ce16200bfc5f0bfc89cbd999ca16a859f6c3090b896a85e2095497fd6cbe0ea735184df8e43ef16be0bd93d891561fd0f26ad955dc4e3f3f96652d4115c62d4ff4f35084bbac0cfdbd7506896beedcda35aab70166ed10253d360b2c555c8c523d0c04e6673e92e8f33be3c2945ed1b67dc927d5331c6d236f8caea3f5f3cdd4203ca335eb19630373d9a50c528a9daf5b9abb9c7da14bcc4f72360b9abe2e803c64a5055ed52d81d6744064aee8c188637608ac341fbfcc42460a4e19ec4af0d634c121ed595e2ddbc32756b9fef809eaabfc90409869b3c8d8eb48cb114158f25d9d80a0d95bdc72638b22a2cfad7dc5f0d26546701392e5d89f3b838c60b92364395897d76ac47f8f366ff647ef9813cacdb1a85cd1ac4120bd90703c2ba76763e5cf3003900e41ac16b52f70f1810eafed38f53d32f76696fdf955f2194fa44a7cdc3b3a3cab6e9f2ef1d82049b14831d01f039d0dc808fb585688558516c18475b023d227d0d904feba285a31432b661605f72aca4939024b8c824e85c2d2bb09e5d8a409478a2255b253e0dbd582d398594598a97d747000a67e0cf5e13fa11139d0e4b032c7d6b97528375cb58e8bf4d4df486552938c0ba1030aa8e9f90f3eef21c84d103f12371ae18715bd406ae863e1f57bd1911122312f6d64292f6db3d9a354c69c5fa7adb8fd14be2c68eb1e7dcca756bf67f28050e5c487593854f9c66831349c1ee7595e4cef7a730a376d2b0ce600d8985e748fad07592d15f3efc750dd65c094ae1ce57d3c8d888a47ec7f644a5b4d3710edd1dd43d6f2fe7cd3442fd5234eaed6a356b6ca507802ee7cdb5ee33ffc9384c85dd1d2aa1a85a8c1316e863f531cb86bb620595828c3478c9cd3954c13215e4c28daa090d99de47d30521c743f5db175b89925339440594b7388dcbf796d507ca1e6dec5734bbe602de8a4c0105b44cb6d15691e270b4764903b2cd0322b0069d9c0c769b7d1e731bb2e6acede8777f388f08e9b08a3545b87e55513617b1b1ee4a00629faf8b116ab6c77d553da780e3d90199efc92f03829f940d05868359149514d54d19967c1ed3dc7a7324d7bac242d90b28f1d4b650b3eeb6b91cccd272b5b2da9761079f9285500ab63e6a1250f1baf7f83d05ac9fad4e4878cd9fe5591fffeb8e75a26c418399918edd453b0f59d9bf529c07d164daa7e458c03ab2ec1f5ab971193c3f0808a2af257895334941d0566d3d6177fd8e0f6d6bb81a91a36d32dc51df103517bb1b4c3a9c431caf4da254ebcb57b3d491d7b3a43ad66062dc27920f94e7de6e22ec77fc2ec2f65a3a284113c02d86bf1fdf5908bd5cc531f672f212a5b230cdb1bfbf5019112b7d135b9fee7963995a8e427ddb9acd21f8ed6661bf3c2c8d20f6eb205807617150aa51e34691c239"),
            0x1f07ffff, 4);

        consensus.hashGenesisBlock = genesis.GetHash();
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
        assert(genesis.hashMerkleRoot == uint256S("0x87800ace8ce2299bbf33ac3f76186ee66be9d7de9a9e22cdba040d3c4776870e"));
        assert(consensus.hashGenesisBlock == uint256S("0x0003f52e78c166a7f44506c152f5e1df1577f21cb7062f863dd8f9a47e125ff9"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("1efb6b60d74ed972e0x7cb89cb3fcf7c933bbd38572af35e58ee19604609061d369e99134b9c811fedb2369fa90940b6a9533f2ae73aa11bb55346f5823fa2f653.CONBINI", "conbinicoin.com"));

        // guarantees the first 2 characters, when base58 encoded, are "L1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x0A,0xB5};
        // guarantees the first 2 characters, when base58 encoded, are "L3"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x0A,0xB9};
        // the first character, when base58 encoded, is "5" or "K" or "L" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0x80};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};	// xpub
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE3};	// xprv
        // guarantees the first 2 characters, when base58 encoded, are "zm"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xAA};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVK"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAB,0xD3};
        // guarantees the first 2 characters, when base58 encoded, are "MK"
        base58Prefixes[ZCSPENDING_KEY]     = {0x89,0x64};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (      0, consensus.hashGenesisBlock)
            (    293, uint256S("000094343dc23483c26239f71603980a5c56062c061b81a6b6f30a77e6717d41"))
            (    586, uint256S("000015256f276b0bb1d8e3b601ac37644e76cf860d8bc565aa1ff82fc0a6ef3f"))
            (    879, uint256S("000083828428d8d2f5245d9d4ada17df9418ae1c320268f477a853f800df3365"))
            (   1330, uint256S("0000c242f621ac3a22e6cd230b25fc27800082072724cab678f5e32c12f8d1f8"))
            (   2659, uint256S("00004c165c02803abd5cbb066a7b70328efa8e0345fa7658701af96c53458da8"))
            (   5317, uint256S("0000486d6d3e2587fe0c3f48fd74ed21676202bf1867648dbf4c1a52f3659d4e"))
            (  10633, uint256S("0000005f809e79671f57d4dbb0ad8777d1e4a2f07d72e146316271567e6987b0"))
            (  21266, uint256S("000000126cfdf6cb5279df2a53e79ab30ea0f7336c794120c3197b9373908dd6"))
            (  31901, uint256S("00000088282df4c26a47bea22cb313a29ffe9ac8f30aa7de0129ca2c3a770f9a")),
            1520105722,     // * UNIX timestamp of last checkpoint block
            68284,          // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            800             // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        strCurrencyUnits = "TLZ";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;

        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0x90;
        pchMessageStart[2] = 0x86;
        pchMessageStart[3] = 0x5d;
        vAlertPubKey = ParseHex("04aef689da1e268663f53c4157fac611af2a7211e0694873d66327aed938a77f483d9bacade8da7cff1d402820899970b764c5f3508e3dc52fdcecf82679911ae9");

        nDefaultPort = 39333;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        const size_t N = 200, K = 9;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        genesis = CreateGenesisBlock(
            1511954736,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000001610"),
            ParseHex("008abde46ca8e31bbcbdb0c02713b4f8d7d85ccee24a0b33aef216ab6b5948258f2b7ddc7a34851c336b158fc5a08b07c861079899506267b3ab7849fcc5ce529c2ebd05b05f97fcb19882775966dad45337290701ab2b2938e3ee7175ed0164111f1b8916ba92c78e100c945919899b09e6f5d4563765dfe926c9f47cc601fd1a4cb88b0f211b6ca3b0477d5845a61c14cd430cdf3c59359e378d70901277aeb57ca5f7ed1f2ce609ccdfc9bbe91961d69fd2b0489e194a1024dfed0e0e5eb1a591c83f499c0103925fe81e9db1dff9106d154e3b41c9e3ab113805a43ed0e296ea179cb99d91445854f6a8d185f59c54d9d5ed7b9cee8b061aa8f90b82c788e8a14cd1425a01acc6125948aa2ecf39e5104fd12c545cd9c5715a31570af29f9d67373fc70115a84ab06367d43bff89582f384c8f464e4b98992319f7fcb675cb83d75fe89a729577bd5336331ce16200bfc5f0bfc89cbd999ca16a859f6c3090b896a85e2095497fd6cbe0ea735184df8e43ef16be0bd93d891561fd0f26ad955dc4e3f3f96652d4115c62d4ff4f35084bbac0cfdbd7506896beedcda35aab70166ed10253d360b2c555c8c523d0c04e6673e92e8f33be3c2945ed1b67dc927d5331c6d236f8caea3f5f3cdd4203ca335eb19630373d9a50c528a9daf5b9abb9c7da14bcc4f72360b9abe2e803c64a5055ed52d81d6744064aee8c188637608ac341fbfcc42460a4e19ec4af0d634c121ed595e2ddbc32756b9fef809eaabfc90409869b3c8d8eb48cb114158f25d9d80a0d95bdc72638b22a2cfad7dc5f0d26546701392e5d89f3b838c60b92364395897d76ac47f8f366ff647ef9813cacdb1a85cd1ac4120bd90703c2ba76763e5cf3003900e41ac16b52f70f1810eafed38f53d32f76696fdf955f2194fa44a7cdc3b3a3cab6e9f2ef1d82049b14831d01f039d0dc808fb585688558516c18475b023d227d0d904feba285a31432b661605f72aca4939024b8c824e85c2d2bb09e5d8a409478a2255b253e0dbd582d398594598a97d747000a67e0cf5e13fa11139d0e4b032c7d6b97528375cb58e8bf4d4df486552938c0ba1030aa8e9f90f3eef21c84d103f12371ae18715bd406ae863e1f57bd1911122312f6d64292f6db3d9a354c69c5fa7adb8fd14be2c68eb1e7dcca756bf67f28050e5c487593854f9c66831349c1ee7595e4cef7a730a376d2b0ce600d8985e748fad07592d15f3efc750dd65c094ae1ce57d3c8d888a47ec7f644a5b4d3710edd1dd43d6f2fe7cd3442fd5234eaed6a356b6ca507802ee7cdb5ee33ffc9384c85dd1d2aa1a85a8c1316e863f531cb86bb620595828c3478c9cd3954c13215e4c28daa090d99de47d30521c743f5db175b89925339440594b7388dcbf796d507ca1e6dec5734bbe602de8a4c0105b44cb6d15691e270b4764903b2cd0322b0069d9c0c769b7d1e731bb2e6acede8777f388f08e9b08a3545b87e55513617b1b1ee4a00629faf8b116ab6c77d553da780e3d90199efc92f03829f940d05868359149514d54d19967c1ed3dc7a7324d7bac242d90b28f1d4b650b3eeb6b91cccd272b5b2da9761079f9285500ab63e6a1250f1baf7f83d05ac9fad4e4878cd9fe5591fffeb8e75a26c418399918edd453b0f59d9bf529c07d164daa7e458c03ab2ec1f5ab971193c3f0808a2af257895334941d0566d3d6177fd8e0f6d6bb81a91a36d32dc51df103517bb1b4c3a9c431caf4da254ebcb57b3d491d7b3a43ad66062dc27920f94e7de6e22ec77fc2ec2f65a3a284113c02d86bf1fdf5908bd5cc531f672f212a5b230cdb1bfbf5019112b7d135b9fee7963995a8e427ddb9acd21f8ed6661bf3c2c8d20f6eb205807617150aa51e34691c239"),
            0x1f07ffff, 4);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(genesis.hashMerkleRoot == uint256S("0x87800ace8ce2299bbf33ac3f76186ee66be9d7de9a9e22cdba040d3c4776870e"));
        assert(consensus.hashGenesisBlock == uint256S("0x000777e63f7c2efb3c554405a07a4f3dd1def8ea5cef4fda65b2c57247171141"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("1efb6b60d74ed972e0x7cb89cb3fcf7c933bbd38572af35e58ee19604609061d369e99134b9c811fedb2369fa90940b6a9533f2ae73aa11bb55346f5823fa2f653.CONBINI", "conbinicoin.com"));

        // guarantees the first 2 characters, when base58 encoded, are "T1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x0E,0xA4};
        // guarantees the first 2 characters, when base58 encoded, are "T3"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x0E,0xA9};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCE};	// tpub
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};	// tprv
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVt"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        // guarantees the first 2 characters, when base58 encoded, are "TK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xB1,0xF8};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock),
            1511954736,  // * UNIX timestamp of last checkpoint block
            1,           // * total number of transactions between genesis and last checkpoint
                         //   (the tx=... number in the SetBestChain debug.log lines)
            715          //   total number of tx / (checkpoint block height / (24 * 24))
        };
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "RLZ";
        consensus.fCoinbaseMustBeProtected = false;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // Turn off adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;

        pchMessageStart[0] = 0xea;
        pchMessageStart[1] = 0x8c;
        pchMessageStart[2] = 0x71;
        pchMessageStart[3] = 0x19;

        nDefaultPort = 49444;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        const size_t N = 48, K = 5;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        genesis = CreateGenesisBlock(
            1511954736,
            uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"),
            ParseHex(""),
            0x200f0f0f, 4);

        consensus.hashGenesisBlock = genesis.GetHash();

        assert(genesis.hashMerkleRoot == uint256S("0x87800ace8ce2299bbf33ac3f76186ee66be9d7de9a9e22cdba040d3c4776870e"));
        assert(consensus.hashGenesisBlock == uint256S("0x502ed0d1096705079d99872827b5448bdb357f99876bd497d78e6d01b1804272"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        // These prefixes are the same as the testnet prefixes
        base58Prefixes[PUBKEY_ADDRESS]     = {0x0E,0xA4};
        base58Prefixes[SCRIPT_ADDRESS]     = {0x0E,0xA9};
        base58Prefixes[SECRET_KEY]         = {0xEF};
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCE};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        base58Prefixes[ZCSPENDING_KEY]     = {0xB1,0xF8};

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock),
            1511954736,
            1,
            0
        };
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
