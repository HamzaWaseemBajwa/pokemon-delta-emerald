#include "MainClass.h"
#include <SDL.h>
#include <fstream>
#include "HybridHealItem.h"
#include <string>
#include <cctype>
#include <sstream>
#include "BaseBattle.h"
#include "TrainerBattle.h"
#include "Sound.h"


extern std::vector<PokemonBase> pokemon_list;
extern std::vector<PokemonMove*> move_list;
extern std::vector<Item*> item_list;

MainClass::MainClass() : _current(nullptr)
{
	Sound::InitlizeMusic();

	_quit = false;

	_screenHeight = 720;
	_screenWidth = 720;

	_sdlSetup = new SdlSetup(&_quit, _screenWidth, _screenHeight);
	_statusBar = new StatusBar(_sdlSetup);

	_current = new Enviroment(_sdlSetup, _screenWidth, _screenHeight, &_cameraX, &_cameraY);

	LoadSaveFile();
}


void MainClass::LoadSaveFile()
{
	//temporary variables for storage 
	std::string playerName;
	std::array <PokemonGen*, 6> pokemonSet = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	std::array<PokemonMove*, 4> moves = { nullptr, nullptr, nullptr, nullptr };
	std::array<int, 4> movePp = { 0, 0, 0, 0 };
	int money = 0;
	Bag* player_bag = new Bag();

	std::ifstream saveFile;
	saveFile.open("SaveFiles/SaveFile.xml");
	std::string fileString;
	bool fileRead = false;
	getline(saveFile, fileString);
	if (fileString == "<SaveFile>") //Start file read
	{
		while (!fileRead)
		{
			if (fileString == "</SaveFile>") //End file read
			{
				fileRead = true;
			}
			else if (fileString == "<Position>") //Get the player's position
			{
				getline(saveFile, fileString);
				while (fileString != "</Position>")
				{
					std::stringstream lineStream(fileString);
					std::string pos[2];
					int i = 0;
					while (getline(lineStream, pos[i], ','))
					{
						++i;
					}
					_cameraX = stod(pos[0]);
					_cameraY = stod(pos[1]);
					getline(saveFile, fileString);
				}
			}
			else if (fileString == "<Player>") //Get player Data
			{
				getline(saveFile, fileString);
				while (fileString != "</Player>")
				{
					if (fileString == "<Name>") //Get player Name
					{
						getline(saveFile, fileString);
						while (fileString != "</Name>")
						{
							playerName = fileString;
							getline(saveFile, fileString);
						}
					}
					else if (fileString == "<Money>") //Get player money
					{
						getline(saveFile, fileString);
						while (fileString != "</Money>")
						{
							money = stoi(fileString);
							getline(saveFile, fileString);
						}
					}
					else if (fileString == "<Bag>") //Get player's bag data
					{
						getline(saveFile, fileString);
						while (fileString != "</Bag>")
						{
							if (fileString == "<Item>") //get each item and quantity
							{
								getline(saveFile, fileString);
								std::stringstream lineStream(fileString);
								std::string data[3];
								int i = 0;
								while (getline(lineStream, data[i], ','))
								{
									++i;
								}
								player_bag->AddItem(item_list[stoi(data[0])], stoi(data[1]));
							}
							getline(saveFile, fileString);
						}

					}
					else if (fileString == "<PokemonSet>") //Get player's pokemon set
					{
						int pokemon_index = 0;
						while (fileString != "</PokemonSet>")
						{
							getline(saveFile, fileString);
							if (fileString == "<Pokemon>") //Get individual Pokemon Data
							{
								getline(saveFile, fileString);
								std::stringstream lineStream(fileString);
								std::string data[9];
								int i = 0;
								while (getline(lineStream, data[i], ','))
								{
									++i;
								}
								getline(saveFile, fileString);
								while (fileString != "</Pokemon>")
								{
									if (fileString == "<MoveSet>") //Get Pokemon's moveset
									{
										int moveIndex = 0;
										while (fileString != "</MoveSet>")
										{
											getline(saveFile, fileString);
											if (fileString == "<Move>") //Get move data
											{
												while (fileString != "</Move>")
												{
													getline(saveFile, fileString);
													std::string move_data[3];
													std::stringstream lineStream_2(fileString);
													int j = 0;
													while (getline(lineStream_2, move_data[j], ','))
													{
														++j;
													}
													moves[moveIndex] = move_list[stoi(move_data[0])];
													movePp[moveIndex] = stoi(move_data[1]);
													++moveIndex;

													getline(saveFile, fileString);
												}
											}
										}
										MoveSet * moveSet = new MoveSet(moves, movePp);
										pokemonSet[pokemon_index] = new PokemonGen(pokemon_list[stoi(data[0])], stoi(data[1]), stoi(data[2]), static_cast<StatusEffect>(stoi(data[3])), stoi(data[4]), static_cast<PokemonNature>(stoi(data[5])), ConvertToArray(data[6]), ConvertToArray(data[7]), *moveSet);
										++pokemon_index;
										delete moveSet;
										moves = { nullptr, nullptr, nullptr, nullptr };
										movePp = { 0,0,0,0 };
									}
									getline(saveFile, fileString);
								}

							}
						}
					}
					getline(saveFile, fileString);
				}
				_player = new Player(playerName, _sdlSetup, &_cameraX, &_cameraY, "trchar001.png", pokemonSet, player_bag, money, _current); //create the player
				getline(saveFile, fileString);
			}
			getline(saveFile, fileString);
		}
	}
	else
	{
		std::cout << "Invalid file format\n";
	}
	saveFile.close();
}

