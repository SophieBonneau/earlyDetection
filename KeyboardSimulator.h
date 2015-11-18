#ifndef __KEYBOARDSIMULATOR_H__
#define __KEYBOARDSIMULATOR_H__

#include <windows.h>
#include <stdio.h>

using namespace std;

//enum Command	{Chudan, Guard, Hadouken, LKick, LPunch, MetsuHadou, RKick, RPunch, ShinkuHadou, Shoryuken};
enum Command {Hadouken,Jump,MPunch,Shoryuken,Squat};

class KeyboardSimulator{
private:
	void KeyAction(WORD VirtualKey, BOOL bKeepPressing, DWORD extkey = 0)
	{
		INPUT input[1];
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VirtualKey;
		input[0].ki.wScan = MapVirtualKey(input[0].ki.wVk, 0);
		input[0].ki.dwFlags = extkey;
		::SendInput(1, input, sizeof(INPUT));
		if (!bKeepPressing)
		{
			input[0].ki.dwFlags = extkey | KEYEVENTF_KEYUP;
			::SendInput(1, input, sizeof(INPUT));
		}
	}

public:
	int command;
	bool print_flg;


	KeyboardSimulator() {
		print_flg = false; 
	}

	void TestCommand()
	{
		KeyAction('A', TRUE);
//		Sleep(50);
		KeyAction('A', FALSE);	
		KeyAction('B', TRUE);
//		Sleep(50);
		KeyAction('B', FALSE);
		KeyAction('C', TRUE);
//		Sleep(50);
		KeyAction('C', FALSE);
		KeyAction('D', TRUE);
//		Sleep(50);
		KeyAction('D', FALSE);
	}

