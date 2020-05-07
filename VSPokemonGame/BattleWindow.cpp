#include "BattleWindow.h"
#include "SdlSetup.h"
#include "Text.h"
#include "Sound.h"

//Menu dimensions

int menu_x = 0;
int menu_y = 360;
int menu_w = 360;
int menu_h = 240;


BattleWindow::BattleWindow(Player* player, PokemonGen* pokemon1, PokemonGen* pokemon2) //Ctor for BaseBattle
{
	//initlize player, pokemon 
	_player = player;
	_pokemon1 = pokemon1;
	_pokemon2 = pokemon2;
	_opponent = nullptr;
	_battleQuit = false;

	//initlize a new SDL Setup for the battle window

	_battleSdlSetup = new SdlSetup(&_battleQuit, 360, 600);
	_battleBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleBackground.png", 0, 0, 360, 360, nullptr, nullptr, nullptr);

	//initlize pokemon sprites

	_ownPokemonSprite = new PokemonSprite(_battleSdlSetup);
	_oppPokemonSprite = new PokemonSprite(_battleSdlSetup);
	_ownPokemonSprite->Update(_pokemon1->GetImagePath(), 20, 140);
	_oppPokemonSprite->Update(_pokemon2->GetImagePath(), 190, 30);
	_pokemon1LastHp = _pokemon1->CurrentHp();
	_pokemon2LastHp = _pokemon2->CurrentHp();
	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMenuEmpty.png", menu_x, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);
	BattleStartMessage(); 
}

void BattleWindow::AttackAnimation(PokemonGen* attacker) const
{
	for (int i = 0; i < 20; ++i) //shift the attacking pokemon sprite
	{
		_battleSdlSetup->Begin();
		_menuBackground->DrawSteady();
		_battleBackground->DrawSteady();
		if (attacker == _pokemon1)
		{	
			_ownPokemonSprite->Update(_pokemon1->GetImagePath(), 20 + i * 10, 140 - i * 7); // change sprite drawing location
		}
		else
		{
			_oppPokemonSprite->Update(_pokemon2->GetImagePath(), 190 - i * 10, 30 + i * 7); // change sprite drawing location
		}
		BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2->CurrentHp());
		BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1->CurrentHp());
		_ownPokemonSprite->DrawBack();
		_oppPokemonSprite->DrawFront();
		RenderText();
		_battleSdlSetup->End();
	}
	_ownPokemonSprite->Update(_pokemon1->GetImagePath(), 20 , 140 ); // change sprite drawing location
	_oppPokemonSprite->Update(_pokemon2->GetImagePath(), 190 , 30 ); // change sprite drawing location
}



BattleWindow::BattleWindow(Player* player, PokemonGen* pokemon1, Trainer* trainer) //Ctor for TrainerBattle
{
	//initlize player, pokemon and opponent
	_player = player;
	_pokemon1 = pokemon1;
	_opponent = trainer;
	_pokemon2 = trainer->PokemonSet()[0];
	_battleQuit = false;

	//initlize a new SDL Setup for the battle window

	_battleSdlSetup = new SdlSetup(&_battleQuit, 360, 600);
	_battleBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleBackground.png", 0, 0, 360, 360, nullptr, nullptr, nullptr);
	_ownPokemonSprite = new PokemonSprite(_battleSdlSetup);
	_oppPokemonSprite = new PokemonSprite(_battleSdlSetup);
	_ownPokemonSprite->Update(_pokemon1->GetImagePath(), 20, 140);
	_oppPokemonSprite->Update(_pokemon2->GetImagePath(), 190, 30);
	_opponent->InitializeBattleSprite(_battleSdlSetup);
	_pokemon1LastHp = _pokemon1->CurrentHp();
	_pokemon2LastHp = _pokemon2->CurrentHp();
	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMenuEmpty.png", menu_x, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);
	BattleStartMessage();
}