MainClass::~MainClass()
{
	Sound::EndMusic();
	delete _player;
	delete _current;
	delete _sdlSetup;
	SDL_Quit();
}

void MainClass::TitleScreen() const
{
	Sound::ChangeMusic("TitleScreen.ogg"); //Play the title screen music
	std::vector<Sprite*> images;
	for (int i = 0; i < 90; ++i) //load all the images
	{
		const std::string frame = ((i < 10) ? "0" : "") + std::to_string(i); //generate filename for each frame
		const std::string filePath = "Resources/TitleScreen/frame_" + frame + "_delay-0.04s.png";
		images.push_back(new Sprite(_sdlSetup->GetRenderer(), filePath, 0, 120, 720, 480, nullptr, nullptr, nullptr)); //load the image and store in vector

	}
	int i = 0;
	while (_sdlSetup->GetMainEvent()->key.keysym.sym != SDLK_SPACE) //display images in a loop
	{
		i = i == 90 ? 0 : i;
		_sdlSetup->Begin();
		images[i]->DrawSteady();
		_sdlSetup->End();
		SDL_Delay(30);
		++i;
	}
	Sound::PlayInteractSound();
	for (Sprite* image : images) //clear the images
	{
		delete image;
	}
	images.clear();
}

void MainClass::StartScreen() const
{
	Sound::EndMusic();
	Text* playerName = new Text(_sdlSetup, 150, 30, 20);
	Text* noOfPokemon = new Text(_sdlSetup, 150, 70, 20);
	Text* money = new Text(_sdlSetup, 150, 110, 20);
	Text* currentZone = new Text(_sdlSetup, 150, 150, 20);
	Sprite* playerIcon = new Sprite(_sdlSetup->GetRenderer(), "Resources/CharacterSprites/trchar001.png", 30, 30, 128, 128, nullptr, nullptr, nullptr);
	playerIcon->GetCrop()->w = 64;
	playerIcon->GetCrop()->h = 64;

	int number = 0;

	for (int i = 0; i < 6; ++i) //count the number of pokemon in the player's party
	{
		if (_player->PokemonSet()[i] != nullptr)
		{
			++number;
		}
	}
	SDL_Rect bground_current = { 20, 20, 680, 200 };
	_current->Update();
	while (_sdlSetup->GetMainEvent()->key.keysym.sym != SDLK_z) //display the current save file information
	{
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 153, 255, 0);
		_sdlSetup->Begin();
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 255, 255, 0);
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &bground_current);
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
		SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &bground_current);
		playerName->Update("Player Name: " + _player->GetName());
		noOfPokemon->Update("Pokemon: " + std::to_string(number));
		money->Update("Money: " + std::to_string(_player->GetMoney()));
		currentZone->Update("Location: " + _current->DisplayName());
		playerIcon->DrawSteady();
		_sdlSetup->End();
	}
	Sound::PlayInteractSound();
	delete playerName;
	delete noOfPokemon;
	delete money;
	delete currentZone;
	delete playerIcon;
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
}

