// Copyright (c) 2011-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020 The Miracle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "miracleunits.h"

#include "primitives/transaction.h"

#include <QStringList>

MiracleUnits::MiracleUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<MiracleUnits::Unit> MiracleUnits::availableUnits()
{
    QList<MiracleUnits::Unit> unitlist;
    unitlist.append(MCAM);
    return unitlist;
}

bool MiracleUnits::valid(int unit)
{
    switch(unit)
    {
    case MCAM:
        return true;
    default:
        return false;
    }
}

QString MiracleUnits::name(int unit)
{
    switch(unit)
    {
    case MCAM: return QString("MCAM ");
    default: return QString("???");
    }
}

QString MiracleUnits::description(int unit)
{
    switch(unit)
    {
    case MCAM: return QString("Miracles");
    default: return QString("???");
    }
}

qint64 MiracleUnits::factor(int unit)
{
    switch(unit)
    {
    case MCAM:  return 10000;
    default:   return 10000;
    }
}

qint64 MiracleUnits::factorToken(int unit)
{
    switch(unit)
    {
        case 0:  return 1;
        case 1: return 10;
        case 2: return 100;
        case 3: return 1000;
        case 4: return 10000;
        case 5: return 100000;
        case 6: return 1000000;
        case 7: return 10000000;
        case 8: return 100000000;
        default:   return 100000000;
    }
}

int MiracleUnits::decimals(int unit)
{
    switch(unit)
    {
    case MCAM: return 4;
    default: return 0;
    }
}

QString MiracleUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators, const int nTokenUnit)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if((nTokenUnit < 0 || nTokenUnit > 4) && !valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 n = (qint64)nIn;
    qint64 coin = nTokenUnit >= 0 ? factorToken(nTokenUnit) : factor(unit);
    int num_decimals = nTokenUnit >= 0 ? nTokenUnit : decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Use SI-style thi
    // n space separators as these are locale independent and can't be
    // confused with the decimal marker.
    QChar thin_sp(THIN_SP_CP);
    int q_size = quotient_str.size();
    if (separators == separatorAlways || (separators == separatorStandard && q_size > 4))
        for (int i = 3; i < q_size; i += 3)
            quotient_str.insert(q_size - i, thin_sp);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');

    if (nTokenUnit == MIN_TOKEN_UNITS)
        return quotient_str;


    return quotient_str + QString(".") + remainder_str;
}


// NOTE: Using formatWithUnit in an HTML context risks wrapping
// quantities at the thousands separator. More subtly, it also results
// in a standard space rather than a thin space, due to a bug in Qt's
// XML whitespace canonicalisation
//
// Please take care to use formatHtmlWithUnit instead, when
// appropriate.

QString MiracleUnits::formatWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QString(" ") + name(unit);
}

QString MiracleUnits::formatWithCustomName(QString customName, const CAmount& amount, int unit, bool plussign, SeparatorStyle separators)
{
    return format(MCAM, amount / factorToken(MAX_TOKEN_UNITS - unit), plussign, separators, unit) + QString(" ") + customName;
}

QString MiracleUnits::formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(formatWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}


bool MiracleUnits::parse(int unit, const QString &value, CAmount *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

bool MiracleUnits::tokenParse(int tokenUnit, const QString &value, CAmount *val_out)
{
    if(!(tokenUnit >= 0 && tokenUnit <= 4) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = tokenUnit;

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

QString MiracleUnits::getAmountColumnTitle(int unit)
{
    QString amountTitle = QObject::tr("Amount");
    if (MiracleUnits::valid(unit))
    {
        amountTitle += " ("+MiracleUnits::name(unit) + ")";
    }
    return amountTitle;
}

int MiracleUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant MiracleUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}

CAmount MiracleUnits::maxMoney()
{
    return MAX_MONEY;
}
