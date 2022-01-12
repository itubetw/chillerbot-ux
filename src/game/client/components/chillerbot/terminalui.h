
#ifndef GAME_CLIENT_COMPONENTS_CHILLERBOT_TERMINALUI_H
#define GAME_CLIENT_COMPONENTS_CHILLERBOT_TERMINALUI_H

#include <game/client/component.h>

#if defined(CONF_CURSES_CLIENT)
#include "terminalui_keys.h" /* undefines conflicting ncurses key codes */
#include <ncurses.h>
#include <unistd.h>
#endif

extern CGameClient *g_pClient;

class CTerminalUI : public CComponent
{
#if defined(CONF_CURSES_CLIENT)
	enum
	{
		KEY_HISTORY_LEN = 20
	};

	void DrawBorders(WINDOW *screen, int x, int y, int w, int h);
	void DrawBorders(WINDOW *screen);
	void RenderScoreboard(int Team, WINDOW *pWin);
	int m_aLastPressedKey[KEY_HISTORY_LEN];
	bool KeyInHistory(int Key, int Ticks = KEY_HISTORY_LEN)
	{
		for(int i = 0; i < KEY_HISTORY_LEN && i < Ticks; i++)
			if(Key == m_aLastPressedKey[i])
				return true;
		return false;
	};
	void KeyHistoryToStr(char *pBuf, int Size)
	{
		str_copy(pBuf, "", Size);
		for(int i = 0; i < KEY_HISTORY_LEN; i++)
		{
			char aBuf[8];
			str_format(aBuf, sizeof(aBuf), " %d/%c", m_aLastPressedKey[i], m_aLastPressedKey[i]);
			str_append(pBuf, aBuf, Size);
		}
	};
	void TrackKey(int Key)
	{
		for(int i = 0; i < KEY_HISTORY_LEN - 1; i++)
		{
			m_aLastPressedKey[i] = m_aLastPressedKey[i + 1];
		}
		m_aLastPressedKey[KEY_HISTORY_LEN - 1] = Key;
	};

	enum
	{
		INPUT_OFF = 0,
		INPUT_NORMAL,
		INPUT_LOCAL_CONSOLE,
		INPUT_REMOTE_CONSOLE,
		INPUT_CHAT,
		INPUT_CHAT_TEAM,

		NC_INFO_SIZE = 3,
	};
	const char *GetInputMode()
	{
		switch(m_InputMode)
		{
		case INPUT_OFF:
			return "OFF";
		case INPUT_NORMAL:
			return "NORMAL MODE";
		case INPUT_LOCAL_CONSOLE:
			return "LOCAL CONSOLE";
		case INPUT_REMOTE_CONSOLE:
			return "REMOTE CONSOLE";
		case INPUT_CHAT:
			return "CHAT";
		case INPUT_CHAT_TEAM:
			return "TEAM CHAT";
		default:
			return "INVALID";
		}
	};

	virtual void OnInit();
	virtual void OnRender();
	virtual void OnShutdown();
	bool RconAuthed() { return false; } // TODO:
	int GetInput();
	void DrawAllBorders();
	void LogDraw();
	void InfoDraw();
	void InputDraw();
	int CursesTick();
	int AimX;
	int AimY;
	bool m_ScoreboardActive;
	int m_InputMode;

public:
	int OnKeyPress(int Key, WINDOW *pWin);
#endif
};

#endif