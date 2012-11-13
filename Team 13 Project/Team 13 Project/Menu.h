#ifndef MENU_H

#define MENU_H

#include<vector>
#include"Button.h"

/*
Given the type of the menu, this class stores
the appropriate buttons into a vector.
*/

enum MenuTypeEnum 
{
	MAIN_MENU,
	LOAD_MENU,
	PLAY_MENU,
	PAUSE_MENU,
	GAMEOVER_MENU
};


class Menu
{
public:
	Menu(MenuTypeEnum);	// default constructor
	
	// deselect the selected button and select the given one
	void selectNew(Button& btn);


	// self-explanatory
	std::vector<Button> buttonList;
	
	// pointer to the currently selected Button
	Button* selected;
private:
	MenuTypeEnum type;	
};

	

#endif // MENU_H