// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The N�wa Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	CMutableTransaction txNew;
	txNew.nVersion = 1;
	txNew.vin.resize(1);
	txNew.vout.resize(1);
	txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	txNew.vout[0].nValue = genesisReward;
	txNew.vout[0].scriptPubKey = genesisOutputScript;

	CBlock genesis;
	genesis.vtx.push_back(txNew);
	genesis.hashPrevBlock.SetNull();
	genesis.nVersion = nVersion;
	genesis.nTime = nTime;
	genesis.nBits = nBits;
	genesis.nNonce = nNonce;
	genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
	return genesis;
}

/**
* Build the genesis block. Note that the output of the genesis coinbase cannot
* be spent as it did not originally exist in the database.
*
* CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
*   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
*     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
*     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
*   vMerkleTree: e0028e
*/
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	const char* pszTimestamp = "Apple updates AirTags after stalking fears";
	const CScript genesisOutputScript = CScript() << ParseHex("04b1d5123f36ad8dc63791a1bdb8f0b91a6da8c18c593a95e6c2a16cb63ea746a7960b8025b904767bc671d5dfe706c2bd2e13b86122e1064a0ecb7bf863254313") << OP_CHECKSIG;
	return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
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
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256S("0x00000c53a8106ca9bf574abb32c55389734ac3aff26cf648204548e4e29d7ff9"))
(1, uint256("0x00000cf80c05d2b45b6b494558cacfed9aba2e9a1c74c9fc408491bbe20eb3f6"))
(604, uint256("0x00000002b885cc244f9c074ca1a261adc1c4173eb821ea70de1c3a59f5970f7e"))
(1954, uint256("0xe8997eaafeb3b454c29d6b7f9ef3adaec5be0c40c87d459150b776d018fc8892"))
(3245, uint256("0x204fd08db407bb405c17d0bb8819b69bc08d0567602775882ffeddb1d72434e1"))
(4784, uint256("0x33d51c47509b62c88f60de64824405f399a45799fe168c6b6119ea5e734ba45a"))
(5338, uint256("0x4f38c7a949d92058513df12f45ceb0eeae6a5ebffbd7ce1ca4f2c45554789c55"))
(6407, uint256("0x1c26bfd2316337c1eb5901b03f4a69be61537cdf6476e5c193698dcb87065b2c"))
(8118, uint256("0xaecc4332792a40aad1cde9edd67642ae14d8da05213c2c0b0e9a275171bdfcab"))
(9673, uint256("0x717f1e0277aa98f1c4bdd3c53dd1843e23eb250a955b81f64c1caec5c0401605"))
(10768, uint256("0x942cdf9c5ce521045d1b24a0c1aaf00544491ba429e7a66d9fc2de341e09d0f0"))
(13571, uint256("0xc6b02f6ebcb841ecec9462077647ea6c54ec3d41795a211b46294cfa7c727f0f"))

;

static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
	1624861935, // * UNIX timestamp of last checkpoint block
	26663,	    // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the UpdateTip debug.log lines)
	720         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1591225230,
	3501914,
	3000 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1454124731,
	0,
	100 };

