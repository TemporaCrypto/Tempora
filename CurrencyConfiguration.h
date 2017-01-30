/**
 * EmpineX is a currency designed for novices in CryptoCurrency to make their own currency
 * The codebase is based of the DarkSilk (A DashPay based currency)
 * 
 * The features like the Dynamic Domain Name System has been REMOVED!
 * 
 * WARNING: THE EMPINEX DEVELOPERS ARE NOT LIABLE IF YOU LAUNCH THIS AS AN ACTUAL ALTCOIN
 * 			UNLESS YOU KNOW WHAT YOU ARE DOING, PLEASE DON'T TRY AND PAINSTAKE THE ALTCOIN COMMUNITY
 * 			BY GIFTING US, THE COMMUNITY - SPAMCOINS OF ABSOLUTE PROPORTIONS
 *  
 **/ 

const std::string passwordToTheWorld = ["goldilocks_the_chicken"]; /** Please enter the password as your unique identifer */
const uint256	  passwordToTheHash	 = ["0x"] /**   X11 Hash of the passwordToTheWorld String, needed to launch clients   */

namespace CurrencyParameters {
	
	/**
	 * EMPINEX_GENESIS_POW_GENERATION_Y 
	 * When set to true will generate a new genesis, it is required if you want a new genesis,
	 * it must be set to false after the currency parameters have been created
	 * 
	 * EMPINEX_GENESIS_POW_NONCE_PROOF_NO
	 * The Proof Of Work System employed here requires a 'nonce' - the amount of attempts it takes
	 * for you to reach the appropriate hash, it will be generated
	 * 
	 * EMPINEX_GENESIS_POW_BLOCK_TIMSTAMP
	 * The Block will be containing a "Timestamp" which will be in UNIX Time, it will be generated by
	 * the genesis generator
	 * 
	 * EMPINEX_GENESIS_POW_PROOF_HASH
	 * This will be the proof of work hash, it will be generated if EMPINEX_GENESIS_POW_GENERATION_Y is
	 * set to true on client initialisation
	 * 
	 * EMPINEX_GENESIS_POW_MERKLE_HASH
	 * This will be the transaction hash that will accompany with EMPINEX_GENESIS_POW_PROOF_HASH, it is 
	 * generated if EMPINEX_GENESIS_POW_GENERATION_Y set true on client initialisation
	 * 
	 **/ 

	const bool	  EMPINEX_GENESIS_POW_GENERATION_Y	 = true;
	const int	  EMPINEX_GENESIS_POW_NONCE_PROOF_NO = 0;
	const int	  EMPINEX_GENESIS_POW_BLOCK_TIMSTAMP = 0;
	const uint256 EMPINEX_GENESIS_POW_PROOF_HASH	 = uint256S("0x");
	const uint256 EMPINEX_GENESIS_POW_MERKLE_HASH	 = uint256S("0x");
	
	/**
	 * currencyName
	 * It will be the name of your currency in the Command Line interface and in the GUI
	 * 
	 * currencyTicker
	 * It will be the ticker (abbriviation) of your currency in the Command Line interface and in the GUI
	 * 
	 * EMPINEX_ALERT_PUBLIC_KEY
	 * It will be the public key of the pubkey:privkey pair that will allow you to send alerts to the client
	 * 
	 **/ 
	const std::string currencyName 		= ["SampleCurrency"];
	const std::string currencyTicker 	= ["SCR"];
	
	const char 		EMPINEX_ALERT_PUBLIC_KEY	 	= [""];
	const int64_t 	EMPINEX_NETWORK_MAXIMUM_DRIFT 	= 0;

	/**
	 * EMPINEX_BLOCKS_MIN_TARGET
	 * The minimum hash target of a Proof Of Work Block [recommended not to touch at all]
	 * 
	 * EMPINEX_BLOCKS_MAX_NUMBER
	 * The maximum number of blocks the network will have in the absolute
	 * 
	 * EMPINEX_BLOCKS_TARGET_SECONDS
	 * The median target block timing of each block that will be minted by 
	 * the Proof Of Work Phase
	 * 
	 * EMPINEX_BLOCKS_RETARGET_SECONDS
	 * The median amount of time it should take to recalculate the difficulty for 
	 * the Proof Of Work Phase
	 * 
	 * EMPINEX_BLOCKS_MAX_TIP_AGE
	 * The maximum age of the last block in the change after which it will respond 
	 * with a synchronization message
	 * 
	 * EMPINEX_BLOCKS_BLOCKVERSION
	 * The block version of a proof of work block
	 * 
	 **/
	  
	const uint256 EMPINEX_BLOCKS_MIN_TARGET			= uint256S("0x");
	const int64_t EMPINEX_BLOCKS_MAX_NUMBER 		= 0;
	const int 	  EMPINEX_BLOCKS_TARGET_SECONDS 	= 0;
	const int 	  EMPINEX_BLOCKS_RETARGET_SECONDS 	= 0;
	const int	  EMPINEX_BLOCKS_MAX_TIP_AGE		= 0;
	const int 	  EMPINEX_BLOCKS_BLOCKVERSION		= 0;
	
