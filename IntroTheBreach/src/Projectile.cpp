#include "Projectile.h"

SDL_Texture* Projectile::m_PROJECTILE_TEXTURE = nullptr;

Projectile::Projectile() {
}

Projectile::Projectile(int st_tileCol, int st_tileRow, int destinationTileCol, int destinationTileRow) {
	m_rect.w = PROJECTILE_SIZE;
	m_rect.h = PROJECTILE_SIZE;
	
	m_realCoords = gridToScreenCoords(int2(st_tileCol * TILE_SIZE - TILE_SIZE / 2, st_tileRow * TILE_SIZE - TILE_SIZE / 2));
	m_destinationCoords = gridToScreenCoords(int2(destinationTileCol * TILE_SIZE - TILE_SIZE / 2, destinationTileRow * TILE_SIZE - TILE_SIZE / 2));
	m_z = 0;

	m_vel.z = 15;

	int ticksLifespan = m_vel.z * 4 + 1;

	m_vel.x = (destinationTileCol * TILE_SIZE - st_tileCol * TILE_SIZE + 0.f) / ticksLifespan;
	m_vel.y = (destinationTileRow * TILE_SIZE - st_tileRow * TILE_SIZE + 0.f) / ticksLifespan;

	m_delete = false;
}

Projectile::~Projectile() {
}

void Projectile::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_PROJECTILE_TEXTURE, NULL, &m_rect);
}

void Projectile::update() {
	m_realCoords.x += m_vel.x;
	m_realCoords.y += m_vel.y;
	m_z += m_vel.z;
	m_vel.z -= GRAVITY_PULL;

	if (m_z <= 0) {
		m_delete = true;
	}

	int2 temp = gridToScreenCoords(m_realCoords);
	m_rect.x = temp.x;
	m_rect.y = temp.y - m_z;
}
