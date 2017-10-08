#ifndef _BALL_SPHERICAL_HPP_
#define _BALL_SPHERICAL_HPP_

//#pragma message(__DATE__ "  " __TIME__"  ���ڱ���"__FILE__)

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "math/basic_math.hpp"

namespace spherical
{
	namespace
	{
		using namespace std;
	}

	double rad_to_angle(double i);
	double angle(double degree, double min = 0.0, double sec = 0.0);

	double MOD(double x, double y);   //������������������� ����ķ����������ͬ��

	inline double standard_longitude(double x)
	{
		return MOD(x + 180, 360) - 180;
	}

	inline double standard_latitude(double x)
	{
		return -fabs(MOD(x + 90, 360) - 180) + 90;
	}

	class Spherical
	{
		public:
			double longitude, latitude, height;   //����, γ��
			static const double R;   //����뾶6371004m
			string comment;

			Spherical(double longitude, double latitude, double height = 0.0, const string &comment = "")
			{
				this->longitude = standard_longitude(longitude);
				this->latitude = standard_latitude(latitude);
				this->height = height;
				this->comment = comment;
			}

			void standard()
			{
				longitude = standard_longitude(longitude);
				latitude = standard_latitude(latitude);
			}

			string to_string() const;
			friend ostream& operator <<(ostream &output, const Spherical &s);
	};

	double ball_distance(const Spherical &a, const Spherical &b);
	double real_distance(const Spherical &a, const Spherical &b);

} /* Namespace spherical */

#endif	/* End _SPHERICAL_HPP_ */
