#include "global.h"

namespace Related {

	Base::RBlockingQueque<RequestUnit *> G_RequestQuque;				/*!< �ͻ���������� */
	Base::RBlockingQueque<FileRequestUnit *> G_FileRequestQuque;		/*!< �ļ��ͻ���������� */
} //namespace Related 