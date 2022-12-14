#include "global.h"
#include "RadarValues.h"

#include "RageUtil.h"

RadarValues::RadarValues()
{
	MakeUnknown();
}

void RadarValues::MakeUnknown()
{
	FOREACH_ENUM( RadarCategory, rc )
	{
		(*this)[rc] = RADAR_VAL_UNKNOWN;
	}
}

void RadarValues::Zero()
{
	FOREACH_ENUM( RadarCategory, rc )
	{
		(*this)[rc] = 0;
	}
}


/* iMaxValues is only used for writing compatibility fields in non-cache
 * SM files; they're never actually read. */
RString RadarValues::ToString( int iMaxValues ) const
{
	if( iMaxValues == -1 )
		iMaxValues = NUM_RadarCategory;
	iMaxValues = min( iMaxValues, (int)NUM_RadarCategory );

	vector<RString> asRadarValues;
	for( int r=0; r < iMaxValues; r++ )
	{
		asRadarValues.push_back(ssprintf("%.3f", (*this)[r]));
	}

	return join( ",",asRadarValues );
}

void RadarValues::FromString( RString sRadarValues )
{
	vector<RString> saValues;
	split( sRadarValues, ",", saValues, true );

	if( saValues.size() != NUM_RadarCategory )
	{
		MakeUnknown();
		return;
	}

	FOREACH_ENUM( RadarCategory, rc )
	{
		(*this)[rc] = StringToFloat(saValues[rc]);
	}
    
}

/*
 * (c) 2001-2004 Chris Danford
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