void MainClass::DisplayBag() const
{
	std::vector<Sprite*> itemSprites; //vector of item icons
	std::vector<Text*> text1; //vector of item names
	std::vector<Text*> text2; //vector of item quantities
	std::vector<Button> itemButtons; //vector of item buttons
	Text titleText{ _sdlSetup, 120, 10, 10 }; //Bag title text
	for (int i = 0; i < _player->PlayerBag().Size(); ++i) //for each item in the bag, add the item's sprite, its name and quantity to respective vectors
	{
		std::string fileName = "Resources/items/";
		fileName += _player->PlayerBag()[i]->stored_item->Name() + ".png";
		itemSprites.push_back(new Sprite(_sdlSetup->GetRenderer(), fileName, 40, 45 + 39 * i, 32, 32, nullptr, nullptr, nullptr));
		text1.push_back(new Text{ _sdlSetup, 80 , i * 39 + 45, 18 });
		text2.push_back(new Text{ _sdlSetup, 200, i * 39 + 45, 18 });
		itemButtons.push_back(Button(_sdlSetup, 40, 40 + 39 * i, 200, 40));
	}

	//mouse location 

	int x = 0;
	int y = 0;
	bool clicked = false;
	int clickedButton = 0;

	while (_sdlSetup->GetMainEvent()->key.keysym.sym != SDLK_x && !clicked) //while user does exit menu, or an item is not clicked
	{
		_sdlSetup->Begin();
		_current->DrawBack();
		_player->GetPlayerSprite()->Draw();
		_current->DrawFront();
		SDL_Rect rect = { 40,0, 200,400 };
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 255, 255, 0);
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &rect);
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
		SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &rect);
		titleText.Update("Bag");
		for (int i = 0; i < _player->PlayerBag().Size(); ++i) //for each item, display the item icon and information
		{
			SDL_Rect borderRect = { 40,40 + 39 * i, 200, 40 };
			SDL_Rect iconRect = { 40, 40 + 39 * i, 40,40 };
			SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &borderRect);
			SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &iconRect);
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
			text1[i]->Update(_player->PlayerBag()[i]->stored_item->Name());
			text2[i]->Update("x " + std::to_string(_player->PlayerBag()[i]->quantity));
			itemSprites[i]->DrawSteady();
		}
		SDL_GetMouseState(&x, &y);
		if (_sdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONUP) //if the mouse is clicked
		{
			int buttonIndex = 0;

			for (std::vector<Button>::iterator i = itemButtons.begin(); i != itemButtons.end(); ++i) //loop thought the button vector, check which was clicked
			{
				if ((*i).Clicked(x, y))
				{
					clicked = true;
					Sound::PlayInteractSound();
					clickedButton = buttonIndex; //set the clicked button index 
					std::cout << buttonIndex << std::endl;
					(*i).ClickedAnimation();
					SDL_Delay(100);
					break;
				}
				++buttonIndex;
			}
		}
		if (clicked)
		{
			DisplayPokemonSet(UseItem, _player->PlayerBag()[clickedButton]->stored_item); //display the pokemon set, and pass the the item to be used
			clicked = false;
		}

		_sdlSetup->End();
	}
	for (int i = 0; i < _player->PlayerBag().Size(); ++i) //delete all the items icons and text
	{
		delete text1[i];
		delete text2[i];
		delete itemSprites[i];
	}
}

