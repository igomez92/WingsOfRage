#include<SFML/Graphics.hpp>
#include"Button.h"
using namespace sf;
using namespace std;

// Refer to Button.h for notes on this class.


Button::Button(ButtonTypeEnum type, bool select)
	: btnType(type), selectedState(select)
{
	switch(btnType)
	{
	case MainStartButton:
		{
			imageLocation = "../Images/Buttons/MainStart.png";
			break;
		}
	case MainLoadButton:
		{
			imageLocation = "../Images/Buttons/MainLoad.png";
			break;
		}
	case MainQuitButton:
		{
			imageLocation = "../Images/Buttons/MainQuit.png";
			break;
		}
	case LoadSelectedFileButton:
		{
			imageLocation = "../Images/Buttons/LoadSelectFile.png";
			break;
		}
	case LoadBackButton:
		{
			imageLocation = "../Images/Buttons/LoadBack.png";
			break;
		}
	case PauseResumeButton:
		{
			imageLocation = "../Images/Buttons/PauseResume.png";
			break;
		}
	case GameOverRestartButton:
		{
			imageLocation = "../Images/Buttons/GameOverRestart.png";
			break;
		}
	case GameOverMainMenuButton:
		{
			imageLocation = "../Images/Buttons/GameOverMainMenu.png";
			break;
		}

	}
	loadButton();
}


bool Button::isSelected()
{
	return selectedState;
}

void Button::selectButton()
{
	selectedState = true;
}

void Button::deselectButton()
{
	selectedState = false;
}


void Button::loadButton()
{
	btnTexture.loadFromFile(imageLocation);
	btnSprite = Sprite(btnTexture);
}

Sprite Button::getButtonSprite()
{
	return btnSprite;
}
