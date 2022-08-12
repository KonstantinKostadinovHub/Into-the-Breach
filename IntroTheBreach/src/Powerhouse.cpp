#include "Powerhouse.h"

#include <fstream>
#include <string>

using std::fstream;
using std::to_string;

vector<Powerhouse*> Powerhouse::m_all = vector<Powerhouse*>();

Powerhouse::Powerhouse()
{
    m_team = 0;
}

Powerhouse::~Powerhouse()
{
}

/*
* @param renderer   - pointer to the main renderer
* @param type       - the level of the house that we want
* @param team       - to which player it belongs
*/
void Powerhouse::init(SDL_Renderer* renderer, POWERHOUSE type, int team)
{
    string tmp;

    fstream stream;

    stream.open("config\\game\\powerhouses\\powerhouse_" + to_string(int(type)) + ".txt");

    stream >> tmp >> m_rect.w >> m_rect.h;

    stream >> tmp >> m_health;

    stream.close();

    m_texture = loadTexture(renderer, "game\\powerhouses\\powerhouse_" + to_string(int(type)) + ".bmp");

    m_team = team;

    m_all.push_back(this);
}

// do not forget to also call delete
void Powerhouse::destroy()
{
    for (int i = 0; i < m_all.size(); i++)
    {
        if (m_all[i] == this)
        {
            m_all.erase(m_all.begin() + i);
            break;
        }
    }

    SDL_DestroyTexture(m_texture);
}

void Powerhouse::takeDamage(int damage)
{
    m_health -= damage;
}

/*
* @param renderer - the main renderer
* @param coor - the centered coordinates of the tile
*/
void Powerhouse::draw(SDL_Renderer* renderer, int2 coor)
{
    m_rect.x = coor.x - m_rect.w / 2;
    m_rect.y = coor.y - m_rect.h;
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}

// sums up the health of all powerhouses that belong to a given player
int Powerhouse::getTeamHealth(int team)
{
    int res = 0;

    for (auto& house : m_all)
    {
        if (house->m_team == team)
        {
            res += house->m_health;
        }
    }

    return res;
}
