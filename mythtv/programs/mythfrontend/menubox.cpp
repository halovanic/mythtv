#include <qlayout.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qcursor.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qbitmap.h>

#include "menubox.h"
#include "settings.h"

extern Settings *globalsettings;

MenuBox::MenuBox(const char *text, QWidget *parent, 
                 const char *name)
       : QDialog(parent, name)
{
    int screenheight = QApplication::desktop()->height();
    int screenwidth = QApplication::desktop()->width();

    if (globalsettings->GetNumSetting("GuiWidth") > 0)
        screenwidth = globalsettings->GetNumSetting("GuiWidth");
    if (globalsettings->GetNumSetting("GuiHeight") > 0)
        screenheight = globalsettings->GetNumSetting("GuiHeight");

    float wmult = screenwidth / 800.0;
    float hmult = screenheight / 600.0;

    setGeometry(0, 0, screenwidth, screenheight);
    setFixedWidth(screenwidth);
    setFixedHeight(screenheight);

    setFont(QFont("Arial", 40 * hmult, QFont::Bold));
    setCursor(QCursor(Qt::BlankCursor));

    QLabel *maintext = new QLabel(text, this);
    maintext->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    maintext->setFont(QFont("Arial", 40 * hmult, QFont::Bold));

    box = new QVBoxLayout(this, 20 * wmult);

    box->addWidget(maintext, 0);

    buttongroup = new QButtonGroup(0);

    setFont(QFont("Arial", 16 * hmult, QFont::Bold));

    connect(buttongroup, SIGNAL(clicked(int)), this, SLOT(buttonPressed(int)));
}

void MenuBox::AddButton(const char *title)
{
    QPushButton *button = new QPushButton(title, this);
    buttongroup->insert(button);

    box->addWidget(button, 2);
}

void MenuBox::Show()
{
    showFullScreen();
    setActiveWindow();
}

void MenuBox::buttonPressed(int which)
{
    done(which + 1);
}
