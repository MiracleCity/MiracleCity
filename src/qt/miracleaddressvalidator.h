// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020 The Miracle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MIRACLE_QT_MIRACLEADDRESSVALIDATOR_H
#define MIRACLE_QT_MIRACLEADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class MiracleAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MiracleAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Miracle address widget validator, checks for a valid miracle address.
 */
class MiracleAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MiracleAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // MIRACLE_QT_MIRACLEADDRESSVALIDATOR_H