void BattleWindow::BattleStartMessage() 
{
	//display the opponent and player, and battle message
	_battleSdlSetup->Begin();
	SetDefaultBackground();
	_menuBackground->DrawSteady();
	Sprite playerSprite{ _battleSdlSetup->GetRenderer(), "Resources/CharacterSprites/redBack1.png", 40, 160, 140, 100, nullptr, nullptr, nullptr };
	_battleBackground->DrawSteady();
	playerSprite.DrawSteady();
	if (_opponent == nullptr)
	{
		_oppPokemonSprite->DrawFront();
		_battleText = "A wild " + _pokemon2->Name() + " appeared!";
	}
	else
	{
		_opponent->DrawSprite();
		_battleText = "Trainer " + _opponent->GetName() + " would like to battle!";
	}
	RenderText();
	SDL_Delay(1000);
}


void BattleWindow::SetDefaultBackground()
{
	//remove the curretn background, and set the empty menu background
	delete _menuBackground;
	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMenuEmpty.png", menu_x, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);

}


void BattleWindow::DisplayBattleMenu(int& choice)
{
	ClearMenu();
	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMenu.png", menu_x, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);

	//push back four buttons, for the four given options

	_buttons.push_back(new Button(_battleSdlSetup, menu_x, menu_y + 20, menu_w, 150));
	_buttons.push_back(new Button(_battleSdlSetup, menu_x, menu_y + 180, menu_w / 3, 60));
	_buttons.push_back(new Button(_battleSdlSetup, menu_x + 120, menu_y + 180, menu_w / 3, 60));
	_buttons.push_back(new Button(_battleSdlSetup, menu_x + 240, menu_y + 180, menu_w / 3, 60));

	bool clicked = false;
	while (!clicked) //loop until a valid click is registered
	{
		_battleSdlSetup->Begin();

		//draw the battle elements

		_battleBackground->DrawSteady();
		_ownPokemonSprite->DrawBack();
		_oppPokemonSprite->DrawFront();
		_menuBackground->DrawSteady();
		BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1LastHp);
		BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2LastHp);

		//intialize coordinates for the mouse position and get position

		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);

		if (_battleSdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN) //if the user clicks down on the mouse
		{

			for (int i = 0; i < 4; ++i) //loop through the buttons
			{
				if (_buttons[i]->Clicked(x, y)) //if the button has been clicked
				{
					clicked = true;
					choice = i; //set the choice as the clicked button index
					_buttons[i]->ClickedAnimation(); //play the clicking animation
					SDL_Delay(50);
					break;
				}
			}
		}
		RenderText(); //draw the battle text
		_battleSdlSetup->End();
	}
}

void BattleWindow::ClearMenu()
{
	delete _menuBackground; //delete the background
	for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i) //destroy all the stored buttons
	{
		delete *i;
	}
	_buttons.clear();
}