	void SetSyoryukenP1() 
	{
		KeyAction(VK_RIGHT, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(50);
		KeyAction(VK_RIGHT, FALSE, KEYEVENTF_EXTENDEDKEY);
		KeyAction(VK_DOWN, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(50);
		KeyAction(VK_DOWN, FALSE, KEYEVENTF_EXTENDEDKEY);
		KeyAction(VK_RIGHT, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(50);
		KeyAction(VK_RIGHT, FALSE, KEYEVENTF_EXTENDEDKEY);
		KeyAction('A', TRUE);
		Sleep(50);
		KeyAction('A', FALSE);
		Sleep(2000);
	}

	void SetSyoryukenP2() 
	{
		KeyAction('J', TRUE);
		Sleep(50);
		KeyAction('J', FALSE);
		KeyAction('M', TRUE);
		Sleep(50);
		KeyAction('J', TRUE);
		Sleep(50);
		KeyAction('M', FALSE);
		KeyAction('J', FALSE);
		KeyAction('4', TRUE);
		Sleep(50);
		KeyAction('4', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	void SetHadoukenP1() 
	{
		KeyAction(VK_DOWN, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(50);
		KeyAction(VK_RIGHT, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(50);
		KeyAction(VK_DOWN, FALSE, KEYEVENTF_EXTENDEDKEY);
		Sleep(50);
		KeyAction(VK_RIGHT, FALSE, KEYEVENTF_EXTENDEDKEY);
		KeyAction('D', TRUE);
		Sleep(50);
		KeyAction('D', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	void SetHadoukenP2() 
	{
		KeyAction('M', TRUE);
		Sleep(50);
		KeyAction('J', TRUE);
		Sleep(50);
		KeyAction('M', FALSE);
		Sleep(50);
		KeyAction('J', FALSE);
		KeyAction('4', TRUE);
		Sleep(50);
		KeyAction('4', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);

	}

	// 1P滅・波動拳
	void SetMetsuP1() 
	{
		KeyAction('Z', TRUE);
		Sleep(20);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction('Z', FALSE);
		Sleep(20);
		KeyAction('S', FALSE);
		Sleep(20);
		KeyAction('Z', TRUE);
		Sleep(20);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction('Z', FALSE);
		Sleep(20);
		KeyAction('S', FALSE);
		KeyAction('X', TRUE);
		Sleep(20);
		KeyAction('X', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P滅・波動拳
	void SetMetsuP2()
	{
		KeyAction('M', TRUE);
		Sleep(20);
		KeyAction('J', TRUE);
		Sleep(20);
		KeyAction('M', FALSE);
		Sleep(20);
		KeyAction('J', FALSE);
		Sleep(20);
		KeyAction('M', TRUE);
		Sleep(20);
		KeyAction('J', TRUE);
		Sleep(20);
		KeyAction('M', FALSE);
		Sleep(20);
		KeyAction('J', FALSE);
		KeyAction('7', TRUE);
		Sleep(20);
		KeyAction('7', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P弱パンチ
	void SetLPunchP1()
	{
		//KeyAction('D', TRUE);
		//Sleep(20);
		//KeyAction('D', FALSE);
		KeyAction('A', TRUE);
		Sleep(20);
		KeyAction('A', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P弱パンチ
	void SetLPunchP2()
	{
		KeyAction('4', TRUE);
		Sleep(20);
		KeyAction('4', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P弱キック
	void SetLKickP1()
	{
		//KeyAction('E', TRUE);
		//Sleep(20);
		//KeyAction('E', FALSE);
		KeyAction('Z', TRUE);
		Sleep(20);
		KeyAction('Z', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P弱キック
	void SetLKickP2()
	{
		KeyAction('1', TRUE);
		Sleep(20);
		KeyAction('1', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P中パンチ
	void SetMPunchP1()
	{
		//KeyAction('F', TRUE);
		//Sleep(20);
		//KeyAction('F', FALSE);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction('S', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P中パンチ
	void SetMPunchP2()
	{
		KeyAction('5', TRUE);
		Sleep(20);
		KeyAction('5', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P中キック
	void SetMKickP1()
	{
		KeyAction('R', TRUE);
		Sleep(20);
		KeyAction('R', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P中キック
	void SetMKickP2()
	{
		KeyAction('2', TRUE);
		Sleep(20);
		KeyAction('2', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P強パンチ
	void SetHPunchP1()
	{
		KeyAction('D', TRUE);
		Sleep(20);
		KeyAction('D', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P強パンチ
	void SetHPunchP2()
	{
		KeyAction('8', TRUE);
		Sleep(20);
		KeyAction('8', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 1P強キック
	void SetHKickP1()
	{
		//KeyAction('G', TRUE);
		//Sleep(20);
		//KeyAction('G', FALSE);
		KeyAction('C', TRUE);
		Sleep(20);
		KeyAction('C', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P強キック
	void SetHKickP2()
	{
		KeyAction('6', TRUE);
		Sleep(20);
		KeyAction('6', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}	

	// 1P真空波動拳
	void SetShinkuHadouP1()
	{
		KeyAction('Z', TRUE);
		Sleep(20);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction('Z', FALSE);
		Sleep(20);
		KeyAction('S', FALSE);
		Sleep(20);
		KeyAction('Z', TRUE);
		Sleep(20);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction('Z', FALSE);
		Sleep(20);
		KeyAction('S', FALSE);
		KeyAction('D', TRUE);
		Sleep(20);
		KeyAction('D', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(3000);
	}

	// 2P真空波動拳
	void SetShinkuHadouP2()
	{
		KeyAction('M', TRUE);
		Sleep(20);
		KeyAction('J', TRUE);
		Sleep(20);
		KeyAction('M', FALSE);
		Sleep(20);
		KeyAction('J', FALSE);
		Sleep(20);
		KeyAction('M', TRUE);
		Sleep(20);
		KeyAction('J', TRUE);
		Sleep(20);
		KeyAction('M', FALSE);
		Sleep(20);
		KeyAction('J', FALSE);
		KeyAction('4', TRUE);
		Sleep(20);
		KeyAction('4', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(3000);
	}

	//void SetShinryukenP2() 
	//{
	//	KeyAction('M', TRUE);
	//	Sleep(20);
	//	KeyAction('J', TRUE);
	//	Sleep(20);
	//	KeyAction('M', FALSE);
	//	Sleep(20);
	//	KeyAction('J', FALSE);
	//	Sleep(20);
	//	KeyAction('M', TRUE);
	//	Sleep(20);
	//	KeyAction('J', TRUE);
	//	Sleep(20);
	//	KeyAction('M', FALSE);
	//	Sleep(20);
	//	KeyAction('J', FALSE);
	//	KeyAction('7', TRUE);
	//	Sleep(20);
	//	KeyAction('7', FALSE);


	//}

	// 1Pガード
	void SetGuardP1() 
	{
		KeyAction(VK_LEFT, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(1000);
		KeyAction(VK_LEFT, FALSE, KEYEVENTF_EXTENDEDKEY);
		//KeyAction('A', TRUE);
		//Sleep(50);
		//KeyAction('A', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(1200);
	}

	// 2Pガード
	void SetGuardP2()
	{
		KeyAction('K', TRUE);
		Sleep(50);
		KeyAction('K', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(1000);
	}

	// 1P中段攻撃(リュウ・鎖骨割り)
	void SetChudanP1()
	{
		KeyAction(VK_RIGHT, TRUE, KEYEVENTF_EXTENDEDKEY);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction(VK_RIGHT, FALSE, KEYEVENTF_EXTENDEDKEY);
		KeyAction('S', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	// 2P中段攻撃(リュウ・鎖骨割り)
	void SetChudanP2()
	{
		KeyAction('J', TRUE);
		KeyAction('5', TRUE);
		Sleep(20);
		KeyAction('J', FALSE);
		KeyAction('5', FALSE);
		// ユーザ動作が終わるまで時間がかかるので、それまで停止
		Sleep(2000);
	}

	void SetJumpP1()
	{
		KeyAction(VK_UP, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(20);
		KeyAction(VK_UP, FALSE, KEYEVENTF_EXTENDEDKEY);
		Sleep(1000);
	}

	void SetSquatP1()
	{
		KeyAction(VK_DOWN, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(500);
		KeyAction(VK_DOWN, FALSE, KEYEVENTF_EXTENDEDKEY);
		Sleep(1700);
	}

};

/********** 1P側のコマンド呼び出し *** Class to call 1 player's command *******/
class CallCommand{

private:
    unsigned int thID;
    HANDLE hTh;
	int new_command_flag;
public:
	KeyboardSimulator *ks;

	//スレッド用関数
	static unsigned __stdcall mythread(void *lpx)
	{
		KeyboardSimulator *ks = (KeyboardSimulator *)lpx;
		KeyboardSimulator *ks2 = (KeyboardSimulator *)lpx;

		switch(ks->command){
			case Chudan:
				//ks->print_flg = true;
				cout << "1P_中段攻撃! Chudan!" << endl;
				ks->SetChudanP1();
				break;

			case Guard:
				//ks->print_flg = true;
				cout << "1P_ガード!" << endl;
				ks->SetGuardP1();
				break;

			case Hadouken:
				//ks->print_flg = true;
				cout << "1P_波動拳! Hadouken!" << endl;
				ks->SetHadoukenP1();
				break;

			case Jump:
				//ks->print_flg = true;
				cout << "1P_Jump!" << endl;
				ks->SetJumpP1();
				break;

			/*case LKick:
				//ks->print_flg = true;
				cout << "1P_左キック!" << endl;
				ks->SetLKickP1();
				break;
			
			case MetsuHadou:
				//ks->print_flg = true;
				//cout << "1P_MetsuHadou!" << endl;
				//ks->SetMetsuP1();
				cout << "1P_波動拳!" << endl;
				ks->SetHadoukenP1();
				
				break;
			case RKick:
				cout << "1P_右キック!" << endl;
				//ks->SetMKickP1();
				//ks->print_flg = true;
				ks->SetHKickP1();
				break;*/

			case LPunch:
				cout << "1P_左パンチ!" << endl;
				ks->SetLPunchP1();
				//ks->print_flg = true;
				break;

			case MPunch:
				//ks->print_flg = true;
				cout << "1P_右パンチ!" << endl;
				ks->SetMPunchP1();
				break;

			case HPunch:
				cout << "1P_Big 左パンチ!" << endl;
				ks->SetHPunchP1();
				//ks->print_flg = true;
				break;

			/*case ShinkuHadou:
				//ks->print_flg = true;
				//cout << "1P_ShinkuHadou!" << endl;
				//ks->SetShinkuHadouP1();
				cout << "1P_波動拳!" << endl;
				ks->SetHadoukenP1();
				break;*/

			case Shoryuken:
				//ks->print_flg = true;
				cout << "1P_昇竜拳! Shoryuken!" << endl;
				ks->SetSyoryukenP1();
				break;

			case Squat:
				//ks->print_fflg = true
				cout << "1P_Squat!" << endl;
				ks->SetSquatP1();
				break;
		}
		//Sleep(1500);
		return 0;
	}

	

	void call_thread()
	{
		DWORD dwExCode;
		if (hTh != NULL){
			GetExitCodeThread(hTh, &dwExCode); //if the specified thread has not terminated and the function succeeds, the status returned is STILL_ACTIVE
			
			if (dwExCode == STILL_ACTIVE) {
//				printf("スレッド稼働中\n");
			} else {	//Movement detected
				hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, (void *)ks, 0, &thID);
				if (hTh == 0) {
					printf("スレッド作成失敗\n");
					return;
				}
			}
		}
	}

public:
	CallCommand()
	{
		
		hTh = (HANDLE)1;
		new_command_flag = 0;
		ks = new KeyboardSimulator();

	}

	void SendCommand(int _command)
	{
		if (_command < 0){
			return;
		} else {
			ks->command = _command;
			call_thread();
		}
	}

};

/********** 2P側のコマンド呼び出し **********/
/*class CallCommand_2{

private:
    unsigned int thID;
    HANDLE hTh;
	int new_command_flag;
	KeyboardSimulator *ks;
	bool write_flg;

	//スレッド用関数
	static unsigned __stdcall mythread(void *lpx)
	{
		KeyboardSimulator *ks = (KeyboardSimulator *)lpx;


		switch(ks->command){
			case Chudan:
				cout << "2P_中段攻撃!" << endl;
				ks->SetChudanP2();
				break;
			case Guard:
				cout << "2P_ガード！" << endl;
				ks->SetGuardP2();
				break;
			case Hadouken:
				cout << "2P_波動拳!" << endl;
				ks->SetHadoukenP2();
				break;
			case LKick:
				cout << "2P_左キック!" << endl;
				ks->SetLKickP2();
				break;
			case LPunch:
				cout << "2P_左パンチ!" << endl;
				ks->SetLPunchP2();
				break;
			case MetsuHadou:
				cout << "2P_滅・波動拳!" << endl;
				ks->SetMetsuP2();
				break;
			case RKick:
				cout << "2P_右キック!" << endl;
				ks->SetMKickP2();
				//ks->SetHKickP2();
				break;
			case RPunch:
				cout << "2P_右パンチ!" << endl;
				ks->SetMPunchP2();
				//ks->SetHPunchP2();
				break;
			case ShinkuHadou:
				cout << "2P_真空波動拳!" << endl;
				ks->SetShinkuHadouP2();
				break;
			case Shoryuken:
				cout << "2P_昇竜拳!" << endl;
				ks->SetSyoryukenP2();
				break;

		}
		//Sleep(1000);
		return 0;
	}

	

	void call_thread()
	{
		DWORD dwExCode;
		if (hTh != NULL){
			GetExitCodeThread(hTh, &dwExCode);
			if (dwExCode == STILL_ACTIVE) {
//				printf("スレッド稼働中\n");
			} else {
				hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, (void *)ks, 0, &thID);
				if (hTh == 0) {
					printf("スレッド作成失敗\n");
					return;
				}
			}
		}
	}

public:
	CallCommand_2()
	{
		
		hTh = (HANDLE)1;
		new_command_flag = 0;
		ks = new KeyboardSimulator();
	}

	void SendCommand(int _command)
	{
		//cout<<"com "<<_command<<endl;
		if (_command < 0){
			return;
		} else {
			ks->command = _command;
			call_thread();
		}
	}

};*/



#endif//__KEYBOARDSIMULATOR_H