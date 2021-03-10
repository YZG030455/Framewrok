/*!
 * @brief     ����ԭʼ�����ļ�������߳�
 * @details	  �û�����ָ���ļ��������������ļ���Ϣ
 * @author    yzg
 * @version   1.0
 * @date      2021.03.10 10:33:51
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QObject>

namespace Related {

	class TaskRawDataFileCheckThread : public QObject
	{
		Q_OBJECT

	public:
		TaskRawDataFileCheckThread(QObject *parent = nullptr);
		~TaskRawDataFileCheckThread();

		void setRawDataFileRootPath(QString path);
		bool checkRawDataDir();
		QStringList getFileLists();

	private:
		bool dealRawDataDir(QString path);

	private:
		QString  m_rootPath;					/*!< ��Ŀ¼ */
		QStringList m_listFileNames;			/*!< �ļ��б� */
	};

}//namespace Related 