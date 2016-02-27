/*
    cbp2make : Makefile generation tool for the Code::Blocks IDE
    Copyright (C) 2010-2016 Mirai Computing (mirai.computing@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//------------------------------------------------------------------------------
#include <cmath>
//------------------------------------------------------------------------------
#include "stltime.h"
#include "stlconvert.h"
//------------------------------------------------------------------------------

void TimeToHMS(const double Time, int& Hours, int& Minutes, int& Seconds)
{
 Hours = (int)floor(Time / 3600);
 Minutes = (int)floor((Time - Hours * 3600) / 60);
 Seconds = (int)floor(Time - Hours * 3600 - Minutes * 60);
}

void TimeToHMSmS(const double Time, int& Hours, int& Minutes, int& Seconds, int& Miliseconds)
{
 Hours = (int)floor(Time / 3600);
 Minutes = (int)floor((Time - Hours * 3600) / 60);
 Seconds = (int)floor(Time - Hours * 3600 - Minutes * 60);
 Miliseconds = (int)floor(1000.0*(Time - Hours * 3600.0 - Minutes * 60.0 - Seconds * 1.0));
}

void TimeToHMSmSuS(const double Time, int& Hours, int& Minutes, int& Seconds, int& Miliseconds, int& Microseconds)
{
 Hours = (int)floor(Time / 3600);
 Minutes = (int)floor((Time - Hours * 3600) / 60);
 Seconds = (int)floor(Time - Hours * 3600 - Minutes * 60);
 Miliseconds = (int)floor(1000.0*(Time - Hours * 3600.0 - Minutes * 60.0 - Seconds * 1.0));
 Microseconds = (int)floor(1000.0*(Time - Hours * 3600.0 - Minutes * 60.0 - Seconds * 1.0 - Microseconds * 0.001));
}

CString TimeToStrHMS(const double Time)
{
 int hours, minutes, seconds;
 TimeToHMS(Time,hours,minutes,seconds);
 CString result = IntegerToString(hours)+"h:"
                 +IntegerToString(minutes)+"m:"
                 +IntegerToString(seconds)+"s";
 return result;
}

CString TimeToStrHMSmS(const double Time)
{
 int hours, minutes, seconds, msec;
 TimeToHMSmS(Time,hours,minutes,seconds,msec);
 CString result = IntegerToString(hours)+"h:"
                 +IntegerToString(minutes)+"m:"
                 +IntegerToString(seconds)+"s:"
                 +IntegerToString(msec)+"ms";
 return result;
}

CString TimeToStrHMSmSuS(const double Time)
{
 int hours, minutes, seconds, msec, usec;
 TimeToHMSmSuS(Time,hours,minutes,seconds,msec,usec);
 CString result = IntegerToString(hours)+"h:"
                 +IntegerToString(minutes)+"m:"
                 +IntegerToString(seconds)+"s:"
                 +IntegerToString(msec)+"ms:"
                 +IntegerToString(usec)+"us";
 return result;
}

CString TimeToStrF(const time_t Time, const CString& Format)
{
 struct tm *local_time;
 local_time = localtime(&Time);
 CString result; result.SetLength(0x100);
 strftime(result.GetCString(),result.GetLength(),Format.GetCString(),local_time);
 result.SetLength();
 return result;
}

CString GMTimeToStrF(const time_t Time, const CString& Format)
{
 struct tm *local_time;
 local_time = gmtime(&Time);
 CString result; result.SetLength(0x100);
 strftime(result.GetCString(),result.GetLength(),Format.GetCString(),local_time);
 result.SetLength();
 return result;
}

//------------------------------------------------------------------------------