void MainClass::RandomWildBattle() const
{
	Sound::EndMusic();
	Sound::ChangeMusic("WildMusic.ogg");
	//start a wild battle with a random pokemon and moveset
	PokemonGen* wildPokemon = new PokemonGen(pokemon_list[rand() % 662], rand() % 100 + 1, MoveSet({ move_list[rand() % 340], move_list[rand() % 340], move_list[rand() % 340], move_list[rand() % 340] }));
	BaseBattle* wildBattle = new BaseBattle(_player, wildPokemon);
	SDL_Delay(3000);
	wildBattle->InitilizeBattleWindow(); //open the battle window
	wildBattle->BattleLoop(); //start the battle loop
	if (!wildBattle->Captured())
	{
		delete wildPokemon;
	}
	delete wildBattle;
	Sound::ChangeMusic("Overworld.ogg");
}



void MainClass::PlayerMoved() const
{
	{
		for (Sprite* element : _current->GetGrass()) //loop through all grass tiles
		{
			if (_player->GetPlayerSprite()->GetImage()->LeftCol(*element->GetCollisionRectangle()) || _player->GetPlayerSprite()->GetImage()->RightCol(*element->GetCollisionRectangle())) //if player is colliding horizontally with tile
			{
				const int chance = rand() % 100; //randomizer for wild battle start
				if (chance < 2)
				{
					RandomWildBattle();
					break;
				}
			}
			if (_player->GetPlayerSprite()->GetImage()->TopCol(*element->GetCollisionRectangle()) || _player->GetPlayerSprite()->GetImage()->BottomCol(*element->GetCollisionRectangle())) //if player is colliding verticaly with tile
			{
				const int chance = rand() % 100;
				if (chance < 2)
				{
					RandomWildBattle();
					break;
				}
			}
		}
	}
}


