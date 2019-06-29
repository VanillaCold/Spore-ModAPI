/****************************************************************************
* Copyright (C) 2018 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include <Spore\UTFWin\Allocator.h>
#include <Spore\UTFWin\UTFWinObject.h>

namespace UTFWin
{
	/////////////////////
	//// Allocator.h ////
	/////////////////////

	auto_STATIC_METHOD_(UTFWin, ICoreAllocator*, GetAllocator);

	////////////////////////
	//// UTFWinObject.h ////
	////////////////////////

	void* UTFWinObject::operator new(size_t n, size_t align, const char* pName, ICoreAllocator* pAllocator)
	{
		return STATIC_CALL(GetAddress(0x951760, 0x951230, 0x951230), void*, 
			PARAMS(size_t n, size_t align, const char* pName, ICoreAllocator* pAllocator), PARAMS(n, align, pName, pAllocator));
	}

	void* UTFWinObject::operator new(size_t n)
	{
		return operator new(n, 4, "", UTFWin::GetAllocator());
	}

	void UTFWinObject::operator delete(void* p)
	{
		STATIC_CALL(GetAddress(0x9517C0, 0x951290, 0x951290), void, PARAMS(void* p), PARAMS(p));
	}


	//////////////////////////
}