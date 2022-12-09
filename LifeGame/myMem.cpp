#include "myMem.h"
#include "sdkconfig.h"

/**
 * @fn void* myMemset_Uint32_t(void* _Dst, uint32_t _Val, size_t _Size)
 * @brief 初始化32位无符号内存段
 * @param _Dst 被初始化的内存段首地址
 * @param _Val 初始化的值
 * @param _Size 被初始化的内存大小（以32位为计数单位）
 * @raturn void* 初始化后的内存段首地址
 */
void* myMemset_Uint32_t(void* _Dst, uint32_t _Val, size_t _Size) {
	uint32_t* _pDst = (uint32_t*)_Dst;

	while (_Size--) *_pDst++ = _Val;

	return _Dst;
}
