#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

class QLabel;
// ======================================================================
class AboutDialog : public QDialog {
    Q_OBJECT
private:

public:
    AboutDialog(QWidget* pwgt = 0);

};


#endif // ABOUT_H
