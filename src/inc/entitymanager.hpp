#ifndef TEABAG_ENTITYMANAGER_HPP
#define TEABAG_ENTITYMANAGER_HPP

#include "defines.hpp"
#include "optionsparser.hpp"

#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

class Game;
class GameMap;

TEABAG_INTERNAL

class EntityManager {
private:
	friend class teabag::Game;
	friend class GameMap;

	EntityManager();
	~EntityManager();

	int addEntity(std::string name, int x, int y);

	sf::Sprite* getEntity(std::string name);

	std::unordered_map<std::string, sf::Texture> texMap;
	std::unordered_map<std::string, sf::Sprite> entityMap;

}; // class EntityManager;

TEABAG_INTERNAL_END

TEABAG_NS_END

#endif // TEABAG_ENTITYMANAGER_HPP
