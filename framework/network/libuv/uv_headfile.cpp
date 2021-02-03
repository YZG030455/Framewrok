#include "uv_headfile.h"

#include <iostream>

/*!
 * @brief ����ָ����С�����ݿ飬���ڿ�����������
 * @attention һ���Է��䳤��<BUFFER_SIZEʱ��ֻ�����Ӧ��С�ĳ��ȣ�������ĳ���>BUFFER_SIZEʱ��ֻ����BUFFER_SIZE��������
 * @param[in] dataSize ���������ݿ鳤��
 * @return ���������
 */
WriteSegment* allocWriteSegment(int fullDataSize)
{
	WriteSegment * param = (WriteSegment*)malloc(sizeof(WriteSegment));

	int realAllocSize = fullDataSize > BUFFER_SIZE ? BUFFER_SIZE : fullDataSize;
	param->deleteable = false;
	param->dataBuff.base = (char*)malloc(realAllocSize);
	param->dataBuff.len = realAllocSize;
	param->dataLen = realAllocSize;
	return param;
}

void freeWriteSegment(WriteSegment* param)
{
	free(param->dataBuff.base);
	free(param);
}

string getLastUvError(int erroCode)
{
	if (0 == erroCode)
		return "";

	std::string err;

	auto tmpChar = uv_err_name(erroCode);
	if (tmpChar) {
		err = tmpChar;
		err += ":";
	}
	else {
		err = "unknown system erroCode " + std::to_string((long long)erroCode);
		err += ":";
	}

	tmpChar = uv_strerror(erroCode);

	if (tmpChar) {
		err += tmpChar;
	}
	return std::move(err);
}

void msleep(int millsecond)
{
#if OS_WIN
	Sleep(millsecond);
#elif OS_LINUX
	usleep(millsecond * 1000);
#endif
}
