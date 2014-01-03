#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION	1.0.0

class Pid {

	public:

		#define AUTOMATIC	1
		#define MANUAL	0
		#define DIRECT  0
		#define REVERSE  1

		Pid(double* input, double* output, double* setpoint,
			double Kp, double Ki, double Kd, int ControllerDirection);

		void setMode(int Mode);

		bool compute();

		void setOutputLimits(double minLimit, double maxLimit);

		void setTunings(double Kp, double Ki, double Kd);
		void setControllerDirection(int);
		void setSampleTime(int);


		double getKp();
		double getKi();
		double getKd();
		int getMode();
		int getDirection();

	private:

		void Initialize();

		double _dispKp;				// * we'll hold on to the tuning parameters in user-entered
		double _dispKi;				//   format for display purposes
		double _dispKd;				//

		double _Kp;                  // * (P)roportional Tuning Parameter
		double _Ki;                  // * (I)ntegral Tuning Parameter
		double _Kd;                  // * (D)erivative Tuning Parameter

		int _controllerDirection;

		double * _myInput;              // * Pointers to the Input, Output, and Setpoint variables
		double * _myOutput;             //   This creates a hard link between the variables and the
		double * _mySetpoint;           //   PID, freeing the user from having to constantly tell us
									  //   what these values are.  with pointers we'll just know.
		unsigned long _lastTime;
		double _ITerm, _lastInput;

		unsigned long _sampleTime;
		double _outMin, _outMax;
		bool _inAuto;
};

#endif

