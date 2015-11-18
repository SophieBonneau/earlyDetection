// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
// Myo sensor records with a 50Hz frequency
#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

#include "atltime.h"
#include <process.h>
#include <conio.h>

// The only file that needs to be included to use the Myo C++ SDK is myo.hpp.
#include <myo/myo.hpp>

#include "DetectEvent.h"


static ofstream ofs[nMyoSensors];
//static ofstream test[nMyoSensors];


// Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behavior is to do nothing.
class DataCollector : public myo::DeviceListener {
public:
	DataCollector()
		: onArm(false), isUnlocked(false), currentPose(), emgSamples()
	{
	}

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp)
	{
		// We've lost a Myo.
		// Let's clean up some leftover state.
		onArm = false;
		isUnlocked = false;
		emgSamples[identifyMyo(myo)].fill(0);
	}

	//onPair() is called when a Myo has been paired
	void onPair(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
	{
		// Add the Myo pointer to our list of known Myo devices. This list is used to implement identifyMyo() below so
		// that we can give each Myo a nice short identifier.
		knownMyos.push_back(myo);

		// Now that we've added it to our list, get our short ID for it and print it out.
		std::cout << "Paired with " << identifyMyo(myo) << "." << std::endl;
	}

	//onConnect() is called when a paired Myo has been connected
	void onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
	{
		std::cout << "Myo " << identifyMyo(myo) << " has connected." << std::endl;
		myo->setStreamEmg(myo::Myo::streamEmgEnabled);
	}

	//onDisconnect() is called when a paired Myo has been disconnected
	void onDisconnect(myo::Myo* myo, uint64_t timestamp)
	{
		std::cout << "Myo " << identifyMyo(myo) << " has disconnected." << std::endl;
	}

	// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
	// as a unit quaternion.
	/*void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
	{
		using std::atan2;
		using std::asin;
		using std::sqrt;
		using std::max;
		using std::min;

		// Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
		roll[identifyMyo(myo)] = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
			1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
		pitch[identifyMyo(myo)] = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
		yaw[identifyMyo(myo)] = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
			1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

		//ofs[identifyMyo(myo) - 1] << roll << "," << pitch << "," << yaw << ",";
	}*/

	// onAccelerometerData() is called whenever the Myo device provides its current acceleration, which is represented
	// as a three-dimensional vector.
	void onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel){
		CTime u_time = CTime::GetCurrentTime();
		accel_x[identifyMyo(myo)] = accel.x();
		accel_y[identifyMyo(myo)] = accel.y();
		accel_z[identifyMyo(myo)] = accel.z();
	}

	// onGyroscopeData() is called whenever the Myo device provides its current angular velocity, which is represented
	// as a three-dimensional vector.
	void onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro){

		gyro_x[identifyMyo(myo)] = gyro.x();
		gyro_y[identifyMyo(myo)] = gyro.y();
		gyro_z[identifyMyo(myo)] = gyro.z();
	}

	// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enable
	void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
	{
		for (int i = 0; i < 8; i++){
			emgSamples[identifyMyo(myo)][i] = emg[i];			
			
		}
	}

	// This is a utility function implemented for this sample that maps a myo::Myo* to a unique ID starting at 1.
	// It does so by looking for the Myo pointer in knownMyos, which onPair() adds each Myo into as it is paired.
	size_t identifyMyo(myo::Myo* myo) {
		// Walk through the list of Myo devices that we've seen pairing events for.
		for (size_t i = 0; i < knownMyos.size(); ++i) {
			// If two Myo pointers compare equal, they refer to the same Myo device.
			if (knownMyos[i] == myo) {
				return i + 1;
			}
		}
		return 0;
	}

	// We define this function to print the current values that were updated by the on...() functions above.
	void print(NormParam* param)
	{		
		for (int sens = 0; sens < nMyoSensors; sens++) {

			//Print acceleration and orientation results in the csv file
			/*seq(0+DIM*sens, compt) = accel_x[sens];
			seq(1+DIM*sens, compt) = accel_y[sens];
			seq(2+DIM*sens, compt) = accel_z[sens];
			seq(3+DIM*sens, compt) = roll[sens];
			seq(4+DIM*sens, compt) = pitch[sens];
			seq(5+DIM*sens, compt) = yaw[sens];*/

			//Normalized data
			seq(0+DIM*sens, compt) = (accel_x[sens] - param->mean(14*sens + 0,0))/param->stand_dev(14*sens + 0,0);
			seq(1+DIM*sens, compt) = (accel_y[sens] - param->mean(14*sens + 1,0))/param->stand_dev(14*sens + 1,0);
			seq(2+DIM*sens, compt) = (accel_z[sens] - param->mean(14*sens + 2,0))/param->stand_dev(14*sens + 2,0);
			seq(3+DIM*sens, compt) = (gyro_x[sens] - param->mean(14*sens + 3,0))/param->stand_dev(14*sens + 3,0);
			seq(4+DIM*sens, compt) = (gyro_y[sens] - param->mean(14*sens + 4,0))/param->stand_dev(14*sens + 4,0);
			seq(5+DIM*sens, compt) = (gyro_z[sens] - param->mean(14*sens + 5,0))/param->stand_dev(14*sens + 5,0);

			//ofs[sens] << accel_x[sens] << "," << accel_y[sens] << "," << accel_z[sens] << "," << roll[sens] << "," << pitch[sens] << "," << yaw[sens] << "," ;

			// Print out the EMG data
			for (size_t i = 0; i < emgSamples[sens].size(); i++){
				//seq(6 + i + DIM*sens, compt) = emgSamples[sens][i];
				seq(6 + i + DIM*sens, compt) = (emgSamples[sens][i] - param->mean(6 + 14*sens + i,0))/param->stand_dev(6 + 14*sens + i,0);	//Normalization of EMG data

				/*std::ostringstream oss;
				oss << static_cast<double>(seq(6 + i + DIM*sens, compt));
				std::string emgString = oss.str();

				ofs[sens] << emgString << ",";*/
			}
			//ofs[sens] << endl;
		}

		compt++;
	}

	// These values are set by onArmSync() and onArmUnsync() above.
	bool onArm;
	myo::Arm whichArm;

	// This is set by onUnlocked() and onLocked() above.
	bool isUnlocked;

	// These values are set by onOrientationData() and onPose() above.
	myo::Pose currentPose;

	//float roll[nMyoSensors], pitch[nMyoSensors], yaw[nMyoSensors];
	float accel_x[nMyoSensors], accel_y[nMyoSensors], accel_z[nMyoSensors];
	float gyro_x[nMyoSensors], gyro_y[nMyoSensors], gyro_z[nMyoSensors];
	std::array<int8_t, 8> emgSamples[nMyoSensors];

	// We store each Myo pointer that we pair with in this list, so that we can keep track of the order we've seen
	// each Myo and give it a unique short identifier (see onPair() and identifyMyo() above).
	std::vector<myo::Myo*> knownMyos;
};



