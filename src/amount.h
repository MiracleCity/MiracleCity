// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2014 The BlackCoin developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020 The Miracle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MIRACLE_AMOUNT_H
#define MIRACLE_AMOUNT_H

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <limits>

/** Amount in corbies (Can be negative) */
typedef int64_t CAmount;

static const CAmount COIN = 10000;
static const CAmount CENT = 100;

/** No amount larger than this (in satoshi) is valid.*/
static const CAmount MAX_MONEY = std::numeric_limits<int64_t>::max();
static const CAmount MAX_MONEY_TOKENS = 100000000000 * COIN;

inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

#endif //  MIRACLE_AMOUNT_H
