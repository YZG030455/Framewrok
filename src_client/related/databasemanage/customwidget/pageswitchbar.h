/*!
 * @brief     ҳ���л�������
 * @details	  �ṩͨ�õĵ�ҳ���л�����������л���ҳ����һҳ����һҳ��βҳ
 * @author    wey
 * @version   1.0
 * @date      21.01.14 14:43:19
 * @warning
 * @copyright NanJing RenGu.
 * @note
 */
#pragma once

#include <QWidget>
#include <base\selfwidget\iconbutton.h>

class QComboBox;
class QLineEdit;

namespace Related {

	class PageSwitchBar : public QWidget
	{
		Q_OBJECT

	public:
		PageSwitchBar(QWidget *parent = nullptr);
		~PageSwitchBar();

		void setDataSize(int dataSize);

	signals:
		void perPageNumsChanged(int perPageNum);
		void switchPage(int curPage);

	private slots:
		void respPageCountChanged(int pageIndex);
		void buttPressed();

	private:
		void init();

		void reCalc();
		void updateButtState();
		void updatePageIndicate();

	private:
		enum ButtType {
			FIRST_PAGE,
			PRI_PAGE,
			NEXT_PAGE,
			LAST_PAGE
		};

	private:
		Base::RIconButton * m_firstButton;
		Base::RIconButton * m_prePageButton;
		Base::RIconButton * m_nextPageButton;
		Base::RIconButton * m_lastButton;

		QComboBox * m_pageItemCountBox;
		QLineEdit * m_pageNumLabel;

		int m_dataSize;				/*!< �������� */
		int m_pageCount;			/*!< ҳ������ */
		int m_currPage;				/*!< ��ǰҳ������ */
		int m_perPageItemCount;		/*!< ��ǰҳ���������� */		
	};

} //namespace Related 
