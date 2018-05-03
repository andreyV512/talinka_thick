#ifndef RThicknessH
#define RThicknessH

namespace RThickness
{
	/** @brief ��������� ������, ����������� ����� ��������� �������
	 */
	struct CurvePeak
	{
		// ! �������� ����� ��������� �� �������
		int X;
		// ! �������� ����� ��������� �� �������
		double Y;
		// ! ����������� �� ���������
		CurvePeak() : X(0), Y(0.0)
		{
		}

		// ! ����������� � �������������� ��������
		CurvePeak(int _X, double _Y) : X(_X), Y(_Y)
		{
		}
	};
};
#endif
