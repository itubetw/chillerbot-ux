#ifndef GAME_CLIENT_COMPONENTS_CHILLERBOT_CHILLPW_H
#define GAME_CLIENT_COMPONENTS_CHILLERBOT_CHILLPW_H

#include <engine/client.h>
#include <engine/console.h>
#include <engine/shared/config.h>
#include <game/client/component.h>

#define MAX_PASSWORDS 1024
#define MAX_PASSWORD_LENGTH 2048
#define MAX_HOSTNAME_LENGTH 128

class CChillPw : public CComponent
{
public:
	int Sizeof() const override { return sizeof(*this); }

private:
	void OnMapLoad() override;
	void OnRender() override;
	void OnInit() override;
	void OnConsoleInit() override;

	static void ConChillpw(IConsole::IResult *pResult, void *pUserData);

	void ConStatus();
	void ConDumpHost();

	bool AuthChatAccount(int Dummy, int Offset);
	void SavePassword(const char *pServer, const char *pPassword);

	bool GotInvalidToken(const char *p, int Line, const char *pLine)
	{
		if(p)
			return false;
		char aBuf[2048];
		str_format(aBuf, sizeof(aBuf), "%s:%d '%s' invalid token", g_Config.m_ClPasswordFile, Line, pLine);
		Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "chillerbot", aBuf);
		return true;
	}

	int m_aDummy[MAX_PASSWORDS];
	char m_aaPasswords[MAX_PASSWORDS][MAX_PASSWORD_LENGTH];
	char m_aaHostnames[MAX_PASSWORDS][MAX_HOSTNAME_LENGTH];
	char m_aCurrentServerAddr[64];
	/*
		m_aCurrentServerAddrNoPort

		Cut off first occurence of ":" so only supporting ipv4
	*/
	char m_aCurrentServerAddrNoPort[64];
	int64_t m_ChatDelay[NUM_DUMMIES];
	int m_LoginOffset[NUM_DUMMIES];
	int m_NumLoadedPasswords;
};

#endif
