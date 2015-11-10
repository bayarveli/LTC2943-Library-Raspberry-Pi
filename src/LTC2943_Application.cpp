//============================================================================
// Name        : LTC2943_Application.cpp
// Author      : Veli Bayar
// Version     :
// Copyright   : @openSourceDeveloper
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <signal.h>
#include <iomanip>

//#include <sys/types.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <sys/stat.h>
#include "lib/IMI2C.h"
#include "lib/LTC2943.h"

#define AUTOMATIC_MODE 					0xC0
#define SCAN_MODE						0x80
#define MANUAL_MODE						0x40
#define SLEEP_MODE						0x00

#define PRESCALER_1						0x00
#define PRESCALER_4						0x08
#define PRESCALER_16					0x10
#define PRESCALER_64					0x18
#define PRESCALER_256					0x20
#define PRESCALER_1024					0x28
#define PRESCALER_4096					0x30
#define PRESCALER_4096_2				0x31

#define ALERT_MODE						0x04
#define CHARGE_COMPLETE_MODE			0x02
#define DISABLE_ALCC_PIN				0x00

#define SHUTDOWN_MODE					0x01

using namespace std;

// The flag for terminating program
bool terminateProg = true;

// Signal handler for understanding CTRL+C pressed or not
void sighandler(int sig)
{
	cout << "Terminating..." << endl;

	terminateProg = false;
}

int main()
{
	key_t key;
	sem_t *mutex;
	FILE *fd;

	int i_status = 0;

	LTC2943 batteryReader = LTC2943(0x64,string("/dev/i2c-1"), mutex);

	float voltage, current, accCharge, temperature;
	int statusReg, voltageThresholdLow;

	batteryReader.setControlRegister(AUTOMATIC_MODE,PRESCALER_4096, ALERT_MODE);

	i_status = batteryReader.setVoltageThresholdHigh(7.5);

	i_status = batteryReader.setVoltageThresholdLow(4.5);

	/* Signal handler for catching "CTRL+C" and break the while loop*/
	signal(SIGINT,&sighandler);

	char KeyPress = 0;

	while(terminateProg)
	{
		cout << "Press Read (r), Alert Reset (a):" << endl;
		cin >> KeyPress;

		switch(KeyPress)
		{
			case 'r':
				accCharge = batteryReader.readAccumulatedCharge();
				voltage = batteryReader.readVoltage();
				current = batteryReader.readCurrent();
				temperature = batteryReader.readTemperature();
				statusReg = batteryReader.readStatusRegister();

				cout << "Status Register: ";
				cout << std::hex << statusReg << endl;
				cout << "Accumulated Charge: ";
				cout << accCharge << endl;
				cout << "Voltage: ";
				cout << voltage << endl;
				cout << "Current: ";
				cout << current << endl;
				cout << "Sıcaklık: ";
				cout << temperature << endl;
				cout << endl;
				break;
			case 'a':
				i_status = batteryReader.resetAlertStatus();
				cout << "Alert Response: ";
				cout << i_status << endl;
				break;
		}
	}

	return 0;
}