void BattleWindow::DisplayAttackMenu(int& choice)
{
	ClearMenu();
	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMoveSelect.png", 0, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);

	//make and store the buttons for each move

	if (_pokemon1->Moves()[0] != nullptr)
	{
		_buttons.push_back(new Button(_battleSdlSetup, menu_x + 20, menu_y + 40, menu_w / 2 - 20, 60));
	}
	if (_pokemon1->Moves()[1] != nullptr)
	{
		_buttons.push_back(new Button(_battleSdlSetup, menu_x + 180, menu_y + 40, menu_w / 2 - 20, 60));
	}
	if (_pokemon1->Moves()[2] != nullptr)
	{
		_buttons.push_back(new Button(_battleSdlSetup, menu_x + 20, menu_y + 100, menu_w / 2 - 20, 60));
	}
	if (_pokemon1->Moves()[3] != nullptr)
	{
		_buttons.push_back(new Button(_battleSdlSetup, menu_x + 180, menu_y + 100, menu_w / 2 - 20, 60));
	}
	bool clicked = false;
	while (!clicked) //loop until mouse clicked
	{
		//draw the battle elements

		_battleSdlSetup->Begin();
		_battleBackground->DrawSteady();
		_ownPokemonSprite->DrawBack();
		_oppPokemonSprite->DrawFront();
		_menuBackground->DrawSteady();
		BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1LastHp);
		BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2LastHp);

		//for each of the buttons draw the button, passing the move which the button represents

		int moveIndex = 0;
		for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i)
		{
			if (_pokemon1->Moves()[moveIndex] != nullptr)
			{
				(*i)->Draw(_pokemon1->Moves()[moveIndex], _pokemon1->Moves().GetPp(moveIndex));
			}
			++moveIndex;
		}

		//Get the mouse location

		int x = 0;
		int y = 0;

		SDL_GetMouseState(&x, &y);


		if (_battleSdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			int buttonIndex = 0;

			//determine which button was clicked 

			for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i)
			{
				if ((*i)->Clicked(x, y))
				{
					if (_pokemon1->Moves().GetPp(buttonIndex) != 0) //register a valid click only if the move has 1 or more PP left
					{
						clicked = true;
						choice = buttonIndex; //set the move 
						(*i)->ClickedAnimation();
						SDL_Delay(100);
						break;
					}
				}
				++buttonIndex;
			}
		}
		RenderText();
		_battleSdlSetup->End();
	}
}

void BattleWindow::DisplayPokemonSet(int& choice)
{
	ClearMenu();
	std::vector<SDL_Rect*> buttonRects; //rects for button dimensions 
	std::vector<Sprite*> icons; //pokemon icons

	//nested loops for drawing grid of icons

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			buttonRects.push_back(new SDL_Rect({ menu_x + menu_w / 2 * i, menu_y + menu_h / 3 * j,menu_w / 2,menu_h / 3 })); //make grid with relative dimensions (2 x 3 buttons)
			if (_player->PokemonSet()[3 * i + j] != nullptr) //if pokemon does not exist, donot draw button
			{
				_buttons.push_back(new Button{ _battleSdlSetup,  menu_x + menu_w / 2 * i, menu_y + (menu_h / 3) * j, menu_w / 2,menu_h / 3 });
				const std::string filepath = "Resources/PokemonSprites/icon/" + _player->PokemonSet()[3 * i + j]->GetImagePath() + ".png"; //load and store the icon
				icons.push_back(new Sprite{ _battleSdlSetup->GetRenderer(), filepath,buttonRects[3 * i + j]->x + 5 , buttonRects[3 * i + j]->y + 10, 48,48, nullptr, nullptr, nullptr });
			}
		}
	}
	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMenuEmpty.png", menu_x, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);
	bool clicked = false;
	while (!clicked) //while the user does not make a valid click
	{
		_battleSdlSetup->Begin();
		_battleBackground->DrawSteady();
		_ownPokemonSprite->DrawBack();
		_oppPokemonSprite->DrawFront();
		_menuBackground->DrawSteady();
		BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1LastHp);
		BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2LastHp);

		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);
		

		int pokemonIndex = 0;
		for (std::vector<SDL_Rect*>::iterator i = buttonRects.begin(); i != buttonRects.end(); ++i) //for each button draw the icon, button background and the pokemon'status bar
		{
			if (_player->PokemonSet()[pokemonIndex] != nullptr)
			{
				if (_player->PokemonSet()[pokemonIndex]->Status() == Faint)
				{
					SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 255, 0, 0, 0);
				}
				else
				{
					SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 0, 0, 255, 0);
				}
				SDL_RenderFillRect(_battleSdlSetup->GetRenderer(), *i);
				icons[pokemonIndex]->DrawSteady();
				BattleStatusBar(buttonRects[pokemonIndex]->x + 50, buttonRects[pokemonIndex]->y + 40, buttonRects[pokemonIndex]->w - 60, 7, _player->PokemonSet()[pokemonIndex], _player->PokemonSet()[pokemonIndex]->CurrentHp());
			}
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 255, 255, 255, 0);
			SDL_RenderDrawRect(_battleSdlSetup->GetRenderer(), *i); //draw outline rect
			++pokemonIndex;
		}
		if (_battleSdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN) //if the user clicks, get the selected button index
		{
			int buttonIndex = 0;
			for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i)
			{
				if ((*i)->Clicked(x, y))
				{
					if (_player->PokemonSet()[buttonIndex]->Status() != Faint) //registr a valid click only if selected pokemon has not fainted
					{
						clicked = true;
						choice = buttonIndex;
						(*i)->ClickedAnimation();
						SDL_Delay(100);
						break;
					}
				}
				++buttonIndex;
			}
		}
		RenderText();
		SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 0, 0, 0, 0);
		_battleSdlSetup->End();
	}

	//clear the icons and button rects

	for (Sprite* icon : icons)
	{
		delete icon;
	}
	for (struct SDL_Rect* rect : buttonRects)
	{
		delete rect;
	}
}

