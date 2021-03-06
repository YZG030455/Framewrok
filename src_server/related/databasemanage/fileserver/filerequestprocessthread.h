/*!
 * @brief     数据文件请求解析线程
 * @details 
 * @author    yzg
 * @version   1.0
 * @date      2021.03.10 08:25:36
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>

#include <core/network/rtask.h>
#include <commondefines/protocol.h>
#include <base\common\sql\databasemanager.h>

#include "../datastruct.h"
#include "../business/fileprocesscenter.h"

namespace Related {

	struct FileRequestUnit;

	class FileRequestProcessThread : public Core::RTask
	{
		Q_OBJECT

	public:
		FileRequestProcessThread(QObject *parent = nullptr);
		~FileRequestProcessThread();

		void startMe();
		void stopMe();

	protected:
		void run();

	private: 
		void parseFileRequest(FileRequestUnit * unit);

	private:
		Base::Database * m_dbConnect;						/*!< 数据库 */
		FileProcessCenter m_processCenter;					/*!< 文件处理 */
	};

}//namespace Related 