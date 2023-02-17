#include <coreinit/debug.h>
#include <whb/proc.h>
#include <mocha/mocha.h>
#include <sysapp/title.h>
#include <sysapp/launch.h>

int main() {
	WHBProcInit();

	if (WHBProcIsRunning()) {
		if (Mocha_InitLibrary() == MOCHA_RESULT_SUCCESS) {
			if (
				SYSCheckTitleExists(0x000500301001300A) || // * JPN
				SYSCheckTitleExists(0x000500301001310A) || // * USA
				SYSCheckTitleExists(0x000500301001320A)    // * EUR
			) {
				_SYSSwitchTo(SYSAPP_PFID_TVII);
			} else {
				OSFatal("Failed to find TVii");
			}

			Mocha_DeInitLibrary();

		} else {
			SYSLaunchMenu();
		}

		while(WHBProcIsRunning()) {}
	}

	return 0;
}