void BattleWindow::DisplayBag(int& choice)
{
	ClearMenu();
	std::vector<SDL_Rect*> buttonRects; //button outline and size rect vector
	std::vector<Sprite*> icons; //item icons vector
	std::vector<Text*> itemName; //item name vector
	std::vector<Text*> quantity; //item quantity vector

	_menuBackground = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/BattleMenuEmpty.png", menu_x, menu_y, menu_w, menu_h, nullptr, nullptr, nullptr);

	//load buttons in a 3 x 4 grid

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			const int buttonX = menu_x + (menu_w / 3) * i;
			const int buttonY = menu_y + (menu_h / 4) * j;
			const int buttonW = menu_w / 3;
			const int buttonH = menu_h / 4;

			buttonRects.push_back(new SDL_Rect({ buttonX, buttonY, buttonW, buttonH}));
			if (4 * i + j < _player->PlayerBag().Size()) //if an item exists at the index
			{
				//load and store the items icon, name and quantity into the vectors

				_buttons.push_back(new Button{ _battleSdlSetup,  buttonX, buttonY, buttonW, buttonH});
				std::string fileName = "Resources/items/";
				fileName += _player->PlayerBag()[4 * i + j]->stored_item->Name() + ".png";
				icons.push_back(new Sprite{ _battleSdlSetup->GetRenderer(), fileName, buttonX, buttonY + 4, 32,32, nullptr, nullptr, nullptr });
				itemName.push_back(new Text{ _battleSdlSetup, buttonX, buttonY + 35, 10 });
				quantity.push_back(new Text{ _battleSdlSetup, buttonX + 35, buttonY + 10, 10 });
			}
		}
	}
	bool clicked = false;
	while (!clicked)
	{
		_battleSdlSetup->Begin();
		_battleBackground->DrawSteady();
		_ownPokemonSprite->DrawBack();
		_oppPokemonSprite->DrawFront();
		_menuBackground->DrawSteady();
		BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1LastHp);
		BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2LastHp);

		//get mouse location

		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y);

		//draw each item along with its text

		int itemIndex = 0;
		for (std::vector<SDL_Rect*>::iterator i = buttonRects.begin(); i != buttonRects.end(); ++i)
		{
			if (itemIndex < _player->PlayerBag().Size())
			{
				SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 255, 255, 255, 0);
				SDL_RenderFillRect(_battleSdlSetup->GetRenderer(), *i);
				icons[itemIndex]->DrawSteady();
				itemName[itemIndex]->Update(_player->PlayerBag()[itemIndex]->stored_item->Name());
				quantity[itemIndex]->Update(std::to_string(_player->PlayerBag()[itemIndex]->quantity));
			}
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 0, 0, 0, 0);
			SDL_RenderDrawRect(_battleSdlSetup->GetRenderer(), *i);
			++itemIndex;
		}
		if (_battleSdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN) //determine which button was clicked,
		{
			int buttonIndex = 0;
			for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i)
			{
				if ((*i)->Clicked(x, y))
				{
					clicked = true;
					choice = buttonIndex;
					(*i)->ClickedAnimation();
					SDL_Delay(100);
					break;
				}
				++buttonIndex;
			}
		}
		RenderText();
		SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 0, 0, 0, 0);
		_battleSdlSetup->End();
	}
	//clear icons, button rects and text

	for (Sprite* icon : icons)
	{
		delete icon;
	}
	for (struct SDL_Rect* rect : buttonRects)
	{
		delete rect;
	}
	for (Text* name : itemName)
	{
		delete name;
	}
	for (Text* q : quantity)
	{
		delete q;
	}
}