void MainClass::PlayerInteract() const
{
	if (_current->legendary_pokemon != nullptr) //if the legendary pokemon still exists
	{

		if (_player->GetPlayerSprite()->GetImage()->TopCol(*_current->legendary_pokemon->GetCollisionRectangle())) //if the player is facing the pokemon
		{
			//Sound::EndMusic();
			Sound::PlayCry(pokemon_list[655].GetImagePath());
			_current->PokemonActive();
			const int delay = SDL_GetTicks();
			while (SDL_GetTicks() - delay < 2500)
			{
				_sdlSetup->Begin();
				//draw elements in order depth
				_current->DrawBack();
				_player->GetPlayerSprite()->Draw();
				_current->DrawFront();
				//update player sprite, environment
				_player->GetPlayerSprite()->Update();
				_current->Update();
				_statusBar->Draw(_player, _current); //draw status bar
				_sdlSetup->End();
			}
			Sound::EndMusic();
			Sound::ChangeMusic("LegendaryBattle.ogg");
			BaseBattle* wildBattle = new BaseBattle(_player, new PokemonGen(pokemon_list[655], 75, MoveSet({ move_list[324], move_list[170], move_list[96], move_list[213] }))); //start the battle
			wildBattle->InitilizeBattleWindow();
			wildBattle->BattleLoop();
			delete wildBattle;
			delete _current->legendary_pokemon;
			_current->legendary_pokemon = nullptr;
			Sound::ChangeMusic("Overworld.ogg");
		}
	}

	if (_player->GetPlayerSprite()->GetImage()->TopCol(*_current->GetPokemonCenter()->GetCollisionRectangle())) //if player is facing the pokemon center
	{
		Sound::PlayInteractSound();
		for (PokemonGen* pokemon : _player->PokemonSet()) //heal the players pokemon
		{
			if (pokemon != nullptr)
			{
				pokemon->Restore();
			}
		}
		Sound::PlaySound("Heal");
	}


	for (Trainer* trainer : _current->GetTrainers()) //if the player is facing any trainer who has not be defeated
	{
		if (_player->GetPlayerSprite()->GetImage()->TopCol(*trainer->GetSprite()->GetImage()->GetCollisionRectangle()))
		{
			Sound::PlayInteractSound();
			if (trainer->IsDefeated() == false)
			{
				TrainerBattle* battle = new TrainerBattle(_player, trainer);
				if (trainer->GetClass() == "Trainer")
				{
					Sound::ChangeMusic(trainer->GetName() + ".ogg");
				}
				else
				{
					Sound::ChangeMusic("TrainerMusic.ogg");
				}
				battle->InitilizeBattleWindow();
				battle->BattleLoop();
				delete battle;
				Sound::ChangeMusic("Overworld.ogg");
			}
		}
	}


	for (std::vector<ItemPickup*>::iterator i = _current->GetItems().begin(); i != _current->GetItems().end(); ++i) //loop through all of the environments items
	{
		//if the player is touching any item
		Sound::PlayInteractSound();
		if (_player->GetPlayerSprite()->GetImage()->TopCol(*(*i)->GetItemSprite()->GetCollisionRectangle()) || _player->GetPlayerSprite()->GetImage()->BottomCol(*(*i)->GetItemSprite()->GetCollisionRectangle()))
		{
			_player->PlayerBag().AddItem((*i)->GetItem()); //add item to player's bag
			delete *i; //delete from the environment;
			_current->GetItems().erase(i);
			break;
		}
		if (_player->GetPlayerSprite()->GetImage()->LeftCol(*(*i)->GetItemSprite()->GetCollisionRectangle()) || _player->GetPlayerSprite()->GetImage()->RightCol(*(*i)->GetItemSprite()->GetCollisionRectangle()))
		{
			_player->PlayerBag().AddItem((*i)->GetItem());
			delete *i;
			_current->GetItems().erase(i);
			break;
		}
	}
}

void MainClass::PokemonStatusBar(const int x, const int y, const int w, const int h, PokemonGen* pokemon) const
{
	SDL_Color old = {};
	SDL_GetRenderDrawColor(_sdlSetup->GetRenderer(), &old.r, &old.g, &old.b, &old.a); //get old renderer color
	const SDL_Color bgColor = { 255, 255, 255, 0 }; //background color of bar
	SDL_Rect bgrect = { x, y, w, h }; //background rectangle 
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(_sdlSetup->GetRenderer(), &bgrect);
	const double percent = static_cast<double>(pokemon->CurrentHp()) / static_cast<double>(pokemon->MaxHp()); //percentage to represent
	const int pw = static_cast<int>(static_cast<double>(w) * percent); //width of the bar
	SDL_Color fgColor; //set bar color based on remaining health
	if (percent > 0.5)
	{
		fgColor = { 0, 255, 0, 0 }; //green
	}
	else if (percent > 0.25)
	{
		fgColor = { 255, 231, 71, 0 }; //yellow 
	}
	else
	{
		fgColor = { 255, 0, 0, 0 }; //red
	}
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), fgColor.r, fgColor.g, fgColor.b, fgColor.a);
	const int px = x;
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(_sdlSetup->GetRenderer(), &fgrect);
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
	SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &bgrect); //bar outline

	//additonal info

	Text hp{ _sdlSetup, x - 3, y + 5 , 10 }; //pokemon HP
	Text name{ _sdlSetup,x, y - 25, 10 }; //pokemon Name
	Text level{ _sdlSetup, x + 80, y - 20 ,10 }; //pokemon Level
	if (pokemon->Status() != NoEffect) //Status effect if any
	{
		Text status{ _sdlSetup,x + 103, y + 6,15 };
		SDL_Rect statusRect = { x + 100, y + 8, 45, 15 };
		switch (pokemon->Status()) //generate different color for different status
		{
		case Paralysis:
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 200, 0, bgColor.a);
			break;
		case Poisoning:
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 165, 0, 255, bgColor.a);
			break;
		case Burn:
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 0, 0, bgColor.a);
			break;
		case Sleep:
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 165, 165, 165, bgColor.a);
			break;
		case Freeze:
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 225, 105, bgColor.a);
			break;
		case Faint:
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 180, 0, 0, bgColor.a);
			break;
		default:
			break;
		}
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &statusRect);
		status.Update(to_string(pokemon->Status()));

	}
	hp.Update(std::to_string(pokemon->CurrentHp()) + '/' + std::to_string(pokemon->MaxHp()));
	name.Update(pokemon->Name());
	level.Update("Lv. " + std::to_string(pokemon->Level()));
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), old.r, old.g, old.b, old.a);
}



