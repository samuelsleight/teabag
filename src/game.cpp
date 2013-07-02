#include "inc/game.hpp"

TEABAG_NAMESPACE_BEGIN

Game::Game()
	: tileMan(),
	  sprMan(),
	  entMan(),
	  gameMap(&tileMan, &sprMan, &entMan) {

} // Game::Game(bool init);

int Game::init(bool loadMapNow) {
	TEABAG_LOG("Reading main game definition file.")

	std::ifstream mainfile(TEABAG_MAIN_FILE, std::ifstream::in);
	if(!mainfile) {
		TEABAG_FILE_NOT_FOUND(TEABAG_MAIN_FILE)
		return -1;

	} // if(!mainfile);

	std::string line;
	while(std::getline(mainfile, line)) {
		std::istringstream lineStream(line);
		std::string value;

		lineStream >> value;

		if(value == "name") {
			gameName == lineStream.str();

		} // if(value == "name");
		else if(value == "start") {
			lineStream >> gameMap.mapName;

		} // else if(value == "start");

	} // while(std::getline(mainfile, line));

	mainfile.close();

	if(gameName.empty()) {
		TEABAG_LOG("No game name provided.")
		gameName = TEABAG_DEFAULT_NAME;

	} // if(gameName == "");

	TEABAG_LOG("Game name: " + gameName)

	if(loadMapNow) {
		if(gameMap.mapName.empty()) {
			TEABAG_ERROR("No initial map set to load.")
			return -1;

		} // if(currentMapName.empty());
		else {
			if(gameMap.loadMap() < 0) {
				return -1;

			} // if(loadMap() < 0);

		} // else;

	} // if(loadMapNow);

	TEABAG_LOG("Opening SFML window.")
	gameWindow.create(sf::VideoMode(800, 600), gameName);

	return 0;

} // void Game::init();

int Game::addEventCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func) {
	return eventMan.addCallback(sfEventType, func);

} // int Game::addEventCallback(sf::Event::EventType sfEventType, std::function<void(sf::Event)> func);

int Game::run() {
	while(gameWindow.isOpen()) {
		sf::Event e;
		while(gameWindow.pollEvent(e)) {
			eventMan.handleEvent(e);

		} // while(gameWindow.pollEvent(e));

		gameWindow.clear();

		for(auto& v : gameMap.mapTiles) {
			for(auto& t : v) {
				gameWindow.draw(t);

			} // for(auto& t : v);

		} // for(auto& v : gameMap.mapTiles);

		for(auto& p : entMan.entities) {
			gameWindow.draw(p.second.sprite);

		} // for(auto& p : entMan.entities);

		gameWindow.display();

	} // while(gameWindow.isOpen());

	return 0;

} // int Game::run();

int Game::quit() {
	gameWindow.close();

	return 0;

} // int Game::quit();

TEABAG_NAMESPACE_END