BattleWindow::~BattleWindow()
{
	for (std::vector<Button*>::iterator i = _buttons.begin(); i != _buttons.end(); ++i)
	{
		delete *i;
	}
	_buttons.clear();
	delete _menuBackground;
	delete _battleBackground;
	delete _ownPokemonSprite;
	delete _oppPokemonSprite;
	delete _battleSdlSetup;
	if (_opponent != nullptr)
	{
		_opponent->DeleteBattleSprite();
	}
}


void BattleWindow::UpdateStatus(PokemonGen* pokemon1, PokemonGen* pokemon2) //update the status bar, looping each time the pokemons' HP changes
{
	//draw battle elements

	_battleSdlSetup->Begin();
	SetDefaultBackground();
	_menuBackground->DrawSteady();
	_battleBackground->DrawSteady();
	_ownPokemonSprite->DrawBack();
	_oppPokemonSprite->DrawFront();

	//if any of theb pokemon's HP has changes, draw the status bars in a loop, changing the displayed HP by one each time for smooth animation

	//status bar for pokemon 1 (own) 
	
	if (pokemon1->CurrentHp() == _pokemon1LastHp) //if hp has not changed, draw the bar once
	{
		BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1->CurrentHp());
	}
	else
	{
		//determine if the HP has decreased or increased
		int diff;
		if (pokemon1->CurrentHp() < _pokemon1LastHp)
		{
			diff = -1;
		}
		else
		{
			diff = 1;
			Sound::PlaySound("Heal");
		}
		int hp = _pokemon1LastHp;
		bool damageFlash = false;
		while (hp != _pokemon1->CurrentHp()) 	//loop until the displayed HP is equal to the actual HP
		{
			//draw all the battle elements
			_battleSdlSetup->Begin();
			_menuBackground->DrawSteady();
			_battleBackground->DrawSteady();
			if (!damageFlash && diff == -1)
			{
				_ownPokemonSprite->DrawBack();
			}
			damageFlash = !damageFlash;
			_oppPokemonSprite->DrawFront();
			BattleStatusBar(200, 215, 140, 7, _pokemon1, hp);
			BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2->CurrentHp());
			RenderText();
			_battleSdlSetup->End();
			hp += diff;
		}
	}

	//status bar for pokemon 2 (opp)

	if (pokemon2->CurrentHp() == _pokemon2LastHp)
	{
		BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2->CurrentHp());
	}
	else
	{
		int diff;
		if (pokemon2->CurrentHp() < _pokemon2LastHp)
		{
			diff = -1;
		}
		else
		{
			diff = 1;
		}
		int hp = _pokemon2LastHp;
		bool damageFlash = false;
		while (hp != _pokemon2->CurrentHp())
		{
			_battleSdlSetup->Begin();
			_menuBackground->DrawSteady();
			_battleBackground->DrawSteady();
			_ownPokemonSprite->DrawBack();
			if (!damageFlash && diff == -1)
			{
				_oppPokemonSprite->DrawFront();
			}
			damageFlash = !damageFlash;
			BattleStatusBar(20, 90, 140, 7, _pokemon2, hp);
			BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1->CurrentHp());
			RenderText();
			_battleSdlSetup->End();
			hp += diff;
		}
	}
	//update the pokemon's sprite if any pokemon has been switched
	Update(pokemon1, pokemon2);
	RenderText();
	_battleSdlSetup->End();
}