void MainClass::DisplayPokemonSet(const DisplayMode mode, Item* item) const
{
	std::vector<Button> buttons; //vector of buttons
	std::vector<Sprite*> pokemonIcons; //vector of pokemon icons
	for (int i = 0; i < 6; ++i) //for each pokemon in set, add a button and an icon to the respective vecotrs
	{
		if (_player->PokemonSet()[i] != nullptr) //check if slot is not empty
		{
			const std::string filepath = "Resources/PokemonSprites/icon/" + _player->PokemonSet()[i]->GetImagePath() + ".png";
			pokemonIcons.push_back(new Sprite{ _sdlSetup->GetRenderer(), filepath, 20, i * 70 + 90, 64,64, nullptr, nullptr, nullptr });
			buttons.push_back(Button(_sdlSetup, 20, i * 70 + 100, 230, 64));
		}
	}

	bool clicked = false;
	int clickedButton = 0;

	int firstClick = -1; //index of first clicked pokemon
	int secondClick = -1; //index of second clicked pokemon


	while (_sdlSetup->GetMainEvent()->key.keysym.sym != SDLK_x && !clicked) //while user does not exit menu
	{
		//draw the background elements

		_sdlSetup->Begin();
		_current->DrawBack();
		_player->GetPlayerSprite()->Draw();
		_current->DrawFront();

		//menu background and outline

		SDL_Rect background = { 0, 90, 260, 435 };
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 65, 105, 255, 0);
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &background);
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 255, 255, 0);
		SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &background);

		//for each pokemon in set, display the icon and status bar

		for (int i = 0; i < 6; ++i)
		{
			if (_player->PokemonSet()[i] != nullptr)
			{
				pokemonIcons[i]->DrawSteady();
				PokemonStatusBar(84, i * 70 + 130, 100, 5, _player->PokemonSet()[i]);
			}
			SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 255, 255, 0);
			SDL_Rect border = { 20, i * 70 + 100, 230, 64 };
			SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &border);
		}

		//get the mouse location

		int x = 0;
		int y = 0;


		SDL_GetMouseState(&x, &y);
		if (_sdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN && !clicked)
		{
			int buttonIndex = 0;

			for (std::vector<Button>::iterator i = buttons.begin(); i != buttons.end(); ++i) //check which button was clicked
			{
				if ((*i).Clicked(x, y))
				{
					clicked = true;
					Sound::PlayInteractSound();
					clickedButton = buttonIndex;
					(*i).ClickedAnimation();
					break;
				}
				++buttonIndex;
			}
		}
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
		_sdlSetup->End();
		if (mode == SwitchPokemon) //if mode calling mode was Pokemon Switching
		{
			if (firstClick == -1) //set first clicked index
			{
				firstClick = clickedButton;
			}
			else if (secondClick == -1) //set second clicked index
			{
				secondClick = clickedButton;
				if (secondClick == firstClick) //if both indexes are the same, set both to original value
				{
					firstClick = -1;
					secondClick = -1;
				}
				else
				{
					//swap pokemon

					PokemonGen* temp = _player->PokemonSet()[firstClick];
					_player->PokemonSet()[firstClick] = _player->PokemonSet()[secondClick];
					_player->PokemonSet()[secondClick] = temp;

					//rebuild icons

					for (Sprite* icon : pokemonIcons)
					{
						delete icon;
					}
					pokemonIcons.clear();
					for (int i = 0; i < 6; ++i)
					{
						if (_player->PokemonSet()[i] != nullptr)
						{
							const std::string filepath = "Resources/PokemonSprites/icon/" + _player->PokemonSet()[i]->GetImagePath() + ".png";
							pokemonIcons.push_back(new Sprite{ _sdlSetup->GetRenderer(), filepath, 20, i * 70 + 90, 64,64, nullptr, nullptr, nullptr });

						}
					}
					//reset indexes

					firstClick = -1;
					secondClick = -1;
				}
			}
			clicked = false;
		}
	}

	//if button was clicked and mode is to use items

	if (clicked)
	{
		if (mode == UseItem)
		{
			if (item->Use(_player->PokemonSet()[clickedButton])) //use the item, and return whether it was successful
			{
				_player->PlayerBag().UseItem(_player->PlayerBag().GetItemIndex(item)); //reduce the items quantiy in bag
			}
		}
	}

	//clear the icons and buttons

	for (Sprite* icon : pokemonIcons)
	{
		delete icon;
	}
	buttons.clear();
	pokemonIcons.clear();
}

