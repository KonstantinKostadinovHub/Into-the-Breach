#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::Terrain(int st_tileCol, int st_tileRow)
{
	m_rect.w = 100;
	m_rect.h = 100;
	m_curTile.first =

}

Terrain::~Terrain()
{
}

void Terrain::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}