class CMainParams : public CChainParams
{
public:
	CMainParams()
	{
		networkID = CBaseChainParams::MAIN;
		strNetworkID = "main";

		genesis = CreateGenesisBlock(1623142800, 110995, 0x1e0ffff0, 1, 0);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(consensus.hashGenesisBlock == uint256S("00000c53a8106ca9bf574abb32c55389734ac3aff26cf648204548e4e29d7ff9"));
		assert(genesis.hashMerkleRoot == uint256S("ba586ef5d21d7ef3d16db4156e96ae72fff393edec63d313855623f413ba139d")); 

		consensus.fPowAllowMinDifficultyBlocks = false;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // NuwaCoin starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 9999999;       // approx. 1 every 30 days
		consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
		consensus.nCoinbaseMaturity = 60;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 100000000000 * COIN;
		consensus.nPoolMaxTransactions = 3;
		consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
		consensus.nStakeMinAge = 60 * 60;
		consensus.nStakeMinDepth = 60;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 2 * 60;
		consensus.nTimeSlotLength = 15;


		// spork keys
		consensus.strSporkPubKey = "04cba7cacb3f265f185724f1dc1250021f0fdda325412867326516ca1f8f459105abbf708762d0cb6c0971341f54f5fb0ab412b5b22d226cae682b5b3ead9235a0";
		consensus.strSporkPubKeyOld = "04cba7cacb3f265f185724f1dc1250021f0fdda325412867326516ca1f8f459105abbf708762d0cb6c0971341f54f5fb0ab412b5b22d226cae682b5b3ead9235a0";
		consensus.nTime_EnforceNewSporkKey = 1623150000;    //!> Tuesday, 8 June 2021 11:00:00 AM GMT
		consensus.nTime_RejectOldSporkKey = 1623236400;     //!> Wednesday, 9 June 2021 11:00:00 AM GMT

		// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 1001;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 1;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 1300;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 1001;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 1100;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

		consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
			uint256S("0x");
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
			uint256S("0x");
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
			uint256S("0x");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/
		pchMessageStart[0] = 0xbd;
		pchMessageStart[1] = 0x3e;
		pchMessageStart[2] = 0xd7;
		pchMessageStart[3] = 0xea;
		nDefaultPort = 7621;

		// Note that of those with the service bits flag, most only support a subset of possible options
		vSeeds.push_back(CDNSSeedData("137.74.249.96", "137.74.249.96", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.97", "137.74.249.97", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.98", "137.74.249.98", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.99", "137.74.249.99", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.100", "137.74.249.100", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.101", "137.74.249.101", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.102", "137.74.249.102", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.103", "137.74.249.103", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.104", "137.74.249.104", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.105", "137.74.249.105", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.106", "137.74.249.106", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.107", "137.74.249.107", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.108", "137.74.249.108", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.109", "137.74.249.109", true));
		vSeeds.push_back(CDNSSeedData("137.74.249.110", "137.74.249.110", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::96", "2001:41d0:303:bea::96", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::97", "2001:41d0:303:bea::97", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::98", "2001:41d0:303:bea::98", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::99", "2001:41d0:303:bea::99", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::00", "2001:41d0:303:bea::00", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::01", "2001:41d0:303:bea::01", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::02", "2001:41d0:303:bea::02", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::03", "2001:41d0:303:bea::03", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::04", "2001:41d0:303:bea::04", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::05", "2001:41d0:303:bea::05", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::06", "2001:41d0:303:bea::06", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::07", "2001:41d0:303:bea::07", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::08", "2001:41d0:303:bea::08", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::09", "2001:41d0:303:bea::09", true));
		vSeeds.push_back(CDNSSeedData("2001:41d0:303:bea::10", "2001:41d0:303:bea::10", true));
		
		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 53);		// N
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
		base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 23);	// A
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
		// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xde).convert_to_container<std::vector<unsigned char> >();

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

		// Sapling
		bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ps";
		bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviews";
		bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
		bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-main";
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return data;
	}

};
static CMainParams mainParams;

