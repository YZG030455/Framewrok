/*!
 * @brief     ����ԭʼ�����ļ������߳�
 * @details	  �������񣬽�ԭʼ�����ļ����зֿ飬�ֿ鷢������
 * @author    yzg
 * @version   1.0
 * @date      2021.03.10 09:23:35
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>

#include <core/network/rtask.h>

namespace Related {

	class TaskRawDataFileDealThread : public Core::RTask
	{
		Q_OBJECT

	public:
		TaskRawDataFileDealThread(QObject *parent = nullptr);
		~TaskRawDataFileDealThread();

		void setTaskId(QString taskId);
		void setFilePats(QStringList pathList);

		void startMe();
		void stopMe();

	protected:
		void run();

	private:
		void dealFile();
		void dealSingleFile(QString filePath);

		void sendNewTaskRawDataFile(QByteArray buff);

	private:
		QString m_taskId;
		QStringList m_rawDataList;
		double m_totalFileSize;
	};

}//namespace Related 