void BattleWindow::operator<<(const std::string text) //overloaded << to display text on battle screen :-)
{
	UpdateText(text);
}


void BattleWindow::FaintingAnimation(PokemonGen* pokemon) const 
{
	PokemonGen* other; //determine the non-fainted pokemon
	if (pokemon == _pokemon1)
	{
		other = _pokemon2;
	}
	else
	{
		other = _pokemon1;
	}

	for (int i = 0; i < 200; ++i) //shift the fainted pokemon's sprite out of view smoothly
	{
		_battleSdlSetup->Begin();
		_menuBackground->DrawSteady();
		_battleBackground->DrawSteady();
		if (other == _pokemon2)
		{
			BattleStatusBar(20, 90, 140, 7, other, other->CurrentHp());
			_ownPokemonSprite->Update(_pokemon1->GetImagePath(), 20 - i * 10, 140); // change sprite drawing location
		}
		else
		{
			BattleStatusBar(200, 215, 140, 7, other, other->CurrentHp());
			_oppPokemonSprite->Update(_pokemon2->GetImagePath(), 190 + i * 10, 30);
		}
		_ownPokemonSprite->DrawBack();
		_oppPokemonSprite->DrawFront();
		RenderText();
		_battleSdlSetup->End();
	}
}

void BattleWindow::BattleStart() const
{
	Sprite* playerBack = new Sprite(_battleSdlSetup->GetRenderer(), "Resources/CharacterSprites/redBack1.png", 40, 160,
		140, 100, nullptr, nullptr, nullptr);
	if (_opponent == nullptr)
	{
		Sound::PlayCry(_pokemon2->GetImagePath());
	}
	while (_battleSdlSetup->GetMainEvent()->key.keysym.sym != SDLK_z)
	{
		_battleSdlSetup->Begin();
		_menuBackground->DrawSteady();
		_battleBackground->DrawSteady();
		if (_opponent == nullptr)
		{
			_oppPokemonSprite->DrawFront();
		}
		else
		{
			_opponent->DrawSprite();
		}
		playerBack->DrawSteady();
		//BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2->CurrentHp());
		RenderText();
		_battleSdlSetup->End();
	}
	Sound::PlaySound("PokeballThrow");
	for (int i = 2; i < 9; ++i)
	{
		delete playerBack;
		const std::string fileName = "Resources/CharacterSprites/redBack" + std::to_string(i) + ".png";
		playerBack = new Sprite(_battleSdlSetup->GetRenderer(), fileName, 40, 160, 140, 100, nullptr, nullptr, nullptr);
		_battleSdlSetup->Begin();
		_menuBackground->DrawSteady();
		_battleBackground->DrawSteady();
		if (_opponent == nullptr)
		{
			_oppPokemonSprite->DrawFront();
		}
		else
		{
			_opponent->DrawSprite();
		}
		playerBack->DrawSteady();
		//BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2->CurrentHp());
		RenderText();
		_battleSdlSetup->End();
		SDL_Delay(100);
	}
	delete playerBack;
	Sound::PlaySound("PokeballOpen");
	Sound::PlayCry(_pokemon1->GetImagePath());
	if (_opponent != nullptr)
	{
		Sound::PlayCry(_pokemon2->GetImagePath());
	}
}


void BattleWindow::UpdateText(const std::string text) //display battle text with delay
{
	_battleSdlSetup->Begin();
	SetDefaultBackground();
	_menuBackground->DrawSteady();
	_battleBackground->DrawSteady();
	_ownPokemonSprite->DrawBack();
	_oppPokemonSprite->DrawFront();
	BattleStatusBar(200, 215, 140, 7, _pokemon1, _pokemon1LastHp);
	BattleStatusBar(20, 90, 140, 7, _pokemon2, _pokemon2LastHp);
	_battleText = text;
	RenderText();
	SDL_Delay(1000);
}


