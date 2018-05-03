#ifndef uCFFTH
#define uCFFTH
#include <IniFiles.hpp>

//! ����� �� ������� ��� �������
class CFFT
{

private:
	int *h;
	double *c;
	int n;
	int m;
	int nv;
	void Direct(double* x);
	void Inverse(double* x);
	void Spectrum(double* x);
	int size;
	double* BUF;
	double* BUF_spectro;
	bool CFFT_256;
	int acfBorderLeft;
	int acfBorderRight;
	TIniFile* ini;
public:
	//! ����������� � �������� �������
	CFFT(int _size,TIniFile* _ini);
	//! ����������
	~CFFT(void);
	//! @brief ������ ���
	//! @param _buf ������ � �������� ��������, ��� �������� ����� ���������.
	//! retval ������������ ������ ������������ � ���� �� ���������� _buf
	void Calc(double* _buf);
	//! @brief ������ ���
	//! @param _buf ������ � �������� ��������, ��� �������� ����� ���������.
	//! retval ������������ ������ ������������ � ���� �� ���������� _buf
	void Calc(char* _buf);
	inline int GetBufSize(void)
	{
		return (n);
	};
	inline int GetSize(void)
	{
		return (size);
	};
	inline int GetHalfBufSize(void)
	{
		return (nv);
	};
	inline double* GetBUF(void)
	{
		return(BUF);
	};
	inline double* GetBUFSpectro(void)
	{
		return(BUF_spectro);
	};
	inline int GetBorderLeft(void)
	{
		return(acfBorderLeft);
	}
	inline int GetBorderRight(void)
	{
		return(acfBorderRight);
	}
	void SetBorders(int _acfBorderLeft,int _acfBorderRight);
};
#endif
