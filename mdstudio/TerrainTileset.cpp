///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2015 Matt Phillips, Big Evil Corporation
///////////////////////////////////////////////////////

#include "TerrainTileset.h"
#include <ion/core/cryptography/Hash.h>

TerrainTileset::TerrainTileset()
{
}

void TerrainTileset::Clear()
{
	m_tiles.clear();
}

TerrainTileId TerrainTileset::AddTerrainTile()
{
	TerrainTileId index = m_tiles.size();
	m_tiles.push_back(TerrainTile());
	m_tiles[index].CalculateHash();
	AddToHashMap(index);
	return index;
}

void TerrainTileset::PopBackTerrainTile()
{
	RemoveFromHashMap(m_tiles.size() - 1);
	m_tiles.pop_back();
}

void TerrainTileset::HashChanged(TerrainTileId tileId)
{
	RemoveFromHashMap(tileId);
	m_tiles[tileId].CalculateHash();
	AddToHashMap(tileId);
}

void TerrainTileset::AddToHashMap(TerrainTileId tileId)
{
	m_hashMap.insert(std::make_pair(m_tiles[tileId].GetHash(), tileId));
}

void TerrainTileset::RemoveFromHashMap(TerrainTileId tileId)
{
	m_hashMap.erase(m_tiles[tileId].GetHash());
}

void TerrainTileset::CalculateHash(const TerrainTile& tile, u64& hash) const
{
	s8 heights[TerrainTile::tileWidth];
	tile.GetHeights(heights);

	hash = ion::Hash64((const u8*)heights, TerrainTile::tileWidth);
}

TerrainTileId TerrainTileset::FindDuplicate(const TerrainTile& tile) const
{
	//Calculate hash
	u64 hash;
	CalculateHash(tile, hash);

	//Find duplicate
	return FindDuplicate(hash);
}

TerrainTileId TerrainTileset::FindDuplicate(u64 hash) const
{
	//Find duplicate
	HashMap::const_iterator it = m_hashMap.find(hash);

	if(it != m_hashMap.end())
	{
		return it->second;
	}

	return InvalidTerrainTileId;
}

TerrainTile* TerrainTileset::GetTerrainTile(TerrainTileId tileId)
{
	TerrainTile* tile = NULL;

	if(tileId != InvalidTerrainTileId && tileId < m_tiles.size())
	{
		tile = &m_tiles[tileId];
	}

	return tile;
}

const TerrainTile* TerrainTileset::GetTerrainTile(TerrainTileId tileId) const
{
	const TerrainTile* tile = NULL;

	if(tileId != InvalidTerrainTileId && tileId < m_tiles.size())
	{
		tile = &m_tiles[tileId];
	}

	return tile;
}

int TerrainTileset::GetCount() const
{
	return m_tiles.size();
}

void TerrainTileset::Serialise(ion::io::Archive& archive)
{
	archive.Serialise(m_tiles, "tiles");
	archive.Serialise(m_hashMap, "hashMap");
}

void TerrainTileset::Export(std::stringstream& stream) const
{
	for(int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i].Export(stream);
		stream << std::endl;
	}
}

void TerrainTileset::Export(ion::io::File& file) const
{
	for(int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i].Export(file);
	}
}