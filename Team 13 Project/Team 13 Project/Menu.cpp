#include"Button.h"
#include"Menu.h"
#include<vector>

// Refer to Menu.h for notes on this class



Menu::Menu(MenuTypeEnum menu)
	: type (menu)
{
	switch(menu)
	{
		case MAIN_MENU:
		{
			Button startBtn(MainStartButton, true);
			Button loadBtn(MainLoadButton, false);
			Button quitBtn(MainQuitButton, false);
			buttonList.push_back(startBtn);
			buttonList.push_back(loadBtn);
			buttonList.push_back(quitBtn);
			selected = &startBtn;
			break;
		}
		case LOAD_MENU:
		{
			Button selectFileBtn(LoadSelectedFileButton, true);
			Button backBtn(LoadBackButton, false);
			buttonList.push_back(selectFileBtn);
			buttonList.push_back(backBtn);
			selected = &selectFileBtn;
			break;
		}
		case PLAY_MENU:
		{
			// more stuff here
			// for sub-menus: attack menu, item menu, health menu
		}
		case PAUSE_MENU:
		{
			Button resumeBtn(PauseResumeButton, true);
			Button quitBtn(MainQuitButton, false);
			buttonList.push_back(resumeBtn);
			buttonList.push_back(quitBtn);
			selected = &resumeBtn;
			break;
		}
		case GAMEOVER_MENU:
		{
			Button restartBtn(GameOverRestartButton, true);
			Button mainmenuBtn(GameOverMainMenuButton, false);
			Button quitBtn(MainQuitButton, false);
			buttonList.push_back(restartBtn);
			buttonList.push_back(mainmenuBtn);
			buttonList.push_back(quitBtn);
			selected = &restartBtn;
			break;
		}
		default:	
		{
			break;
		}
	}

}



void Menu::selectNew(Button& btn)
{
	selected->deselectButton();
	selected = &btn;
	selected->selectButton();
}