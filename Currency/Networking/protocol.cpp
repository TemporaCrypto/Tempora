// Copyright (c) 2009-2017 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Developers
// Copyright (c) 2014-2017 The Dash Core Developers
// Copyright (c) 2015-2017 Silk Network Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "protocol.h"

#include "util.h"
#include "utilstrencodings.h"

#ifndef WIN32
# include <arpa/inet.h>
#endif

namespace NetMsgType {
const char *VERSION="version";
const char *VERACK="verack";
const char *ADDR="addr";
const char *INV="inv";
const char *GETDATA="getdata";
const char *MERKLEBLOCK="merkleblock";
const char *GETBLOCKS="getblocks";
const char *GETHEADERS="getheaders";
const char *TX="tx";
const char *HEADERS="headers";
const char *BLOCK="block";
const char *GETADDR="getaddr";
const char *MEMPOOL="mempool";
const char *PING="ping";
const char *PONG="pong";
const char *ALERT="alert";
const char *NOTFOUND="notfound";
const char *FILTERLOAD="filterload";
const char *FILTERADD="filteradd";
const char *FILTERCLEAR="filterclear";
const char *REJECT="reject";
const char *SENDHEADERS="sendheaders";
// DarkSilk message types
const char *TXLOCKREQUEST="ix";
const char *TXLOCKVOTE="txlvote";
const char *SPORK="spork";
const char *GETSPORKS="getsporks";
const char *STORMNODEPAYMENTVOTE="snw";
const char *STORMNODEPAYMENTBLOCK="snwb";
const char *STORMNODEPAYMENTSYNC="snget";
const char *SNBUDGETSYNC="snvs"; // depreciated since 12.1
const char *SNBUDGETVOTE="svote"; // depreciated since 12.1
const char *SNBUDGETPROPOSAL="sprop"; // depreciated since 12.1
const char *SNBUDGETFINAL="fbs"; // depreciated since 12.1
const char *SNBUDGETFINALVOTE="fbvote"; // depreciated since 12.1
const char *SNQUORUM="sn quorum"; // not implemented
const char *SNANNOUNCE="snb";
const char *SNPING="snp";
const char *SSACCEPT="ssa";
const char *SSVIN="ssi";
const char *SSFINALTX="ssf";
const char *SSSIGNFINALTX="sss";
const char *SSCOMPLETE="ssc";
const char *SSSTATUSUPDATE="sssu";
const char *SSTX="sstx";
const char *SSQUEUE="ssq";
const char *SSEG="sseg";
const char *SYNCSTATUSCOUNT="ssc";
const char *SNGOVERNANCESYNC="govsync";
const char *SNGOVERNANCEOBJECT="govobj";
const char *SNGOVERNANCEOBJECTVOTE="govobjvote";
const char *SNVERIFY="snv";
};

static const char* ppszTypeName[] =
{
    "ERROR", // Should never occur
    NetMsgType::TX,
    NetMsgType::BLOCK,
    "filtered block", // Should never occur
    // DarkSilk message types
    // NOTE: include non-implmented here, we must keep this list in sync with enum in protocol.h
    NetMsgType::TXLOCKREQUEST,
    NetMsgType::TXLOCKVOTE,
    NetMsgType::SPORK,
    NetMsgType::STORMNODEPAYMENTVOTE,
    NetMsgType::STORMNODEPAYMENTBLOCK, // reusing, was SNSCANERROR previousely, was NOT used in 12.0, we need this for inv
    NetMsgType::SNBUDGETVOTE, // depreciated since 12.1
    NetMsgType::SNBUDGETPROPOSAL, // depreciated since 12.1
    NetMsgType::SNBUDGETFINAL, // depreciated since 12.1
    NetMsgType::SNBUDGETFINALVOTE, // depreciated since 12.1
    NetMsgType::SNQUORUM, // not implemented
    NetMsgType::SNANNOUNCE,
    NetMsgType::SNPING,
    NetMsgType::SSTX,
    NetMsgType::SNGOVERNANCEOBJECT,
    NetMsgType::SNGOVERNANCEOBJECTVOTE,
    NetMsgType::SNVERIFY,
};

/** All known message types. Keep this in the same order as the list of
 * messages above and in protocol.h.
 */
