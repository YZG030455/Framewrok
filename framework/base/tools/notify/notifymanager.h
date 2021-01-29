/*!
 * @brief     �Զ����Win10��Ϣ֪ͨ   
 * @author    wey
 * @version   1.0
 * @date      2021.01.29 16:23:22
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
 #pragma once

#include <QObject>
#include <QQueue>

#include "../../base_global.h"

namespace Base {

	class Notify;

	class BASESHARED_EXPORT NotifyManager : public QObject
	{
		Q_OBJECT

	public:
		NotifyManager(QObject *parent = nullptr);
		~NotifyManager();

		void information(QString content);
		void warning(QString content);

		void notify(const QString &title, const QString &icon, const QString &content);

		/*! 
		 * @brief ����֪ͨ�����ʾ����
		 * @details ������֪ͨ��������6��
		 * @param count >0
		 */
		void setMaxCount(ushort count);

		/*! 
		 * @brief ���õ���֪ͨ�ͣ��ʱ��
		 * @param ms ����
		 */
		void setDisplayTime(int ms);

	private:
		class NotifyData {
		public:
			NotifyData(const QString &icon, const QString &title, const QString &body) :
				icon(icon),title(title),body(body){}

			QString icon;
			QString title;
			QString body;
		};

		void reArrange();
		void showNext();

		QQueue<NotifyData> m_dataQueue;
		QList<Notify*> m_notifyList;	/*!< ��ǰ֪ͨ�б� */
		int m_maxCount;		/*!< �����ʾ֪ͨ���� */
		int m_displayTime;	/*!< ����֪ͨ���ʾʱ�� */
	};

} //namespace Base 