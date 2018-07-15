//
// Copyright (C) 2004 Tanguy Fautré.
// For conditions of distribution and use,
// see copyright notice in tri_stripper.h
//
//////////////////////////////////////////////////////////////////////
// SVN: $Id: policy.h 86 2005-06-08 17:47:27Z gpsnoopy $
//////////////////////////////////////////////////////////////////////

#ifndef TRI_STRIPPER_HEADER_GUARD_POLICY_H
#define TRI_STRIPPER_HEADER_GUARD_POLICY_H

#include "../public_types.h"
#include "types.h"




namespace triangle_stripper {

	namespace detail {




class policy
{
public:
	policy(std::size_t MinStripSize, bool Cache);

	strip BestStrip() const;
	void Challenge(strip Strip, std::size_t Degree, std::size_t CacheHits);

private:
	strip	m_Strip;
	std::size_t	m_Degree;
	std::size_t	m_CacheHits;

	const std::size_t	m_MinStripSize;
	const bool		m_Cache;
};





inline policy::policy(std::size_t MinStripSize, bool Cache)
: m_Degree(0), m_CacheHits(0), m_MinStripSize(MinStripSize), m_Cache(Cache) { }


inline strip policy::BestStrip() const
{
	return m_Strip;
}




	} // namespace detail

} // namespace triangle_stripper




#endif // TRI_STRIPPER_HEADER_GUARD_POLICY_H
