/****************************************************************************
* Copyright (C) 2019 Eric Mor
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

#pragma once

#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\Image.h>

namespace UTFWin
{
	enum class BackgroundTiling : uint32_t
	{
		/// Stretches background image.
		Stretch = 0,
		/// Tiles image.
		Tile = 1,
		/// Stretches center of image and tiles edges,
		CenterStretch = 2,
		/// Tiles center and edges.
		CenterTile = 3
	};

	///
	/// An abstract class that has the methods that a drawable for a dialog would require.
	///
	class IDialogDrawable : public UTFWinObject
	{
	public:
		enum
		{
			kImageBackground = 0,
			kImageTitleBar = 1,
			kImageBorderLeft = 2,
			kImageBorderRight = 3,
			kImageBorderTop = 4,
			kImageBorderBottom = 5,
			kImageBorderTopLeft = 6,
			kImageBorderTopRight = 7,
			kImageBorderBottomLeft = 8,
			kImageBorderBottomRight = 9
		};

		///
		/// Get the IDrawable instance that represents this class.
		///
		virtual IDrawable* ToDrawable() = 0;

		///
		/// Set the images used by this drawable. The index is one of the AbstractDialogDrawable::kImage... values.
		/// @param index The index of the image to set.
		/// @param pImage The image.
		///
		/* 14h */	virtual void SetImage(int index, Image* image) = 0;

		///
		/// Gets the color used to fill the background.
		/// @param dst The Color where the value will be set.
		/// @returns The background fill color.
		///
		/* 18h */	virtual Color GetBackgroundColor(Color& dst) const = 0;

		///
		/// Sets the color used to fill the background.
		/// @param color The new Color value.
		/// @returns The background fill color.
		///
		/* 1Ch */	virtual void SetBackgroundColor(Color color) = 0;

		///
		/// Gets the tiling mode used to fill the background.
		/// @param dst The BackgroundTiling where the value will be set.
		/// @returns The background tiling mode.
		///
		/* 20h */	virtual BackgroundTiling GetBackgroundTiling(BackgroundTiling& dst) const = 0;

		///
		/// Sets the color used to fill the background.
		/// @param value The new tiling value, from the BackgroundTiling enum.
		/// @returns The background tiling mode.
		///
		/* 24h */	virtual void SetBackgroundTiling(BackgroundTiling value) = 0;
	};

	///
	/// The standard IDrawable for a dialog component.
	///
	class DialogDrawable : public IDrawable, public DefaultLayoutElement, public IDialogDrawable
	{
	public:
		static const uint32_t TYPE = 0x6F0C6FF6;

		DialogDrawable();
		virtual ~DialogDrawable();

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual void Paint(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params) override;
		virtual bool IsColliding(const Math::Rectangle& area, const Math::Point& point, RenderParams& params) override;
		virtual bool GetDimensions(Dimensions& dst, int state, int index) override;
		virtual bool UseCollision(uint32_t type, bool& dst) override;

		virtual IDrawable* ToDrawable() override;
		virtual void SetImage(int index, Image* image) override;
		virtual Color GetBackgroundColor(Color& dst) const override;
		virtual void SetBackgroundColor(Color color) override;
		virtual BackgroundTiling GetBackgroundTiling(BackgroundTiling& dst) const override;
		virtual void SetBackgroundTiling(BackgroundTiling value) override;


	protected:
		/* 10h */	Color mBackgroundFillColor;
		/* 14h */	BackgroundTiling mBackgroundTiling;
		/* 18h */	intrusive_ptr<Image> mpImages[10];
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(DialogDrawable) == 0x40, "sizeof(DialogDrawable) != 40h");

	namespace InternalAddressList(DialogDrawable)
	{
		DefineAddress(SetSerializer, GetAddress(0x96D960, 0x96D560, 0x96D560));
		DefineAddress(GetProxyID, GetAddress(0x96BD30, 0x96B940, 0x96B940));

		DefineAddress(Paint, GetAddress(0x96DA20, 0x96D620, 0x96D620));
		DefineAddress(IsColliding, GetAddress(0x689880, 0x5ACA30, 0x5ACA30));
		DefineAddress(GetDimensions, GetAddress(0x96BD70, 0x96B980, 0x96B980));
		DefineAddress(UseCollision, GetAddress(0x951320, 0x950E00, 0x950E00));

		DefineAddress(ToDrawable, GetAddress(0x97E760, 0x96FEB0, 0x96FEB0));
		DefineAddress(SetImage, GetAddress(0x96BE50, 0x96BA60, 0x96BA60));
		DefineAddress(GetBackgroundColor, GetAddress(0x96BE90, 0x96BAA0, 0x96BAA0));
		DefineAddress(SetBackgroundColor, GetAddress(0x980670, 0xFCCD90, 0xFCCD90));
		DefineAddress(GetBackgroundTiling, GetAddress(0x96BEB0, 0x96BAC0, 0x96BAC0));
		DefineAddress(SetBackgroundTiling, GetAddress(0x96BEA0, 0x96BAB0, 0x96BAB0));
	}

	inline DialogDrawable::DialogDrawable()
		: mBackgroundFillColor(0xFF7F7F7F)
		, mBackgroundTiling()
		, mpImages{}
	{

	}

	inline DialogDrawable::~DialogDrawable() {}
}