#include "Entity.h"

vector<EntityAssets> Entity::m_ENTITIES = vector<EntityAssets>();

Entity::Entity() {
}

Entity::Entity(int st_tileCol, int st_tileRow, int identity, bool enemy) {
	m_rect.w = 60;
	m_rect.h = 78;
	m_enemy = enemy;

	setCoordsOnTile(st_tileCol, st_tileRow);
	
	m_healthbar = Healthbar(m_ENTITIES[identity].m_health, int2(m_rect.x + m_rect.w / 2, m_rect.y - HEALTHBAR_OFFSET_FROM_ENTITY), m_enemy);


	m_texture = m_ENTITIES[identity].m_texture;
	m_type = identity;
	m_dead = false;
	m_moving = false;
	m_destinationTile.first = -1;
	m_destinationTile.second = -1;
}

Entity::~Entity() {
}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
	for (int i = 0; i < m_projectile.size(); i++) {
		m_projectile[i].draw(renderer);
	}
	m_healthbar.draw(renderer);
}

void Entity::update() {
	if (m_moving) {
		continueMoving();
	}
	for (int i = 0; i < m_projectile.size(); i++) {
		if (!m_projectile[i].m_delete) {
			m_projectile[i].update();
		}
		if (m_projectile[i].m_delete) {
			m_projectile.erase(m_projectile.begin() + i);
			i--;
		}
	}
}

void Entity::readEntityAssets(SDL_Renderer* renderer) {
	ifstream read;
	read.open("config\\entity\\entity.txt");
	string temp;
	getline(read, temp, ';');

	int i = 0;
	while (!read.eof()) {
		m_ENTITIES.push_back(EntityAssets());

		int jumpingMelee, straightProj, piercingProj;
		read >> m_ENTITIES[i].m_name >> m_ENTITIES[i].m_health >> m_ENTITIES[i].m_moveRadius 
			 >> jumpingMelee >> straightProj >> piercingProj >> m_ENTITIES[i].m_doKnockback;

		m_ENTITIES[i].m_texture = loadTexture(renderer, "entity\\" + m_ENTITIES[i].m_name + ".bmp");

		if (jumpingMelee == -1) {
			m_ENTITIES[i].m_ranged = true;
			m_ENTITIES[i].m_jumpingMelee = false;
		}
		else {
			m_ENTITIES[i].m_ranged = false;
			m_ENTITIES[i].m_jumpingMelee = jumpingMelee;
		}

		m_ENTITIES[i].m_straightProjectile = min(straightProj, 0);
		m_ENTITIES[i].m_piercingProjectile = min(piercingProj, 0);

		//Read possible moves
		int a;
		string temp;
		read >> temp;
		while (temp != ";") {
			read >> a;
			m_ENTITIES[i].m_movableTiles.push_back(pair<int, int>(stoi(temp), a));
			read >> temp;
		}

		i++;
	}

}

void Entity::moveToTile(int tileCol, int tileRow) {
	//Check for terrain in the path should already be done
	if (m_curTile.first == tileCol && m_curTile.second == tileRow) {
		return;
	}
	m_moving = true;
	m_moveSpeed.x = (tileCol - m_curTile.first + 0.f) * TILE_SIZE / ENTITY_KNOCKBACK_TICKS;
	m_moveSpeed.y = (tileRow - m_curTile.second + 0.f) * TILE_SIZE / ENTITY_KNOCKBACK_TICKS;

	m_curTile.first = tileCol;
	m_curTile.second = tileCol;
	m_destinationTile.first = tileCol;
	m_destinationTile.second = tileRow;
}

void Entity::continueMoving() {
	grid2dCoords.x += m_moveSpeed.x;
	grid2dCoords.y += m_moveSpeed.y;

	float2 temp = floatGridToScreenCoords(grid2dCoords);
	temp.x += ISOM_TILE_H / 2;
	temp.y += ISOM_TILE_H / 4;
	setBottomCenterCoords(int2(temp.x, temp.y));

	m_healthbar.setCoords(int2(m_rect.x + m_rect.w / 2, m_rect.y - HEALTHBAR_OFFSET_FROM_ENTITY));

	int dest_x = m_destinationTile.first;
	int dest_y = m_destinationTile.second;
	if (int(grid2dCoords.x - TILE_SIZE / 2) == dest_x * TILE_SIZE || int(ceil(grid2dCoords.x - TILE_SIZE / 2)) == dest_x * TILE_SIZE) {
		if (int(grid2dCoords.y - TILE_SIZE / 2) == dest_y * TILE_SIZE || int(ceil(grid2dCoords.y - TILE_SIZE / 2)) == dest_y * TILE_SIZE) {
			m_moving = false;
			m_destinationTile.first = -1;
			m_destinationTile.second = -1;
			m_moveSpeed.x = 0;
			m_moveSpeed.y = 0;
		}
	}
}

void Entity::attack(int attackedTileCol, int attackedTileRow) {
	m_projectile.push_back(Projectile(m_curTile.first, m_curTile.second, attackedTileCol, attackedTileRow,
		m_ENTITIES[m_type].m_straightProjectile, m_ENTITIES[m_type].m_piercingProjectile));
}

void Entity::decreaseHealth(int decrease) {
	m_healthbar.decreaseHealth(decrease);
	if (m_healthbar.m_healthDepleted) {
		m_dead = true;
	}
}

void Entity::setCoordsOnTile(int tileCol, int tileRow) {
	m_curTile.first = tileCol;
	m_curTile.second = tileRow;

	grid2dCoords.x = tileCol * TILE_SIZE + TILE_SIZE / 2;
	grid2dCoords.y = tileRow * TILE_SIZE + TILE_SIZE / 2;

	//Change rect
	int2 temp = normalToIsom(int2(tileCol * TILE_SIZE, tileRow * TILE_SIZE));
	//temp.x += ISOM_TILE_W / 2;
	temp.y += ISOM_TILE_H / 2;

	setBottomCenterCoords(temp);
}

void Entity::setCenterCoords(int2 centerCoords) {
	m_rect.x = centerCoords.x - m_rect.w / 2;
	m_rect.y = centerCoords.y - m_rect.h / 2;
}

void Entity::setBottomCenterCoords(int2 bottomCenterCoords) {
	//Bottom of the rect is on the bottom of the tile
	m_rect.x = bottomCenterCoords.x - m_rect.w / 2;
	m_rect.y = bottomCenterCoords.y - m_rect.h - 5;
}