void MainClass::Update()
{
	switch (_sdlSetup->GetMainEvent()->type)
	{
	case SDL_KEYDOWN:
		switch (_sdlSetup->GetMainEvent()->key.keysym.sym) //switched on used key
		{
			//booleans used so only one click is registered per frame

		case SDLK_F1:
			_fileSaved = true;
			Sound::PlayInteractSound();
			break;
		case SDLK_F2:
			_showBag = true;
			Sound::PlayInteractSound();
			break;
		case SDLK_F3:
			_showPokemon = true;
			Sound::PlayInteractSound();
			break;
		case SDLK_z:
			_interact = true;
			Sound::PlayInteractSound();
			break;
		case SDLK_h:
			_helpMenu = true;
			Sound::PlayInteractSound();
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (_sdlSetup->GetMainEvent()->key.keysym.sym)
		{
		case SDLK_h:
			if (_helpMenu) //dislay help menu
			{
				Sprite* helpmenu = new Sprite(_sdlSetup->GetRenderer(), "Resources/HelpMenu.png", 100, 100, 480, 300, nullptr, nullptr, nullptr);
				while (_sdlSetup->GetMainEvent()->key.keysym.sym != SDLK_x) //until user exits
				{
					_sdlSetup->Begin();
					_current->DrawBack();
					_player->GetPlayerSprite()->Draw();
					_current->DrawFront();
					helpmenu->DrawSteady();
					_sdlSetup->End();
				}
				delete helpmenu;
				_helpMenu = false;
			}
			break;
		case SDLK_z:
			if (_interact)
			{
				PlayerInteract();
				_interact = false;
			}
			break;
		case SDLK_F1:
			if (_fileSaved)
			{
				SaveFile();
				_current->SaveEnviroment(); //save the enviroment's item and character layout
				_fileSaved = false;
			}
			break;
		case SDLK_F2:
		{
			if (_showBag)
			{
				DisplayBag();
				_showBag = false;
			}
		}
		case SDLK_F3:
		{
			if (_showPokemon)
			{
				DisplayPokemonSet(SwitchPokemon, nullptr); //call the pokemon diplay function, in switch mode
				_showBag = false;
			}
		}
		default:
			break;
		}
		break;
	default:
		break;
	}
}


void MainClass::GameLoop()  //Main game loop
{
	Sound::ChangeMusic("Overworld.ogg");
	//initial camera position to track movement
	double initCameraX = _cameraX;
	double initCameraY = _cameraY;
	while (_sdlSetup->GetMainEvent()->type != SDL_QUIT) //while user does not quit window
	{

		_sdlSetup->Begin();

		//draw elements in order depth

		_current->DrawBack();
		_player->GetPlayerSprite()->Draw();
		_current->DrawFront();

		//update player sprite, environment

		_player->GetPlayerSprite()->Update();
		_current->Update();

		_statusBar->Draw(_player, _current); //draw status bar

		Update(); //manage key pressed

		CheckPokemonFainted();

		_sdlSetup->End();
		if (pow(pow(initCameraX - _cameraX, 2.0) + pow(initCameraY - _cameraY, 2.0), 0.5) > 40.0) //if players has moved a certain distance
		{
			PlayerMoved();
			initCameraX = _cameraX;
			initCameraY = _cameraY;
		}
	}
}

void MainClass::CheckPokemonFainted()
{
	bool allPokemonFainted = true;
	for (PokemonGen* pokemon : _player->PokemonSet()) //if anyone pokemon has not fainted, break the loop
	{
		if (pokemon != nullptr && pokemon->Status() != Faint)
		{
			allPokemonFainted = false;
			break;
		}
	}
	if (allPokemonFainted) //if all pokemon have fainted
	{
		SDL_Rect rect = { 0,0,720,720 }; //black out screen
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &rect);
		_sdlSetup->End();
		SDL_Delay(1000);
		_cameraX = -1440; //move to pokemon center
		_cameraY = -840;
		_player->GetPlayerSprite()->GetImage()->GetCrop()->x = 0;
		_player->GetPlayerSprite()->GetImage()->GetCrop()->y = 0;
		for (PokemonGen* pokemon : _player->PokemonSet()) //revive all the players pokemon
		{
			if (pokemon != nullptr)
			{
				pokemon->Restore();
			}
		}
	}

}