int main(int argc, char** argv)
{
	//Initialisation
	const char *hadou_file = "./training_set/Hadou.mat";
	const char *jump_file = "./training_set/Jump.mat";
	const char *mpunch_file = "./training_set/Punch.mat"; 
	const char *shoryu_file = "./training_set/Shoryu.mat";
	const char *squat_file = "./training_set/Squat.mat";

	//1 number = 1 movement (ex: 1=>hadouken)
	//To see the corresponding number, let see the KeyboardSimulator.h file
	//The second number correspond to the associate thresholds
	DetectEvent* event_hadou = new DetectEvent(hadou_file,1,1.6); 
	DetectEvent* event_jump = new DetectEvent(jump_file,2,0.5);
	DetectEvent* event_mpunch = new DetectEvent(mpunch_file,3,1.5);
	DetectEvent* event_shoryu = new DetectEvent(shoryu_file,4,1.8);
	DetectEvent* event_squat = new DetectEvent(squat_file,5,1.9);

	const char *norm_file = "./norm_param_1206nomvt.mat";
	NormParam* param = new NormParam(norm_file);
	
	// We catch any exceptions that might occur below -- see the catch statement for more details.
	try{
		
		/*CTime c_time = CTime::GetCurrentTime();
		unsigned char YY = c_time.GetYear() - 2000;
		unsigned char MM = c_time.GetMonth();
		unsigned char DD = c_time.GetDay();
		unsigned char hh = c_time.GetHour();
		unsigned char mm = c_time.GetMinute();
		unsigned char ss = c_time.GetSecond();

		char filename[256];
		//char filen[256];
		for (int i = 0; i < nMyoSensors; i++) {
			sprintf_s(filename, sizeof(filename), "%02d%02d%02d_%02d%02d%02d_%i.csv", YY, MM, DD, hh, mm, ss,i);
			ofs[i] = ofstream(filename, ios::app);
			//sprintf_s(filen, sizeof(filen), "%02d%02d%02d_%02d%02d%02d_test%i.csv", YY, MM, DD, hh, mm, ss,i);
			//test[i] = ofstream(filen,ios::app);
		}*/
		

		// First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
		// publishing your application. The Hub provides access to one or more Myos.
		myo::Hub hub("com.limu.hello-myo");  

		std::cout << "Attempting to find a Myo..." << std::endl;

		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		myo::Myo* myo = hub.waitForMyo(10000);

		// If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!"); 
		}
		
		// We've found a Myo.
		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

		// Next we enable EMG streaming on the found Myo.
		myo->setStreamEmg(myo::Myo::streamEmgEnabled);

		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
		DataCollector collector;

		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners.
		hub.addListener(&collector);
		

		// Finally we enter our main loop.
		while (1) {
			// In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
			// In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
			hub.run(1000 / 50);
			
			// After processing events, we call the print() member function we defined above to print out the values we've
			// obtained from any events that have occurred.
			collector.print(param);

			//Create threads to recognize event 
			if(compt == MINLENGTH+10){	//Compute the similarity of the first 30 frames
				event_hadou ->call_comp();
				event_jump ->call_comp();
				event_mpunch ->call_comp();
				event_shoryu ->call_comp();
				event_squat ->call_comp();
			}
			if(compt > MINLENGTH+10 && compt%STRIDE == 0) {	//Compute the detection score function for each stride of frames
				event_hadou ->call_recognize();
				event_jump ->call_recognize();
				event_mpunch ->call_recognize();
				event_shoryu ->call_recognize();
				event_squat ->call_recognize();
			}
		}

	}

	// If a standard exception occurred, we print out its message and exit.
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           