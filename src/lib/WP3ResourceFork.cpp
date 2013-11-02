/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WP3ResourceFork.h"
#include "libwpd_internal.h"
#include "WPXEncryption.h"
#include <vector>
#include <sstream>

WP3ResourceFork::WP3ResourceFork(RVNGInputStream *input, WPXEncryption *encryption) :
	m_resourcesTypeMultimap(), m_resourcesIDMultimap()
{
	input->seek(16, RVNG_SEEK_SET);
	uint32_t dataOffset = readU32(input, encryption, true);
	uint32_t mapOffset = readU32(input, encryption, true);
	/* uint32_t dataLength = */
	readU32(input, encryption, true);
	/* uint32_t mapLength = */
	readU32(input, encryption, true);

	input->seek(40+mapOffset, RVNG_SEEK_SET);

	uint32_t typeOffset = readU16(input, encryption, true);
	uint32_t nameListOffset = readU16(input, encryption, true);

	input->seek(16+typeOffset+mapOffset, RVNG_SEEK_SET);
	uint16_t resourceTypesNumber = (uint16_t)(1 + readU16(input, encryption, true));

	for (unsigned i=0; i < resourceTypesNumber; i++)
	{
		uint32_t resourceType = readU32(input,encryption, true);
		uint32_t resourcesNumber = 1+readU16(input, encryption, true);
		uint32_t referenceListOffset = 16+typeOffset+mapOffset+readU16(input, encryption, true);
		long position = input->tell();
		input->seek(referenceListOffset, RVNG_SEEK_SET);
		for (uint32_t j=0; j < resourcesNumber; j++)
		{
			uint32_t resourceReferenceID = readU16(input, encryption, true);
			uint16_t resourceNameOffset = readU16(input, encryption, true);
			RVNGString resourceName;
			if (resourceNameOffset != 0xffff)
			{
				long position2 = input->tell();
				input->seek(16+mapOffset+nameListOffset+resourceNameOffset, RVNG_SEEK_SET);
				resourceName = readPascalString(input, encryption);
				input->seek(position2, RVNG_SEEK_SET);
			}
			uint8_t resourceAttributes = readU8(input, encryption);
			uint32_t offsetToData = (uint32_t)((uint32_t)readU8(input, encryption) << 16);
			offsetToData |= readU16(input, encryption, true);
			offsetToData += 16+dataOffset;
			long position3 = input->tell();
			input->seek(offsetToData, RVNG_SEEK_SET);
			uint32_t resourceDataSize = readU32(input, encryption, true);

			unsigned long oldEncryptionOffset = 0;
			unsigned char oldEncryptionMaskBase = 0;
			if (encryption)
			{
				oldEncryptionOffset = encryption->getEncryptionStartOffset();
				oldEncryptionMaskBase = encryption->getEncryptionMaskBase();
				/* WBOX resource and PICT resource for the time being */
				if (resourceType == 0x57424f58 /* WBOX */ || resourceType == 0x50494354 /* PICT */)
				{
					encryption->setEncryptionStartOffset((unsigned long)input->tell());
					encryption->setEncryptionMaskBase(0);
				}
			}

			RVNGBinaryData resourceData;
			for (unsigned long k = 0; k < (unsigned long)resourceDataSize && !input->isEnd(); k++)
				resourceData.append((unsigned char)readU8(input, encryption));

			if (encryption)
			{
				encryption->setEncryptionStartOffset(oldEncryptionOffset);
				encryption->setEncryptionMaskBase(oldEncryptionMaskBase);
			}

			input->seek(position3, RVNG_SEEK_SET);
			WP3Resource *resource = new WP3Resource(resourceType, resourceReferenceID, resourceName, resourceAttributes, resourceData);
			m_resourcesTypeMultimap.insert(std::multimap<uint32_t, WP3Resource *>::value_type( resourceType, resource ) );
			m_resourcesIDMultimap.insert(std::multimap<uint32_t, WP3Resource *>::value_type( resourceReferenceID, resource ) );
			WPD_DEBUG_MSG(("WP3Resource: Type 0x%.8x, ID %i, name %s, attributes 0x%.2x\n", resourceType, resourceReferenceID, resourceName.cstr(), resourceAttributes));
			input->seek(4, RVNG_SEEK_CUR);
#if 0
			RVNGInputStream *tmpBinaryStream = const_cast<RVNGInputStream *>(resourceData.getDataStream());
			int indexNumber = 0;
			while (!tmpBinaryStream->isEnd())
			{
				if (!(indexNumber % 16))
					printf("%.8x: ", indexNumber);
				else if (!(indexNumber % 8))
					printf("| ");
				printf("%.2x ", readU8(tmpBinaryStream, 0));
				indexNumber++;
				if (!(indexNumber % 16))
					printf("\n");
			}
			printf("\n");
#endif
#if 0
			std::ostringstream filename;
			filename << "binarydump" << m_resourcesTypeMultimap.size() << ".bin";
			FILE *f = fopen(filename.str().c_str(), "wb");
			RVNGBinaryData tmpResData;
			for (int tmpIndex = 0; tmpIndex < 512; tmpIndex++)
				tmpResData.append((const unsigned char)0);
			tmpResData.append(resourceData);
			if (f)
			{
				RVNGInputStream *tmpStream = const_cast<RVNGInputStream *>(tmpResData.getDataStream());
				while (!tmpStream->isEnd())
					fprintf(f, "%c", readU8(tmpStream, 0));
				fclose(f);
			}
#endif
		}
		input->seek(position, RVNG_SEEK_SET);
	}
}

WP3ResourceFork::~WP3ResourceFork()
{
	// delete the pointers from one of the multimaps.
	for (std::multimap<uint32_t, WP3Resource *>::iterator iter = m_resourcesTypeMultimap.begin(); iter != m_resourcesTypeMultimap.end(); ++iter)
		delete iter->second;
}

const WP3Resource *WP3ResourceFork::getResource(uint32_t type, uint32_t ID) const
{
	std::pair< std::multimap<uint32_t, WP3Resource *>::const_iterator, std::multimap<uint32_t, WP3Resource *>::const_iterator > tempPair
	    = m_resourcesTypeMultimap.equal_range(type);

	if (tempPair.first == m_resourcesTypeMultimap.end())
		return NULL;

	for (std::multimap<uint32_t, WP3Resource *>::const_iterator iter = tempPair.first; iter != tempPair.second; ++iter)
		if (iter->second->getResourceReferenceID() == ID )
			return iter->second;

	return NULL;
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