	/**
	 * EMPINEX_TX_COINBASE_CONFIRMS
	 * The minimum confirmations required for a coinbase transaction to be 
	 * confirmed
	 * 
	 * EMPINEX_TX_STANDARD_UI_CONFIRMS
	 * The surface minimum confirmations required for a standard transaction 
	 * to be confirmed (applicable for GUI only)
	 * 
	 * EMPINEX_TX_MINIMUM_FEE
	 * The median minimum fee for a transaction, the below of which will be considered
	 * to be considered nonexistant
	 * 
	 **/
	 
	const int 	  EMPINEX_TX_COINBASE_CONFIRMS		= 0;
	const int 	  EMPINEX_TX_STANDARD_UI_CONFIRMS	= 0;
	const int64_t EMPINEX_TX_MINIMUM_FEE		    = 0 * COIN;
	
	
	/**
	 * EMPINEX_P2P_MESSAGE_CODES
	 * It is a unique message code within each BitCoin Cryptocurrency used to uniquely
	 * identify each currency
	 * 
	 * EMPINEX_P2P_ACCESS_PORT
	 * The port the client will use to connect with out clients
	 * 
	 * EMPINEX_RPC_ACCESS_PORT
	 * The port the client will use to connect to the RPC client
	 * 
	 * EMPINEX_P2P_SEED_NODES
	 * The seeds the client will connect to automatically when it connects
	 **/
	 
	unsigned char 	 EMPINEX_P2P_MESSAGE_CODES[4] 			= { 0xf9, 0xbe, 0xb4, 0xd9 };
	const int 		 EMPINEX_P2P_ACCESS_PORT				= 0;
	const int 		 EMPINEX_RPC_ACCESS_PORT				= 0;
	
	static SeedSpec6 EMPINEX_P2P_SEED_NODES[] = {
		{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xa3,0xac,0xd5,0x3e}, EMPINEX_P2P_ACCESS_PORT},
		{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x33,0x0f,0x03,0x80}, EMPINEX_P2P_ACCESS_PORT},
		{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x80,0xc7,0xa5,0x4f}, EMPINEX_P2P_ACCESS_PORT},
		{{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xa2,0xf3,0x26,0x85}, EMPINEX_P2P_ACCESS_PORT}
	};
	
	/**
	 * EMPINEX_P2P_MESSAGE_CODES
	 * It is a unique message code within each BitCoin Cryptocurrency used to uniquely
	 * identify each currency
	 * 
	 * EMPINEX_P2P_ACCESS_PORT
	 * The port the client will use to connect with out clients
	 * 
	 * EMPINEX_RPC_ACCESS_PORT
	 * The port the client will use to connect to the RPC client
	 * 
	 * EMPINEX_P2P_SEED_NODES
	 * The seeds the client will connect to automatically when it connects
	 **/

	const int 		EMPINEX_POW_ALGORITHM_IDENTIFICATION_NO = 0;
	const int64_t 	EMPINEX_POW_REWARD_EMISSION_FACTOR		= 0;
	const int64_t 	EMPINEX_POW_REWARD_MAX_CELING			= 0 * COIN;
	const int64_t 	EMPINEX_POW_REWARD_MIN_CELING			= 0 * COIN;
	const int64_t 	EMPINEX_POW_REWARD_MAXIMUM_COINS_SUPPLY = 0 * COIN;
	
	const std::string 	EMPINEX_SUPERNODES_SPORK_PUBLIC_KEY			= ["Whatever!"];
	const std::string 	EMPINEX_SUPERNODES_SPORK_PUBLIC_KEY			= ["Whatever!"];
	const int64_t		EMPINEX_SUPERNODES_PRIVATESEND_COLLATERAL	= 0 * COIN;
	const int64_t		EMPINEX_SUPERNODES_INSTANTSEND_MAX			= 0 * COIN;
	const int64_t		EMPINEX_SUPERNODES_STATIC_SUPERBLOCK_AMOUNT = 0 * COIN;
	const int64_t 		EMPINEX_SUPERNODES_REWARD_FROM_POW_PERCENT 	= 0; // %
	
	
	checkpointData = (CCheckpointData) {
		boost::assign::map_list_of
		(  0, uint256S("0x0000a65ae4ea0c71cb974c5c49df0bde20aa68e79177d372a32e234470199c20")),
		1482255823, // * UNIX timestamp of last checkpoint block
		0,          // * total number of transactions between genesis and last checkpoint
					//   (the tx=... number in the SetBestChain debug.log lines)
		2000        // * estimated number of transactions per day after checkpoint
	};
}

