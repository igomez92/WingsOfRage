#ifndef BUTTON_H

#define BUTTON_H

#include<SFML/Graphics.hpp>

/*
 The button class can load every type of button in the game,
 given it's button type (enum) and whether or not it's selected
 by default (i.e., When the main menu starts, the "Play" button
 is automatically selected).

 One important function is the getButtonSprite(), which returns
 the sprite and can be drawn on a Window with the  "draw()" function.

 NOTE: In the CPP, The image .png's have not been made yet,
 and the file locations are tentative since they may not be correct.

*/




// if more buttons are to be added, they shouuld be added here first
enum ButtonTypeEnum
{
	MainStartButton,
	MainLoadButton,
	MainQuitButton,
	LoadSelectedFileButton,
	LoadBackButton,
	PauseResumeButton,
	GameOverRestartButton,
	GameOverMainMenuButton
};


class Button
{
public:
	// Given the type, this constructor loads from the image file
	// into a sf::Texture then into a sf::Sprite
	// for you. The select boolean is for
	// having the button be selected by default.
	Button(ButtonTypeEnum type, bool select);

	// self-explanatory
	bool isSelected();	
	void selectButton();
	void deselectButton();
	
	// intended for a sf::Window class to "draw()" the buttons on a window
	sf::Sprite getButtonSprite();

private:
	// used inside of the constructor
	void loadButton();
	
	bool selectedState;
	sf::Texture btnTexture;
	sf::Sprite btnSprite;
	std::string imageLocation;
	ButtonTypeEnum btnType
};





#endif // MENU_H