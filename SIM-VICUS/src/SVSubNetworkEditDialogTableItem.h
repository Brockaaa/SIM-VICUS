#ifndef SVSUBNETWORKEDITDIALOGTABLEITEM_H
#define SVSUBNETWORKEDITDIALOGTABLEITEM_H

#include <QWidget>

namespace Ui {
class SVSubNetworkEditDialogTableItem;
}

class SVSubNetworkEditDialogTableItem : public QWidget
{
	Q_OBJECT

public:
	explicit SVSubNetworkEditDialogTableItem(QString filename, QString typeName, QString tooltip, int height, QWidget *parent = nullptr, bool subCategory = false, bool inbuild = true);
	~SVSubNetworkEditDialogTableItem();

	// TODO Maik: comment! Das soll heißen builtIn ?
	bool m_inbuild;

	// TODO Maik: implement local
	// DB Elemente können 1 aus 3 Zuständen haben: local, userDB, builtIn. Diese sind durch die Flags local und builtIn definiert.
	// Ich weiß, ist nicht optimal das durch 2 bools zu machen aber historisch so gewachsen. Das müsstest du so durchziehen. local elemente haben schwarzen Hintergrund, userDB elemente blauen Hintergrund (userDBBackground)
	// und builtIn elemente haben grünen Background (alternativeBackgroundColor)
	// Die selection color sollte immer gelb sein, das ist die default color für selections im gesamten Programm, muss normalerweise nicht explizit gesetzt werden.
	// Als Beispiel kannst du einen anderen DB Dialog z.b. Pipes anschauen.
	bool m_local;

private:
	Ui::SVSubNetworkEditDialogTableItem *m_ui;
};

#endif // SVSUBNETWORKEDITDIALOGTABLEITEM_H
