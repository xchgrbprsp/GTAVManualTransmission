/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/

#include "..\..\ScriptHookV_SDK\inc\main.h"

#include "script.h"
#include "Logger.hpp"
#include "MemoryPatcher.hpp"
#include "Util.hpp"
#include "keyboard.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
	Logger logger(LOGFILE);
	// ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			scriptRegister(hInstance, ScriptMain);
			keyboardHandlerRegister(OnKeyboardMessage);
			logger.Clear();
			logger.Write("GTAVManualTransmission v4.0.4");
			logger.Write(eGameVersionToString(getGameVersion()));
			logger.Write("Script loaded");
			break;
		}
		case DLL_PROCESS_DETACH: {
			logger.Write("Init shutdown");
			bool successI = MemoryPatcher::RestoreInstructions();

			if (successI) {
				logger.Write("Shut down script successfully");
			}
			else {
				if (!successI)
					logger.Write("Shut down script with instructions not restored");
			}
			scriptUnregister(hInstance);
			keyboardHandlerUnregister(OnKeyboardMessage);
			break;
		}
	}
	return TRUE;
}