/**
* Testnet (v3)
*/
class CTestNetParams : public CMainParams
{
public:
	CTestNetParams()
	{
		networkID = CBaseChainParams::TESTNET;
		strNetworkID = "test";

		genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		//assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // NuwaCoin starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
		consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
		consensus.nCoinbaseMaturity = 15;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 43199500 * COIN;
		consensus.nPoolMaxTransactions = 2;
		consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
		consensus.nStakeMinAge = 60 * 60;
		consensus.nStakeMinDepth = 100;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 1 * 60;
		consensus.nTimeSlotLength = 15;

		// spork keys
		consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
		consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
		consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
		consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

															// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 201;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 51197;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight = 851019;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 1214000;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight = 1347000;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

		consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
			uint256S("0xc54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30");
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
			uint256S("0x1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199");
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
			uint256S("0x30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882");

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/

		pchMessageStart[0] = 0x45;
		pchMessageStart[1] = 0x76;
		pchMessageStart[2] = 0x65;
		pchMessageStart[3] = 0xba;
		nDefaultPort = 51474;

		vFixedSeeds.clear();
		vSeeds.clear();
		// nodes with support for servicebits filtering should be at the top
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "nuwacoin-testnet.seed.fuzzbawls.pw", true));
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "nuwacoin-testnet.seed2.fuzzbawls.pw", true));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet nuwacoin addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet nuwacoin script addresses start with '8' or '9'
		base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
																			 // Testnet nuwacoin BIP32 pubkeys start with 'DRKV'
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
		// Testnet nuwacoin BIP32 prvkeys start with 'DRKP'
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
		// Testnet nuwacoin BIP44 coin type is '1' (All coin's testnet default)
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

		// Sapling
		bech32HRPs[SAPLING_PAYMENT_ADDRESS] = "ptestsapling";
		bech32HRPs[SAPLING_FULL_VIEWING_KEY] = "pviewtestsapling";
		bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "bcktestsapling";
		bech32HRPs[SAPLING_EXTENDED_SPEND_KEY] = "p-secret-spending-key-test";
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataTestnet;
	}
};
static CTestNetParams testNetParams;

/**
* Regression test
*/
class CRegTestParams : public CTestNetParams
{
public:
	CRegTestParams()
	{
		networkID = CBaseChainParams::REGTEST;
		strNetworkID = "regtest";

		genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		//assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.powLimit = ~UINT256_ZERO >> 20;   // NuwaCoin starting difficulty is 1 / 2^12
		consensus.posLimitV1 = ~UINT256_ZERO >> 24;
		consensus.posLimitV2 = ~UINT256_ZERO >> 20;
		consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
		consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
		consensus.nCoinbaseMaturity = 100;
		consensus.nFutureTimeDriftPoW = 7200;
		consensus.nFutureTimeDriftPoS = 180;
		consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
		consensus.nMaxMoneyOut = 43199500 * COIN;
		consensus.nPoolMaxTransactions = 2;
		consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
		consensus.nStakeMinAge = 0;
		consensus.nStakeMinDepth = 2;
		consensus.nTargetTimespan = 40 * 60;
		consensus.nTargetTimespanV2 = 30 * 60;
		consensus.nTargetSpacing = 1 * 60;
		consensus.nTimeSlotLength = 15;

		/* Spork Key for RegTest:
		WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
		private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
		Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
		*/
		consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
		consensus.strSporkPubKeyOld = "";
		consensus.nTime_EnforceNewSporkKey = 0;
		consensus.nTime_RejectOldSporkKey = 0;

		// Network upgrades
		consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
			Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
		consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight = 251;
		consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight =
			Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
		consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight = 300;

		/**
		* The message start string is designed to be unlikely to occur in normal data.
		* The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		* a large 4-byte int at any alignment.
		*/

		pchMessageStart[0] = 0xa1;
		pchMessageStart[1] = 0xcf;
		pchMessageStart[2] = 0x7e;
		pchMessageStart[3] = 0xac;
		nDefaultPort = 51476;

		vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataRegtest;
	}

	void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
	{
		assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
		consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
	}
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
	assert(pCurrentParams);
	return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
	switch (network) {
	case CBaseChainParams::MAIN:
		return mainParams;
	case CBaseChainParams::TESTNET:
		return testNetParams;
	case CBaseChainParams::REGTEST:
		return regTestParams;
	default:
		assert(false && "Unimplemented network");
		return mainParams;
	}
}

void SelectParams(CBaseChainParams::Network network)
{
	SelectBaseParams(network);
	pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
	CBaseChainParams::Network network = NetworkIdFromCommandLine();
	if (network == CBaseChainParams::MAX_NETWORK_TYPES)
		return false;

	SelectParams(network);
	return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
	regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
