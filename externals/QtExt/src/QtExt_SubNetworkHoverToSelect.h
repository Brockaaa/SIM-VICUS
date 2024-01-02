#ifndef QTEXT_SUBNETWORKHOVERTOSELECT_H
#define QTEXT_SUBNETWORKHOVERTOSELECT_H

#include <QWidget>
#include <QLabel>

class QtExt_SubNetworkHoverToSelect : public QWidget
{
	Q_OBJECT

public:
	explicit QtExt_SubNetworkHoverToSelect(QWidget *parent = nullptr);

	void setThumbnail(const QPixmap &thumbnail);

signals:

	void thumbNailClicked();

protected:
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QLabel					*label;
	QPixmap					*m_thumbNail;

	/*! Editing icon */
	QPixmap					*m_icon = new QPixmap (QPixmap(":/gfx/master/editscene_green.png"));
};

#endif // QTEXT_SUBNETWORKHOVERTOSELECT_H
