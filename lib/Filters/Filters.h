/*
	You should have received a copy of the GNU General Public License
   along with Leka. If not, see <http://www.gnu.org/licenses/>.
*/


// file Filters.h
// @author Gareth Dys
// @version 1.0

 #ifndef Filters_h
#define Filters_h

#include "RunningAverage.h"

class PID
{
	public:
	PID(void);
	explicit PID(const float, const float,const float);
	~PID();
	
	float CalculatePID(const float);
	//Impact Initial Angle
	void SetInitialAngle(const float);
	float GetInitialAngle();

	private:

	float _error;
	float _setPoint;
	float _input;

	//Angles Variables
	float _current_angle;
	float _InitialAngle;

	//Working variables
	float _CycleTime;
		//Init values of filter
	float _PIDOutput;
	float _Proportional;
	float _Derivative;
	float _Integral;

	//PID coefficients
	float _Kp;
	float _Ki;
	float _Kd;

	float _ErrorVariation;
	float _Error;

	RunningAverage _ErrorTracker;
	//constructeurs
	

	protected:

};

#endif