void MainClass::SaveFile() const
{
	std::string fileData = "<SaveFile>";
	fileData += '\n';
	fileData += "<Position>";
	fileData += '\n';
	fileData += std::to_string(static_cast<int>(_cameraX)) + ',' + std::to_string(static_cast<int>(_cameraY));
	fileData += '\n';
	fileData += "</Position>";
	fileData += '\n';
	fileData += "<Player>";
	fileData += '\n';
	fileData += "<Name>";
	fileData += '\n';
	fileData += _player->GetName();
	fileData += '\n';
	fileData += "</Name>";
	fileData += '\n';
	fileData += "<Money>";
	fileData += '\n';
	fileData += std::to_string(_player->GetMoney());
	fileData += '\n';
	fileData += "</Money>";
	fileData += '\n';
	fileData += "<Bag>";
	fileData += '\n';
	for (int i = 0; i < _player->PlayerBag().Size(); ++i)
	{
		fileData += "<Item>";
		fileData += '\n';
		fileData += _player->PlayerBag()[i]->stored_item->ItemIndex() + ',' + std::to_string(_player->PlayerBag()[i]->quantity);
		fileData += '\n';
		fileData += "</Item>";
		fileData += '\n';
	}
	fileData += "</Bag>";
	fileData += '\n';
	fileData += "<PokemonSet>";
	fileData += '\n';
	for (auto pokemon : _player->PokemonSet())
	{
		if (pokemon != nullptr)
		{
			fileData += pokemon->ToString() + '\n';
		}
	}
	fileData += "</PokemonSet>";
	fileData += '\n';
	fileData += "</Player>";
	fileData += '\n';
	fileData += "</SaveFile>";
	std::cout << "File saved!";
	std::ofstream savefile;
	savefile.open("SaveFiles/SaveFile.xml");
	savefile << fileData;
	savefile.close();
}