void BattleWindow::RenderText() const
{
	Text battleText{ _battleSdlSetup, 20, 300, 10,}; //create a nw text object and display the battle text
	battleText.Update(_battleText);
	_battleSdlSetup->End();
}


void BattleWindow::BattleStatusBar(int x, int y, int w, int h, PokemonGen* pokemon, const int passed_hp) const
{
	SDL_Color old = {};
	SDL_GetRenderDrawColor(_battleSdlSetup->GetRenderer(), &old.r, &old.g, &old.b, &old.a);
	const SDL_Color bgColor = { 255, 255, 255, 0 };
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(_battleSdlSetup->GetRenderer(), &bgrect);
	const double percent = static_cast<double>(passed_hp) / static_cast<double>(pokemon->MaxHp());
	const int pw = static_cast<int>(static_cast<float>(w) * percent);
	SDL_Color fgColor;
	if (percent > 0.5)
	{
		fgColor = { 0, 255, 0, 0 };
	}
	else if (percent > 0.25)
	{
		fgColor = { 255, 231, 71, 0 };
	}
	else
	{
		fgColor = { 255, 0, 0, 0 };
	}
	SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), fgColor.r, fgColor.g, fgColor.b, fgColor.a);
	const int px = x;
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(_battleSdlSetup->GetRenderer(), &fgrect);
	SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 0, 0, 0, 0);
	SDL_RenderDrawRect(_battleSdlSetup->GetRenderer(), &bgrect);
	Text hp{ _battleSdlSetup, x - 3, y + 5 , 10 };
	Text name{ _battleSdlSetup,x, y - 25, 10 };
	Text level{ _battleSdlSetup, x + w - 50, y - 20 ,10 };
	if (pokemon->Status() != NoEffect)
	{
		Text status{ _battleSdlSetup,x + 103, y + 6,15 };
		SDL_Rect statusRect = { x + 100, y + 8, 45, 15 };
		switch (pokemon->Status())
		{
		case Paralysis:
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 255, 200, 0, bgColor.a);
			break;
		case Poisoning: 
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 165, 0, 255, bgColor.a);
			break;
		case Burn:
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 255, 0, 0, bgColor.a);
			break;
		case Sleep: 
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 165, 165, 165, bgColor.a);
			break;
		case Freeze:
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 255, 225, 105, bgColor.a);
			break;
		case Faint: 
			SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), 180, 0, 0, bgColor.a);
			break;
		default:;
		}
		SDL_RenderFillRect(_battleSdlSetup->GetRenderer(), &statusRect);
		status.Update(to_string(pokemon->Status()));
	}
	hp.Update(std::to_string(passed_hp) + '/' + std::to_string(pokemon->MaxHp()));
	name.Update(pokemon->Name());
	level.Update("Lv. " + std::to_string(pokemon->Level()));
	SDL_SetRenderDrawColor(_battleSdlSetup->GetRenderer(), old.r, old.g, old.b, old.a);
}


void BattleWindow::Update(PokemonGen* pokemon1, PokemonGen* pokemon2)
{
	//if the battle pokemon have change, update their sprotes accordingly
	if (pokemon1 != _pokemon1)
	{
		_pokemon1 = pokemon1;
		_ownPokemonSprite->Update(_pokemon1->GetImagePath(), 20, 140);
		Sound::PlaySound("PokeballOpen");
		Sound::PlayCry(_pokemon1->GetImagePath());
	}
	if (pokemon2 != _pokemon2)
	{
		_pokemon2 = pokemon2;
		_oppPokemonSprite->Update(_pokemon2->GetImagePath(), 190, 30);
		Sound::PlaySound("PokeballOpen");
		Sound::PlayCry(_pokemon2->GetImagePath());
	}
	//set Pokemon last HPs for status bar animation
	_pokemon1LastHp = _pokemon1->CurrentHp();
	_pokemon2LastHp = _pokemon2->CurrentHp();
}

