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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);

	}

	// 1P�ŁE�g����
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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P�ŁE�g����
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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P��p���`
	void SetLPunchP1()
	{
		//KeyAction('D', TRUE);
		//Sleep(20);
		//KeyAction('D', FALSE);
		KeyAction('A', TRUE);
		Sleep(20);
		KeyAction('A', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P��p���`
	void SetLPunchP2()
	{
		KeyAction('4', TRUE);
		Sleep(20);
		KeyAction('4', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P��L�b�N
	void SetLKickP1()
	{
		//KeyAction('E', TRUE);
		//Sleep(20);
		//KeyAction('E', FALSE);
		KeyAction('Z', TRUE);
		Sleep(20);
		KeyAction('Z', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P��L�b�N
	void SetLKickP2()
	{
		KeyAction('1', TRUE);
		Sleep(20);
		KeyAction('1', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P���p���`
	void SetMPunchP1()
	{
		//KeyAction('F', TRUE);
		//Sleep(20);
		//KeyAction('F', FALSE);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction('S', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P���p���`
	void SetMPunchP2()
	{
		KeyAction('5', TRUE);
		Sleep(20);
		KeyAction('5', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P���L�b�N
	void SetMKickP1()
	{
		KeyAction('R', TRUE);
		Sleep(20);
		KeyAction('R', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P���L�b�N
	void SetMKickP2()
	{
		KeyAction('2', TRUE);
		Sleep(20);
		KeyAction('2', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P���p���`
	void SetHPunchP1()
	{
		KeyAction('D', TRUE);
		Sleep(20);
		KeyAction('D', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P���p���`
	void SetHPunchP2()
	{
		KeyAction('8', TRUE);
		Sleep(20);
		KeyAction('8', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 1P���L�b�N
	void SetHKickP1()
	{
		//KeyAction('G', TRUE);
		//Sleep(20);
		//KeyAction('G', FALSE);
		KeyAction('C', TRUE);
		Sleep(20);
		KeyAction('C', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P���L�b�N
	void SetHKickP2()
	{
		KeyAction('6', TRUE);
		Sleep(20);
		KeyAction('6', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}	

	// 1P�^��g����
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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(3000);
	}

	// 2P�^��g����
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
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
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

	// 1P�K�[�h
	void SetGuardP1() 
	{
		KeyAction(VK_LEFT, TRUE, KEYEVENTF_EXTENDEDKEY);
		Sleep(1000);
		KeyAction(VK_LEFT, FALSE, KEYEVENTF_EXTENDEDKEY);
		//KeyAction('A', TRUE);
		//Sleep(50);
		//KeyAction('A', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(1200);
	}

	// 2P�K�[�h
	void SetGuardP2()
	{
		KeyAction('K', TRUE);
		Sleep(50);
		KeyAction('K', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(1000);
	}

	// 1P���i�U��(�����E�E��������)
	void SetChudanP1()
	{
		KeyAction(VK_RIGHT, TRUE, KEYEVENTF_EXTENDEDKEY);
		KeyAction('S', TRUE);
		Sleep(20);
		KeyAction(VK_RIGHT, FALSE, KEYEVENTF_EXTENDEDKEY);
		KeyAction('S', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
		Sleep(2000);
	}

	// 2P���i�U��(�����E�E��������)
	void SetChudanP2()
	{
		KeyAction('J', TRUE);
		KeyAction('5', TRUE);
		Sleep(20);
		KeyAction('J', FALSE);
		KeyAction('5', FALSE);
		// ���[�U���삪�I���܂Ŏ��Ԃ�������̂ŁA����܂Œ�~
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

/********** 1P���̃R�}���h�Ăяo�� *** Class to call 1 player's command *******/
class CallCommand{

private:
    unsigned int thID;
    HANDLE hTh;
	int new_command_flag;
public:
	KeyboardSimulator *ks;

	//�X���b�h�p�֐�
	static unsigned __stdcall mythread(void *lpx)
	{
		KeyboardSimulator *ks = (KeyboardSimulator *)lpx;
		KeyboardSimulator *ks2 = (KeyboardSimulator *)lpx;

		switch(ks->command){
			case Chudan:
				//ks->print_flg = true;
				cout << "1P_���i�U��! Chudan!" << endl;
				ks->SetChudanP1();
				break;

			case Guard:
				//ks->print_flg = true;
				cout << "1P_�K�[�h!" << endl;
				ks->SetGuardP1();
				break;

			case Hadouken:
				//ks->print_flg = true;
				cout << "1P_�g����! Hadouken!" << endl;
				ks->SetHadoukenP1();
				break;

			case Jump:
				//ks->print_flg = true;
				cout << "1P_Jump!" << endl;
				ks->SetJumpP1();
				break;

			/*case LKick:
				//ks->print_flg = true;
				cout << "1P_���L�b�N!" << endl;
				ks->SetLKickP1();
				break;
			
			case MetsuHadou:
				//ks->print_flg = true;
				//cout << "1P_MetsuHadou!" << endl;
				//ks->SetMetsuP1();
				cout << "1P_�g����!" << endl;
				ks->SetHadoukenP1();
				
				break;
			case RKick:
				cout << "1P_�E�L�b�N!" << endl;
				//ks->SetMKickP1();
				//ks->print_flg = true;
				ks->SetHKickP1();
				break;*/

			case LPunch:
				cout << "1P_���p���`!" << endl;
				ks->SetLPunchP1();
				//ks->print_flg = true;
				break;

			case MPunch:
				//ks->print_flg = true;
				cout << "1P_�E�p���`!" << endl;
				ks->SetMPunchP1();
				break;

			case HPunch:
				cout << "1P_Big ���p���`!" << endl;
				ks->SetHPunchP1();
				//ks->print_flg = true;
				break;

			/*case ShinkuHadou:
				//ks->print_flg = true;
				//cout << "1P_ShinkuHadou!" << endl;
				//ks->SetShinkuHadouP1();
				cout << "1P_�g����!" << endl;
				ks->SetHadoukenP1();
				break;*/

			case Shoryuken:
				//ks->print_flg = true;
				cout << "1P_������! Shoryuken!" << endl;
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
//				printf("�X���b�h�ғ���\n");
			} else {	//Movement detected
				hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, (void *)ks, 0, &thID);
				if (hTh == 0) {
					printf("�X���b�h�쐬���s\n");
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

/********** 2P���̃R�}���h�Ăяo�� **********/
/*class CallCommand_2{

private:
    unsigned int thID;
    HANDLE hTh;
	int new_command_flag;
	KeyboardSimulator *ks;
	bool write_flg;

	//�X���b�h�p�֐�
	static unsigned __stdcall mythread(void *lpx)
	{
		KeyboardSimulator *ks = (KeyboardSimulator *)lpx;


		switch(ks->command){
			case Chudan:
				cout << "2P_���i�U��!" << endl;
				ks->SetChudanP2();
				break;
			case Guard:
				cout << "2P_�K�[�h�I" << endl;
				ks->SetGuardP2();
				break;
			case Hadouken:
				cout << "2P_�g����!" << endl;
				ks->SetHadoukenP2();
				break;
			case LKick:
				cout << "2P_���L�b�N!" << endl;
				ks->SetLKickP2();
				break;
			case LPunch:
				cout << "2P_���p���`!" << endl;
				ks->SetLPunchP2();
				break;
			case MetsuHadou:
				cout << "2P_�ŁE�g����!" << endl;
				ks->SetMetsuP2();
				break;
			case RKick:
				cout << "2P_�E�L�b�N!" << endl;
				ks->SetMKickP2();
				//ks->SetHKickP2();
				break;
			case RPunch:
				cout << "2P_�E�p���`!" << endl;
				ks->SetMPunchP2();
				//ks->SetHPunchP2();
				break;
			case ShinkuHadou:
				cout << "2P_�^��g����!" << endl;
				ks->SetShinkuHadouP2();
				break;
			case Shoryuken:
				cout << "2P_������!" << endl;
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
//				printf("�X���b�h�ғ���\n");
			} else {
				hTh = (HANDLE)_beginthreadex(NULL, 0, mythread, (void *)ks, 0, &thID);
				if (hTh == 0) {
					printf("�X���b�h�쐬���s\n");
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