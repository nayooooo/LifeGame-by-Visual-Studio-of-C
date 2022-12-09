#include "myMem.h"
#include "sdkconfig.h"

/**
 * @fn void* myMemset_Uint32_t(void* _Dst, uint32_t _Val, size_t _Size)
 * @brief ��ʼ��32λ�޷����ڴ��
 * @param _Dst ����ʼ�����ڴ���׵�ַ
 * @param _Val ��ʼ����ֵ
 * @param _Size ����ʼ�����ڴ��С����32λΪ������λ��
 * @raturn void* ��ʼ������ڴ���׵�ַ
 */
void* myMemset_Uint32_t(void* _Dst, uint32_t _Val, size_t _Size) {
	uint32_t* _pDst = (uint32_t*)_Dst;

	while (_Size--) *_pDst++ = _Val;

	return _Dst;
}
