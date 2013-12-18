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

		void SetTunings(double Kp, double Ki, double Kd);
		void SetControllerDirection(int);
		void SetSampleTime(int);


		double GetKp();
		double GetKi();
		double GetKd();
		int GetMode();
		int GetDirection();

	private:

		void Initialize();

		double dispKp;				// * we'll hold on to the tuning parameters in user-entered
		double dispKi;				//   format for display purposes
		double dispKd;				//

		double kp;                  // * (P)roportional Tuning Parameter
		double ki;                  // * (I)ntegral Tuning Parameter
		double kd;                  // * (D)erivative Tuning Parameter

		int controllerDirection;

		double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
		double *myOutput;             //   This creates a hard link between the variables and the
		double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
									  //   what these values are.  with pointers we'll just know.
		unsigned long lastTime;
		double ITerm, lastInput;

		unsigned long SampleTime;
		double outMin, outMax;
		bool inAuto;
};

#endif

