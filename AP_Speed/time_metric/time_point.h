#ifndef MYSTL_D_TIME_POINT //!MYSTL_D_TIME_POINT
#define MYSTL_D_TIME_POINT

#include <chrono>

namespace time_metric
{
	class time_point
	{
	private:
		using time_point_t = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds>;
		
		time_point_t _point;

		explicit time_point(const time_point_t & p);
	public:
		time_point();
		
		time_point(const time_point & other);
		
		time_point(time_point && other);
		
		~time_point();

		time_point & operator = (const time_point & other);
		
		time_point & operator = (time_point && other);

		static unsigned long long int time_span(const time_point & former, const time_point & latter);

		static time_point make_point();
	};
}

#endif //!MYSTL_D_TIME_POINT

