// jpleph.h
//
// Copyright (C) 2004, Chris Laurel <claurel@shatters.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// Load JPL's DE200, DE405, and DE406 ephemerides and compute planet
// positions.

#pragma once

#include <iosfwd>
#include <vector>

#include <Eigen/Core>

enum JPLEphemItem
{
    JPLEph_Mercury       =  0,
    JPLEph_Venus         =  1,
    JPLEph_EarthMoonBary =  2,
    JPLEph_Mars          =  3,
    JPLEph_Jupiter       =  4,
    JPLEph_Saturn        =  5,
    JPLEph_Uranus        =  6,
    JPLEph_Neptune       =  7,
    JPLEph_Pluto         =  8,
    JPLEph_Moon          =  9,
    JPLEph_Sun           = 10,
    JPLEph_Earth         = 11,
    JPLEph_SSB           = 12,
};


#define JPLEph_NItems 12

struct JPLEphCoeffInfo
{
    unsigned int offset;
    unsigned int nCoeffs;
    unsigned int nGranules;
};


struct JPLEphRecord
{
    JPLEphRecord() = default;
    ~JPLEphRecord();

    double t0{ 0.0 };
    double t1{ 0.0 };
    double* coeffs{ nullptr };
};


class JPLEphemeris
{
private:
    JPLEphemeris() = default;

public:
    ~JPLEphemeris() = default;

    Eigen::Vector3d getPlanetPosition(JPLEphemItem, double t) const;

    static JPLEphemeris* load(std::istream&);

    unsigned int getDENumber() const;
    double getStartDate() const;
    double getEndDate() const;
    bool getByteSwap() const;
    unsigned int getRecordSize() const;

private:
    JPLEphCoeffInfo coeffInfo[JPLEph_NItems];
    JPLEphCoeffInfo librationCoeffInfo;

    double startDate;
    double endDate;
    double daysPerInterval;

    double au;
    double earthMoonMassRatio;

    unsigned int DENum;       // ephemeris version
    unsigned int recordSize;  // number of doubles per record
    bool swapBytes;

    std::vector<JPLEphRecord> records;
};