const static std::string allNetMessageTypes[] = {
    NetMsgType::VERSION,
    NetMsgType::VERACK,
    NetMsgType::ADDR,
    NetMsgType::INV,
    NetMsgType::GETDATA,
    NetMsgType::MERKLEBLOCK,
    NetMsgType::GETBLOCKS,
    NetMsgType::GETHEADERS,
    NetMsgType::TX,
    NetMsgType::HEADERS,
    NetMsgType::BLOCK,
    NetMsgType::GETADDR,
    NetMsgType::MEMPOOL,
    NetMsgType::PING,
    NetMsgType::PONG,
    NetMsgType::ALERT,
    NetMsgType::NOTFOUND,
    NetMsgType::FILTERLOAD,
    NetMsgType::FILTERADD,
    NetMsgType::FILTERCLEAR,
    NetMsgType::REJECT,
    NetMsgType::SENDHEADERS,
    // DarkSilk message types
    // NOTE: do NOT include non-implmented here, we want them to be "Unknown command" in ProcessMessage()
    NetMsgType::TXLOCKREQUEST,
    NetMsgType::TXLOCKVOTE,
    NetMsgType::SPORK,
    NetMsgType::GETSPORKS,
    NetMsgType::STORMNODEPAYMENTVOTE,
    // NetMsgType::STORMNODEPAYMENTBLOCK, // there is no message for this, only inventory
    NetMsgType::STORMNODEPAYMENTSYNC,
    NetMsgType::SNANNOUNCE,
    NetMsgType::SNPING,
    NetMsgType::SSACCEPT,
    NetMsgType::SSVIN,
    NetMsgType::SSFINALTX,
    NetMsgType::SSSIGNFINALTX,
    NetMsgType::SSCOMPLETE,
    NetMsgType::SSSTATUSUPDATE,
    NetMsgType::SSTX,
    NetMsgType::SSQUEUE,
    NetMsgType::SSEG,
    NetMsgType::SYNCSTATUSCOUNT,
    NetMsgType::SNGOVERNANCESYNC,
    NetMsgType::SNGOVERNANCEOBJECT,
    NetMsgType::SNGOVERNANCEOBJECTVOTE,
    NetMsgType::SNVERIFY,
};
const static std::vector<std::string> allNetMessageTypesVec(allNetMessageTypes, allNetMessageTypes+ARRAYLEN(allNetMessageTypes));

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    nMessageSize = -1;
    nChecksum = 0;
}

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn, const char* pszCommand, unsigned int nMessageSizeIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    strncpy(pchCommand, pszCommand, COMMAND_SIZE);
    nMessageSize = nMessageSizeIn;
    nChecksum = 0;
}

std::string CMessageHeader::GetCommand() const
{
    return std::string(pchCommand, pchCommand + strnlen(pchCommand, COMMAND_SIZE));
}

bool CMessageHeader::IsValid(const MessageStartChars& pchMessageStartIn) const
{
    // Check start string
    if (memcmp(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE) != 0)
        return false;

    // Check the command string for errors
    for (const char* p1 = pchCommand; p1 < pchCommand + COMMAND_SIZE; p1++)
    {
        if (*p1 == 0)
        {
            // Must be all zeros after the first zero
            for (; p1 < pchCommand + COMMAND_SIZE; p1++)
                if (*p1 != 0)
                    return false;
        }
        else if (*p1 < ' ' || *p1 > 0x7E)
            return false;
    }

    // Message size
    if (nMessageSize > MAX_SIZE)
    {
        LogPrintf("CMessageHeader::IsValid(): (%s, %u bytes) nMessageSize > MAX_SIZE\n", GetCommand(), nMessageSize);
        return false;
    }

    return true;
}



CAddress::CAddress() : CService()
{
    Init();
}

CAddress::CAddress(CService ipIn, uint64_t nServicesIn) : CService(ipIn)
{
    Init();
    nServices = nServicesIn;
}

void CAddress::Init()
{
    nServices = NODE_NETWORK;
    nTime = 100000000;
}

CInv::CInv()
{
    type = 0;
    hash.SetNull();
}

CInv::CInv(int typeIn, const uint256& hashIn)
{
    type = typeIn;
    hash = hashIn;
}

CInv::CInv(const std::string& strType, const uint256& hashIn)
{
    unsigned int i;
    for (i = 1; i < ARRAYLEN(ppszTypeName); i++)
    {
        if (strType == ppszTypeName[i])
        {
            type = i;
            break;
        }
    }
    if (i == ARRAYLEN(ppszTypeName))
        throw std::out_of_range(strprintf("CInv::CInv(string, uint256): unknown type '%s'", strType));
    hash = hashIn;
}

bool operator<(const CInv& a, const CInv& b)
{
    return (a.type < b.type || (a.type == b.type && a.hash < b.hash));
}

bool CInv::IsKnownType() const
{
    return (type >= 1 && type < (int)ARRAYLEN(ppszTypeName));
}

const char* CInv::GetCommand() const
{
    if (!IsKnownType())
        throw std::out_of_range(strprintf("CInv::GetCommand(): type=%d unknown type", type));
    return ppszTypeName[type];
}

std::string CInv::ToString() const
{
    return strprintf("%s %s", GetCommand(), hash.ToString());
}

const std::vector<std::string> &getAllNetMessageTypes()
{
    return allNetMessageTypesVec;
}