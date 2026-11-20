#ifndef miniBeastV1_h
#define miniBeastV1_h
		

class Movement{ 
	public: 
		Movement(); 
		void SETUP(); 
        void speedM1M2(int16_t speed1, int16_t speed2);
		//void S();
		int Trimpot(); 
        float VoltageIn(); 
		void ToggleLeds(int Time);
        void LipoCutOff(int Cell);
        void CounterLeds(int Time, int countx);
		void MotorControl(int RightMotorPwm, int LeftMotorPwm);
		byte mode();
		bool GetButton();
		void UserLed1(int Time);
        void UserLed2(int Time);
		
};



extern Movement movement; 
#endif